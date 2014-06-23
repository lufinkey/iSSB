
#pragma once

namespace GameEngine
{
	typedef struct
	{
		float x,y;
		long ID;
	} TouchPoint;
	
	static TouchPoint createTouchPoint(long ID, float x, float y)
	{
		TouchPoint point;
		point.ID = ID;
		point.x = x;
		point.y = y;
		return point;
	}
}