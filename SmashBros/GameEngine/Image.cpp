
#include "Image.h"
#include "BufferedImage.h"
#include "SDL_image.h"

namespace GameEngine
{
	Image::Image()
	{
		pixels = NULL;
		width = 0;
		height = 0;
	}
	
	Image::~Image()
	{
		if(pixels!=NULL)
		{
			delete pixels;
			pixels = NULL;
		}
		width = 0;
		height = 0;
	}
	
	void Image::create(unsigned int w, unsigned int h, const ValueRGBA&color)
	{
		unsigned int total = w*h;
		if(pixels!=NULL)
		{
			delete pixels;
			pixels = NULL;
		}
		
		pixels = new ValueRGBA[total];
		
		for(unsigned int i=0; i<total; i++)
		{
			pixels[i] = color;
		}
		
		width = w;
		height = h;
	}
	
	bool Image::loadFromFile(const String&fileName)
	{
		SDL_Surface*img = IMG_Load(fileName);
		
		if(img!=NULL)
		{
			if(pixels!=NULL)
			{
				delete pixels;
				pixels = NULL;
			}
			
			width = 0;
			height = 0;
			unsigned int bpp = (unsigned int)img->format->BytesPerPixel;
			
			width = img->w;
			height = img->h;
			unsigned int total = width*height;
			
			unsigned int counter = 0;
			
			unsigned char*imgPx = (unsigned char*)img->pixels;
			
			for(unsigned int i=0; i<total; i++)
			{
				ValueRGBA px;
				switch(bpp)
				{
					case 1:
					px.r = imgPx[counter];
					px.g = imgPx[counter];
					px.b = imgPx[counter];
					px.a = 255;
					break;
					
					case 2:
					px.r = imgPx[counter];
					px.g = imgPx[counter+1];
					px.b = imgPx[counter+1];
					px.a = 255;
					break;
					
					case 3:
					px.r = imgPx[counter];
					px.g = imgPx[counter+1];
					px.b = imgPx[counter+2];
					px.a = 255;
					break;
					
					case 4:
					px.r = imgPx[counter];
					px.g = imgPx[counter+1];
					px.b = imgPx[counter+2];
					px.a = imgPx[counter+3];
					break;
				}
				pixels[i] = px;
				counter+=bpp;
			}
			
			SDL_FreeSurface(img);
			
			return true;
		}
		return false;
	}
	
	void Image::setPixel(unsigned int x, unsigned int y, const ValueRGBA&color)
	{
		pixels[(width*y)+x] = color;
	}
	
	void Image::setPixel(unsigned int index, const ValueRGBA&color)
	{
		pixels[index] = color;
	}
	
	ValueRGBA Image::getPixel(unsigned int x, unsigned int y)
	{
		return pixels[(width*y)+x];
	}
	
	ValueRGBA Image::getPixel(unsigned int index)
	{
		return pixels[index];
	}
	
	unsigned int Image::getWidth() const
	{
		return width;
	}
	
	unsigned int Image::getHeight() const
	{
		return height;
	}
}