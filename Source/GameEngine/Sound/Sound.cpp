
#include "Sound.h"
#include "SDL_timer.h"
#include "../Output/Console.h"

namespace GameEngine
{
	Sound::SoundInfo*Sound::sounds = NULL;
	int Sound::totalChannels = 0;
	
	void ChannelFinishHandler(int channel)
	{
		Sound::SoundInfo info = Sound::sounds[channel];
		if(info.finishing)
		{
			info.sound->channels[channel] = false;
			info.sound->onFinish(channel);
		}
		else
		{
			info.sound->channels[channel] = false;
			info.finishing = true;
		}
	}
	
	void Sound::init()
	{
		Mix_ChannelFinished(ChannelFinishHandler);
		totalChannels = Mix_AllocateChannels(-1);
		sounds = new SoundInfo[totalChannels];
	}
	
	Sound::Sound()
	{
		sound = NULL;
		loaded = false;
		channels = new bool[totalChannels];
		for(int i=0; i<totalChannels; i++)
		{
			channels[i] = false;
		}
	}
	
	Sound::~Sound()
	{
		if(loaded)
		{
			for(int i=0; i<totalChannels; i++)
			{
				if(channels[i])
				{
					sounds[i].finishing = false;
					Mix_HaltChannel(i);
					while(!sounds[i].finishing);
					channels[i] = false;
				}
			}
			Mix_FreeChunk(sound);
		}
		delete[] channels;
	}
	
	bool Sound::loadFromFile(const String&filePath)
	{
		if(loaded)
		{
			for(int i=0; i<totalChannels; i++)
			{
				if(channels[i])
				{
					sounds[i].finishing = false;
					Mix_HaltChannel(i);
					while(!sounds[i].finishing);
					channels[i] = false;
					onStop(i);
				}
			}
			loaded = false;
			Mix_FreeChunk(sound);
			sound = NULL;
		}
		
		sound = Mix_LoadWAV(filePath);
		
		if(sound!=NULL)
		{
			loaded = true;
			return true;
		}
		loaded = false;
		Console::WriteLine((String)"Error loading sound file " + filePath);
		return false;
	}
	
	int Sound::play()
	{
		if(loaded)
		{
			int channel = Mix_PlayChannel(-1,sound,0);
			if(channel!=-1)
			{
				SoundInfo info;
				info.sound = this;
				info.paused = false;
				info.finishing = true;
				sounds[channel] = info;
				channels[channel] = true;
				return channel;
			}
		}
		return -1;
	}
	
	int Sound::loop()
	{
		if(loaded)
		{
			int channel = Mix_PlayChannel(-1,sound,-1);
			if(channel!=-1)
			{
				SoundInfo info;
				info.sound = this;
				info.paused = false;
				info.finishing = true;
				sounds[channel] = info;
				channels[channel] = true;
				return channel;
			}
		}
		return -1;
	}
	
	int Sound::loop(unsigned int numLoops)
	{
		if(loaded)
		{
			int channel = Mix_PlayChannel(-1,sound,numLoops-1);
			if(channel!=-1)
			{
				SoundInfo info;
				info.sound = this;
				info.paused = false;
				info.finishing = true;
				sounds[channel] = info;
				channels[channel] = true;
				return channel;
			}
		}
		return -1;
	}
	
	void Sound::stop()
	{
		if(loaded)
		{
			for(int i=0; i<totalChannels; i++)
			{
				if(channels[i])
				{
					sounds[i].finishing = false;
					Mix_HaltChannel(i);
					while(!sounds[i].finishing);
					channels[i] = false;
					onStop(i);
				}
			}
		}
	}
	
	void Sound::stop(int channel)
	{
		if(loaded)
		{
			if(channels[channel])
			{
				sounds[channel].finishing = false;
				Mix_HaltChannel(channel);
				while(!sounds[channel].finishing);
				channels[channel] = false;
				onStop(channel);
			}
		}
	}
	
	void Sound::pause()
	{
		if(loaded)
		{
			for(int i=0; i<totalChannels; i++)
			{
				if(channels[i] && !sounds[i].paused)
				{
					sounds[i].paused = true;
					Mix_Pause(i);
					onPause(i);
				}
			}
		}
	}
	
	void Sound::pause(int channel)
	{
		if(loaded)
		{
			if(channels[channel] && !sounds[channel].paused)
			{
				sounds[channel].paused = true;
				Mix_Pause(channel);
				onPause(channel);
			}
		}
	}
	
	void Sound::resume()
	{
		if(loaded)
		{
			for(int i=0; i<totalChannels; i++)
			{
				if(channels[i] && sounds[i].paused)
				{
					sounds[i].paused = false;
					Mix_Resume(i);
					onResume(i);
				}
			}
		}
	}
	
	void Sound::resume(int channel)
	{
		if(loaded)
		{
			if(channels[channel] && sounds[channel].paused)
			{
				sounds[channel].paused = false;
				Mix_Resume(channel);
				onResume(channel);
			}
		}
	}
	
	bool Sound::isLoaded()
	{
		return loaded;
	}
	
	bool Sound::isPaused(int channel)
	{
		if(loaded)
		{
			if(channels[channel] && sounds[channel].paused)
			{
				return true;
			}
		}
		return false;
	}
	
	bool Sound::isStopped(int channel)
	{
		if(loaded)
		{
			if(channels[channel])
			{
				return false;
			}
			return true;
		}
		return false;
	}
	
	void Sound::onPlay(int channel)
	{
		//Open for implementation
	}
	
	void Sound::onPause(int channel)
	{
		//Open for implementation
	}
	
	void Sound::onResume(int channel)
	{
		//Open for implementation
	}
	
	void Sound::onStop(int channel)
	{
		//Open for implementation
	}
	
	void Sound::onFinish(int channel)
	{
		//Open for implementation
	}
}