
#include "MenuBar.h"

#pragma once

namespace SmashBros
{
	class MenuBarValue : public MenuBar
	{
	private:
		class LeftArrow : public Actor
		{
		private:
			MenuBarValue*menuBar;
		public:
			LeftArrow(MenuBarValue*menuBar, float x1, float y1);
			virtual ~LeftArrow();

			virtual void onMouseEnter();
			virtual void onMouseLeave();
			virtual void onRelease();
		};

		class RightArrow : public Actor
		{
		private:
			MenuBarValue*menuBar;
		public:
			RightArrow(MenuBarValue*menuBar, float x1, float y1);
			virtual ~RightArrow();

			virtual void onMouseEnter();
			virtual void onMouseLeave();
			virtual void onRelease();
		};

		LeftArrow*leftArrow;
		RightArrow*rightArrow;

		TextActor*label2;
		int label2Size;

		TextActor*valueActor;
		int valueActorSize;
		boolean numLabel;

		int value;
		int minValue, maxValue;
		int incr;

		void createMenuBar();

	public:
		MenuBarValue(float x1, float y1, String label);
		MenuBarValue(float x1, float y1, String label, String label2);
		virtual ~MenuBarValue();

		virtual void Update(long gameTime);
		virtual void Draw(Graphics2D&g, long gameTime);
		
		int getValue();
		void setValue(int value);
		void setProperties(int min, int max, int increment);
	};
}