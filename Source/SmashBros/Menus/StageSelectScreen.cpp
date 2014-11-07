
#include "StageSelectScreen.h"
#include "Menus.h"
#include "../Global.h"
#include "../Loader.h"

namespace SmashBros
{
	StageSelectScreen::StageIcon::StageIcon(StageSelectScreen*screen, float x1, float y1, int num) : Actor(x1,y1)
	{
		this->num = num;
		this->screen = screen;
	}

	StageSelectScreen::StageIcon::~StageIcon()
	{
		//
	}

	void StageSelectScreen::StageIcon::onMouseEnter()
	{
		setColor(Color::YELLOW);
	}

	void StageSelectScreen::StageIcon::onMouseLeave()
	{
		setColor(Color::WHITE);
	}

	void StageSelectScreen::StageIcon::onRelease()
	{
		Global::selectedStage = num;
		MusicManager::stop();
		screen->queueLoad = 1;
		screen->onSelect(num);
	}

	StageSelectScreen::StageSelectScreen(const String&name) : Screen(name)
	{
		stageGrid = new ActorGrid(80,145, 5, 8);
		stageGrid->setSpacing(105, 100);
		stageGrid->setScale(1.5f);
		for(int i=0; i<=Global::totalStages; i++)
		{
			StageIcon*a = new StageIcon(this, 0,0, i);
			String sPath = "";
			
			sPath = StageLoader::getIconPath(i);
			
			a->addAnimation(new Animation("normal",1,sPath));
			a->changeAnimation("normal", FORWARD);
			stageGrid->add(a);
		}
		
		loadScreen = new Actor(450,300);
		loadScreen->addAnimation(new Animation("normal",1,"Images/loading.png"));
		loadScreen->changeAnimation("normal", FORWARD);
		loadScreen->setAlpha(0.5f);
		loadScreen->Scale = 1.876f;

		queueLoad = 0;
		drawnOnce = false;
	}

	StageSelectScreen::~StageSelectScreen()
	{
		delete stageGrid;
		delete loadScreen;
	}

	void StageSelectScreen::onLoad()
	{
		//Open for implementation
		Global::LoadGame();
	}
	
	void StageSelectScreen::onSelect(int stageNo)
	{
		//Open for implementation
	}
	
	void StageSelectScreen::onGoToGame()
	{
		//Open for implementation
		ScreenManager::GoToScreen("Game");
	}
	
#ifndef SMASHBROS_SCRIPT_DISABLE
	void StageSelectScreen::unloadScriptedStages()
	{
		stageGrid->remove(scriptStageIcons, false);
		for(int i=0; i<scriptStageIcons.size(); i++)
		{
			delete scriptStageIcons.get(i);
		}
		scriptStageIcons.clear();
	}
	
	void StageSelectScreen::reloadScriptedStages()
	{
		unloadScriptedStages();
		
		ArrayList<ScriptModule::ScriptEntityInfo*> scriptEntities = StageLoader::getScriptEntities();
		for(int i=0; i<scriptEntities.size(); i++)
		{
			ScriptModule::ScriptEntityInfo* info = scriptEntities.get(i);
			String iconPath = info->getPath() + '/' + info->getIcon();
			bool loadedIcon = AssetManager::loadImage(iconPath);
			if(!loadedIcon)
			{
				iconPath = "Images/Menus/StageSelect/default.png";
				AssetManager::loadImage(iconPath);
			}
			
			StageIcon* stageIcon = new StageIcon(this, 0,0, Global::totalStages+i+1);
			stageIcon->addAnimation(new Animation("normal",1,iconPath));
			stageIcon->changeAnimation("normal", FORWARD);
			scriptStageIcons.add(stageIcon);
			stageGrid->add(stageIcon);
		}
	}
#endif //SMASHBROS_SCRIPT_DISABLE
	
	void StageSelectScreen::LoadContent()
	{
		Screen::LoadContent();
		queueLoad = 0;
		drawnOnce = false;
#ifndef SMASHBROS_SCRIPT_DISABLE
		reloadScriptedStages();
#endif //SMASHBROS_SCRIPT_DISABLE
	}
	
	void StageSelectScreen::UnloadContent()
	{
		Screen::UnloadContent();
		queueLoad = 0;
		drawnOnce = false;
#ifndef SMASHBROS_SCRIPT_DISABLE
		unloadScriptedStages();
#endif //SMASHBROS_SCRIPT_DISABLE
	}
	
	void StageSelectScreen::Update(long gameTime)
	{
		if(drawnOnce)
		{
			if(queueLoad==1)
			{
				onLoad();
				queueLoad++;
			}
			else if(queueLoad == 2)
			{
				onGoToGame();
				queueLoad = 0;
				drawnOnce = false;
			}
		}
		stageGrid->Update(gameTime);
		Menus::button_back->Update(gameTime);
	}

	void StageSelectScreen::Draw(Graphics2D&g, long gameTime)
	{
		stageGrid->Draw(g, gameTime);
		Menus::button_back->Draw(g, gameTime);
		if(queueLoad>0)
		{
			loadScreen->Draw(g, gameTime);
			drawnOnce = true;
		}
	}
}