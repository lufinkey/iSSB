
#include "HUD.h"
#include "Global.h"
#include "ItemManager.h"
#include "Camera.h"
#include "Controls.h"
#include "P2PDataManager.h"

namespace SmashBros
{
	HUD::ReadyGoActor::ReadyGoActor(float x1, float y1, HUD*hud) : Actor(x1,y1)
	{
		setRelativeToView(false);
		this->hud = hud;
	}
	
	HUD::ReadyGoActor::~ReadyGoActor()
	{
		//
	}
	
	void HUD::ReadyGoActor::onAnimationFinish(const String&n)
	{
		if(n.equals("go"))
		{
			hud->showReadyGo = false;
		}
	}
	
	HUD::HUD()
	{
		Load();
		
		showReadyGo = true;
		showFinishGame = false;
		finishGameTime = 0;
		prevWorldTime = 0;
		firstUpdate = true;
		
		if(Global::gameType == Global::TYPE_TRAINING)
		{
			trainingMenu = new TrainingMenu(this);
			pauseMenu = null;
		}
		else
		{
			pauseMenu = new PauseMenu();
			trainingMenu = null;
		}
		
		ReadyGo = new ReadyGoActor(View::getScalingWidth() * 0.5f,View::getScalingHeight() * 0.5f, this);
		ReadyGo->setRelativeToView(false);
		
		ReadyGo->addAnimation(new Animation("ready",1,"Images/Game/HUD/Ready.png"));
		ReadyGo->addAnimation(new Animation("go",1,"Images/Game/HUD/Go.png"));
		ReadyGo->addAnimation(new Animation("suddendeath", 1, "Images/Game/HUD/SuddenDeath.png"));
		if(Global::suddenDeath)
		{
			ReadyGo->changeAnimation("suddendeath", FORWARD);
		}
		else
		{
			ReadyGo->changeAnimation("ready", FORWARD);
		}
		ReadyGo->setScale(0.7f);
		
		FinishGame = new Actor(View::getScalingWidth() * 0.5f,View::getScalingHeight() * 0.5f);
		FinishGame->setRelativeToView(false);
		
		FinishGame->addAnimation(new Animation("game", 1, "Images/Game/HUD/Game.png"));
		FinishGame->changeAnimation("game", FORWARD);
		
		int counter = 0;
		for(byte i=1; i<=Global::possPlayers; i++) //TODO: loop characters
		{
			if(Global::characters[i]!=null && (!Global::suddenDeath || (Global::suddenDeath && Global::isInSuddenDeath(i))))
			{
				counter++;
				
				CharacterPanel*panel = new CharacterPanel(this,i);
				
				panel->y = (View::getScalingHeight() * 0.8f);
				if(Global::suddenDeath)
				{
					panel->x = ((float)View::getScalingWidth() / (Global::suddenDeathPlayers.size()+1))*counter;
				}
				else
				{
					panel->x = ((float)View::getScalingWidth() / (Global::charAmount+1))*counter;
				}
				
				charPanels.add(panel);
			}
		}
		
		if(Global::gameMode == Global::MODE_TIME_LIMIT)
		{
			currentTime = new TextActor((float)View::getScalingWidth()/2, 40, "0:00", AssetManager::getFont("Fonts/arial.ttf", Font::BOLD, 48), Color::WHITE);
			currentTime->setRelativeToView(false);
			currentTime->setAlignment(TextActor::ALIGN_CENTER);
		}
		else
		{
			currentTime = null;
		}
	}

	HUD::~HUD()
	{
		if(ReadyGo!=null)
		{
			delete ReadyGo;
		}
		if(FinishGame!=null)
		{
			delete FinishGame;
		}
		if(currentTime!=null)
		{
			delete currentTime;
		}
		if(trainingMenu!=null)
		{
			delete trainingMenu;
		}
		if(pauseMenu!=null)
		{
			delete pauseMenu;
		}
		for(int i=0; i<charPanels.size(); i++)
		{
			delete charPanels.get(i);
		}
		charPanels.clear();
	}
	
	void HUD::Load()
	{
		files.add("Images/Game/HUD/Ready.png");
		files.add("Images/Game/HUD/Go.png");
		files.add("Images/Game/HUD/PercentText/0.png");
		files.add("Images/Game/HUD/PercentText/1.png");
		files.add("Images/Game/HUD/PercentText/2.png");
		files.add("Images/Game/HUD/PercentText/3.png");
		files.add("Images/Game/HUD/PercentText/4.png");
		files.add("Images/Game/HUD/PercentText/5.png");
		files.add("Images/Game/HUD/PercentText/6.png");
		files.add("Images/Game/HUD/PercentText/7.png");
		files.add("Images/Game/HUD/PercentText/8.png");
		files.add("Images/Game/HUD/PercentText/9.png");
		files.add("Images/Game/HUD/PercentText/percent.png");
	}
	
	void HUD::Unload()
	{
		for(int i=0; i<files.size(); i++)
		{
			AssetManager::unloadImage(files.get(i));
		}
	}
	
	void HUD::updateTimeActor()
	{
		if((Global::getWorldTime()/100)%10==0)
		{
			int tempSeconds=(int)(Global::timeAmount%60);
			int tempMinutes=(int)(Global::timeAmount/60);
			if(tempSeconds<10)
			{
				currentTime->setText((String)tempMinutes + ":0" + tempSeconds);
			}
			else
			{
				currentTime->setText((String)tempMinutes + ":" + tempSeconds);
			}
		}
	}
	
	void HUD::Update(long gameTime)
	{
		if(firstUpdate)
		{
			startGameTime = Global::getWorldTime() + 1000;
			firstUpdate = false;
		}
		else if(startGameTime>0)
		{
			if(Global::getWorldTime() > startGameTime)
			{
				Global::gamePlaying = true;
				startGameTime = 0;
				ReadyGo->changeAnimation("go", FORWARD);
				
				if(P2PDataManager::isEnabled())
				{
					DataVoid data;
					
					byte type = P2PDataManager::DATA_READYGO;
					data.add(&type, sizeof(type));
					
					type = P2PDataManager::READYGO_GO;
					data.add(&type, sizeof(type));
					
					P2PManager::sendData(data.getData(), data.length(), P2PManager::SENDDATA_RELIABLE);
				}
			}
		}
		if(showReadyGo)
		{
			ReadyGo->Update(gameTime);
		}
		for(int i=0; i<charPanels.size(); i++)
		{
			charPanels.get(i)->Update(gameTime);
		}
		if(Global::gamePlaying)
		{
			if(prevWorldTime!=(Global::getWorldTime()/100))
			{
				if(((Global::getWorldTime()/100)%10)==0)
		        {
		            Global::timeAmount-=1;
		        }
				prevWorldTime = (Global::getWorldTime()/100);
			}
		}
		if(Global::gameMode == Global::MODE_TIME_LIMIT && Global::gamePlaying && !Global::suddenDeath)
		{
			updateTimeActor();
			if(Global::timeAmount<=0)
			{
				Global::finishGame();
				
				if(P2PDataManager::isEnabled())
				{
					P2PDataManager::sendScore(NULL, true);
				}
			}
			currentTime->Update(gameTime);
		}
		if(showFinishGame && Global::getWorldTime()>=finishGameTime)
		{
			showFinishGame = false;
			
			Global::finishBrawl();
		}
		if(trainingMenu!=null)
		{
			trainingMenu->Update(gameTime);
		}
		if(pauseMenu!=null && !P2PDataManager::isEnabled())
		{
			pauseMenu->Update(gameTime);
		}
	}
	
	void HUD::Draw(Graphics2D&g, long gameTime)
	{
		for(int i=0; i<charPanels.size(); i++)
		{
			charPanels.get(i)->Draw(g, gameTime);
		}
		if(Global::gameMode == Global::MODE_TIME_LIMIT && !Global::suddenDeath)
		{
			updateTimeActor();
			currentTime->Draw(g, gameTime);
		}
		if(showReadyGo)
		{
			ReadyGo->Draw(g, gameTime);
		}
		else if(showFinishGame)
		{
			FinishGame->Draw(g, gameTime);
		}
		Controls::Draw(g, gameTime);
		if(trainingMenu!=null)
		{
			trainingMenu->Draw(g, gameTime);
		}
		if(pauseMenu!=null && !P2PDataManager::isEnabled())
		{
			pauseMenu->Draw(g, gameTime);
		}
	}
	
	HUD::CharacterPanel*HUD::getCharPanel(byte pNum)
	{
		for(int i=0; i<charPanels.size(); i++)
		{
			if(charPanels.get(i)->playerNo == pNum)
			{
				return charPanels.get(i);
			}
		}
		return null;
	}
	
	bool HUD::isClicked()
	{
		if(trainingMenu!=NULL)
		{
			if(trainingMenu->tab->isClicked())
			{
				return true;
			}
		}
		if(pauseMenu!=NULL)
		{
			if(pauseMenu->pauseButton->isClicked())
			{
				return true;
			}
		}
		return false;
	}
	
	void HUD::showScore(byte pNum, int amount)
	{
		if(amount<=0)
		{
			CharacterPanel*panel = getCharPanel(pNum);
			panel->scoreText->setText(amount);
			panel->scoreText->setColor(Color::RED);
			panel->scoreShowing = true;
			panel->scoreTime = Global::getWorldTime() + 2000;
		}
		else if(amount>0)
		{
			CharacterPanel*panel = getCharPanel(pNum);
			panel->scoreText->setText(amount);
			panel->scoreText->setColor(Color::BLUE);
			panel->scoreShowing = true;
			panel->scoreTime = Global::getWorldTime() + 2000;
		}
	}
	
	HUD::CharacterPanel::CharacterPanel(HUD*hud, byte playerNo)
	{
		percentText = null;
		symbol = null;
		stockIcon = null;
		stockText = null;
		playerName = null;
		scoreText = null;
		
		percent = 00;
		this->playerNo = 0;
		scoreTime = 0;
		scoreShowing = false;
		
		x = 0;
		y = 0;
		
		this->playerNo = playerNo;
		
		String path = Global::getPlayerActor(playerNo)->getFolderPath();
		
		if(Global::gameMode == Global::MODE_STOCK)
		{
			stockIcon = new Actor(0,0);
			/*{
				public void Draw(Graphics2D g, long gameTime)
				{
					drawActor(g, gameTime, this.x, this.y, this.Scale, false);
				}
			};*/
			stockIcon->setRelativeToView(false);
			int exists = AssetManager::loadImage(path + "stock.png");
			
			if(exists == 1)
			{
				String image = path + "stock.png";
				hud->files.add(image);
				stockIcon->addAnimation(new Animation("normal", 1, image));
				stockIcon->changeAnimation("normal", FORWARD);
			}
			else
			{
				String image = "Images/Game/HUD/default_stock.png";
				hud->files.add(image);
				stockIcon->addAnimation(new Animation("normal", 1, image));
				stockIcon->changeAnimation("normal", FORWARD);
			}
			stockIcon->setScale(1.6f);
			
			stockText = new TextActor("", AssetManager::getFont("Fonts/arial.ttf", Font::BOLD, 18),Color::WHITE);
			/*{
				@Override
				public void Draw(Graphics2D g, long gameTime)
				{
					drawActor(g, gameTime, false);
				}
			};*/
			stockText->setRelativeToView(false);
			
			stockText->setAlignment(TextActor::ALIGN_TOPLEFT);
		}
		
		scoreText = new TextActor("+1", AssetManager::getFont("Fonts/arial.ttf", Font::BOLD, 36), Color::BLUE);
		/*{
			@Override
			public void Draw(Graphics2D g, long gameTime)
			{
				drawActor(g, gameTime, false);
			}
		};*/
		scoreText->setRelativeToView(false);
		scoreText->setAlignment(TextActor::ALIGN_CENTER);
		
		percentText = new Actor(0,0);
		/*{
			@Override
			public void Draw(Graphics2D g, long gameTime)
			{
				drawActor(g,gameTime,x,y,Scale,false);
		        width *= Scale;
		        height*= Scale;
			}
		};*/
		percentText->setRelativeToView(false);
		
		percentText->addAnimation(new Animation("0",1,"Images/Game/HUD/PercentText/0.png"));
		percentText->addAnimation(new Animation("1",1,"Images/Game/HUD/PercentText/1.png"));
		percentText->addAnimation(new Animation("2",1,"Images/Game/HUD/PercentText/2.png"));
		percentText->addAnimation(new Animation("3",1,"Images/Game/HUD/PercentText/3.png"));
		percentText->addAnimation(new Animation("4",1,"Images/Game/HUD/PercentText/4.png"));
		percentText->addAnimation(new Animation("5",1,"Images/Game/HUD/PercentText/5.png"));
		percentText->addAnimation(new Animation("6",1,"Images/Game/HUD/PercentText/6.png"));
		percentText->addAnimation(new Animation("7",1,"Images/Game/HUD/PercentText/7.png"));
		percentText->addAnimation(new Animation("8",1,"Images/Game/HUD/PercentText/8.png"));
		percentText->addAnimation(new Animation("9",1,"Images/Game/HUD/PercentText/9.png"));
		percentText->addAnimation(new Animation("%",1,"Images/Game/HUD/PercentText/percent.png"));
		percentText->setScale(0.28f);
		
		int exists = AssetManager::loadImage(path + "symbol.png");
		
		if(exists == 1)
		{
			String image = path + "symbol.png";
			hud->files.add(image);
			symbol = new Actor(0,0);
			/*{
				@Override
				public void Draw(Graphics2D g, long gameTime)
				{
					drawActor(g,gameTime,x,y,Scale,false);
			        width *= Scale;
			        height*= Scale;
				}
			};*/
			symbol->setRelativeToView(false);
			symbol->addAnimation(new Animation("normal",1,image));
			symbol->changeAnimation("normal", FORWARD);
			symbol->setAlpha(0.5f);
		}
		else
		{
			AssetManager::loadImage("Images/Game/HUD/default_symbol.png");
			hud->files.add("Images/Game/HUD/default_symbol.png");
			symbol = new Actor(0,0);
			/*{
				@Override
				public void Draw(Graphics2D g, long gameTime)
				{
					drawActor(g,gameTime,x,y,Scale,false);
			        width *= Scale;
			        height*= Scale;
				}
			};*/
			symbol->setRelativeToView(false);
			symbol->addAnimation(new Animation("normal",1,"Images/Game/HUD/default_symbol.png"));
			symbol->changeAnimation("normal", FORWARD);
			symbol->setAlpha(0.5f);
		}
		
		byte team = Global::getPlayerActor(playerNo)->getTeam();
		
		if(team==0)
		{
			team = (byte)playerNo;
		}
		
		switch(team)
		{
			default:
			symbol->setColor(Color::GRAY);
			break;
			
			case 1:
			symbol->setColor(Color::RED);
			break;
			
			case 2:
			symbol->setColor(Color::BLUE);
			break;
			
			case 3:
			symbol->setColor(Color::YELLOW);
			break;
			
			case 4:
			symbol->setColor(Color::GREEN);
			break;
		}
		
		playerName = new TextActor(Global::getPlayerActor(playerNo)->getName(),AssetManager::getFont("Fonts/arial.ttf", Font::BOLD, 18),Color::WHITE);
		/*{
			@Override
			public void Draw(Graphics2D g, long gameTime)
			{
				drawActor(g,gameTime,false);
			}
		};*/
		playerName->setRelativeToView(false);
		playerName->setAlignment(TextActor::ALIGN_CENTER);
	}

	HUD::CharacterPanel::~CharacterPanel()
	{
		if(percentText!=null)
		{
			delete percentText;
		}
		if(symbol!=null)
		{
			delete symbol;
		}
		if(stockIcon!=null)
		{
			delete stockIcon;
		}
		if(stockText!=null)
		{
			delete stockText;
		}
		if(playerName!=null)
		{
			delete playerName;
		}
		if(scoreText!=null)
		{
			delete scoreText;
		}
	}
	
	void HUD::CharacterPanel::Update(long gameTime)
	{
		percent = Global::characters[playerNo]->getPercent();
		if(Global::getWorldTime()>=scoreTime)
		{
			scoreShowing = false;
		}
		
		if(percent<=510)
	    {
	        byte newColor=(510-(percent))/2;
	        byte r = percentText->getColor().r;
	        byte g=newColor;
	        byte b=newColor;
	        percentText->setColor(Color(r,g,b));
	    }
	    else if(percent<820)
	    {
	        byte newColor=(310-(percent-510))/2;
	        byte r=newColor;
	        byte g=0;
	        byte b=0;
	        percentText->setColor(Color(r,g,b));
	    }
	    else
	    {
	        byte r=100;
	        byte g=0;
	        byte b=0;
	        percentText->setColor(Color(r,g,b));
	    }
	}
	
	void HUD::CharacterPanel::Draw(Graphics2D&g, long gameTime)
	{
		percent = Global::characters[playerNo]->getPercent();
		
		if(percent<=510)
	    {
	        byte newColor=(510-(percent))/2;
	        byte r = percentText->getColor().r;
	        byte g=newColor;
	        byte b=newColor;
	        percentText->setColor(Color(r,g,b));
	    }
	    else if(percent<820)
	    {
	        byte newColor=(310-(percent-510))/2;
	        byte r=newColor;
	        byte g=0;
	        byte b=0;
	        percentText->setColor(Color(r,g,b));
	    }
	    else
	    {
	        byte r=100;
	        byte g=0;
	        byte b=0;
	        percentText->setColor(Color(r,g,b));
	    }
		
		symbol->x = x + 30;
		symbol->y = y + 15;
		symbol->Draw(g, gameTime);
		String percentString = "";
		if(percent<10)
		{
			percentString = (String)"0" + percent + "%";
		}
		else
		{
			percentString = (String)percent + "%";
		}
		float currentX = 50;
		percentText->y = y + 10;
		for(int i=(percentString.length()-1); i>=0; i--)
		{
			percentText->changeAnimation((String)"" + percentString.charAt(i), FORWARD);
			percentText->x = x + currentX;
			percentText->Draw(g, gameTime);
			currentX -=42;
		}
		
		playerName->x = x;
		playerName->y = y + 50;
		playerName->Draw(g, gameTime);
		if(stockIcon!=null)
		{
			stockIcon->x = x - 22;
			stockIcon->y = y - 28;
			stockIcon->Draw(g, gameTime);
			
			stockText->x = x;
			stockText->y = y - 40;
			stockText->setText((String)"x " + Global::characters[playerNo]->stock);
			stockText->Draw(g, gameTime);
		}
		
		if(scoreShowing)
		{
			scoreText->x = x - 30;
			scoreText->y = y - 30;
			scoreText->Draw(g, gameTime);
		}
	}
	
	HUD::TrainingMenu::TrainingMenu(HUD*hud)
	{
		bg = new Actor(0,0);
		bg->setScale(1.9f);
		bg->addAnimation(new Animation("normal",1,"Images/Game/HUD/Training/bg.png"));
		bg->changeAnimation("normal", FORWARD);
		bg->setVisible(false);
		bg->setRelativeToView(false);
		
		bg->x = (float)bg->width/2;
		bg->y = (float)bg->height/2;
		
		tab = new Actor(0,0);
		tab->addAnimation(new Animation("closed",1,"Images/Game/HUD/Training/button_open.png"));
		tab->addAnimation(new Animation("opened",1,"Images/Game/HUD/Training/button_close.png"));
		tab->changeAnimation("closed", FORWARD);
		tab->setRelativeToView(false);
		
		tab->x = (float)tab->width/2;
		tab->y = 100;
		
		apply = new Actor(100,450);
		apply->addAnimation(new Animation("normal",1,"Images/Game/HUD/Training/button_apply.png"));
		apply->changeAnimation("normal", FORWARD);
		apply->setRelativeToView(false);
		apply->setVisible(false);
		apply->setScale(1.2f);
		
		finish = new Actor(100,500);
		finish->addAnimation(new Animation("normal",1,"Images/Game/HUD/Training/button_finish.png"));
		finish->changeAnimation("normal", FORWARD);
		finish->setRelativeToView(false);
		finish->setVisible(false);
		finish->setScale(1.2f);
		
		//options = new ArrayList<OptionPanel*>();
		
		OptionPanel*optionPanel = new OptionPanel(100,100,"Images/Game/HUD/Training/panel_items.png");
		optionPanel->setMin(0);
		optionPanel->setMax(Global::totalItems);
		optionPanel->setValue(0);
		optionPanel->setScale(1.4f);
		options.add(optionPanel);
		
		optionPanel = new OptionPanel(100,180,"Images/Game/HUD/Training/panel_cpu.png");
		optionPanel->setMin(1);
		optionPanel->setMax(6);
		optionPanel->setValue(1);
		optionPanel->setScale(1.4f);
		options.add(optionPanel);
		
		optionPanel = new OptionPanel(100,260,"Images/Game/HUD/Training/panel_camera.png");
		optionPanel->setMin(0);
		optionPanel->setMax(2);
		optionPanel->setValue(2);
		optionPanel->setScale(1.4f);
		options.add(optionPanel);
		
		opened = false;
	}

	HUD::TrainingMenu::~TrainingMenu()
	{
		if(bg!=null)
		{
			delete bg;
		}
		if(tab!=null)
		{
			delete tab;
		}
		for(int i=0; i<options.size(); i++)
		{
			delete options.get(i);
		}
		options.clear();
		if(apply!=null)
		{
			delete apply;
		}
		if(finish!=null)
		{
			delete finish;
		}
	}
	
	void HUD::TrainingMenu::Update(long gameTime)
	{
		bg->Update(gameTime);
		tab->Update(gameTime);
		apply->Update(gameTime);
		finish->Update(gameTime);
		
		if(opened)
		{
			tab->x = (float)bg->width + (float)tab->width/2;
			tab->y = 100;
			tab->changeAnimation("opened", FORWARD);
			bg->setVisible(true);
			bg->x = (float)bg->width/2;
			bg->y = (float)bg->height/2;
			apply->setVisible(true);
			finish->setVisible(true);
			
			if(apply->wasClicked() && !apply->isClicked())
			{
				applyChanges();
				opened = false;
				onClose();
			}
			if(apply->mouseOver())
			{
				apply->setColor(Color::RED);
			}
			else
			{
				apply->setColor(Color::WHITE);
			}
			applyLabels(gameTime);
			
			if(finish->wasClicked() && !finish->isClicked())
			{
				Global::finishGameSoloTraining();
				Controls::enableTouchControls(true);
				return;
			}
			if(finish->mouseOver())
			{
				finish->setColor(Color::RED);
			}
			else
			{
				finish->setColor(Color::WHITE);
			}
		}
		else
		{
			tab->x = (float)tab->width/2;
			tab->y = 100;
			tab->changeAnimation("closed", FORWARD);
			bg->setVisible(false);
			apply->setVisible(false);
			finish->setVisible(false);
		}
		
		if(!Controls::controlsDown())
		{
			if(tab->mouseOver())
			{
				tab->setColor(Color::RED);
			}
			else
			{
				tab->setColor(Color::WHITE);
			}
		}
		if(!Controls::controlsDown() && tab->wasClicked() && !tab->isClicked())
		{
			if(opened)
			{
				opened = false;
				onClose();
			}
			else if(!Controls::controlsDown())
			{
				opened = true;
				onOpen();
			}
		}
	}
	
	void HUD::TrainingMenu::Draw(Graphics2D&g, long gameTime)
	{
		bg->Draw(g, gameTime);
		tab->Draw(g, gameTime);
		apply->Draw(g, gameTime);
		finish->Draw(g, gameTime);
		if(opened)
		{
			for(int i=0; i<options.size(); i++)
			{
				options.get(i)->Draw(g, gameTime);
			}
		}
	}
	
	void HUD::TrainingMenu::applyLabels(long gameTime)
	{
		for(int i=0; i<options.size(); i++)
		{
			OptionPanel*option = options.get(i);
			option->Update(gameTime);
			switch(i)
			{
				case OPTION_ITEMS: //item options
				if(option->getValue()==0)
				{
					option->setLabel("none");
				}
				else
				{
					option->setLabel(Global::getItemName(option->getValue()));
				}
				break;
				
				case OPTION_CPU: //AI options
				switch(option->getValue())
				{
					case Player::AI_STOP:
					option->setLabel("Stop");
					break;
					
					case Player::AI_WALK:
					option->setLabel("Walk");
					break;
					
					case Player::AI_RUN:
					option->setLabel("Run");
					break;
					
					case Player::AI_JUMP:
					option->setLabel("Jump");
					break;
					
					case Player::AI_NORMAL:
					option->setLabel("Attack");
					break;
					
					case Player::AI_FOLLOW:
					option->setLabel("Follow");
					break;
				}
				break;
				
				case OPTION_CAMERA: //camera options
				switch(option->getValue())
				{
					case Camera::MODE_ZOOM:
					option->setLabel("Zoom");
					break;
					
					case Camera::MODE_FOLLOW:
					option->setLabel("Follow");
					break;
					
					case Camera::MODE_FIXED:
					option->setLabel("Fixed");
					break;
				}
				break;
			}
		}
	}
	
	void HUD::TrainingMenu::applyChanges()
	{
		for(int i=0; i<options.size(); i++)
		{
			OptionPanel*option = options.get(i);
			switch(i)
			{
				case OPTION_ITEMS: //item options
				if(option->getValue()!=0)
				{
					ItemManager::SpawnItem(option->getValue());
				}
				break;
				
				case OPTION_CPU: //AI options
				if(Global::characters[2]!=null)
				{
					Global::characters[2]->aiType = (byte)option->getValue();
				}
				break;
				
				case OPTION_CAMERA: //camera options
				Camera::setMode((byte)option->getValue());
				break;
			}
		}
	}
	
	void HUD::TrainingMenu::onOpen()
	{
		Controls::enableTouchControls(false);
		for(int i=0; i<options.size(); i++)
		{
			OptionPanel*option = options.get(i);
			switch(i)
			{
				case OPTION_CPU:
				if(Global::characters[2]!=null)
				{
					option->setValue(Global::characters[2]->aiType);
				}
				else
				{
					option->setValue(Player::AI_STOP);
				}
				break;
			}
		}
	}
	
	void HUD::TrainingMenu::onClose()
	{
		Controls::enableTouchControls(true);
		for(int i=0; i<options.size(); i++)
		{
			OptionPanel*option = options.get(i);
			switch(i)
			{
				case OPTION_ITEMS:
				option->setValue(0);
				break;
			}
		}
	}
	
	HUD::OptionPanel::OptionPanel(float x1, float y1, String anim) : Actor(x1,y1)
	{
		min = 0;
		max = 0;
		value = 0;
		label = new TextActor("",AssetManager::getFont("Fonts/arial.ttf", Font::BOLD, textSize),Color::BLACK);
		label->setAlignment(TextActor::ALIGN_CENTER);
		label->setRelativeToView(false);
		
		setRelativeToView(false);
		
		addAnimation(new Animation("normal",1,anim));
		changeAnimation("normal",FORWARD);
			
		left = new Actor(0,0);
		left->addAnimation(new Animation("normal",1,"Images/Game/HUD/Training/arrow.png"));
		left->changeAnimation("normal", FORWARD);
		left->setRelativeToView(false);
		left->setAlpha(0.6f);
		right = new Actor(0,0);
		Animation*a = new Animation("normal",1,"Images/Game/HUD/Training/arrow.png");
		a->mirror(true);
		right->addAnimation(a);
		right->changeAnimation("normal", FORWARD);
		right->setRelativeToView(false);
		right->setAlpha(0.6f);
	}

	HUD::OptionPanel::~OptionPanel()
	{
		if(left!=null)
		{
			delete left;
		}
		if(right!=null)
		{
			delete right;
		}
		if(label!=null)
		{
			delete label;
		}
	}
	
	void HUD::OptionPanel::Update(long gameTime)
	{
		Actor::Update(gameTime);
		left->setScale(getScale());
		left->x = x-((float)arrowXOffset*getScale());
		left->y = y;
		right->setScale(getScale());
		right->x = x+((float)arrowXOffset*getScale());
		right->y = y;
		left->Update(gameTime);
		right->Update(gameTime);
		label->setSize((unsigned int)((float)textSize*getScale()));
		label->x = x;
		label->y = y + ((float)labelYOffset*getScale());
		label->Update(gameTime);
		
		if(left->wasClicked() && !left->isClicked())
		{
			value--;
			if(value < min)
			{
				value = max;
			}
		}
		else if(right->wasClicked() && !right->isClicked())
		{
			value++;
			if(value > max)
			{
				value = min;
			}
		}
		if(left->mouseOver())
		{
			left->setColor(Color::RED);
		}
		else
		{
			left->setColor(Color::WHITE);
		}
		if(right->mouseOver())
		{
			right->setColor(Color::RED);
		}
		else
		{
			right->setColor(Color::WHITE);
		}
	}
		
	void HUD::OptionPanel::Draw(Graphics2D&g, long gameTime)
	{
		Actor::Draw(g, gameTime);
		left->Draw(g, gameTime);
		right->Draw(g, gameTime);
		label->Draw(g, gameTime);
	}
	
	void HUD::OptionPanel::setMin(int min)
	{
		this->min = min;
	}
	
	void HUD::OptionPanel::setMax(int max)
	{
		this->max = max;
	}
		
	void HUD::OptionPanel::setValue(int value)
	{
		this->value = value;
	}
		
	void HUD::OptionPanel::setLabel(String label)
	{
		this->label->setText(label);
	}
		
	int HUD::OptionPanel::getValue()
	{
		return value;
	}
	
	HUD::PauseMenu::PauseMenu()
	{
		pauseButton = new Actor(110,60);
		pauseButton->addAnimation(new Animation("normal", 1, "Images/Game/Controls/button_start.png"));
		pauseButton->changeAnimation("normal", FORWARD);
		pauseButton->setRelativeToView(false);
		pauseButton->setAlpha(0.2f);
		pauseButton->setScale(2.0f);
		
		resumeButton = new Actor(220,160);
		resumeButton->addAnimation(new Animation("normal", 1, "Images/Game/HUD/ResumeButton.png"));
		resumeButton->changeAnimation("normal", FORWARD);
		resumeButton->setRelativeToView(false);
		resumeButton->setAlpha(0.2f);
		resumeButton->setScale(1.6f);
		
		finishButton = new Actor((float)View::getScalingWidth()/2, (float)View::getScalingHeight()/2);
		finishButton->addAnimation(new Animation("normal", 1, "Images/Game/HUD/FinishButton.png"));
		finishButton->changeAnimation("normal", FORWARD);
		finishButton->setRelativeToView(false);
		finishButton->setAlpha(0.2f);
		finishButton->setScale(1.6f);
		
		exitButton = new Actor(680, 440);
		exitButton->addAnimation(new Animation("normal", 1, "Images/Game/HUD/ExitButton.png"));
		exitButton->changeAnimation("normal", FORWARD);
		exitButton->setRelativeToView(false);
		exitButton->setAlpha(0.2f);
		exitButton->setScale(1.6f);
	}
	
	HUD::PauseMenu::~PauseMenu()
	{
		delete pauseButton;
		delete resumeButton;
		delete finishButton;
		delete exitButton;
	}
	
	void HUD::PauseMenu::Update(long gameTime)
	{
		pauseButton->Update(gameTime);
		if(!Controls::controlsDown())
		{
			if(pauseButton->isClicked() && !pauseButton->wasClicked())
			{
				pauseButton->setColor(Color::BLUE);
			}
			else if(!pauseButton->isClicked() && pauseButton->wasClicked())
			{
				pauseButton->setColor(Color::WHITE);
				Game::Suspend();
			}
		}
	}
	
	void HUD::PauseMenu::Draw(Graphics2D&g, long gameTime)
	{
		if(Game::Suspended())
		{
			resumeButton->Update(gameTime);
			if(resumeButton->isClicked() && !resumeButton->wasClicked())
			{
				resumeButton->setColor(Color::BLUE);
			}
			if(!resumeButton->isClicked() && resumeButton->wasClicked())
			{
				resumeButton->setColor(Color::WHITE);
				Game::Resume();
			}
			resumeButton->Draw(g, gameTime);
			
			finishButton->Update(gameTime);
			if(finishButton->isClicked() && !finishButton->wasClicked())
			{
				finishButton->setColor(Color::BLUE);
			}
			if(!finishButton->isClicked() && finishButton->wasClicked())
			{
				finishButton->setColor(Color::WHITE);
				Game::Resume();
				Global::UnloadGame();
				if(Global::gameType == Global::TYPE_TRAINING)
				{
					ScreenManager::GoToScreen("TrainingCharSelect");
				}
				else if(Global::gameType == Global::TYPE_GROUPBRAWL)
				{
					ScreenManager::GoToScreen("BrawlCharSelect");
				}
			}
			finishButton->Draw(g, gameTime);
			
			exitButton->Update(gameTime);
			if(exitButton->isClicked() && !exitButton->wasClicked())
			{
				exitButton->setColor(Color::BLUE);
			}
			if(!exitButton->isClicked() && exitButton->wasClicked())
			{
				exitButton->setColor(Color::WHITE);
				Game::Resume();
				Game::Exit();
			}
			exitButton->Draw(g, gameTime);
		}
		else
		{
			pauseButton->Draw(g, gameTime);
		}
	}
}
