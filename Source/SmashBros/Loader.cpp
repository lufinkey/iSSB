
#include "Loader.h"

#include "Game/Characters/Mario.h"
#include "Game/Characters/Sonic.h"
#include "Game/Characters/Ichigo.h"
#include "Game/Characters/Fox.h"
#include "Game/Characters/Pikachu.h"

#include "Game/Stages/FractalStage.h"
#include "Game/Stages/HillsideBattleground.h"
#include "Game/Stages/BattlefieldBrawl.h"
#include "Game/Stages/FinalDestinationBrawl.h"
#include "Game/Stages/HyruleTemple.h"

namespace SmashBros
{
	String CharacterLoader::getMenuFilename(int charNo)
	{
		switch(charNo)
		{
			default:
			return "random.png";
			
			case Global::CHAR_MARIO:
			return "mario.png";
			
			case Global::CHAR_ICHIGO:
			return "ichigo.png";
			
			case Global::CHAR_SONIC:
			return "sonic.png";
			
			case Global::CHAR_FOX:
			return "fox.png";
			
			case Global::CHAR_PIKACHU:
			return "pikachu.png";
		}
	}
	
	String CharacterLoader::getFolder(int charNo)
	{
		return (String)"Images/Game/Characters/" + getName(charNo);
	}
	
	String CharacterLoader::getName(int charNo)
	{
		switch(charNo)
		{
			default:
			return "";
			
			case Global::CHAR_MARIO:
			return "Mario";
			
			case Global::CHAR_ICHIGO:
			return "Ichigo";
			
			case Global::CHAR_SONIC:
			return "Sonic";
			
			case Global::CHAR_FOX:
			return "Fox";
			
			case Global::CHAR_PIKACHU:
			return "Pikachu";
		}
	}
	
	String CharacterLoader::getIconPath(int charNo)
	{
		return (String)"Images/Menus/CharacterSelect/icons/" + getMenuFilename(charNo);
	}
	
	String CharacterLoader::getPreviewPath(int charNo)
	{
		return (String)"Images/Menus/CharacterSelect/previews/" + getMenuFilename(charNo);
	}
	
	Player* CharacterLoader::createPlayer(float x1, float y1, byte playerNo, byte team,int charNum)
	{
		Player*p = null;
		Console::WriteLine((String)"creating character " + charNum);
		switch(charNum)
		{
			case Global::CHAR_MARIO:
			p = new Mario(x1,y1,playerNo,team);
			p->charNo = Global::CHAR_MARIO;
			break;
			
			case Global::CHAR_ICHIGO:
			p = new Ichigo(x1,y1,playerNo,team);
			p->charNo = Global::CHAR_ICHIGO;
			break;
			
			case Global::CHAR_SONIC:
			p = new Sonic(x1,y1,playerNo,team);
			p->charNo = Global::CHAR_SONIC;
			break;
			
			case Global::CHAR_FOX:
			p = new Fox(x1,y1,playerNo,team);
			p->charNo = Global::CHAR_FOX;
			break;
			
			case Global::CHAR_PIKACHU:
			p = new Pikachu(x1,y1,playerNo,team);
			p->charNo = Global::CHAR_PIKACHU;
			break;
		}
		return p;
	}
	
	ArrayList<Animation*> CharacterLoader::getWinnersScreenAnimations(int charNo)
	{
		int win_fps = 1;
		int win_rows = 1;
		int win_cols = 1;
		
		int winhold_fps = 1;
		int winhold_rows = 1;
		int winhold_cols = 1;
		
		int lose_fps = 4;
		int lose_rows = 2;
		int lose_cols = 1;
		
		switch(charNo)
		{
			case Global::CHAR_MARIO:
			win_fps = 8;
			win_rows = 8;
			break;
			
			case Global::CHAR_ICHIGO:
			win_fps = 6;
			win_rows = 5;
			break;
			
			case Global::CHAR_SONIC:
			win_fps = 5;
			win_rows = 6;
			break;
			
			case Global::CHAR_FOX:
			win_fps = 8;
			win_rows = 6;
			break;
			
			case Global::CHAR_PIKACHU:
			win_fps = 6;
			winhold_fps = 6;
			winhold_rows = 10;
			break;
		}
		
		String charFolder = getFolder(charNo);
		
		ArrayList<Animation*> animations;
		
		Animation* win = new Animation("win", win_fps, win_rows, win_cols);
		win->addFrame(charFolder + "/win.png");
		animations.add(win);
		
		Animation* winhold = new Animation("win_hold", winhold_fps, winhold_rows, winhold_cols);
		winhold->addFrame(charFolder + "/win_hold.png");
		animations.add(winhold);
		
		Animation* lose = new Animation("lose", lose_fps, lose_rows, lose_cols);
		lose->addFrame(charFolder + "/lose.png");
		animations.add(lose);
		
		return animations;
	}
	
	
	
	//StageLoader
	
	
	
	String StageLoader::getMenuFilename(int stageNo)
	{
		switch(stageNo)
		{
			default:
			case Global::STAGE_FRACTALSTAGE:
			return "test.png";
			
			case Global::STAGE_HILLSIDEBATTLEGROUND:
			return "hillside_battleground.png";
			
			case Global::STAGE_BATTLEFIELDBRAWL:
			return "battlefield.png";
			
			case Global::STAGE_FINALDESTINATION:
			return "final_destination.png";
			
			case Global::STAGE_HYRULETEMPLE:
			return "hyruletemple.png";
		}
	}
	
	String StageLoader::getIconPath(int stageNo)
	{
		return (String)"Images/Menus/StageSelect/" + getMenuFilename(stageNo);
	}
	
	Stage* StageLoader::createStage(int x1, int y1, int stageNum)
	{
		switch(stageNum)
		{
			case Global::STAGE_FRACTALSTAGE:
			return new FractalStage(x1,y1);
			
			case Global::STAGE_HILLSIDEBATTLEGROUND:
			return new HillsideBattleground(x1,y1);
			
			case Global::STAGE_HYRULETEMPLE:
			return new HyruleTemple(x1,y1);
			
			case Global::STAGE_BATTLEFIELDBRAWL:
			return new BattlefieldBrawl(x1,y1);
			
			case Global::STAGE_FINALDESTINATION:
			return new FinalDestinationBrawl(x1,y1);
		}
		return null;
	}
}
