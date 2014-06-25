
#include "Music.h"
#include "../Output/Console.h"

namespace GameEngine
{
	Music*Music::musicPlaying = NULL;
	bool Music::lockMusicPlaying = false;
	
	void MusicFinishHandler()
	{
		while(Music::lockMusicPlaying);
		Music::lockMusicPlaying = true;
		if(Music::musicPlaying!=NULL)
		{
			if(Music::musicPlaying->finishing)
			{
				Music::musicPlaying->onFinish();
				Music::musicPlaying->stopped = true;
				Music::musicPlaying->paused = false;
			}
			else
			{
				Music::musicPlaying->stopped = true;
				Music::musicPlaying->paused = false;
				Music::musicPlaying->finishing = true;
			}
		}
		Music::lockMusicPlaying = false;
	}
	
	void Music::init()
	{
		Mix_HookMusicFinished(MusicFinishHandler);
	}
	
	Music::Music()
	{
		loaded = false;
		paused = false;
		stopped = true;
		music = NULL;
	}
	
	Music::~Music()
	{
		if(loaded)
		{
			Mix_FreeMusic(music);
			music = NULL;
			paused = false;
			stopped = true;
			loaded = false;
		}
	}
	
	bool Music::loadFromFile(const String&filePath)
	{
		if(loaded)
		{
			Mix_FreeMusic(music);
			music = NULL;
			paused = false;
			stopped = true;
			finishing = true;
			loaded = false;
		}
		
		music = Mix_LoadMUS(filePath);
		if(music!=NULL)
		{
			paused = false;
			stopped = true;
			loaded = true;
			finishing = true;
			return true;
		}
		Console::WriteLine((String)"Error: " + Mix_GetError());
		return false;
	}
	
	void Music::play()
	{
		if(loaded)
		{
			Music*storeMusicPlaying = musicPlaying;
			if(musicPlaying!=NULL)
			{
				musicPlaying->finishing = false;
				Mix_HaltMusic();
				musicPlaying->stopped = true;
				musicPlaying->paused = false;
				while(!musicPlaying->finishing);
				musicPlaying = NULL;
			}
			
			Mix_PlayMusic(music, 1);
			paused = false;
			stopped = false;
			musicPlaying = this;
			
			if(storeMusicPlaying!=NULL)
			{
				storeMusicPlaying->onStop();
			}
			onPlay();
		}
	}
	
	void Music::loop()
	{
		if(loaded)
		{
			Music*storeMusicPlaying = musicPlaying;
			if(musicPlaying!=NULL)
			{
				musicPlaying->finishing = false;
				Mix_HaltMusic();
				musicPlaying->stopped = true;
				musicPlaying->paused = false;
				while(!musicPlaying->finishing);
				musicPlaying = NULL;
			}
			
			Mix_PlayMusic(music, -1);
			paused = false;
			stopped = false;
			musicPlaying = this;
			
			if(storeMusicPlaying!=NULL)
			{
				storeMusicPlaying->onStop();
			}
			onPlay();
		}
	}
	
	void Music::loop(unsigned int numLoops)
	{
		if(loaded && numLoops!=0)
		{
			Music*storeMusicPlaying = musicPlaying;
			if(musicPlaying!=NULL)
			{
				musicPlaying->finishing = false;
				Mix_HaltMusic();
				musicPlaying->stopped = true;
				musicPlaying->paused = false;
				while(!musicPlaying->finishing);
				musicPlaying = NULL;
			}
			
			Mix_PlayMusic(music, numLoops);
			paused = false;
			stopped = false;
			musicPlaying = this;
			
			if(storeMusicPlaying!=NULL)
			{
				storeMusicPlaying->onStop();
			}
			onPlay();
		}
	}
	
	void Music::stop()
	{
		if(loaded)
		{
			if(!stopped)
			{
				finishing = false;
				Mix_HaltMusic();
				stopped = true;
				paused = false;
				while(!finishing);
				musicPlaying = NULL;
				onStop();
			}
		}
	}
	
	void Music::pause()
	{
		if(loaded)
		{
			if(!paused && !stopped)
			{
				Mix_PauseMusic();
				paused = true;
				stopped = false;
				musicPlaying = this;
				onPause();
			}
		}
	}
	
	void Music::resume()
	{
		if(loaded)
		{
			if(paused)
			{
				Mix_ResumeMusic();
				paused = false;
				stopped = false;
				musicPlaying = this;
				onResume();
			}
		}
	}
	
	bool Music::isLoaded()
	{
		return loaded;
	}
	
	bool Music::isPaused()
	{
		return paused;
	}
	
	bool Music::isStopped()
	{
		return stopped;
	}
	
	void Music::onPlay()
	{
		//Open for implementation
	}
	
	void Music::onPause()
	{
		//Open for implementation
	}
	
	void Music::onResume()
	{
		//Open for implementation
	}
	
	void Music::onStop()
	{
		//Open for implementation
	}
	
	void Music::onFinish()
	{
		//Open for implementation
	}
}