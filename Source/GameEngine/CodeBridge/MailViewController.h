
#ifdef __APPLE__
#import <Foundation/Foundation.h>
#include "TargetConditionals.h"
#if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
#import <UIKit/UIKit.h>
#import <MessageUI/MessageUI.h>

#pragma once

@interface MailViewController : MFMailComposeViewController <MFMailComposeViewControllerDelegate>
{
	BOOL mailOpened;
}

- (void)openMailInViewController:(UIViewController*)viewCtrl person:(NSString*)person subject:(NSString*)subject body:(NSString*)body;
- (BOOL)isOpened;
@end

#endif
#endif

