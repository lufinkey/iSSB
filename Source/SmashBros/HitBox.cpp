
#include "HitBox.h"
#include "Camera.h"

namespace SmashBros
{
	HitBox::HitBox(byte playerNo, float x1, float y1, int w, int h) : WireframeActor(x1,y1,w,h)
	{
		this->playerNo = playerNo;
	}

	HitBox::~HitBox()
	{
		//
	}

	void HitBox::Draw(Graphics2D&g, long gameTime)
	{
		drawActor(g, gameTime, (x*Camera::Zoom), (y*Camera::Zoom), Camera::Zoom);
	}
}