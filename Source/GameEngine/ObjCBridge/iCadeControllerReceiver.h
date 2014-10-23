
#ifdef __OBJC__
#import <Foundation/Foundation.h>
#import "iCade/iCadeReaderView.h"
#endif //__OBJC__
#include "iCade/iCadeState.h"

#pragma once

typedef void (*iCadeEventCallback)(iCadeState);

#ifdef __OBJC__
@interface iCadeControllerReceiver : iCadeReaderView <iCadeEventDelegate>
{
	iCadeEventCallback stateChangedCallback;
	iCadeEventCallback buttonDownCallback;
	iCadeEventCallback buttonUpCallback;
}

@property (nonatomic) iCadeEventCallback stateChangedCallback;
@property (nonatomic) iCadeEventCallback buttonDownCallback;
@property (nonatomic) iCadeEventCallback buttonUpCallback;

@end
#endif //__OBJC__
