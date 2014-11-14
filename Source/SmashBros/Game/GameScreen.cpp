
#include "GameScreen.h"
#include "../Global.h"
#include "../Camera.h"
#include "../Controls.h"
#include "../Preferences.h"
#include "../Menus/Menus.h"
#include "../P2PDataManager.h"

namespace SmashBros
{
	GameScreen::GameScreen(const String&name) : Screen(name)
	{
		prevEnterPressed = false;
		firstUpdate = true;
		sendFrame = true;
	}
	
	GameScreen::~GameScreen()
	{
		delete Global::hud;
		Global::hud = null;
	}

	void GameScreen::Initialize()
	{
		//
	}
	
	void GameScreen::LoadContent()
	{
		Global::createHUD();
		Game::showBackground(false);
		Camera::Update();
		sendFrame = true;
		if(Preferences::ingameMusicOn())
		{
			MusicManager::play();
		}
		P2PDataManager::lastRecieveTime = 0;
	}
	
	void GameScreen::UnloadContent()
	{
		MusicManager::stop();
	}
	
	void GameScreen::Update(long gameTime)
	{
		if(P2PDataManager::isEnabled() && P2PDataManager::isServer())
		{
			P2PDataManager::updateGame(gameTime);
			if(P2PDataManager::errorstate)
			{
				P2PDataManager::errorstate = false;
				//P2PDataManager::dataQueue.clear();
				//Global::UnloadGame();
				//ScreenManager::GoToScreen("BrawlCharSelect");
				//ScreenManager::GoToScreen("BluetoothMenu");
				P2PManager::endSession();
				return;
			}
		}
		if((P2PDataManager::isEnabled() && (P2PDataManager::isServer() || (!P2PDataManager::isServer() && firstUpdate)))
		   || !P2PDataManager::isEnabled())
		{
			Global::Update(gameTime);
			
			if(Global::currentStage!=null)
			{
				Global::currentStage->Update(gameTime);
			}
			if(Global::currentStage!=null)
			{
				Camera::Update();
			}
			if(Global::hud!=null)
			{
				Global::hud->Update(gameTime);
			}
			if(Global::gamePlaying)
			{
				Controls::Update(gameTime);
			}
		}
		else if(P2PDataManager::isEnabled() && !P2PDataManager::isServer())
		{
			if(Global::gamePlaying)
			{
				Controls::Update(gameTime);
			}
		}
		firstUpdate = false;
	}
	
	void GameScreen::Draw(Graphics2D&g, long gameTime)
	{
		if(P2PDataManager::isEnabled())
		{
			if(P2PDataManager::isServer())
			{
				if(Preferences::highFPS())
				{
					if(sendFrame)
					{
						P2PDataManager::sendGameData();
						sendFrame = false;
					}
					else
					{
						sendFrame = true;
					}
				}
				else
				{
					P2PDataManager::sendGameData();
				}
			}
			else
			{
				P2PDataManager::updateGame(gameTime);
				if(P2PDataManager::errorstate)
				{
					P2PDataManager::errorstate = false;
					//P2PDataManager::dataQueue.clear();
					//Global::UnloadGame();
					//ScreenManager::GoToScreen("BrawlCharSelect");
					//ScreenManager::GoToScreen("BluetoothMenu");
					P2PManager::endSession();
					return;
				}
			}
		}
		if(Global::currentStage!=null)
		{
			if(Game::getKeyPressed(Keys::ENTER) && !prevEnterPressed)
			{
				if(Game::Suspended())
				{
					Console::WriteLine("resumed");
					Game::Resume();
				}
				else if(Global::gamePlaying)
				{
					Console::WriteLine("paused");
					Game::Suspend();
				}
				prevEnterPressed = true;
			}
			else if(!Game::getKeyPressed(Keys::ENTER))
			{
				prevEnterPressed = false;
			}
			Global::currentStage->Draw(g, gameTime);
			if(Global::hud!=null)
			{
				Global::hud->Draw(g, gameTime);
			}
		}
	}
}