
#include "ToggleButton.h"

namespace SmashBros
{
	ToggleButton::ToggleButton(float x1, float y1, boolean toggle) : Actor(x1,y1)
	{
		Animation*on = new Animation("on",1,"Images/Menus/Buttons/Generic/toggle_on.png");
		Animation*off = new Animation("off",1,"Images/Menus/Buttons/Generic/toggle_off.png");
		addAnimation(on);
		addAnimation(off);
		if(toggle)
		{
			changeAnimation("on", FORWARD);
		}
		else
		{
			changeAnimation("off", FORWARD);
		}
		this->toggle = toggle;
	}

	ToggleButton::~ToggleButton()
	{
		//
	}

	void ToggleButton::Update(long gameTime)
	{
		Actor::Update(gameTime);
		if(toggle)
		{
			changeAnimation("on",FORWARD);
		}
		else
		{
			changeAnimation("off",FORWARD);
		}
	}

	void ToggleButton::setToggle(boolean toggle)
	{
		this->toggle = toggle;
		if(toggle)
		{
			changeAnimation("on",FORWARD);
		}
		else
		{
			changeAnimation("off",FORWARD);
		}
		onToggle(toggle);
	}

	boolean ToggleButton::getToggle()
	{
		return toggle;
	}

	void ToggleButton::onRelease()
	{
		if(toggle)
		{
			toggle = false;
		}
		else
		{
			toggle = true;
		}
		onToggle(toggle);
	}

	void ToggleButton::onToggle(boolean toggle)
	{
		//Open for implementation
	}
}