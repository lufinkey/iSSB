
#include "../../../GameEngine/GameEngine.h"

#pragma once

namespace SmashBros
{
	class Arrows
	{
	private:
		class UpArrow : public Actor
		{
		private:
			Arrows*arrows;
		public:
			UpArrow(Arrows*arrows, float x1, float y1);
			virtual ~UpArrow();

			virtual void onMouseEnter();
			virtual void onMouseLeave();
			virtual void onRelease();
		};

		class DownArrow : public Actor
		{
		private:
			Arrows*arrows;
		public:
			DownArrow(Arrows*arrows, float x1, float y1);
			virtual ~DownArrow();

			virtual void onMouseEnter();
			virtual void onMouseLeave();
			virtual void onRelease();
		};
		
		UpArrow*up;
		DownArrow*down;

		int value,maxValue,minValue,incr;
		float Scale;

	public:
		Arrows(float x1, float y1, float x2, float y2);
		virtual ~Arrows();

		virtual void Update(long gameTime);
		virtual void Draw(Graphics2D&g, long gameTime);
		boolean isClicked();
		boolean wasClicked();
		void setScale(float scale);
		float getScale();
		void setValue(int value);
		int getValue();
		void setProperties(int min, int max, int increment);
	};
}