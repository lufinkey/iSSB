
#include "RayGun.h"
#include "../../Global.h"
#include <cmath>

namespace SmashBros
{
	RayGun::RayGun(float x1, float y1) : Item(x1, y1, 200, TYPE_HOLD)
	{
		itemNo = Global::ITEM_RAYGUN;
		
		weight = 0.2f;
		
		ammo = 16;
		active = false;
		activeTime = 0;
		attackDir = 0;
		
		Animation*anim;
		
		anim = new Animation("left",1,"Images/Game/Items/RayGun/raygun.png");
		addAnimation(anim);
		
		anim = new Animation("right",1,"Images/Game/Items/RayGun/raygun.png");
		anim->mirror(true);
		addAnimation(anim);
		
		anim = new Animation("down_left",1,"Images/Game/Items/RayGun/raygun_down.png");
		addAnimation(anim);
		
		anim = new Animation("down_right",1,"Images/Game/Items/RayGun/raygun_down.png");
		anim->mirror(true);
		addAnimation(anim);
		
		dir = (byte)((GameEngine::random()*2)+1);
		
		switch(dir)
		{
			case 1:
			changeAnimation("left",FORWARD);
			break;
			
			case 2:
			changeAnimation("right",FORWARD);
			break;
		}
		
		setHoldOffset(5, 1);
	}

	RayGun::~RayGun()
	{
		//
	}
	
	void RayGun::onDiscard(Player*discarder)
	{
		switch(discarder->getPlayerDir())
		{
			case Player::LEFT:
			xvelocity = 2;
			break;
			
			case Player::RIGHT:
			xvelocity = -2;
			break;
		}
		dir = discarder->getPlayerDir();
		yvelocity = -3;
	}
	
	boolean RayGun::use(byte attackDir)
	{
		this->attackDir = attackDir;
		if(attackDir==ATTACK_NORMAL)
		{
			if(!active)
			{
				active = true;
				if(ammo>0)
				{
					createProjectile(new Ray(getItemHolder(),x,y));
					ammo--;
				}
				activeTime = Global::getWorldTime() + 5;
			}
			return true;
		}
		else if(attackDir==ATTACK_SIDE)
		{
			if(!active)
			{
				active = true;
				if(ammo>0)
				{
					createProjectile(new Ray(getItemHolder(),x,y));
					ammo--;
				}
				activeTime = Global::getWorldTime() + 4;
			}
			return true;
		}
		return false;
	}
	
	boolean RayGun::holderCanDo()
	{
		if(active && attackDir==ATTACK_NORMAL)
		{
			return false;
		}
		return true;
	}
	
	void RayGun::Update(long gameTime)
	{
		Item::Update(gameTime);
		
		if(isHeld())
		{
			if(activeTime<=Global::getWorldTime())
			{
				active = false;
			}
			Player*playr = getPlayer();
			if(active)
			{
				switch(playr->getPlayerDir())
				{
					case Player::LEFT:
					changeAnimation("left",FORWARD);
					break;
					
					case Player::RIGHT:
					changeAnimation("right",FORWARD);
					break;
				}
			}
			else
			{
				switch(playr->getPlayerDir())
				{
					case Player::LEFT:
					changeAnimation("down_left",FORWARD);
					break;
					
					case Player::RIGHT:
					changeAnimation("down_right",FORWARD);
					break;
				}
			}
		}
		else
		{
			switch(dir)
			{
				case Player::LEFT:
				changeAnimation("left",FORWARD);
				break;
				
				case Player::RIGHT:
				changeAnimation("right",FORWARD);
				break;
			}
		}
	}
	
	RayGun::Ray::Ray(byte playerNo, float x1, float y1) : Projectile(playerNo, x1, y1)
	{
		Animation*anim;
			
		anim = new Animation("left",1,"Images/Game/Items/RayGun/ray.png");
		addAnimation(anim);
			
		anim = new Animation("right",1,"Images/Game/Items/RayGun/ray.png");
		anim->mirror(true);
		addAnimation(anim);
			
		switch(itemdir)
		{
			case Player::LEFT:
			changeAnimation("left",FORWARD);
			xvelocity = -6;
			break;
				
			case Player::RIGHT:
			changeAnimation("right",FORWARD);
			xvelocity = 6;
			break;
		}
			
		startX = x;
	}

	RayGun::Ray::~Ray()
	{
		//
	}
	
	void RayGun::Ray::Update(long gameTime)
	{
		Projectile::Update(gameTime);
		if(std::abs(startX - x)>240)
		{
			destroy();
		}
	}
	
	void RayGun::Ray::onPlayerHit(Player*collide, byte dir)
	{
		if(isHittable(collide,dir))
		{
			if(collide->getAttacksPriority()==5)
			{
			    if(itemdir==collide->getPlayerDir())
			    {
			        causeDamage(collide,2);
			        collide->y-=3;
			        causeHurtLaunch(collide,0,0,0, -1,1,1);
			        switch(itemdir)
			        {
			            case 1:
			            causeHurtLaunch(collide,-1,3,1, 0,0,0);
			            causeHurt(collide, Player::RIGHT, 3);
			            break;
						
			            case 2:
			            causeHurtLaunch(collide,1,3,1, 0,0,0);
			            causeHurt(collide, Player::LEFT, 3);
			            break;
			        }
			        destroy();
			    }
			    else
			    {
			        xvelocity=-xvelocity;
			        switch(itemdir)
			        {
			            case 1:
			            itemdir=2;
			            changeAnimation("right", NO_CHANGE);
			            break;
			 
			            case 2:
			            itemdir=1;
			            changeAnimation("left", NO_CHANGE);
			            break;
			        }
			    }
			}
			 
			else if(collide->getAttacksPriority()==6)
			{
			    xvelocity=-xvelocity;
			    switch(itemdir)
			    {
			        case 1:
			        itemdir=2;
			        changeAnimation("right", NO_CHANGE);
			        break;
			 
			        case 2:
			        itemdir=1;
			        changeAnimation("left", NO_CHANGE);
			        break;
			    }
			}
			 
			else if(collide->getAttacksPriority()==7)
			{
			    destroy();
			}
			 
			else
			{
			    causeDamage(collide,2);
			    collide->y-=3;
			    causeHurtLaunch(collide,0,0,0, -1,1,1);
			    switch(itemdir)
			    {
			        case 1:
			        causeHurtLaunch(collide, -1,3,1, 0,0,0);
			        causeHurt(collide, Player::RIGHT, 3);
			        break;

			        case 2:
			        causeHurtLaunch(collide,1,3,1, 0,0,0);
			        causeHurt(collide, Player::LEFT, 3);
			        break;
			    }
			    destroy();
			}
		}
	}
}