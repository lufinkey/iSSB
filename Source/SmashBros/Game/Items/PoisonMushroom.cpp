
#include "PoisonMushroom.h"
#include "../../Global.h"

namespace SmashBros
{
	PoisonMushroom::PoisonMushroom(float x1, float y1) : Item(x1, y1, 16000, TYPE_WIELD)
	{
		itemNo = Global::ITEM_POISONMUSHROOM;
		
		weight = 0.2f;
		
		moving = false;
		active = false;
		scale = 1;
		finishTime = 0;
		
		dir = (byte)((GameEngine::random()*2)+1);
		
		addAnimation(new Animation("normal", 1, "Images/Game/Items/Mushroom/poison_mushroom.png"));
		
		changeAnimation("normal",FORWARD);
	}
	
	PoisonMushroom::~PoisonMushroom()
	{
		//
	}

	boolean PoisonMushroom::canPickUp()
	{
		return false;
	}
	
	void PoisonMushroom::onPlayerCollide(Player*collide)
	{
		if(!active)
		{
			if(collide->pickUpItem(this))
			{
				scale = collide->getScale();
				
				int oldHeight = collide->height;
				
				collide->setScale(collide->getScale()*0.5f);
				
				int newHeight = (int)(collide->height*0.5f);
				
				int dif = newHeight - oldHeight;
				collide->y-=dif/2;
				
				finishTime = Global::getWorldTime() + 10000;
				
				moving = false;
				active = true;
				
				setVisible(false);
			}
		}
	}
	
	void PoisonMushroom::onPlatformCollide(Platform*collide, byte dir)
	{
		switch(dir)
		{
			case DIR_LEFT:
			this->dir = Player::LEFT;
			break;
			
			case DIR_RIGHT:
			this->dir = Player::RIGHT;
			break;
		}
	}
	
	void PoisonMushroom::onGroundCollide()
	{
		moving = true;
	}
	
	void PoisonMushroom::onDestroy()
	{
		if(active)
		{
			Player*playr = Global::getPlayerActor(getItemHolder());
			playr->setScale(scale);
		}
	}
	
	void PoisonMushroom::Update(long gameTime)
	{
		Item::Update(gameTime);
		if(active)
		{
			if(finishTime<=Global::getWorldTime())
			{
				destroy();
			}
		}
		if(isHeld())
		{
			Player*playr = getPlayer();
			x = playr->x;
			y = playr->y;
		}
		else
		{
			if(moving)
			{
				switch(dir)
				{
					case Player::LEFT:
					x-=2;
					break;
					
					case Player::RIGHT:
					x+=2;
					break;
				}
			}
		}
	}
}