
#include "MusicManager.h"
#include "Preferences.h"
#include "../GameEngine/Output/Console.h"

namespace SmashBros
{
	Music*MusicManager::music = NULL;
	String MusicManager::currentSong = "";
	ArrayList<MusicManager::MusicDict> MusicManager::songs = ArrayList<MusicManager::MusicDict>();
	
	void MusicManager::addSong(const String&name, const String&filePath)
	{
		for(int i=0; i<songs.size(); i++)
		{
			MusicDict&dict = songs.get(i);
			if(dict.name.equals(name))
			{
				dict.filePath = filePath;
				songs.set(i,dict);
				return;
			}
		}
		MusicDict dict;
		dict.name = name;
		dict.filePath = filePath;
		songs.add(dict);
	}
	
	String MusicManager::getFilePath(const String&name)
	{
		for(int i=0; i<songs.size(); i++)
		{
			MusicDict&song = songs.get(i);
			if(song.name.equals(name))
			{
				return song.filePath;
			}
		}
		return "";
	}
	
	bool MusicManager::loadSong(const String&name)
	{
		if(music==NULL)
		{
			music = new Music();
		}
		
		if(!currentSong.equals(name))
		{
			if(!music->isStopped())
			{
				music->stop();
			}
			
			String path = getFilePath(name);
			
			if(path.equals(""))
			{
				return false;
			}
			
			Console::WriteLine((String)"Loading song " + path);
			
			bool success = music->loadFromFile(path);
			
			if(success)
			{
				currentSong = name;
				return true;
			}
			Console::WriteLine((String)"Error loading song " + name + " from path " + path);
			return false;
		}
		return true;
	}
	
	void MusicManager::play()
	{
		if(music!=NULL && music->isLoaded())
		{
			Console::WriteLine((String)"Playing song " + currentSong);
			music->loop();
		}
	}
	
	void MusicManager::stop()
	{
		if(music!=NULL && music->isLoaded() && !music->isStopped())
		{
			Console::WriteLine((String)"Stopping song " + currentSong);
			music->stop();
		}
	}
}