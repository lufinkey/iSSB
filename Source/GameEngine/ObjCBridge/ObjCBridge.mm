
#include "ObjCBridge.h"
#include "SDL.h"
#include "SDL_syswm.h"
#include "CPPBridge.h"
#include <math.h>
#include <sys/time.h>

#if defined(__APPLE__)
	#include "TargetConditionals.h"
	#if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
		#import <UIKit/UIKit.h>
		#import "MailViewController.h"
		#import "UIWebViewController.h"
		#import "MessageBoxDelegate.h"
		
		//static NSDate*startDate = nil;
		static iCadeControllerReceiver* iCade_receiver = nil;
	#endif
#elif defined(__ANDROID__)
	#include <iostream>
	#include <android/log.h>
	#include "../Util/String.h"
	#include "../Application.h"
#endif

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

#ifdef __APPLE__
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
#endif

#if defined(__ANDROID__)
void GameEngine_charToUrlEncoding(char *s, char *enc, char *tb)
{
	for (; *s; s++)
	{
		if (tb[*s])
		{
			sprintf(enc, "%c", tb[*s]);
		}
		else
		{
			sprintf(enc, "%%%02X", *s);
		}
		while (*++enc);
	}
}

GameEngine::String GameEngine_urlencode(char*str)
{
	int length = strlen(str)+1;
	char* enc = new char[length * 3];
	
	char rfc3986[256] = {0};
	char html5[256] = {0};
	
	int i;
	for (i = 0; i < 256; i++)
	{
		rfc3986[i] = isalnum(i)||i == '~'||i == '-'||i == '.'||i == '_'
		? i : 0;
		html5[i] = isalnum(i)||i == '*'||i == '-'||i == '.'||i == '_'
		? i : (i == ' ') ? '+' : 0;
	}
	
	charToUrlEncoding(str, enc, rfc3986);
	GameEngine::String result = enc;
	delete enc;
	
	return result;
}
#endif

void openURL(const char*url, SDL_Window*window)
{
#if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
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
	
#elif defined(__ANDROID__)
	GameEngine::String command = (GameEngine::String)"./adb shell am start -a android.intent.action.VIEW -d " + url;
	system(command);
#endif
}

void writeEmail(SDL_Window*window, const char*recipient, const char*subject, const char*body)
{
#if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
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
	
#elif defined(__ANDROID__)
	GameEngine::String subj = subject;
	GameEngine::String bod = body;
	
	GameEngine::String url = (GameEngine::String)"mailto:" + recipient + "?subject=" + urlencode(subj) + "&body=" + urlencode(bod);
	GameEngine::String command = (GameEngine::String)"./adb shell am start -a android.intent.action.VIEW -d " + url;
	system(command);
#endif
}

void getDeviceModel(char*deviceString)
{
#if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
	if(deviceString!=NULL)
	{
		UIDevice*device = [UIDevice currentDevice];
		strcpy(deviceString, [[device model] UTF8String]);
	}
	
#else
	//TODO add getDeviceModel for android
	if(deviceString!=NULL)
	{
		strcpy(deviceString, "Unknown");
	}
#endif
}

void getDeviceName(char*nameString)
{
#if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
	if(nameString!=NULL)
	{
		UIDevice*device = [UIDevice currentDevice];
		strcpy(nameString, [[device name] UTF8String]);
	}
	
#else
	if(nameString!=NULL)
	{
		strcpy(nameString, "Unknown");
	}
#endif
}



void iCade_enable(bool toggle, SDL_Window*window)
{
#if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
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
#endif
}

bool iCade_enabled()
{
#if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
	if(iCade_receiver!=nil)
	{
		return true;
	}
#endif
	return false;
}

void iCade_setStateChangedCallback(iCadeEventCallback callback)
{
	iCade_stateChangedCallback = callback;
#if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
	if(iCade_receiver!=nil)
	{
		iCade_receiver.stateChangedCallback = callback;
	}
#endif
}

void iCade_setButtonDownCallback(iCadeEventCallback callback)
{
	iCade_buttonDownCallback = callback;
#if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
	if(iCade_receiver!=nil)
	{
		iCade_receiver.buttonDownCallback = callback;
	}
#endif
}

void iCade_setButtonUpCallback(iCadeEventCallback callback)
{
	iCade_buttonUpCallback = callback;
#if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
	if(iCade_receiver!=nil)
	{
		iCade_receiver.buttonUpCallback = callback;
	}
#endif
}



void SDL_ShowSimpleMessageBoxFixed(const char*title, const char*message)
{
#if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
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
	
#else
	SDL_Window* window = GameEngine::Application::getWindow();
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, title, message, window);
#endif
}

int SDL_ShowMessageBoxFixed(const char*title, const char*message, const char**options, int numOptions)
{
#if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
	MessageBoxDelegate*messageDelegate = [[MessageBoxDelegate alloc] init];
	[messageDelegate prepare];
	UIAlertView *alert = [[UIAlertView alloc] initWithTitle:[NSString stringWithUTF8String:title]
													message:[NSString stringWithUTF8String:message]
												   delegate:messageDelegate
										  cancelButtonTitle:nil
										  otherButtonTitles:nil];
	for(int i=0; i<numOptions; i++)
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
	
#else
	SDL_Window* window = GameEngine::Application::getWindow();
	SDL_MessageBoxButtonData*buttons = new SDL_MessageBoxButtonData[numOptions];
	for(int i=0; i<numOptions; i++)
	{
		SDL_MessageBoxButtonData button = {0, i, (char*)options[i]};
		buttons[i] = button;
	}
	SDL_MessageBoxData messageBoxData = {SDL_MESSAGEBOX_INFORMATION, window, (const char*)title, (const char*)message, numOptions, buttons, NULL};
	int buttonid = 0;
	SDL_ShowMessageBox(&messageBoxData, &buttonid);
	delete[] buttons;
	return buttonid;
#endif
}

void GameEngine_Log(char*text)
{
#if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
	NSLog(@"%@", [NSString stringWithUTF8String:text]);
	
#elif defined(__ANDROID__)
	__android_log_print(ANDROID_LOG_INFO, "SDL", "%s", text);
#endif
}

long getUptimeMillis(void)
{
	struct timeval tv;
	gettimeofday(&tv,NULL);
	//return (long)((long)((long)tv.tv_sec*1000) + (long)((long)tv.tv_usec/1000));
	long elapsed = (long)(tv.tv_sec)*1000 + (long)tv.tv_usec/1000;
	return elapsed;
}
