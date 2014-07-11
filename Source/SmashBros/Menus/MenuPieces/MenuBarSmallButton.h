
#include "MenuBarSmall.h"

#pragma once

namespace SmashBros
{
	class MenuBarSmallButton : public MenuBarSmall
	{
	private:
		boolean hasTarget;
		String target;

	public:
		MenuBarSmallButton(float x1, float y1, String label);
		MenuBarSmallButton(float x1, float y1, String label, String target);
		virtual ~MenuBarSmallButton();

		virtual void onMouseEnter();
		virtual void onMouseLeave();
		virtual void onRelease();
	};
}