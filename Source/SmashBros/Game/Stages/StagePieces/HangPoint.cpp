
#include "HangPoint.h"
#include "../../../Camera.h"

namespace SmashBros
{
	HangPoint::HangPoint(byte dir, float x1, float y1) : WireframeActor(x1,y1,10,10)
	{
		hanging = 0;
		this->dir = dir;
	}

	HangPoint::~HangPoint()
	{
		//
	}

	void HangPoint::Update(long gameTime)
	{
		WireframeActor::Update(gameTime);
	}

	void HangPoint::Draw(Graphics2D&g, long gameTime)
	{
		drawActor(g, gameTime, (float)(x*Camera::Zoom), (float)(y*Camera::Zoom), Camera::Zoom);
	}

	byte HangPoint::getHangSide()
	{
		return dir;
	}
}