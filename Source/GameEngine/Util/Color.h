
#include "../forwards.h"
#include "BufferedImage.h"
#include "SDL_pixels.h"

#ifdef TRANSPARENT
#undef TRANSPARENT
#endif

#pragma once

namespace GameEngine
{
	class Color
	{
	public:
		static const Color BLACK;
		static const Color BLUE;
		static const Color CYAN;
		static const Color DARKGRAY;
		static const Color GRAY;
		static const Color GREEN;
		static const Color LIGHTGRAY;
		static const Color MAGENTA;
		static const Color ORANGE;
		static const Color PINK;
		static const Color RED;
		static const Color WHITE;
		static const Color YELLOW;
		static const Color TRANSPARENT;
		
		unsigned char r,g,b,a;
		
		Color();
		Color(const Color&color);
		Color(const ValueRGBA&color);
		Color(const SDL_Color&color);
		Color(int rgb, bool alpha = false);
		Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a=255);
		~Color();
		
		Color&operator=(const ValueRGBA&color);
		Color&operator=(const SDL_Color&color);
		Color&operator=(const Color&color);
		bool operator==(const ValueRGBA&color) const;
		bool operator==(const SDL_Color&color) const;
		bool operator==(const Color&color) const;
		operator ValueRGBA() const;
		operator SDL_Color() const;
		
		int getRGBA();
		
		bool equals(const ValueRGBA&color) const;
		bool equals(const SDL_Color&color) const;
		bool equals(const Color&color) const;
	};
}