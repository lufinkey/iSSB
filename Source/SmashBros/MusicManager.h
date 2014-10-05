
#include "../GameEngine/GameEngine.h"

#pragma once

namespace SmashBros
{
	class MusicManager
	{
	private:
		typedef struct
		{
			String name;
			String filePath;
		} MusicDict;
		
		static Music*music;
		static String currentSong;
		static ArrayList<MusicDict> songs;
		
	public:
		static void addSong(const String&name, const String&filePath);
		static String getFilePath(const String&name);
		
		static bool loadSong(const String&name);
		static void play();
		static void stop();
	};
}