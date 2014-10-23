
#include "Application.h"
#include "AssetManager.h"
#include "Output/Console.h"
#include "View.h"
#include <time.h>
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "Input/Keys.h"
#include "Sound/Sound.h"
#include "Sound/Music.h"
#include "ObjCBridge/ObjCBridge.h"

namespace GameEngine
{
	int ApplicationEventHandler(void*userdata, SDL_Event*event)
	{
		switch(event->type)
		{
			case SDL_APP_WILLENTERBACKGROUND:
			{
				if(Application::appEventListener != NULL)
				{
					Application::appEventListener->onAppWillEnterBackground();
				}
			}
			break;
			
			case SDL_APP_DIDENTERBACKGROUND:
			{
				if(Application::appEventListener != NULL)
				{
					Application::appEventListener->onAppDidEnterBackground();
				}
				Application::minimizing = true;
			}
			break;
			
			case SDL_APP_WILLENTERFOREGROUND:
			{
				if(Application::appEventListener != NULL)
				{
					Application::appEventListener->onAppWillEnterForeground();
				}
			}
			break;
			
			case SDL_APP_DIDENTERFOREGROUND:
			{
				if(Application::appEventListener != NULL)
				{
					Application::appEventListener->onAppDidEnterForeground();
				}
				Application::minimizing = false;
				Application::readyToMinimize = false;
			}
			break;
			
			case SDL_APP_TERMINATING:
			{
				if(Application::appEventListener != NULL)
				{
					Application::appEventListener->onAppTerminating();
				}
			}
			break;
			
			case SDL_APP_LOWMEMORY:
			{
				if(Application::appEventListener != NULL)
				{
					Application::appEventListener->onLowMemory();
				}
			}
			break;
		}
		
		return 1;
	}
	
	SDL_Window*Application::window = NULL;
	SDL_Renderer*Application::renderer = NULL;
	Application*Application::game = NULL;
	ApplicationEventListener*Application::appEventListener = NULL;
	LoadThread*Application::loadThread = NULL;
	bool Application::loaded = false;
	bool Application::exiting = false;
	long Application::worldTime = 0;
	long Application::frame = 0;
	int Application::upf = 1;
	int Application::sleepTime = 33;
	bool Application::paused = false;
	bool Application::closing = false;
	Graphics2D*Application::graphics = NULL;
	long Application::realFPS = 0;
	bool Application::showfps = false;
	long Application::lastFrame = 0;
	long Application::firstFrame = 0;
	long Application::lastFrameTime = 0;
	bool Application::gameRunning = false;
	bool Application::borderless = false;
	bool Application::scalescreen = false;
	unsigned char Application::orientation = Application::ORIENTATION_LANDSCAPE;
	bool Application::updating = false;
	
	bool Application::bgVisible = false;
	String Application::bgName = "";
	bool Application::showLoad = false;
	float Application::loadbarDim[4];
	Color Application::loadbarColor = Color::BLACK;
	BufferedImage*Application::loadImage = NULL;
	float Application::loadTotal = 1;
	float Application::loadCurrent = 0;
	
	Color Application::bgColor = Color::WHITE;
	
	int Application::lastKey = -1;
	int Application::currentLastKey = -1;
	ArrayList<TouchPoint> Application::touchPoints = ArrayList<TouchPoint>();
	ArrayList<TouchPoint> Application::currentTouchPoints = ArrayList<TouchPoint>();
	ArrayList<TouchPoint> Application::prevTouchPoints = ArrayList<TouchPoint>();
	bool Application::KeyState[526];
	bool Application::currentKeyState[526];
	bool Application::prevKeyState[526];
	
	bool Application::minimizing = false;
	bool Application::readyToMinimize = false;
	
	Application::Application() {}
	Application::~Application() {}
	
	void Application::Initialize() {}
	void Application::LoadContent() {}
	void Application::UnloadContent() {}
	void Application::Update(long gameTime) {}
	void Application::Draw(Graphics2D&g, long gameTime) {}
	
	void Application::onSuspend() {}
	void Application::onResume() {}
	
	bool Application::Run(unsigned char orient, bool statusbar)
	{
		if(!gameRunning)
		{
			gameRunning = true;
			
			srand((unsigned)time(NULL));
			
			if(!SDL_WasInit(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_JOYSTICK | SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER))
			{
				if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_JOYSTICK | SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER) < 0)
				//if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
				{
					Console::WriteLine("failed to initialize SDL");
					gameRunning = false;
					return false;
				}
			}
			
			if(!TTF_WasInit())
			{
				if(TTF_Init() < 0)
				{
					Console::WriteLine("failed to initalize SDL_ttf library");
					gameRunning = false;
					return false;
				}
			}
			
			{
				int flags = MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_MOD | MIX_INIT_OGG;
				Mix_Init(flags);
			}
			
			if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096)<0)
			{
				Console::WriteLine("failed to open SDL_mixer Audio");
			}
			
			Sound::init();
			Music::init();
			
			GameEngine_init();
			
			{
				SDL_Rect displayRect;
				
				SDL_GetDisplayBounds(0, &displayRect);
				
				unsigned int bigger;
				unsigned int smaller;
				
				if(displayRect.w > displayRect.h)
				{
					bigger = displayRect.w;
					smaller = displayRect.h;
				}
				else
				{
					bigger = displayRect.h;
					smaller = displayRect.w;
				}
				
				if(orient == ORIENTATION_PORTRAIT)
				{
					View::windowWidth = smaller;
					View::windowHeight = bigger;
					View::scaleWidth = smaller;
					View::scaleHeight = bigger;
				}
				else if(orient == ORIENTATION_LANDSCAPE)
				{
					View::windowWidth = bigger;
					View::windowHeight = smaller;
					View::scaleWidth = bigger;
					View::scaleHeight = smaller;
				}
				
				orientation = orient;
				if(statusbar)
				{
					borderless = false;
				}
				else
				{
					borderless = true;
				}
			}
			
			if(borderless)
			{
				window = SDL_CreateWindow(NULL, 0, 0, View::windowWidth, View::windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS | SDL_WINDOW_SHOWN);
			}
			else
			{
				window = SDL_CreateWindow(NULL, 0, 0, View::windowWidth, View::windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
			}
			
			if(window == NULL)
			{
				Console::WriteLine("failed to create SDL_Window");
				gameRunning = false;
				return false;
			}
			
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			
			if(renderer == NULL)
			{
				Console::WriteLine("failed to create SDL_Renderer from SDL_Window");
				gameRunning = false;
				return false;
			}
			
			if(orientation == ORIENTATION_PORTRAIT)
			{
				SDL_SetHintWithPriority("SDL_HINT_ORIENTATIONS", "Portrait PortraitUpsideDown", SDL_HINT_OVERRIDE);
			}
			else if(orientation == ORIENTATION_LANDSCAPE)
			{
				SDL_SetHintWithPriority("SDL_HINT_ORIENTATIONS", "LandscapeLeft LandscapeRight", SDL_HINT_OVERRIDE);
			}
			
			SDL_SetEventFilter(ApplicationEventHandler, this);
			
			game = this;
			
			this->Initialize();
			
			graphics = new Graphics2D();
			graphics->renderer = renderer;
			
			lastFrameTime = getUptimeMillis();
			
			while(gameRunning && !closing)
			{
				lastFrame = getUptimeMillis();
				int timeDif = lastFrame-firstFrame;
				if(timeDif==0)
				{
					realFPS = 0;
				}
				else
				{
					realFPS = (1000/timeDif);
				}
				firstFrame = getUptimeMillis();
				
				if(loaded)
				{
					long startTime = getUptimeMillis();
					updateEvents();
					if(!closing)
					{
						updateKeys(currentKeyState, KeyState);
						updateTouchPoints(currentTouchPoints, touchPoints);
						currentLastKey = lastKey;
						lastKey = -1;
						
						if(!paused)
						{
							if(upf>1)
							{
								for(int i=0; i<upf; i++)
								{
									if(i!=0)
									{
										updateKeys(prevKeyState,currentKeyState);
										updateTouchPoints(prevTouchPoints, currentTouchPoints);
										
										updateKeys(currentKeyState, KeyState);
										updateTouchPoints(currentTouchPoints, touchPoints);
										currentLastKey = lastKey;
										lastKey = -1;
									}
									this->Update(worldTime);
									if(paused)
									{
										i = upf;
									}
								}
							}
							else
							{
								this->Update(worldTime);
							}
						}
						
						SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
						SDL_RenderClear(renderer);
						SDL_SetRenderDrawColor(renderer, 0,0,0,255);
						
						graphics->reset();
						graphics->updateStringCache();
						View::Update(*graphics);
						if(bgVisible)
						{
							BufferedImage*img = AssetManager::getImage(bgName);
							graphics->drawImage(img,0,0,(float)View::ScaleWidth(),(float)View::ScaleHeight(),0,0,img->getWidth(),img->getHeight());
						}
						this->Draw(*graphics,worldTime);
						if(!paused)
						{
							updateKeys(prevKeyState,currentKeyState);
							updateTouchPoints(prevTouchPoints, currentTouchPoints);
						}
						View::Draw(*graphics);
						SDL_RenderPresent(renderer);
						
						long currentFrameTime = getUptimeMillis();
						if(!paused)
						{
							frame++;
							//worldTime+=sleepTime;
							worldTime += (currentFrameTime - lastFrameTime);
						}
						lastFrameTime = currentFrameTime;
						
						long endTime = getUptimeMillis();
						long newSleepTime = sleepTime - (endTime - startTime);
						
						//Console::WriteLine(endTime-startTime);
						
						if(newSleepTime>0)
						{
							bool firstSleep = true;
							do
							{
								if(!firstSleep)
								{
									updateEvents();
									lastFrameTime = getUptimeMillis();
								}
								firstSleep = false;
								readyToMinimize = true;
								SDL_Delay(newSleepTime);
							}
							while(minimizing);
							readyToMinimize = false;
						}
						else
						{
							SDL_Delay(1);
						}
					}
				}
				else
				{
					updateEvents();
					View::Update(*graphics);
					/*if(loadThread==NULL)
					{
						loadThread = new LoadThread(this);
						loadThread->start();
					}*/
					
					if(showLoad)
					{
						SDL_SetRenderDrawColor(renderer, 0,0,0,255);
						SDL_RenderClear(renderer);
						graphics->drawImage(loadImage,0,0,(float)View::ScaleWidth(),(float)View::ScaleHeight(),0,0,loadImage->getWidth(),loadImage->getHeight());
						graphics->setColor(loadbarColor);
						graphics->fillRect(loadbarDim[0], loadbarDim[1], (float)((float)(loadCurrent/loadTotal)*loadbarDim[2]), loadbarDim[3]);
						SDL_RenderPresent(renderer);
					}
					else
					{
						SDL_SetRenderDrawColor(renderer, bgColor.r,bgColor.g,bgColor.b,bgColor.a);
						SDL_RenderClear(renderer);
						SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
						SDL_RenderPresent(renderer);
					}
					
					/*if(!loadThread->isAlive())
					{
						loaded = true;
						delete loadThread;
						loadThread = NULL;
					}*/
					LoadContent();
					loaded = true;
					lastFrameTime = getUptimeMillis();
				}
				
				if(exiting)
				{
					UnloadContent();
					closing = true;
				}
			}
			
			delete graphics;
			if(renderer!=NULL)
			{
				SDL_DestroyRenderer(renderer);
				renderer = NULL;
			}
			if(window!=NULL)
			{
				SDL_DestroyWindow(window);
				window = NULL;
			}
			
			gameRunning = false;
			
			SDL_Quit();
			
			return true;
		}
		return false;
	}
		
	void Application::updateEvents()
	{
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
				this->UnloadContent();
				graphics->renderer = NULL;
				SDL_DestroyRenderer(renderer);
				renderer = NULL;
				SDL_DestroyWindow(window);
				window = NULL;
				closing = true;
				break;
				
				case SDL_APP_WILLENTERBACKGROUND:
				Mix_PauseMusic();
				break;
				
				case SDL_APP_DIDENTERFOREGROUND:
				Mix_ResumeMusic();
				break;
				
				case SDL_KEYDOWN:
				keyPressed(Keys::SDLK_to_KeyCode(event.key.keysym.sym));
				break;
				
				case SDL_KEYUP:
				keyReleased(Keys::SDLK_to_KeyCode(event.key.keysym.sym));
				break;
				
				case SDL_FINGERDOWN:
				addTouchPoint(event.tfinger.fingerId, (event.tfinger.x*View::windowWidth), (event.tfinger.y*View::windowHeight));
				break;
				
				case SDL_FINGERMOTION:
				updateTouchPoint(event.tfinger.fingerId, (event.tfinger.x*View::windowWidth), (event.tfinger.y*View::windowHeight));
				break;
				
				case SDL_FINGERUP:
				removeTouchPoint(event.tfinger.fingerId, (event.tfinger.x*View::windowWidth), (event.tfinger.y*View::windowHeight));
				break;
			}
        }
		SDL_JoystickUpdate();
	}
	
	void Application::Exit()
	{
		exiting = true;
	}
	
	void Application::showMessage(const String&message)
	{
		//SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "", message, window);
		SDL_ShowSimpleMessageBoxFixed("", message);
	}
	
	void Application::showMessage(const String&title, const String&message)
	{
		//SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, title, message, window);
		SDL_ShowSimpleMessageBoxFixed("", message);
	}
	
	int Application::showMessage(const String&title, const String&message, const ArrayList<String>&options)
	{
		/*SDL_MessageBoxButtonData*buttons = new SDL_MessageBoxButtonData[options.size()];
		for(int i=0; i<options.size(); i++)
		{
			SDL_MessageBoxButtonData button = {0, i, (char*)options.get(i)};
			buttons[i] = button;
		}
		SDL_MessageBoxData messageBoxData = {SDL_MESSAGEBOX_INFORMATION, window, (char*)title, (char*)message, options.size(), buttons, NULL};
		int buttonid = 0;
		SDL_ShowMessageBox(&messageBoxData, &buttonid);
		delete[] buttons;
		return buttonid;*/
		
		char**buttons = new char*[options.size()];
		for(int i=0; i<options.size(); i++)
		{
			buttons[i] = (char*)options.get(i);
		}
		int result = SDL_ShowMessageBoxFixed((char*)title, (char*)message, (const char**)buttons, options.size());
		delete[] buttons;
		return result;
	}
	
	int Application::GetLastKey()
	{
		return currentLastKey;
	}
	
	bool Application::KeyPressed(int key) //check if a key is pressed
	{
		return currentKeyState[key];
	}
	
	bool Application::PrevKeyPressed(int key) //check if a key was pressed in the last frame
	{
		return prevKeyState[key];
	}
	
	int Application::TouchX(long touchID)
	{
		TouchPoint*point = getTouchPoint(touchID);
		if(point==NULL)
		{
			return 0;
		}
		else if(scalescreen)
		{
			return (int)((point->x/View::multScale) - View::letterBoxW*(1/View::multScale));
		}
		else
		{
			return point->x;
		}
	}
	
	int Application::PrevTouchX(long touchID)
	{
		TouchPoint*point = getPrevTouchPoint(touchID);
		if(point==NULL)
		{
			return 0;
		}
		else if(scalescreen)
		{
			return (int)((point->x/View::multScale) - View::letterBoxW*(1/View::multScale));
		}
		else
		{
			return point->x;
		}
	}
	
	int Application::TouchY(long touchID)
	{
		TouchPoint*point = getTouchPoint(touchID);
		if(point==NULL)
		{
			return 0;
		}
		else if(scalescreen)
		{
			return (int)((point->y/View::multScale) - View::letterBoxH*(1/View::multScale));
		}
		else
		{
			return point->y;
		}
	}
	
	int Application::PrevTouchY(long touchID)
	{
		TouchPoint*point = getPrevTouchPoint(touchID);
		if(point==NULL)
		{
			return 0;
		}
		else if(scalescreen)
		{
			return (int)((point->y/View::multScale) - View::letterBoxH*(1/View::multScale));
		}
		else
		{
			return point->y;
		}
	}
	
	bool Application::checkTouchActive(long touchID)
	{
		for(int i=0; i<currentTouchPoints.size(); i++)
		{
			if(currentTouchPoints.get(i).ID == touchID)
			{
				return true;
			}
		}
		return false;
	}
	
	bool Application::checkPrevTouchActive(long touchID)
	{
		for(int i=0; i<prevTouchPoints.size(); i++)
		{
			if(prevTouchPoints.get(i).ID == touchID)
			{
				return true;
			}
		}
		return false;
	}
	
	ArrayList<TouchPoint> Application::getTouchPoints()
	{
		if(scalescreen)
		{
			ArrayList<TouchPoint> points;
			
			for(int i=0; i<currentTouchPoints.size(); i++)
			{
				TouchPoint point = currentTouchPoints.get(i);
				point.x = (float)((point.x/View::multScale) - View::letterBoxW*(1/View::multScale));
				point.y = (float)((point.y/View::multScale) - View::letterBoxH*(1/View::multScale));
				points.add(point);
			}
			return points;
		}
		else
		{
			return currentTouchPoints;
		}

	}
	
	ArrayList<TouchPoint> Application::getPrevTouchPoints()
	{
		if(scalescreen)
		{
			ArrayList<TouchPoint> points;
			
			for(int i=0; i<prevTouchPoints.size(); i++)
			{
				TouchPoint point = prevTouchPoints.get(i);
				point.x = (float)((point.x/View::multScale) - View::letterBoxW*(1/View::multScale));
				point.y = (float)((point.y/View::multScale) - View::letterBoxH*(1/View::multScale));
				points.add(point);
			}
			return points;
		}
		else
		{
			return prevTouchPoints;
		}
	}
	
	void Application::keyPressed(int keycode)
	{
		if(keycode!=0)
		{
			KeyState[keycode] = true;
			lastKey = keycode;
		}
	}
	
	void Application::keyReleased(int keycode)
	{
		if(keycode!=0)
		{
			KeyState[keycode] = false;
		}
	}
	
	void Application::addTouchPoint(long givenID, float x, float y)
	{
		long touchID = TouchPoint_currentID;
		
		TouchPoint_currentID++;
		if(TouchPoint_currentID>10000)
		{
			TouchPoint_currentID = 0;
		}
		
		bool exists = false;
		
		do
		{
			exists = false;
			
			for(int i=0; i<touchPoints.size(); i++)
			{
				if(touchPoints.get(i).ID == TouchPoint_currentID)
				{
					exists = true;
					i=touchPoints.size();
				}
			}
			
			if(!exists)
			{
				for(int i=0; i<currentTouchPoints.size(); i++)
				{
					if(currentTouchPoints.get(i).ID == TouchPoint_currentID)
					{
						exists = true;
						i=currentTouchPoints.size();
					}
				}
			}
			
			if(!exists)
			{
				for(int i=0; i<prevTouchPoints.size(); i++)
				{
					if(prevTouchPoints.get(i).ID == TouchPoint_currentID)
					{
						exists = true;
						i=prevTouchPoints.size();
					}
				}
			}
			
			if(exists)
			{
				TouchPoint_currentID++;
				if(TouchPoint_currentID>10000)
				{
					TouchPoint_currentID = 0;
				}
			}
		}
		while(exists);
		
		touchPoints.add(createTouchPoint(touchID, givenID, x, y));
	}
	
	void Application::updateTouchPoint(long givenID, float x, float y)
	{
		for(int i=0; i<touchPoints.size(); i++)
		{
			TouchPoint point = touchPoints.get(i);
			if(point.givenID == givenID)
			{
				point.x = x;
				point.y = y;
				touchPoints.set(i, point);
				return;
			}
		}
	}
	
	void Application::removeTouchPoint(long givenID, float x, float y)
	{
		for(int i=0; i<touchPoints.size(); i++)
		{
			TouchPoint&point = touchPoints.get(i);
			if(point.givenID == givenID)
			{
				touchPoints.remove(i);
				return;
			}
		}
	}
	
	TouchPoint*Application::getTouchPoint(long ID)
	{
		for(int i=0; i<currentTouchPoints.size(); i++)
		{
			TouchPoint*point = &currentTouchPoints[i];
			if(point->ID == ID)
			{
				return point;
			}
		}
		return NULL;
	}
	
	TouchPoint*Application::getPrevTouchPoint(long ID)
	{
		for(int i=0; i<prevTouchPoints.size(); i++)
		{
			TouchPoint*point = &prevTouchPoints[i];
			if(point->ID == ID)
			{
				return point;
			}
		}
		return NULL;
	}
	
	void Application::updateKeys(bool*keys1, bool*keys2)
	{
		for(int i=0; i<totalKeys; i++)
		{
			keys1[i]=keys2[i];
		}
	}
	
	void Application::updateTouchPoints(ArrayList<TouchPoint>&points1, ArrayList<TouchPoint>&points2)
	{
		points1.clear();
		for(int i=0; i<points2.size(); i++)
		{
			points1.add(points2.get(i));
		}
	}
	
	void Application::setUpdatesPerFrame(int total)
	{
		if(total>=1)
		{
			upf = total;
		}
	}
	
	long Application::getFrame()
	{
		return frame;
	}
	
	SDL_Window*Application::getWindow()
	{
		return window;
	}
	
	void Application::setFPS(int fps)
	{
		sleepTime = 1000/fps;
	}
	
	void Application::showRealFPS(bool toggle)
	{
		showfps = toggle;
	}
	
	bool Application::colcompare(Color c1, Color c2)
	{
		if(c1.r==c2.r && c1.g==c2.g && c1.b==c2.b && c1.a==c1.a)
		{
			return true;
		}
		return false;
	}
	
	long Application::getGameTime()
	{
		return worldTime;
	}
	
	long Application::getSystemTime()
	{
		return getUptimeMillis();
	}
	
	void Application::setGameTime(long time)
	{
		worldTime = time;
	}
	
	void Application::Suspend()
	{
		paused = true;
		game->onSuspend();
	}
	
	void Application::Resume()
	{
		paused = false;
		game->onResume();
	}
	
	bool Application::Suspended()
	{
		return paused;
	}
	
	void Application::scaleToWindow(bool toggle)
	{
		scalescreen=toggle;
		View::scaleWidth = View::windowWidth;
		View::scaleHeight = View::windowHeight;
	}
	
	void Application::scaleToWindow(bool toggle, int width, int height)
	{
		scalescreen=toggle;
		View::scaleWidth = width;
		View::scaleHeight = height;
	}
	
	void Application::setLoadScreen(const String&imgName)
	{
		bool success = AssetManager::loadImage(imgName);
		if(success)
		{
			showLoad = true;
			loadImage = AssetManager::getImage(imgName);
		}
	}
	
	void Application::setLoadBar(float x1,float y1, float w1, float h1, Color color)
	{
		loadbarDim[0]=x1;
		loadbarDim[1]=y1;
		loadbarDim[2]=w1;
		loadbarDim[3]=h1;
		loadbarColor = color;
	}
	
	void Application::setLoadTotal(float total)
	{
		loadTotal = total;
	}
	
	void Application::incrementLoad(float incr)
	{
		game->updateEvents();
		loadCurrent+=incr;
		//graphics->reset();
		/*window->clear();
		if(showLoad)
		{
			BufferedImage*img = AssetManager::getImage(loadScreen);
			graphics->drawImage(img,0,0,(float)View::ScaleWidth(),(float)View::ScaleHeight(),0,0,img->getWidth(),img->getHeight());
		}*/
		graphics->setColor(loadbarColor);
		graphics->fillRect(loadbarDim[0], loadbarDim[1], (float)((float)(loadCurrent/loadTotal)*loadbarDim[2]), loadbarDim[3]);
		SDL_RenderPresent(renderer);
	}
	
	void Application::showBackground(bool toggle)
	{
		bgVisible = toggle;
	}
	
	void Application::setBackgroundImage(const String&imgName)
	{
		bool success=AssetManager::loadImage(imgName);
		if(success)
		{
			bgName=imgName;
			bgVisible = true;
		}
	}
	
	void Application::setBackgroundColor(Color color)
	{
		bgColor = color;
	}
}
