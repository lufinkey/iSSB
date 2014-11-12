
#include "Mouse.h"
#include <SDL_events.h>

namespace GameEngine
{
	int Mouse::SDL_BUTTON_to_MouseState(unsigned char button)
	{
		if(button == SDL_BUTTON_LEFT)
		{
			return LEFTCLICK;
		}
		else if(button == SDL_BUTTON_RIGHT)
		{
			return RIGHTCLICK;
		}
		else if(button == SDL_BUTTON_MIDDLE)
		{
			return MIDDLECLICK;
		}
		return (int)button;
	}
}