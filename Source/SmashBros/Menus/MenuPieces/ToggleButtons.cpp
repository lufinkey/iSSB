
#include "ToggleButtons.h"

namespace SmashBros
{
	ToggleButtons::DualToggleButton::DualToggleButton(ToggleButtons*holder, byte num, float x1, float y1, boolean toggle) : ToggleButton(x1,y1,toggle)
	{
		this->holder = holder;
		this->num = num;
	}

	ToggleButtons::DualToggleButton::~DualToggleButton()
	{
		//
	}

	void ToggleButtons::DualToggleButton::onRelease()
	{
		ToggleButton::onRelease();
		switch(num)
		{
			case 1:
			if(getToggle())
			{
				holder->toggle = 1;
				holder->t2->setToggle(false);
			}
			else
			{
				holder->toggle = 2;
				holder->t2->setToggle(true);
			}
			break;

			case 2:
			if(getToggle())
			{
				holder->toggle = 2;
				holder->t1->setToggle(false);
			}
			else
			{
				holder->toggle = 1;
				holder->t1->setToggle(true);
			}
			break;
		}
	}

	ToggleButtons::ToggleButtons(float x1,float y1, float x2, float y2)
	{
		toggle = 1;
		t1 = new DualToggleButton(this,1,x1,y1,true);
		t2 = new DualToggleButton(this,2,x2,y2,false);
	}

	ToggleButtons::~ToggleButtons()
	{
		delete t1;
		delete t2;
	}

	void ToggleButtons::Update(long gameTime)
	{
		byte prevToggle = toggle;
		t1->Update(gameTime);
		t2->Update(gameTime);
		if(toggle!=prevToggle)
		{
			onToggle(toggle);
		}
	}

	void ToggleButtons::Draw(Graphics2D&g, long gameTime)
	{
		t1->Draw(g, gameTime);
		t2->Draw(g, gameTime);
	}

	byte ToggleButtons::getToggle()
	{
		return toggle;
	}

	void ToggleButtons::setToggle(byte toggle)
	{
		if(toggle>=2)
		{
			toggle = 2;
			t1->setToggle(false);
			t2->setToggle(true);
		}
		else if(toggle<=1)
		{
			toggle = 1;
			t1->setToggle(true);
			t2->setToggle(false);
		}
		this->toggle = toggle;
		onToggle(this->toggle);
	}
	
	void ToggleButtons::onToggle(byte toggle)
	{
		//Open for implementation
	}

	void ToggleButtons::setScale(float scale)
	{
		Scale = scale;
		t1->setScale(Scale);
		t2->setScale(Scale);
	}
	
	bool ToggleButtons::isClicked()
	{
		if(t1->isClicked() || t2->isClicked())
		{
			return true;
		}
		return false;
	}
}