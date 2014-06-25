
#import <UIKit/UIKit.h>
#import <MessageUI/MessageUI.h>

#pragma once

@interface MailViewController : UIViewController <MFMailComposeViewControllerDelegate>
- (IBAction)openMail:(id)sender viewCtrl:(UIViewController*)viewCtrl person:(NSString*)person subject:(NSString*)subject body:(NSString*)body;
- (bool)isOpened;
@end