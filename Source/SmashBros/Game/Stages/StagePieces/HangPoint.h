
#include "../../../../GameEngine/GameEngine.h"

#pragma once

namespace SmashBros
{
	class HangPoint : public WireframeActor
	{
	private:
		byte dir;

	public:
		static const byte LEFT = 1;
		static const byte RIGHT = 2;

		int hanging;

		HangPoint(byte dir, float x1, float y1);
		virtual ~HangPoint();

		virtual void Update(long gameTime);
		virtual void Draw(Graphics2D&g, long gameTime);

		byte getHangSide();
	};
}