
#pragma once

#define null 0

namespace GameEngine
{
	const double PI = 3.1415926535897931;
	
	const int INTEGER_MAX = 2147483647;
	
	static double radtodeg(double rad)
	{
		return rad * 180 / PI;
	}
	
	static double degtorad(double degrees)
	{
		return degrees * PI / 180;
	}
	
	typedef struct
	{
		int left,top,right,bottom;
	} Rect;
	
	typedef struct
	{
		float left,top,right,bottom;
	} RectF;
	
	class Rectangle
	{
	public:
		int x,y,width,height;
		
		Rectangle()
		{
			x=0;
			y=0;
			width=0;
			height=0;
		}
		
		Rectangle(int x,int y,int width,int height)
		{
			this->x = x;
			this->y = y;
			this->width = width;
			this->height = height;
		}
		
		~Rectangle()
		{
			//
		}
		
		bool equals(const Rectangle&rect)
		{
			if(x==rect.x && y==rect.y && width==rect.width && height==rect.height)
			{
				return true;
			}
			return false;
		}
	};
	
	class RectangleF
	{
	public:
		float x,y,width,height;
		
		RectangleF()
		{
			x=0;
			y=0;
			width=0;
			height=0;
		}
		
		RectangleF(float x,float y,float width,float height)
		{
			this->x = x;
			this->y = y;
			this->width = width;
			this->height = height;
		}
		
		~RectangleF()
		{
			//
		}
		
		bool equals(const RectangleF&rect)
		{
			if(x==rect.x && y==rect.y && width==rect.width && height==rect.height)
			{
				return true;
			}
			return false;
		}
	};
}