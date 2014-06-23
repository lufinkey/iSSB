#include "Stage.h"

#pragma once

namespace SmashBros
{
	class HyruleTemple : public Stage
	{
	private:
		Platform*watchPlat;
		void loadGameElements();
		void loadPlatforms();
		void loadForeground();
		void loadHangPoints();
		void loadGround();

	public:
		HyruleTemple(int x1, int y1);
		~HyruleTemple();

		virtual void Update(long gameTime);
		virtual void Draw(Graphics2D&g, long gameTime);
	};
}