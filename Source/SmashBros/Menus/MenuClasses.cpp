
#include "../Global.h"
#include "MenuClasses.h"
#include "../Preferences.h"
#include "Menus.h"
#include "../Controls.h"
#include "../MusicManager.h"
#include "../P2PDataManager.h"

namespace SmashBros
{
	TitleScreen::TitleScreenActor::TitleScreenActor(TitleScreen*screen, float x1, float y1) : Actor(x1,y1)
	{
		this->screen = screen;
	}
	
	TitleScreen::TitleScreenActor::~TitleScreenActor()
	{
		//
	}
	
	void TitleScreen::TitleScreenActor::onRelease()
	{
		setEventEnabled(Actor::EVENT_MOUSERELEASE, false);
		screen->changing = true;
		screen->changeTime = Game::getGameTime() + 1600;
		MusicManager::stop();
		Menus::playSound("titlescreen click");
	}
	
	TitleScreen::TitleScreen(const String&name) : Screen(name)
	{
		titleScreen = null;
		changeTime = 0;
		changing = false;
	}
	
	TitleScreen::~TitleScreen()
	{
		if(titleScreen!=null)
		{
			delete titleScreen;
		}
	}
	
	void TitleScreen::Initialize()
	{
		titleScreen = new TitleScreenActor(this, (float)View::getScalingWidth()/2,(float)View::getScalingHeight()/2);
	}
	
	void TitleScreen::LoadContent()
	{
		MusicManager::loadSong("Main Theme");
		Menus::playSong("Main Theme");
		titleScreen->setEventEnabled(Actor::EVENT_MOUSERELEASE, true);
		Game::showBackground(false);
		Menus::menuNo = MENU_TITLESCREEN;
		Animation*anim = new Animation("title",1);
		anim->addFrame("Images/Menus/titlescreen.png");
		titleScreen->addAnimation(anim);
		titleScreen->changeAnimation("title", FORWARD);
		titleScreen->setScale(1.876f);
	}
	
	void TitleScreen::Update(long gameTime)
	{
		titleScreen->Update(gameTime);
		if(changing && changeTime<=gameTime)
		{
			MusicManager::loadSong("Menu Theme");
			ScreenManager::GoToScreen("MainMenu");
			changeTime = 0;
			changing = false;
		}
	}
	
	void TitleScreen::Draw(Graphics2D&g, long gameTime)
	{
		if(changing)
		{
			g.setColor(Color::WHITE);
			g.fillRect(0, 0, (float)View::getScalingWidth(), (float)View::getScalingHeight());
		}
		else
		{
			titleScreen->Draw(g, gameTime);
		}
	}

	MainMenu::MainMenu(const String&name) : MenuScreen(name)
	{
		//
	}

	MainMenu::~MainMenu()
	{
		//
	}

	void MainMenu::Initialize()
	{
		addItem(260, 180, "Images/Menus/Buttons/Group/group.png", "Images/Menus/Buttons/Group/group_selected.png", "GroupMenu");
		setItemScale(0,1.15f);
		setItemSound(0, Menus::soundMgr->getSound("select menu item"));
		addItem(630, 215, "Images/Menus/Buttons/Solo/solo.png", "Images/Menus/Buttons/Solo/solo_selected.png", "SoloMenu");
		setItemScale(1,1.15f);
		setItemSound(1, Menus::soundMgr->getSound("select menu item"));
		addItem(700, 395, "Images/Menus/Buttons/Options/options.png", "Images/Menus/Buttons/Options/options_selected.png", "OptionsMenu");
		setItemScale(2,1.25f);
		setItemSound(2, Menus::soundMgr->getSound("select menu item"));
		if(GameEngine::isOnPlatform("ios"))
		{
			addItem(200, 400, "Images/Menus/Buttons/Bluetooth/Bluetooth.png", "Images/Menus/Buttons/Bluetooth/Bluetooth_selected.png", "BluetoothMenu");
			setItemSound(3, Menus::soundMgr->getSound("select menu item"));
		}
	}

	void MainMenu::LoadContent()
	{
		if(Menus::menuNo==MENU_TITLESCREEN)
		{
			MusicManager::loadSong("Menu Theme");
			Menus::playSong("Menu Theme");
		}
		Menus::menuNo = MENU_MAINMENU;
		Game::setBackgroundImage("Images/Menus/Backgrounds/bg2.png");
		if(Preferences::menuSoundFXOn())
		{
			this->enableSound(true);
		}
		else
		{
			this->enableSound(false);
		}

	}

	void MainMenu::Update(long gameTime)
	{
		MenuScreen::Update(gameTime);
		Menus::button_back->Update(gameTime);
		Menus::description->Update(gameTime);
		
		switch(selectedIndex)
		{
			default:
			Menus::description->setText("");
			break;
					
			case 0:
			Menus::description->setText("Play a variety of Smash modes with multiple players");
			break;
					
			case 1:
			Menus::description->setText("Play this mode solo or challenge it coopertively");
			break;
					
			case 2:
			Menus::description->setText("Choose and save your own personal Smash settings");
			break;
		}
	}

	void MainMenu::Draw(Graphics2D&g, long gameTime)
	{
		MenuScreen::Draw(g,gameTime);
		Menus::button_back->Draw(g, gameTime);
		Menus::description->Draw(g,gameTime);
	}
	
	GroupMenu::GroupMenu(const String&name) : MenuScreen(name)
	{
		//
	}

	GroupMenu::~GroupMenu()
	{
		//
	}

	void GroupMenu::Initialize()
	{
		addItem(280, 200, "Images/Menus/Buttons/Group/brawl.png", "Images/Menus/Buttons/Group/brawl_selected.png", "BrawlCharSelect");
		setItemSound(0, Menus::soundMgr->getSound("select menu item"));
		addItem(680, 220, "Images/Menus/Buttons/Group/rules.png", "Images/Menus/Buttons/Group/rules_selected.png", "RulesMenu");
		setItemScale(1, 2);
		setItemSound(1, Menus::soundMgr->getSound("select menu item"));
	}

	void GroupMenu::LoadContent()
	{
		Menus::menuNo = MENU_GROUPMENU;
		if(Global::gameMode == 0)
		{
			Global::gameMode = Global::MODE_TIME_LIMIT;
		}
		Game::setBackgroundImage("Images/Menus/Backgrounds/bg2.png");
		if(Preferences::menuSoundFXOn())
		{
			this->enableSound(true);
		}
		else
		{
			this->enableSound(false);
		}
	}

	void GroupMenu::Update(long gameTime)
	{
		MenuScreen::Update(gameTime);
		Menus::button_back->Update(gameTime);
		switch(selectedIndex)
		{
			default:
			Menus::description->setText("");
			break;
					
			case 0:
			Menus::description->setText("Jump right in and start brawling with your friends!");
			break;
		}
		Menus::description->Update(gameTime);
	}

	void GroupMenu::Draw(Graphics2D&g, long gameTime)
	{
		MenuScreen::Draw(g, gameTime);
		Menus::button_back->Draw(g, gameTime);
		Menus::description->Draw(g, gameTime);
	}

	SoloMenu::SoloMenu(const String&name) : MenuScreen(name)
	{
		//
	}

	SoloMenu::~SoloMenu()
	{
		//
	}

	void SoloMenu::Initialize()
	{
		addItem(700, 380, "Images/Menus/Buttons/Solo/training.png", "Images/Menus/Buttons/Solo/training_selected.png", "TrainingCharSelect");
		//setItemScale(0, 1.6f);
		setItemSound(0, Menus::soundMgr->getSound("select menu item"));
	}

	void SoloMenu::LoadContent()
	{
		Menus::menuNo = MENU_SOLOMENU;
		Game::setBackgroundImage("Images/Menus/Backgrounds/bg2.png");
		if(Preferences::menuSoundFXOn())
		{
			this->enableSound(true);
		}
		else
		{
			this->enableSound(false);
		}
	}

	void SoloMenu::Update(long gameTime)
	{
		MenuScreen::Update(gameTime);
		Menus::button_back->Update(gameTime);
	}

	void SoloMenu::Draw(Graphics2D&g, long gameTime)
	{
		MenuScreen::Draw(g, gameTime);
		Menus::button_back->Draw(g, gameTime);
	}

	BrawlCharSelect::RulesBar::RulesBar(float x1, float y1) : Actor(x1,y1)
	{
		//
	}

	BrawlCharSelect::RulesBar::~RulesBar()
	{
		//
	}

	void BrawlCharSelect::RulesBar::onMouseEnter()
	{
		changeAnimation("hover", FORWARD);
	}

	void BrawlCharSelect::RulesBar::onMouseLeave()
	{
		changeAnimation("normal", FORWARD);
	}

	void BrawlCharSelect::RulesBar::onRelease()
	{
		ScreenManager::GoToScreen("RulesMenu");
		changeAnimation("normal",FORWARD);
	}

	BrawlCharSelect::ReadyToFightBar::ReadyToFightBar(float x1, float y1) : Actor(x1,y1)
	{
		//
	}

	BrawlCharSelect::ReadyToFightBar::~ReadyToFightBar()
	{
		//
	}

	void BrawlCharSelect::ReadyToFightBar::onMouseEnter()
	{
		changeAnimation("hover",FORWARD);
	}

	void BrawlCharSelect::ReadyToFightBar::onMouseLeave()
	{
		changeAnimation("normal",FORWARD);
	}

	void BrawlCharSelect::ReadyToFightBar::onRelease()
	{
		ScreenManager::GoToScreen("BrawlStageSelect");
	}

	BrawlCharSelect::TeamsButton::TeamsButton(float x1, float y1) : Actor(x1, y1)
	{
		//
	}

	BrawlCharSelect::TeamsButton::~TeamsButton()
	{
		//
	}

	void BrawlCharSelect::TeamsButton::onMouseEnter()
	{
		if(Global::teamBattle)
		{
			changeAnimation("team_hover", FORWARD);
		}
		else
		{
			changeAnimation("hover", FORWARD);
		}
	}

	void BrawlCharSelect::TeamsButton::onMouseLeave()
	{
		if(Global::teamBattle)
		{
			changeAnimation("team_normal", FORWARD);
		}
		else
		{
			changeAnimation("normal", FORWARD);
		}
	}

	void BrawlCharSelect::TeamsButton::onRelease()
	{
		if(Global::teamBattle)
		{
			Global::teamBattle = false;
			if(mouseOver())
			{
				changeAnimation("hover", FORWARD);
			}
			else
			{
				changeAnimation("normal", FORWARD);
			}
		}
		else
		{
			Global::teamBattle = true;
			if(mouseOver())
			{
				changeAnimation("team_hover", FORWARD);
			}
			else
			{
				changeAnimation("team_normal", FORWARD); 
			}
		}
	}

	BrawlCharSelect::BrawlCharSelect(const String&name) : CharSelectScreen(name)
	{
		wasReadyToFight = false;
	}

	BrawlCharSelect::~BrawlCharSelect()
	{
		if(rules_bar!=null)
		{
			delete rules_bar;
		}
		if(rules_bar_text!=null)
		{
			delete rules_bar_text;
		}
		if(rules_bar_value!=null)
		{
			delete rules_bar_value;
		}
		if(rules_arrows!=null)
		{
			delete rules_arrows;
		}
		if(readyToFight!=null)
		{
			delete readyToFight;
		}
		if(teams_button!=null)
		{
			delete teams_button;
		}
	}

	void BrawlCharSelect::Initialize()
	{
		ArrayList<int> cardTypes;
		cardTypes.add(0); cardTypes.add(2); cardTypes.add(2); cardTypes.add(2);
		createCards(cardTypes);
		createCharIcons();

		ArrayList<int> resetTypes;
		resetTypes.add(1); resetTypes.add(0); resetTypes.add(0); resetTypes.add(0);
		resetCards(resetTypes);
		
		Animation*normal = new Animation("normal",1,"Images/Menus/Buttons/Generic/rules_bar.png");
		Animation*hover = new Animation("hover",1,"Images/Menus/Buttons/Generic/rules_bar_selected.png");
		rules_bar = new RulesBar(684,50);
		rules_bar->addAnimation(normal);
		rules_bar->addAnimation(hover);
		rules_bar->changeAnimation("normal", FORWARD);
		rules_bar->setScale(1.8f);
		rules_bar_value = new TextActor(510,60,"02",AssetManager::getFont("Fonts/arial.ttf", Font::BOLD, 30),Color::BLACK);
		rules_bar_value->setAlignment(TextActor::ALIGN_BOTTOMLEFT);
		rules_bar_text = new TextActor(560,60,"",AssetManager::getFont("Fonts/arial.ttf", Font::BOLD, 26),Color::BLACK);
		rules_bar_text->setAlignment(TextActor::ALIGN_BOTTOMLEFT);
		
		readyToFight = new ReadyToFightBar((float)View::getScalingWidth()/2, 380);
		readyToFight->addAnimation(new Animation("normal",1,"Images/Menus/Buttons/Generic/readytofight.png"));
		readyToFight->addAnimation(new Animation("hover",1,"Images/Menus/Buttons/Generic/readytofight_selected.png"));
		readyToFight->changeAnimation("normal", FORWARD);
		readyToFight->setScale(1.845f);
		readyToFight->mouseOverUsesPixel(true);
		
		rules_arrows = new Arrows(530,22,530,72);
		switch(Global::gameMode)
		{
			case Global::MODE_STOCK:
			rules_arrows->setValue(Global::stockAmount);
			rules_arrows->setProperties(Global::minLives, Global::maxLives, 1);
			break;
					
			case Global::MODE_TIME_LIMIT:
			rules_arrows->setValue(Global::timeLimit);
			rules_arrows->setProperties(Global::minTime, Global::maxTime, 1);
			break;
		}
		rules_arrows->setScale(1.5f);
		
		teams_button = new TeamsButton(260,35);
		teams_button->setScale(1.7f);
		
		teams_button->addAnimation(new Animation("normal",1,"Images/Menus/Buttons/Group/freeforall.png"));
		teams_button->addAnimation(new Animation("hover",1,"Images/Menus/Buttons/Group/freeforall_selected.png"));
		teams_button->addAnimation(new Animation("team_normal",1,"Images/Menus/Buttons/Group/teambattle.png"));
		teams_button->addAnimation(new Animation("team_hover",1,"Images/Menus/Buttons/Group/teambattle_selected.png"));
		teams_button->changeAnimation("normal", FORWARD);
	}

	void BrawlCharSelect::LoadContent()
	{
		if(Menus::menuNo==MENU_GROUPMENU)
		{
			ArrayList<int> resetType;
			resetType.add(1); resetType.add(0); resetType.add(0); resetType.add(0);
			resetCards(resetType);
			
			for(int i=0; i<4; i++)
			{
				hideCoin(i, false);
				enableCardChange(i);
			}
			wasReadyToFight = false;
		}
		else if(Menus::menuNo==MENU_P2PMENU)
		{
			ArrayList<int> resetType;
			resetType.add(1); resetType.add(1);
			resetCards(resetType);
			for(int i=0; i<4; i++)
			{
				disableCardChange(i);
			}
			for(int i=1; i<4; i++)
			{
				hideCoin(i, true);
			}
			wasReadyToFight = false;
		}
		
		if(Menus::menuNo == MENU_P2PMENU || Menus::menuNo == MENU_RULESMENU_P2PCHARSELECT || Menus::menuNo == MENU_P2PSTAGESELECT)
		{
			Menus::menuNo=MENU_P2PCHARSELECT;
		}
		else
		{
			Menus::menuNo=MENU_BRAWLCHARSELECT;
		}
		switch(Global::gameMode)
		{
			case Global::MODE_STOCK:
			rules_arrows->setProperties(Global::minLives, Global::maxLives, 1);
			rules_arrows->setValue(Global::stockAmount);
			break;
			
			case Global::MODE_TIME_LIMIT:
			rules_arrows->setProperties(Global::minTime, Global::maxTime, 1);
			rules_arrows->setValue(Global::timeLimit);
			break;
		}
		if(Global::teamBattle)
		{
			teams_button->changeAnimation("team_normal", FORWARD);
		}
		else
		{
			teams_button->changeAnimation("normal", FORWARD);
		}
		Game::setBackgroundImage("Images/Menus/Backgrounds/bg1.png");
	}
	
	void BrawlCharSelect::Update(long gameTime)
	{
		P2PDataManager::updateGame(gameTime);
		switch(Global::gameMode)
		{
			case Global::MODE_STOCK:
			rules_arrows->setValue(Global::stockAmount);
			rules_arrows->setProperties(Global::minLives, Global::maxLives, 1);
			break;
			
			case Global::MODE_TIME_LIMIT:
			rules_arrows->setValue(Global::timeLimit);
			rules_arrows->setProperties(Global::minTime, Global::maxTime, 1);
			break;
		}
		if(Menus::menuNo==MENU_P2PCHARSELECT)
		{
			selectCharacter(2, Global::selectedChar[1]); //TODO: fix for multiple peers
		}
		CharSelectScreen::Update(gameTime);
		rules_arrows->Update(gameTime);
		if(rules_arrows->wasClicked())
		{
			rules_bar->setEventEnabled(Actor::EVENT_MOUSERELEASE, false);
		}
		else
		{
			rules_bar->setEventEnabled(Actor::EVENT_MOUSERELEASE, true);
		}
		rules_bar->Update(gameTime);
		int prevValue;
		switch(Global::gameMode)
		{
			case Global::MODE_STOCK:
			prevValue = Global::stockAmount;
			Global::stockAmount = rules_arrows->getValue();
			if(prevValue!=Global::stockAmount)
			{
				P2PDataManager::toggleSetting("stockAmount", 0);
			}
			if(Global::stockAmount<10)
			{
				rules_bar_value->setText((String)"0" + Global::stockAmount);
			}
			else
			{
				rules_bar_value->setText((String)"" + Global::stockAmount);
			}
			rules_bar_text->setText("- Man Survival Test!");
			break;
					
			case Global::MODE_TIME_LIMIT:
			prevValue = Global::timeLimit;
			Global::timeLimit = rules_arrows->getValue();
			if(prevValue != Global::timeLimit)
			{
				P2PDataManager::toggleSetting("timeLimit", 0);
			}
			if(Global::timeLimit<10)
			{
				rules_bar_value->setText((String)"0" + Global::timeLimit);
			}
			else
			{
				rules_bar_value->setText((String)"" + Global::timeLimit);
			}
			rules_bar_text->setText("- Minute Survival Match!");
			break;
		}
		rules_bar_value->Update(gameTime);
		rules_bar_text->Update(gameTime);
		if(!P2PDataManager::isEnabled())
		{
			teams_button->Update(gameTime);
		}
		if(checkReadyToFight(2) && !coinsClicked())
		{
			if(!wasReadyToFight)
			{
				wasReadyToFight = true;
				Menus::playSound("ready to fight");
			}
			readyToFight->Update(gameTime);
		}
		else
		{
			wasReadyToFight = false;
		}
	}
	
	void BrawlCharSelect::Draw(Graphics2D&g, long gameTime)
	{
		rules_bar->Draw(g, gameTime);
		rules_bar_value->Draw(g, gameTime);
		rules_bar_text->Draw(g, gameTime);
		rules_arrows->Draw(g, gameTime);
		if(!P2PDataManager::isEnabled())
		{
			teams_button->Draw(g, gameTime);
		}
		CharSelectScreen::Draw(g,gameTime);
		if(checkReadyToFight(2) && !coinsClicked())
		{
			readyToFight->Draw(g, gameTime);
		}
	}
	
	void BrawlCharSelect::onSelectCharacter(int player, int character)
	{
		if(P2PManager::isConnected() && player==1)
		{
			DataVoid data;
			byte type = P2PDataManager::DATA_CHARSELECT;
			data.add(&type, sizeof(byte));
			data.add(&character, sizeof(character));
			P2PManager::sendData(data.getData(), data.length(), P2PManager::SENDDATA_RELIABLE);
		}
	}

	BrawlStageSelect::BrawlStageSelect(const String&name) : StageSelectScreen(name)
	{
		//
	}

	BrawlStageSelect::~BrawlStageSelect()
	{
		//
	}

	void BrawlStageSelect::LoadContent()
	{
		StageSelectScreen::LoadContent();
		if(Menus::menuNo == MENU_BRAWLCHARSELECT)
		{
			Menus::menuNo = MENU_BRAWLSTAGESELECT;
		}
		else if(Menus::menuNo == MENU_P2PCHARSELECT)
		{
			Menus::menuNo = MENU_P2PSTAGESELECT;
		}
		Global::gameType = Global::TYPE_GROUPBRAWL;
		Game::setBackgroundImage("Images/Menus/Backgrounds/bg1.png");
	}
	
	void BrawlStageSelect::Update(long gameTime)
	{
		StageSelectScreen::Update(gameTime);
	}
	
	void BrawlStageSelect::onSelect(int stageNo)
	{
		if(Menus::menuNo==MENU_P2PSTAGESELECT)
		{
			Global::stageVotes.add(stageNo);
			
			Global::selfReadyToPlay = true;
			DataVoid data;
			byte type = P2PDataManager::DATA_STARTGAME;
			data.add(&type, sizeof(type));
			data.add(&stageNo, sizeof(stageNo));
			P2PManager::sendData(data.getData(), data.length(), P2PManager::SENDDATA_RELIABLE);
		}
	}
	
	void BrawlStageSelect::onLoad()
	{
		if(Menus::menuNo==MENU_P2PSTAGESELECT)
		{
			Console::WriteLine("going to P2PWaitScreen");
			ScreenManager::GoToScreen("P2PWaitScreen");
		}
		else
		{
			StageSelectScreen::onLoad();
		}
	}
	
	OptionsMenu::OptionsMenu(const String&name) : MenuScreen(name)
	{
		//
	}

	OptionsMenu::~OptionsMenu()
	{
		//
	}

	void OptionsMenu::Initialize()
	{
		addItem(140, 270, "Images/Menus/Buttons/Options/controls.png", "Images/Menus/Buttons/Options/controls_selected.png", "ControlOptions");
		setItemScale(0, 1.6f);
		setItemSound(0, Menus::soundMgr->getSound("select menu item"));
		addItem(346, 270, "Images/Menus/Buttons/Options/sound.png", "Images/Menus/Buttons/Options/sound_selected.png", "AudioOptions");
		setItemScale(1, 1.6f);
		setItemSound(1, Menus::soundMgr->getSound("select menu item"));
		addItem(554, 270, "Images/Menus/Buttons/Options/display.png", "Images/Menus/Buttons/Options/display_selected.png", "DisplayOptions");
		setItemScale(2, 1.6f);
		setItemSound(2, Menus::soundMgr->getSound("select menu item"));
		addItem(760, 270, "Images/Menus/Buttons/Options/other.png", "Images/Menus/Buttons/Options/other_selected.png", "OtherOptions");
		setItemScale(3, 1.6f);
		setItemSound(3, Menus::soundMgr->getSound("select menu item"));
	}

	void OptionsMenu::LoadContent()
	{
		Menus::menuNo = MENU_OPTIONSMENU;
		Game::setBackgroundImage("Images/Menus/Backgrounds/bg2.png");
		if(Preferences::menuSoundFXOn())
		{
			this->enableSound(true);
		}
		else
		{
			this->enableSound(false);
		}
	}

	void OptionsMenu::Update(long gameTime)
	{
		MenuScreen::Update(gameTime);
		Menus::button_back->Update(gameTime);
		switch(selectedIndex)
		{
			default:
			Menus::description->setText("");
			break;
			
			case 0:
			Menus::description->setText("Customize your controls to fit your preference");
			break;
			
			case 1:
			Menus::description->setText("Change sound/music volume and behavior");
			break;
			
			case 2:
			Menus::description->setText("Change window to full screen and other display settings");
			break;
			
			case 3:
			Menus::description->setText("Miscellaneous settings");
			break;
		}
		Menus::description->Update(gameTime);
	}
	
	void OptionsMenu::Draw(Graphics2D&g, long gameTime)
	{
		MenuScreen::Draw(g, gameTime);
		Menus::button_back->Draw(g, gameTime);
		Menus::description->Draw(g, gameTime);
	}
	
	const float ControlOptions::farDist = 10000;
	const float ControlOptions::centerDist = 625;

	ControlOptions::ControlOptions(const String&name) : Screen(name)
	{
		joystickLabel = new MenuBarSmall(200,140,"Joystick");
		joystickLabel->setScale(2);
		dpadLabel = new MenuBarSmall(600,140,"D-Pad");
		dpadLabel->setScale(2);
		toggles = new ToggleButtons(390,140, 790,140);
		toggles->setScale(1.6f);
		
		button_a = new Actor(820, 450);
        button_a->addAnimation(new Animation("normal", 1, "Images/Game/Controls/button_a.png"));
        button_a->changeAnimation("normal", FORWARD);
        button_a->setRelativeToView(false);
		button_a->setScale(2);
		button_a->setAlpha(0.2f);
		
        button_b = new Actor(707.5f, 525);
        button_b->addAnimation(new Animation("normal", 1, "Images/Game/Controls/button_b.png"));
        button_b->changeAnimation("normal", FORWARD);
        button_b->setRelativeToView(false);
		button_b->setScale(2);
		button_b->setAlpha(0.2f);
		
        button_x = new Actor(820, 337.5f);
        button_x->addAnimation(new Animation("normal", 1, "Images/Game/Controls/button_xy.png"));
        button_x->changeAnimation("normal", FORWARD);
        button_x->setRelativeToView(false);
		button_x->setScale(2);
		button_x->setAlpha(0.2f);
		
        arrow_up = new Actor(150, 375);
        arrow_up->addAnimation(new Animation("normal", 1, "Images/Game/Controls/arrow_up.png"));
        arrow_up->changeAnimation("normal", FORWARD);
        arrow_up->setRelativeToView(false);
		arrow_up->setScale(2);
		arrow_up->setAlpha(0.5f);
		
        arrow_down = new Actor(150, 525);
        arrow_down->addAnimation(new Animation("normal", 1, "Images/Game/Controls/arrow_down.png"));
        arrow_down->changeAnimation("normal", FORWARD);
        arrow_down->setRelativeToView(false);
		arrow_down->setScale(2);
		arrow_down->setAlpha(0.5f);
		
        arrow_left = new Actor(75, 450);
        arrow_left->addAnimation(new Animation("normal", 1, "Images/Game/Controls/arrow_left.png"));
        arrow_left->changeAnimation("normal", FORWARD);
        arrow_left->setRelativeToView(false);
		arrow_left->setScale(2);
		arrow_left->setAlpha(0.5f);
		
        arrow_right = new Actor(225, 450);
        arrow_right->addAnimation(new Animation("normal", 1, "Images/Game/Controls/arrow_right.png"));
        arrow_right->changeAnimation("normal", FORWARD);
        arrow_right->setRelativeToView(false);
		arrow_right->setScale(2);
		arrow_right->setAlpha(0.5f);
		
		joystickArea = new WireframeActor(0,0,View::getScalingWidth()/2, View::getScalingHeight());
		joystickArea->relativeToView(false);
		
		joystick = new Actor(150, 450);
		joystick->addAnimation(new Animation("center", 1, "Images/Game/Controls/joystick_center.png"));
		joystick->addAnimation(new Animation("up", 1, "Images/Game/Controls/joystick_up.png"));
		joystick->addAnimation(new Animation("up2", 1, "Images/Game/Controls/joystick_up2.png"));
		joystick->addAnimation(new Animation("down", 1, "Images/Game/Controls/joystick_down.png"));
		joystick->addAnimation(new Animation("down2", 1, "Images/Game/Controls/joystick_down2.png"));
		joystick->addAnimation(new Animation("left", 1, "Images/Game/Controls/joystick_left.png"));
		joystick->addAnimation(new Animation("left2", 1, "Images/Game/Controls/joystick_left2.png"));
		joystick->addAnimation(new Animation("right", 1, "Images/Game/Controls/joystick_right.png"));
		joystick->addAnimation(new Animation("right2", 1, "Images/Game/Controls/joystick_right2.png"));
		joystick->addAnimation(new Animation("up_left", 1, "Images/Game/Controls/joystick_up_left.png"));
		joystick->addAnimation(new Animation("up_left2", 1, "Images/Game/Controls/joystick_up_left2.png"));
		joystick->addAnimation(new Animation("up_right", 1, "Images/Game/Controls/joystick_up_right.png"));
		joystick->addAnimation(new Animation("up_right2", 1, "Images/Game/Controls/joystick_up_right2.png"));
		joystick->addAnimation(new Animation("down_left", 1, "Images/Game/Controls/joystick_down_left.png"));
		joystick->addAnimation(new Animation("down_left2", 1, "Images/Game/Controls/joystick_down_left2.png"));
		joystick->addAnimation(new Animation("down_right", 1, "Images/Game/Controls/joystick_down_right.png"));
		joystick->addAnimation(new Animation("down_right2", 1, "Images/Game/Controls/joystick_down_right2.png"));
		joystick->changeAnimation("center", FORWARD);
		joystick->setRelativeToView(false);
		joystick->setScale(2);
		joystick->setAlpha(0.5f);
		
		joystickDir = 0;
		joystickFar = false;
		joystickDown = false;
		joystickEnabled = true;
	}
	
	ControlOptions::~ControlOptions()
	{
		delete button_a;
        delete button_b;
        delete button_x;
        delete arrow_up;
        delete arrow_down;
        delete arrow_left;
        delete arrow_right;
		delete joystick;
		delete joystickArea;
	}

	void ControlOptions::Initialize()
	{
		//
	}
	
	void ControlOptions::LoadContent()
	{
		Menus::menuNo = MENU_CONTROLOPTIONS;
		Game::setBackgroundImage("Images/Menus/Backgrounds/bg1.png");
		if(Controls::isJoystickActive())
		{
			joystickEnabled = true;
			toggles->setToggle(1);
		}
		else
		{
			joystickEnabled = false;
			toggles->setToggle(2);
		}

	}

	void ControlOptions::UnloadContent()
	{
		Preferences::save();
	}

	void ControlOptions::Update(long gameTime)
	{
		Menus::button_back->Update(gameTime);
		joystickLabel->Update(gameTime);
		dpadLabel->Update(gameTime);
		toggles->Update(gameTime);
		if(toggles->getToggle()==1)
		{
			joystickEnabled = true;
		}
		else if(toggles->getToggle()==2)
		{
			joystickEnabled = false;
		}
		
		joystickArea->Update(gameTime);
		joystick->Update(gameTime);
		button_a->Update(gameTime);
		button_b->Update(gameTime);
		button_x->Update(gameTime);
		arrow_up->Update(gameTime);
		arrow_down->Update(gameTime);
		arrow_left->Update(gameTime);
		arrow_right->Update(gameTime);
		
		if(!Menus::button_back->isClicked() && !toggles->isClicked())
		{
			if(button_a->isClicked() && !button_a->wasClicked())
			{
				button_a->setColor(Color::BLUE);
			}
			else if(!button_a->isClicked() && button_a->wasClicked())
			{
				button_a->setColor(Color::WHITE);
			}
			else if(button_b->isClicked() && !button_b->wasClicked())
			{
				button_b->setColor(Color::GREEN);
			}
			else if(!button_b->isClicked() && button_b->wasClicked())
			{
				button_b->setColor(Color::WHITE);
			}
			else if(button_x->isClicked() && !button_x->wasClicked())
			{
				button_x->setColor(Color::YELLOW);
			}
			else if(!button_x->isClicked() && button_x->wasClicked())
			{
				button_x->setColor(Color::WHITE);
			}
			
			if(joystickEnabled)
			{
				if(joystickArea->isClicked())
				{
					long touchId = joystickArea->getTouchId();
					int mousex = Game::getTouchX(touchId);
					int mousey = Game::getTouchY(touchId);
					byte dir = PrimitiveActor::getDir(joystick->x, joystick->y, (float)mousex, (float)mousey);
					float dist = (float)PrimitiveActor::distanceUnSqr(joystick->x, joystick->y, (float)mousex, (float)mousey);
					if(dist<=centerDist)
					{
						if(joystickDir!=0)
						{
							joystick->changeAnimation("center", NO_CHANGE);
							joystickDown = true;
							joystickFar = false;
							joystickDir = 0;
						}
					}
					else if(dist<farDist)
					{
						if(joystickDir!=dir)
						{
							joystickDir = dir;
							joystickDown = true;
							joystickFar = false;
							switch(dir)
							{
								case PrimitiveActor::DIR_UP:
								joystick->changeAnimation("up", NO_CHANGE);
								break;
								
								case PrimitiveActor::DIR_UPLEFT:
								joystick->changeAnimation("up_left", NO_CHANGE);
								break;
									
								case PrimitiveActor::DIR_UPRIGHT:
								joystick->changeAnimation("up_right", NO_CHANGE);
								break;
								
								case PrimitiveActor::DIR_LEFT:
								joystick->changeAnimation("left", NO_CHANGE);
								break;
									
								case PrimitiveActor::DIR_RIGHT:
								joystick->changeAnimation("right", NO_CHANGE);
								break;
									
								case PrimitiveActor::DIR_DOWNLEFT:
								joystick->changeAnimation("down_left", NO_CHANGE);
								break;
									
								case PrimitiveActor::DIR_DOWNRIGHT:
								joystick->changeAnimation("down_right", NO_CHANGE);
								break;
									
								case PrimitiveActor::DIR_DOWN:
								joystick->changeAnimation("down", NO_CHANGE);
								break;
							}
						}
					}
					else
					{
						if(!(joystickDir==dir && joystickFar))
						{
							joystickDir = dir;
							joystickDown = true;
							joystickFar = true;
							switch(dir)
							{
								case PrimitiveActor::DIR_UP:
								joystick->changeAnimation("up2", NO_CHANGE);
								break;
									
								case PrimitiveActor::DIR_UPLEFT:
								joystick->changeAnimation("up_left2", NO_CHANGE);
								break;
									
								case PrimitiveActor::DIR_UPRIGHT:
								joystick->changeAnimation("up_right2", NO_CHANGE);
								break;
									
								case PrimitiveActor::DIR_LEFT:
								joystick->changeAnimation("left2", NO_CHANGE);
								break;
									
								case PrimitiveActor::DIR_RIGHT:
								joystick->changeAnimation("right2", NO_CHANGE);
								break;
										
								case PrimitiveActor::DIR_DOWNLEFT:
								joystick->changeAnimation("down_left2", NO_CHANGE);
								break;
								
								case PrimitiveActor::DIR_DOWNRIGHT:
								joystick->changeAnimation("down_right2", NO_CHANGE);
								break;
									
								case PrimitiveActor::DIR_DOWN:
								joystick->changeAnimation("down2", NO_CHANGE);
								break;
							}
						}
					}
				}
				else
				{
					if(joystickDown)
					{
						joystick->changeAnimation("center", NO_CHANGE);
						joystickDir = 0;
						joystickDown = false;
						joystickFar = false;
					}
				}
			}
			else
			{
				if(arrow_up->isClicked() && !arrow_up->wasClicked())
				{
					arrow_up->setColor(Color::YELLOW);
				}
				else if(!arrow_up->isClicked() && arrow_up->wasClicked())
				{
					arrow_up->setColor(Color::WHITE);
				}
				if(arrow_down->isClicked() && !arrow_down->wasClicked())
				{
					arrow_down->setColor(Color::YELLOW);
				}
				else if(!arrow_down->isClicked() && arrow_down->wasClicked())
				{
					arrow_down->setColor(Color::WHITE);
				}
				if(arrow_left->isClicked() && !arrow_left->wasClicked())
				{
					arrow_left->setColor(Color::YELLOW);
				}
				else if(!arrow_left->isClicked() && arrow_left->wasClicked())
				{
					arrow_left->setColor(Color::WHITE);
				}
				if(arrow_right->isClicked() && !arrow_right->wasClicked())
				{
					arrow_right->setColor(Color::YELLOW);
				}
				else if(!arrow_right->isClicked() && arrow_right->wasClicked())
				{
					arrow_right->setColor(Color::WHITE);
				}
			}
		}
		Controls::setJoystickActive(joystickEnabled);
	}

	void ControlOptions::Draw(Graphics2D&g, long gameTime)
	{
		Menus::button_back->Draw(g, gameTime);
		joystickLabel->Draw(g, gameTime);
		dpadLabel->Draw(g, gameTime);
		toggles->Draw(g, gameTime);
		
		button_a->Draw(g, gameTime);
		button_b->Draw(g, gameTime);
		button_x->Draw(g, gameTime);
		if(joystickEnabled)
		{
			joystickArea->Draw(g, gameTime);
			joystick->Draw(g, gameTime);
		}
		else
		{
			arrow_up->Draw(g, gameTime);
			arrow_down->Draw(g, gameTime);
			arrow_left->Draw(g, gameTime);
			arrow_right->Draw(g, gameTime);
		}
	}
	
	AudioOptions::AudioOptions(const String&name) : Screen(name)
	{
		menumusic = null;
		menusoundfx = null;
		ingamemusic = null;
	}

	AudioOptions::~AudioOptions()
	{
		if(menumusic!=null)
		{
			delete menumusic;
		}
		if(menusoundfx!=null)
		{
			delete menusoundfx;
		}
		if(ingamemusic!=null)
		{
			delete ingamemusic;
		}
	}

	void AudioOptions::onSettingToggle(String setting, boolean toggle)
	{
		if(setting.equals("menumusic"))
		{
			Preferences::toggleMenuMusic(toggle);
			if(toggle)
			{
				MusicManager::play();
			}
			else
			{
				MusicManager::stop();
			}
		}
		else if(setting.equals("menusoundfx"))
		{
			Preferences::toggleMenuSoundFX(toggle);
		}
		else if(setting.equals("ingamemusic"))
		{
			Preferences::toggleInGameMusic(toggle);
		}
	}

	void AudioOptions::Initialize()
	{
		prevMenumusic = Preferences::menuMusicOn();
		prevMenusoundfx = Preferences::menuSoundFXOn();
		prevIngamemusic = Preferences::ingameMusicOn();

		menumusic = new MenuBarToggle(300,130,"Menu Music",prevMenumusic);
		menumusic->setScale(1.6f);
		
		menusoundfx = new MenuBarToggle(300,200,"Menu SoundFX",prevMenusoundfx);
		menusoundfx->setScale(1.6f);
		menusoundfx->setTextOffsetX(18);
		
		ingamemusic = new MenuBarToggle(300,270,"In-Game Music",prevIngamemusic);
		ingamemusic->setScale(1.6f);
		ingamemusic->setTextOffsetX(20);
	}
	
	void AudioOptions::LoadContent()
	{
		Menus::menuNo = MENU_AUDIOOPTIONS;
		Game::setBackgroundImage("Images/Menus/Backgrounds/bg2.png");
	}
	
	void AudioOptions::UnloadContent()
	{
		Preferences::save();
	}

	void AudioOptions::Update(long gameTime)
	{
		menumusic->Update(gameTime);
		if(menumusic->getToggle() != prevMenumusic)
		{
			onSettingToggle("menumusic", menumusic->getToggle());
		}
		prevMenumusic = menumusic->getToggle();

		menusoundfx->Update(gameTime);
		if(menusoundfx->getToggle() != prevMenusoundfx)
		{
			onSettingToggle("menusoundfx", menusoundfx->getToggle());
		}
		prevMenusoundfx = menusoundfx->getToggle();
		
		ingamemusic->Update(gameTime);
		if(ingamemusic->getToggle() != prevIngamemusic)
		{
			onSettingToggle("ingamemusic", ingamemusic->getToggle());
		}
		prevIngamemusic = ingamemusic->getToggle();
		
		Menus::button_back->Update(gameTime);
	}

	void AudioOptions::Draw(Graphics2D&g, long gameTime)
	{
		menumusic->Draw(g, gameTime);
		menusoundfx->Draw(g, gameTime);
		ingamemusic->Draw(g, gameTime);
		Menus::button_back->Draw(g, gameTime);
	}

	DisplayOptions::DisplayOptions(const String&name) : Screen(name)
	{
		//
	}

	DisplayOptions::~DisplayOptions()
	{
		if(fullScreen!=null)
		{
			delete fullScreen;
		}
		if(fps!=null)
		{
			delete fps;
		}
	}

	void DisplayOptions::onSettingToggle(String setting, boolean toggle)
	{
		if(setting.equals("fullscreen"))
		{
			//TODO: add fullscreen
			//Game::setFullScreen(toggle);
		}
	}
	
	void DisplayOptions::Initialize()
	{
		/*fullScreen = new MenuBarToggle(300,130,"Full Screen");
		fullScreen->Scale = 1.6f;
		prevFullscreen = fullScreen->getToggle();*/
		
		fps = new MenuBarValue(300, 130/*200*/, "Frame Rate");
		if(Preferences::highFPS())
		{
			fps->setValue(60);
		}
		else
		{
			fps->setValue(30);
		}
		fps->setProperties(30, 60, 30);
		fps->setScale(1.6f);
	}
	
	void DisplayOptions::LoadContent()
	{
		Menus::menuNo = MENU_DISPLAYOPTIONS;
		Game::setBackgroundImage("Images/Menus/Backgrounds/bg2.png");
		if(Preferences::highFPS())
		{
			fps->setValue(60);
		}
		else
		{
			fps->setValue(30);
		}
	}
	
	void DisplayOptions::UnloadContent()
	{
		Preferences::save();
	}

	void DisplayOptions::Update(long gameTime)
	{
		/*fullScreen->Update(gameTime);
		if(prevFullscreen != fullScreen->getToggle())
		{
			onSettingToggle("fullscreen",fullScreen->getToggle());
		}
		prevFullscreen = fullScreen->getToggle();*/

		fps->Update(gameTime);
		if(fps->getValue()==60)
		{
			Preferences::setHighFPS(true);
		}
		else if(fps->getValue()==30)
		{
			Preferences::setHighFPS(false);
		}
		Menus::button_back->Update(gameTime);
	}

	void DisplayOptions::Draw(Graphics2D&g, long gameTime)
	{
		//fullScreen->Draw(g, gameTime);
		fps->Draw(g, gameTime);
		Menus::button_back->Draw(g, gameTime);
	}
	
	OtherOptions::FacebookButton::FacebookButton(float x1, float y1, const String&label) : MenuBarSmallButton(x1,y1,label) {}
	OtherOptions::FacebookButton::~FacebookButton() {}
	void OtherOptions::FacebookButton::onRelease()
	{
		openURL("https://www.facebook.com/BrokenPhysicsStudios/");
	}
	
	OtherOptions::TwitterButton::TwitterButton(float x1, float y1, const String&label) : MenuBarSmallButton(x1,y1,label) {}
	OtherOptions::TwitterButton::~TwitterButton() {}
	void OtherOptions::TwitterButton::onRelease()
	{
		openURL("https://www.twitter.com/lufinkey/");
	}
	
	OtherOptions::ContactDeveloperButton::ContactDeveloperButton(float x1, float y1, const String&label) : MenuBarSmallButton(x1,y1,label) {}
	OtherOptions::ContactDeveloperButton::~ContactDeveloperButton() {}
	void OtherOptions::ContactDeveloperButton::onRelease()
	{
		writeEmail(Game::getWindow(), "luisfinke@gmail.com", "iSSB", "");
	}
	
	OtherOptions::PatreonButton::PatreonButton(float x1, float y1, const String&label) : MenuBarSmallButton(x1,y1,label) {}
	OtherOptions::PatreonButton::~PatreonButton() {}
	void OtherOptions::PatreonButton::onRelease()
	{
		openURL("https://www.patreon.com/lufinkey");
	}
	
	OtherOptions::VenmoButton::VenmoButton(float x1, float y1, const String&label) : MenuBarSmallButton(x1,y1,label) {}
	OtherOptions::VenmoButton::~VenmoButton() {}
	void OtherOptions::VenmoButton::onRelease()
	{
		openURL("https://venmo.com/lufinkey");
	}
	
	OtherOptions::OtherOptions(const String&name) : Screen(name)
	{
		facebook = NULL;
		twitter = NULL;
		contactDev = NULL;
		patreon = NULL;
		venmo = NULL;
	}
	
	OtherOptions::~OtherOptions()
	{
		if(facebook!=NULL)
		{
			delete facebook;
		}
		if(twitter!=NULL)
		{
			delete twitter;
		}
		if(contactDev!=NULL)
		{
			delete contactDev;
		}
		if(patreon!=NULL)
		{
			delete patreon;
		}
		if(venmo!=NULL)
		{
			delete venmo;
		}
	}
	
	void OtherOptions::Initialize()
	{
		facebook = new FacebookButton(200,140, "Our Facebook");
		facebook->setScale(2.0f);
		facebook->setLabelSize(14);
		
		twitter = new TwitterButton(200,200, "Follow on Twitter");
		twitter->setScale(2.0f);
		twitter->setLabelSize(14);
		twitter->setTextOffsetX(10);
		
		contactDev = new ContactDeveloperButton(200,260, "Email Developer");
		contactDev->setScale(2.0f);
		contactDev->setLabelSize(14);
		contactDev->setTextOffsetX(8);
		
		patreon = new PatreonButton(200,320, "Patreon");
		patreon->setScale(2.0f);
		patreon->setLabelSize(14);
		patreon->setTextOffsetX(-26);
		
		venmo = new VenmoButton(200,380, "Donate with Venmo");
		venmo->setScale(2.0f);
		venmo->setLabelSize(14);
	}
	
	void OtherOptions::LoadContent()
	{
		Menus::menuNo = MENU_OTHEROPTIONS;
	}
	
	void OtherOptions::Update(long gameTime)
	{
		Menus::button_back->Update(gameTime);
		facebook->Update(gameTime);
		twitter->Update(gameTime);
		contactDev->Update(gameTime);
		patreon->Update(gameTime);
		venmo->Update(gameTime);
	}
	
	void OtherOptions::Draw(Graphics2D&g, long gameTime)
	{
		Menus::button_back->Draw(g, gameTime);
		facebook->Draw(g, gameTime);
		twitter->Draw(g, gameTime);
		contactDev->Draw(g, gameTime);
		patreon->Draw(g, gameTime);
		venmo->Draw(g, gameTime);
	}
	
	TrainingCharSelect::ReadyToFightBar::ReadyToFightBar(float x1, float y1) : Actor(x1,y1)
	{
		//
	}
	
	TrainingCharSelect::ReadyToFightBar::~ReadyToFightBar()
	{
		//
	}

	void TrainingCharSelect::ReadyToFightBar::onMouseEnter()
	{
		changeAnimation("hover",FORWARD);
	}

	void TrainingCharSelect::ReadyToFightBar::onMouseLeave()
	{
		changeAnimation("normal",FORWARD);
	}

	void TrainingCharSelect::ReadyToFightBar::onRelease()
	{
		ScreenManager::GoToScreen("TrainingStageSelect");
	}

	TrainingCharSelect::TrainingCharSelect(String name) : CharSelectScreen(name)
	{
		readyToFight = null;
		trainingBanner = null;
		wasReadyToFight = false;
	}

	TrainingCharSelect::~TrainingCharSelect()
	{
		if(readyToFight!=null)
		{
			delete readyToFight;
		}
		if(trainingBanner!=null)
		{
			delete trainingBanner;
		}
	}

	void TrainingCharSelect::Initialize()
	{
		ArrayList<int> types;
		types.add(1); types.add(3);
		createCards(types);
		createCharIcons();
		resetCards(types);
		trainingBanner = new Actor(260,35);
		trainingBanner->addAnimation(new Animation("normal",1,"Images/Menus/Buttons/Solo/training_mode.png"));
		trainingBanner->changeAnimation("normal",FORWARD);
		trainingBanner->setScale(1.8f);
		
		readyToFight = new ReadyToFightBar(450, 380);
		readyToFight->addAnimation(new Animation("normal",1,"Images/Menus/Buttons/Generic/readytofight.png"));
		readyToFight->addAnimation(new Animation("hover",1,"Images/Menus/Buttons/Generic/readytofight_selected.png"));
		readyToFight->changeAnimation("normal", FORWARD);
		readyToFight->setScale(1.845f);
	}
	
	void TrainingCharSelect::LoadContent()
	{
		if(Menus::menuNo==MENU_SOLOMENU)
		{
			for(int i=0; i<Global::possPlayers; i++)
			{
				Global::selectedChar[i] = 0;
			}
			ArrayList<int> types;
			types.add(1); types.add(3);
			resetCards(types);
			selectRandomCharacter(2);
			wasReadyToFight = false;
		}
		Menus::menuNo=MENU_TRAININGCHARSELECT;
		Game::setBackgroundImage("Images/Menus/Backgrounds/bg1.png");
	}

	void TrainingCharSelect::Update(long gameTime)
	{
		trainingBanner->Update(gameTime);
		CharSelectScreen::Update(gameTime);
		if(checkReadyToFight(2) && !coinsClicked())
		{
			if(!wasReadyToFight)
			{
				wasReadyToFight = true;
				Menus::playSound("ready to fight");
			}
			readyToFight->Update(gameTime);
		}
		else
		{
			wasReadyToFight = false;
		}

	}

	void TrainingCharSelect::Draw(Graphics2D&g, long gameTime)
	{
		trainingBanner->Draw(g, gameTime);
		CharSelectScreen::Draw(g, gameTime);
		if(checkReadyToFight(2) && !coinsClicked())
		{
			readyToFight->Draw(g, gameTime);
		}
	}

	TrainingStageSelect::TrainingStageSelect(const String&name) : StageSelectScreen(name)
	{
		//
	}

	TrainingStageSelect::~TrainingStageSelect()
	{
		//
	}

	void TrainingStageSelect::LoadContent()
	{
		Menus::menuNo = MENU_TRAININGSTAGESELECT;
		Global::gameType = Global::TYPE_TRAINING;
		Global::gameMode = Global::MODE_FREEFORALL;
		Game::setBackgroundImage("Images/Menus/Backgrounds/bg1.png");
	}

	RulesMenu::RulesMenu(const String&name) : Screen(name)
	{
		//
	}

	RulesMenu::~RulesMenu()
	{
		if(button_items!=null)
		{
			delete button_items;
		}
		if(stocks!=null)
		{
			delete stocks;
		}
		if(time!=null)
		{
			delete time;
		}
		if(gameMode!=null)
		{
			delete gameMode;
		}
	}
	
	void RulesMenu::Initialize()
	{
		gameMode = new ToggleButtons(615,131,645,201);
		gameMode->setScale(1.4f);
		
		time = new MenuBarValue(300,130,"Time Limit","min");
		time->setProperties(Global::minTime, Global::maxTime, 1);
		time->setValue(Global::timeLimit);
		time->setScale(1.6f);
				
		stocks = new MenuBarValue(330,200,"Stock");
		stocks->setProperties(Global::minLives, Global::maxLives, 1);
		stocks->setValue(Global::stockAmount);
		stocks->setScale(1.6f);
				
		button_items = new MenuBarSmallButton(660,500,"Item Switch","ItemsMenu");
		button_items->setScale(1.8f);
	}
	
	void RulesMenu::LoadContent()
	{
		if(Menus::menuNo==MENU_BRAWLCHARSELECT)
		{
			Menus::menuNo=MENU_RULESMENU_BRAWLCHARSELECT;
		}
		else if(Menus::menuNo==MENU_GROUPMENU)
		{
			Menus::menuNo=MENU_RULESMENU_GROUPMENU;
		}
		else if(Menus::menuNo==MENU_P2PCHARSELECT)
		{
			Menus::menuNo=MENU_RULESMENU_P2PCHARSELECT;
		}
		else if(Menus::menuNo==MENU_ITEMMENU_BRAWLCHARSELECT)
		{
			Menus::menuNo=MENU_RULESMENU_BRAWLCHARSELECT;
		}
		else if(Menus::menuNo==MENU_ITEMMENU_GROUPMENU)
		{
			Menus::menuNo=MENU_RULESMENU_GROUPMENU;
		}
		else if(Menus::menuNo==MENU_ITEMMENU_P2PCHARSELECT)
		{
			Menus::menuNo=MENU_RULESMENU_P2PCHARSELECT;
		}
		time->setValue(Global::timeLimit);
		stocks->setValue(Global::stockAmount);
		Game::setBackgroundImage("Images/Menus/Backgrounds/bg1.png");
	}

	void RulesMenu::Update(long gameTime)
	{
		P2PDataManager::updateGame(gameTime);
		time->setValue(Global::timeLimit);
		stocks->setValue(Global::stockAmount);
		Menus::button_back->Update(gameTime);
		stocks->Update(gameTime);
		time->Update(gameTime);
		gameMode->setToggle(Global::gameMode);
		gameMode->Update(gameTime);
		button_items->Update(gameTime);
		
		int prevValue = Global::gameMode;
		byte gamemode = gameMode->getToggle();
		if(gamemode == 1)
		{
			Global::gameMode = Global::MODE_TIME_LIMIT;
		}
		else if(gamemode == 2)
		{
			Global::gameMode = Global::MODE_STOCK;
		}
		if(prevValue!=Global::gameMode)
		{
			P2PDataManager::toggleSetting("gameMode", 0);
		}
		
		prevValue = Global::stockAmount;
		Global::stockAmount = stocks->getValue();
		if(prevValue!=Global::stockAmount)
		{
			P2PDataManager::toggleSetting("stockAmount", 0);
		}
		
		prevValue = Global::timeLimit;
		Global::timeLimit = time->getValue();
		if(prevValue!=Global::timeLimit)
		{
			P2PDataManager::toggleSetting("timeLimit", 0);
		}
	}

	void RulesMenu::Draw(Graphics2D&g, long gameTime)
	{
		Menus::button_back->Draw(g, gameTime);
		stocks->Draw(g, gameTime);
		time->Draw(g, gameTime);
		gameMode->Draw(g, gameTime);
		button_items->Draw(g, gameTime);
	}
	
	boolean ItemsMenu::updatingGrid = false;
	
	ItemsMenu::ItemPane::ItemPane(ItemsMenu*menu, int id, float x1, float y1, boolean toggle) : TogglePane(x1,y1,toggle)
	{
		this->id = id;
		this->menu = menu;
	}

	ItemsMenu::ItemPane::~ItemPane()
	{
		//
	}

	void ItemsMenu::ItemPane::onToggle(boolean toggle)
	{
		if(!updatingGrid)
		{
			Global::itemsOn[id] = toggle;
			P2PDataManager::toggleSetting("item", id);
		}
	}

	ItemsMenu::ItemsMenu(const String&name) : Screen(name)
	{
		//
	}

	ItemsMenu::~ItemsMenu()
	{
		delete paneGrid;
		delete itemGrid;
	}

	void ItemsMenu::addActorsToGrid()
	{
		for(int i=0; i<30; i++)
		{
			ItemPane*pane = new ItemPane(this,i,0,0,false);
			paneGrid->add((Actor*)pane);
		}
		for(int i=1; i<=Global::totalItems; i++)
		{
			Actor*a = new Actor(0,0);
			
			String name = "";
			
			switch(i) //TODO: add items
			{
				case Global::ITEM_SMASHBALL:
				name = "Images/Menus/Rules/Items/smashball.png";
				break;
				
				case Global::ITEM_RAYGUN:
				name = "Images/Menus/Rules/Items/raygun.png";
				break;
				
				case Global::ITEM_HEARTCONTAINER:
				name = "Images/Menus/Rules/Items/heart_container.png";
				break;
				
				case Global::ITEM_BEAMSWORD:
				name = "Images/Menus/Rules/Items/beamsword.png";
				break;
				
				case Global::ITEM_SUPERMUSHROOM:
				name = "Images/Menus/Rules/Items/mushroom.png";
				break;
				
				case Global::ITEM_POISONMUSHROOM:
				name = "Images/Menus/Rules/Items/poison_mushroom.png";
				break;
			}
			
			if(!name.equals(""))
			{
				a->addAnimation(new Animation("normal", 1, name));
				a->changeAnimation("normal", FORWARD);
				((TogglePane*)paneGrid->get(i-1))->setToggle(Global::itemsOn[i-1]);
				itemGrid->add(a);
			}
			else
			{
				itemGrid->add(null);
			}
		}
	}
	
	void ItemsMenu::Initialize()
	{
		paneGrid = new ActorGrid(110,120, 5, 6);
		paneGrid->setSpacing(140, 60);
		paneGrid->setScale(1.8f);
				
		itemGrid = new ActorGrid(80,120, 5, 6);
		itemGrid->setSpacing(140, 60);
		itemGrid->setScale(1.6f);
				
		addActorsToGrid();
	}

	void ItemsMenu::LoadContent()
	{
		if(Menus::menuNo==MENU_RULESMENU_BRAWLCHARSELECT)
		{
			Menus::menuNo=MENU_ITEMMENU_BRAWLCHARSELECT;
		}
		else if(Menus::menuNo==MENU_RULESMENU_GROUPMENU)
		{
			Menus::menuNo=MENU_ITEMMENU_GROUPMENU;
		}
		else if(Menus::menuNo==MENU_RULESMENU_P2PCHARSELECT)
		{
			Menus::menuNo=MENU_ITEMMENU_P2PCHARSELECT;
		}
		Game::setBackgroundImage("Images/Menus/Backgrounds/bg2.png");
		for(int i=0; i<Global::totalItems; i++)
		{
			((TogglePane*)paneGrid->get(i))->setToggle(Global::itemsOn[i]);
		}
	}
	
	void ItemsMenu::UnloadContent()
	{
		Preferences::save();
	}

	void ItemsMenu::Update(long gameTime)
	{
		P2PDataManager::updateGame(gameTime);
		updatingGrid = true;
		for(int i=0; i<Global::totalItems; i++)
		{
			((TogglePane*)paneGrid->get(i))->setToggle(Global::itemsOn[i]);
		}
		updatingGrid = false;
		Menus::button_back->Update(gameTime);
		paneGrid->Update(gameTime);
		itemGrid->Update(gameTime);
		switch((paneGrid->getHoveredIndex()+1)) //TODO: add items
		{
			default:
			Menus::description->setText("");
			break;
			case Global::ITEM_SMASHBALL:
			Menus::description->setText("Smash Ball - Allows you to use your Final Smash");
			break;
			case Global::ITEM_RAYGUN:
			Menus::description->setText("Ray Gun - Fires a laser bullet at your opponent");
			break;
			case Global::ITEM_HEARTCONTAINER:
			Menus::description->setText("Heart Container - Replenishes 100% damage");
			break;
			case Global::ITEM_BEAMSWORD:
			Menus::description->setText("Beam Sword - Saber of pure energy. Hits hard!");
			break;
			case Global::ITEM_SUPERMUSHROOM:
			Menus::description->setText("Super Mushroom - Makes you become giant-sized");
			break;
			case Global::ITEM_POISONMUSHROOM:
			Menus::description->setText("Poison Mushroom - Shrinks your characters to mini-size.");
			break;
		}
		Menus::description->Update(gameTime);
	}

	void ItemsMenu::Draw(Graphics2D&g, long gameTime)
	{
		Menus::button_back->Draw(g, gameTime);
		paneGrid->Draw(g, gameTime);
		itemGrid->Draw(g, gameTime);
		Menus::description->Draw(g, gameTime);
	}
	
	BluetoothMenu::PeerCard::PeerCard(const String&name, const String&id)
	{
		x = 0;
		y = 0;
		displayName = name;
		peerID = id;
		device = "";
		card = new Actor(x,y);
		card->setScale(0.5f);
		card->addAnimation(new Animation("empty", 1, "Images/Menus/Buttons/Bluetooth/no_peer.png"));
		card->addAnimation(new Animation("iPod Touch", 1, "Images/Menus/Buttons/Bluetooth/iPod_Touch.png"));
		card->addAnimation(new Animation("iPhone", 1, "Images/Menus/Buttons/Bluetooth/iPhone.png"));
		card->changeAnimation("empty", FORWARD);
		textDisplay = new TextActor("Click to connect", AssetManager::getFont("Fonts/arial.ttf", Font::PLAIN, 18), Color::BLACK);
		textDisplay->x = x;
		textDisplay->y = y+190;
		textDisplay->setAlignment(TextActor::ALIGN_CENTER);
	}
	
	BluetoothMenu::PeerCard::~PeerCard()
	{
		delete card;
		delete textDisplay;
	}
	
	void BluetoothMenu::PeerCard::Update(long gameTime)
	{
		card->x = x;
		card->y = y;
		textDisplay->x = x;
		textDisplay->y = y + 190;
		
		if(!displayName.equals(""))
		{
			String text = "";
			if(device.equals("iPod Touch") || device.equals("iPod touch"))
			{
				card->changeAnimation("iPod Touch", FORWARD);
			}
			else if(device.equals("iPhone"))
			{
				card->changeAnimation("iPhone", FORWARD);
			}
			else if(device.equals("iPhone Simulator"))
			{
				card->changeAnimation("iPhone", FORWARD);
			}
			else
			{
				card->changeAnimation("iPod Touch", FORWARD);
			}
			text += (String)"Device: " + device + '\n';
			text += (String)"Display Name: " + displayName + '\n';
			if(peerID.equals(""))
			{
				text += (String)"PeerID: NULL";
			}
			else
			{
				text += (String)"PeerID: " + peerID;
			}
			
			textDisplay->setText(text);
		}
		else
		{
			card->changeAnimation("empty", FORWARD);
			textDisplay->setText("Click to connect");
		}
		
		card->Update(gameTime);
		textDisplay->Update(gameTime);
	}
	
	void BluetoothMenu::PeerCard::Draw(Graphics2D&g, long gameTime)
	{
		card->x = x;
		card->y = y;
		textDisplay->x = x;
		textDisplay->y = y + 190;
		card->Draw(g, gameTime);
		textDisplay->Draw(g, gameTime);
	}
	
	boolean BluetoothMenu::PeerCard::isClicked()
	{
		return card->isClicked();
	}
	
	boolean BluetoothMenu::PeerCard::wasClicked()
	{
		return card->wasClicked();
	}
	
	boolean BluetoothMenu::PeerCard::mouseOver()
	{
		return card->mouseOver();
	}
	
	void BluetoothMenu::PeerCard::setDisplayName(const String&name)
	{
		displayName = name;
	}
	
	void BluetoothMenu::PeerCard::setPeerID(const String&id)
	{
		peerID = id;
	}
	
	void BluetoothMenu::PeerCard::setDevice(const String&dev)
	{
		device = dev;
	}
	
	String BluetoothMenu::PeerCard::getDisplayName()
	{
		return displayName;
	}
	
	String BluetoothMenu::PeerCard::getPeerID()
	{
		return peerID;
	}
	
	String BluetoothMenu::PeerCard::getDevice()
	{
		return device;
	}
	
	BluetoothMenu::BluetoothMenu(const String&name) : Screen(name)
	{
		selfCard = NULL;
		peerCard = NULL;
		brawl = NULL;
		wasConnected = false;
	}
	
	BluetoothMenu::~BluetoothMenu()
	{
		if(selfCard!=NULL)
		{
			delete selfCard;
			selfCard = NULL;
		}
		if(peerCard!=NULL)
		{
			delete peerCard;
			peerCard = NULL;
		}
		if(brawl!=NULL)
		{
			delete brawl;
			brawl = NULL;
		}
	}
	
	void BluetoothMenu::Initialize()
	{
		char buffer[40];
		getDeviceName(buffer);
		selfCard = new PeerCard(buffer,"");
		getDeviceModel(buffer);
		selfCard->setDevice(buffer);
		
		peerCard = new PeerCard("", "");
		
		brawl = new Actor((float)View::getScalingWidth()/2, 540);
		brawl->setScale(0.5f);
		brawl->addAnimation(new Animation("disabled", 1, "Images/Menus/Buttons/Bluetooth/Brawl_disabled.png"));
		brawl->addAnimation(new Animation("enabled", 1, "Images/Menus/Buttons/Bluetooth/Brawl.png"));
		brawl->addAnimation(new Animation("selected", 1, "Images/Menus/Buttons/Bluetooth/Brawl_selected.png"));
		brawl->changeAnimation("disabled", FORWARD);
	}
	
	void BluetoothMenu::LoadContent()
	{
		P2PDataManager::enabled = true;
		Menus::menuNo = MENU_P2PMENU;
		Game::setBackgroundImage("Images/Menus/Backgrounds/bg1.png");
		if(!P2PManager::isConnected())
		{
			for(int i=0; i<Global::possPlayers; i++)
			{
				Global::selectedChar[i] = 0;
			}
		}
	}
	
	void BluetoothMenu::UnloadContent()
	{
		//
	}
	
	void BluetoothMenu::Update(long gameTime)
	{
		if(!P2PManager::isConnected())
		{
			for(int i=0; i<Global::possPlayers; i++)
			{
				Global::selectedChar[i] = 0;
			}
		}
		
		P2PDataManager::updateGame(gameTime);
		Menus::button_back->Update(gameTime);
		selfCard->Update(gameTime);
		peerCard->Update(gameTime);
		brawl->Update(gameTime);
		if(P2PManager::isConnected())
		{
			if(brawl->wasClicked() && !brawl->isClicked())
			{
				brawl->changeAnimation("enabled", FORWARD);
				ScreenManager::GoToScreen("BrawlCharSelect");
			}
			else if(brawl->isClicked() && !brawl->wasClicked())
			{
				brawl->changeAnimation("selected", FORWARD);
			}
			else if(!brawl->isClicked())
			{
				brawl->changeAnimation("enabled", FORWARD);
			}
			if(!wasConnected)
			{
				P2PDataManager::sendInitial();
			}
			peerCard->setDevice(P2PDataManager::getPeerDevice());
			String peerID = P2PDataManager::getPeerID();
			peerCard->setPeerID(peerID);
			peerCard->setDisplayName(P2PManager::getPeerDisplayName(peerID));
			selfCard->setPeerID(P2PManager::getID());
			selfCard->setDisplayName(P2PManager::getDisplayName());
			wasConnected = true;
		}
		else
		{
			brawl->changeAnimation("disabled", FORWARD);
			if(wasConnected)
			{
				peerCard->setDevice("");
				peerCard->setDisplayName("");
				peerCard->setPeerID("");
				selfCard->setPeerID("NULL");
				wasConnected = false;
			}
			else
			{
				if(peerCard->wasClicked() && !peerCard->isClicked())
				{
					P2PDataManager::connectToPeers();
				}
			}
		}
	}
	
	void BluetoothMenu::Draw(Graphics2D&g, long gameTime)
	{
		int totalPeers = 2;
		
		float width = ((float)View::getScalingWidth())/(totalPeers+1);
		
		Menus::button_back->Draw(g, gameTime);
		
		selfCard->x = width;
		selfCard->y = 250;
		peerCard->x = width*2;
		peerCard->y = 250;
		
		selfCard->Draw(g, gameTime);
		peerCard->Draw(g, gameTime);
		brawl->Draw(g, gameTime);
	}
	
	P2PWaitScreen::P2PWaitScreen(const String&name) : Screen(name)
	{
		message = new TextActor("Waiting for peer...\n", AssetManager::getFont("Fonts/arial.ttf", Font::BOLD, 18), Color::BLACK);
		message->setAlignment(TextActor::ALIGN_TOPLEFT);
		message->x = 100;
		message->y = 100;
	}
	
	P2PWaitScreen::~P2PWaitScreen()
	{
		delete message;
	}
	
	void P2PWaitScreen::LoadContent()
	{
		Global::P2PMessage = "Waiting for peer...\n";
		Game::showBackground(false);
		Game::setBackgroundColor(Color::WHITE);
	}
	
	void P2PWaitScreen::Update(long gameTime)
	{
		message->Update(gameTime);
		
		P2PDataManager::updateGame(gameTime);
		
		if(Global::selfReadyToPlay && Global::peerReadyToPlay)
		{
			if(P2PDataManager::isServer())
			{
				P2PDataManager::serverHandleStart();
			}
		}
		
		if(Global::selfLoaded && Global::peerLoaded)
		{
			P2PDataManager::handleLoaded();
		}
	}
	
	void P2PWaitScreen::Draw(Graphics2D&g, long gameTime)
	{
		message->setText(Global::P2PMessage);
		message->Draw(g, gameTime);
	}
}
