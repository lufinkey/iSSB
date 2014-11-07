
#include "../../Stage.h"

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
		HillsideBattleground(float x1, float y1);
		~HillsideBattleground();

		virtual void Draw(Graphics2D&g, long gameTime);
	};
}