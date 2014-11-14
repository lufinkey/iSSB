
#include "MenuScreen.h"
#include "../Application.h"
#include "ScreenManager.h"
#include "../Input/Mouse.h"

namespace GameEngine
{
	MenuScreen::MenuScreen(const String& name) : Screen(name)
	{
		selectedIndex = -1;
		Items = ArrayList<MenuItem*>();
		soundEnabled = true;
	}
	
	MenuScreen::~MenuScreen()
	{
		int total = Items.size();
		for(int i=0; i<total; i++)
		{
			delete Items.get(i);
		}
		Items.clear();
	}
	
	void MenuScreen::Update(long gameTime)
	{
		Screen::Update(gameTime);

		if(Application::hasMultitouch())
		{
			long prevTouchId = -1;
			if(selectedIndex>-1)
			{
				prevTouchId = Items.get(selectedIndex)->getTouchId();
			}
			Screen::Update(gameTime);
			ArrayList<TouchPoint> touchPoints = Application::getTouchPoints();
			ArrayList<TouchPoint> prevTouchPoints = Application::getPrevTouchPoints();
			if(touchPoints.size()>0)
			{
				selecting = true;
			}
			else
			{
				selecting = false;
			}
		
			bool canBeSelected = true;
			int prevSelectedIndex = selectedIndex;
			selectedIndex = -1;
			for(int i=(Items.size()-1); i>=0; i--)
			{
				MenuItem*currentItem = Items.get(i);
				currentItem->Update(gameTime);
				if(canBeSelected)
				{
					if(currentItem->MouseOver())
					{
						currentItem->setSelected(true);
						selectedIndex = i;
						canBeSelected = false;
					}
					else
					{
						currentItem->setSelected(false);
					}
				}
				else
				{
					currentItem->setSelected(false);
				}
			}
		
			if(prevSelectedIndex>=0 && !Application::checkTouchActive(prevTouchId))
			{
				Items.get(prevSelectedIndex)->OnRelease();
				Items.get(prevSelectedIndex)->setSelected(false);
				prevSelectedIndex = -1;
			}
		}
		else
		{
			if(Application::getMouseState(Mouse::LEFTCLICK))
			{
				selecting = true;
			}
			else
			{
				selecting = false;
			}
		
			bool canBeSelected = true;
			selectedIndex = -1;
			for(int i=(Items.size()-1); i>=0; i--)
			{
				MenuItem*currentItem = Items.get(i);
				currentItem->Update(gameTime);
				if(canBeSelected)
				{
					if(currentItem->MouseOver())
					{
						currentItem->setSelected(true);
						selectedIndex = i;
						canBeSelected = false;
					}
					else
					{
						currentItem->setSelected(false);
					}
				}
				else
				{
					currentItem->setSelected(false);
				}
			}
		
			if(selectedIndex>=0 && !Application::getMouseState(Mouse::LEFTCLICK) && Application::getPrevMouseState(Mouse::LEFTCLICK))
			{
				Items.get(selectedIndex)->OnRelease();
				Items.get(selectedIndex)->setSelected(false);
				selectedIndex = -1;
			}
		}
	}
	
	void MenuScreen::Draw(Graphics2D& g, long gameTime)
	{
		Screen::Draw(g,gameTime);
		for(int i=0; i<Items.size(); i++)
		{
			Items.get(i)->Draw(g, gameTime);
		}
	}
	
	//ImageMenuItem
	
	void MenuScreen::addItem(float x1, float y1,Animation*normAnim, Animation*hoverAnim, const String& target)
	{
		Items.add(new MenuItem(this, new ImageMenuItem(this, x1,y1,normAnim,hoverAnim,target)));
	}
	
	void MenuScreen::addItem(float x1, float y1,Animation*normAnim, Animation*hoverAnim, Animation*clickAnim, const String& target)
	{
		Items.add(new MenuItem(this, new ImageMenuItem(this, x1,y1,normAnim,hoverAnim,clickAnim,target)));
	}
	
	void MenuScreen::addItem(float x1, float y1,Animation*anim, const Color&hoverColor, const String& target)
	{
		Items.add(new MenuItem(this, new ImageMenuItem(this, x1,y1,anim,hoverColor,target)));
	}
	
	void MenuScreen::addItem(float x1, float y1,Animation*anim, const Color&hoverColor, const Color&clickColor, const String& target)
	{
		Items.add(new MenuItem(this, new ImageMenuItem(this, x1,y1,anim,hoverColor,clickColor,target)));
	}
	
	void MenuScreen::addItem(float x1, float y1,const String& normAnim, const String& hoverAnim, const String& target)
	{
		Animation*norm = new Animation("normal",1);
		norm->addFrame(normAnim);
		Animation*hover = new Animation("hover",1);
		hover->addFrame(hoverAnim);
		Items.add(new MenuItem(this, new ImageMenuItem(this, x1,y1,norm,hover,target)));
	}
	
	void MenuScreen::addItem(float x1, float y1,const String& normAnim, const String& hoverAnim, const String& clickAnim, const String& target)
	{
		Animation*norm = new Animation("normal",1);
		norm->addFrame(normAnim);
		Animation*hover = new Animation("hover",1);
		hover->addFrame(hoverAnim);
		Animation*click = new Animation("click",1);
		click->addFrame(clickAnim);
		Items.add(new MenuItem(this, new ImageMenuItem(this, x1,y1,norm,hover,click,target)));
	}
	
	void MenuScreen::addItem(float x1, float y1, const String& anim, const Color&hoverColor, const String& target)
	{
		Animation*norm = new Animation("normal",1);
		norm->addFrame(anim);
		Items.add(new MenuItem(this, new ImageMenuItem(this, x1,y1,norm,hoverColor,target)));
	}
	
	void MenuScreen::addItem(float x1, float y1, const String& anim, const Color&hoverColor, const Color&clickColor, const String& target)
	{
		Animation*norm = new Animation("normal",1);
		norm->addFrame(anim);
		Items.add(new MenuItem(this, new ImageMenuItem(this, x1,y1,norm,hoverColor,clickColor,target)));
	}
	
	//TextMenuItem
	
	void MenuScreen::addItem(float x1, float y1, const String& s, Font*f, const Color&normC, const Color&hoverC, const String& target)
	{
		Items.add(new MenuItem(this, new TextMenuItem(this, x1, y1, s,f,normC,hoverC,target)));
	}
	
	void MenuScreen::addItem(float x1, float y1, const String& s, Font*f, const Color&normC, const Color&hoverC, const Color&clickC, const String& target)
	{
		Items.add(new MenuItem(this, new TextMenuItem(this, x1, y1, s,f,normC,hoverC,clickC,target)));
	}
	
	void MenuScreen::setItemScale(int index, float scale)
	{
		Items.get(index)->setScale(scale);
	}
	
	void MenuScreen::setItemRotation(int index, float degrees)
	{
		Items.get(index)->setRotation(degrees);
	}
	
	void MenuScreen::setItemColor(int index, const Color&c)
	{
		Items.get(index)->setColor(c);
	}
	
	void MenuScreen::setItemSound(int index, Sound*sound)
	{
		Items.get(index)->sound = sound;
	}
	
	void MenuScreen::enableSound(bool toggle)
	{
		soundEnabled = toggle;
	}
	
	MenuScreen::TextMenuItem::TextMenuItem(MenuScreen*menu, float x1, float y1, const String& s, Font*f, const Color&normC, const Color&hoverC, const String& target) : TextActor(x1,y1,s,f,normC)
	{
		type = 0;
		this->normColor = normC;
		this->hoverColor = hoverC;
		this->target = target;
		this->setAlignment(ALIGN_CENTER);
		this->menu = menu;
	}
	
	MenuScreen::TextMenuItem::TextMenuItem(MenuScreen*menu, float x1, float y1, const String& s, Font*f, const Color&normC, const Color&hoverC, const Color&clickC, const String& target) : TextActor(x1,y1,s,f,normC)
	{
		type = 1;
		this->normColor = normC;
		this->hoverColor = hoverC;
		this->clickColor = clickC;
		this->target = target;
		this->setAlignment(ALIGN_CENTER);
		this->menu = menu;
	}
	
	MenuScreen::TextMenuItem::~TextMenuItem()
	{
		//
	}
	
	void MenuScreen::TextMenuItem::OnRelease()
	{
		ScreenManager::GoToScreen(target);
	}
	
	void MenuScreen::TextMenuItem::Draw(Graphics2D& g, long gameTime)
	{
		switch(type)
		{
			case 0:
			if(selected)
			{
				setColor(hoverColor);
			}
			else
			{
				setColor(normColor);
			}
			break;
			
			case 1:
			if(selected)
			{
				if(menu->selecting)
				{
					setColor(clickColor);
				}
				else
				{
					setColor(hoverColor);
				}
			}
			else
			{
				setColor(normColor);
			}
			break;
		}
		TextActor::Draw(g,gameTime);
	}
	
	MenuScreen::ImageMenuItem::ImageMenuItem(MenuScreen*menu, float x1, float y1,Animation*normAnim, Animation*hoverAnim, const String& target) : Actor(x1,y1)
	{
		type = 0;
		normAnim->name = "normal";
		hoverAnim->name = "hover";
		addAnimation(normAnim);
		addAnimation(hoverAnim);
		changeAnimation("normal", FORWARD);
		this->target = target;
		this->menu = menu;
	}
	
	MenuScreen::ImageMenuItem::ImageMenuItem(MenuScreen*menu, float x1, float y1,Animation*normAnim, Animation*hoverAnim, Animation*clickAnim, const String& target) : Actor(x1,y1)
	{
		type = 1;
		normAnim->name = "normal";
		hoverAnim->name = "hover";
		clickAnim->name = "click";
		addAnimation(normAnim);
		addAnimation(hoverAnim);
		addAnimation(clickAnim);
		changeAnimation("normal", FORWARD);
		this->target = target;
		this->menu = menu;
	}
	
	MenuScreen::ImageMenuItem::ImageMenuItem(MenuScreen*menu, float x1, float y1,Animation*anim, const Color&hoverColor, const String& target) : Actor(x1,y1)
	{
		type = 2;
		anim->name = "normal";
		addAnimation(anim);
		this->hover = hoverColor;
		changeAnimation("normal", FORWARD);
		this->target = target;
		this->menu = menu;
	}
	
	MenuScreen::ImageMenuItem::ImageMenuItem(MenuScreen*menu, float x1, float y1,Animation*anim, const Color&hoverColor, const Color&clickColor, const String& target) : Actor(x1,y1)
	{
		type = 3;
		hover = hoverColor;
		click = clickColor;
		anim->name = "normal";
		addAnimation(anim);
		changeAnimation("normal", FORWARD);
		this->target = target;
		this->menu = menu;
	}
	
	MenuScreen::ImageMenuItem::~ImageMenuItem()
	{
		//
	}
	
	void MenuScreen::ImageMenuItem::OnRelease()
	{
		ScreenManager::GoToScreen(target);
	}
	
	void MenuScreen::ImageMenuItem::Draw(Graphics2D& g, long gameTime)
	{
		switch(type)
		{
			case 0:
			if(selected)
			{
				changeAnimation("hover",NO_CHANGE);
			}
			else
			{
				changeAnimation("normal", NO_CHANGE);
			}
			break;
			
			case 1:
			if(selected)
			{
				if(menu->selecting)
				{
					changeAnimation("click",NO_CHANGE);
				}
				else
				{
					changeAnimation("hover",NO_CHANGE);
				}
			}
			else
			{
				changeAnimation("normal", NO_CHANGE);
			}
			break;
			
			case 2:
			if(selected)
			{
				this->setColor(hover);
			}
			else
			{
				this->setColor(normal);
			}
			break;
			
			case 3:
			if(selected)
			{
				if(menu->selecting)
				{
					this->setColor(click);
				}
				else
				{
					this->setColor(hover);
				}
			}
			else
			{
				this->setColor(normal);
			}
			break;
		}
		Actor::Draw(g, gameTime);
	}
	
	MenuScreen::MenuItem::MenuItem(MenuScreen*menuScreen, TextMenuItem*textItem)
	{
		this->itemType = TEXT;
		this->textItem = textItem;
		sound = NULL;
		this->menuScreen = menuScreen;
	}
	
	MenuScreen::MenuItem::MenuItem(MenuScreen*menuScreen, ImageMenuItem*imageItem)
	{
		this->itemType = IMAGE;
		this->imageItem = imageItem;
		sound = NULL;
		this->menuScreen = menuScreen;
	}
	
	MenuScreen::MenuItem::~MenuItem()
	{
		switch(itemType)
		{
			case TEXT:
			delete textItem;
			break;

			case IMAGE:
			delete imageItem;
			break;
		}
	}
	
	void MenuScreen::MenuItem::Update(long gameTime)
	{
		switch(itemType)
		{
			case TEXT:
			textItem->Update(gameTime);
			break;

			case IMAGE:
			imageItem->Update(gameTime);
			break;
		}
	}
	
	void MenuScreen::MenuItem::Draw(Graphics2D& g, long gameTime)
	{
		switch(itemType)
		{
			case TEXT:
			textItem->Draw(g,gameTime);
			break;

			case IMAGE:
			imageItem->Draw(g,gameTime);
			break;
		}
	}
	
	long MenuScreen::MenuItem::getTouchId()
	{
		switch(itemType)
		{
			case TEXT:
			return textItem->getTouchId();
				
			case IMAGE:
			return imageItem->getTouchId();
		}
		return 0;
	}
	
	bool MenuScreen::MenuItem::MouseOver()
	{
		switch(itemType)
		{
			case TEXT:
			return textItem->mouseOver();
			
			case IMAGE:
			return imageItem->mouseOver();
		}
		return false;
	}
	
	void MenuScreen::MenuItem::OnRelease()
	{
		if(sound!=NULL && menuScreen->soundEnabled)
		{
			sound->play();
		}
		switch(itemType)
		{
			case TEXT:
			textItem->OnRelease();
			break;
			
			case IMAGE:
			imageItem->OnRelease();
			break;
		}
	}
	
	void MenuScreen::MenuItem::setSelected(bool toggle)
	{
		switch(itemType)
		{
			case TEXT:
			textItem->selected = toggle;
			break;

			case IMAGE:
			imageItem->selected = toggle;
			break;
		}
	}
	
	bool MenuScreen::MenuItem::selected()
	{
		switch(itemType)
		{
			case TEXT:
			return textItem->selected;
			
			case IMAGE:
			return imageItem->selected;
		}
		return false;
	}
	
	void MenuScreen::MenuItem::setScale(float scale)
	{
		switch(itemType)
		{
			case TEXT:
			textItem->getFont()->setSize((int)scale);
			break;
			
			case IMAGE:
			imageItem->setScale(scale);
			break;
		}
	}
	
	void MenuScreen::MenuItem::setRotation(float degrees)
	{
		switch(itemType)
		{
			case TEXT:
			textItem->setRotation(degrees);
			break;
			
			case IMAGE:
			imageItem->setRotation(degrees);
			break;
		}
	}
	
	void MenuScreen::MenuItem::setColor(const Color&color)
	{
		switch(itemType)
		{
			case TEXT:
			textItem->normColor = color;
			break;
			
			case IMAGE:
			imageItem->normal = color;
			break;
		}
	}
}