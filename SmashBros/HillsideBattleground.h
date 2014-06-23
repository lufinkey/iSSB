#include "Stage.h"

#pragma once

namespace SmashBros
{
	class HillsideBattleground : public Stage
	{
	private:
		void loadGameElements();
		void loadPlatforms();
		void loadHangPoints();
		void loadGround();

	public:
		HillsideBattleground(int x1, int y1);
		~HillsideBattleground();

		virtual void Draw(Graphics2D&g, long gameTime);
	};
}