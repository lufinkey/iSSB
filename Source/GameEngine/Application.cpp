
#include "Application.h"
#include "AssetManager.h"
#include "Output/Console.h"
#include "View.h"
#include <ctime>
#include <cstdlib>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "Input/Keys.h"
#include "Input/Mouse.h"
#include "Sound/Sound.h"
#include "Sound/Music.h"
#include "Util/HapticFeedback.h"
#include "CodeBridge/ObjCBridge.h"

#if defined(__APPLE__)
	#include "TargetConditionals.h"
#endif

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
	bool Application::fullscreen = false;
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
	bool Application::KeyState[526];
	bool Application::currentKeyState[526];
	bool Application::prevKeyState[526];
	int Application::mouseX = 0;
	int Application::mouseY = 0;
	int Application::currentMouseX = 0;
	int Application::currentMouseY = 0;
	int Application::prevMouseX = 0;
	int Application::prevMouseY = 0;
	bool Application::mouseState[4];
	bool Application::currentMouseState[4];
	bool Application::prevMouseState[4];
	ArrayList<TouchPoint> Application::touchPoints = ArrayList<TouchPoint>();
	ArrayList<TouchPoint> Application::currentTouchPoints = ArrayList<TouchPoint>();
	ArrayList<TouchPoint> Application::prevTouchPoints = ArrayList<TouchPoint>();
	
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
	
#define GameEngine_SDL_Subsystems SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_JOYSTICK | SDL_INIT_EVENTS | SDL_INIT_HAPTIC
	
	bool Application::Run(unsigned char orient, bool statusbar)
	{
		if(!gameRunning)
		{
			gameRunning = true;
			
			std::srand((unsigned int)std::time(NULL));
			
			if(!SDL_WasInit(GameEngine_SDL_Subsystems))
			{
				if(SDL_Init(GameEngine_SDL_Subsystems)!=0)
				//if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
				{
					Console::WriteLine((String)"failed to initialize SDL with error: " + SDL_GetError());
					gameRunning = false;
					return false;
				}
			}
			
			if(!TTF_WasInit())
			{
				if(TTF_Init() < 0)
				{
					Console::WriteLine((String)"failed to initalize SDL_ttf library with error: " + TTF_GetError());
					gameRunning = false;
					return false;
				}
			}
			
			{
				int flags = MIX_INIT_FLAC | MIX_INIT_MP3 | /*MIX_INIT_MOD | */MIX_INIT_OGG;
				if(Mix_Init(flags) != flags)
				{
					Console::WriteLine((String)"failed to initialize SDL_mixer with error: " + Mix_GetError());
				}
			}
			
			if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096)<0)
			{
				Console::WriteLine((String)"failed to open SDL_mixer audio with error: " + Mix_GetError());
			}
			
			Sound::init();
			Music::init();
			
			GameEngine_init();
			
			HapticFeedback::initialize();
			
			{
#if defined(__APPLE__) && (TARGET_OS_IPHONE == 1 || TARGET_IPHONE_SIMULATOR == 1) || defined (__ANDROID__)
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
#endif

#if defined(__APPLE__) && (TARGET_OS_IPHONE == 1 || TARGET_IPHONE_SIMULATOR == 1) || defined (__ANDROID__)
				int windowX = 0;
				int windowY = 0;
#else
				int windowX = SDL_WINDOWPOS_UNDEFINED;
				int windowY = SDL_WINDOWPOS_UNDEFINED;
#endif
				
				if(borderless)
				{
					window = SDL_CreateWindow(NULL, windowX, windowY, View::windowWidth, View::windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS | SDL_WINDOW_SHOWN);
				}
				else
				{
					window = SDL_CreateWindow(NULL, windowX, windowY, View::windowWidth, View::windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
				}
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
						currentMouseX = mouseX;
						currentMouseY = mouseY;
						updateKeys(currentKeyState, KeyState);
						updateMouse(currentMouseState, mouseState);
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
										updateMouse(prevMouseState, currentMouseState);
										updateTouchPoints(prevTouchPoints, currentTouchPoints);
										
										currentMouseX = mouseX;
										currentMouseY = mouseY;
										updateKeys(currentKeyState, KeyState);
										updateMouse(currentMouseState, mouseState);
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
							graphics->drawImage(img,0,0,(float)View::getScalingWidth(),(float)View::getScalingHeight(),0,0,img->getWidth(),img->getHeight());
						}
						this->Draw(*graphics,worldTime);
						if(!paused)
						{
							updateKeys(prevKeyState,currentKeyState);
							updateMouse(prevMouseState, currentMouseState);
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
					
					redrawLoadScreen();
					
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

	void Application::redrawLoadScreen() {
		if(showLoad) {
			SDL_SetRenderDrawColor(renderer, 0,0,0,255);
			SDL_RenderClear(renderer);
			graphics->drawImage(loadImage,0,0,(float)View::getScalingWidth(),(float)View::getScalingHeight(),0,0,loadImage->getWidth(),loadImage->getHeight());
			graphics->setColor(loadbarColor);
			graphics->fillRect(loadbarDim[0], loadbarDim[1], (float)((float)(loadCurrent/loadTotal)*loadbarDim[2]), loadbarDim[3]);
			SDL_RenderPresent(renderer);
		}
		else {
			SDL_SetRenderDrawColor(renderer, bgColor.r,bgColor.g,bgColor.b,bgColor.a);
			SDL_RenderClear(renderer);
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderPresent(renderer);
		}
	}
		
	void Application::updateEvents()
	{
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_WINDOWEVENT_CLOSE:
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

				case SDL_WINDOWEVENT_RESIZED:
				windowResized(event.window.data1, event.window.data2);
				break;
				
				case SDL_KEYDOWN:
				keyPressed(Keys::SDLK_to_KeyCode(event.key.keysym.sym));
				break;
				
				case SDL_KEYUP:
				keyReleased(Keys::SDLK_to_KeyCode(event.key.keysym.sym));
				break;

				case SDL_MOUSEBUTTONDOWN:
				mousePressed(Mouse::SDL_BUTTON_to_MouseState(event.button.button));
				break;

				case SDL_MOUSEBUTTONUP:
				mouseReleased(Mouse::SDL_BUTTON_to_MouseState(event.button.button));
				break;

				case SDL_MOUSEMOTION:
				mouseMoved(event.motion.x, event.motion.y);
				break;
				
				case SDL_FINGERDOWN:
				addTouchPoint((long)event.tfinger.fingerId, (event.tfinger.x*View::windowWidth), (event.tfinger.y*View::windowHeight));
				break;
				
				case SDL_FINGERMOTION:
				updateTouchPoint((long)event.tfinger.fingerId, (event.tfinger.x*View::windowWidth), (event.tfinger.y*View::windowHeight));
				break;
				
				case SDL_FINGERUP:
				removeTouchPoint((long)event.tfinger.fingerId, (event.tfinger.x*View::windowWidth), (event.tfinger.y*View::windowHeight));
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
	
	int Application::getLastKey()
	{
		return currentLastKey;
	}
	
	bool Application::getKeyPressed(int key) //check if a key is pressed
	{
		return currentKeyState[key];
	}
	
	bool Application::getPrevKeyPressed(int key) //check if a key was pressed in the last frame
	{
		return prevKeyState[key];
	}

	bool Application::getMouseState(int state)
	{
		return currentMouseState[state];
	}
	
	bool Application::getPrevMouseState(int state)
	{
		return prevMouseState[state];
	}
	
	int Application::getMouseX()
	{
		if(scalescreen)
		{
			return (int)((currentMouseX/View::multScale) - View::letterBoxW*(1/View::multScale));
		}
		else
		{
			return currentMouseX;
		}
	}
	
	int Application::getPrevMouseX()
	{
		if(scalescreen)
		{
			return (int)((prevMouseX/View::multScale) - View::letterBoxW*(1/View::multScale));
		}
		else
		{
			return prevMouseX;
		}
	}
	
	int Application::getMouseY()
	{
		if(scalescreen)
		{
			return (int)((currentMouseY/View::multScale) - View::letterBoxH*(1/View::multScale));
		}
		else
		{
			return currentMouseY;
		}
	}
	
	int Application::getPrevMouseY()
	{
		if(scalescreen)
		{
			return (int)((prevMouseY/View::multScale) - View::letterBoxH*(1/View::multScale));
		}
		else
		{
			return prevMouseY;
		}
	}
	
	int Application::getTouchX(long touchID)
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
			return (int)point->x;
		}
	}
	
	int Application::getPrevTouchX(long touchID)
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
			return (int)point->x;
		}
	}
	
	int Application::getTouchY(long touchID)
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
			return (int)point->y;
		}
	}
	
	int Application::getPrevTouchY(long touchID)
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
			return (int)point->y;
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

	bool Application::hasMultitouch()
	{
#if defined(__APPLE__) && (TARGET_OS_IPHONE == 1 || TARGET_IPHONE_SIMULATOR == 1) || defined(__ANDROID__)
		return true;
#else
		return false;
#endif
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

	void Application::mousePressed(int eventcode)
	{
		if(eventcode<3)
		{
			mouseState[eventcode] = true;
		}
	}

	void Application::mouseReleased(int eventcode)
	{
		if(eventcode<3)
		{
			mouseState[eventcode] = false;
		}
	}

	void Application::mouseMoved(int x1, int y1)
	{
		if(x1<0 || y1<0 || x1>View::windowWidth || y1>View::windowHeight)
		{
			mouseState[Mouse::ONSCREEN] = false;
		}
		else
		{
			mouseState[Mouse::ONSCREEN] = true;
		}
		mouseX = x1;
		mouseY = y1;
	}

	void Application::windowResized(int width, int height)
	{
		View::oldWidth = View::windowWidth;
		View::oldHeight = View::windowHeight;
		View::windowWidth = width;
		View::windowHeight = height;
	}
	
	void Application::updateKeys(bool*keys1, bool*keys2)
	{
		for(int i=0; i<totalKeys; i++)
		{
			keys1[i]=keys2[i];
		}
	}

	void Application::updateMouse(bool*mouse1, bool*mouse2)
	{
		for(int i=0; i<totalMousestates; i++)
		{
			mouse1[i]=mouse2[i];
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
		if(closing)
		{
			return;
		}

		loadCurrent+=incr;
		//graphics->reset();
		/*window->clear();
		if(showLoad)
		{
			BufferedImage*img = AssetManager::getImage(loadScreen);
			graphics->drawImage(img,0,0,(float)View::getScalingWidth(),(float)View::getScalingHeight(),0,0,img->getWidth(),img->getHeight());
		}*/
		if(showLoad) {
			redrawLoadScreen();
		}
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

	void Application::setWindowTitle(const String& title)
	{
		SDL_SetWindowTitle(window, title);
	}

	void Application::setFullScreen(bool toggle)
	{
		if(toggle)
		{
			fullscreen = true;
			SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		}
		else
		{
			fullscreen = false;
			SDL_SetWindowFullscreen(window, 0);
		}
	}
}
