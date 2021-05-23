
#include "Game.h"
#include <iostream>
#include <SDL_main.h>

#ifdef _WIN32
#include "GameEngine/CodeBridge/CPPBridge.h"
#endif

#ifndef __APPLE__
int main(int argc, char *argv[])
{
/*#ifdef _WIN32
	GameEngine_setDLLDirectory("DLL");
#endif
	*/
	SmashBros::Game*game = new SmashBros::Game();
	game->Run(Application::ORIENTATION_LANDSCAPE, false);
	delete game;
	exit(0);
	return 0;
}
#endif
