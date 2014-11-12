
#include <SDL_ttf.h>
#include "ArrayList.h"
#include "String.h"

#pragma once

namespace GameEngine
{
	class Font
	{
	private:
		typedef struct
		{
			unsigned int size;
			TTF_Font*font;
		} FontSize;
		
		ArrayList<FontSize> sizes;
		TTF_Font*font;
		
		unsigned int size;
		int style;
		
		String fontPath;
		
	public:
		static const int PLAIN = 0;
		static const int BOLD = 1;
		static const int ITALIC = 2;
		static const int UNDERLINE = 3;
		static const int STRIKETHROUGH = 4;
		
		Font(const String&fileName, int style = PLAIN, unsigned int size = 1);
		virtual ~Font();
		
		int getStyle();
		void setStyle(int style);
		
		unsigned int getSize();
		void setSize(unsigned int size);
		
		TTF_Font*getTTF();
	};
	
	class StringTexture
	{
		friend class Graphics2D;
	private:
		Font*font;
		String text;
		unsigned int size;
		int style;
		SDL_Texture*texture;
		
	public:
		StringTexture(SDL_Texture*texture, Font*font, const String&text, unsigned int size, int style);
		~StringTexture();
		
		bool equals(const StringTexture&strTxtr);
	};
}