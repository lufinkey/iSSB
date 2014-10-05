
#include "MenuBarSmallButton.h"

namespace SmashBros
{
	MenuBarSmallButton::MenuBarSmallButton(float x1, float y1, String label) : MenuBarSmall(x1,y1,label)
	{
		hasTarget = false;
		addAnimation(new Animation("hover",1,"Images/Menus/Buttons/Generic/options_bar_small_selected.png"));
	}

	MenuBarSmallButton::MenuBarSmallButton(float x1, float y1, String label, String target) : MenuBarSmall(x1,y1,label)
	{
		hasTarget = true;
		this->target = target;
		this->addAnimation(new Animation("hover",1,"Images/Menus/Buttons/Generic/options_bar_small_selected.png"));
	}

	MenuBarSmallButton::~MenuBarSmallButton()
	{
		//
	}

	void MenuBarSmallButton::onMouseEnter()
	{
		changeAnimation("hover",FORWARD);
	}

	void MenuBarSmallButton::onMouseLeave()
	{
		changeAnimation("normal",FORWARD);
	}

	void MenuBarSmallButton::onRelease()
	{
		if(hasTarget)
		{
			ScreenManager::GoToScreen(target);
		}
	}
}