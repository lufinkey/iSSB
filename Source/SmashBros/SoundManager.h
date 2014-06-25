
#include "../GameEngine/GameEngine.h"

#pragma once

namespace SmashBros
{
	class SoundManager
	{
	private:
		class SoundDict
		{
			friend class SoundManager;
		private:
			Sound*sound;
			String name;
		public:
			SoundDict();
			SoundDict(const String&name, Sound*sound);
			~SoundDict();
		};
		
		ArrayList<SoundDict*> sounds;
		
	public:
		SoundManager();
		~SoundManager();
		
		bool loadSound(const String&name, const String&filePath);
		void playSound(const String&name);
		Sound*getSound(const String&name);
	};
}