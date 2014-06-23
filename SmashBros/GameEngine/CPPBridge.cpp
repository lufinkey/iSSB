
#include "CPPBridge.h"
#include "Application.h"

namespace GameEngine
{
	void private_updateAppEvents(void)
	{
		GameEngine::Application::game->updateEvents();
	}
}

void updateAppEvents(void)
{
	GameEngine::private_updateAppEvents();
}

void showMessage(const char*title, const char*message)
{
	GameEngine::Application::showMessage(title,message);
}