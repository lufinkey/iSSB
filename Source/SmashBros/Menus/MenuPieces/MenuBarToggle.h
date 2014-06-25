
#include "MenuBar.h"
#include "ToggleButton.h"

#pragma once

namespace SmashBros
{
	class MenuBarToggle : public MenuBar
	{
	private:
		class MenuBarToggleButton : public ToggleButton
		{
		private:
			MenuBarToggle*menuBar;
		public:
			MenuBarToggleButton(MenuBarToggle*menuBar, float x1, float y1, boolean toggle=false);
			virtual ~MenuBarToggleButton();

			virtual void onToggle(boolean toggle);
		};

		MenuBarToggleButton*toggleButton;
		boolean toggle;
		void whenToggled(boolean toggle);

	public:
		MenuBarToggle(float x1, float y1, String label, boolean toggle=false);
		virtual ~MenuBarToggle();

		virtual void Update(long gameTime);
		virtual void Draw(Graphics2D&g, long gameTime);
		virtual void onToggle(boolean toggle);

		void setToggle(boolean toggle);
		boolean getToggle();
	};
}