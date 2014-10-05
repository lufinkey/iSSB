
#include "../../../GameEngine/GameEngine.h"

#pragma once

namespace SmashBros
{
	class MenuBar : public Actor
	{
	private:
		TextActor*label;
		int labelSize;
		float xOffset;

	public:
		MenuBar(float x1, float y1, String label);
		virtual ~MenuBar();

		virtual void Update(long gameTime);
		virtual void Draw(Graphics2D&g, long gameTime);
		
		void setTextOffsetX(float x1);
		float getTextOffsetX();
		void setLabel(String str);
		String getLabel();
	};
}