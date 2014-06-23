
#include "View.h"
#include "Application.h"
#include "Console.h"
#include <math.h>

namespace GameEngine
{
	float View::x = 0;
	float View::y = 0;
	
	float View::Zoom = 1.0;
	
	int View::windowWidth = 480;
	int View::windowHeight = 320;
	
	int View::scaleWidth = 480;
	int View::scaleHeight = 320;
	
	float View::multScale = 1;
	float View::letterBoxW = 0;
	float View::letterBoxH = 0;
	
	void View::setScaleSize(int w, int h)
	{
		scaleWidth=w;
		scaleHeight=h;
	}
	
	int View::Width()
	{
		return windowWidth;
	}
	
	int View::Height()
	{
		return windowHeight;
	}
	
	int View::ScaleWidth()
	{
		return scaleWidth;
	}
	
	int View::ScaleHeight()
	{
		return scaleHeight;
	}
	
	void View::Update(Graphics2D&g)
	{
		multScale = 1;
		if(Application::scalescreen)
		{
			float ratX = (float)windowWidth/(float)scaleWidth;
			float ratY = (float)windowHeight/(float)scaleHeight;
			if(ratX<ratY)
			{
				multScale = ratX;
			}
			else
			{
				multScale = ratY;
			}
		}
		g.scale(Zoom*multScale,Zoom*multScale);
		float difX;
		float difY;
		if(Application::scalescreen)
		{
			difX = (float)((windowWidth - (windowWidth*Zoom))+(windowWidth - (scaleWidth*multScale)))/(float)(2*Zoom*multScale);
			difY = (float)((windowHeight - (windowHeight*Zoom))+(windowHeight - (scaleHeight*multScale)))/(float)(2*Zoom*multScale);
			letterBoxW = (float)abs((windowWidth - (scaleWidth*multScale))/2);
			letterBoxH = (float)abs((windowHeight - (scaleHeight*multScale))/2);
		}
		else
		{
			difX = (float)(windowWidth - (windowWidth*Zoom))/(float)(2*Zoom);
			difY = (float)(windowHeight - (windowHeight*Zoom))/(float)(2*Zoom);
			letterBoxW = (float)abs((windowWidth - (scaleWidth*multScale))/2);
			letterBoxH = (float)abs((windowHeight - (scaleHeight*multScale))/2);
		}
		g.translate(difX,difY);
	}
	
	void View::Draw(Graphics2D&g)
	{
		g.setScale(1,1);
		g.setTranslation(0,0);
		if(Application::scalescreen)
		{
			g.setColor(Color::BLACK);
			g.setFont(g.defaultFont);
			if(letterBoxW>0)
			{
				g.fillRect(0,0,letterBoxW,(float)windowHeight);
				g.fillRect((((float)windowWidth)-letterBoxW),0,letterBoxW,(float)windowHeight);
			}
			if(letterBoxH>0)
			{
				g.fillRect(0,0,(float)windowWidth,letterBoxH);
				g.fillRect(0,((float)windowHeight-letterBoxH),(float)windowWidth,letterBoxH);
			}
			
			if(Application::showfps)
			{
				g.setColor(Color::BLACK);
				g.drawString((String)Application::realFPS + (String)" fps", (letterBoxW+(30*multScale)), (letterBoxH+(50*multScale)));
			}
		}
		else
		{
			if(Application::showfps)
			{
				g.setColor(Color::BLACK);
				g.drawString((String)Application::realFPS + (String)" fps", 30, 50);
			}
		}
	}
}