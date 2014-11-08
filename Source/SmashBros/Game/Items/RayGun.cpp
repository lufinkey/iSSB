
#include "RayGun.h"
#include "../../Global.h"
#include <cmath>

namespace SmashBros
{
	RayGun::RayGun(float x1, float y1) : Item(x1, y1, 20000, TYPE_HOLD)
	{
		itemNo = Global::ITEM_RAYGUN;
		
		weight = 0.2f;
		
		ammo = 16;
		active = false;
		activeTime = 0;
		attackType = 0;
		
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
			case Player::LEFT:
			changeAnimation("left",FORWARD);
			break;
			
			case Player::RIGHT:
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
		dir = discarder->getPlayerDir();
	}
	
	boolean RayGun::use(byte attackType)
	{
		this->attackType = attackType;
		if(attackType==Player::ATTACK_A)
		{
			if(!active)
			{
				active = true;
				if(ammo>0)
				{
					createProjectile(new Ray(getItemHolder(),x,y));
					ammo--;
				}
				activeTime = Global::getWorldTime() + 500;
			}
			return true;
		}
		else if(attackType==Player::ATTACK_SIDEA)
		{
			if(!active)
			{
				active = true;
				if(ammo>0)
				{
					createProjectile(new Ray(getItemHolder(),x,y));
					ammo--;
				}
				activeTime = Global::getWorldTime() + 400;
			}
			return true;
		}
		return false;
	}
	
	boolean RayGun::holderCanDo()
	{
		if(active && attackType==Player::ATTACK_A)
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
	
	void RayGun::Ray::deflect(byte dir)
	{
		switch(dir)
		{
			case DIR_LEFT:
			case DIR_UPLEFT:
			case DIR_DOWNLEFT:
			itemdir = LEFT;
			xvelocity = -6;
			changeAnimation("left", FORWARD);
			break;
			
			case DIR_RIGHT:
			case DIR_UPRIGHT:
			case DIR_DOWNRIGHT:
			itemdir = RIGHT;
			xvelocity = 6;
			changeAnimation("right", FORWARD);
			break;
		}
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
			            case Player::LEFT:
			            causeHurtLaunch(collide,-1,3,1, 0,0,0);
			            causeHurt(collide, Player::RIGHT, 300);
			            break;
						
			            case Player::RIGHT:
			            causeHurtLaunch(collide,1,3,1, 0,0,0);
			            causeHurt(collide, Player::LEFT, 300);
			            break;
			        }
			        destroy();
			    }
			    else
			    {
			        xvelocity=-xvelocity;
			        switch(itemdir)
			        {
			            case Player::LEFT:
						itemdir=Player::RIGHT;
			            changeAnimation("right", NO_CHANGE);
			            break;
			 
			            case Player::RIGHT:
						itemdir=Player::LEFT;
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
			        case Player::LEFT:
					itemdir=Player::RIGHT;
			        changeAnimation("right", NO_CHANGE);
			        break;
						
			        case Player::RIGHT:
					itemdir=Player::LEFT;
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
			        case Player::LEFT:
			        causeHurtLaunch(collide, -1,3,1, 0,0,0);
			        causeHurt(collide, Player::RIGHT, 300);
			        break;
					
			        case Player::RIGHT:
			        causeHurtLaunch(collide,1,3,1, 0,0,0);
			        causeHurt(collide, Player::LEFT, 300);
			        break;
			    }
			    destroy();
			}
		}
	}
}