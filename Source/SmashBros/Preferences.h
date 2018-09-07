
#include "../GameEngine/GameEngine.h"

#pragma once

namespace SmashBros
{
	class Preferences
	{
	private:
		static bool menuMusic;
		static bool menuSoundFx;
		static bool ingameMusic;

		static bool highfps;
		static bool hapticFeedback;
		
		static PrefManager prefMgr;

	public:
		static const String version;
		
		static bool newVersion;
		static String versionMessage;
		
		static bool debuglog;
		
		static void init();
		
		static void load();
		static void save();
		
		static void toggleMenuMusic(bool toggle);
		static void toggleMenuSoundFX(bool toggle);
		static void toggleInGameMusic(bool toggle);
		static void setHighFPS(bool toggle);
		static void setHapticFeedback(bool hapticEnabled);
		static bool hasHapticFeedback();
		static bool menuMusicOn();
		static bool menuSoundFXOn();
		static bool ingameMusicOn();
		static bool highFPS();
	};
}

