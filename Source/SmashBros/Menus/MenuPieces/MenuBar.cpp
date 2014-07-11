
#include "MenuBar.h"

namespace SmashBros
{
	MenuBar::MenuBar(float x1, float y1, String label) : Actor(x1,y1)
	{
		labelSize = 20;
		xOffset = 0;
		addAnimation(new Animation("normal",1,"Images/Menus/Buttons/Generic/options_bar.png"));
		changeAnimation("normal",FORWARD);
		this->label = new TextActor(label,AssetManager::getFont("Fonts/arial.ttf", Font::BOLD, 20),Color::BLACK);
		this->label->setAlignment(TextActor::ALIGN_CENTER);
	}

	MenuBar::~MenuBar()
	{
		delete label;
	}

	void MenuBar::Update(long gameTime)
	{
		Actor::Update(gameTime);
		label->Update(gameTime);
	}

	void MenuBar::Draw(Graphics2D&g, long gameTime)
	{
		Actor::Draw(g,gameTime);
		
		label->x = (x - 100 * Scale);
		label->y = (y - 2 * Scale);
		label->x += xOffset*Scale;
		if(((int)(labelSize*Scale)) != label->getSize())
		{
			label->setSize((int)(labelSize*Scale));
		}
		
		label->Draw(g, gameTime);
	}

	void MenuBar::setTextOffsetX(float x1)
	{
		xOffset = x1;
	}

	float MenuBar::getTextOffsetX()
	{
		return xOffset;
	}

	void MenuBar::setLabel(String str)
	{
		label->setText(str);
	}

	String MenuBar::getLabel()
	{
		return label->getText();
	}
}