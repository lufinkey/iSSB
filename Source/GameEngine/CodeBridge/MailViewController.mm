
#ifdef __APPLE__
#import "MailViewController.h"
#include "TargetConditionals.h"
#if (TARGET_OS_IPHONE == 1 || TARGET_IPHONE_SIMULATOR == 1)

@implementation MailViewController

- (id)init
{
	self = [super init];
	if(self==nil)
	{
		return nil;
	}
	
	mailOpened = NO;
	
	return self;
}

- (BOOL)isOpened
{
	return mailOpened;
}

- (void)openMailInViewController:(UIViewController*)viewCtrl person:(NSString*)person subject:(NSString*)subject body:(NSString*)body
{
    if ([MFMailComposeViewController canSendMail] && !mailOpened)
    {
        self.mailComposeDelegate = self;
		[self setSubject:subject];
        NSArray *toRecipients = [[NSArray alloc] initWithObjects:person, nil];
        [self setToRecipients:toRecipients];
        [self setMessageBody:body isHTML:NO];
		[viewCtrl presentViewController:self animated:YES completion:nil];
		mailOpened = YES;
    }
    else
    {
		NSLog(@"Error: your device doesn't support the composer sheet");
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Failure"
                                                        message:@"Your device doesn't support the composer sheet"
                                                       delegate:nil
                                              cancelButtonTitle:@"OK"
                                              otherButtonTitles:nil];
        [alert show];
    }
}

- (void)mailComposeController:(MFMailComposeViewController*)controller didFinishWithResult:(MFMailComposeResult)result error:(NSError*)error
{
    switch (result)
    {
        case MFMailComposeResultCancelled:
		NSLog(@"Mail cancelled: you cancelled the operation and no email message was queued.");
        break;
		
        case MFMailComposeResultSaved:
		NSLog(@"Mail saved: you saved the email message in the drafts folder.");
        break;
		
        case MFMailComposeResultSent:
        NSLog(@"Mail send: the email message is queued in the outbox. It is ready to send.");
		break;
		
        case MFMailComposeResultFailed:
		NSLog(@"Mail failed: the email message was not saved or queued, possibly due to an error.");
		break;
		
        default:
		NSLog(@"Mail not sent.");
		break;
    }
	// Remove the mail view
	[self dismissViewControllerAnimated:YES completion:nil];
	mailOpened = false;
}

@end

#endif
#endif
