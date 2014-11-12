
#import <UIKit/UIKit.h>

@interface MessageBoxDelegate : UIViewController <UIAlertViewDelegate>
{
@public
	BOOL closed;
	int result;
}

- (void)prepare;
- (BOOL)isClosed;
- (int)getResult;

@end
