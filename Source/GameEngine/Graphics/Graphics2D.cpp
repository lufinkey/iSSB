
#include "Graphics2D.h"
#include "../GlobalDefs.h"
#include "../Output/Console.h"
#include "../Application.h"
#include "../View.h"
#include <math.h>

namespace GameEngine
{
	ArrayList<StringTexture*> Graphics2D::stringCache = ArrayList<StringTexture*>();
	ArrayList<StringTexture*> Graphics2D::nextStringCache = ArrayList<StringTexture*>();
	
	void Graphics2D::reset()
	{
		setRotation(0,0,0);
		setScale(1,1);
		setTranslation(0,0);
		setAlpha(255);
		setColor(Color::BLACK);
		setImageMask(Color::WHITE);
		font = defaultFont;
		SDL_Rect rect;
		rect.x = 0;
		rect.y = 0;
		rect.w = View::getWidth();
		rect.h = View::getHeight();
		SDL_RenderSetViewport(renderer, &rect);
	}
	
	void Graphics2D::updateStringCache()
	{
		for(int i=0; i<stringCache.size(); i++)
		{
			StringTexture*oldStrTxtr = stringCache.get(i);
			bool stored = false;
			for(int j=0; (j<nextStringCache.size() && !stored); j++)
			{
				StringTexture*strTxtr = nextStringCache.get(j);
				if(strTxtr->equals(*oldStrTxtr))
				{
					stored = true;
				}
			}
			if(!stored)
			{
				delete oldStrTxtr;
			}
		}
		stringCache.clear();
		stringCache = nextStringCache;
		nextStringCache.clear();
	}
	
	void Graphics2D::setClippedDrawRect(RectF&srcrect, RectF&dstrect)
	{
		float srcW = srcrect.right - srcrect.left;
		float srcH = srcrect.bottom - srcrect.top;
		float dstW = dstrect.right - dstrect.left;
		float dstH = dstrect.bottom - dstrect.top;
		
		if(dstrect.left < 0)
		{
			float dif = 0 - dstrect.left;
			float lev = (float)((int)((dif/dstW)*srcW));
			srcrect.left += lev;
			dstrect.left += (float)((lev/srcW)*dstW);
		}
		if(dstrect.top < 0)
		{
			float dif = 0 - dstrect.top;
			float lev = (float)((int)((dif/dstH)*srcH));
			srcrect.top += lev;
			dstrect.top += (float)((lev/srcH)*dstH);
		}
		if(dstrect.right > View::getWidth())
		{
			float dif = dstrect.right - View::getWidth();
			float lev = (float)((int)((dif/dstW)*srcW));
			srcrect.right -= lev;
			dstrect.right -= (float)((lev/srcW)*dstW);
		}
		if(dstrect.bottom > View::getHeight())
		{
			float dif = dstrect.bottom - View::getHeight();
			float lev = (float)((int)((dif/dstH)*srcH));
			srcrect.bottom -= lev;
			dstrect.bottom -= (float)((lev/srcH)*dstH);
		}
	}
	
	Vector2f Graphics2D::getRotationCoords(float x1, float y1)
	{
		if(Rotation == 0)
		{
			return Vector2f(x1,y1);
		}
		else
		{
			float s = sinRad;
			float c = cosRad;
			
			// translate point back to origin:
			x1 -= (rotX*ScaleX);
			y1 -= (rotY*ScaleY);
			
			// rotate point
			float xnew = x1 * c - y1 * s;
			float ynew = x1 * s + y1 * c;
			
			return Vector2f(xnew + (rotX*ScaleX), ynew + (rotY*ScaleY));
		}
	}
	
	Color Graphics2D::getColorWithAlpha(const Color&color)
	{
		return Color(color.r,color.g,color.b,(unsigned char)alpha);
	}
	
	SDL_Texture*Graphics2D::getTextureFromString(const String&text)
	{
		for(int i=0; i<stringCache.size(); i++)
		{
			StringTexture*strTxtr = stringCache.get(i);
			if(strTxtr->font==font && strTxtr->text.equals(text) && strTxtr->size==font->getSize() && strTxtr->style==font->getStyle())
			{
				bool stored = false;
				for(int j=0; (j<nextStringCache.size() && !stored); j++)
				{
					StringTexture*nxtStrTxtr = nextStringCache.get(j);
					if(strTxtr->equals(*nxtStrTxtr))
					{
						stored = true;
					}
				}
				if(!stored)
				{
					nextStringCache.add(strTxtr);
				}
				return strTxtr->texture;
			}
		}
		for(int i=0; i<nextStringCache.size(); i++)
		{
			StringTexture*strTxtr = nextStringCache.get(i);
			if(strTxtr->font==font && strTxtr->text.equals(text) && strTxtr->size==font->getSize() && strTxtr->style==font->getStyle())
			{
				return strTxtr->texture;
			}
		}
		
		SDL_Surface*surface = TTF_RenderText_Solid(font->getTTF(), text, Color::WHITE);
		SDL_Texture*texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
		
		StringTexture*strTxtr = new StringTexture(texture, font, text, font->getSize(), font->getStyle());
		nextStringCache.add(strTxtr);
		return texture;
	}
	
	Graphics2D::Graphics2D(void)
	{
		color = Color::BLACK;
		imageColor = Color::WHITE;
		overlayColor = Color::TRANSPARENT;
		defaultFont = new Font("Fonts/arial.ttf", Font::PLAIN, 12);
		font = defaultFont;
		alpha=255;
		Rotation = 0;
		ScaleX = 1;
		ScaleY = 1;
		rotX = 0;
		rotY = 0;
		tx = 0;
		ty = 0;
		created = false;
	}
	
	Graphics2D::Graphics2D(const Graphics2D&g)
	{
		color = g.color;
		imageColor = g.imageColor;
		overlayColor = g.overlayColor;
		defaultFont = g.defaultFont;
		font = g.font;
		alpha = g.alpha;
		Rotation = g.Rotation;
		ScaleX = g.ScaleX;
		ScaleY = g.ScaleY;
		rotX = g.rotX;
		rotY = g.rotY;
		tx = g.tx;
		ty = g.ty;
		renderer = g.renderer;
		created = true;
	}
	
	Graphics2D::~Graphics2D(void)
	{
		if(!created)
		{
			delete defaultFont;
		}
	}
	
	Graphics2D Graphics2D::create()
	{
		return Graphics2D(*this);
	}
	
	SDL_Renderer*Graphics2D::getRenderer()
	{
		return renderer;
	}
	
	void Graphics2D::setRotation(float rotation)
	{
		this->Rotation = rotation;
		if(Rotation==0)
		{
			sinRad = 0;
			cosRad = 1;
		}
		else
		{
			float radians = (float)degtorad((float)Rotation);
			sinRad = sin(radians);
			cosRad = cos(radians);
		}
	}
	
	void Graphics2D::setRotation(float rotation, float x1, float y1)
	{
		this->Rotation = rotation;
		if(Rotation==0)
		{
			sinRad = 0;
			cosRad = 1;
		}
		else
		{
			float radians = (float)degtorad((float)Rotation);
			sinRad = sin(radians);
			cosRad = cos(radians);
		}
	}
	
	float Graphics2D::getRotation()
	{
		return Rotation;
	}
	
	void Graphics2D::rotate(float rotation)
	{
		this->Rotation += rotation;
		if(Rotation==0)
		{
			sinRad = 0;
			cosRad = 1;
		}
		else
		{
			float radians = (float)degtorad((float)Rotation);
			sinRad = sin(radians);
			cosRad = cos(radians);
		}
	}
	
	void Graphics2D::rotate(float rotation, float x1, float y1)
	{
		this->Rotation += rotation;
		rotX = x1;
		rotY = y1;
		if(Rotation==0)
		{
			sinRad = 0;
			cosRad = 1;
		}
		else
		{
			float radians = (float)degtorad((float)Rotation);
			sinRad = sin(radians);
			cosRad = cos(radians);
		}
	}
	
	void Graphics2D::setScale(float scalex, float scaley)
	{
		ScaleX = scalex;
		ScaleY = scaley;
	}
	
	void Graphics2D::scale(float scalex, float scaley)
	{
		ScaleX*=scalex;
		ScaleY*=scaley;
	}
	
	Vector2f Graphics2D::getScale()
	{
		return Vector2f(ScaleX,ScaleY);
	}
	
	void Graphics2D::setTranslation(float x1, float y1)
	{
		tx = x1;
		ty = y1;
	}
	
	void Graphics2D::translate(float x1, float y1)
	{
		tx+=x1;
		ty+=y1;
	}
	
	void Graphics2D::setColor(const Color&color)
	{
		this->color = color;
	}
	
	const Color& Graphics2D::getColor()
	{
		return color;
	}
	
	void Graphics2D::setImageMask(const Color&color)
	{
		this->imageColor = color;
	}
	
	const Color& Graphics2D::getImageMask()
	{
		return imageColor;
	}
	
	void Graphics2D::setAlpha(unsigned char alpha)
	{
		this->alpha = alpha;
	}
	
	unsigned char Graphics2D::getAlpha()
	{
		return alpha;
	}
	
	void Graphics2D::setFont(Font*font)
	{
		this->font = font;
	}
	
	Font*Graphics2D::getFont()
	{
		return font;
	}
	
	Font*Graphics2D::getDefaultFont()
	{
		return defaultFont;
	}
	
	void Graphics2D::drawString(const String&text, float x1, float y1)
	{
		if(!text.equals(""))
		{
			SDL_Texture*texture = getTextureFromString(text);
			
			int w,h;
			int access;
			unsigned int format;
			
			SDL_QueryTexture(texture, &format, &access, &w, &h);
			
			Vector2f vect = getRotationCoords((x1+tx)*ScaleX,(y1+ty)*ScaleY);
			x1 = vect.x;
			y1 = vect.y;
			y1 -= ((float)font->getSize()*ScaleY);
			
			SDL_Rect srcrect;
			srcrect.x = 0;
			srcrect.y = 0;
			srcrect.w = w;
			srcrect.h = h;
			
			SDL_Rect dstrect;
			dstrect.x = (int)x1;
			dstrect.y = (int)(y1 + ((float)font->getSize()/20) - 1);
			dstrect.w = (int)(w*ScaleX);
			dstrect.h = (int)(h*ScaleY);
			
			SDL_Point center;
			center.x = 0;
			center.y = 0;
			
			SDL_SetTextureAlphaMod(texture, alpha);
			SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
			
			if(renderer!=NULL)
			{
				SDL_RenderCopyEx(renderer, texture, &srcrect, &dstrect, (double)Rotation, &center, SDL_FLIP_NONE);
			}
		}
	}
	
	void Graphics2D::drawLine(float x1,float y1,float x2,float y2)
	{
		Vector2f v1 = getRotationCoords((x1+tx)*ScaleX,(y1+ty)*ScaleY);
		Vector2f v2 = getRotationCoords((x2+tx)*ScaleX,(y2+ty)*ScaleY);
		
		if(renderer!=NULL)
		{
			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, alpha);
			SDL_RenderDrawLine(renderer, (int)v1.x, (int)v1.y, (int)v2.x, (int)v2.y);
		}
	}
	
	void Graphics2D::drawRect(float x1,float y1,float w,float h)
	{
		SDL_Rect rect;
		
		Vector2f vect = getRotationCoords((x1+tx)*ScaleX,(y1+ty)*ScaleY);
		x1 = vect.x;
		y1 = vect.y;
		rect.x = (int)x1;
		rect.y = (int)y1;
		rect.w = (int)(w*ScaleX);
		rect.h = (int)(h*ScaleX);
		
		if(renderer!=NULL)
		{
			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, alpha);
			SDL_RenderDrawRect(renderer, &rect);
		}
	}
	
	void Graphics2D::fillRect(float x1,float y1,float w,float h)
	{
		SDL_Rect rect;
		
		Vector2f vect = getRotationCoords((x1+tx)*ScaleX,(y1+ty)*ScaleY);
		x1 = vect.x;
		y1 = vect.y;
		rect.x = (int)x1;
		rect.y = (int)y1;
		rect.w = (int)(w*ScaleX);
		rect.h = (int)(h*ScaleX);
		
		if(renderer!=NULL)
		{
			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, alpha);
			SDL_RenderFillRect(renderer, &rect);
		}
	}
	
	/*void Graphics2D::drawOval(float x1,float y1,float w,float h)
	{
		sf::CircleShape oval;
		if(w>h)
		{
			float scale = w/h;
			oval = sf::CircleShape(h/2);
			oval.setScale(scale*ScaleX,1*ScaleY);
		}
		else if(h>w)
		{
			float scale = h/w;
			oval = sf::CircleShape(w/2);
			oval.setScale(1*ScaleX,scale*ScaleY);
		}
		else
		{
			oval = sf::CircleShape(w/2);
			oval.setScale(ScaleX,ScaleY);
		}
		
		sf::Vector2f vect = getRotationCoords((x1+tx)*ScaleX,(y1+ty)*ScaleY);
		x1 = vect.x;
		y1 = vect.y;
		oval.setPosition(x1,y1);
		oval.setRotation(Rotation);
		
		oval.setOutlineColor(getColorWithAlpha(color));
		oval.setOutlineThickness(1);
		oval.setFillColor(sf::Color::Transparent);
		window->draw(oval);
	}*/
	
	/*void Graphics2D::fillOval(float x1,float y1,float w,float h)
	{
		sf::CircleShape oval;
		if(w>h)
		{
			float scale = w/h;
			oval = sf::CircleShape(h/2);
			oval.setScale(scale*ScaleX,1*ScaleY);
		}
		else if(h>w)
		{
			float scale = h/w;
			oval = sf::CircleShape(w/2);
			oval.setScale(1*ScaleX,scale*ScaleY);
		}
		else
		{
			oval = sf::CircleShape(w/2);
			oval.setScale(ScaleX,ScaleY);
		}
		
		sf::Vector2f vect = getRotationCoords((x1+tx)*ScaleX,(y1+ty)*ScaleY);
		x1 = vect.x;
		y1 = vect.y;
		oval.setPosition(x1,y1);
		oval.setRotation(Rotation);
		
		oval.setFillColor(getColorWithAlpha(color));
		window->draw(oval);
	}*/
	
	void Graphics2D::drawImage(BufferedImage*img, float x1, float y1)
	{
		SDL_Texture*texture = img->getTexture();
		unsigned int width = img->getWidth();
		unsigned int height = img->getHeight();
		
		SDL_Rect srcrect;
		srcrect.x = 0;
		srcrect.y = 0;
		srcrect.w = width;
		srcrect.h = height;
		
		Vector2f vect = getRotationCoords((x1+tx)*ScaleX, (y1+ty)*ScaleY);
		x1 = vect.x;
		y1 = vect.y;
		
		SDL_Rect dstrect;
		dstrect.x = (int)x1;
		dstrect.y = (int)y1;
		dstrect.w = (int)(width*ScaleX);
		dstrect.h = (int)(height*ScaleY);
		
		SDL_Point center;
		center.x = 0;
		center.y = 0;
		
		SDL_SetTextureColorMod(texture, imageColor.r, imageColor.g, imageColor.b);
		SDL_SetTextureAlphaMod(texture, alpha);
		
		if(renderer!=NULL)
		{
			SDL_RenderCopyEx(renderer, texture, &srcrect, &dstrect, (double)Rotation, &center, SDL_FLIP_NONE);
		}
	}
	
	void Graphics2D::drawImage(BufferedImage*img, float x1, float y1, float w, float h)
	{
		SDL_Texture*texture = img->getTexture();
		unsigned int width = img->getWidth();
		unsigned int height = img->getHeight();
		
		SDL_Rect srcrect;
		srcrect.x = 0;
		srcrect.y = 0;
		srcrect.w = (int)width;
		srcrect.h = (int)height;
		
		Vector2f vect = getRotationCoords((x1+tx)*ScaleX,(y1+ty)*ScaleY);
		x1 = vect.x;
		y1 = vect.y;
		
		SDL_Rect dstrect;
		dstrect.x = (int)x1;
		dstrect.y = (int)y1;
		dstrect.w = (int)(w*ScaleX);
		dstrect.h = (int)(h*ScaleY);
		
		SDL_Point center;
		center.x = 0;
		center.y = 0;
		
		SDL_SetTextureColorMod(texture, imageColor.r, imageColor.g, imageColor.b);
		SDL_SetTextureAlphaMod(texture, alpha);
		
		if(renderer!=NULL)
		{
			SDL_RenderCopyEx(renderer, texture, &srcrect, &dstrect, (double)Rotation, &center, SDL_FLIP_NONE);
		}
	}
	
	void Graphics2D::drawImage(BufferedImage*img, float dx1, float dy1, float dx2, float dy2, int sx1, int sy1, int sx2, int sy2)
	{
		SDL_Texture* texture = img->getTexture();
		
		Vector2f topLeft = getRotationCoords((dx1+tx)*ScaleX, (dy1+ty)*ScaleY);
		double realDx2 = topLeft.x + ((dx2-dx1)*ScaleX);
		double realDy2 = topLeft.y + ((dy2-dy1)*ScaleY);
		
		dx1 = topLeft.x;
		dy1 = topLeft.y;
		dx2 = realDx2;
		dy2 = realDy2;
		
		bool flipHort = false;
		bool flipVert = false;
		SDL_RendererFlip flip = SDL_FLIP_NONE;
		if(dx2 < dx1)
		{
			double tmp = dx1;
			dx1 = dx2;
			dx2 = tmp;
			//really SDL...? I really have to force cast this bitwise operation?
			flip = (SDL_RendererFlip)(flip | SDL_FLIP_HORIZONTAL);
			flipHort = true;
		}
		if(dy2 < dy1)
		{
			double tmp = dy1;
			dy1 = dy2;
			dy2 = tmp;
			//...absolutely brilliant
			flip = (SDL_RendererFlip)(flip | SDL_FLIP_VERTICAL);
			flipVert = true;
		}
		
		SDL_Rect dstrect;
		dstrect.x = (int)dx1;
		dstrect.y = (int)dy1;
		dstrect.w = (int)(dx2 - (double)dstrect.x);
		dstrect.h = (int)(dy2 - (double)dstrect.y);

		SDL_Point center;
		float rotation = Rotation;
		if(flipHort)
		{
			center.x = dstrect.w;
			rotation = -rotation;
		}
		else
		{
			center.x = 0;
		}
		if(flipVert)
		{
			center.y = dstrect.h;
			rotation = -rotation;
		}
		else
		{
			center.y = 0;
		}
		
		SDL_Rect srcrect;
		srcrect.x = (int)sx1;
		srcrect.y = (int)sy1;
		srcrect.w = (int)(sx2 - sx1);
		srcrect.h = (int)(sy2 - sy1);
		
		SDL_SetTextureColorMod(texture, imageColor.r, imageColor.g, imageColor.b);
		SDL_SetTextureAlphaMod(texture, alpha);
		
		if(renderer!=NULL)
		{
			SDL_RenderCopyEx(renderer, texture, &srcrect, &dstrect, (double)rotation, &center, flip);
		}
	}
}
