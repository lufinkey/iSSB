
#include "../../Stage.h"

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
		FinalDestinationBrawl(float x1,float y1);
		~FinalDestinationBrawl();

		virtual void Draw(Graphics2D&g, long gameTime);
	};
}