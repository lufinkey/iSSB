
#import "iCadeControllerReceiver.h"

#if defined(__APPLE__) && (TARGET_OS_IPHONE == 1 || TARGET_IPHONE_SIMULATOR == 1) && defined(__OBJC__)

@implementation iCadeControllerReceiver

@synthesize stateChangedCallback;
@synthesize buttonDownCallback;
@synthesize buttonUpCallback;

- (id)initWithFrame:(CGRect)frame
{
	self = [super initWithFrame:frame];
	if(self==nil)
	{
		return nil;
	}
	
	self.delegate = self;
	
	return self;
}

- (void)stateChanged:(iCadeState)state
{
	if(stateChangedCallback!=NULL)
	{
		stateChangedCallback(state);
	}
}

- (void)buttonDown:(iCadeState)button
{
	if(buttonDownCallback!=NULL)
	{
		buttonDownCallback(button);
	}
}

- (void)buttonUp:(iCadeState)button
{
	if(buttonUpCallback!=NULL)
	{
		buttonUpCallback(button);
	}
}

@end

#endif
