
#include "ToggleButton.h"

#pragma once

namespace SmashBros
{
	class ToggleButtons
	{
	private:
		class DualToggleButton : public ToggleButton
		{
		private:
			byte num;
			ToggleButtons*holder;
		public:
			DualToggleButton(ToggleButtons*holder, byte num, float x1, float y1, boolean toggle);
			virtual ~DualToggleButton();

			virtual void onRelease();
		};

		DualToggleButton*t1;
		DualToggleButton*t2;

		float Scale;
		byte toggle;

	public:
		ToggleButtons(float x1, float y1, float x2, float y2);
		virtual ~ToggleButtons();

		virtual void Update(long gameTime);
		virtual void Draw(Graphics2D&g, long gameTime);
		virtual void onToggle(byte toggle);
		
		byte getToggle();
		void setToggle(byte Toggle);
		void setScale(float scale);
		
		bool isClicked();
	};
}