
#include "Font.h"
#include "../Output/Console.h"

namespace GameEngine
{
	Font::Font(const String&fileName, int style, unsigned int size)
	{
		font = TTF_OpenFont(fileName, (int)size);
		
		if(font==NULL)
		{
			Console::WriteLine((String)"error loading font " + fileName);
		}
		
		if(style==BOLD)
		{
			TTF_SetFontStyle(font, TTF_STYLE_BOLD);
		}
		else if(style==ITALIC)
		{
			TTF_SetFontStyle(font, TTF_STYLE_ITALIC);
		}
		else if(style==UNDERLINE)
		{
			TTF_SetFontStyle(font, TTF_STYLE_UNDERLINE);
		}
		else if(style==STRIKETHROUGH)
		{
			TTF_SetFontStyle(font, TTF_STYLE_STRIKETHROUGH);
		}
		
		this->style = style;
		this->size = size;
		fontPath = fileName;
	}
	
	Font::~Font()
	{
		TTF_CloseFont(font);
		
		for(int i=0; i<sizes.size(); i++)
		{
			TTF_CloseFont(sizes.get(i).font);
		}
		
		sizes.clear();
	}
	
	int Font::getStyle()
	{
		return style;
	}
	
	void Font::setStyle(int style)
	{
		if(this->style!=style)
		{
			if(style==PLAIN)
			{
				TTF_SetFontStyle(font, TTF_STYLE_NORMAL);
			}
			else if(style==BOLD)
			{
				TTF_SetFontStyle(font, TTF_STYLE_BOLD);
			}
			else if(style==ITALIC)
			{
				TTF_SetFontStyle(font, TTF_STYLE_ITALIC);
			}
			else if(style==UNDERLINE)
			{
				TTF_SetFontStyle(font, TTF_STYLE_UNDERLINE);
			}
			else if(style==STRIKETHROUGH)
			{
				TTF_SetFontStyle(font, TTF_STYLE_STRIKETHROUGH);
			}
			
			this->style = style;
		}
	}
	
	unsigned int Font::getSize()
	{
		return size;
	}
	
	void Font::setSize(unsigned int size)
	{
		if(size != this->size)
		{
			for(int i=0; i<sizes.size(); i++)
			{
				FontSize fontSize = sizes.get(i);
				if(fontSize.size == size)
				{
					TTF_Font*font = fontSize.font;
					fontSize.font = this->font;
					fontSize.size = this->size;
					sizes.set(i, fontSize);
					this->font = font;
					this->size = size;
					
					if(style==PLAIN)
					{
						TTF_SetFontStyle(this->font, TTF_STYLE_NORMAL);
					}
					else if(style==BOLD)
					{
						TTF_SetFontStyle(this->font, TTF_STYLE_BOLD);
					}
					else if(style==ITALIC)
					{
						TTF_SetFontStyle(this->font, TTF_STYLE_ITALIC);
					}
					else if(style==UNDERLINE)
					{
						TTF_SetFontStyle(this->font, TTF_STYLE_UNDERLINE);
					}
					else if(style==STRIKETHROUGH)
					{
						TTF_SetFontStyle(this->font, TTF_STYLE_STRIKETHROUGH);
					}
					return;
				}
			}
			
			FontSize fontSize = {this->size, this->font};
			sizes.add(fontSize);
			this->font = TTF_OpenFont(fontPath, size);
			this->size = size;
			
			if(style==PLAIN)
			{
				TTF_SetFontStyle(this->font, TTF_STYLE_NORMAL);
			}
			else if(style==BOLD)
			{
				TTF_SetFontStyle(this->font, TTF_STYLE_BOLD);
			}
			else if(style==ITALIC)
			{
				TTF_SetFontStyle(this->font, TTF_STYLE_ITALIC);
			}
			else if(style==UNDERLINE)
			{
				TTF_SetFontStyle(this->font, TTF_STYLE_UNDERLINE);
			}
			else if(style==STRIKETHROUGH)
			{
				TTF_SetFontStyle(this->font, TTF_STYLE_STRIKETHROUGH);
			}
		}
	}
	
	TTF_Font*Font::getTTF()
	{
		return font;
	}
	
	StringTexture::StringTexture(SDL_Texture*texture, Font*font, const String&text, unsigned int size, int style)
	{
		this->texture = texture;
		this->font = font;
		this->text = text;
		this->size = size;
		this->style = style;
	}
	
	StringTexture::~StringTexture()
	{
		SDL_DestroyTexture(texture);
	}
	
	bool StringTexture::equals(const StringTexture&strTxtr)
	{
		if(font==strTxtr.font && text.equals(strTxtr.text) && size==strTxtr.size && style==strTxtr.style)
		{
			return true;
		}
		return false;
	}
}