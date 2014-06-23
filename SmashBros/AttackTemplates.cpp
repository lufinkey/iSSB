#include "AttackTemplates.h"
#include "Global.h"
#include "Item.h"

namespace SmashBros
{
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
				if(playr->x<collide->x && PrimitiveActor::getDir(collide->getHitbox(),playr->getHitbox())!=PrimitiveActor::DIR_LEFT)
				{
					boolean inflicted = collide->onPlayerDeflectDamage(playr, amount);
					if(inflicted)
					{
						canInflict = false;
						collide->deflectState = true;
					}
				}
				break;
				
				case Player::RIGHT:
				if(playr->x>collide->x && PrimitiveActor::getDir(collide,playr)!=PrimitiveActor::DIR_RIGHT)
				{
					boolean inflicted = collide->onPlayerDeflectDamage(playr, amount);
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
			boolean inflicted = collide->onPlayerDeflectDamage(playr, amount);
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
			collide->onPlayerDeflectLaunch(playr, xDir, xAmount, xMult, yDir, yAmount, yMult);
		}
		else
		{
		    //float oldXvel;
		    //float oldYvel;
		    float newyVel=(float)(yDir*(yAmount+(yMult*(collide->percent))/100));
		    float newxVel=(float)(xDir*(xAmount+(xMult*(collide->percent))/100));
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
		if(!collide->deflectState)
		{
		    if(abs(collide->xvelocity)<=3)
		    {
		        if(abs(collide->yvelocity)<=3)
		        {
		            switch(dir)
		            {
		                case Player::LEFT:
		                collide->changeAnimation("hurt_minor_left", NO_CHANGE);
		                break;
		 
		                case Player::RIGHT:
		                collide->changeAnimation("hurt_minor_right", NO_CHANGE);
		                break;
		            }
		        }
		        else if((abs(collide->yvelocity)>3)&&(abs(collide->yvelocity)<7))
		        {
		            switch(dir)
		            {
		                case Player::LEFT:
		                collide->changeAnimation("hurt_minor_left", NO_CHANGE);
		                break;
		 
		                case Player::RIGHT:
		                collide->changeAnimation("hurt_minor_right", NO_CHANGE);
		                break;
		            }
		        }
		        else if((abs(collide->yvelocity)>=7)&&(abs(collide->yvelocity)<12))
		        {
		            switch(dir)
		            {
		                case Player::LEFT:
		                collide->changeAnimation("hurt_flip_left", NO_CHANGE);
		                break;
		 
		                case Player::RIGHT:
		                collide->changeAnimation("hurt_flip_left", NO_CHANGE);
		                break;
		            }
		        }
		        else if(abs(collide->yvelocity)>=12)
		        {
		            collide->changeAnimation("hurt_spin_up", NO_CHANGE);
		        }
		    }
		 
		    else if((abs(collide->xvelocity)>3)&&(abs(collide->xvelocity)<7))
		    {
		        if(abs(collide->yvelocity)<=3)
		        {
		            switch(dir)
		            {
		                case Player::LEFT:
		                collide->changeAnimation("hurt_fly_left", NO_CHANGE);
		                break;
		 
		                case Player::RIGHT:
		                collide->changeAnimation("hurt_fly_right", NO_CHANGE);
		                break;
		            }
		        }
		        else if((abs(collide->yvelocity)>3)&&(abs(collide->yvelocity)<7))
		        {
		            switch(dir)
		            {
		                case Player::LEFT:
		                collide->changeAnimation("hurt_minor_left", NO_CHANGE);
		                break;
		 
		                case Player::RIGHT:
		                collide->changeAnimation("hurt_minor_right", NO_CHANGE);
		                break;
		            }
		        }
		        else if((abs(collide->yvelocity)>=7)&&(abs(collide->yvelocity)<12))
		        {
		            switch(dir)
		            {
		                case Player::LEFT:
		                collide->changeAnimation("hurt_fly_left", NO_CHANGE);
		                break;
		 
		                case Player::RIGHT:
		                collide->changeAnimation("hurt_fly_right", NO_CHANGE);
		                break;
		            }
		        }
		        else if(abs(collide->yvelocity)>=12)
		        {
		            switch(dir)
		            {
		                case Player::LEFT:
		                collide->changeAnimation("hurt_flip_left", NO_CHANGE);
		                break;
		 
		                case Player::RIGHT:
		                collide->changeAnimation("hurt_flip_right", NO_CHANGE);
		                break;
		            }
		        }
		    }
		 
		    else if(abs(collide->xvelocity)>=7)
		    {
		        if(abs(collide->yvelocity)<=3)
		        {
		            switch(dir)
		            {
		                case Player::LEFT:
		                collide->changeAnimation("hurt_spin_left", NO_CHANGE);
		                break;
		 
		                case Player::RIGHT:
		                collide->changeAnimation("hurt_spin_right", NO_CHANGE);
		                break;
		            }
		        }
		        else if((abs(collide->yvelocity)>3)&&(abs(collide->yvelocity)<7))
		        {
		            switch(dir)
		            {
		                case Player::LEFT:
		                collide->changeAnimation("hurt_spin_left", NO_CHANGE);
		                break;
		 
		                case Player::RIGHT:
		                collide->changeAnimation("hurt_spin_right", NO_CHANGE);
		                break;
		            }
		        }
		        else if((abs(collide->yvelocity)>=7)&&(abs(collide->yvelocity)<12))
		        {
		            switch(dir)
		            {
		                case Player::LEFT:
		                collide->changeAnimation("hurt_spin_left", NO_CHANGE);
		                break;
		 
		                case Player::RIGHT:
		                collide->changeAnimation("hurt_spin_right", NO_CHANGE);
		                break;
		            }
		        }
		        else if(abs(collide->yvelocity)>=12)
		        {
		            switch(dir)
		            {
		                case Player::LEFT:
		                collide->changeAnimation("hurt_flip_left", NO_CHANGE);
		                break;
		 
		                case Player::RIGHT:
		                collide->changeAnimation("hurt_flip_right", NO_CHANGE);
		                break;
		            }
		        }
		    }
		    collide->xVel=0;
		    collide->yVel=0;
		    collide->attackTime=0;
		    collide->setToDefaultValues();
		    collide->chargingAttack=false;
		    collide->bUp=false;
		    collide->up=false;
		    collide->hurt=2;
		    collide->landing=false;
		    collide->jumping=false;
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
	    switch(playr->playerdir)
	    {
	        case 1:
	        playr->changeAnimation("standard_attack_left", FORWARD);
	        break;
	 
	        case 2:
	        playr->changeAnimation("standard_attack_right", FORWARD);
	        break;
	    }
	    playr->attacksHolder=aNo;
        playr->attacksPriority=aP;
	}

	void AttackTemplates::combo2A(Player*playr, int comTime, int aNo,double aP,int aNo2,double aP2)
	{
		playr->jumping = false;
		playr->hurt = 0;
	    if(!(Global::worldTime<=(playr->comboTime+comTime)))
	    {
	        playr->standardCombo=0;
	        playr->comboTime=0;
	    }
	    switch(playr->playerdir)
	    {
	        case 1:
	        switch(playr->standardCombo)
	        {
	            case 0:
	            playr->standardCombo=1;
	            playr->attacksHolder=aNo;
	            playr->attacksPriority=aP;
	            playr->changeAnimation("standard_attack_left", FORWARD);
	            playr->comboTime=Global::worldTime;
	            break;
	 
	            case 1:
	            playr->standardCombo=0;
	            playr->attacksHolder=aNo2;
	            playr->attacksPriority=aP2;
	            playr->changeAnimation("standard_attack2_left", FORWARD);
	            playr->comboTime=0;
	            break;
	        }
	        break;
	 
	        case 2:
	        switch(playr->standardCombo)
	        {
	            case 0:
	            playr->standardCombo=1;
	            playr->attacksHolder=aNo;
	            playr->attacksPriority=aP;
	            playr->changeAnimation("standard_attack_right", FORWARD);
	            playr->comboTime=Global::worldTime;
	            break;
	 
	            case 1:
	            playr->standardCombo=0;
	            playr->attacksHolder=aNo2;
	            playr->attacksPriority=aP2;
	            playr->changeAnimation("standard_attack2_right", FORWARD);
	            playr->comboTime=0;
	            break;
	        }
	        break;
	    }
	}

	void AttackTemplates::combo3A(Player*playr, int comTime, int aNo,double aP,int aNo2,double aP2,int aNo3, double aP3)
	{
		playr->jumping = false;
		playr->hurt = 0;
	    if(!(Global::worldTime<=(playr->comboTime+comTime)))
	    {
	        playr->standardCombo=0;
	        playr->comboTime=0;
	    }
	    switch(playr->playerdir)
	    {
	        case 1:
	        switch(playr->standardCombo)
	        {
	            case 0:
	            playr->standardCombo=1;
	            playr->attacksHolder=aNo;
	            playr->attacksPriority=aP;
	            playr->changeAnimation("standard_attack_left", FORWARD);
	            playr->comboTime=Global::worldTime;
	            break;
	 
	            case 1:
	            playr->standardCombo=2;
	            playr->attacksHolder=aNo2;
	            playr->attacksPriority=aP2;
	            playr->changeAnimation("standard_attack2_left", FORWARD);
	            playr->comboTime=Global::worldTime;
	            break;
	 
	            case 2:
	            playr->standardCombo=0;
	            playr->attacksHolder=aNo3;
	            playr->attacksPriority=aP3;
	            playr->changeAnimation("standard_attack3_left", FORWARD);
	            playr->comboTime=0;
	            break;
	        }
	        break;
	 
	        case 2:
	        switch(playr->standardCombo)
	        {
	            case 0:
	            playr->standardCombo=1;
	            playr->attacksHolder=aNo;
	            playr->attacksPriority=aP;
	            playr->changeAnimation("standard_attack_right", FORWARD);
	            playr->comboTime=Global::worldTime;
	            break;
	 
	            case 1:
	            playr->standardCombo=2;
	            playr->attacksHolder=aNo2;
	            playr->attacksPriority=aP2;
	            playr->changeAnimation("standard_attack2_right", FORWARD);
	            playr->comboTime=Global::worldTime;
	            break;
	 
	            case 2:
	            playr->standardCombo=0;
	            playr->attacksHolder=aNo3;
	            playr->attacksPriority=aP3;
	            playr->changeAnimation("standard_attack3_right", FORWARD);
	            playr->comboTime=0;
	            break;
	        }
	        break;
	    }
	}

	void AttackTemplates::normalAirA(Player*playr, int aNo, double aP)
	{
		playr->hurt = 0;
	    playr->up=false;
	    playr->jumping=false;
	    switch(playr->playerdir)
	    {
	        case 1:
	        playr->changeAnimation("air_attack_left", FORWARD);
	        break;
	 
	        case 2:
	        playr->changeAnimation("air_attack_right", FORWARD);
	        break;
	    }
	    playr->attacksHolder=aNo;
        playr->attacksPriority=aP;
	}

	void AttackTemplates::normalSideA(Player*playr, int aNo, double aP)
	{
		playr->jumping = false;
		playr->hurt = 0;
	    switch(playr->playerdir)
	    {
	        case 1:
	        playr->changeAnimation("standard_attack_side_left", FORWARD);
	        break;
	 
	        case 2:
	        playr->changeAnimation("standard_attack_side_right", FORWARD);
	        break;
	    }
	    playr->attacksHolder=aNo;
        playr->attacksPriority=aP;
	}

	void AttackTemplates::normalDashA(Player*playr, int aNo, double aP, float speed)
	{
		playr->jumping = false;
		playr->hurt = 0;
	    switch(playr->playerdir)
	    {
	        case 1:
	        playr->changeAnimation("dash_attack_left", FORWARD);
	        playr->xVel=-speed;
	        break;
	 
	        case 2:
	        playr->changeAnimation("dash_attack_right", FORWARD);
	        playr->xVel=speed;
	        break;
	    }
	    playr->attacksHolder=aNo;
        playr->attacksPriority=aP;
	}

	void AttackTemplates::normalAirSideA(Player*playr, int aNo, double aP)
	{
		playr->hurt = 0;
	    playr->up=false;
	    playr->jumping=false;
	    switch(playr->playerdir)
	    {
	        case 1:
	        playr->changeAnimation("air_attack_side_left", FORWARD);
	        break;
	 
	        case 2:
	        playr->changeAnimation("air_attack_side_right", FORWARD);
	        break;
	    }
	    playr->attacksHolder=aNo;
        playr->attacksPriority=aP;
	}

	void AttackTemplates::rehitAirSideA(Player*playr, int aNo, double aP)
	{
		playr->hurt = 0;
	    playr->up=false;
	    playr->jumping=false;
	    playr->hitAmount=0;
	    switch(playr->playerdir)
	    {
	        case 1:
	        playr->changeAnimation("air_attack_side_left", FORWARD);
	        break;
	 
	        case 2:
	        playr->changeAnimation("air_attack_side_right", FORWARD);
	        break;
	    }
	    playr->attacksHolder=aNo;
        playr->attacksPriority=aP;
	}

	void AttackTemplates::normalUpA(Player*playr, int aNo, double aP)
	{
		playr->jumping = false;
		playr->hurt = 0;
	    switch(playr->playerdir)
	    {
	        case 1:
	        playr->changeAnimation("standard_attack_up_left", FORWARD);
	        break;
	 
	        case 2:
	        playr->changeAnimation("standard_attack_up_right", FORWARD);
	        break;
	    }
	    playr->attacksHolder=aNo;
        playr->attacksPriority=aP;
	}

	void AttackTemplates::normalAirUpA(Player*playr, int aNo, double aP)
	{
		playr->hurt = 0;
	    playr->up=false;
	    playr->jumping=false;
	    switch(playr->playerdir)
	    {
	        case 1:
	        playr->changeAnimation("air_attack_up_left", FORWARD);
	        break;
	 
	        case 2:
	        playr->changeAnimation("air_attack_up_right", FORWARD);
	        break;
	    }
	    playr->attacksHolder=aNo;
        playr->attacksPriority=aP;
	}
	
	void AttackTemplates::normalDownA(Player*playr, int aNo, double aP)
	{
		playr->jumping = false;
		playr->hurt = 0;
	    switch(playr->playerdir)
	    {
	        case 1:
	        playr->changeAnimation("standard_attack_down_left", FORWARD);
	        break;
	 
	        case 2:
	        playr->changeAnimation("standard_attack_down_right", FORWARD);
	        break;
	    }
	    playr->attacksHolder=aNo;
        playr->attacksPriority=aP;
	}

	void AttackTemplates::normalAirDownA(Player*playr, int aNo, double aP)
	{
		playr->hurt = 0;
	    playr->up=false;
	    playr->jumping=false;
	    switch(playr->playerdir)
	    {
	        case 1:
	        playr->changeAnimation("air_attack_down_left", FORWARD);
	        break;
	 
	        case 2:
	        playr->changeAnimation("air_attack_down_right", FORWARD);
	        break;
	    }
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

	void AttackTemplates::dropAirDownA(Player*playr, int type, int aNo, double aP, float speed, float speed2)
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
	        switch(playr->playerdir)
	        {
	            case 1:
	            playr->changeAnimation("air_prep_down_left", FORWARD);
	            break;
	 
	            case 2:
	            playr->changeAnimation("air_prep_down_right", FORWARD);
	            break;
	        }
	        break;
	 
	        case Player::STEP_GO:
	        playr->landing=false;
	        if((playr->yvelocity)<=(-speed))
	        {
	            playr->yvelocity+=speed;
	        }
	        else if(((playr->yvelocity)>0) && ((playr->yvelocity)<speed))
	        {
	            playr->yvelocity=speed;
	        }
	        switch(playr->playerdir)
	        {
	            case 1:
	            playr->xvelocity=-speed2;
	            playr->changeAnimation("air_attack_down_left", FORWARD);
	            break;
	 
	            case 2:
	            playr->xvelocity=speed;
	            playr->changeAnimation("air_attack_down_right", FORWARD);
	            break;
	        }
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
	            switch(playr->playerdir)
	            {
	                case 1:
	                playr->changeAnimation("air_land_down_left", FORWARD);
	                break;
	 
	                case 2:
	                playr->changeAnimation("air_land_down_right", FORWARD);
	                break;
	            }
	        }
	        else
	        {
	            playr->animFinish();
	            playr->xvelocity=0;
	        }
	        break;
	    }
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
	            playr->playerdir=2;
	        }
	        else if((playr->x)>(closePlayer->x))
	        {
	            playr->playerdir=1;
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
	            playr->playerdir=2;
	        }
	        else if((playr->x)>(closePlayer->x))
	        {
	            playr->playerdir=1;
	        }
	        double dist = PrimitiveActor::distance(playr->x, playr->y, closePlayer->x, closePlayer->y);
	        speedX=(float)(((closePlayer->x-playr->x)/dist)*speed);
	        speedY=(float)(((closePlayer->y-playr->y)/dist)*speed);
	    }
	    else
	    {
	        switch(playr->playerdir)
	        {
	            case 1:
	            speedX=-0.7f*speed;
	            speedY=0.7f*speed;
	            break;
	 
	            case 2:
	            speedX=0.7f*speed;
	            speedY=0.7f*speed;
	            break;
	        }
	    }
	    playr->xvelocity=speedX;
	    playr->yvelocity=speedY;
	    //playr->recoverTime=Global::worldTime+wait;
	 
	    switch(playr->playerdir)
	    {
	        case 1:
	        playr->changeAnimation("special_attack_left", FORWARD);
	        break;
	 
	        case 2:
	        playr->changeAnimation("special_attack_right", FORWARD);
	        break;
	    }
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

	void AttackTemplates::normalSideB(Player*playr, int aNo, double aP, float xDist)
	{
		playr->jumping = false;
		playr->hurt = 0;
	    switch(playr->playerdir)
	    {
	        case 1:
	        playr->changeAnimation("special_attack_side_left", FORWARD);
	        playr->x-=xDist;
	        break;
	 
	        case 2:
	        playr->changeAnimation("special_attack_side_right", FORWARD);
	        playr->x+=xDist;
	        break;
	    }
	    playr->attacksHolder=aNo;
        playr->attacksPriority=aP;
	}

	void AttackTemplates::dashSideB(Player*playr, int aNo, double aP, float speed)
	{
		playr->jumping = false;
		playr->hurt = 0;
	    switch(playr->playerdir)
	    {
	        case 1:
	        playr->changeAnimation("special_attack_side_left", FORWARD);
	        playr->xVel=-speed;
	        break;
	 
	        case 2:
	        playr->changeAnimation("special_attack_side_right", FORWARD);
	        playr->xVel=speed;
	        break;
	    }
	    playr->attacksHolder=aNo;
        playr->attacksPriority=aP;
	}

	void AttackTemplates::rollAttack(Player*playr, int aNo, double aP, float speed, int time)
	{
		playr->jumping = false;
		playr->hurt = 0;
	    switch(playr->playerdir)
	    {
	        case 1:
	        playr->changeAnimation("roll_left", FORWARD);
	        playr->xVel=-speed;
	        break;
	 
	        case 2:
	        playr->changeAnimation("roll_right", FORWARD);
	        playr->xVel=speed;
	        break;
	    }
	    playr->attacksHolder=aNo;
        playr->attacksPriority=aP;
	    playr->attackTime=(Global::worldTime+time);
	}

	void AttackTemplates::launchUpB(Player*playr, int aNo, double aP, float yVeloc, float yVeloc2)
	{
		playr->jumping = false;
		playr->hurt = 0;
	    switch(playr->playerdir)
	    {
	        case 1:
	        playr->changeAnimation("special_attack_up_left", FORWARD);
	        //playr->bUpWaitTime=Global::worldTime+wTime;
	        break;
	 
	        case 2:
	        playr->changeAnimation("special_attack_up_right", FORWARD);
	        //playr->bUpWaitTime=Global::worldTime+wTime;
	        break;
	    }
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
	    switch(playr->playerdir)
	    {
	        case 1:
	        playr->changeAnimation("special_attack_up_left", FORWARD);
	        //playr->bUpWaitTime=Global::worldTime+wTime;
	        break;
	 
	        case 2:
	        playr->changeAnimation("special_attack_up_right", FORWARD);
	        //playr->bUpWaitTime=Global::worldTime+wTime;
	        break;
	    }
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
	    switch(playr->playerdir)
	    {
	        case 1:
	        playr->changeAnimation("special_attack_up_left", FORWARD);
	        //playr->bUpWaitTime=Global::worldTime+wTime;
	        break;
	 
	        case 2:
	        playr->changeAnimation("special_attack_up_right", FORWARD);
	        //playr->bUpWaitTime=Global::worldTime+wTime;
	        break;
	    }
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
	    switch(playr->playerdir)
	    {
	        case 1:
	        playr->changeAnimation("special_attack_down_left", FORWARD);
	        break;
	 
	        case 2:
	        playr->changeAnimation("special_attack_down_right", FORWARD);
	        break;
	    }
	    playr->attacksHolder=aNo;
        playr->attacksPriority=aP;
	}

	void AttackTemplates::prepareDownB(Player*playr, int aNo, double aP)
	{
		playr->hurt = 0;
	    playr->up=false;
	    playr->jumping=false;
	    switch(playr->playerdir)
	    {
	        case 1:
	        playr->changeAnimation("special_prep_down_left", FORWARD);
	        break;
	 
	        case 2:
	        playr->changeAnimation("special_prep_down_right", FORWARD);
	        break;
	    }
	    playr->attacksHolder=aNo;
        playr->attacksPriority=aP;
	}

	void AttackTemplates::bounceDownB(Player*playr,int aNo,double aP,float speed)
	{
		playr->hurt = 0;
	    playr->up=false;
	    playr->jumping=false;
	    switch(playr->playerdir)
	    {
	        case 1:
	        playr->changeAnimation("special_attack_down_left", FORWARD);
	        break;
	 
	        case 2:
	        playr->changeAnimation("special_attack_down_right", FORWARD);
	        break;
	    }
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
			switch(playr->getPlayerDir())
			{
				case 1:
				playr->changeAnimation("smash_charge_left", FORWARD);
				break;
				
				case 2:
				playr->changeAnimation("smash_charge_right", FORWARD);
				break;
			}
			break;
			
			case Player::STEP_GO:
			playr->chargeSmash = 0;
			playr->attacksHolder=aNo;
	        playr->attacksPriority=aP;
			switch(smashType)
			{
				case 1:
				switch(playr->getPlayerDir())
				{
					case 1:
					playr->changeAnimation("smash_attack_left",FORWARD);
					break;
					
					case 2:
					playr->changeAnimation("smash_attack_right", FORWARD);
					break;
				}
				break;
				
				case 2:
				switch(playr->getPlayerDir())
				{
					case 1:
					playr->changeAnimation("smash_attack_up_left",FORWARD);
					break;
					
					case 2:
					playr->changeAnimation("smash_attack_up_right", FORWARD);
					break;
				}
				break;
				
				case 3:
				switch(playr->getPlayerDir())
				{
					case 1:
					playr->changeAnimation("smash_attack_down_left",FORWARD);
					break;
					
					case 2:
					playr->changeAnimation("smash_attack_down_right", FORWARD);
					break;
				}
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