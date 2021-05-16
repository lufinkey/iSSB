//
//  HapticFeedbackiOS.m
//  iSSB
//
//  Created by Luis Finke on 9/6/18.
//  Copyright © 2018 Luis Finke. All rights reserved.
//

#include "HapticFeedback.h"
#include <thread>

#if defined(__APPLE__)
#import "TargetConditionals.h"
#endif

#if defined(__APPLE__) && (TARGET_OS_IPHONE == 1 || TARGET_IPHONE_SIMULATOR == 1)

#import <AudioToolbox/AudioToolbox.h>
#import <UIKit/UIKit.h>

FOUNDATION_EXTERN void AudioServicesPlaySystemSoundWithVibration(SystemSoundID, objc_object*, NSDictionary*);

namespace GameEngine
{
	bool HapticFeedback::initialize() {
		#ifdef TARGET_OS_IPHONE
			return true;
		#else
			return false;
		#endif
	}
	
	void HapticFeedback::buzz(long milliseconds, float strength) {
		#ifdef TARGET_OS_IPHONE
			AudioServicesPlaySystemSoundWithVibration(kSystemSoundID_Vibrate, nil, @{ @"Intensity": @(strength), @"VibePattern": @[ @YES, @(milliseconds) ] });
		#endif
	}
}

#endif
