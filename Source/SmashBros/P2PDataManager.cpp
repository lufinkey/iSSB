
#include "P2PDataManager.h"
#include "../GameEngine/CodeBridge/CPPBridge.h"
#include "Global.h"
#include "Camera.h"
#include "ItemManager.h"
#include "ProjectileManager.h"
#include "Controls.h"
#include "Player.h"
#include "Menus/Menus.h"
#include "Preferences.h"
#include <string.h>

namespace SmashBros
{
	P2PDataManager::P2PEvents::P2PEvents()
	{
		//
	}
	
	P2PDataManager::P2PEvents::~P2PEvents()
	{
		//
	}
	
	void P2PDataManager::P2PEvents::peerDidConnect(String peerID)
	{
		needInfo = true;
		P2PDataManager::peerID = peerID;
	}
	
	void P2PDataManager::P2PEvents::peerDidDisconnect(String peerID)
	{
		Application::showMessage((String)"Peer " + P2PManager::getPeerDisplayName(peerID) + " disconnected");
		server = false;
		needInfo = true;
		P2PDataManager::peerID = "";
		enabled = false;
		P2PDataManager::peerDevice = "";
		dataQueue.clear();
		if(Menus::menuNo == MENU_P2PSTAGESELECT)
		{
			Global::UnloadGame();
			ScreenManager::GoToScreen("BrawlCharSelect");
			ScreenManager::GoToScreen("BluetoothMenu");
			ScreenManager::GoToScreen("MainMenu");
		}
		else
		{
			ScreenManager::GoToScreen("BluetoothMenu");
			ScreenManager::GoToScreen("MainMenu");
		}
	}
	
	void P2PDataManager::P2PEvents::peerDidRequestConnection(P2PRequest*request)
	{
		server = true;
	}
	
	void P2PDataManager::P2PEvents::pickerDidCancel()
	{
		server = false;
		needInfo = true;
		P2PDataManager::peerID = peerID;
	}
	
	void P2PDataManager::P2PEvents::didRecieveData(String peerID, void*data, unsigned int size)
	{
		DataVoid*recieved = new DataVoid(data,size);
		while(lockDataList);
		lockDataList = true;
		P2PDataManager::dataQueue.add(recieved);
		lockDataList = false;
	}
	
	boolean P2PDataManager::needInfo = true;
	boolean P2PDataManager::server = false;
	boolean P2PDataManager::enabled = false;
	String P2PDataManager::peerID = "";
	String P2PDataManager::peerDevice = "";
	boolean P2PDataManager::reliable = false;
	boolean P2PDataManager::errorstate = false;
	long P2PDataManager::lastRecieveTime = 0;
	
	boolean P2PDataManager::lockDataList = false;
	ArrayList<DataVoid*> P2PDataManager::dataQueue = ArrayList<DataVoid*>();
	P2PDataManager::P2PEvents* P2PDataManager::listener = NULL;
	
	boolean P2PDataManager::connectToPeers()
	{
		if(listener == NULL)
		{
			listener = new P2PEvents();
		}
		P2PManager::setEventListener(listener);
		needInfo = true;
		P2PManager::setSessionID("com.brokenphysics.issb");
		boolean result = P2PManager::searchForPeers();
		/*if(result)
		{
			char buffer[40];
			getDeviceModel(buffer);
			int length = strlen(buffer) + 1;
			P2PManager::sendData(buffer, length, P2PManager::SENDDATA_RELIABLE);
			while(needInfo)
			{
				SDL_Delay(30);
				updateAppEvents();
			}
		}*/
		return result;
	}
	
	boolean P2PDataManager::pollDataQueue(DataVoid*data)
	{
		while(lockDataList);
		lockDataList = true;
		if(dataQueue.size()>0)
		{
			DataVoid*poll = dataQueue.get(0);
			dataQueue.remove(0);
			data->setData(poll->getData(), poll->length());
			delete poll;
			lockDataList = false;
			return true;
		}
		else
		{
			lockDataList = false;
			return false;
		}
	}
	
	String P2PDataManager::getPeerDevice()
	{
		return peerDevice;
	}
	
	String P2PDataManager::getPeerID()
	{
		return peerID;
	}
	
	boolean P2PDataManager::isServer()
	{
		return server;
	}
	
	boolean P2PDataManager::isEnabled()
	{
		return enabled;
	}
	
	void P2PDataManager::setReliable()
	{
		reliable = true;
	}
	
	void P2PDataManager::setErrorState()
	{
		errorstate = true;
	}
	
	void P2PDataManager::toggleSetting(const String&setting, int value1)
	{
		if(P2PManager::isConnected())
		{
			if(setting.equals("item"))
			{
				DataVoid data;
				byte type = DATA_RULES;
				data.add(&type, sizeof(type));
				byte ruleType = RULES_ITEM;
				data.add(&ruleType, sizeof(ruleType));
				int index = value1;
				data.add(&index, sizeof(index));
				bool toggle = Global::itemsOn[index];
				data.add(&toggle, sizeof(toggle));
				P2PManager::sendData(data.getData(), data.length(), P2PManager::SENDDATA_RELIABLE);
			}
			else if(setting.equals("gameMode"))
			{
				DataVoid data;
				byte type = DATA_RULES;
				data.add(&type, sizeof(type));
				byte ruleType = RULES_MODE;
				data.add(&ruleType, sizeof(ruleType));
				int mode = Global::gameMode;
				data.add(&mode, sizeof(mode));
				P2PManager::sendData(data.getData(), data.length(), P2PManager::SENDDATA_RELIABLE);
			}
			else if(setting.equals("timeLimit"))
			{
				DataVoid data;
				byte type = DATA_RULES;
				data.add(&type, sizeof(type));
				byte ruleType = RULES_TIMELIMIT;
				data.add(&ruleType, sizeof(type));
				int timelimit = Global::timeLimit;
				data.add(&timelimit, sizeof(timelimit));
				P2PManager::sendData(data.getData(), data.length(), P2PManager::SENDDATA_RELIABLE);
			}
			else if(setting.equals("stockAmount"))
			{
				DataVoid data;
				byte type = DATA_RULES;
				data.add(&type, sizeof(type));
				byte ruleType = RULES_STOCK;
				data.add(&ruleType, sizeof(type));
				int stock = Global::stockAmount;
				data.add(&stock, sizeof(stock));
				P2PManager::sendData(data.getData(), data.length(), P2PManager::SENDDATA_RELIABLE);
			}
		}
	}
	
	void P2PDataManager::sendInitial()
	{
		DataVoid data;
		byte type = DATA_INITIAL;
		data.add(&type, sizeof(type));
		
		String version = Preferences::version;
		int length = version.length() + 1;
		data.add(&length, sizeof(length));
		data.add((char*)version, (unsigned int)length);

		auto deviceModel = getDeviceModel();
		length = deviceModel.length() + 1;
		data.add(&length, sizeof(length));
		data.add((const void*)deviceModel.c_str(), (unsigned int)length);
		
		for(int i=0; i<Global::totalItems; i++)
		{
			boolean item = Global::itemsOn[i];
			data.add(&item, sizeof(item));
		}
		data.add(&Global::gameMode, sizeof(Global::gameMode));
		data.add(&Global::stockAmount, sizeof(Global::stockAmount));
		data.add(&Global::timeLimit, sizeof(Global::timeLimit));
	}
	
	void P2PDataManager::updateGame(long gameTime)
	{
		if(P2PManager::isConnected())
		{
			DataVoid data;
			while(pollDataQueue(&data))
			{
				byte*dataBytes = (byte*)data.getData();
				switch(dataBytes[0])
				{
					case DATA_INITIAL:
					{
						dataBytes += sizeof(byte);
						
						int length = DataVoid::toInt(dataBytes);
						dataBytes += sizeof(int);
						
						String version = (char*)dataBytes;
						dataBytes += ((unsigned int)length);
						
						if(!version.equals(Preferences::version))
						{
							Game::showMessage("Warning!", "These two devices do not have the same version of iSSB! This may cause some problems. Please update.");
						}
						
						length = DataVoid::toInt(dataBytes);
						dataBytes += sizeof(int);
						
						char*deviceName = (char*)dataBytes;
						dataBytes += ((unsigned int)length);
						
						P2PDataManager::peerDevice = deviceName;
						needInfo = false;
						
						for(int i=0; i<Global::totalItems; i++)
						{
							boolean item = DataVoid::toBool(dataBytes);
							dataBytes += sizeof(byte);
							Global::itemsOn[i] = item;
						}
						Global::gameMode = DataVoid::toInt(dataBytes);
						dataBytes += sizeof(int);
						
						Global::stockAmount = DataVoid::toInt(dataBytes);
						dataBytes += sizeof(int);
						
						Global::timeLimit = DataVoid::toInt(dataBytes);
						dataBytes += sizeof(int);
					}
					break;
					
					case DATA_CHARSELECT:
					{
						dataBytes += sizeof(byte);
						int character = DataVoid::toInt(dataBytes);
						dataBytes += sizeof(int);
						
						Global::selectedChar[1] = character;
					}
					break;
					
					case DATA_RULES:
					{
						dataBytes += sizeof(byte);
						switch(dataBytes[0])
						{
							case RULES_MODE:
							{
								dataBytes += sizeof(byte);
								int mode = DataVoid::toInt(dataBytes);
								dataBytes += sizeof(int);
								
								Global::gameMode = mode;
							}
							break;
							
							case RULES_ITEM:
							{
								dataBytes += sizeof(byte);
								int index = DataVoid::toInt(dataBytes);
								dataBytes += sizeof(int);
								bool toggle = DataVoid::toBool(dataBytes);
								dataBytes += sizeof(bool);
								
								Global::itemsOn[index] = toggle;
							}
							break;
							
							case RULES_TIMELIMIT:
							{
								dataBytes += sizeof(byte);
								int timelimit = DataVoid::toInt(dataBytes);
								dataBytes += sizeof(int);
								
								Global::timeLimit = timelimit;
							}
							break;
							
							case RULES_STOCK:
							{
								dataBytes += sizeof(byte);
								int stock = DataVoid::toInt(dataBytes);
								dataBytes += sizeof(int);
								
								Global::stockAmount = stock;
							}
							break;
						}
					}
					break;
					
					case DATA_STARTGAME:
					{
						Global::P2PMessage += "Got start game message from peer...\n";
						dataBytes+=sizeof(byte);
						int stageNo = DataVoid::toInt(dataBytes);
						Global::stageVotes.add(stageNo);
						Global::peerReadyToPlay = true;
						
						if(Global::selfReadyToPlay && Global::peerReadyToPlay)
						{
							if(isServer())
							{
								Global::P2PMessage += "Preparing to send info to server...\n";
								serverHandleStart();
							}
						}
					}
					break;
					
					case DATA_SELECTSTAGE:
					{
						Global::P2PMessage += "Got selected stage from server... loading...\n";
						
						dataBytes+=sizeof(byte);
						int stageNo = DataVoid::toInt(dataBytes);
						Global::selectedStage = stageNo;
						Global::stageVotes.clear();
						
						Global::LoadGame();
						
						Global::characters[1]->switchDirection();
						Global::characters[2]->switchDirection();
						
						Global::selfLoaded = true;
						
						data.clear();
						byte type = DATA_LOADED;
						data.add(&type, sizeof(type));
						P2PManager::sendData(data.getData(), data.length(), P2PManager::SENDDATA_RELIABLE);
						
						Global::P2PMessage += "Got selected stage from server... loaded...\n";
					}
					break;
					
					case DATA_LOADED:
					{
						Global::peerLoaded = true;
						
						if(Global::selfLoaded && Global::peerLoaded)
						{
							handleLoaded();
						}
					}
					break;
					
					case DATA_READYGO:
					{
						dataBytes += sizeof(byte);
						
						byte readygoType = dataBytes[0];
						dataBytes += sizeof(byte);
						
						switch(readygoType)
						{
							case READYGO_GO:
							{
								Global::gamePlaying = true;
								Global::hud->startGameTime = 0;
								Global::hud->ReadyGo->changeAnimation("go", FORWARD);
							}
							break;
							
							case READYGO_GAME:
							{
								Global::finishBrawl();
							}
							break;
						}
					}
					break;
					
					case DATA_GAMEDATA:
					{
						dataBytes += sizeof(byte);
						
						//gameTime
						long time = DataVoid::toLong(dataBytes);
						dataBytes += sizeof(long);
						//if(time>=lastRecieveTime)
						{
							Game::setGameTime(time);
							lastRecieveTime = time;
							
							//worldTime
							long worldtime = DataVoid::toLong(dataBytes);
							dataBytes += sizeof(long);
							Global::worldTime = worldtime;
							
							//timeAmount
							long timeamount = DataVoid::toLong(dataBytes);
							dataBytes += sizeof(long);
							Global::timeAmount = timeamount;
							
							//characters
							Global::characters[2]->handleSetP2PData(dataBytes);
							Global::characters[1]->handleSetP2PData(dataBytes);
							
							//stage
							Global::currentStage->handleSetP2PData(dataBytes);
							
							//projectiles
							ProjectileManager::handleSetP2PData(dataBytes);
							if(errorstate)
							{
								return;
							}
							
							//items
							ItemManager::handleSetP2PData(dataBytes);
							if(errorstate)
							{
								return;
							}
							
							if(Global::gamePlaying)
							{
								Camera::Update();
							}
						}
					}
					break;
					
					case DATA_JOYSTICK:
					{
						dataBytes += sizeof(byte);
						Controls::handleP2PData(dataBytes);
					}
					break;
					
					case DATA_UPDATESCORE:
					{
						dataBytes += sizeof(byte);
						
						//playerNo
						byte playerNo = dataBytes[0];
						if(playerNo==1)
						{
							playerNo = 2;
						}
						else if(playerNo==2)
						{
							playerNo = 1;
						}
						dataBytes += sizeof(byte);
						
						//stock
						Global::characters[2]->stock = DataVoid::toInt(dataBytes);
						dataBytes += sizeof(int);
						Global::characters[1]->stock = DataVoid::toInt(dataBytes);
						dataBytes += sizeof(int);
						
						//scores
						Global::scores[2] = DataVoid::toInt(dataBytes);
						dataBytes += sizeof(int);
						Global::scores[1] = DataVoid::toInt(dataBytes);
						dataBytes += sizeof(int);
						
						//deaths
						Global::deaths[2] = DataVoid::toInt(dataBytes);
						dataBytes += sizeof(int);
						Global::deaths[1] = DataVoid::toInt(dataBytes);
						dataBytes += sizeof(int);
						
						//KOs
						Global::KOs[2] = DataVoid::toInt(dataBytes);
						dataBytes += sizeof(int);
						Global::KOs[1] = DataVoid::toInt(dataBytes);
						dataBytes += sizeof(int);
						
						//Winners
						int winner = DataVoid::toInt(dataBytes);
						dataBytes += sizeof(int);
						if(winner==1)
						{
							winner=2;
						}
						else if(winner==2)
						{
							winner=1;
						}
						Global::winners[1] = winner;
						winner = DataVoid::toInt(dataBytes);
						dataBytes += sizeof(int);
						if(winner==1)
						{
							winner=2;
						}
						else if(winner==2)
						{
							winner=1;
						}
						Global::winners[2] = winner;
						
						//bools
						bool wasHit = false;
						Global::suddenDeath = false;
						bool finishedGame = false;
						byte boolsByte = dataBytes[0];
						Bitset bools(boolsByte);
						if(bools.get(0))
						{
							wasHit = true;
						}
						if(bools.get(1))
						{
							Global::suddenDeath = true;
						}
						if(bools.get(2))
						{
							finishedGame = true;
						}
						dataBytes += sizeof(byte);
						
						//finish game time
						if(finishedGame)
						{
							Global::hud->showFinishGame = true;
						}
						
						if(wasHit)
						{
							Global::hud->showScore(playerNo, -1);
							if(playerNo==1)
							{
								Global::hud->showScore(2, 1);
							}
							else if(playerNo==2)
							{
								Global::hud->showScore(1, 1);
							}
						}
						else if(playerNo!=0)
						{
							Global::hud->showScore(playerNo, -1);
						}
						
						//sudden death players
						if(Global::suddenDeath)
						{
							Global::suddenDeathPlayers.clear();
							int total = DataVoid::toInt(dataBytes);
							dataBytes += sizeof(int);
							Console::WriteLine((String)"recieved sudden death players: " + total);
							for(int i=0; i<total; i++)
							{
								int playr = DataVoid::toInt(dataBytes);
								dataBytes += sizeof(int);
								Console::WriteLine((String)"player " + playr);
								if(playr==1)
								{
									playr=2;
								}
								else if(playr==2)
								{
									playr=1;
								}
								Global::suddenDeathPlayers.add(playr);
							}
						}
					}
					break;
				}
			}
		}
	}
	
	void P2PDataManager::sendGameData()
	{
		DataVoid data;
		
		byte type = DATA_GAMEDATA;
		data.add(&type, sizeof(type));
		
		//gameTime
		long gametime = Game::getGameTime();
		data.add(&gametime, sizeof(gametime));
		
		//worldTime
		long worldtime = Global::getWorldTime();
		data.add(&worldtime, sizeof(worldtime));
		
		//timeAmount
		long timeamount = Global::timeAmount;
		data.add(&timeamount, sizeof(timeamount));
		
		//characters
		Global::characters[1]->handleAddP2PData(data);
		Global::characters[2]->handleAddP2PData(data);
		
		//stage
		Global::currentStage->handleAddP2PData(data);
		
		//projectiles
		ProjectileManager::handleAddP2PData(data);
		
		//items
		ItemManager::handleAddP2PData(data);
		
		//if(reliable)
		{
			P2PManager::sendData(data.getData(), data.length(), P2PManager::SENDDATA_RELIABLE);
		}
		/*else
		{
			P2PManager::sendData(data.getData(), data.length(), P2PManager::SENDDATA_UNRELIABLE);
		}*/
		
		reliable = false;
	}
	
	void P2PDataManager::sendScore(Player*playr, bool finished)
	{
		DataVoid data;
		
		//type
		byte type = P2PDataManager::DATA_UPDATESCORE;
		data.add(&type, sizeof(type));
		
		//playerNo
		byte playerNo = 0;
		if(playr!=NULL)
		{
			playerNo = playr->getPlayerNo();
		}
		data.add(&playerNo, sizeof(playerNo));
		
		//stock
		data.add(&(Global::characters[1]->stock), sizeof(Global::characters[1]->stock));
		data.add(&(Global::characters[2]->stock), sizeof(Global::characters[2]->stock));
		
		//scores
		data.add(&Global::scores[1], sizeof(Global::scores[1]));
		data.add(&Global::scores[2], sizeof(Global::scores[2]));
		
		//deaths
		data.add(&Global::deaths[1], sizeof(Global::deaths[1]));
		data.add(&Global::deaths[2], sizeof(Global::deaths[2]));
		
		//KOs
		data.add(&Global::KOs[1], sizeof(Global::KOs[1]));
		data.add(&Global::KOs[2], sizeof(Global::KOs[2]));
		
		//Winners
		data.add(&Global::winners[1], sizeof(Global::winners[1]));
		data.add(&Global::winners[2], sizeof(Global::winners[2]));
		
		//bools
		bool wasHit = false;
		if(playr!=NULL)
		{
			if(playr->lastHit>0)
			{
				wasHit = true;
			}
		}
		
		Bitset bools;
		bools.set(0, wasHit);
		bools.set(1, Global::suddenDeath);
		bools.set(2, finished);
		
		byte boolsByte = bools.getByte();
		data.add(&boolsByte, sizeof(boolsByte));
		
		//sudden death players
		if(Global::suddenDeath)
		{
			int total = Global::suddenDeathPlayers.size();
			data.add(&total, sizeof(total));
			Console::WriteLine((String)"sudden death players: " + total);
			for(int i=0; i<total; i++)
			{
				int pNum = Global::suddenDeathPlayers.get(i);
				Console::WriteLine((String)"player " + pNum);
				data.add(&pNum, sizeof(pNum));
			}
		}
		
		P2PManager::sendData(data.getData(), data.length(), P2PManager::SENDDATA_RELIABLE);
	}
	
	void P2PDataManager::serverHandleStart()
	{
		Global::P2PMessage += "Selecting Stage...\n";
		
		int index = (int)(GameEngine::random()*2);
		int stageNo = Global::stageVotes.get(index);
		Global::selectedStage = stageNo;
		Global::stageVotes.clear();
		
		Global::P2PMessage += "Sending stage selection to peer...\n";
		
		DataVoid data;
		byte type = DATA_SELECTSTAGE;
		data.add(&type, sizeof(type));
		data.add(&stageNo, sizeof(stageNo));
		P2PManager::sendData(data.getData(), data.length(), P2PManager::SENDDATA_RELIABLE);
		
		Global::P2PMessage += "Loading Stage...\n";
		
		Global::LoadGame();
		
		if(Global::peerReadyToPlay)
		{
			Global::P2PMessage += "Loaded Stage... Waiting for Peer to load...\n";
		}
		else
		{
			Global::P2PMessage += "Loaded Stage... Waiting for Peer to be ready...\n";
		}
		
		Global::selfLoaded = true;
		
		data.clear();
		type = DATA_LOADED;
		data.add(&type, sizeof(type));
		P2PManager::sendData(data.getData(), data.length(), P2PManager::SENDDATA_RELIABLE);
		
		Global::selfReadyToPlay = false;
		Global::peerReadyToPlay = false;
	}
	
	void P2PDataManager::handleLoaded()
	{
		Global::P2PMessage += "Going to Stage...\n";
		
		ScreenManager::GoToScreen("Game");
		
		Global::selfLoaded = false;
		Global::peerLoaded = false;
	}
}