
#import "ObjCBridge.h"
#import <UIKit/UIKit.h>
#import "MailViewController.h"
#import "UIWebViewController.h"
#import "MessageBoxDelegate.h"
#import "SDL.h"
#import "SDL_syswm.h"
#import "CPPBridge.h"
#include <math.h>
#include <sys/time.h>

//static NSDate*startDate = nil;
static iCadeControllerReceiver* iCade_receiver = nil;

static iCadeEventCallback iCade_stateChangedCallback = NULL;
static iCadeEventCallback iCade_buttonDownCallback = NULL;
static iCadeEventCallback iCade_buttonUpCallback = NULL;

void GameEngine_init()
{
	/*if(startDate==nil)
	{
		startDate = [[NSDate alloc] initWithTimeInterval:0 sinceDate:[NSDate date]];
	}*/
}

UIViewController*getSDLViewController(SDL_Window*window)
{
	SDL_SysWMinfo systemWindowInfo;
    SDL_VERSION(&systemWindowInfo.version);
    if ( ! SDL_GetWindowWMInfo(window, &systemWindowInfo))
	{
        // consider doing some kind of error handling here 
        return nil;
    }
    UIWindow * appWindow = systemWindowInfo.info.uikit.window;
    UIViewController * rootViewController = appWindow.rootViewController;
    return rootViewController;
}

void openURL(const char*url, SDL_Window*window)
{
	if(window==NULL)
	{
		[[UIApplication sharedApplication] openURL:[NSURL URLWithString:[NSString stringWithUTF8String:url]]];
	}
	else
	{
		UIWebViewController* webview = [[UIWebViewController alloc] init];
		UIViewController*viewCtrl = getSDLViewController(window);
		if(viewCtrl==nil)
		{
			return;
		}
		[webview openSite:[NSString stringWithUTF8String:url] inViewController:viewCtrl];
		
		while([webview isOpened])
		{
			updateAppEvents();
			SDL_Delay(30);
		}
		[webview release];
	}
}

void writeEmail(SDL_Window*window, const char*recipient, const char*subject, const char*body)
{
	MailViewController *mailer = [[MailViewController alloc] init];
	//SDL_HideWindow(window);
	UIViewController*viewCtrl = getSDLViewController(window);
	if(viewCtrl==nil)
	{
		NSLog(@"%s", "Error getting SDL ViewController");
		return;
	}
	[mailer openMailInViewController:viewCtrl person:[NSString stringWithUTF8String:recipient] subject:[NSString stringWithUTF8String:subject] body:[NSString stringWithUTF8String:body]];
	
	while([mailer isOpened])
	{
		updateAppEvents();
		SDL_Delay(30);
	}
	[mailer release];
}

void getDeviceModel(char*deviceString)
{
	if(deviceString!=NULL)
	{
		UIDevice*device = [UIDevice currentDevice];
		strcpy(deviceString, [[device model] UTF8String]);
	}
}

void getDeviceName(char*nameString)
{
	if(nameString!=NULL)
	{
		UIDevice*device = [UIDevice currentDevice];
		strcpy(nameString, [[device name] UTF8String]);
	}
}

void iCade_enable(bool toggle, SDL_Window*window)
{
	if(toggle && iCade_receiver==nil)
	{
		iCade_receiver = [[iCadeControllerReceiver alloc] initWithFrame:CGRectMake(0,0,0,0)];
		iCade_receiver.stateChangedCallback = iCade_stateChangedCallback;
		iCade_receiver.buttonDownCallback = iCade_buttonDownCallback;
		iCade_receiver.buttonUpCallback = iCade_buttonUpCallback;
		iCade_receiver.active = YES;
		[getSDLViewController(window).view addSubview:iCade_receiver];
	}
	else if(!toggle && iCade_receiver!=nil)
	{
		[iCade_receiver removeFromSuperview];
		[iCade_receiver release];
		iCade_receiver = nil;
	}
}

bool iCade_enabled()
{
	if(iCade_receiver!=nil)
	{
		return true;
	}
	return false;
}

void iCade_setStateChangedCallback(iCadeEventCallback callback)
{
	iCade_stateChangedCallback = callback;
	if(iCade_receiver!=nil)
	{
		iCade_receiver.stateChangedCallback = callback;
	}
}

void iCade_setButtonDownCallback(iCadeEventCallback callback)
{
	iCade_buttonDownCallback = callback;
	if(iCade_receiver!=nil)
	{
		iCade_receiver.buttonDownCallback = callback;
	}
}

void iCade_setButtonUpCallback(iCadeEventCallback callback)
{
	iCade_buttonUpCallback = callback;
	if(iCade_receiver!=nil)
	{
		iCade_receiver.buttonUpCallback = callback;
	}
}

void SDL_ShowSimpleMessageBoxFixed(const char*title, const char*message)
{
	UIAlertView *alert = [[UIAlertView alloc] initWithTitle:[NSString stringWithUTF8String:title]
													message:[NSString stringWithUTF8String:message]
												   delegate:nil
										  cancelButtonTitle:@"OK"
										  otherButtonTitles:nil];
	[alert show];
	while(alert.visible==YES)
	{
		updateAppEvents();
		SDL_Delay(30);
	}
	[alert release];
}

int SDL_ShowMessageBoxFixed(const char*title, const char*message, const char**options, int numOptions)
{
	int i;
	MessageBoxDelegate*messageDelegate = [[MessageBoxDelegate alloc] init];
	[messageDelegate prepare];
	UIAlertView *alert = [[UIAlertView alloc] initWithTitle:[NSString stringWithUTF8String:title]
													message:[NSString stringWithUTF8String:message]
												   delegate:messageDelegate
										  cancelButtonTitle:nil
										  otherButtonTitles:nil];
	for(i=0; i<numOptions; i++)
	{
		[alert addButtonWithTitle:[NSString stringWithUTF8String:options[i]]];
	}
	[alert show];
	while([messageDelegate isClosed] == NO)
	{
		updateAppEvents();
		SDL_Delay(30);
	}
	int result = [messageDelegate getResult];
	[alert release];
	[messageDelegate release];
	return result;
}

void GameEngine_Log(char*text)
{
	NSLog(@"%@", [NSString stringWithUTF8String:text]);
}

long getUptimeMillis(void)
{
	struct timeval tv;
	gettimeofday(&tv,NULL);
	//return (long)((long)((long)tv.tv_sec*1000) + (long)((long)tv.tv_usec/1000));
	long elapsed = (long)(tv.tv_sec)*1000 + (long)tv.tv_usec/1000;
	return elapsed;
}
