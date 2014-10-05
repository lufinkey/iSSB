
#include "TogglePane.h"

namespace SmashBros
{
	TogglePane::TogglePane(float x1, float y1, boolean toggle) : Actor(x1,y1)
	{
		Animation*on = new Animation("on",1,"Images/Menus/Rules/Items/toggle_on.png");
		Animation*off = new Animation("off",1,"Images/Menus/Rules/Items/toggle_off.png");
		addAnimation(on);
		addAnimation(off);
		this->toggle = toggle;
		if(toggle)
		{
			changeAnimation("on", FORWARD);
		}
		else
		{
			changeAnimation("off", FORWARD);
		}
	}

	TogglePane::~TogglePane()
	{
		//
	}

	void TogglePane::Update(long gameTime)
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

	void TogglePane::setToggle(boolean toggle)
	{
		this->toggle = toggle;
		onToggle(toggle);
	}

	boolean TogglePane::getToggle()
	{
		return toggle;
	}

	void TogglePane::onRelease()
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

	void TogglePane::onToggle(boolean toggle)
	{
		//Open for implementation
	}
}