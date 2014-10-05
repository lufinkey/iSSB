
#include "SDL_mixer.h"
#include "../Util/String.h"

#pragma once

namespace GameEngine
{
	class Music
	{
		friend class Application;
		friend void MusicFinishHandler();
	private:
		static Music*musicPlaying;
		static bool lockMusicPlaying;
		static void init();
		
		bool loaded, paused, stopped, finishing;
		Mix_Music*music;
		
	public:
		Music();
		virtual ~Music();
		
		bool loadFromFile(const String&filePath);
		
		void play();
		void loop();
		void loop(unsigned int numLoops);
		void stop();
		void pause();
		void resume();
		
		bool isLoaded();
		bool isPaused();
		bool isStopped();
		
		virtual void onPlay();
		virtual void onPause();
		virtual void onResume();
		virtual void onStop();
		virtual void onFinish();
	};
}