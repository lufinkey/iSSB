
#include "../forwards.h"
#include "Color.h"

#pragma once

namespace GameEngine
{
	class Image
	{
		friend class BufferedImage;
	private:
		ValueRGBA*pixels;
		unsigned int width, height;
		
	public:
		Image();
		~Image();
		
		void create(unsigned int w, unsigned int h, const ValueRGBA&color);
		bool loadFromFile(const String&fileName);
		
		void setPixel(unsigned int x, unsigned int y, const ValueRGBA&color);
		void setPixel(unsigned int index, const ValueRGBA&color);
		ValueRGBA getPixel(unsigned int x, unsigned int y);
		ValueRGBA getPixel(unsigned int index);
		
		unsigned int getWidth() const;
		unsigned int getHeight() const;
	};
}