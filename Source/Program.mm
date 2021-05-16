
#import <Foundation/Foundation.h>
#include "Game.h"
#include <iostream>

#ifdef __APPLE__
int main(int argc, char *argv[])
{
/*#ifdef _WIN32
	GameEngine_setDLLDirectory("DLL");
#endif
	*/
	@autoreleasepool {
		//
	}
	SmashBros::Game*game = new SmashBros::Game();
	game->Run(Application::ORIENTATION_LANDSCAPE, false);
	delete game;
	return 0;
}
#endif
