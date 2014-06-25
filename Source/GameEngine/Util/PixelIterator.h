
#include "../forwards.h"

#pragma once

namespace GameEngine
{
	class PixelIterator
	{
	private:
		Actor*actor;
		BufferedImage*img;
		float currentPoint, lastRowStart, yPnt, xIncr, yIncr, oldYPnt;
		int rowMax, xCnt;
		int nextRow;
		
	public:
		PixelIterator(Actor*actor);
		virtual ~PixelIterator();
		
		void reset(float x1,float y1,float incrX,float incrY,int w,int h);
		bool checkNextPixel();
		
		int getCurrentPoint();
	};
}