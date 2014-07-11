
#include "../../GameEngine/GameEngine.h"
#include "../SoundManager.h"

#pragma once

//menuNo
	//-1 TitleScreen
	//0 MainMenu
	//1 GroupMenu
	//2 SoloMenu
	//3 BrawlCharSelect
	//4 BrawlStageSelect
	//5 RulesMenu from BrawlCharSelect
	//6 RulesMenu from GroupMenu
	//7 ItemMenu from BrawCharSelect
	//8 ItemMenu from GroupMenu
	//9 OptionsMenu
	//10 AudioOptions
	//11 ControlOptions
	//12 DisplayOptions
	//13 OtherOptions
	//14 TrainingCharSelect
	//15 TrainingStageSelect

namespace SmashBros
{
	static const byte MENU_TITLESCREEN = -1;
	static const byte MENU_MAINMENU = 0;
	static const byte MENU_GROUPMENU = 1;
	static const byte MENU_SOLOMENU = 2;
	static const byte MENU_P2PMENU = 3;
	static const byte MENU_BRAWLCHARSELECT = 4;
	static const byte MENU_BRAWLSTAGESELECT = 5;
	static const byte MENU_RULESMENU_BRAWLCHARSELECT = 6;
	static const byte MENU_RULESMENU_GROUPMENU = 7;
	static const byte MENU_RULESMENU_P2PCHARSELECT = 8;
	static const byte MENU_ITEMMENU_BRAWLCHARSELECT = 9;
	static const byte MENU_ITEMMENU_GROUPMENU = 10;
	static const byte MENU_ITEMMENU_P2PCHARSELECT = 11;
	static const byte MENU_OPTIONSMENU = 12;
	static const byte MENU_AUDIOOPTIONS = 13;
	static const byte MENU_CONTROLOPTIONS = 14;
	static const byte MENU_DISPLAYOPTIONS = 15;
	static const byte MENU_OTHEROPTIONS = 16;
	static const byte MENU_TRAININGCHARSELECT = 17;
	static const byte MENU_TRAININGSTAGESELECT = 18;
	static const byte MENU_P2PCHARSELECT = 19;
	static const byte MENU_P2PSTAGESELECT = 20;
	
	class Menus
	{
	private:
		//static WAV*backclick;

		class BackButton : public Actor
		{
		public:
			BackButton(float x1, float y1);
			virtual ~BackButton();

			virtual void onMouseEnter();
			virtual void onMouseLeave();
			virtual void onRelease();
		};

	public:
		static Actor*button_back;
		static TextActor*description;
		static int menuNo;
		
		static SoundManager*soundMgr;
		static void playSound(const String&name);
		static void playSong(const String&name);

		static void loadAssets();
		static void loadMenus();
	};
}