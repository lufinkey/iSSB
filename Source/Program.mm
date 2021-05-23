
#ifdef __APPLE__
#import <Foundation/Foundation.h>

#include "Game.h"
#include <iostream>
#include <SDL_main.h>

int main(int argc, char *argv[]) {
	@autoreleasepool {
		//
	}
	SmashBros::Game*game = new SmashBros::Game();
	game->Run(Application::ORIENTATION_LANDSCAPE, false);
	delete game;
	return 0;
}
#endif
