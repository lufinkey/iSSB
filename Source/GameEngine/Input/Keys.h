
#include "../Util/String.h"
#include "SDL_keycode.h"

#pragma once

namespace GameEngine
{
	class Keys
	{
		friend class Application;
	public:
		static const int A = 1;
		static const int B = 2;
		static const int C = 3;
		static const int D = 4;
		static const int E = 5;
		static const int F = 6;
		static const int G = 7;
		static const int H = 8;
		static const int I = 9;
		static const int J = 10;
		static const int K = 11;
		static const int L = 12;
		static const int M = 13;
		static const int N = 14;
		static const int O = 15;
		static const int P = 16;
		static const int Q = 17;
		static const int R = 18;
		static const int S = 19;
		static const int T = 20;
		static const int U = 21;
		static const int V = 22;
		static const int W = 23;
		static const int X = 24;
		static const int Y = 25;
		static const int Z = 26;
		static const int NUM_0 = 27;
		static const int NUM_1 = 28;
		static const int NUM_2 = 29;
		static const int NUM_3 = 30;
		static const int NUM_4 = 31;
		static const int NUM_5 = 32;
		static const int NUM_6 = 33;
		static const int NUM_7 = 34;
		static const int NUM_8 = 35;
		static const int NUM_9 = 36;
		static const int ESCAPE = 37;
		static const int CTRL_LEFT = 38;
		static const int SHIFT_LEFT = 39;
		static const int ALT_LEFT = 40;
		static const int WINDOWS_LEFT = 41;
		static const int CTRL_RIGHT = 42;
		static const int SHIFT_RIGHT = 43;
		static const int ALT_RIGHT = 44;
		static const int WINDOWS_RIGHT = 45;
		static const int CONTEXT_MENU = 46;
		static const int OPENBRACKET = 47;
		static const int CLOSEBRACKET = 48;
		static const int SEMICOLON = 49;
		static const int COMMA = 50;
		static const int PERIOD = 51;
		static const int QUOTE = 52;
		static const int FORWARDSLASH = 53;
		static const int BACKSLASH = 54;
		static const int EQUALS = 55;
		static const int DASH = 56;
		static const int SPACE = 57;
		static const int ENTER = 58;
		static const int BACKSPACE = 59;
		static const int TAB = 60;
		static const int PAGEUP = 61;
		static const int PAGEDOWN = 62;
		static const int END = 63;
		static const int HOME = 64;
		static const int INS = 65;
		static const int DEL = 66;
		static const int ADD = 67;
		static const int SUBTRACT = 68;
		static const int MULTIPLY = 69;
		static const int DIVIDE = 70;
		static const int LEFTARROW = 71;
		static const int RIGHTARROW = 72;
		static const int UPARROW = 73;
		static const int DOWNARROW = 74;
		static const int NUMPAD_0 = 75;
		static const int NUMPAD_1 = 76;
		static const int NUMPAD_2 = 77;
		static const int NUMPAD_3 = 78;
		static const int NUMPAD_4 = 79;
		static const int NUMPAD_5 = 80;
		static const int NUMPAD_6 = 81;
		static const int NUMPAD_7 = 82;
		static const int NUMPAD_8 = 83;
		static const int NUMPAD_9 = 84;
		static const int F1 = 85;
		static const int F2 = 86;
		static const int F3 = 87;
		static const int F4 = 88;
		static const int F5 = 89;
		static const int F6 = 90;
		static const int F7 = 91;
		static const int F8 = 92;
		static const int F9 = 93;
		static const int F10 = 94;
		static const int F11 = 95;
		static const int F12 = 96;
		static const int F13 = 97;
		static const int F14 = 98;
		static const int F15 = 99;
		static const int PAUSE = 100;
		
		static String GetKeyText(int keyNum);
	private:
		static int SDLK_to_KeyCode(int code);
	};
}