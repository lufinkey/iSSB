
#include "../GameEngine/GameEngine.h"

#pragma once

namespace SmashBros
{
	class HitBox : public WireframeActor
	{
		friend class Stage;
		friend class Player;
	private:
		byte playerNo;

	public:
		HitBox(byte playerNo, float x1, float y1, int w, int h);
		virtual ~HitBox();

		virtual void Draw(Graphics2D&g, long gameTime);
	};
}