
#import "MailViewController.h"

static bool mailOpened = false;
static UIViewController*currentView = nil;

@implementation MailViewController

- (bool)isOpened
{
	return mailOpened;
}

- (IBAction)openMail:(id)sender viewCtrl:(UIViewController*)viewCtrl person:(NSString*)person subject:(NSString*)subject body:(NSString*)body
{
    if ([MFMailComposeViewController canSendMail] && !mailOpened)
    {
		MFMailComposeViewController *mailer = [[MFMailComposeViewController alloc] init];
        mailer.mailComposeDelegate = self;
		[mailer setSubject:subject];
        NSArray *toRecipients = [NSArray arrayWithObjects:person, nil];
        [mailer setToRecipients:toRecipients];
        [mailer setMessageBody:body isHTML:NO];
        [viewCtrl presentModalViewController:mailer animated:YES];
        [mailer release];
		currentView = viewCtrl;
		mailOpened = true;
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
        [alert release];
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
	[currentView dismissModalViewControllerAnimated:YES];
	mailOpened = false;
}

@end