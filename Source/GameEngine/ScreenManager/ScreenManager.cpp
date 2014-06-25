
#include "ScreenManager.h"
#include "../Output/Console.h"
#include "../View.h"

namespace GameEngine
{
	ArrayList<Screen*> ScreenManager::screens = ArrayList<Screen*>();
	int ScreenManager::totalScreens = 0;
	int ScreenManager::currentScreen = -1;

	void ScreenManager::Add(Screen*s)
	{
		s->Initialize();
		screens.add(s);
		totalScreens++;
	}

	bool ScreenManager::Remove(String s)
	{
		for(int i=(totalScreens-1); i>=0; i--)
        {
            String scr = (screens.get(i))->name;
            if(scr.equals(s))
            {
                screens.remove(i);
                totalScreens--;
                if(currentScreen>=i)
                {
                	currentScreen--;
                	if(totalScreens==0)
                	{
                		currentScreen=-1;
                	}
                }
                return true;
            }
        }
        Console::WriteLine((String)"Error ScreenManager::Remove(): screen " + s + (String)"does not exist!");
        return false;
	}

	bool ScreenManager::GoToScreen(String s)
	{
		for(int i=0; i<totalScreens; i++)
        {
            String scr = (screens.get(i))->name;
            if(scr.equals(s))
            {
                if(currentScreen!=-1)
                {
                    screens.get(currentScreen)->UnloadContent();
                }
                currentScreen = i;
				View::x = 0;
                View::y = 0;
                screens.get(i)->LoadContent();
                return true;
            }
        }
        Console::WriteLine((String)"Error ScreenManager::GoToScreen(): screen " + s + (String)" does not exist!");
        return false;
	}

	void ScreenManager::Update(long gameTime)
	{
    	if(currentScreen!=-1)
    	{
        	screens.get(currentScreen)->Update(gameTime);
    	}
	}

	void ScreenManager::Draw(Graphics2D& g,long gameTime)
	{
		if(currentScreen!=-1)
    	{
        	screens.get(currentScreen)->Draw(g,gameTime);
    	}
	}
}