
#include "../forwards.h"
#include "String.h"
#include <SDL.h>
#include <vector>

#pragma once

namespace GameEngine
{
	typedef struct
	{
		unsigned char r,g,b,a;
	} ValueRGBA;
	
	class BufferedImage
	{
	private:
		SDL_Texture*texture;
		std::vector<bool> pixels;
		unsigned int width,height;
		BufferedImage(const SDL_Texture*texture);
		
	public:
		BufferedImage();
		BufferedImage(const Image&img);
		virtual ~BufferedImage();
		
		bool loadFromFile(const String&fileName);
		
		unsigned int getWidth() const;
		unsigned int getHeight() const;
		
		bool pixelAtPoint(unsigned int index) const;
		bool pixelAtPoint(unsigned int x,unsigned int y) const;
		
		SDL_Texture*getTexture() const;
	};
}