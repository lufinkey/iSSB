
#pragma once

namespace GameEngine
{
	class Mouse
	{
		friend class Application;
	public:
		static const int LEFTCLICK = 0;
		static const int RIGHTCLICK = 1;
		static const int MIDDLECLICK = 2;
		static const int ONSCREEN = 3;

	private:
		static int SDL_BUTTON_to_MouseState(unsigned char button);
	};
}