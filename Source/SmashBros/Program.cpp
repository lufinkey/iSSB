
#include "Game.h"

int main(int argc, char *argv[])
{
	SmashBros::Game*game = new SmashBros::Game();
	game->Run(Application::ORIENTATION_LANDSCAPE, false);
	delete game;
	exit(0);
	return 0;
}