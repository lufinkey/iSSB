
#include "CharSelectScreen.h"
#include "../Global.h"
#include "Menus.h"
#include "../Loader.h"

namespace SmashBros
{
	void CharSelectScreen::createCharIcons()
	{
		for(int i=1; i<=Global::totalCharacters; i++)
		{
			newCharIcon(i, CharacterLoader::getIconPath(i));
		}
	}

	void CharSelectScreen::loadCharPreviews(int num)
	{
		Actor*a = charPreviews.get(num-1);
		for(int i=1; i<=Global::totalCharacters; i++)
		{
			a->addAnimation(new Animation(CharacterLoader::getName(i),1, CharacterLoader::getPreviewPath(i)));
		}
		a->changeAnimation(CharacterLoader::getName(Global::CHAR_MARIO),FORWARD);
		a->Scale = 2.0f;
		a->setAlpha(1);
	}

	CharSelectScreen::CharSelectScreen(const String&name) : Screen(name)
	{
		canGrabCoin = false;
		selectedCoin = 0;
		cardTypes = null;
		charSelectArea = null;
		coinPoints = null;
		cardAvailable = null;
	}

	CharSelectScreen::~CharSelectScreen()
	{
		for(int i=0; i<charCards.size(); i++)
		{
			delete charCards.get(i);
		}
		charCards.clear();

		for(int i=0; i<charIcons.size(); i++)
		{
			delete charIcons.get(i);
		}
		charIcons.clear();

		for(int i=0; i<charIconPoints.size(); i++)
		{
			delete charIconPoints.get(i);
		}
		charIconPoints.clear();

		for(int i=0; i<charCoins.size(); i++)
		{
			delete charCoins.get(i);
		}
		charCoins.clear();

		for(int i=0; i<charPreviews.size(); i++)
		{
			delete charPreviews.get(i);
		}
		charPreviews.clear();

		for(int i=0; i<charNames.size(); i++)
		{
			delete charNames.get(i);
		}
		charNames.clear();

		if(charSelectArea!=null)
		{
			delete charSelectArea;
		}
		if(coinPoints!=null)
		{
			delete[] coinPoints;
		}
		if(cardTypes!=null)
		{
			delete[] cardTypes;
		}
		if(cardAvailable!=null)
		{
			delete[] cardAvailable;
		}
	}

	void CharSelectScreen::Initialize()
	{
		ArrayList<int> types;
		for(int i=1; i<=4; i++)
		{
			types.add(0);
		}
		createCards(types);
		createCharIcons();
		resetCards(types);
	}

	void CharSelectScreen::LoadContent()
	{
		//Menus::menuNo=3;
		Game::setBackgroundImage("Images/Menus/Backgrounds/bg1.png");
	}

	void CharSelectScreen::UnloadContent()
	{
		//
	}

	void CharSelectScreen::Update(long gameTime)
	{
		if(Global::gameFinished)
		{
			Global::gameFinished = false;
			Global::onReturnToMenu();
			Menus::playSong("Menu Theme");
		}
		charSelectArea->Update(gameTime);
		for(int i=0; i<charCards.size(); i++)
		{
			charCards.get(i)->Update(gameTime);
			setCardAnimation(i+1);
		}
		for(int i=0; i<charIcons.size(); i++)
		{
			charIcons.get(i)->Update(gameTime);
		}
		int skip = selectedCoin-1;
		canGrabCoin=true;
		if(selectedCoin>0)
		{
			charCoins.get(selectedCoin-1)->Update(gameTime);
			if(charCoins.get(selectedCoin-1)->isClicked())
			{
				canGrabCoin = false;
			}
			else
			{
				selectedCoin = 0;
			}
		}
		for(int i=0; i<charCoins.size(); i++)
		{
			if(i!=skip && !coinHidden(i))
			{
				charCoins.get(i)->Update(gameTime);
				if(charCoins.get(i)->isClicked())
				{
					canGrabCoin = false;
					selectedCoin = i+1;
				}
			}
		}
		for(int i=0; i<charCoins.size(); i++)
		{
			if(!coinHidden(i))
			{
				for(int j=0; j<charIconPoints.size(); j++)
				{
					if(charCoins.get(i)->rectsColliding(charIconPoints.get(j)))
					{
						int selected=charIcons.get(j)->num;
						if(selected != Global::selectedChar[i])
						{
							onSelectCharacter(i+1, selected);
						}
						Global::selectedChar[i]=selected;
						j=charIconPoints.size();
					}
				}
				if(!charCoins.get(i)->rectsColliding(charSelectArea))
				{
					if(Global::selectedChar[i]!=0)
					{
						onSelectCharacter(i+1, 0);
					}
					Global::selectedChar[i]=0;
				}
				if(charCoins.get(i)->isClicked() && !charCoins.get(i)->wasClicked() && !cardAvailable[i])
				{
					switch(cardTypes[i])
					{
						default:
						cardAvailable[i] = true;
						Global::CPU[i] = false;
						break;
						
						case 2:
						case 3:
						cardAvailable[i] = true;
						Global::CPU[i] = true;
						break;
					}
				}
				else if(!charCoins.get(i)->isClicked() && charCoins.get(i)->wasClicked() && Global::selectedChar[i]==0)
				{
					cardAvailable[i] = false;
					Global::CPU[i] = false;
				}
			}
		}
		for(int i=0; i<charPreviews.size(); i++)
		{
			int cNum = Global::selectedChar[i];
			if(cNum == 0)
			{
				charPreviews.get(i)->setAlpha(1);
			}
			else
			{
				charPreviews.get(i)->setAlpha(0);
				charPreviews.get(i)->changeAnimation(CharacterLoader::getName(cNum), NO_CHANGE);
			}
			charPreviews.get(i)->Update(gameTime);
			charNames.get(i)->Update(gameTime);
			charNames.get(i)->setText(CharacterLoader::getName(cNum));
		}
		Menus::button_back->Update(gameTime);
	}

	void CharSelectScreen::Draw(Graphics2D&g, long gameTime)
	{
		Menus::button_back->Draw(g, gameTime);
		charSelectArea->Draw(g,gameTime);
		for(int i=0; i<charCards.size(); i++)
		{
			charCards.get(i)->Draw(g, gameTime);
		}
		for(int i=0; i<charIcons.size(); i++)
		{
			charIcons.get(i)->Draw(g, gameTime);
		}
		for(int i=0; i<charIconPoints.size(); i++)
		{
			charIconPoints.get(i)->Draw(g, gameTime);
		}
		for(int i=0; i<charPreviews.size(); i++)
		{
			charPreviews.get(i)->Draw(g, gameTime);
		}
		for(int i=0; i<charNames.size(); i++)
		{
			charNames.get(i)->Draw(g, gameTime);
		}
		for(int i=(charCoins.size()-1); i>=0; i--)
		{
			if(!coinHidden(i))
			{
				charCoins.get(i)->Draw(g, gameTime);
			}
		}
	}
	
	void CharSelectScreen::onSelectCharacter(int player, int character)
	{
		//Open for implementation
	}
	
	void CharSelectScreen::selectCharacter(int player, int character)
	{
		Global::selectedChar[player-1]=character;
		if(character!=0)
		{
			CharCoin*charCoin = charCoins.get(player-1);
			charCoin->x = charIcons.get(character-1)->x;
			charCoin->y = charIcons.get(character-1)->y;
		}
	}
	
	void CharSelectScreen::selectRandomCharacter(int player)
	{
		int select = (int)(GameEngine::random()*charIcons.size());
		int index = player-1;
		CharCoin*charCoin = charCoins.get(index);
		charCoin->x = charIcons.get(select)->x;
		charCoin->y = charIcons.get(select)->y;
	}

	boolean CharSelectScreen::checkReadyToFight(int minPlayers)
	{
		if(Global::teamBattle)
		{
			ArrayList<int> selected;
			for(int i=0; i<Global::possPlayers; i++)
			{
				if(Global::selectedChar[i]>0)
				{
					selected.add(i+1);
				}
			}
			if(selected.size()>=minPlayers)
			{
				ArrayList<int> teamTotals;
				for(int i=0; i<=Global::possTeams; i++)
				{
					teamTotals.add(0);
				}
				
				for(int i=0; i<selected.size(); i++)
				{
					int index = Global::currentTeams[selected.get(i)];
					teamTotals.set(index, teamTotals.get(index)+1);
				}
				
				int activeTeams = 0;
				
				for(int i=0; i<teamTotals.size(); i++)
				{
					if(teamTotals.get(i)>0)
					{
						activeTeams++;
						if(activeTeams>1)
						{
							return true;
						}
					}
				}
				
				if(activeTeams>1)
				{
					return true;
				}
				return false;
			}
			return false;
		}
		else
		{
			int total = 0;
			for(int i=0; i<Global::possPlayers; i++)
			{
				if(Global::selectedChar[i]>0)
				{
					total++;
				}
			}
			if(total>=minPlayers)
			{
				return true;
			}
		}
		return false;
	}

	boolean CharSelectScreen::coinsClicked()
	{
		for(int i=0; i<charCoins.size(); i++)
		{
			if(charCoins.get(i)->isClicked())
			{
				return true;
			}
		}
		return false;
	}

	void CharSelectScreen::createCards(ArrayList<int> type)
	{
		int total = type.size();

		if(charSelectArea!=null)
		{
			delete charSelectArea;
			charSelectArea = null;
		}
		if(coinPoints!=null)
		{
			delete[] coinPoints;
			coinPoints = null;
		}
		if(cardTypes!=null)
		{
			delete[] cardTypes;
			cardTypes = null;
		}
		if(cardAvailable!=null)
		{
			delete[] cardAvailable;
			cardAvailable = null;
		}
		
		for(int i=0; i<charCards.size(); i++)
		{
			delete charCards.get(i);
			delete charPreviews.get(i);
			delete charNames.get(i);
		}
		charCards.clear();
		charPreviews.clear();
		charNames.clear();
		
		cardAvailable = new boolean[type.size()];
		cardTypes = new byte[type.size()];
		coinPoints = new Vector2i[type.size()];
		charSelectArea = new WireframeActor();
		//CharSelectArea->setVisible(true);
		int space = View::ScaleWidth()/(total);
		for(int i=1; i<=total; i++)
		{
			Global::CPU[i-1]=false;
			cardAvailable[i-1]=false;
			cardTypes[i-1] = (byte)type.get(i-1);
			Actor*a = setUpCard(i,type.get(i-1));
			a->Scale = 1.65f;
			Actor*a2 = new Actor(0,0);
			TextActor*a3 = new TextActor(" ", AssetManager::getFont("Fonts/arial.ttf", Font::BOLD, 12), Color::WHITE);
			a3->setAlignment(TextActor::ALIGN_CENTER);
			addToGrid(a,100+(space/10),500,type.size(),1,space,0,i);
			a2->x = a->x;
			a2->y = a->y - 10;
			a3->x = a->x - 5;
			a3->y = a->y + 43;
			charCards.add(a);
			charPreviews.add(a2);
			charNames.add(a3);
			addCardAnimations(i);
			loadCharPreviews(i);
		}
		createCharCoins(total);
	}

	void CharSelectScreen::createCharCoins(int num)
	{
		for(int i=1; i<=num; i++)
		{
			CharCoin*a = new CharCoin(this,i);
			int space = View::ScaleWidth()/(num);
			addToGrid(a,25+(space/10),500,num,1,space,0,i);
			coinPoints[i-1].x=(int)a->x;
			coinPoints[i-1].y=(int)a->y;
			a->Scale = 1.4f;
			charCoins.add(a);
		}
	}

	void CharSelectScreen::newCharIcon(int num, String anim)
	{
		CharIcon*a = new CharIcon(num, 0,0, new Animation("normal",1,anim));
		addToGrid(a,70,115,9,5,95,65,charIcons.size()+1);
		if(charIcons.size()==0)
		{
			charSelectArea->x = a->x - (a->width/2);
			charSelectArea->y = a->y - (a->height/2);
		}
		float csW = (a->x + (a->width/2)) - charSelectArea->x;
		float csH = (a->y + (a->height/2)) - charSelectArea->y;
		if(csW>charSelectArea->width)
		{
			charSelectArea->width = csW;
		}
		if(csH>charSelectArea->height)
		{
			charSelectArea->height = csH;
		}
		WireframeActor*a2 = new WireframeActor(a->x-20,a->y-20,40,40);
		charIconPoints.add(a2);
		charIcons.add(a);
	}
	
	void CharSelectScreen::setCardState(int card, bool cardOn, bool cpu)
	{
		cardAvailable[card] = cardOn;
		Global::CPU[card] = cpu;
	}

	void CharSelectScreen::clickCharCard(int num)
	{
		if(!cardAvailable[num-1])
		{
			cardAvailable[num-1]=true;
		}
		else if(!Global::CPU[num-1])
		{
			Global::CPU[num-1]=true;
		}
		else
		{
			Global::CPU[num-1]=false;
			cardAvailable[num-1]=false;
			charCoins.get(num-1)->moveTo((float)coinPoints[num-1].x, (float)coinPoints[num-1].y, 45);
		}
	}

	void CharSelectScreen::clickCharCardFirstCPU(int num)
	{
		if(!cardAvailable[num-1])
		{
			cardAvailable[num-1]=true;
			Global::CPU[num-1]=true;
		}
		else if(Global::CPU[num-1])
		{
			Global::CPU[num-1]=false;
		}
		else
		{
			Global::CPU[num-1]=false;
			cardAvailable[num-1]=false;
			charCoins.get(num-1)->moveTo((float)coinPoints[num-1].x, (float)coinPoints[num-1].y, 45);
		}
	}

	void CharSelectScreen::clickCharCardOnlyCPU(int num)
	{
		if(!cardAvailable[num-1])
		{
			cardAvailable[num-1]=true;
			Global::CPU[num-1]=true;
		}
		else
		{
			cardAvailable[num-1]=false;
			Global::CPU[num-1]=false;
			charCoins.get(num-1)->moveTo((float)coinPoints[num-1].x, (float)coinPoints[num-1].y, 45);
		}
	}

	void CharSelectScreen::clickCharCardOnlyHMU(int num)
	{
		if(!cardAvailable[num-1])
		{
			cardAvailable[num-1]=true;
			Global::CPU[num-1]=false;
		}
		else
		{
			cardAvailable[num-1]=false;
			Global::CPU[num-1]=false;
			charCoins.get(num-1)->moveTo((float)coinPoints[num-1].x, (float)coinPoints[num-1].y, 45);
		}
	}

	void CharSelectScreen::resetCards(ArrayList<int> type)
	{
		for(int i=0; i<type.size(); i++)
		{
			switch(type.get(i))
			{
				case 0:
				cardAvailable[i]=false;
				Global::CPU[i]=false;
				break;
				
				case 1:
				cardAvailable[i]=true;
				Global::CPU[i]=false;
				break;
				
				case 2:
				case 3:
				cardAvailable[i]=true;
				Global::CPU[i]=true;
				break;
			}
			charCoins.get(i)->x = (float)coinPoints[i].x;
			charCoins.get(i)->y = (float)coinPoints[i].y;
		}
		
		for(int i=0; i<=Global::possPlayers; i++)
		{
			Global::currentTeams[i] = Global::TEAM_RED;
		}
		
		Global::teamBattle = false;
	}
	
	void CharSelectScreen::setCardType(int card, byte type)
	{
		cardTypes[card] = type;
	}
	
	void CharSelectScreen::hideCoin(int num, boolean toggle)
	{
		for(int i=0; i<hiddenCoins.size(); i++)
		{
			if(hiddenCoins.get(i) == num)
			{
				if(!toggle)
				{
					hiddenCoins.remove(i);
				}
				return;
			}
		}
		if(toggle)
		{
			hiddenCoins.add(num);
		}
	}
	
	boolean CharSelectScreen::coinHidden(int num)
	{
		for(int i=0; i<hiddenCoins.size(); i++)
		{
			if(hiddenCoins.get(i) == num)
			{
				return true;
			}
		}
		return false;
	}
	
	void CharSelectScreen::disableCardChange(int card)
	{
		for(int i=0; i<disabledCards.size(); i++)
		{
			if(disabledCards.get(i) == card)
			{
				return;
			}
		}
		disabledCards.add(card);
	}
	
	void CharSelectScreen::enableCardChange(int card)
	{
		for(int i=0; i<disabledCards.size(); i++)
		{
			if(disabledCards.get(i) == card)
			{
				disabledCards.remove(i);
				return;
			}
		}
	}
	
	bool CharSelectScreen::cardChangeDisabled(int card)
	{
		for(int i=0; i<disabledCards.size(); i++)
		{
			if(disabledCards.get(i) == card)
			{
				return true;
			}
		}
		return false;
	}

	void CharSelectScreen::setCardAnimation(int num)
	{
		if(!cardAvailable[num-1])
		{
			charCards.get(num-1)->changeAnimation("NA", FORWARD);
		}
		else if(Global::CPU[num-1])
		{
			charCards.get(num-1)->changeAnimation("CPU", FORWARD);
		}
		else
		{
			charCards.get(num-1)->changeAnimation("HMU", FORWARD);
		}
	}

	void CharSelectScreen::addCardAnimations(int num)
	{
		charCards.get(num-1)->addAnimation(new Animation("NA",1,"Images/Menus/CharacterSelect/cards/na.png"));
		charCards.get(num-1)->addAnimation(new Animation("CPU",1,"Images/Menus/CharacterSelect/cards/cpu.png"));
		switch(num)
		{
			case 1:
			charCards.get(num-1)->addAnimation(new Animation("HMU",1,"Images/Menus/CharacterSelect/cards/p1_red.png"));
			break;
			
			case 2:
			charCards.get(num-1)->addAnimation(new Animation("HMU",1,"Images/Menus/CharacterSelect/cards/p2_blue.png"));
			break;
			
			case 3:
			charCards.get(num-1)->addAnimation(new Animation("HMU",1,"Images/Menus/CharacterSelect/cards/p3_yellow.png"));
			break;
			
			case 4:
			charCards.get(num-1)->addAnimation(new Animation("HMU",1,"Images/Menus/CharacterSelect/cards/p4_green.png"));
			break;
		}
		charCards.get(num-1)->changeAnimation("NA", FORWARD);
	}

	void CharSelectScreen::addToGrid(Actor*a,int x1,int y1,int xAmount,int yAmount,int xspace,int yspace,int num)
	{
		int xLoc;
	    int yLoc;
	    int xCreate;
	    int yCreate;
	    if(num>xAmount)
	    {
	    	xLoc = ((num-1)%xAmount)+1;
	        yLoc = ((num-1)/xAmount)+1;
	    }
	    else
	    {
	        xLoc=num;
	        yLoc=1;
	    }
	    xCreate=x1+(xspace*(xLoc-1));
	    yCreate=y1+(yspace*(yLoc-1));
	    a->x=(float)xCreate;
	    a->y=(float)yCreate;
	}

	Actor*CharSelectScreen::setUpCard(int num, int cType)
	{
		Actor*a;
		a = new CharCard(this,0,0,num,cType);
		return a;
	}

	CharSelectScreen::CharCoin::CharCoin(CharSelectScreen*screen,int num) : Actor(0,0)
	{
		drag = false;
		dragId = 0;
		this->screen = screen;
		Animation*anim;
		switch(num)
		{
			default:
			anim = new Animation("normal",1,"Images/Menus/CharacterSelect/coins/coin.png");
			break;
				
			case 1:
			anim = new Animation("normal",1,"Images/Menus/CharacterSelect/coins/coin1.png");
			break;
				
			case 2:
			anim = new Animation("normal",1,"Images/Menus/CharacterSelect/coins/coin2.png");
			break;
				
			case 3:
			anim = new Animation("normal",1,"Images/Menus/CharacterSelect/coins/coin3.png");
			break;
					
			case 4:
			anim = new Animation("normal",1,"Images/Menus/CharacterSelect/coins/coin4.png");
			break;
		}
		addAnimation(anim);
		changeAnimation("normal",FORWARD);
	}

	CharSelectScreen::CharCoin::~CharCoin()
	{
		//
	}

	void CharSelectScreen::CharCoin::onClick()
	{
		if(screen->canGrabCoin)
		{
			drag = true;
			dragId = getTouchId();
		}
	}

	void CharSelectScreen::CharCoin::onRelease()
	{
		drag = false;
	}

	void CharSelectScreen::CharCoin::Update(long gameTime)
	{
		Actor::Update(gameTime);
		if(drag && Game::checkTouchActive(dragId))
		{
			x = (float)Game::TouchX(dragId);
			y = (float)Game::TouchY(dragId);
		}
		else
		{
			drag = false;
		}
	}

	CharSelectScreen::CharIcon::CharIcon(int num, float x1, float y1, Animation*anim) : Actor(x1,y1)
	{
		Scale = 1.8f;
		addAnimation(anim);
		changeAnimation(anim->name, FORWARD);
		this->num = num;
	}

	CharSelectScreen::CharIcon::~CharIcon()
	{
		//
	}

	CharSelectScreen::CharCard::TeamFlag::TeamFlag(float x1, float y1, int num) : Actor(x1,y1)
	{
		this->num = num;
	}

	CharSelectScreen::CharCard::TeamFlag::~TeamFlag()
	{
		//
	}

	void CharSelectScreen::CharCard::TeamFlag::onRelease()
	{
		if(Global::currentTeams[num]==Global::TEAM_RED)
		{
			Global::currentTeams[num]=Global::TEAM_BLUE;
		}
		else if(Global::currentTeams[num]==Global::TEAM_BLUE)
		{
			Global::currentTeams[num]=Global::TEAM_GREEN;
		}
		else
		{
			Global::currentTeams[num] = Global::TEAM_RED;
		}
	}

	CharSelectScreen::CharCard::CharCard(CharSelectScreen*screen,float x1,float y1, int pNum, int type) : Actor(x1,y1)
	{
		this->screen = screen;
		this->type = type;
		this->num = pNum;
		Animation*anim = new Animation("normal",1);
		anim->addFrame("Images/Menus/CharacterSelect/cards/na.png");
		addAnimation(anim);
		
		Global::currentTeams[num] = Global::TEAM_RED;
		
		teamFlag = new TeamFlag(0,0, num);

		teamFlag->addAnimation(new Animation("red",1, "Images/Menus/CharacterSelect/flags/red.png"));
		teamFlag->addAnimation(new Animation("blue",1, "Images/Menus/CharacterSelect/flags/blue.png"));
		teamFlag->addAnimation(new Animation("green",1, "Images/Menus/CharacterSelect/flags/green.png"));
		teamFlag->changeAnimation("red", FORWARD);
			
		teamFlag->Scale = 1.4f;
	}

	CharSelectScreen::CharCard::~CharCard()
	{
		delete teamFlag;
	}

	void CharSelectScreen::CharCard::onRelease()
	{
		if(!screen->cardChangeDisabled(num-1) && !screen->coinsClicked() && !teamFlag->mouseOver() && !teamFlag->isClicked() && !teamFlag->wasClicked())
		{
			switch(type)
			{
				default:
				screen->clickCharCard(num);
				break;
					
				case 1:
				screen->clickCharCardOnlyHMU(num);
				break;
					
				case 2:
				screen->clickCharCardFirstCPU(num);
				break;
					
				case 3:
				screen->clickCharCardOnlyCPU(num);
				break;
			}
		}
	}

	void CharSelectScreen::CharCard::Update(long gameTime)
	{
		if(Global::teamBattle)
		{
			teamFlag->Update(gameTime);
			switch(Global::currentTeams[num])
			{
				default:
				Global::currentTeams[num] = Global::TEAM_RED;
				case Global::TEAM_RED:
				teamFlag->changeAnimation("red", FORWARD);
				break;
					
				case Global::TEAM_BLUE:
				teamFlag->changeAnimation("blue", FORWARD);
				break;
					
				case Global::TEAM_GREEN:
				teamFlag->changeAnimation("green", FORWARD);
				break;
			}
		}
		Actor::Update(gameTime);
	}

	void CharSelectScreen::CharCard::Draw(Graphics2D&g, long gameTime)
	{
		Actor::Draw(g, gameTime);
		if(Global::teamBattle)
		{
			teamFlag->x = x + 30;
			teamFlag->y = y - 60;
			teamFlag->Draw(g, gameTime);
		}
	}
}
