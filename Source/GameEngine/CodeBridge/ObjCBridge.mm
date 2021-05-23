
#define _CRT_SECURE_NO_WARNINGS

#include "CPPBridge.h"
#include "SDL.h"
#include "SDL_syswm.h"
#include <string.h>
#include <math.h>
#include <iostream>

#ifdef __APPLE__

#include "TargetConditionals.h"
#if (TARGET_OS_IPHONE == 1 || TARGET_IPHONE_SIMULATOR == 1)
	#import <UIKit/UIKit.h>
	#import "MailViewController.h"
	#import "WebViewController.h"

	//static NSDate*startDate = nil;
	static iCadeControllerReceiver* iCade_receiver = nil;
#endif
#include "../Application.h"

static iCadeEventCallback iCade_stateChangedCallback = NULL;
static iCadeEventCallback iCade_buttonDownCallback = NULL;
static iCadeEventCallback iCade_buttonUpCallback = NULL;

void GameEngine_Log(const char* text)
{
	NSLog(@"%@", [NSString stringWithUTF8String:text]);
}


#if (TARGET_OS_IPHONE == 1 || TARGET_IPHONE_SIMULATOR == 1)
UIViewController* getSDLViewController(SDL_Window*window)
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

UIViewController* GameEngine_getTopViewController(UIViewController* controller)
{
	if(controller == nil)
	{
		return nil;
	}
	else if(controller.presentedViewController != nil)
	{
		return GameEngine_getTopViewController(controller.presentedViewController);
	}
	else if(controller.navigationController != nil)
	{
		return GameEngine_getTopViewController(controller.navigationController);
	}
	else if(controller.parentViewController != nil)
	{
		return GameEngine_getTopViewController(controller.parentViewController);
	}
	return controller;
}


void openURL(const char*url, SDL_Window*window)
{
	if(window==NULL)
	{
		[[UIApplication sharedApplication] openURL:[NSURL URLWithString:[NSString stringWithUTF8String:url]]];
	}
	else
	{
		WebViewController* webview = [[WebViewController alloc] init];
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
}

std::string getDeviceModel()
{
	UIDevice* device = [UIDevice currentDevice];
	return [[device model] UTF8String];
}

std::string getDeviceName()
{
	UIDevice*device = [UIDevice currentDevice];
	return [[device name] UTF8String];
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
		iCade_receiver = nil;
	}
}

bool iCade_enabled()
{
	if(iCade_receiver != nil)
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
	UIAlertController* alert = [UIAlertController alertControllerWithTitle:[NSString stringWithUTF8String:title]
																   message:[NSString stringWithUTF8String:message]
															preferredStyle:UIAlertControllerStyleAlert];
	
	[alert addAction:[UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleDefault handler:^(UIAlertAction* action) {
		//
	}]];
	
	SDL_Window* window = GameEngine::Application::getWindow();
	UIViewController* rootVC = getSDLViewController(window);
	UIViewController* topVC = GameEngine_getTopViewController(rootVC);
	[topVC presentViewController:alert animated:YES completion:nil];
	
	while(alert.isBeingPresented || alert.isBeingDismissed || alert.presentingViewController != nil)
	{
		updateAppEvents();
		SDL_Delay(30);
	}
}

int SDL_ShowMessageBoxFixed(const char*title, const char*message, const char**options, int numOptions)
{
	UIAlertController* alert = [UIAlertController alertControllerWithTitle:[NSString stringWithUTF8String:title]
																   message:[NSString stringWithUTF8String:message]
															preferredStyle:UIAlertControllerStyleAlert];
	
	__block int result = -1;
	for(int i=0; i<numOptions; i++)
	{
		[alert addAction:[UIAlertAction actionWithTitle:[NSString stringWithUTF8String:options[i]] style:UIAlertActionStyleDefault handler:^(UIAlertAction* action) {
			result = i;
		}]];
	}
	
	SDL_Window* window = GameEngine::Application::getWindow();
	UIViewController* rootVC = getSDLViewController(window);
	UIViewController* topVC = GameEngine_getTopViewController(rootVC);
	[topVC presentViewController:alert animated:YES completion:nil];
	
	while(alert.isBeingPresented || alert.isBeingDismissed || alert.presentingViewController != nil)
	{
		updateAppEvents();
		SDL_Delay(30);
	}
	
	return result;
}
#endif

#endif
