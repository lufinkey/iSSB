
#include "BufferedImage.h"
#include "Image.h"
#include "../Output/Console.h"
#include <SDL_image.h>
#include "../Application.h"

namespace GameEngine
{
	BufferedImage::BufferedImage()
	{
		texture = NULL;
		width = 0;
		height = 0;
	}
	
	BufferedImage::BufferedImage(const Image&img)
	{
		texture = SDL_CreateTexture(Application::renderer, SDL_PIXELFORMAT_BGRA8888, SDL_TEXTUREACCESS_STREAMING, (int)img.getWidth(), (int)img.getHeight());
		int pitch;
		
		unsigned int total = img.width*img.height;
		
		pixels.resize(total);
		
		void*pixsVoid = NULL;
		if(SDL_LockTexture(texture, NULL, &pixsVoid, &pitch)<0)
		{
			Console::WriteLine(SDL_GetError());
		}
		ValueRGBA*pixs = (ValueRGBA*)pixsVoid;
		for(unsigned int i=0; i<total; i++)
		{
			ValueRGBA&px = img.pixels[i];
			if(px.a>0)
			{
				pixels[i] = true;
			}
			else
			{
				pixels[i] = false;
			}
			pixs[i] = px;
		}
		
		SDL_UnlockTexture(texture);
		
		width = img.width;
		height = img.height;
	}
	
	BufferedImage::~BufferedImage()
	{
		pixels.resize(0);
		if(texture!=NULL)
		{
			SDL_DestroyTexture(texture);
		}
		width = 0;
		height = 0;
	}
	
	bool BufferedImage::loadFromFile(const String&fileName)
	{
		if(texture!=NULL)
		{
			SDL_DestroyTexture(texture);
			texture = NULL;
			width = 0;
			height = 0;
		}
		SDL_Surface*img = IMG_Load(fileName);
		if(img!=NULL)
		{
			texture = SDL_CreateTextureFromSurface(Application::renderer, img);
			if(texture == NULL)
			{
				Console::WriteLine((String)"Error BufferedImage::loadFromFile(String) " + IMG_GetError());
				SDL_FreeSurface(img);
				return false;
			}
			width = img->w;
			height = img->h;
			unsigned int total = width*height;
			int bpp = img->format->BytesPerPixel;
			if(bpp==4)
			{
				ValueRGBA*pixs = (ValueRGBA*)img->pixels;
				pixels.resize(total);
				for(unsigned int i=0; i<total; i++)
				{
					ValueRGBA&point = pixs[i];
					if(point.a==0)
					{
						pixels[i] = false;
					}
					else
					{
						pixels[i] = true;
					}
				}
			}
			else
			{
				pixels.resize(total);
				for(unsigned int i=0; i<total; i++)
				{
					pixels[i] = true;
				}
			}
			SDL_FreeSurface(img);
			return true;
		}
		Console::WriteLine((String)"Error BufferedImage::loadFromFile(String) " + IMG_GetError());
		return false;
	}
	
	unsigned int BufferedImage::getWidth() const
	{
		return width;
	}
	
	unsigned int BufferedImage::getHeight() const
	{
		return height;
	}
	
	bool BufferedImage::pixelAtPoint(unsigned int index) const
	{
		return pixels[index];
	}
	
	bool BufferedImage::pixelAtPoint(unsigned int x,unsigned int y) const
	{
		return pixels[(width*y)+x];
	}
	
	SDL_Texture*BufferedImage::getTexture() const
	{
		return texture;
	}
}