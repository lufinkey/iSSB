
#import "MessageBoxDelegate.h"


@implementation MessageBoxDelegate

- (void)prepare
{
	result = 0;
	closed = NO;
}

- (void)alertView:(UIAlertView *)alertView didDismissWithButtonIndex:(NSInteger)buttonIndex
{
	result = buttonIndex;
	closed = YES;
}

- (BOOL)isClosed
{
	return closed;
}

- (int)getResult
{
	return result;
}

@end
