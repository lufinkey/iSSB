
#include "Arrows.h"

namespace SmashBros
{
	Arrows::UpArrow::UpArrow(Arrows*arrows, float x1, float y1) : Actor(x1,y1)
	{
		this->arrows = arrows;
	}

	Arrows::UpArrow::~UpArrow()
	{
		//
	}

	void Arrows::UpArrow::onMouseEnter()
	{
		changeAnimation("hover",FORWARD);
	}

	void Arrows::UpArrow::onMouseLeave()
	{
		changeAnimation("normal",FORWARD);
	}

	void Arrows::UpArrow::onRelease()
	{
		arrows->value+=arrows->incr;
		if(arrows->value > arrows->maxValue)
		{
			arrows->value = arrows->minValue;
		}
	}

	Arrows::DownArrow::DownArrow(Arrows*arrows, float x1, float y1) : Actor(x1,y1)
	{
		this->arrows = arrows;
	}

	Arrows::DownArrow::~DownArrow()
	{
		//
	}

	void Arrows::DownArrow::onMouseEnter()
	{
		changeAnimation("hover",FORWARD);
	}

	void Arrows::DownArrow::onMouseLeave()
	{
		changeAnimation("normal",FORWARD);
	}

	void Arrows::DownArrow::onRelease()
	{
		arrows->value-=arrows->incr;
		if(arrows->value < arrows->minValue)
		{
			arrows->value = arrows->maxValue;
		}
	}

	Arrows::Arrows(float x1, float y1, float x2, float y2)
	{
		up = new UpArrow(this,x1,y1);
		down = new DownArrow(this,x2,y2);
		up->addAnimation(new Animation("normal",1,"Images/Menus/Buttons/Generic/arrow_up.png"));
		up->addAnimation(new Animation("hover",1,"Images/Menus/Buttons/Generic/arrow_up_selected.png"));
		up->changeAnimation("normal", FORWARD);
		down->addAnimation(new Animation("normal",1,"Images/Menus/Buttons/Generic/arrow_down.png"));
		down->addAnimation(new Animation("hover",1,"Images/Menus/Buttons/Generic/arrow_down_selected.png"));
		down->changeAnimation("normal", FORWARD);
		Scale = 1;
	}

	Arrows::~Arrows()
	{
		delete up;
		delete down;
	}

	void Arrows::Update(long gameTime)
	{
		up->Update(gameTime);
		down->Update(gameTime);
	}

	void Arrows::Draw(Graphics2D&g, long gameTime)
	{
		up->Draw(g, gameTime);
		down->Draw(g, gameTime);
	}

	boolean Arrows::isClicked()
	{
		if(up->isClicked() || down->isClicked())
		{
			return true;
		}
		return false;
	}

	boolean Arrows::wasClicked()
	{
		if(up->wasClicked() || down->wasClicked())
		{
			return true;
		}
		return false;
	}
	
	void Arrows::setScale(float scale)
	{
		up->setScale(scale);
		down->setScale(scale);
		Scale = scale;
	}
	
	float Arrows::getScale()
	{
		return Scale;
	}
	
	void Arrows::setValue(int value)
	{
		this->value = value;
	}

	int Arrows::getValue()
	{
		return value;
	}

	void Arrows::setProperties(int min, int max, int increment)
	{
		minValue = min;
		maxValue = max;
		incr = increment;
	}
}