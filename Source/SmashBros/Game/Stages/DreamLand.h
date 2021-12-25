
#include "../../Stage.h"

#pragma once

namespace SmashBros
{
	class DreamLand : public Stage
	{
	private:
		void loadGameElements();
		void loadPlatforms();
		void loadHangPoints();

	public:
		DreamLand(float x1, float y1);
		virtual ~DreamLand();
		
		virtual void Draw(Graphics2D&g, long gameTime);
	};
}
