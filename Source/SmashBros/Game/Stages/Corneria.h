
#include "../../Stage.h"

#pragma once

namespace SmashBros
{
	class Corneria : public Stage
	{
	private:
		void loadGameElements();
		void loadPlatforms();
		void loadHangPoints();
		void loadGround();

	public:
		Corneria(float x1, float y1);
		~Corneria();

		virtual void Draw(Graphics2D&g, long gameTime);
	};
}