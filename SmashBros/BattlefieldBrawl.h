#include "Stage.h"

#pragma once

namespace SmashBros
{
	class BattlefieldBrawl : public Stage
	{
	private:
		void loadGameElements();
		void loadPlatforms();
		void loadHangPoints();

	public:
		BattlefieldBrawl(int x1, int y1);
		virtual ~BattlefieldBrawl();
		
		virtual void Draw(Graphics2D&g, long gameTime);
	};
}