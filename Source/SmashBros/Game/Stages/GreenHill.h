
#include "../../Stage.h"

#pragma once

namespace SmashBros
{
	class GreenHill : public Stage
	{
	private:
		void loadGameElements();
		void loadPlatforms();
		void loadHangPoints();

	public:
		GreenHill(float x1, float y1);
		virtual ~GreenHill();
		
		virtual void Draw(Graphics2D&g, long gameTime);
	};
}
