
#include "Color.h"

namespace GameEngine
{
	const Color Color::BLACK = Color(0,0,0);
	const Color Color::BLUE = Color(0,0,255);
	const Color Color::CYAN = Color(0,255,255);
	const Color Color::DARKGRAY = Color(64,64,64);
	const Color Color::GRAY = Color(128,128,128);
	const Color Color::GREEN = Color(0,255,0);
	const Color Color::LIGHTGRAY = Color(192,192,192);
	const Color Color::MAGENTA = Color(255,0,255);
	const Color Color::ORANGE = Color(255,200,0);
	const Color Color::PINK = Color(255,175,175);
	const Color Color::RED = Color(255,0,0);
	const Color Color::WHITE = Color(255,255,255);
	const Color Color::YELLOW = Color(255,255,0);
	const Color Color::TRANSPARENT = Color(0,0,0,0);
	
	Color::Color()
	{
		r = 255;
		g = 255;
		b = 255;
		a = 255;
	}
	
	Color::Color(unsigned char R, unsigned char G, unsigned char B, unsigned char A)
	{
		r = R;
		g = G;
		b = B;
		a = A;
	}
	
	Color::Color(int rgb, bool alpha)
	{
		unsigned char*rgbArray = (unsigned char*)(&rgb);
		r = rgbArray[0];
		g = rgbArray[1];
		b = rgbArray[2];
		if(alpha)
		{
			a = rgbArray[3];
		}
	}
	
	Color::Color(const Color&color)
	{
		r = color.r;
		g = color.g;
		b = color.b;
		a = color.a;
	}
	
	Color::Color(const SDL_Color&color)
	{
		r = color.r;
		g = color.g;
		b = color.b;
		a = 255;
	}
	
	Color::Color(const ValueRGBA&color)
	{
		r = color.r;
		g = color.g;
		b = color.b;
		a = color.a;
	}
	
	Color::~Color()
	{
		//
	}
	
	Color&Color::operator=(const Color&color)
	{
		r = color.r;
		g = color.g;
		b = color.b;
		a = color.a;
		return *this;
	}
	
	Color&Color::operator=(const SDL_Color&color)
	{
		r = color.r;
		g = color.g;
		b = color.b;
		a = 255;
		return *this;
	}
	
	Color&Color::operator=(const ValueRGBA&color)
	{
		r = color.r;
		g = color.g;
		b = color.b;
		a = color.a;
		return *this;
	}
	
	bool Color::operator==(const Color&color) const
	{
		return equals(color);
	}
	
	bool Color::operator==(const SDL_Color&color) const
	{
		return equals(color);
	}
	
	bool Color::operator==(const ValueRGBA&color) const
	{
		return equals(color);
	}
	
	Color::operator ValueRGBA() const
	{
		ValueRGBA color = {r,g,b,a};
		return color;
	}
	
	Color::operator SDL_Color() const
	{
		SDL_Color color;
		color.r = r;
		color.g = g;
		color.b = b;
		return color;
	}
	
	int Color::getRGBA()
	{
		int rgba = 0;
		unsigned char*arr = (unsigned char*)(&rgba);
		arr[0] = r;
		arr[1] = g;
		arr[2] = b;
		arr[3] = a;
		return rgba;
	}
	
	bool Color::equals(const Color&color) const
	{
		if(r==color.r && g==color.g && b==color.b && a==color.a)
		{
			return true;
		}
		return false;
	}
	
	bool Color::equals(const SDL_Color&color) const
	{
		if(r==color.r && g==color.g && b==color.b && a==255)
		{
			return true;
		}
		return false;
	}
	
	bool Color::equals(const ValueRGBA&color) const
	{
		if(r==color.r && g==color.g && b==color.b && a==color.a)
		{
			return true;
		}
		return false;
	}
}