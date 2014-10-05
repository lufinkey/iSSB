
#include "SoundManager.h"

namespace SmashBros
{
	SoundManager::SoundDict::SoundDict()
	{
		name = "";
		sound = NULL;
	}
	
	SoundManager::SoundDict::SoundDict(const String&name, Sound*sound)
	{
		this->name = name;
		this->sound = sound;
	}
	
	SoundManager::SoundDict::~SoundDict()
	{
		if(sound!=NULL)
		{
			delete sound;
		}
	}
	
	SoundManager::SoundManager()
	{
		sounds = ArrayList<SoundDict*>();
	}
	
	SoundManager::~SoundManager()
	{
		for(int i=0; i<sounds.size(); i++)
		{
			delete sounds.get(i);
		}
		sounds.clear();
	}
	
	bool SoundManager::loadSound(const String&name, const String&filePath)
	{
		for(int i=0; i<sounds.size(); i++)
		{
			if(sounds.get(i)->name.equals(name))
			{
				return true;
			}
		}
		
		Sound*sound = new Sound();
		if(sound->loadFromFile(filePath))
		{
			sounds.add(new SoundDict(name,sound));
			return true;
		}
		delete sound;
		return false;
	}
	
	void SoundManager::playSound(const String&name)
	{
		for(int i=0; i<sounds.size(); i++)
		{
			SoundDict*dict = sounds.get(i);
			if(dict->name.equals(name))
			{
				dict->sound->play();
				return;
			}
		}
	}
	
	Sound*SoundManager::getSound(const String&name)
	{
		for(int i=0; i<sounds.size(); i++)
		{
			SoundDict*dict = sounds.get(i);
			if(dict->name.equals(name))
			{
				return dict->sound;
			}
		}
		return NULL;
	}
}