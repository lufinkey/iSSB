
#include "Global.h"
#include "ProjectileManager.h"
#include "ItemManager.h"
#include "Camera.h"
#include "Controls.h"
#include "P2PDataManager.h"
#include "Magnifier.h"
#include "Loader.h"

#if defined(__APPLE__)
	#include "TargetConditionals.h"
#endif

namespace SmashBros
{
	long Global::worldTime = 0;

	int*Global::players = new int[possPlayers+1];
	
	Player**Global::characters = new Player*[possPlayers+1];
	byte*Global::currentTeams = new byte[possPlayers+1];
	int*Global::scores = new int[possPlayers+1];
	int*Global::KOs = new int[possPlayers+1];
	int*Global::deaths = new int[possPlayers+1];
	int*Global::winners = new int[possPlayers+1];
	int*Global::teamWinners = new int[possTeams+1];
	Stage*Global::currentStage = null;
	
	HUD*Global::hud = null;

	int Global::charAmount = 0;

	int*Global::selectedChar = new int[possPlayers];
	int Global::selectedStage = 0;

	boolean Global::gamePlaying = false;
	boolean Global::gameFinished = false;

	boolean Global::suddenDeath = false;
	ArrayList<int> Global::suddenDeathPlayers = ArrayList<int>();

	boolean Global::smashBallOnField = false;
	boolean Global::playerHasSmashBall = false;

	boolean*Global::CPU = new boolean[possPlayers];
	int Global::timeLimit = 2;
	int Global::stockAmount = 3;
	int Global::gameMode = 1;
	int Global::gameType = 0;
	boolean Global::teamBattle = false;
	long Global::timeAmount = 0;

	boolean*Global::itemsOn = new boolean[30];
	ArrayList<int> Global::itemsActive = ArrayList<int>();

	int Global::maxLives = 20;
	int Global::minLives = 1;

	int Global::maxTime = 45;
	int Global::minTime = 1;
	
	ArrayList<int> Global::stageVotes = ArrayList<int>();
	boolean Global::selfReadyToPlay = false;
	boolean Global::peerReadyToPlay = false;
	boolean Global::peerLoaded = false;
	boolean Global::selfLoaded = false;
	String Global::P2PMessage = "Waiting for Peer...\n";
	
	void Global::init()
	{
		for(int i=0; i<possPlayers; i++)
		{
			selectedChar[i]=0;
			CPU[i] = false;
		}
		for(int i=0; i<=possPlayers; i++)
		{
			players[i] = 0;
			characters[i] = NULL;
			currentTeams[i] = 0;
			scores[i] = 0;
			KOs[i] = 0;
			deaths[i] = 0;
			winners[i] = 0;
		}
		for(int i=0; i<=possTeams; i++)
		{
			teamWinners[i] = 0;
		}
		for(int i=0; i<30; i++)
		{
			itemsOn[i] = false;
		}
		for(int i=0; i<totalItems; i++)
		{
			itemsOn[i] = true;
		}
	}

	String Global::getDirText(byte dir)
	{
		switch(dir)
		{
			case PrimitiveActor::DIR_DOWN:
			return "down";
			
			case PrimitiveActor::DIR_DOWNLEFT:
			return "downleft";
			
			case PrimitiveActor::DIR_LEFT:
			return "left";
			
			case PrimitiveActor::DIR_UPLEFT:
			return "upleft";
			
			case PrimitiveActor::DIR_UP:
			return "up";
			
			case PrimitiveActor::DIR_UPRIGHT:
			return "upright";
		}
		return "";
	}
	
	String Global::getAddonsFolder()
	{
#if defined(__APPLE__) && (TARGET_OS_IPHONE == 1 || TARGET_IPHONE_SIMULATOR == 1 || TARGET_OS_MAC == 1)
		return (String)getenv("HOME") + "/Library/iSSB/addons";
#elif defined(__ANDROID__)
		// TODO change for android
		return (String)"addons";
#else
		return (String)"addons";
#endif
	}

	long Global::getWorldTime()
	{
		return worldTime;
	}

	void Global::Update(long gameTime)
	{
		worldTime = gameTime;
	}
	
	void Global::onReturnToMenu()
	{
		MusicManager::loadSong("Menu Theme");
		selectedStage = 0;
	}

	String Global::getPlayerName(int playerNo)
	{
		return CharacterLoader::getName(getPlayerActor(playerNo)->charNo);
	}

	boolean Global::isInSuddenDeath(byte playerNo)
	{
		for(int i=0; i<suddenDeathPlayers.size(); i++)
		{
			if(playerNo == (byte)(suddenDeathPlayers.get(i)))
			{
				return true;
			}
		}
		return false;
	}

	void Global::scorePoint(byte pNum)
	{
		Player*playr = getPlayerActor(pNum);
	    if(playr->lastHit == 0)
	    {
	        scores[pNum]-=1;
	        Console::WriteLine((String)"scores[" + pNum + "]-=1");
	        hud->showScore(pNum, -1);
	    }
	    else
	    {
	        scores[pNum]-=1;
	        scores[playr->lastHit]+=1;
	        Console::WriteLine((String)"scores[" + pNum + "]-=1  scores[" + playr->lastHit + "]+1");
	        hud->showScore(pNum, -1);
	        hud->showScore(playr->lastHit, 1);
	    }
	    for(int i=0; i<=possPlayers; i++)
	    {
	    	Console::Write((String)"scores[" + i + "]=" + scores[i] + ", ");
	    }
	    Console::WriteLine("");
	}
	
	void Global::finishBrawl()
	{
		if(P2PDataManager::isEnabled() && P2PDataManager::isServer())
		{
			DataVoid data;
			
			byte type = P2PDataManager::DATA_READYGO;
			data.add(&type, sizeof(type));
			
			type = P2PDataManager::READYGO_GAME;
			data.add(&type, sizeof(type));
			
			P2PManager::sendData(data.getData(), data.length(), P2PManager::SENDDATA_RELIABLE);
		}
		
		if(Global::suddenDeath)
		{
			for(byte i=0; i<=Global::possPlayers; i++) //TODO: loop characters
			{
				if(Global::characters[i]!=null)
				{
					boolean inSuddenDeath = Global::isInSuddenDeath(i);
					if(inSuddenDeath)
					{
						if(P2PDataManager::isEnabled())
						{
							if(P2PDataManager::isServer())
							{
								Global::characters[i]->respawn();
							}
						}
						else
						{
							Global::characters[i]->respawn();
						}
						Global::characters[i]->percent = 300;
						ItemManager::RemoveAll();
						hud->firstUpdate = true;
						ScreenManager::GoToScreen("Game");
						
					}
					else
					{
						Global::characters[i]->reset();
						Global::characters[i]->alive = false;
					}
				}
			}
		}
		else
		{
			Global::UnloadGame();
			//TODO: add game types
			switch(Global::gameType)
			{
				case Global::TYPE_GROUPBRAWL:
				ScreenManager::GoToScreen("Winners");
				break;
			}
		}
	}

	void Global::UnloadGame()
	{
		for(byte i=0; i<=possPlayers; i++)
		{
			if(characters[i]!=null)
			{
				characters[i]->Unload();
				delete characters[i];
				characters[i] = null;
			}
		}
		
		hud->Unload();
		
		ProjectileManager::RemoveAll();
		ItemManager::Unload();
		
		currentStage->Unload();
		delete currentStage;
		currentStage = null;
		ItemManager::RemoveAll();
		Global::suddenDeath = false;
		Global::gameFinished = true;
		Global::gamePlaying = false;
	}

	void Global::createHUD()
	{
		hud = new HUD();
	}

	void Global::LoadGame()
	{
		Console::WriteLine("calling function LoadGame()");
		
		Controls::enableTouchControls(true);
		
		for(int i=0; i<=Global::possPlayers; i++)
		{
			Global::characters[i] = null;
		}
	    
	    Camera::reset();
		
		ProjectileManager::destroyedProjectiles.clear();
		ItemManager::destroyedItems.clear();
	    
	    gamePlaying = false;
	    
	    for(int i=0; i<possPlayers; i++)
	    {
	        Console::Write((String)"cpu[" + i + "]=" + CPU[i] + ", ");
	    }
	    Console::WriteLine("");
	    
	    Console::WriteLine("storing characters into array players[]");
	    
	    int counter = 0;
	    for(int i=0; i<possPlayers; i++)
	    {
	        if(selectedChar[i]>0)
	        {
	        	counter++;
	        	players[counter]=i+1;
	        }
	    }
	    
	    charAmount=counter;
	    timeAmount = timeLimit*60;
		
	    Console::WriteLine("finished storing in array players[]");
	    
	    for(int i=0; i<=possPlayers; i++)
	    {
	    	scores[i]=0;
	    	winners[i]=0;
	    	teamWinners[i]=0;
	    	KOs[i]=0;
	    	deaths[i]=0;
	    }
	    
	    itemsActive.clear();
	    
	    Global::suddenDeath = false;
	    Global::playerHasSmashBall = false;
	    Global::smashBallOnField = false;
		
	    for(int i=0; i<totalItems; i++)
	    {
	        if(itemsOn[i])
	        {
				Console::Write((String)"itemsOn[" + i + "]=" + itemsOn[i] + ", ");
	            itemsActive.add(i+1);
	        }
	    }
		Console::WriteLine("");
		
	    Console::WriteLine((String)"total active items: " + itemsActive.size());
		
		Magnifier::load();
	    
	    currentStage = StageLoader::createStage((float)View::getScalingWidth()/2, (float)View::getScalingHeight()/2, selectedStage);
	    
	    createPlayers();
	    
	    if(gameType==TYPE_TRAINING)
	    {
	    	if(Global::characters[2]!=null)
	    	{
	    		Global::characters[2]->aiType = Player::AI_STOP;
	    	}
	    }
	}
	
	void Global::createPlayers()
	{
		for(int i=0; i<charAmount; i++)
	    {
	    	Vector2f pnt = currentStage->getSpawnPoint(players[i+1]);
	    	byte teamNo = 0;
	    	if(teamBattle)
	    	{
	    		teamNo = currentTeams[i+1];
	    	}
	    	characters[players[i+1]] = CharacterLoader::createPlayer((float)pnt.x,(float)pnt.y,(byte)players[i+1],teamNo,selectedChar[players[i+1]-1]);
	    }

		for(int i=0; i<=possPlayers; i++)
		{
			if(characters[i]!=null)
			{
				characters[i]->whenCreated();
			}
		}
	}

	Player*Global::getPlayerActor(int pNum)
	{
		return characters[pNum];
	}

	String Global::getItemName(int itemNo)
	{
		switch(itemNo) //TODO: add items
		{
			default:
			return "Unknown";
			
			case ITEM_SMASHBALL:
			return "SmashBall";
			
			case ITEM_SUPERMUSHROOM:
			return "Super Mushroom";
			
			case ITEM_POISONMUSHROOM:
			return "Poison Mushroom";
			
			case ITEM_RAYGUN:
			return "Ray Gun";
			
			case ITEM_HEARTCONTAINER:
			return "Heart Container";
			
			case ITEM_BEAMSWORD:
			return "Beam Sword";
		}
	}

	boolean Global::checkWinners(byte pNum)
	{
		if(gamePlaying)
		{
			if(suddenDeath)
			{
				return checkWinnersSuddenDeath(pNum);
			}
			else
			{
				if(teamBattle)
				{
					ArrayList<ArrayList<int> > teams = ArrayList<ArrayList<int> >();
					
					for(int i=0; i<=possTeams; i++)
					{
						teams.add(ArrayList<int>());
					}
					
					for(int i=0; i<=possPlayers; i++)
					{
						if(characters[i]!=null)
						{
							int t = characters[i]->team;
							
							teams.get(t).add(i);
						}
					}
					
					int totalTeams = 0;
					
					ArrayList<int> aliveTeams = ArrayList<int>();
					
					for(int i=0; i<teams.size(); i++)
					{
						int totalAlive = 0;
						int total = teams.get(i).size();
						if(total>0)
						{
							totalTeams++;
							for(int j=0; j<total; j++)
							{
								if(characters[teams.get(i).get(j)]->stock > 0)
								{
									totalAlive++;
								}
							}
							if(totalAlive>0)
							{
								aliveTeams.add(i);
							}
						}
					}
					
					byte team = characters[pNum]->team;
					
					int total = teams.get(team).size();
					
					int totalAlive = 0;
					
					for(int i=0; i<total; i++)
					{
						if(characters[teams.get(team).get(i)]->stock > 0)
						{
							totalAlive++;
						}
					}
					
					if(totalAlive == 0)
					{
						for(int i=totalTeams; i>=1; i--)
						{
							if(teamWinners[i]==0)
							{
								teamWinners[i] = team;
								i=0;
							}
						}
					}
					
					if(aliveTeams.size()>1)
					{
						if(characters[pNum]->stock <= 0)
						{
							checkWinnersFreeForAll(pNum);
						}
						
						return false;
					}
					else
					{
						if(characters[pNum]->stock <= 0)
						{
							checkWinnersFreeForAll(pNum);
							
							int*actualWinners = new int[possTeams+1];
							for(int i=1; i<=possTeams; i++)
							{
								actualWinners[winners[i]] = i;
							}
							
							ArrayList<int> remaining = ArrayList<int>();
							for(int i=1; i<=possPlayers; i++)
							{
								if(characters[i]!=null)
								{
									if(actualWinners[i]==0)
									{
										remaining.add(i);
									}
								}
							}
							
							int n = remaining.size();
							
							for(int i = 0; i < n; i++)
							{
								for(int j = 1; j < (n-i); j++)
								{
									if(characters[remaining.get(j-1)]->stock < characters[remaining.get(j)]->stock)
									{
										int i1 = remaining.get(j-1);
										remaining.set(j-1,remaining.get(j));
										remaining.set(j,i1);
									}
									else if(characters[remaining.get(j-1)]->stock == characters[remaining.get(j)]->stock)
									{
										if(KOs[remaining.get(j-1)] < KOs[remaining.get(j)])
										{
											int i1 = remaining.get(j-1);
											remaining.set(j-1,remaining.get(j));
											remaining.set(j,i1);
										}
									}
								}
							}
							
							int counter = 0;
							for(int i=1; i<charAmount; i++)
							{
								if(winners[i]==0)
								{
									winners[i] = remaining.get(counter);
									counter++;
								}
							}

							delete[] actualWinners;
						}
						
						teamWinners[1] = aliveTeams.get(0);
						return true;
					}
				}
				else
				{
					return checkWinnersFreeForAll(pNum);
				}
			}
		}
		return false;
	}

	boolean Global::checkWinnersFreeForAll(byte pNum)
	{
		if(characters[pNum]->stock <= 0)
		{
			for(int i=charAmount; i>=1; i--)
			{
				if(winners[i] == 0)
				{
					winners[i] = pNum;
					if(i==2)
					{
						for(int j=0; j<=possPlayers; j++)
						{
							if(characters[j]!=null)
							{
								if(characters[j]->stock > 0)
								{
									winners[1] = j;
									return true;
								}
							}
						}
						return true;
					}
					return false;
				}
			}
		}
		return false;
	}

	boolean Global::checkWinnersSuddenDeath(byte pNum)
	{
		if(teamBattle)
		{
			//for teams, make sure only one team is left standing.
			//queue the teamWinners and winners (by team)
			//winners need to be completely queued (all players)
			
			//Get Teams in array
			ArrayList<ArrayList<int> > sdteams = ArrayList<ArrayList<int> >();
			
			for(int i=0; i<(possTeams+1); i++)
			{
				sdteams.add(ArrayList<int>());
			}
			
			for(int i=0; i<suddenDeathPlayers.size(); i++)
			{
				int t = characters[suddenDeathPlayers.get(i)]->team;
				
				sdteams.get(t).add(suddenDeathPlayers.get(i));
			}
			
			//check if player's team is dead
			byte team = characters[pNum]->team;
			
			int totalAlive = 0;
			
			for(int i=0; i<sdteams.get(team).size(); i++)
			{
				if(characters[sdteams.get(team).get(i)]->stock > 0)
				{
					totalAlive++;
				}
			}
			
			if(totalAlive > 0)
			{
				//player's team is alive
			}
			else
			{
				//put player's team in queue
				
				boolean*aliveTeams = new boolean[possTeams+1];
				
				for(int i=0; i<=possPlayers; i++)
				{
					if(characters[i]!=null)
					{
						aliveTeams[characters[i]->team] = true;
					}
				}
				
				int totalTeams = 0;
				
				int aliveTeamsLength = possTeams+1;
				for(int i=0; i<aliveTeamsLength; i++)
				{
					if(aliveTeams[i])
					{
						totalTeams++;
					}
				}
				
				for(int i=totalTeams; i>=1; i--)
				{
					if(teamWinners[i]==0)
					{
						teamWinners[i] = team;
						i=0;
					}
				}

				delete[] aliveTeams;
			}
			
			//check if only 1 team is alive
			
			ArrayList<int> aliveTeams = ArrayList<int>();
			
			for(int i=0; i<sdteams.size(); i++)
			{
				//check stocks of current team
				//increment totalTeamsAlive if the team is alive
				int totalInTeam = 0;
				
				for(int j=0; j<sdteams.get(i).size(); j++)
				{
					if(characters[sdteams.get(i).get(j)]->stock > 0)
					{
						totalInTeam++;
					}
				}
				
				if(totalInTeam > 0)
				{
					aliveTeams.add(i);
				}
			}
			
			if(aliveTeams.size() > 1)
			{
				return false;
			}
			else
			{
				winners[1] = aliveTeams.get(0);
				
				int*actualWinners = new int[possTeams+1];
				for(int i=1; i<=possTeams; i++)
				{
					actualWinners[winners[i]] = i;
				}
				
				ArrayList<int> remaining = ArrayList<int>();
				for(int i=1; i<=possPlayers; i++)
				{
					if(characters[i]!=null)
					{
						if(actualWinners[i]==0)
						{
							remaining.add(i);
						}
					}
				}
				
				int n = remaining.size();
				
				for(int i = 0; i < n; i++)
				{
					for(int j = 1; j < (n-i); j++)
					{
						if(characters[remaining.get(j-1)]->stock < characters[remaining.get(j)]->stock)
						{
							int i1 = remaining.get(j-1);
							remaining.set(j-1,remaining.get(j));
							remaining.set(j,i1);
						}
						else if(characters[remaining.get(j-1)]->stock == characters[remaining.get(j)]->stock)
						{
							if(KOs[remaining.get(j-1)] < KOs[remaining.get(j)])
							{
								int i1 = remaining.get(j-1);
								remaining.set(j-1,remaining.get(j));
								remaining.set(j,i1);
							}
						}
					}
				}
				
				int counter = 0;
				for(int i=1; i<charAmount; i++)
				{
					if(winners[i]==0)
					{
						winners[i] = remaining.get(counter);
						counter++;
					}
				}
				
				if(aliveTeams.size()>0)
				{
					teamWinners[1] = aliveTeams.get(0);
				}
				
				delete[] actualWinners;

				return true;
			}
		}
		else
		{
			//just regular easy queueing. just fill in teh zeros
			
			for(int i=suddenDeathPlayers.size(); i>=1; i--)
			{
				if(winners[i]==0)
				{
					winners[i] = pNum;
					i=0;
				}
			}
			
			int totalAlive = 0;
			
			for(int i=0; i<suddenDeathPlayers.size(); i++)
			{
				if(characters[suddenDeathPlayers.get(i)]->stock > 0)
				{
					totalAlive++;
				}
			}
			
			if(totalAlive > 1)
			{
				return false;
			}
			else
			{
				for(int i=0; i<suddenDeathPlayers.size(); i++)
				{
					if(characters[suddenDeathPlayers.get(i)]->stock>0)
					{
						winners[1] = suddenDeathPlayers.get(i);
						return true;
					}
				}
				return true;
			}
		}
	}

	void Global::finishGame()
	{
		Console::WriteLine("calling function finishGame()");
	    switch(gameType)
	    {
	        case 1:
	        if(suddenDeath)
	        {
	        	finishGameSuddenDeath();
	        }
	        else
	        {
		        if(teamBattle)
		        {
		        	finishGameTeam();
		        }
		        else
		        {
		            finishGameFreeForAll();
		        }
	        }
	        break;
	        
	        case 2:
	        finishGameSoloTraining();
	        break;
	    }
	    Console::WriteLine("reached end of function finishGame()");
	}

	void Global::finishGameFreeForAll()
	{
		if(gameMode == MODE_TIME_LIMIT)
		{
			ArrayList<ArrayList<int> > ties = ArrayList<ArrayList<int> >();
			
			ArrayList<Vector2i> order = ArrayList<Vector2i>();
			
			for(int i=0; i<=possPlayers; i++)
			{
				if(characters[i]!=null)
				{
					Vector2i vect = Vector2i(i,scores[i]);
					order.add(vect);
				}
			}
			
			int n = order.size();
			
			for(int i = 0; i < n; i++)
			{
				for(int j = 1; j < (n-i); j++)
				{
					if(order.get(j-1).y < order.get(j).y)
					{
						Vector2i vect = order.get(j-1);
						order.set(j-1,order.get(j));
						order.set(j,vect);
					}
				}
			}
			
			int prevScore = 0;
			
			for(int i=0; i<order.size(); i++)
			{
				int value = order.get(i).y;
				if(value==prevScore && i!=0)
				{
					if(ties.size()>0)
					{
						if(scores[ties.get(ties.size()-1).get(0)] == value)
						{
							ties.get(ties.size()-1).add(order.get(i).x);
						}
						else
						{
							ArrayList<int> tied = ArrayList<int>();
							tied.add(order.get(i).x);
							tied.add(order.get(i-1).x);
							ties.add(tied);
						}
					}
					else
					{
						ArrayList<int> tied = ArrayList<int>();
						tied.add(order.get(i).x);
						tied.add(order.get(i-1).x);
						ties.add(tied);
					}
				}
				prevScore = value;
			}
			
			for(int i=0; i<order.size(); i++)
			{
				boolean canStore = true;
				if(ties.size()>0)
				{
					for(int j=0; j<ties.get(0).size(); j++)
					{
						if(ties.get(0).get(j) == order.get(i).x)
						{
							canStore = false;
							j = ties.get(0).size();
						}
					}
				}
				if(canStore)
				{
					winners[i+1] = order.get(i).x;
				}
				else
				{
					winners[i+1] = 0;
				}
			}
			
			suddenDeathPlayers.clear();
			
			if(ties.size()>0)
			{
				suddenDeath = true;
				int totalTies = ties.get(0).size();
				for(int i=0; i<totalTies; i++)
				{
					suddenDeathPlayers.add(ties.get(0).get(i));
				}
			}
			
			for(int i=0; i<suddenDeathPlayers.size(); i++)
			{
				characters[suddenDeathPlayers.get(i)]->stock = 1;
			}
		}
		
		gamePlaying = false;
		hud->showFinishGame = true;
		hud->finishGameTime = getWorldTime() + 3000;
	}

	void Global::finishGameTeam()
	{
		if(gameMode == MODE_TIME_LIMIT)
		{
			//get teams in arraylist
			
			ArrayList<ArrayList<int> > teams = ArrayList<ArrayList<int> >();
			
			for(int i=0; i<5; i++)
			{
				teams.add(ArrayList<int>());
			}
			
			for(int i=0; i<=possPlayers; i++)
			{
				if(characters[i]!=null)
				{
					int t = characters[i]->team;
					
					teams.get(t).add(i);
				}
			}
			
			//get team totals
			
			int*teamTotals = new int[possTeams+1];
			
			for(int i=0; i<=possTeams; i++)
			{
				teamTotals[i] = 0;
			}
			
			for(int i=0; i<=possPlayers; i++)
			{
				if(characters[i]!=null)
				{
					teamTotals[characters[i]->team]+=scores[i];
				}
			}
			
			ArrayList<Vector2i> teamOrder = ArrayList<Vector2i>();
			
			for(int i=0; i<=possTeams; i++)
			{
				if(teams.get(i).size()>0)
				{
					Vector2i vect = Vector2i(i,teamTotals[i]);
					teamOrder.add(vect);
				}
			}
			
			int n = teamOrder.size();
			
			for(int i = 0; i < n; i++)
			{
				for(int j = 1; j < (n-i); j++)
				{
					if(teamOrder.get(j-1).y < teamOrder.get(j).y)
					{
						Vector2i vect = teamOrder.get(j-1);
						teamOrder.set(j-1,teamOrder.get(j));
						teamOrder.set(j,vect);
					}
				}
			}
			
			ArrayList<ArrayList<int> > ties = ArrayList<ArrayList<int> >();
			
			int prevScore = 0;
			
			for(int i=0; i<teamOrder.size(); i++)
			{
				int value = teamOrder.get(i).y;
				if(value==prevScore && i!=0)
				{
					if(ties.size()>0)
					{
						if(teamTotals[ties.get(ties.size()-1).get(0)] == value)
						{
							ties.get(ties.size()-1).add(teamOrder.get(i).x);
						}
						else
						{
							ArrayList<int> tied = ArrayList<int>();
							tied.add(teamOrder.get(i).x);
							tied.add(teamOrder.get(i-1).x);
							ties.add(tied);
						}
					}
					else
					{
						ArrayList<int> tied = ArrayList<int>();
						tied.add(teamOrder.get(i).x);
						tied.add(teamOrder.get(i-1).x);
						ties.add(tied);
					}
				}
				prevScore = value;
			}
			
			for(int i=0; i<teamOrder.size(); i++)
			{
				boolean canStore = true;
				if(ties.size()>0)
				{
					for(int j=0; j<ties.get(0).size(); j++)
					{
						if(ties.get(0).get(j) == teamOrder.get(i).x)
						{
							canStore = false;
							j = ties.get(0).size();
						}
					}
				}
				if(canStore)
				{
					teamWinners[i] = (byte)(teamOrder.get(i).x);
				}
				else
				{
					teamWinners[i] = 0;
				}
			}
			
			suddenDeathPlayers.clear();
			
			if(ties.size()>0)
			{
				suddenDeath = true;
				int totalTies = ties.get(0).size();
				for(int i=0; i<totalTies; i++)
				{
					int currentTeam = ties.get(0).get(i);
					int totalPlayers = teams.get(currentTeam).size();
					for(int j=0; j<totalPlayers; j++)
					{
						suddenDeathPlayers.add(teams.get(currentTeam).get(j));
					}
				}
			}
			else
			{
				// reorder regular scores
				ArrayList<Vector2i> order = ArrayList<Vector2i>();
				
				for(int i=0; i<=possPlayers; i++)
				{
					if(characters[i]!=null)
					{
						Vector2i vect = Vector2i(i,scores[i]);
						order.add(vect);
					}
				}
				
				int n2 = order.size();
				
				for(int i = 0; i < n2; i++)
				{
					for(int j = 1; j < (n2-i); j++)
					{
						if(order.get(j-1).y < order.get(j).y)
						{
							Vector2i vect = order.get(j-1);
							order.set(j-1,order.get(j));
							order.set(j,vect);
						}
					}
				}
				
				for(int i=0; i<order.size(); i++)
				{
					winners[i+1] = order.get(i).x;
				}
			}
			
			for(int i=0; i<suddenDeathPlayers.size(); i++)
			{
				characters[suddenDeathPlayers.get(i)]->stock = 1;
			}

			delete[] teamTotals;
		}
		
		gamePlaying = false;
		hud->showFinishGame = true;
		hud->finishGameTime = getWorldTime() + 3000;
	}

	void Global::finishGameSoloTraining()
	{
		UnloadGame();
		ScreenManager::GoToScreen("TrainingCharSelect");
	}

	void Global::finishGameSuddenDeath()
	{
		/*if(teamBattle)
		{
			
		}
		else
		{*/
			ArrayList<Vector2i> order = ArrayList<Vector2i>();
			
			for(int i=0; i<=possPlayers; i++)
			{
				if(characters[i]!=null)
				{
					Vector2i vect = Vector2i(i,scores[i]);
					order.add(vect);
				}
			}
			
			int n2 = order.size();
			
			for(int i = 0; i < n2; i++)
			{
				for(int j = 1; j < (n2-i); j++)
				{
					if(order.get(j-1).y < order.get(j).y)
					{
						Vector2i vect = order.get(j-1);
						order.set(j-1,order.get(j));
						order.set(j,vect);
					}
				}
			}
			
			for(int i=0; i<order.size(); i++)
			{
				winners[i+1] = order.get(i).x;
			}
		//}
		
		suddenDeath = false;
		gamePlaying = false;
		hud->showFinishGame = true;
		hud->finishGameTime = getWorldTime() + 3000;
	}
}
