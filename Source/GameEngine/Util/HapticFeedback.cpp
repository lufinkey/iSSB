//
//  HapticFeedback.cpp
//  iSSB
//
//  Created by Luis Finke on 9/6/18.
//  Copyright © 2018 Luis Finke. All rights reserved.
//

#include "HapticFeedback.h"
#include "../Output/Console.h"
#include <SDL.h>
#if defined(__APPLE__)
#include "TargetConditionals.h"
#endif

namespace GameEngine
{
#if (!defined(TARGET_OS_IPHONE) || TARGET_OS_IPHONE != 1) && (!defined(TARGET_IPHONE_SIMULATOR) || TARGET_IPHONE_SIMULATOR != 1)

	SDL_Haptic* sdlHaptic = nullptr;
	bool sdlRumbleInitialized = false;
	
	bool HapticFeedback::initialize() {
		if(sdlHaptic == nullptr) {
			// initialize
			sdlHaptic = SDL_HapticOpen(0);
			if(sdlHaptic != nullptr) {
				Console::WriteLine("opened haptic feedback");
				if(SDL_HapticRumbleInit(sdlHaptic) == 0) {
					Console::WriteLine("opened haptic rumble");
					sdlRumbleInitialized = true;
				}
				else {
					Console::WriteLine((String)"could not open haptic rumble: "+SDL_GetError());
				}
			}
			else {
				Console::WriteLine((String)"could not open haptic feedback: "+SDL_GetError());
			}
		}
		// determine if initialized
		if(sdlHaptic != nullptr && sdlRumbleInitialized) {
			return true;
		}
		return false;
	}
	
	void HapticFeedback::buzz(long milliseconds, float strength) {
		if(sdlHaptic != nullptr) {
			Console::WriteLine("calling SDL_HapticRumblePlay");
			int result = SDL_HapticRumblePlay(sdlHaptic, (float)strength, (Uint32)milliseconds);
			if(result != 0) {
				Console::WriteLine((String)"Error playing haptic feedback: "+SDL_GetError());
			}
		}
	}
	
#endif
}
