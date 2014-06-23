#include "Stage.h"

#pragma once

namespace SmashBros
{
	class FinalDestinationBrawl : public Stage
	{
	private:
		GameElement*fg_left;
		GameElement*fg_right;
		float fglx,fgly,fgrx,fgry;

		void loadGameElements();
		void loadPlatforms();
		void loadHangPoints();

	public:
		FinalDestinationBrawl(int x1,int y1);
		~FinalDestinationBrawl();

		virtual void Draw(Graphics2D&g, long gameTime);
	};
}