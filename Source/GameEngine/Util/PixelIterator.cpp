
#include "PixelIterator.h"
#include "../Actor/Actor.h"
#include <cmath>

namespace GameEngine
{
	PixelIterator::PixelIterator(Actor*actor)
	{
		this->actor = actor;
		currentPoint = 0;
		lastRowStart = 0;
		yPnt = 0;
		xIncr = 0;
		yIncr = 0;
		oldYPnt = 0;
		rowMax = 0;
		xCnt = 0;
		nextRow = 0;
	}
	
	PixelIterator::~PixelIterator()
	{
		//
	}
	
	void PixelIterator::reset(float x1, float y1, float incrX, float incrY, int w, int h)
	{
		Animation*anim = actor->getAnimation();
		img = anim->getCurrentImage();
		
		bool mirror = false;
		bool mirrorVertical = false;
		
		if((anim->isMirrored() && !actor->mirrored) || (!anim->isMirrored() && actor->mirrored))
		{
			mirror = true;
		}
		if((anim->isMirroredVertical() && !actor->mirroredVertical) || (!anim->isMirroredVertical() && actor->mirroredVertical))
		{
			mirrorVertical = true;
		}
		
		nextRow = img->getWidth();
		rowMax = w;
		xCnt = 0;
		
		if(mirror)
		{
			x1 = actor->currentImageX + ((actor->currentImageW-1) - x1);
			incrX*=-1;
		}
		else
		{
			x1 = actor->currentImageX + x1;
		}
		
		if(mirrorVertical)
		{
			y1 = actor->currentImageY + ((actor->currentImageH-1) - y1);
			incrY*=-1;
			nextRow*=-1;
		}
		else
		{
			y1 = actor->currentImageY + y1;
		}
		
		currentPoint = (img->getWidth()*std::floor(y1))+x1;
		lastRowStart = currentPoint;
		xIncr = incrX;
		yIncr = incrY;
		yPnt = y1;
		oldYPnt = y1;
	}
	
	bool PixelIterator::checkNextPixel()
	{
		if(xCnt>=rowMax)
		{
			xCnt = 0;
			yPnt +=yIncr;
			int dif = (int)(yPnt - oldYPnt);
			if(dif>0)
			{
				currentPoint = lastRowStart + (float)(nextRow*dif);
				lastRowStart = currentPoint;
				oldYPnt = (float)((int)yPnt);
			}
			else
			{
				currentPoint = lastRowStart;
			}
		}
		
		bool point = img->pixelAtPoint((unsigned int)currentPoint);
		
		currentPoint+=xIncr;
		xCnt++;
		
		return point;
	}
	
	int PixelIterator::getCurrentPoint()
	{
		return (int)currentPoint;
	}
}