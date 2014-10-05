
#include "Global.h"

#pragma once

namespace SmashBros
{
	class CharacterLoader
	{
	private:
		static String getMenuFilename(int charNo);
		
	public:
		static String getFolder(int charNo);
		static String getName(int charNo);
		
		static String getIconPath(int charNo);
		static String getPreviewPath(int charNo);
		
		static Player* createPlayer(float x1, float y1, byte playerNo, byte team,int charNum);
		
		static ArrayList<Animation*> getWinnersScreenAnimations(int charNo);
	};
	
	class StageLoader
	{
	private:
		static String getMenuFilename(int stageNo);
		
	public:
		static String getIconPath(int stageNo);
		
		static Stage* createStage(int x1, int y1, int stageNum);
	};
}
