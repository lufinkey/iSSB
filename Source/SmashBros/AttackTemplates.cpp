
#include "AttackTemplates.h"
#include "Global.h"
#include "Item.h"
#include <cmath>

namespace SmashBros
{
	/*void AttackTemplates::causeKnockback(Player* playr, Player* collide, float damage, float knockbackUnits, float knockbackAngle, float knockbackScaling)
	{
		collide->updateHitbox();
		playr->updateHitbox();
		if(!collide->onDeflectPlayerKnockback(playr, damage, knockbackUnits, knockbackAngle, knockbackScaling))
		{
			if(collide->holdingPlayer)
			{
				collide->releasePlayer();
			}

			float totalKnockback = knockbackUnits+((knockbackScaling*collide->percent)/75);
			float totalKnockbackX = std::cos(degtorad((double)knockbackAngle)) * totalKnockback;
			float totalKnockbackY = -std::sin(degtorad((double)knockbackAngle)) * totalKnockback;
			collide->percent += (int)damage;
			if(collide->percent > 999)
			{
				collide->percent = 999;
			}

			
		}
	}*/

	void AttackTemplates::causeDamage(Player*playr, Player*collide, int amount)
	{
		boolean canInflict = true;
		if(collide->attacksPriority==5)
		{
			collide->updateHitbox();
			playr->updateHitbox();
			switch(collide->playerdir)
			{
				case Player::LEFT:
				if(playr->x<collide->x && PrimitiveActor::getDir(collide,playr)==PrimitiveActor::DIR_LEFT)
				{
					boolean inflicted = false;
					if(playr->attacksPriority!=7)
					{
						inflicted = collide->onDeflectPlayerDamage(playr, amount);
					}
					if(inflicted)
					{
						canInflict = false;
						collide->deflectState = true;
					}
				}
				break;
				
				case Player::RIGHT:
				if(playr->x>collide->x && PrimitiveActor::getDir(collide,playr)==PrimitiveActor::DIR_RIGHT)
				{
					boolean inflicted = false;
					if(playr->attacksPriority!=7)
					{
						inflicted = collide->onDeflectPlayerDamage(playr, amount);
					}
					if(inflicted)
					{
						canInflict = false;
						collide->deflectState = true;
					}
				}
				break;
			}
		}
		else if(collide->attacksPriority==6)
		{
			boolean inflicted = false;
			if(playr->attacksPriority!=7)
			{
				inflicted = collide->onDeflectPlayerDamage(playr, amount);
			}
			if(inflicted)
			{
				canInflict = false;
				collide->deflectState = true;
			}
		}
		if(canInflict)
		{
			collide->percent+=amount;
			if(collide->percent>999)
			{
				collide->percent=999;
			}
		}
	}
	
	void AttackTemplates::causeHurtLaunch(Player*playr, Player*collide, int xDir, float xAmount, float xMult, int yDir, float yAmount, float yMult)
	{
		if(collide->deflectState)
		{
			collide->onDeflectPlayerLaunch(playr, xDir, xAmount, xMult, yDir, yAmount, yMult);
		}
		else
		{
			if(collide->holdingPlayer)
			{
				collide->releasePlayer();
			}
			
			//float oldXvel;
			//float oldYvel;
			float newyVel=(float)(yDir*(yAmount+(yMult*(collide->percent))/75));
			float newxVel=(float)(xDir*(xAmount+(xMult*(collide->percent))/75));
			//Console::WriteLine(this.attacksHolder + ": " + newyVel + "");
			if(newyVel>0)
			{
				if(newyVel>collide->yvelocity)
				{
					collide->yvelocity=newyVel;
				}
			}
			else if(newyVel<0)
			{
				if(newyVel<collide->yvelocity)
				{
					collide->yvelocity=newyVel;
				}
			}
			if(newxVel>0)
			{
				if(newxVel>collide->xvelocity)
				{
					collide->xvelocity=newxVel;
				}
			}
			else if(newxVel<0)
			{
				if(newxVel<collide->xvelocity)
				{
					collide->xvelocity=newxVel;
				}
			}
			collide->y-=1;
			if(collide->yvelocity>0 && collide->isOnGround())
			{
				collide->yvelocity = -(collide->yvelocity/2);
			}
		}
	}

	void AttackTemplates::causeHurt(Player*playr, Player*collide, byte dir, int time)
	{
		if(collide->deflectState)
		{
			byte d = Player::LEFT;
			if(playr->xvelocity < 0)
			{
				d = Player::RIGHT;
			}
			collide->causeHurt(playr, d, time);
			collide->deflectState = false;
		}
		else
		{
			if(std::abs(collide->xvelocity)<=3)
			{
				if(std::abs(collide->yvelocity)<=3)
				{
					collide->changeTwoSidedAnimation("hurt_minor", NO_CHANGE, dir);
				}
				else if((std::abs(collide->yvelocity)>3)&&(std::abs(collide->yvelocity)<7))
				{
					collide->changeTwoSidedAnimation("hurt_minor", NO_CHANGE, dir);
				}
				else if((std::abs(collide->yvelocity)>=7)&&(std::abs(collide->yvelocity)<12))
				{
					collide->changeTwoSidedAnimation("hurt_flip", NO_CHANGE, dir);
				}
				else if(std::abs(collide->yvelocity)>=12)
				{
					collide->changeAnimation("hurt_spin_up", NO_CHANGE);
				}
			}

			else if((std::abs(collide->xvelocity)>3)&&(std::abs(collide->xvelocity)<7))
			{
				if(std::abs(collide->yvelocity)<=3)
				{
					collide->changeTwoSidedAnimation("hurt_fly", NO_CHANGE, dir);
				}
				else if((std::abs(collide->yvelocity)>3)&&(std::abs(collide->yvelocity)<7))
				{
					collide->changeTwoSidedAnimation("hurt_minor", NO_CHANGE, dir);
				}
				else if((std::abs(collide->yvelocity)>=7)&&(std::abs(collide->yvelocity)<12))
				{
					collide->changeTwoSidedAnimation("hurt_fly", NO_CHANGE, dir);
				}
				else if(std::abs(collide->yvelocity)>=12)
				{
					collide->changeTwoSidedAnimation("hurt_flip", NO_CHANGE, dir);
				}
			}

			else if(std::abs(collide->xvelocity)>=7)
			{
				if(std::abs(collide->yvelocity)<=3)
				{
					collide->changeTwoSidedAnimation("hurt_spin", NO_CHANGE, dir);
				}
				else if((std::abs(collide->yvelocity)>3)&&(std::abs(collide->yvelocity)<7))
				{
					collide->changeTwoSidedAnimation("hurt_spin", NO_CHANGE, dir);
				}
				else if((std::abs(collide->yvelocity)>=7)&&(std::abs(collide->yvelocity)<12))
				{
					collide->changeTwoSidedAnimation("hurt_spin", NO_CHANGE, dir);
				}
				else if(std::abs(collide->yvelocity)>=12)
				{
					collide->changeTwoSidedAnimation("hurt_flip", NO_CHANGE, dir);
				}
			}
			collide->xVel=0;
			collide->yVel=0;
			collide->attackTime=0;
			collide->chargingAttack=false;
			collide->bUp=false;
			collide->up=false;
			collide->hurt=2;
			collide->landing=false;
			collide->jumping=false;
			collide->tossing=false;
			collide->grabbing=false;
			//collide->moveLeft=0;
			//collide->moveRight=0;
			collide->hanging=false;
			collide->attacksHolder=-1;
			collide->attacksPriority=0;
			collide->canDo=false;
			collide->hurtTime=Global::worldTime+time;
			collide->hurtFrame=4;
			collide->runTime=0;
			collide->chargeSmash=0;
			collide->lastHit = playr->playerNo;
			collide->destroyCharge();
			collide->setToDefaultValues();
			
			if(collide->itemHolding!=null)
			{
				collide->itemHolding->onHolderHurt();
			}
			/*if(itemActor->itemOwner>0)
			{
				collide->lastHit=itemOwner;
			}*/
		}
	}
	
	void AttackTemplates::normalA(Player*playr, int aNo, double aP)
	{
		playr->jumping = false;
		playr->hurt = 0;
		playr->changeTwoSidedAnimation("standard_attack", FORWARD);
		playr->attacksHolder=aNo;
		playr->attacksPriority=aP;
	}

	void AttackTemplates::combo2A(Player*playr, long comTime, int aNo,double aP,int aNo2,double aP2, boolean loopLast)
	{
		playr->jumping = false;
		playr->hurt = 0;
		if(!(Global::worldTime<=(playr->comboTime+comTime)))
		{
			playr->standardCombo=0;
			playr->comboTime=0;
		}
		switch(playr->standardCombo)
		{
			case 0:
			playr->standardCombo=1;
			playr->attacksHolder=aNo;
			playr->attacksPriority=aP;
			playr->changeTwoSidedAnimation("standard_attack", FORWARD);
			playr->comboTime=Global::worldTime;
			break;
 
			case 1:
			if(loopLast)
			{
				playr->comboTime=Global::worldTime;
			}
			else
			{
				playr->standardCombo=0;
				playr->comboTime=0;
			}
			playr->attacksHolder=aNo2;
			playr->attacksPriority=aP2;
			playr->changeTwoSidedAnimation("standard_attack2", FORWARD);
			break;
		}
	}
	
	void AttackTemplates::combo3A(Player*playr, long comTime, int aNo,double aP,int aNo2,double aP2,int aNo3, double aP3, boolean loopLast)
	{
		playr->jumping = false;
		playr->hurt = 0;
		if(!(Global::worldTime<=(playr->comboTime+comTime)))
		{
			playr->standardCombo=0;
			playr->comboTime=0;
		}
		switch(playr->standardCombo)
		{
			case 0:
			playr->standardCombo=1;
			playr->attacksHolder=aNo;
			playr->attacksPriority=aP;
			playr->changeTwoSidedAnimation("standard_attack", FORWARD);
			playr->comboTime=Global::worldTime;
			break;
			
			case 1:
			playr->standardCombo=2;
			playr->attacksHolder=aNo2;
			playr->attacksPriority=aP2;
			playr->changeTwoSidedAnimation("standard_attack2", FORWARD);
			playr->comboTime=Global::worldTime;
			break;
			
			case 2:
			if(loopLast)
			{
				playr->comboTime=Global::worldTime;
			}
			else
			{
				playr->standardCombo=0;
				playr->comboTime=0;
			}
			playr->attacksHolder=aNo3;
			playr->attacksPriority=aP3;
			playr->changeTwoSidedAnimation("standard_attack3", FORWARD);
			break;
		}
	}
	
	void AttackTemplates::normalAirA(Player*playr, int aNo, double aP)
	{
		playr->hurt = 0;
		playr->up=false;
		playr->jumping=false;
		playr->changeTwoSidedAnimation("air_attack", FORWARD);
		playr->attacksHolder=aNo;
		playr->attacksPriority=aP;
	}

	void AttackTemplates::normalSideA(Player*playr, int aNo, double aP)
	{
		playr->jumping = false;
		playr->hurt = 0;
		playr->changeTwoSidedAnimation("standard_attack_side", FORWARD);
		playr->attacksHolder=aNo;
		playr->attacksPriority=aP;
	}

	void AttackTemplates::normalDashA(Player*playr, int aNo, double aP, float speed)
	{
		playr->jumping = false;
		playr->hurt = 0;
		playr->changeTwoSidedAnimation("dash_attack", FORWARD);
		playr->xVel = playr->getPlayerDirMult()*speed;
		playr->attacksHolder=aNo;
		playr->attacksPriority=aP;
	}

	void AttackTemplates::normalAirSideA(Player*playr, int aNo, double aP)
	{
		playr->hurt = 0;
		playr->up=false;
		playr->jumping=false;
		playr->changeTwoSidedAnimation("air_attack_side", FORWARD);
		playr->attacksHolder=aNo;
		playr->attacksPriority=aP;
	}

	void AttackTemplates::rehitAirSideA(Player*playr, int aNo, double aP)
	{
		playr->hurt = 0;
		playr->up=false;
		playr->jumping=false;
		playr->hitAmount=0;
		playr->changeTwoSidedAnimation("air_attack_side", FORWARD);
		playr->attacksHolder=aNo;
		playr->attacksPriority=aP;
	}

	void AttackTemplates::normalUpA(Player*playr, int aNo, double aP)
	{
		playr->jumping = false;
		playr->hurt = 0;
		playr->changeTwoSidedAnimation("standard_attack_up", FORWARD);
		playr->attacksHolder=aNo;
		playr->attacksPriority=aP;
	}

	void AttackTemplates::normalAirUpA(Player*playr, int aNo, double aP)
	{
		playr->hurt = 0;
		playr->up=false;
		playr->jumping=false;
		playr->changeTwoSidedAnimation("air_attack_up", FORWARD);
		playr->attacksHolder=aNo;
		playr->attacksPriority=aP;
	}
	
	void AttackTemplates::normalDownA(Player*playr, int aNo, double aP)
	{
		playr->jumping = false;
		playr->hurt = 0;
		playr->changeTwoSidedAnimation("standard_attack_down", FORWARD);
		playr->attacksHolder=aNo;
		playr->attacksPriority=aP;
	}

	void AttackTemplates::normalAirDownA(Player*playr, int aNo, double aP)
	{
		playr->hurt = 0;
		playr->up=false;
		playr->jumping=false;
		playr->changeTwoSidedAnimation("air_attack_down", FORWARD);
		playr->attacksHolder=aNo;
		playr->attacksPriority=aP;
	}

	void AttackTemplates::singleAirDownA(Player*playr, int aNo, double aP)
	{
		playr->hurt = 0;
		playr->up=false;
		playr->jumping=false;
		playr->attacksHolder=aNo;
		playr->attacksPriority=aP;
		playr->changeAnimation("air_attack_down", FORWARD);
	}

	void AttackTemplates::dropAirDownA(Player*playr, int type, int aNo, double aP, float speedY, float speedX)
	{
		playr->hurt = 0;
		playr->up=false;
		playr->jumping=false;
		switch(type)
		{
			case Player::STEP_CHARGE:
			if((playr->yvelocity)>=-8)
			{
				playr->yvelocity=-1;
			}
			else
			{
				playr->yvelocity+=6;
			}
			playr->landing=true;
			playr->changeTwoSidedAnimation("air_prep_down", FORWARD);
			break;
	 
			case Player::STEP_GO:
			playr->landing=false;
			if((playr->yvelocity)<=(-speedY))
			{
				playr->yvelocity+=speedY;
			}
			else if(playr->yvelocity > 0 && playr->yvelocity < speedY)
			{
				playr->yvelocity=speedY;
			}
			playr->xvelocity = playr->getPlayerDirMult()*speedX;
			playr->changeTwoSidedAnimation("air_attack_down", FORWARD);
			playr->attacksHolder=aNo;
			playr->attacksPriority=aP;
			break;
	 
			case Player::STEP_FINISH:
			if(playr->isOnGround())
			{
				playr->landing=true;
				playr->attacksHolder=-1;
				playr->attacksPriority=0;
				playr->xvelocity=0;
				playr->changeTwoSidedAnimation("air_land_down", FORWARD);
			}
			else
			{
				playr->animFinish();
				playr->xvelocity=0;
			}
			break;
		}
	}
	
	void AttackTemplates::normalB(Player*playr, int aNo, double aP)
	{
		playr->jumping = false;
		playr->hurt = 0;
		playr->changeTwoSidedAnimation("special_attack_side", FORWARD);
		playr->attacksHolder=aNo;
		playr->attacksPriority=aP;
	}
	
	void AttackTemplates::chargeB(Player*playr, float spMin, float spMax, long totalTime)
	{
		playr->jumping = false;
		playr->hurt = 0;
		playr->chargebar = new Chargebar(playr->getPlayerNo(),spMin, spMax, totalTime, Chargebar::TYPE_SPECIALATTACK);
		playr->chargingAttack = true;
	}
	
	/*void AttackTemplates::chargeB2(Player*playr, int spMin, int spMax, int chargeTotal, int cx1, int cy1, int cbd)
	{
		char chargename[30];
		char chargeAnim[30];
		char chargeTimer[50];
		Actor*chargeActor;
		sprintf(chargeAnim, "chargebar%i", chargeTotal);
		sprintf(chargeTimer, "%stimer", chargeAnim);
		playr->hurt=0;
		sprintf(chargename, "chargebar%i", playr->playerNo);
		playr->attacksPriority=-1;
		switch(playr->playerdir)
		{
			case 1:
			playr->charging_bdown=cbd;
			CreateActor(chargename, chargeAnim, playr->clonename, "(none)", cx1, cy1, true);
			playr->changeAnimation("smash_charge_left", FORWARD);
			chargeActor=getclone(chargename);
			chargeActor->smashPowerMax=spMax;
			chargeActor->smashPowerCharge=spMin*1000;
			//CreateTimer(chargename, chargeTimer, getChargeIncr(chargeTotal));
			break;
	 
			case 2:
			playr->charging_bdown=cbd;
			CreateActor(chargename, chargeAnim, playr->clonename, "(none)", cx1, cy1, true);
			playr->changeAnimation("smash_charge_right", FORWARD);
			chargeActor=getclone(chargename);
			chargeActor->smashPowerMax=spMax;
			chargeActor->smashPowerCharge=spMin*1000;
			//CreateTimer(chargename, chargeTimer, getChargeIncr(chargeTotal));
			break;
		}
	}*/
	
	void AttackTemplates::homingB(Player*playr, int aNo, double aP, float speed)
	{
		ArrayList<Player*> targets = ArrayList<Player*>();
		int i;
		float speedX = 0;
		float speedY = 0;
		for(i=1; i<=Global::possPlayers; i++)
		{
			Player*checker = Global::getPlayerActor(i);
			if(checker!=null)
			{
				if((checker->isAlive()) && (i!=playr->playerNo) && !(Global::teamBattle && checker->team!=playr->team))
				{
					double d=PrimitiveActor::distanceUnSqr(playr->x,playr->y,checker->x,checker->y);
					if(d<=22500)
					{
						targets.add(checker);
					}
				}
			}
		}
		if(targets.size()>1)
		{
			int closest=0;
			Player*closePlayer;
			for(i=2; i<targets.size(); i++)
			{
				Player*target=targets.get(closest);
				Player*newTarget=targets.get(i);
				double d=PrimitiveActor::distanceUnSqr(playr->x,playr->y,target->x,target->y);
				double d2=PrimitiveActor::distanceUnSqr(playr->x,playr->y,newTarget->x,newTarget->y);
				if(d2<d)
				{
					closest=i;
				}
			}
			closePlayer=targets.get(closest);
			if((playr->x)<(closePlayer->x))
			{
				playr->playerdir=Player::RIGHT;
			}
			else if((playr->x)>(closePlayer->x))
			{
				playr->playerdir=Player::LEFT;
			}
			double dist = PrimitiveActor::distance(playr->x, playr->y, closePlayer->x, closePlayer->y);
			speedX=(float)(((closePlayer->x-playr->x)/dist)*speed);
			speedY=(float)(((closePlayer->y-playr->y)/dist)*speed);
		}
		else if(targets.size()==1)
		{
			Player*closePlayer = targets.get(0);
			if((playr->x)<(closePlayer->x))
			{
				playr->playerdir=Player::RIGHT;
			}
			else if((playr->x)>(closePlayer->x))
			{
				playr->playerdir=Player::LEFT;
			}
			double dist = PrimitiveActor::distance(playr->x, playr->y, closePlayer->x, closePlayer->y);
			speedX=(float)(((closePlayer->x-playr->x)/dist)*speed);
			speedY=(float)(((closePlayer->y-playr->y)/dist)*speed);
		}
		else
		{
			speedX = 0.7f*speed * playr->getPlayerDirMult();
			speedY=0.7f*speed;
		}
		playr->xvelocity=speedX;
		playr->yvelocity=speedY;
		//playr->recoverTime=Global::worldTime+wait;
		
		playr->changeTwoSidedAnimation("special_attack", FORWARD);
		playr->attacksHolder=aNo;
		playr->attacksPriority=aP;
	}
	
	void AttackTemplates::singleProjectile(Player*playr, int aNo, double aP, Projectile*projectile)
	{
		playr->jumping = false;
		playr->hurt = 0;
		playr->attacksHolder=aNo;
		playr->createProjectile(projectile);
		playr->attacksPriority=aP;
	}
	
	void AttackTemplates::normalSideB(Player*playr, int aNo, double aP)
	{
		playr->jumping = false;
		playr->hurt = 0;
		playr->changeTwoSidedAnimation("special_attack_side", FORWARD);
		playr->attacksHolder=aNo;
		playr->attacksPriority=aP;
	}
	
	void AttackTemplates::moveSideB(Player*playr, int aNo, double aP, float xDist)
	{
		playr->jumping = false;
		playr->hurt = 0;
		playr->changeTwoSidedAnimation("special_attack_side", FORWARD);
		playr->x += xDist * playr->getPlayerDirMult();
		playr->attacksHolder=aNo;
		playr->attacksPriority=aP;
	}

	void AttackTemplates::dashSideB(Player*playr, int aNo, double aP, float speed)
	{
		playr->jumping = false;
		playr->hurt = 0;
		playr->changeTwoSidedAnimation("special_attack_side", FORWARD);
		playr->xVel = speed * playr->getPlayerDirMult();
		playr->attacksHolder=aNo;
		playr->attacksPriority=aP;
	}

	void AttackTemplates::rollAttack(Player*playr, int aNo, double aP, float speed, long time)
	{
		playr->jumping = false;
		playr->hurt = 0;
		playr->changeTwoSidedAnimation("roll", FORWARD);
		playr->xVel = speed * playr->getPlayerDirMult();
		playr->attacksHolder=aNo;
		playr->attacksPriority=aP;
		playr->attackTime=(Global::worldTime+time);
	}

	void AttackTemplates::launchUpB(Player*playr, int aNo, double aP, float yVeloc, float yVeloc2)
	{
		playr->jumping = false;
		playr->hurt = 0;
		playr->changeTwoSidedAnimation("special_attack_up", FORWARD);
		//playr->bUpWaitTime=Global::worldTime+wTime;
		playr->attacksHolder=aNo;
		playr->attacksPriority=aP;
		if(playr->isOnGround())
		{
			playr->yvelocity=-yVeloc2;
		}
		else
		{
			playr->yvelocity=-yVeloc;
		}
		playr->bUp=true;
	}

	void AttackTemplates::rehitUpB(Player*playr, int aNo, double aP, float yVeloc, float yVeloc2)
	{
		playr->jumping = false;
		playr->hurt = 0;
		playr->hitAmount=0;
		playr->changeTwoSidedAnimation("special_attack_up", FORWARD);
		//playr->bUpWaitTime=Global::worldTime+wTime;
		playr->attacksHolder=aNo;
		playr->attacksPriority=aP;
		
		if(playr->isOnGround())
		{
			playr->yvelocity=-yVeloc2;
		}
		else
		{
			playr->yvelocity=-yVeloc;
		}
		playr->bUp=true;
	}

	void AttackTemplates::rehitUpB2(Player*playr, int aNo, double aP, float yVeloc, float yVeloc2)
	{
		playr->jumping = false;
		playr->hurt = 0;
		playr->hitAmount=0;
		playr->changeTwoSidedAnimation("special_attack_up", FORWARD);
		//playr->bUpWaitTime=Global::worldTime+wTime;
		playr->attacksHolder=aNo;
		playr->attacksPriority=aP;
		
		if(playr->isOnGround())
		{
			playr->yVel=-yVeloc2;
		}
		else
		{
			playr->yVel=-yVeloc;
		}
		playr->bUp=true;
	}

	void AttackTemplates::normalDownB(Player*playr,int aNo,double aP)
	{
		playr->hurt = 0;
		playr->up=false;
		playr->jumping=false;
		playr->changeTwoSidedAnimation("special_attack_down", FORWARD);
		playr->attacksHolder=aNo;
		playr->attacksPriority=aP;
	}

	void AttackTemplates::prepareDownB(Player*playr, int aNo, double aP)
	{
		playr->hurt = 0;
		playr->up=false;
		playr->jumping=false;
		playr->changeTwoSidedAnimation("special_prep_down", FORWARD);
		playr->attacksHolder=aNo;
		playr->attacksPriority=aP;
	}

	void AttackTemplates::bounceDownB(Player*playr,int aNo,double aP,float speed)
	{
		playr->hurt = 0;
		playr->up=false;
		playr->jumping=false;
		playr->changeTwoSidedAnimation("special_attack_down", FORWARD);
		playr->attacksHolder=aNo;
		playr->attacksPriority=aP;
		
		if(playr->yvelocity<=0)
		{
			playr->yvelocity+=speed;
		}
		else if(playr->yvelocity<speed)
		{
			playr->yvelocity=speed;
		}
	}
	
	void AttackTemplates::normalSmash(Player*playr, int aNo, double aP, byte type, int smashType, long totalTime, int cMin, int cMax)
	{
		playr->hurt = 0;
		playr->jumping = false;
		switch(type)
		{
			case Player::STEP_CHARGE:
			playr->chargebar = new Chargebar(playr->getPlayerNo(),(float)cMin, (float)cMax, totalTime, Chargebar::TYPE_SMASHATTACK);
			playr->chargeSmash = smashType;
			playr->yvelocity = 0;
			playr->changeTwoSidedAnimation("smash_charge", FORWARD);
			break;
			
			case Player::STEP_GO:
			playr->chargeSmash = 0;
			playr->attacksHolder=aNo;
			playr->attacksPriority=aP;
			switch(smashType)
			{
				case 1:
				playr->changeTwoSidedAnimation("smash_attack",FORWARD);
				break;
				
				case 2:
				playr->changeTwoSidedAnimation("smash_attack_up",FORWARD);
				break;
				
				case 3:
				playr->changeTwoSidedAnimation("smash_attack_down",FORWARD);
				break;
			}
			break;
		}
	}
	
	void AttackTemplates::stopSmashAttack(Player*playr)
	{
		playr->chargeSmash = 0;
		playr->chargingAttack = false;
		if(playr->chargebar!=null)
		{
			playr->smashPower = (int)playr->chargebar->currentPower;
			delete playr->chargebar;
			playr->chargebar = null;
		}
	}
	
	void AttackTemplates::finalSmash(Player*playr, int aNo)
	{
		playr->hurt = 0;
		playr->jumping = false;
		if(playr->canFinalSmash())
		{
			playr->canFinalsmash = false;
			playr->attacksPriority = 7;
			if(playr->itemWielding!=null)
			{
				if(playr->itemWielding->getItemNo()==Global::ITEM_SMASHBALL)
				{
					playr->itemWielding->onDestroy();
					playr->itemWielding = null;
					Global::playerHasSmashBall = true;
				}
			}
			playr->attacksHolder=aNo;
		}
	}
	
	void AttackTemplates::finishFinalSmash(Player*playr)
	{
		playr->attacksPriority = 0;
		Global::playerHasSmashBall = false;
		Global::smashBallOnField = false;
	}
}