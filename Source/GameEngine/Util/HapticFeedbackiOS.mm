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

#if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)

#import <AudioToolbox/AudioToolbox.h>
#import <UIKit/UIKit.h>

FOUNDATION_EXTERN void AudioServicesPlaySystemSoundWithVibration(SystemSoundID, objc_object*, NSDictionary*);

namespace GameEngine
{
	API_AVAILABLE(ios(10.0))
	UIImpactFeedbackGenerator* impactLightFeedback = nil;
	API_AVAILABLE(ios(10.0))
	UIImpactFeedbackGenerator* impactMediumFeedback = nil;
	API_AVAILABLE(ios(10.0))
	UIImpactFeedbackGenerator* impactHeavyFeedback = nil;
	
	long long HapticFeedback_lastBuzzIndex = 0;
	SystemSoundID silentSoundID = -1;
	
	int tapticEngineType();
	
	bool HapticFeedback::initialize() {
		NSLog(@"initializing haptic feedback");
		#ifdef TARGET_OS_IPHONE
			if(@available(iOS 10.0, *)) {
				impactLightFeedback = [[UIImpactFeedbackGenerator alloc] initWithStyle:UIImpactFeedbackStyleLight];
				impactMediumFeedback = [[UIImpactFeedbackGenerator alloc] initWithStyle:UIImpactFeedbackStyleMedium];
				impactHeavyFeedback = [[UIImpactFeedbackGenerator alloc] initWithStyle:UIImpactFeedbackStyleHeavy];
			}
			// load silent sound
			NSURL* silentSoundURL = [[NSBundle mainBundle] URLForResource:@"silence_100ms" withExtension:@"caf"];
			auto result = AudioServicesCreateSystemSoundID((__bridge CFURLRef)silentSoundURL, &silentSoundID);
			if(result != 0) {
				NSLog(@"unable to open silence_100ms: error %i", (int)result);
			}
			return true;
		#else
			return false;
		#endif
	}
	
	API_AVAILABLE(ios(10.0))
	void vibrateFeedback(UIImpactFeedbackGenerator* feedback) {
		[feedback prepare];
		[feedback performSelectorOnMainThread:@selector(impactOccurred) withObject:nil waitUntilDone:NO];
	}
	
	int tapticEngineType() {
		NSNumber* tapticAvailable = [[UIDevice currentDevice] valueForKey:@"_feedbackSupportLevel"];
		if(tapticAvailable != nil) {
			return (int)tapticAvailable.integerValue;
		}
		return 0;
	}
	
	void HapticFeedback::buzz(long milliseconds, float strength) {
		#ifdef TARGET_OS_IPHONE
			int tapticType = tapticEngineType();
			if(tapticType == 2) {
				if(@available(iOS 10.0, *)) {
					if(strength >= 0.75) {
						if(impactHeavyFeedback != nil) {
							vibrateFeedback(impactHeavyFeedback);
						}
					}
					else if(strength >= 0.5) {
						if(impactMediumFeedback != nil) {
							vibrateFeedback(impactMediumFeedback);
						}
					}
					else {
						if(impactLightFeedback != nil) {
							vibrateFeedback(impactLightFeedback);
						}
					}
				}
			}
			else {
				AudioServicesPlaySystemSoundWithVibration(kSystemSoundID_Vibrate, nil, @{ @"Intensity": @(strength), @"VibePattern": @[ @YES, @(milliseconds) ] });
			}
		#endif
	}
}

#endif
