
#include "MenuBarSmall.h"

namespace SmashBros
{
	MenuBarSmall::MenuBarSmall(float x1, float y1, String label) : Actor(x1,y1)
	{
		labelSize = 16;
		xOffset = 0;
		addAnimation(new Animation("normal",1,"Images/Menus/Buttons/Generic/options_bar_small.png"));
		changeAnimation("normal",FORWARD);
		this->label = new TextActor(label,AssetManager::getFont("Fonts/arial.ttf", Font::BOLD, labelSize),Color::BLACK);
		this->label->setAlignment(TextActor::ALIGN_CENTER);
	}

	MenuBarSmall::~MenuBarSmall()
	{
		delete label;
	}

	void MenuBarSmall::Update(long gameTime)
	{
		Actor::Update(gameTime);
		label->Update(gameTime);
	}

	void MenuBarSmall::Draw(Graphics2D&g, long gameTime)
	{
		Actor::Draw(g,gameTime);
		
		label->x = (x - 10 * getScale());
		label->y = (y - 2 * getScale());
		label->x += xOffset*getScale();
		if(((int)(labelSize*getScale())) != label->getSize())
		{
			label->setSize((int)(labelSize*getScale()));
		}
		
		label->Draw(g, gameTime);
	}

	void MenuBarSmall::setTextOffsetX(float x1)
	{
		xOffset = x1;
	}

	float MenuBarSmall::getTextOffsetX()
	{
		return xOffset;
	}

	void MenuBarSmall::setLabel(String str)
	{
		label->setText(str);
	}

	String MenuBarSmall::getLabel()
	{
		return label->getText();
	}
	
	void MenuBarSmall::setLabelSize(int size)
	{
		labelSize = size;
	}
}