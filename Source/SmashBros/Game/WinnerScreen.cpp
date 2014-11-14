
#include "WinnerScreen.h"
#include "../Global.h"
#include "../Preferences.h"
#include "../Menus/Menus.h"
#include "../Loader.h"

namespace SmashBros
{
	WinnerScreen::FinishButton::FinishButton(float x1, float y1) : Actor(x1,y1)
	{
		//
	}
	
	WinnerScreen::FinishButton::~FinishButton()
	{
		//
	}
	
	void WinnerScreen::FinishButton::onMouseEnter()
	{
		changeAnimation("hover",FORWARD);
	}
	
	void WinnerScreen::FinishButton::onMouseLeave()
	{
		changeAnimation("normal",FORWARD);
	}
	
	void WinnerScreen::FinishButton::onRelease()
	{
		if(Global::gameType==Global::TYPE_GROUPBRAWL)
		{
			ScreenManager::GoToScreen("BrawlCharSelect");
		}
	}
	
	WinnerScreen::WinnerScreen(const String&name) : Screen(name)
	{
		button_finish = new FinishButton(800,500);

		button_finish->addAnimation(new Animation("normal", 1, "Images/Game/WinnerScreen/continue.png"));
		button_finish->addAnimation(new Animation("hover", 1, "Images/Game/WinnerScreen/continue_selected.png"));
		button_finish->changeAnimation("normal", FORWARD);
	}
	
	WinnerScreen::~WinnerScreen()
	{
		for(int i=0; i<stats.size(); i++)
		{
			delete stats.get(i);
		}
		stats.clear();

		files.clear();
		delete button_finish;
	}
	
	void WinnerScreen::Initialize()
	{
		//
	}
	
	void WinnerScreen::LoadContent()
	{
		for(int i=0; i<Global::possTeams; i++)
		{
			Console::Write((String)"teamWinners[" + i + "]=" + Global::teamWinners[i] + ", ");
		}
		Console::WriteLine("");
		for(int i=0; i<Global::possPlayers; i++)
		{
			Console::Write((String)"winners[" + i + "]=" + Global::winners[i] + ", ");
		}
		Console::WriteLine("");
		
		Game::setBackgroundImage("Images/Game/WinnerScreen/bg.png");
		
		for(int i=0; i<stats.size(); i++)
		{
			delete stats.get(i);
		}
		stats.clear();
		
		int actualWinnersLength = Global::possPlayers+1;
		int actualTeamWinnersLength = Global::possTeams+1;
		
		int*actualWinners = new int[Global::possPlayers+1];
		int*actualTeamWinners = new int[Global::possTeams+1];
		
		for(int i=1; i<actualWinnersLength; i++)
		{
			actualWinners[Global::winners[i]] = i;
		}
		for(int i=1; i<actualTeamWinnersLength; i++)
		{
			actualTeamWinners[Global::teamWinners[i-1]] = i;
		}
		
		for(int i=1; i<actualWinnersLength; i++)
		{
			int pNum;
			int team;
			int place;
			int teamplace;
			int score;
			int ko;
			int death;
			
			pNum = i;
			
			if(Global::selectedChar[i-1]!=0)
			{
				if(Global::teamBattle)
				{
					teamplace = actualTeamWinners[Global::currentTeams[i]];
					place = actualWinners[i];
					team = Global::currentTeams[i];
				}
				else
				{
					place = actualWinners[i];
					team = 0;
					teamplace = 0;
				}
				
				score = Global::scores[i];
				ko = Global::KOs[i];
				death = Global::deaths[i];
				
				CharStat*stat = new CharStat(this, pNum, team, place, teamplace, score, ko, death);
				stats.add(stat);
			}
		}
		
		if(Global::teamBattle)
		{
			int n = stats.size();
			
			for(int i = 0; i < n; i++)
			{
				for(int j = 1; j < (n-i); j++)
				{
					if(stats.get(j-1)->teamplace > stats.get(j)->teamplace)
					{
						CharStat*stat = stats.get(j-1);
						stats.set(j-1,stats.get(j));
						stats.set(j,stat);
					}
					else if(stats.get(j-1)->teamplace == stats.get(j)->teamplace)
					{
						if(stats.get(j-1)->place > stats.get(j)->place)
						{
							CharStat*stat = stats.get(j-1);
							stats.set(j-1,stats.get(j));
							stats.set(j,stat);
						}
					}
				}
			}
		}
		else
		{
			int n = stats.size();
			
			for(int i = 0; i < n; i++)
			{
				for(int j = 1; j < (n-i); j++)
				{
					if(stats.get(j-1)->place > stats.get(j)->place)
					{
						CharStat*stat = stats.get(j-1);
						stats.set(j-1,stats.get(j));
						stats.set(j,stat);
					}
				}
			}
		}
		
		for(int i=0; i<stats.size(); i++)
		{
			CharStat*stat = stats.get(i);
			stat->x = (float)((float)View::getScalingWidth() / (float)(Global::charAmount+1))*(float)(i+1);
			stat->y = 250;
		}

		delete[] actualWinners;
		delete[] actualTeamWinners;
	}

	void WinnerScreen::UnloadContent()
	{
		for(int i=0; i<files.size(); i++)
		{
			AssetManager::unloadImage(files.get(i));
		}
		
		if(Preferences::menuMusicOn())
		{
			//Menus::menutheme.play();
		}
	}

	void WinnerScreen::Update(long gameTime)
	{
		for(int i=0; i<stats.size(); i++)
		{
			stats.get(i)->Update(gameTime);
		}
		button_finish->Update(gameTime);
	}

	void WinnerScreen::Draw(Graphics2D&g, long gameTime)
	{
		button_finish->Draw(g, gameTime);
		for(int i=0; i<stats.size(); i++)
		{
			stats.get(i)->Draw(g, gameTime);
		}
	}

	boolean WinnerScreen::addFile(String fileName)
	{
		for(int i=0; i<files.size(); i++)
		{
			if(fileName.equals(files.get(i)))
			{
				return true;
			}
		}
		int r = AssetManager::loadImage(fileName);
		if(r==1)
		{
			files.add(fileName);
			return true;
		}
		return false;
	}

	WinnerScreen::CharStat::CharStatPlayer::CharStatPlayer(float x1, float y1) : Actor(x1,y1)
	{
		//
	}

	WinnerScreen::CharStat::CharStatPlayer::~CharStatPlayer()
	{
		//
	}

	void WinnerScreen::CharStat::CharStatPlayer::onAnimationFinish(const String&name)
	{
		if(name.equals((String)"win"))
		{
			changeAnimation("win_hold",FORWARD);
		}
	}

	WinnerScreen::CharStat::CharStat(WinnerScreen*screen, int pNum, int team, int place, int teamplace, int score, int ko, int death)
	{
		x = 0;
		y = 0;
		this->pNum = pNum;
		this->team = team;
		this->place = place;
		this->teamplace = teamplace;
		this->score = score;
		this->ko = ko;
		this->death = death;
		cNum = Global::selectedChar[pNum-1];
		playr = new CharStatPlayer(x,y);
		
		playr->setScale(3.0f);
		
		boolean success;
		
		String charFolderPath = CharacterLoader::getFolder(cNum);
		String win = charFolderPath + "/win.png";
		String win_hold = charFolderPath + "/win_hold.png";
		String lose = charFolderPath + "/lose.png";
		
		success = screen->addFile(lose);
		if(!success)
		{
			lose = "Images/Game/Misc/placeholder.gif";
			screen->addFile(lose);
		}
		success = screen->addFile(win);
		if(!success)
		{
			win = "Images/Game/Misc/placeholder.gif";
			screen->addFile(win);
		}
		success = screen->addFile(win_hold);
		if(!success)
		{
			win_hold = "Images/Game/Misc/placeholder.gif";
			screen->addFile(win_hold);
		}
			
		ArrayList<Animation*> animations = CharacterLoader::getWinnersScreenAnimations(cNum);
		for(int i=0; i<animations.size(); i++)
		{
			playr->addAnimation(animations.get(i));
		}
			
		if((Global::teamBattle && teamplace==1) || (!Global::teamBattle && place==1))
		{
			playr->changeAnimation("win", FORWARD);
		}
		else
		{
			playr->changeAnimation("lose", FORWARD);
		}
			
		String str = "";
			
		if(Global::teamBattle)
		{
			str += getPlaceString(teamplace) + ": " + getTeamString(team) + " Team\n";
			str += getPlaceString(place) + ": " + "Player " + pNum + "\n";
		}
		else
		{
			str += getPlaceString(place) + ": " + "Player " + pNum + "\n";
		}
		str += "\n";
		str += (String)"Score: " + (String)this->score + (String)"\n";
		str += (String)"KOs: " + (String)this->ko + (String)"\n";
		str += (String)"Deaths: " + (String)this->death + (String)"\n";
			
		description = new TextActor(str, AssetManager::getFont("Fonts/arial.ttf", Font::BOLD, 14), Color::BLACK);
		description->setAlignment(TextActor::ALIGN_CENTER);
	}

	WinnerScreen::CharStat::~CharStat()
	{
		delete playr;
		delete description;
	}

	void WinnerScreen::CharStat::Update(long gameTime)
	{
		playr->x = x;
		playr->y = y - playr->height/2;
		playr->Update(gameTime);
		description->x = x;
		description->y = y + description->height/2;
		description->Update(gameTime);
	}

	void WinnerScreen::CharStat::Draw(Graphics2D&g, long gameTime)
	{
		playr->x = x;
		playr->y = y - playr->height/2;
		playr->Draw(g, gameTime);
		description->x = x;
		description->y = y + description->height/2;
		description->Draw(g, gameTime);
	}

	String WinnerScreen::CharStat::getTeamString(int teamNum)
	{
		switch(teamNum)
		{
			case Global::TEAM_RED:
			return "Red";
				
			case Global::TEAM_BLUE:
			return "Blue";
				
			case Global::TEAM_GREEN:
			return "Green";
				
			case Global::TEAM_YELLOW:
			return "Yellow";
		}
		return "";
	}

	String WinnerScreen::CharStat::getPlaceString(int placeNum)
	{
		switch(placeNum)
		{
			case 1:
			return "1st Place";
				
			case 2:
			return "2nd Place";
				
			case 3:
			return "3rd Place";
				
			case 4:
			return "4th Place";
				
			case 5:
			return "5th Place";
				
			case 6:
			return "6th Place";
		}
		return "";
	}

	String WinnerScreen::CharStat::toString()
	{
		String str = "";
		str += (String)"Player " + (String)pNum + (String)"\n";
			
		if(Global::teamBattle)
		{
			str += (String)"Place: " + (String)teamplace + (String)"\n";
			str += (String)"Actual (non-team) place: " + (String)place + (String)"\n";
			str += (String)"Team: " + (String)team + (String)"\n";
		}
		else
		{
			str += (String)"Place: " + (String)place + (String)"\n";
		}
			
		str += (String)"Score: " + (String)score + (String)"\n";
		str += (String)"KOs: " + (String)ko + (String)"\n";
			
		return str;
	}

	WinnerScreen::CharStat::operator String()
	{
		return toString();
	}
}