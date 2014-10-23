
#if defined(__APPLE__)
#include "TargetConditionals.h"
#endif

#if (defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)) && defined(__OBJC__)
#import <Foundation/Foundation.h>
#import "iCade/iCadeReaderView.h"
#endif

#include "iCade/iCadeState.h"

#pragma once

typedef void (*iCadeEventCallback)(iCadeState);

#if (defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)) && defined(__OBJC__)
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
