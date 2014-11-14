
#include "forwards.h"
#include "Graphics/Graphics2D.h"

#pragma once

namespace GameEngine
{
	class View
	{
		friend class Application;
	private:
		static int oldWidth;
		static int oldHeight;
		
		static int windowWidth;
		static int windowHeight;
		
		static int scaleWidth;
		static int scaleHeight;
		
		static float multScale;
		static float letterBoxW;
		static float letterBoxH;
		
	public:
		static float x;
		static float y;
		
		static float Zoom;
		
		static void setSize(int w, int h);
		static void setScaleSize(int w, int h);
		
		static int getWidth();
		static int getHeight();
		static int getScalingWidth();
		static int getScalingHeight();
		
		static void Update(Graphics2D& g);
		static void Draw(Graphics2D& g);
	};
}