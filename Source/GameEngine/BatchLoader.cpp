
#include "BatchLoader.h"
#include "Application.h"
#include "AssetManager.h"
#include "Output/Console.h"

namespace GameEngine
{
	ArrayList<String> BatchLoader::Images = ArrayList<String>();
	ArrayList<String> BatchLoader::Fonts = ArrayList<String>();
	
	int BatchLoader::totalAmount = 0;
	
	void BatchLoader::addImage(String n)
	{
		Images.add(n);
		totalAmount++;
	}
	
	void BatchLoader::addFont(String n)
	{
    	Fonts.add(n);
    	totalAmount++;
	}
	
	void BatchLoader::loadAll()
	{
    	Application::setLoadTotal((float)totalAmount);
		for(int i=0; i<Images.size(); i++)
		{
			AssetManager::loadImage(Images.get(i));
			Application::incrementLoad(1);
			if(Application::closing)
			{
				return;
			}
		}
		for(int i=0; i<Fonts.size(); i++)
		{
        	AssetManager::loadFont(Fonts.get(i));
        	Application::incrementLoad(1);
			if(Application::closing)
			{
				return;
			}
		}
		Images.clear();
		Fonts.clear();
	}
	
	LoadThread::LoadThread(Application*app)
	{
		this->app = app;
	}
	
	LoadThread::~LoadThread()
	{
		app = NULL;
	}
	
	void LoadThread::run()
	{
		app->LoadContent();
	}
}