
#import <Foundation/Foundation.h>
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