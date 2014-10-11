
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
		
		Rectangle(const Rectangle&rect)
		{
			x = rect.x;
			y = rect.y;
			width = rect.width;
			height = rect.height;
		}
		
		~Rectangle()
		{
			//
		}
		
		Rectangle& operator=(const Rectangle&rect)
		{
			x = rect.x;
			y = rect.y;
			width = rect.width;
			height = rect.height;
			
			return *this;
		}
		
		Rectangle operator-(const Rectangle&rect)
		{
			return Rectangle(x-rect.x,y-rect.y,width-rect.width,height-rect.height);
		}
		
		Rectangle& operator-=(const Rectangle&rect)
		{
			x -= rect.x;
			y -= rect.y;
			width -= rect.width;
			height -= rect.height;
			
			return *this;
		}
		
		operator Rect()
		{
			Rect rect;
			rect.left = x;
			rect.top = y;
			rect.right = x+width;
			rect.bottom = y+height;
			return rect;
		}
		
		bool equals(const Rectangle& rect) const
		{
			if(rect.x==x && rect.y==y && rect.width==width && rect.height==height)
			{
				return true;
			}
			return false;
		}
		
		void expand(int amount)
		{
			x -= amount;
			width += (amount*2);
			y -= amount;
			height += (amount*2);
		}
		
		void expand(int amount, const Rectangle&constraints)
		{
			int overlap = x - constraints.x;
			if(overlap > amount)
			{
				x -= amount;
				width += amount;
			}
			else
			{
				x -= overlap;
				width += overlap;
			}
			
			overlap = (constraints.x+constraints.width) - (x+width);
			if(overlap > amount)
			{
				width += amount;
			}
			else
			{
				width += overlap;
			}
			
			overlap = y - constraints.y;
			if(overlap > amount)
			{
				y -= amount;
				height += amount;
			}
			else
			{
				y -= overlap;
				height += overlap;
			}
			
			overlap = (constraints.y+constraints.height) - (y+height);
			if(overlap > amount)
			{
				height += amount;
			}
			else
			{
				height += overlap;
			}
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
		
		RectangleF(const RectangleF& rect)
		{
			x = rect.x;
			y = rect.y;
			width = rect.width;
			height = rect.height;
		}
		
		~RectangleF()
		{
			//
		}
		
		RectangleF& operator=(const RectangleF&rect)
		{
			x = rect.x;
			y = rect.y;
			width = rect.width;
			height = rect.height;
			
			return *this;
		}
		
		RectangleF operator-(const RectangleF&rect)
		{
			return RectangleF(x-rect.x,y-rect.y,width-rect.width,height-rect.height);
		}
		
		RectangleF& operator-=(const RectangleF&rect)
		{
			x -= rect.x;
			y -= rect.y;
			width -= rect.width;
			height -= rect.height;
			
			return *this;
		}
		
		operator RectF()
		{
			RectF rect;
			rect.left = x;
			rect.top = y;
			rect.right = x+width;
			rect.bottom = y+height;
			return rect;
		}
		
		bool equals(const RectangleF& rect)
		{
			if(rect.x==x && rect.y==y && rect.width==width && rect.height==height)
			{
				return true;
			}
			return false;
		}
		
		void expand(float amount)
		{
			x -= amount;
			width += (amount*2);
			y -= amount;
			height += (amount*2);
		}
		
		void expand(float amount, const RectangleF&constraints)
		{
			float overlap = x - constraints.x;
			if(overlap > amount)
			{
				x -= amount;
				width += amount;
			}
			else
			{
				x -= overlap;
				width += overlap;
			}
			
			overlap = (constraints.x+constraints.width) - (x+width);
			if(overlap > amount)
			{
				width += amount;
			}
			else
			{
				width += overlap;
			}
			
			overlap = y - constraints.y;
			if(overlap > amount)
			{
				y -= amount;
				height += amount;
			}
			else
			{
				y -= overlap;
				height += overlap;
			}
			
			overlap = (constraints.y+constraints.height) - (y+height);
			if(overlap > amount)
			{
				height += amount;
			}
			else
			{
				height += overlap;
			}
		}
	};
}