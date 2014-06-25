
#include "forwards.h"
#include "Graphics/Graphics2D.h"

#pragma once

namespace GameEngine
{
	class View
	{
	private:
		friend class Application;
		
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
		
		static void setScaleSize(int w, int h);
		
		static int Width();
		static int Height();
		static int ScaleWidth();
		static int ScaleHeight();
		
		static void Update(Graphics2D& g);
		static void Draw(Graphics2D& g);
	};
}