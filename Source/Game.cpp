
#include "Game.h"
#include "SmashBros/Preferences.h"
#include "SmashBros/Controls.h"
#include "SmashBros/Menus/Menus.h"
#include "SmashBros/Game/GameScreen.h"

namespace SmashBros
{
	Game::Game()
	{
		//Constructor
		View::setSize(900,600);
		firstUpdate = true;
		drawnOnce = false;
	}
	
	Game::~Game()
	{
		//
	}
	
	void Game::Initialize()
	{
		/*Font* font = new Font("Fonts/arial.ttf",Font::PLAIN,16);
		SDL_Color color;
		color.r = 255;
		color.g = 255;
		color.b = 255;
		color.a = 255;

		SDL_Color bgcolor;
		bgcolor.r = 0;
		bgcolor.g = 0;
		bgcolor.b = 0;
		bgcolor.a = 0;

		SDL_Surface* surface = TTF_RenderGlyph_Shaded(font->getTTF(), 'H', color, bgcolor);
		Console::WriteLine((String)"H: " + surface->w + ", " + surface->h);
		SDL_FreeSurface(surface);
		surface = TTF_RenderGlyph_Shaded(font->getTTF(), 'y', color, bgcolor);
		Console::WriteLine((String)"y: " + surface->w + ", " + surface->h);
		SDL_FreeSurface(surface);
		surface = TTF_RenderGlyph_Shaded(font->getTTF(), 'r', color, bgcolor);
		Console::WriteLine((String)"r: " + surface->w + ", " + surface->h);
		SDL_FreeSurface(surface);
		surface = TTF_RenderGlyph_Shaded(font->getTTF(), '.', color, bgcolor);
		Console::WriteLine((String)".: " + surface->w + ", " + surface->h);
		SDL_FreeSurface(surface);*/

		//Initialize things
		scaleToWindow(true,900,600);

		AssetManager::loadImage("Images/icon.png");
		setLoadScreen("Images/loading.png");
		
		Global::init();
		
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
		//Load Things
		Controls::loadControls();
		Preferences::init();
		Preferences::load();

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
				Game::showMessage((String)"iSSB "+Preferences::version, Preferences::versionMessage);
			}
			firstUpdate = false;
		}
		if(getKeyPressed(Keys::ESCAPE) && !getPrevKeyPressed(Keys::ESCAPE))
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
