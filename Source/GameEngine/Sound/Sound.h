
#include "SDL_mixer.h"
#include "../Util/ArrayList.h"
#include "../Util/String.h"

#pragma once

namespace GameEngine
{
	class Sound
	{
		friend void ChannelFinishHandler(int);
		friend class Application;
	private:
		typedef struct
		{
			Sound*sound;
			bool paused;
			bool finishing;
		} SoundInfo;
		
		static int totalChannels;
		static SoundInfo*sounds;
		
		static void init();
		
		Mix_Chunk*sound;
		bool*channels;
		bool loaded;
		
	public:
		Sound();
		virtual ~Sound();
		
		bool loadFromFile(const String&filePath);
		
		int play();
		int loop();
		int loop(unsigned int numLoops);
		void stop();
		void stop(int channel);
		void pause();
		void pause(int channel);
		void resume();
		void resume(int channel);
		
		bool isLoaded();
		bool isPaused(int channel);
		bool isStopped(int channel);
		
		virtual void onPlay(int channel);
		virtual void onPause(int channel);
		virtual void onResume(int channel);
		virtual void onStop(int channel);
		virtual void onFinish(int channel);
	};
}