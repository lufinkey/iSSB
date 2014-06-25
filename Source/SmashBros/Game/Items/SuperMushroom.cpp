
#include "SuperMushroom.h"
#include "../../Global.h"

namespace SmashBros
{
	SuperMushroom::SuperMushroom(float x1, float y1) : Item(x1, y1, 160, TYPE_WIELD)
	{
		itemNo = Global::ITEM_SUPERMUSHROOM;
		
		weight = 0.2f;
		
		moving = false;
		active = false;
		scale = 1;
		finishTime = 0;
		
		dir = (byte)((GameEngine::random()*2)+1);
		
		addAnimation(new Animation("normal", 1, "Images/Game/Items/Mushroom/mushroom.png"));
		
		changeAnimation("normal",FORWARD);
	}

	SuperMushroom::~SuperMushroom()
	{
		//
	}
	
	boolean SuperMushroom::canPickUp()
	{
		return false;
	}
	
	void SuperMushroom::onPlayerCollide(Player*collide)
	{
		if(!active)
		{
			if(collide->pickUpItem(this))
			{
				scale = collide->Scale;
				
				int oldHeight = collide->height;
				
				collide->Scale*=2.5;
				
				int newHeight = (int)(collide->height*2.5);
				
				int dif = newHeight - oldHeight;
				collide->y-=dif/2;
				
				finishTime = Global::getWorldTime() + 100;
				
				moving = false;
				active = true;
				
				setVisible(false);
			}
		}
	}
	
	void SuperMushroom::onPlatformCollide(Platform*collide, byte dir)
	{
		switch(dir)
		{
			case DIR_LEFT:
			this->dir = 1;
			break;
			
			case DIR_RIGHT:
			this->dir = 2;
			break;
		}
	}
	
	void SuperMushroom::onGroundCollide()
	{
		moving = true;
	}
	
	void SuperMushroom::onDestroy()
	{
		if(active)
		{
			Player*playr = Global::getPlayerActor(getItemHolder());
			playr->Scale = scale;
		}
	}
	
	void SuperMushroom::Update(long gameTime)
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
					case 1:
					x-=2;
					break;
					
					case 2:
					x+=2;
					break;
				}
			}
		}
	}
}