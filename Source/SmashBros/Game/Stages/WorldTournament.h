
#include "../../Stage.h"

#pragma once

namespace SmashBros
{
	class WorldTournament : public Stage
	{
	private:
		void loadGameElements();
		void loadPlatforms();
		void loadHangPoints();
		void loadGround();

	public:
		WorldTournament(float x1, float y1);
		~WorldTournament();

		virtual void Draw(Graphics2D&g, long gameTime);
	};
}
