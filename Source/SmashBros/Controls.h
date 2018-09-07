
#include "Global.h"
#include "../GameEngine/GameEngine.h"
#include "../GameEngine/CodeBridge/iCade/iCadeState.h"

#pragma once

namespace SmashBros
{
	class Controls
	{
		friend class Preferences;
		friend class P2PDataManager;
	private:
		class ControlHUD
		{
			friend class Controls;//nafe
		private:
			
			static const float farDist;
			static const float centerDist;
			static const long runDelay;
			
			Actor*button_a;
			Actor*button_b;
			Actor*button_x;
			Actor*button_z;
			
			Actor*arrow_up;
			Actor*arrow_down;
			Actor*arrow_left;
			Actor*arrow_right;
			
			WireframeActor*joystickArea;
			Actor*joystick;
			
			byte*joystickDir;
			bool*joystickFar;
			bool*joystickDown;
			bool*justPulled;
			long*lastCenterTime;
			
		public:
			ControlHUD();
			~ControlHUD();
			
			void Update(long gameTime);
			void Draw(Graphics2D&g, long gameTime);
			
			void js_release(byte pNum);
			void js_center(byte pNum);
			void js_up(byte pNum);
			void js_up2(byte pNum);
			void js_down(byte pNum);
			void js_down2(byte pNum);
			void js_left(byte pNum);
			void js_left2(byte pNum);
			void js_right(byte pNum);
			void js_right2(byte pNum);
			void js_upleft(byte pNum);
			void js_upleft2(byte pNum);
			void js_upright(byte pNum);
			void js_upright2(byte pNum);
			void js_downleft(byte pNum);
			void js_downleft2(byte pNum);
			void js_downright(byte pNum);
			void js_downright2(byte pNum);
		};
		
		static void handleP2PData(byte*&data);
		
		static int**controls;
		static bool ControllerButtonStates[20];
		static bool PrevControllerButtonStates[20];
		static ControlHUD*touchControls;
		static bool touchEnabled;
		static bool joystickEnabled;
		static byte touchPlayer;
		
		static void iCadeStateChangedHandler(iCadeState);
		static void iCadeButtonDownHandler(iCadeState);
		static void iCadeButtonUpHandler(iCadeState);
		
	public:
		static const byte UP = 0;
		static const byte DOWN = 1;
		
		static const byte BUTTONS_TOTAL = 7;
		
		static const byte BUTTON_UP = 0;
		static const byte BUTTON_LEFT = 1;
		static const byte BUTTON_DOWN = 2;
		static const byte BUTTON_RIGHT = 3;
		static const byte BUTTON_JUMP = 4;
		static const byte BUTTON_STANDARD = 5;
		static const byte BUTTON_SPECIAL = 6;
		static const byte BUTTON_GRAB = 7;
		static const byte BUTTON_NONE = 8;
		
		static const byte BUTTONS_TOTAL2 = 1;
		
		static const byte BUTTON_PAUSE = 9;
		
		static const byte BUTTONDIR_CENTER = 0;
		static const byte BUTTONDIR_UP = 1;
		static const byte BUTTONDIR_RIGHT = 2;
		static const byte BUTTONDIR_DOWN = 3;
		static const byte BUTTONDIR_LEFT = 4;
		
		static void enableTouchControls(bool toggle);
		static void setJoystickActive(bool toggle);
		static bool isJoystickActive();
		static bool controlsDown();

		static void loadControls();
		static void setDefaultControls();
		
		static void CheckKeysDown();
		static void CheckKeysUp();
		
		static void Update(long gameTime);
		static void Draw(Graphics2D&g, long gameTime);
		
		static void buzzForButton();
		static void buzzForJoystick();

		static void buttonUp(byte pNum, byte type);
		static void buttonDown(byte pNum, byte type);
		static void buttonLeft(byte pNum, byte type);
		static void buttonRight(byte pNum, byte type);

		static void buttonX(byte pNum, byte type);
		static void buttonA(byte pNum, byte type);
		static void buttonB(byte pNum, byte type);
		static void buttonZ(byte pNum, byte type);
	};
}

