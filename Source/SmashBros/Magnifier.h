
#include "../GameEngine/GameEngine.h"
#include "GameElement.h"

#pragma once

namespace SmashBros
{
	class Magnifier
	{
	private:
		static Actor*magnifier;

	public:
		static void load();

		static void Draw(Graphics2D&g, long gameTime, GameElement*element);
	};
}