
#include "HeartContainer.h"
#include "../../Global.h"

namespace SmashBros
{
	HeartContainer::HeartContainer(float x1, float y1) : Item(x1, y1, 20000, TYPE_FOOD)
	{
		weight = 0.8f;
		accelerateGravity(false);
		
		itemNo = Global::ITEM_HEARTCONTAINER;
		
		available = true;
		
		addAnimation(new Animation("normal",1,"Images/Game/Items/HeartContainer/heart_container.png"));
		Animation*anim = new Animation("sparkle",8,4,1);
		anim->addFrame("Images/Game/Items/HeartContainer/sparkle.png");
		addAnimation(anim);
		changeAnimation("normal",FORWARD);
	}

	HeartContainer::~HeartContainer()
	{
		//
	}
	
	void HeartContainer::Update(long gameTime)
	{
		Item::Update(gameTime);
	}
	
	void HeartContainer::onPickUp(Player*collide)
	{
		doPowerUp(collide, POWERUP_HEAL, 100);
		available = false;
		changeAnimation("sparkle",FORWARD);
	}
	
	boolean HeartContainer::canPickUp()
	{
		return available;
	}
	
	void HeartContainer::onAnimationFinish(const String&n)
	{
		if(n.equals("sparkle"))
		{
			destroy();
		}
	}
}