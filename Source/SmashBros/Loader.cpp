
#include "Loader.h"

#include "Game/Characters/Mario.h"
#include "Game/Characters/Sonic.h"
#include "Game/Characters/Ichigo.h"
#include "Game/Characters/Fox.h"
#include "Game/Characters/Pikachu.h"
#include "Game/Characters/Link.h"

#include "Game/Stages/FractalStage.h"
#include "Game/Stages/HillsideBattleground.h"
#include "Game/Stages/BattlefieldBrawl.h"
#include "Game/Stages/FinalDestinationBrawl.h"
#include "Game/Stages/HyruleTemple.h"
#include "Game/Stages/Corneria.h"
#include "Game/Stages/WhompFortress.h"

#ifndef SMASHBROS_SCRIPT_DISABLE
#include "../ScriptModule/ScriptManager.h"
#include "../ScriptModule/modules/SmashBros/inherit/lib_sb_inherit_Stage.h"
#endif //SMASHBROS_SCRIPT_DISABLE

namespace SmashBros
{
	String CharacterLoader::getMenuFilename(int charNo)
	{
		switch(charNo)
		{
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
			
			case Global::CHAR_LINK:
			return "link.png";
			
			default:
			if(charNo <= Global::totalCharacters)
			{
				return "random.png";
			}
			else
			{
				//TODO implement getting of Scripted Players here.
				return "random.png";
			}
			break;
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
			
			case Global::CHAR_LINK:
			return "Link";
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
			
			case Global::CHAR_LINK:
			p = new Link(x1,y1,playerNo,team);
			p->charNo = Global::CHAR_LINK;
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
			lose_fps = 8;
			lose_rows = 4;
			break;
			
			case Global::CHAR_SONIC:
			win_fps = 5;
			win_rows = 6;
			lose_fps = 8;
			lose_rows = 4;
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
			
			case Global::CHAR_LINK:
			win_fps = 8;
			win_rows = 4;
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
	
	
	
#ifndef SMASHBROS_SCRIPT_DISABLE
	ArrayList<ScriptModule::ScriptEntityInfo*> StageLoader::scriptEntities = ArrayList<ScriptModule::ScriptEntityInfo*>();
	ArrayList<int> StageLoader::disabledScriptEntities = ArrayList<int>();
	
	void StageLoader::loadScriptEntities(const String& path)
	{
		ArrayList<String> folders = FileTools::getFoldersInDirectory(path);
		for(int i=0; i<folders.size(); i++)
		{
			String folderName = folders.get(i);
			if(FileTools::fileExists(path + '/' + folderName + "/Info.plist"))
			{
				ScriptModule::ScriptEntityInfo* info = new ScriptModule::ScriptEntityInfo();
				String errorMessage;
				bool success = info->loadFromFile(path + '/' + folderName, errorMessage);
				if(success)
				{
					bool success = ScriptModule::ScriptManager::loadScriptEntity(*info, errorMessage);
					if(success)
					{
						AssetManager::loadImage(info->getPath() + '/' + info->getIcon());
						scriptEntities.add(info);
					}
					else
					{
						Game::showMessage("Error", (String)"Unable to load ScriptModule \"" + folderName + "\": " + errorMessage);
						delete info;
					}
				}
				else
				{
					Game::showMessage("Error", (String)"Unable to load ScriptModule \"" + folderName + "\": " + errorMessage);
					delete info;
				}
			}
		}
		
		for(int i=0; i<scriptEntities.size(); i++)
		{
			for(int j=1; j<(scriptEntities.size()-i); j++)
			{
				ScriptModule::ScriptEntityInfo* info1 = scriptEntities.get(j-1);
				ScriptModule::ScriptEntityInfo* info2 = scriptEntities.get(j);
				if(info1->getMainScript().name.compare(info2->getMainScript().name) == 1)
				{
					scriptEntities.set(j-1, info2);
					scriptEntities.set(j, info1);
				}
				else if(info1->getCreator().compare(info2->getCreator()) == 1)
				{
					scriptEntities.set(j-1, info2);
					scriptEntities.set(j, info1);
				}
				else if(info1->getVersion().compare(info2->getVersion()) == 1)
				{
					scriptEntities.set(j-1, info2);
					scriptEntities.set(j, info1);
				}
			}
		}
	}
	
	void StageLoader::unloadScriptEntities()
	{
		for(int i=0; i<scriptEntities.size(); i++)
		{
			ScriptModule::ScriptEntityInfo* info = scriptEntities.get(i);
			ScriptModule::ScriptManager::unloadScriptEntity(*info);
			AssetManager::unloadImage(info->getPath() + '/' + info->getIcon());
			delete info;
		}
		scriptEntities.clear();
	}
	
	void StageLoader::setDisabledScriptEntities(const ArrayList<int>& disabled)
	{
		disabledScriptEntities = disabled;
	}
	
	ArrayList<ScriptModule::ScriptEntityInfo*> StageLoader::getScriptEntities()
	{
		ArrayList<ScriptModule::ScriptEntityInfo*> entities;
		for(int i=0; i<scriptEntities.size(); i++)
		{
			bool canAdd = true;
			for(int j=0; j<disabledScriptEntities.size(); j++)
			{
				if(disabledScriptEntities.get(j) == i)
				{
					canAdd = false;
					j = disabledScriptEntities.size();
				}
			}
			
			if(canAdd)
			{
				entities.add(scriptEntities.get(i));
			}
		}
		
		return entities;
	}
#endif //SMASHBROS_SCRIPT_DISABLE
	
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

			case Global::STAGE_CORNERIA:
			return "corneria.png";
			
			case Global::STAGE_WHOMPFORTRESS:
			return "whompfortress.png";
		}
	}
	
	String StageLoader::getIconPath(int stageNo)
	{
		return (String)"Images/Menus/StageSelect/" + getMenuFilename(stageNo);
	}
	
	Stage* StageLoader::createStage(float x1, float y1, int stageNum)
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

			case Global::STAGE_CORNERIA:
			return new Corneria(x1,y1);

			case Global::STAGE_WHOMPFORTRESS:
			return new WhompFortress(x1,y1);			
			default:
#ifndef SMASHBROS_SCRIPT_DISABLE
			if(stageNum > Global::totalStages)
			{
				//TODO add loading of scripted stages
				int scriptStageNum = stageNum - Global::totalStages - 1;
				ArrayList<ScriptModule::ScriptEntityInfo*> entities = getScriptEntities();
				ScriptModule::ScriptEntityInfo* entityInfo = entities.get(scriptStageNum);
				String scriptPath = entityInfo->getPath() + '/' + entityInfo->getMainScript().script;
				ScriptModule::ScriptData* scriptData = ScriptModule::ScriptManager::getScriptData(scriptPath);
				SCRIPTMGR_ERRORHANDLE(return SCRIPTEDCLASS_NEWFUNCTION_CALL(Stage)(scriptData, x1, y1, std::vector<chaiscript::Boxed_Value>());, "TemplateStage.chai", )
			}
#endif //SMASHBROS_SCRIPT_DISABLE
			return null;
		}
		return null;
	}
}
