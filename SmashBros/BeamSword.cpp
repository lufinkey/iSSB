#include "BeamSword.h"
#include "Global.h"
#include "AttackTemplates.h"

namespace SmashBros
{
	BeamSword::BeamSword(float x1, float y1) : Item(x1, y1, 300, TYPE_HOLD)
	{
		itemNo = Global::ITEM_BEAMSWORD;
		
		weight = 0.2f;
		
		active = false;
		attackDir = 0;
		smashPower = 0;
		
		setCollideType(COLLIDE_SOLID);
		updateHitState(true);
		
		Animation*anim;
		anim = new Animation("normal",1,"Images/Game/Items/BeamSword/beamsword.png");
		addAnimation(anim);
		
		anim = new Animation("carry_left",1,"Images/Game/Items/BeamSword/beamsword_carry.png");
		addAnimation(anim);
		
		anim = new Animation("carry_right",1,"Images/Game/Items/BeamSword/beamsword_carry.png");
		anim->mirror(true);
		addAnimation(anim);
		
		anim = new Animation("swing_left",18,6,1);
		anim->addFrame("Images/Game/Items/BeamSword/beamsword_swing.png");
		addAnimation(anim);
		
		anim = new Animation("swing_right",18,6,1);
		anim->addFrame("Images/Game/Items/BeamSword/beamsword_swing.png");
		anim->mirror(true);
		addAnimation(anim);
		
		anim = new Animation("swing2_left",32,8,1);
		anim->addFrame("Images/Game/Items/BeamSword/beamsword_swing2.png");
		addAnimation(anim);
		
		anim = new Animation("swing2_right",32,8,1);
		anim->addFrame("Images/Game/Items/BeamSword/beamsword_swing2.png");
		anim->mirror(true);
		addAnimation(anim);
		
		changeAnimation("normal",FORWARD);
	}

	BeamSword::~BeamSword()
	{
		//
	}
	
	boolean BeamSword::holderCanDo()
	{
		if(active && (attackDir==ATTACK_NORMAL || attackDir==ATTACK_SMASH))
		{
			return false;
		}
		return true;
	}
	
	void BeamSword::onDiscard(Player*discarder)
	{
		active = false;
		attackDir = 0;
		smashPower = 0;
		y-=height/2;
		switch(discarder->getPlayerDir())
		{
			case Player::LEFT:
			xvelocity = 1.5f;
			break;
			
			case Player::RIGHT:
			xvelocity = -1.5f;
			break;
		}
		yvelocity = -1.5f;
		changeAnimation("normal",FORWARD);
	}
	
	boolean BeamSword::chargeSmash()
	{
		Player*playr = getPlayer();
		AttackTemplates::normalSmash(playr, 0, 0, Player::STEP_CHARGE, 1, 16, 4, 11);
		return true;
	}
	
	boolean BeamSword::use(byte attackDir)
	{
		this->attackDir = attackDir;
		if(attackDir==ATTACK_NORMAL)
		{
			if(!active)
			{
				active = true;
				switch(getPlayer()->getPlayerDir())
				{
					case Player::LEFT:
					changeAnimation("swing_left",FORWARD);
					break;
					
					case Player::RIGHT:
					changeAnimation("swing_right",FORWARD);
					break;
				}
			}
			return true;
		}
		else if(attackDir==ATTACK_SIDE)
		{
			if(!active)
			{
				Player*playr = getPlayer();
				if(attackDir==ATTACK_SMASH)
				{
					smashPower = playr->getSmashPower();
					AttackTemplates::stopSmashAttack(playr);
				}
				active = true;
				switch(playr->getPlayerDir())
				{
					case Player::LEFT:
					changeAnimation("swing2_left",FORWARD);
					//playr.changeAnimation("melee_weapon_left", FORWARD);
					break;
					
					case Player::RIGHT:
					changeAnimation("swing2_right",FORWARD);
					//playr.changeAnimation("melee_weapon_right", FORWARD);
					break;
				}
			}
			return true;
		}
		else if(attackDir==ATTACK_SMASH)
		{
			if(!active)
			{
				Player*playr = getPlayer();
				if(attackDir==ATTACK_SMASH)
				{
					smashPower = playr->getSmashPower();
					AttackTemplates::stopSmashAttack(playr);
				}
				active = true;
				switch(playr->getPlayerDir())
				{
					case Player::LEFT:
					changeAnimation("swing2_left",FORWARD);
					playr->changeAnimation("melee_weapon_left", FORWARD);
					break;
					
					case Player::RIGHT:
					changeAnimation("swing2_right",FORWARD);
					playr->changeAnimation("melee_weapon_right", FORWARD);
					break;
				}
			}
			return true;
		}
		return false;
	}
	
	void BeamSword::onPlayerHit(Player*collide, byte dir)
	{
		if(isHeld())
		{
		    if(attackDir==ATTACK_NORMAL)
		    {
		    	causeDamage(collide,2);
		    	switch(getPlayer()->getPlayerDir())
		    	{
					case Player::LEFT:
		    		causeHurtLaunch(collide, -1,2,3, -1,1,2);
		    		causeHurt(collide, Player::RIGHT, 3);
		    		break;
		    		
					case Player::RIGHT:
		    		causeHurtLaunch(collide, 1,2,3, -1,1,2);
		    		causeHurt(collide, Player::LEFT, 3);
		    		break;
		    	}
		    }
		    else if(attackDir==ATTACK_SIDE)
		    {
		    	causeDamage(collide,3);
		    	switch(getPlayer()->getPlayerDir())
		    	{
					case Player::LEFT:
		    		causeHurtLaunch(collide, -1,3,3.5f, -1,2,2.3f);
		    		causeHurt(collide, Player::RIGHT, 3);
		    		break;
		    		
					case Player::RIGHT:
		    		causeHurtLaunch(collide, 1,3,3.5f, -1,2,2.3f);
		    		causeHurt(collide, Player::LEFT, 3);
		    		break;
		    	}
		    }
		    else if(attackDir==ATTACK_SMASH)
		    {
		    	causeDamage(collide,smashPower);
		    	switch(getPlayer()->getPlayerDir())
		    	{
					case Player::LEFT:
		    		causeHurtLaunch(collide, -1,2+((float)smashPower/4),2.1f, -1,2+((float)smashPower/4),2.6f);
		    		causeHurt(collide, Player::RIGHT, 4);
		    		break;
		    		
					case Player::RIGHT:
		    		causeHurtLaunch(collide, 1,2+((float)smashPower/4),2.1f, -1,2+((float)smashPower/4),2.6f);
		    		causeHurt(collide, Player::LEFT, 4);
		    		break;
		    	}
		    }
	    }
	}
	
	void BeamSword::onAnimationFinish(const String&name)
	{
		if(name.equals("swing_left") || name.equals("swing_right")
		|| name.equals("swing2_left") || name.equals("swing2_right"))
		{
			active = false;
			Player*playr = getPlayer();
			if(playr!=null)
			{
				switch(playr->getPlayerDir())
				{
					case Player::LEFT:
					changeAnimation("carry_left",FORWARD);
					break;
					
					case Player::RIGHT:
					changeAnimation("carry_right",FORWARD);
					break;
				}
			}
			else
			{
				changeAnimation("normal",FORWARD);
			}
		}
	}
	
	void BeamSword::Update(long gameTime)
	{
		Item::Update(gameTime);
		if(active)
		{
			if(isHeld())
			{
				setHitState(true);
				setHoldOffset(0, 0);
			}
		}
		else
		{
			setHitState(false);
			if(isHeld())
			{
				Player*playr = getPlayer();
				switch(playr->getPlayerDir())
				{
					case Player::LEFT:
					changeAnimation("carry_left",FORWARD);
					break;
					
					case Player::RIGHT:
					changeAnimation("carry_right",FORWARD);
					break;
				}
				setHoldOffset(4,-4);
			}
			else
			{
				active = false;
				changeAnimation("normal",FORWARD);
			}
		}
	}
}