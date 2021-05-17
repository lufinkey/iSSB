
#pragma once

#if defined(__APPLE__)
#include "TargetConditionals.h"
#endif

#if defined(__APPLE__) && (TARGET_OS_IPHONE == 1 || TARGET_IPHONE_SIMULATOR == 1) && defined(__OBJC__)
#import <Foundation/Foundation.h>
#import "iCade/iCadeReaderView.h"
#endif

#include "iCade/iCadeState.h"

typedef void (*iCadeEventCallback)(iCadeState);

#if defined(__APPLE__) && (TARGET_OS_IPHONE == 1 || TARGET_IPHONE_SIMULATOR == 1) && defined(__OBJC__)
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
#endif
