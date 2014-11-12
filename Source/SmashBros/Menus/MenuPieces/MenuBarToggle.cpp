
#include "MenuBarToggle.h"

namespace SmashBros
{
	MenuBarToggle::MenuBarToggleButton::MenuBarToggleButton(MenuBarToggle*menuBar,float x1, float y1, boolean toggle) : ToggleButton(x1,y1,toggle)
	{
		this->menuBar = menuBar;
	}

	MenuBarToggle::MenuBarToggleButton::~MenuBarToggleButton()
	{
		//
	}

	void MenuBarToggle::MenuBarToggleButton::onToggle(boolean toggle)
	{
		menuBar->whenToggled(toggle);
	}

	MenuBarToggle::MenuBarToggle(float x1, float y1, String label, boolean toggle) : MenuBar(x1,y1,label)
	{
		toggleButton = new MenuBarToggleButton(this,0,0,toggle);
		this->toggle = toggle;
	}

	MenuBarToggle::~MenuBarToggle()
	{
		delete toggleButton;
	}

	void MenuBarToggle::Update(long gameTime)
	{
		MenuBar::Update(gameTime);
		toggleButton->Update(gameTime);
	}

	void MenuBarToggle::Draw(Graphics2D&g, long gameTime)
	{
		MenuBar::Draw(g, gameTime);
		toggleButton->x = (x + 94 * getScale());
		toggleButton->y = (y + 0 * getScale());
		toggleButton->setScale(getScale());
		toggleButton->Draw(g, gameTime);
	}

	void MenuBarToggle::setToggle(boolean toggle)
	{
		this->toggle = toggle;
		toggleButton->setToggle(toggle);
	}

	boolean MenuBarToggle::getToggle()
	{
		return toggle;
	}

	void MenuBarToggle::whenToggled(boolean toggle)
	{
		this->toggle = toggle;
		onToggle(toggle);
	}

	void MenuBarToggle::onToggle(boolean toggle)
	{
		//Open for implementation
	}
}