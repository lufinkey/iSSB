
#include "forwards.h"
#include <SDL.h>
#include "Graphics/Graphics2D.h"
#include "Util/ArrayList.h"
#include "Util/String.h"
#include "ApplicationEventListener.h"
#include "Input/TouchPoint.h"
#include "BatchLoader.h"

#pragma once

namespace GameEngine
{
	class Application
	{
		friend class View;
		friend class BufferedImage;
		friend class BatchLoader;
		friend int ApplicationEventHandler(void*,SDL_Event*);
		friend void private_updateAppEvents(void);
	private:
		static SDL_Window*window;
		static SDL_Renderer*renderer;
		static Application*game;
		static Graphics2D*graphics;
		static ApplicationEventListener*appEventListener;
		static LoadThread*loadThread;
		
		static int upf;
		static bool loaded;
		static bool exiting;
		static long worldTime;
		static long frame;
		static int sleepTime;
		static bool paused;
		static bool gameRunning;
		static bool closing;
		static bool borderless;
		static bool scalescreen;
		static bool fullscreen;
		static unsigned char orientation;
		static bool updating;
		
		static bool bgVisible;
		static String bgName;
		static bool showLoad;
		static float loadbarDim[4];
		static Color loadbarColor;
		static BufferedImage*loadImage;
		static float loadTotal;
		static float loadCurrent;
		
		static long realFPS;
		static bool showfps;
		
		static long lastFrame;
		static long firstFrame;
		static long lastFrameTime;
		
		static Color bgColor;
		
		static const int totalKeys = 526;
		static bool currentKeyState[526];
		static bool KeyState[526];
		static bool prevKeyState[526];
		static int currentLastKey;
		static int lastKey;

		static const int totalMousestates = 4;
		static bool prevMouseState[4];
		static bool currentMouseState[4];
		static bool mouseState[4];
		static int mouseX;
		static int mouseY;
		static int currentMouseX;
		static int currentMouseY;
		static int prevMouseX;
		static int prevMouseY;

		static ArrayList<TouchPoint> currentTouchPoints;
		static ArrayList<TouchPoint> touchPoints;
		static ArrayList<TouchPoint> prevTouchPoints;
		
		static bool minimizing;
		static bool readyToMinimize;
		
		void updateEvents();
		
		static void keyPressed(int keycode);
		static void keyReleased(int keycode);
		static void mousePressed(int eventcode);
		static void mouseReleased(int eventcode);
		static void mouseMoved(int x, int y);
		static void addTouchPoint(long givenID, float x, float y);
		static void updateTouchPoint(long givenID, float x, float y);
		static void removeTouchPoint(long givenID, float x, float y);
		static TouchPoint*getTouchPoint(long ID);
		static TouchPoint*getPrevTouchPoint(long ID);
		static void windowResized(int width, int height);
		
		static void updateKeys(bool*keys1, bool*keys2);
		void updateMouse(bool*mouse1, bool*mouse2);
		static void updateTouchPoints(ArrayList<TouchPoint>&points1, ArrayList<TouchPoint>&points2);
		
		static void redrawLoadScreen();
		
	public:
		static const unsigned char ORIENTATION_PORTRAIT = 0;
		static const unsigned char ORIENTATION_LANDSCAPE = 1;
		
		Application();
		virtual ~Application();
		
		virtual void Initialize();
		virtual void LoadContent();
		virtual void UnloadContent();
		virtual void Update(long gameTime);
		virtual void Draw(Graphics2D&g, long gameTime);
		
		virtual void onSuspend();
		virtual void onResume();
		
		bool Run(unsigned char orient = ORIENTATION_PORTRAIT, bool statusbar = true);
		
		static void Exit();
		
		static void showMessage(const String&message);
		static void showMessage(const String&title, const String&message);
		static int showMessage(const String&title, const String&message, const ArrayList<String>&options);
		
		static int getLastKey();
		static bool getKeyPressed(int key);
		static bool getPrevKeyPressed(int key);
		
		static bool getMouseState(int state);
		static bool getPrevMouseState(int state);
		static int getMouseX();
		static int getMouseY();
		static int getPrevMouseX();
		static int getPrevMouseY();
		static int getTouchX(long touchID);
		static int getPrevTouchX(long touchID);
		static int getTouchY(long touchID);
		static int getPrevTouchY(long touchID);
		static bool checkTouchActive(long touchID);
		static bool checkPrevTouchActive(long touchID);
		static ArrayList<TouchPoint> getTouchPoints();
		static ArrayList<TouchPoint> getPrevTouchPoints();
		static bool hasMultitouch();
		
		static void setUpdatesPerFrame(int total);
		static long getFrame();
		static SDL_Window*getWindow();
		
		static void setFPS(int fps);
		static void showRealFPS(bool toggle);
		
		static long getGameTime();
		static long getSystemTime();
		static void setGameTime(long time);
		
		static void Suspend();
		static void Resume();
		
		static bool Suspended();
		
		static void scaleToWindow(bool toggle);
		static void scaleToWindow(bool toggle, int width, int height);
		
		static void setLoadScreen(const String&imgName);
		static void setLoadBar(float x1,float y1, float w1, float h1, Color color);
		static void setLoadTotal(float total);
		static void incrementLoad(float incr);
		
		static void showBackground(bool toggle);
		static void setBackgroundImage(const String&imgName);
		static void setBackgroundColor(Color color);
		
		static void setWindowTitle(const String& title);
		static void setFullScreen(bool toggle);	
	};
}
