
#import "iCadeControllerReceiver.h"

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
