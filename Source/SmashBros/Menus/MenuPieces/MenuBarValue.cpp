
#include "MenuBarValue.h"

namespace SmashBros
{
	MenuBarValue::LeftArrow::LeftArrow(MenuBarValue*menuBar, float x1, float y1) : Actor(x1,y1)
	{
		this->menuBar = menuBar;
	}

	MenuBarValue::LeftArrow::~LeftArrow()
	{
		//
	}

	void MenuBarValue::LeftArrow::onMouseEnter()
	{
		changeAnimation("hover",FORWARD);
	}

	void MenuBarValue::LeftArrow::onMouseLeave()
	{
		changeAnimation("normal",FORWARD);
	}

	void MenuBarValue::LeftArrow::onRelease()
	{
		menuBar->value -= menuBar->incr;
		if(menuBar->value < menuBar->minValue)
		{
			menuBar->value = menuBar->maxValue;
		}
	}

	MenuBarValue::RightArrow::RightArrow(MenuBarValue*menuBar, float x1, float y1) : Actor(x1,y1)
	{
		this->menuBar = menuBar;
	}

	MenuBarValue::RightArrow::~RightArrow()
	{
		//
	}

	void MenuBarValue::RightArrow::onMouseEnter()
	{
		changeAnimation("hover",FORWARD);
	}

	void MenuBarValue::RightArrow::onMouseLeave()
	{
		changeAnimation("normal",FORWARD);
	}

	void MenuBarValue::RightArrow::onRelease()
	{
		menuBar->value += menuBar->incr;
		if(menuBar->value > menuBar->maxValue)
		{
			menuBar->value = menuBar->minValue;
		}
	}

	MenuBarValue::MenuBarValue(float x1, float y1, String label) : MenuBar(x1,y1,label)
	{
		label2Size = 15;
		valueActorSize = 18;
		createMenuBar();
		numLabel = false;
	}

	MenuBarValue::MenuBarValue(float x1, float y1, String label,String label2) : MenuBar(x1,y1,label)
	{
		label2Size = 15;
		valueActorSize = 18;
		createMenuBar();
		this->label2 = new TextActor(label2,AssetManager::getFont("Fonts/arial.ttf", Font::BOLD, label2Size),Color::BLACK);
		this->label2->setAlignment(TextActor::ALIGN_CENTER);
		numLabel = true;
	}

	MenuBarValue::~MenuBarValue()
	{
		delete valueActor;
		delete leftArrow;
		delete rightArrow;
		if(label2!=null)
		{
			delete label2;
		}
	}

	void MenuBarValue::createMenuBar()
	{
		valueActor = new TextActor("0",AssetManager::getFont("Fonts/arial.ttf", Font::BOLD, valueActorSize),Color::BLACK);

		leftArrow = new LeftArrow(this,0,0);
		Animation*normal = new Animation("normal",1,"Images/Menus/Buttons/Generic/arrow.png");
		Animation*hover = new Animation("hover",1,"Images/Menus/Buttons/Generic/arrow_selected.png");
		leftArrow->addAnimation(normal);
		leftArrow->addAnimation(hover);
		leftArrow->changeAnimation("normal", FORWARD);

		rightArrow = new RightArrow(this,0,0);
		normal = new Animation("normal",1,"Images/Menus/Buttons/Generic/arrow.png");
		normal->mirror(true);
		hover = new Animation("hover",1,"Images/Menus/Buttons/Generic/arrow_selected.png");
		hover->mirror(true);
		rightArrow->addAnimation(normal);
		rightArrow->addAnimation(hover);
		rightArrow->changeAnimation("normal", FORWARD);
	}

	int MenuBarValue::getValue()
	{
		return value;
	}

	void MenuBarValue::setValue(int value)
	{
		this->value = value;
	}

	void MenuBarValue::setProperties(int min, int max, int increment)
	{
		minValue = min;
		maxValue = max;
		incr = increment;
	}

	void MenuBarValue::Update(long gameTime)
	{
		MenuBar::Update(gameTime);
		if(numLabel)
		{
			label2->Update(gameTime);
		}
		leftArrow->Update(gameTime);
		rightArrow->Update(gameTime);
		valueActor->setText((String)"" + value);
		valueActor->Update(gameTime);
	}

	void MenuBarValue::Draw(Graphics2D&g, long gameTime)
	{
		MenuBar::Draw(g, gameTime);
		if(numLabel)
		{
			label2->x = (x + 106 * getScale());
			label2->y = (y - 1.5f * getScale());
			if(((int)(label2Size*getScale()))!=label2->getSize())
			{
				label2->setSize((int)(label2Size*getScale()));
			}
			valueActor->x = (x + 64 * getScale());
			valueActor->y = (y + 6 * getScale());
			label2->Draw(g, gameTime);
		}
		else
		{
			valueActor->x = (x + 83 * getScale());
			valueActor->y = (y + 6 * getScale());
		}
		
		leftArrow->x = (x + 50 * getScale());
		leftArrow->y = (y);
		leftArrow->setScale(getScale());
		
		rightArrow->x = (x + 136 * getScale());
		rightArrow->y = (y);
		rightArrow->setScale(getScale());
		
		if(((int)(valueActorSize*getScale()))!=valueActor->getSize())
		{
			valueActor->setSize((int)(valueActorSize*getScale()));
		}
		
		valueActor->Draw(g, gameTime);
		leftArrow->Draw(g, gameTime);
		rightArrow->Draw(g, gameTime);
	}
}