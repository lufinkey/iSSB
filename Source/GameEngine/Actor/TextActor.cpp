
#include "TextActor.h"
#include "../View.h"
#include "../Application.h"
#include "../Output/Console.h"
#include "../Util/ArrayList.h"

namespace GameEngine
{
	void TextActor::drawString(Graphics2D& g, String text, float x1, float y1)
	{
		String currentLine = "";
		ArrayList<String> lines = ArrayList<String>();
			
		for(int i=0; i<text.length(); i++)
		{
			char c = text.charAt(i);
				
			if(c=='\n')
			{
				lines.add(currentLine);
				currentLine = "";
				currentLine.clear();
			}
			else
			{
				currentLine+=c;
			}
		}
		lines.add(currentLine);
		
		float currentY = y1;
			
		for(int i=(lines.size()-1); i>=0; i--)
		{
			String line = lines.get(i);
			
			int w = 0;
			int h = 0;
			
			this->font->setSize(fontSize);
			this->font->setStyle(fontStyle);
			TTF_SizeText(this->font->getTTF(), line, &w, &h);
			int lineWidth = w;
			int offset = 0;
			switch(alignment)
			{
				case ALIGN_BOTTOMLEFT:
				case ALIGN_TOPLEFT:
				offset = 0;
				break;
					
				case ALIGN_CENTER:
				offset = (width - lineWidth)/2;
				break;
					
				case ALIGN_BOTTOMRIGHT:
				case ALIGN_TOPRIGHT:
				offset = width - lineWidth;
				break;
			}
			g.drawString(line, x1 + offset, currentY);
			currentY-=charHeight;
		}
		
		lines.clear();
	}

	void TextActor::updateSize()
	{
		int tempheight = fontSize;

		int lines = 1;
		for( int pos = 0; pos < text.length(); pos++)
		{
			char c = text.charAt(pos);
			if( c == '\r' || c== '\n' )
			{
			    lines++;
			}
		}
			
		charHeight = tempheight;
			
		height = tempheight*lines; //got the height!

		ArrayList<int> length = ArrayList<int>();
		ArrayList<String> line = ArrayList<String>();
		line.add("");
		length.add(0);
		
		for( int pos = 0; pos < text.length(); pos++)
		{
			char c = text.charAt(pos);
			if( c == '\r' || c== '\n' )
			{
			    length.add(0);
			    line.add("");
			}
			else
			{
			    String newS = line.get(line.size()-1);
			    newS+=c;
			    line.set(line.size()-1, newS);
			    int i = length.get(length.size()-1);
			    i++;
			    length.set(length.size()-1, i);
			}
		}
		int longest = 0;
		if(length.size()>1)
		{
			for(int i=1; i<length.size(); i++)
			{
				int int1 = length.get(i);
				int intlongest = length.get(longest);
				if(int1>intlongest)
				{
					longest = i;
				}
			}
		}
		
		int w = 0;
		int h = 0;
		this->font->setSize(fontSize);
		this->font->setStyle(fontStyle);
		TTF_SizeText(this->font->getTTF(), line.get(longest), &w, &h);
		
		width = w;
		if(line.size()>0 && line.get(longest).length()>0)
		{
			charWidth = width/line.get(longest).length();
		}
		else
		{
			charWidth = 0;
		}

		
		line.clear();
		length.clear();
	}
	
	bool TextActor::checkHover(float x1, float y1)
	{
		int mousex = 0;
		int mousey = 0;
		if(relative)
		{
			mousex = (int)(x1 + View::x);
			mousey = (int)(y1 + View::y);
		}
		else
		{
			mousex = (int)x1;
			mousey = (int)y1;
		}
		switch(alignment)
		{
			case ALIGN_BOTTOMLEFT:
			if (mousex<(x+width) && mousex>x && mousey<y && mousey>(y-height))
			{
				return true;
			}
			break;
	    		
			case ALIGN_BOTTOMRIGHT:
			if (mousex<(x-width) && mousex>x && mousey<y && mousey>(y-height))
			{
				return true;
			}
			break;
	    		
			case ALIGN_CENTER:
			if (mousex<(x+(width/2)) && mousex>(x-(width/2)) && mousey<(y+(height/2)) && mousey>(y-(height/2)))
			{
				return true;
			}
			break;
	    		
			case ALIGN_TOPLEFT:
			if (mousex<(x+width) && mousex>x && mousey<y && mousey>(y+height))
			{
				return true;
			}
			break;
				
			case ALIGN_TOPRIGHT:
			if (mousex<(x-width) && mousex>x && mousey<y && mousey>(y+height))
			{
				return true;
			}
			break;
		}
	    return false;
	}

	float TextActor::getCenterX()
	{
		switch(alignment)
		{
			default:
			case ALIGN_BOTTOMLEFT:
			return this->x + this->width/2;
				
			case ALIGN_BOTTOMRIGHT:
			return this->x - this->width/2;
				
			case ALIGN_CENTER:
			return this->x;
				
			case ALIGN_TOPLEFT:
			return this->x + this->width/2;
				
			case ALIGN_TOPRIGHT:
			return this->x - this->width/2;
		}
	}
		
	float TextActor::getCenterY()
	{
		switch(alignment)
		{
			default:
			case ALIGN_BOTTOMLEFT:
			return this->y - this->height/2;
				
			case ALIGN_BOTTOMRIGHT:
			return this->y - this->height/2;
				
			case ALIGN_CENTER:
			return this->y;
				
			case ALIGN_TOPLEFT:
			return this->y + this->height/2;
				
			case ALIGN_TOPRIGHT:
			return this->y + this->height/2;
		}
	}
		
	Rectangle TextActor::getRect()
	{
		return Rectangle((int)(getCenterX() - width/2), (int)(getCenterY() - height/2), width, height);
	}

	void TextActor::drawActor(Graphics2D& g, long gameTime, bool relativeToScreen)
	{
		unsigned int originalSize = font->getSize();
		int originalStyle = font->getStyle();
		this->font->setSize(fontSize);
		this->font->setStyle(fontStyle);

		//g.setComposite((AlphaComposite.getInstance(AlphaComposite.SRC_OVER, Alpha)));
			
		if(antialiasing)
		{
			//graphics.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
		}
			
		updateSize();
			
		g.setColor(color);
		g.setAlpha((unsigned char)(255 - (Alpha*255)));
		g.setFont(this->font);
			
		float x1;
		float y1;
		if(relativeToScreen)
		{
			x1 = x - View::x;
			y1 = y - View::y;
		}
		else
		{
			x1 = x;
			y1 = y;
		}
			
		bool onscreen = isOnScreen();
			
		if((onscreen && relativeToScreen)||(!relativeToScreen))
		{
			switch(alignment)
			{
				default:
				alignment = ALIGN_BOTTOMLEFT;
					
				case ALIGN_BOTTOMLEFT:
				g.rotate((float)Rotation,x1,y1);
				drawString(g, text, x1, y1);
				break;
					
				case ALIGN_BOTTOMRIGHT:
				g.rotate((float)Rotation,x1-width,y1);
				drawString(g, text, x1-width, y1);
				break;
					
				case ALIGN_CENTER:
				g.rotate((float)Rotation,x1-(width/2),y1+(height/2));
				drawString(g, text, x1-(width/2), y1+(height/2));
				break;
					
				case ALIGN_TOPLEFT:
				g.rotate((float)Rotation,x1,y1+height);
				drawString(g, text, x1, y1+height);
				break;
					
				case ALIGN_TOPRIGHT:
				g.rotate((float)Rotation,x1-width,y1+height);
				drawString(g, text, x1-width, y1+height);
				break;
			}
		}
			
		if(showwire && ((onscreen && relativeToScreen)||(!relativeToScreen)))
		{
			g.setColor(wireframeColor);
			switch(alignment)
			{
				default:
				alignment = ALIGN_BOTTOMLEFT;
				
				case ALIGN_BOTTOMLEFT:
				g.drawRect(x1, y1-height, (float)width, (float)height);
				break;
				
				case ALIGN_BOTTOMRIGHT:
				g.drawRect(x1-width, y1-height, (float)width, (float)height);
				break;
				
				case ALIGN_CENTER:
				g.drawRect(x1-(width/2), y1-(height/2), (float)width, (float)height);
				break;
				
				case ALIGN_TOPLEFT:
				g.drawRect(x1, y1, (float)width, (float)height);
				break;
				
				case ALIGN_TOPRIGHT:
				g.drawRect(x1-width, y1, (float)width, (float)height);
				break;
			}
		}

		font->setSize(originalSize);
		font->setStyle(originalStyle);
		
		g.setRotation(0,0,0);
		g.setAlpha(255);
	}
		
	TextActor::TextActor(String s, Font*f, const Color&c)
	{
		alignment = ALIGN_BOTTOMLEFT;
		text = s;
		font = f;
		color = c;
		x=0;
		y=0;
		
		fontSize = font->getSize();
		fontStyle = font->getStyle();
		
		updateSize();
		originalText = text;
		actorType = 3;

		wireframeColor = Color::GREEN;
		Rotation = 0;
		Alpha = 0;
		touchId = 0;
		currentTouchId = 0;
		charWidth = 0;
		charHeight = 0;
		mouseover = false;
		prevMouseover = false;
		showwire=false;
		clicked = false;
		antialiasing = false;
		relative = true;
	}
	
	TextActor::TextActor(float x1, float y1,String s, Font*f, const Color&c)
	{
		alignment = ALIGN_BOTTOMLEFT;
		text = s;
		font = f;
		color = c;
		x=x1;
		y=y1;

		fontSize = font->getSize();
		fontStyle = font->getStyle();
		
		updateSize();
		originalText = text;
		actorType = 3;

		wireframeColor = Color::GREEN;
		Rotation = 0;
		Alpha = 0;
		charWidth = 0;
		charHeight = 0;
		touchId = 0;
		currentTouchId = 0;
		mouseover = false;
		prevMouseover = false;
		showwire=false;
		clicked = false;
		antialiasing = false;
		relative = true;
	}

	TextActor::~TextActor()
	{
		//
	}
		
	String TextActor::toString()
	{
		return originalText;
	}
		
	void TextActor::formatToBox(int width, int height)
	{
		String newText = "";
		
		int currentWidth = 0;
		float currentHeight = 0;
			
		bool spaceInLine = false;
			
		String currentWord = "";
			
		for(int i=0; i<originalText.length(); i++)
		{
			char c = originalText.charAt(i);
			if(c=='\n')
			{
				newText+=currentWord + '\n';
				int w = 0;
				int h = 0;
				this->font->setSize(fontSize);
				this->font->setStyle(fontStyle);
				TTF_SizeText(this->font->getTTF(), newText, &w, &h);
				currentWidth = 0;
				currentHeight += h;
				currentWord = "";
				spaceInLine = false;
				if(currentHeight>((float)height))
				{
					i = originalText.length();
				}
					
			}
			else
			{
				if(c==' ')
				{
					newText+=currentWord + ' ';
					currentWidth+=charWidth;
					currentWord = "";
					spaceInLine = true;
						
					if(currentWidth>=width)
					{
						newText+='\n';
						int w = 0;
						int h = 0;
						this->font->setSize(fontSize);
						this->font->setStyle(fontStyle);
						TTF_SizeText(this->font->getTTF(), newText, &w, &h);
						currentWidth = 0;
						currentHeight += h;
						spaceInLine = false;
						if(currentHeight>height)
						{
							i = originalText.length();
						}
							
					}
				}
				else
				{
					currentWord+=c;
					currentWidth+=charWidth;
						
					if(currentWidth>=width)
					{
						if(spaceInLine)
						{
							newText+='\n';
							int w = 0;
							int h = 0;
							this->font->setSize(fontSize);
							this->font->setStyle(fontStyle);
							TTF_SizeText(this->font->getTTF(), newText, &w, &h);
							currentHeight += h;
							TTF_SizeText(this->font->getTTF(), currentWord, &w, &h);
							currentWidth = w;
							spaceInLine = false;
								
							if(currentHeight>height)
							{
								i = originalText.length();
							}
						}
					}
				}
			}
		}

		newText+=currentWord;
		
		text = newText;
		updateSize();
	}
		
	void TextActor::Update(long gameTime)
	{
		prevclicked = clicked;
		
		long prevTouchId = currentTouchId;
		
		bool onmouseenter = false;
		bool onmouseleave = false;
		bool onclick = false;
		bool onrelease = false;

		if(mouseOver())
		{
			bool prevMouseOver = mouseover;
			if(!mouseover)
	    	{
	    		mouseover=true;
	    		onmouseenter = true;
	    	}
			if(!prevMouseOver && !Application::checkPrevTouchActive(touchId))
	    	{
	    		clicked = true;
				onclick = true;
	    	}
		}
		else if(mouseover)
		{
			mouseover=false;
			onmouseleave = true;
		}
		if(clicked && prevMouseover && !Application::checkTouchActive(prevTouchId))
		{
			clicked = false;
			onrelease = true;
		}
		
		if(prevclicked && !Application::checkTouchActive(currentTouchId))
		{
			clicked = false;
		}
		
		prevMouseover = mouseover;
		currentTouchId = touchId;
		
		if(onmouseenter)
		{
			onMouseEnter();
		}
		if(onclick)
		{
			onClick();
		}
		if(onmouseleave)
		{
			onMouseLeave();
		}
		if(onrelease)
		{
			onRelease();
		}
	}
		
	void TextActor::Draw(Graphics2D& g, long gameTime)
	{
		drawActor(g,gameTime,relative);
	}
		
	bool TextActor::isOnScreen()
	{
		int left1, left2;
	    int right1, right2;
	    int top1, top2;
	    int bottom1, bottom2;
	        
	    Rectangle rect = getRect();
	
	    left1 = (int)rect.x;
	    left2 = (int)View::x;
	    right1 = (int)rect.x+rect.width;
	    right2 = (int)View::x+(View::ScaleWidth());
	    top1 = (int)rect.y;
	    top2 = (int)View::y;
	    bottom1 = (int)rect.y+rect.height;
	    bottom2 = (int)View::y+(View::ScaleHeight());
			
	    if (bottom1 < top2)
	    {
	        return false;
	    }
	    if (top1 > bottom2)
	    {
	        return false;
	    }
	
	    if (right1 < left2)
	    {
	        return false;
	    }
	    if (left1 > right2)
	    {
	        return false;
	    }
	
	    return true;
	}
		
	void TextActor::showWireframe(bool toggle)
	{
		showwire = toggle;
	}
	
	void TextActor::setWireframeColor(const Color&c)
	{
		wireframeColor = c;
	}
		
	void TextActor::setText(String s)
	{
		text = s;
		originalText = text;
		updateSize();
	}
		
	String TextActor::getText()
	{
		return text;
	}
		
	void TextActor::setFont(Font*f)
	{
		font = f;
		updateSize();
	}
		
	Font*TextActor::getFont()
	{
		return font;
	}
		
	void TextActor::setSize(unsigned int size)
	{
		fontSize = size;
		updateSize();
	}
		
	int TextActor::getSize()
	{
		return fontSize;
	}
		
	void TextActor::setStyle(int style)
	{
		fontStyle = style;
	}
		
	void TextActor::setColor(const Color&c)
	{
		color = c;
	}
		
	Color TextActor::getColor()
	{
		return color;
	}
		
	void TextActor::setAlignment(unsigned char align)
	{
		if(align<=4)
		{
			alignment = align;
		}
		else
		{
			Console::WriteLine((String)"Error: Invalid argument " + align + (String)" for method setAlignment(unsigned char)");
		}
	}
	
	unsigned char TextActor::getAlignment()
	{
		return alignment;
	}
	
	void TextActor::relativeToView(bool toggle)
	{
		relative = toggle;
	}

	void TextActor::onMouseEnter() //When mouse enters Actor
	{
	    //Open for implementation
	}
	    
	void TextActor::onMouseLeave() //When mouse enters Actor
	{
	    //Open for implementation
	}
		
	void TextActor::onClick() //When Actor is clicked
	{
		//Open for implementation
	}
		
	void TextActor::onRelease() //When Actor's click is released
	{
		//Open for implementation
	}
		
	bool TextActor::mouseOver()
	{
		if(mouseover)
		{
			if(Application::checkTouchActive(currentTouchId))
			{
				if(checkHover(Application::TouchX(currentTouchId), Application::TouchY(currentTouchId)))
				{
					return true;
				}
			}
		}
		ArrayList<TouchPoint> points = Application::getTouchPoints();
		for(int i=0; i<points.size(); i++)
		{
			TouchPoint&point = points.get(i);
			if(checkHover(point.x, point.y))
			{
				touchId = point.ID;
				return true;
			}
		}
		return false;
	}
		
	bool TextActor::isClicked()
	{
	    return clicked;
	}

	bool TextActor::wasClicked()
	{
		return prevclicked;
	}
	
	long TextActor::getTouchId()
	{
		return currentTouchId;
	}
		
	void TextActor::antiAliasing(bool toggle)
	{
		antialiasing = toggle;
	}
		
	void TextActor::setRotation(double degrees) //sets rotation of Actor in degrees
	{
	    Rotation = degrees;
	}
		
	double TextActor::getRotation() //returns current rotation of Actor in degrees
	{
	    return Rotation;
	}
	    
	void TextActor::setAlpha(float alpha)
	{
	    if(alpha<=1)
		{
			Alpha = alpha;
		}
	}
	    
	float TextActor::getAlpha()
	{
	    return Alpha;
	}
}