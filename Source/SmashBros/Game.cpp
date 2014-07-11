
#include "Game.h"
#include "Preferences.h"
#include "Controls.h"
#include "Menus/Menus.h"
#include "Game/GameScreen.h"

namespace SmashBros
{
	Game::Game()
	{
		//Constructor
		firstUpdate = true;
		drawnOnce = false;
	}

	Game::~Game()
	{
		//
	}

	void Game::Initialize()
	{
		//Initialize things
		scaleToWindow(true,900,600);
		
		Global::init();
		Controls::loadControls();
		Preferences::init();
		Preferences::load();
		
		AssetManager::loadImage("Images/icon.png");
		setLoadScreen("Images/loading.png");
		
		showRealFPS(true);
		if(Preferences::highFPS())
		{
			setFPS(60);
			setUpdatesPerFrame(1);
		}
		else
		{
			setFPS(30);
			setUpdatesPerFrame(2);
		}
		//setWindowTitle("Super Smash Bros.");
	}

	void Game::LoadContent()
	{
		bool thingy = true;
		Console::WriteLine((byte)thingy);
		//Load Things
		Menus::loadAssets();
		Menus::loadMenus();
		ScreenManager::Add(new GameScreen("Game"));
		ScreenManager::GoToScreen("TitleScreen");
		if(Preferences::debuglog)
		{
			Console::OutputToFile(true, "iSSB.log");
		}
	}

	void Game::UnloadContent()
	{
		//
	}
	
	void Game::Update(long gameTime)
	{
		if(firstUpdate && drawnOnce)
		{
			if(Preferences::newVersion)
			{
				Preferences::newVersion = false;
				Game::showMessage("Attention!", Preferences::versionMessage);
			}
			firstUpdate = false;
		}
		if(KeyPressed(Keys::ESCAPE) && !PrevKeyPressed(Keys::ESCAPE))
		{
			Exit();
		}
		ScreenManager::Update(gameTime);
	}

	void Game::Draw(Graphics2D& g, long gameTime)
	{
		ScreenManager::Draw(g, gameTime);
		drawnOnce = true;
	}
}