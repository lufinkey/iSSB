
#include "Mario.h"
#include "../../Global.h"
#include "../../AttackTemplates.h"
#include "../../P2PDataManager.h"

namespace SmashBros
{
	void Mario::addProjectileInfo(byte type, int projID, float x, float y)
	{
		ProjectileInfo info;
		info.type = type;
		info.projID = projID;
		info.x = x;
		info.y = y;
		createdProjectiles.add(info);
	}
	
	Mario::Mario(float x1, float y1, byte playerNo, byte team) : Player(x1, y1, playerNo, team)
	{
		walkSpeed = 3;
		runSpeed = 4;
		fallWalk = 2;
		fallRun = 2;
		
		weight = 0.1;
		
		name = "Mario";
		
		setHitbox(-10, -9, 20, 28);
		setHitboxColor(Color::GREEN);
		//showHitboxWireframe(true);
		//setWireframeColor(Color.red);
		//showWireframe(true);
		
		setHangPoint(5, 20);
		
		Console::WriteLine((String)"finished creating player " + playerNo);
	}

	Mario::~Mario()
	{
		//
	}
	
	void Mario::setToDefaultValues()
	{
		charging_attack = 0;
	}
	
	void Mario::Load()
	{
		setFolderPath("Images/Game/Characters/Mario/");
		
		loadFile("Images/Game/Characters/Mario/fireball.png");
		loadFile("Images/Game/Characters/Mario/fludd_water.png");
		loadFile("Images/Game/Characters/Mario/finalsmash_fire.png");
		addTwoSidedAnimation("stand", "stand.png", 10, 9, 1);
		addTwoSidedAnimation("walk", "walk.png", 10, 4, 1);
		addTwoSidedAnimation("run", "run.png", 15, 8, 1);
		addTwoSidedAnimation("jump", "jump.png", 10, 6, 1);
		addTwoSidedAnimation("jump2", "jump2.png", 30, 20, 1);
		addTwoSidedAnimation("land", "land.png", 20, 3, 1);
		addTwoSidedAnimation("fall", "fall.png", 30, 2, 1);
		addTwoSidedAnimation("hang", "hang.png", 1, 1, 1);
		addTwoSidedAnimation("crouch", "crouch.png", 1, 1, 1);
		addTwoSidedAnimation("melee_weapon", "melee_weapon.png", 6, 3, 1);
		addTwoSidedAnimation("hurt_minor", "hurt_minor.png", 2, 1, 1);
		addTwoSidedAnimation("hurt_fly", "hurt_fly.png", 2, 1, 1);
		addTwoSidedAnimation("hurt_flip", "hurt_flip.png", 10, 4, 1);
		addTwoSidedAnimation("hurt_spin", "hurt_spin.png", 18, 9, 1);
		addSingleAnimation("hurt_spin_up", "hurt_spin_up.png", 18, 9, 1);
		addTwoSidedAnimation("dash_attack", "dash_attack.png", 12, 6, 1);
		addTwoSidedAnimation("standard_attack", "standard_attack.png", 24, 6, 1);
		addTwoSidedAnimation("standard_attack2", "standard_attack2.png", 26, 7, 1);
		addTwoSidedAnimation("standard_attack3", "standard_attack3.png", 18, 6, 1);
		addTwoSidedAnimation("standard_attack_side", "standard_attack_side.png", 16, 9, 1);
		addTwoSidedAnimation("standard_attack_up", "standard_attack_up.png", 18, 6, 1);
		addTwoSidedAnimation("standard_attack_down", "standard_attack_down.png", 25, 12, 1);
		addTwoSidedAnimation("air_attack", "air_attack.png", 8, 3, 1);
		addTwoSidedAnimation("air_attack_side", "air_attack_side.png", 12, 6, 1);
		addTwoSidedAnimation("air_attack_up", "air_attack_up.png", 45, 20, 1);
		addSingleAnimation("air_attack_down", "air_attack_down.png", 20, 14, 1);
		addTwoSidedAnimation("special_attack", "special_attack.png", 14, 4, 1);
		addTwoSidedAnimation("special_attack_side", "special_attack_side.png", 14, 5, 1);
		addTwoSidedAnimation("special_attack_up", "special_attack_up.png", 7, 4, 1);
		addTwoSidedAnimation("special_charge_down", "special_charge_down.png", 0, 1, 1);
		addTwoSidedAnimation("special_attack_down", "special_attack_down.png", 0, 1, 1);
		addTwoSidedAnimation("smash_charge", "smash_charge.png", 1, 1, 1);
		addTwoSidedAnimation("smash_attack", "smash_attack.png", 10, 4, 1);
		addTwoSidedAnimation("smash_attack_up", "smash_attack_up.png", 8, 4, 1);
		addTwoSidedAnimation("smash_attack_down", "smash_attack_down.png", 10, 4, 1);
		addTwoSidedAnimation("finalsmash_begin", "finalsmash_begin.png", 10, 13, 1);
		addTwoSidedAnimation("finalsmash_hold", "finalsmash_hold.gif", 0, 1, 1);
		addTwoSidedAnimation("finalsmash_end", "finalsmash_end.png", 15, 18, 1);
	}
	
	void Mario::LoadAttackTypes()
	{
		addAIAttackType(ATTACK_A,         ATTACKTYPE_MELEE, 6);
		addAIAttackType(ATTACK_SIDEA,     ATTACKTYPE_MELEE, 3);
		addAIAttackType(ATTACK_UPA,       ATTACKTYPE_UPMELEE, 1);
		addAIAttackType(ATTACK_DOWNA,     ATTACKTYPE_DOWNMELEE, 1);
		addAIAttackType(ATTACK_DOWNA,     ATTACKTYPE_MELEE, 1);
		addAIAttackType(ATTACK_B,         ATTACKTYPE_PROJECTILE, 1);
		addAIAttackType(ATTACK_SIDEB,     ATTACKTYPE_MELEE, 1);
		addAIAttackType(ATTACK_SIDEB,     ATTACKTYPE_DEFENSIVE, 1);
		addAIAttackType(ATTACK_SIDEB,     ATTACKTYPE_SIDEMOVE, 1);
		addAIAttackType(ATTACK_UPB,       ATTACKTYPE_STRONGMELEE, 1);
		addAIAttackType(ATTACK_UPB,       ATTACKTYPE_UPMOVE, 1);
		addAIAttackType(ATTACK_SIDESMASH, ATTACKTYPE_STRONGMELEE, 2, true);
		addAIAttackType(ATTACK_UPSMASH,   ATTACKTYPE_STRONGMELEE, 1, true);
		addAIAttackType(ATTACK_DOWNSMASH, ATTACKTYPE_STRONGMELEE, 1, true);
		addAIAttackType(ATTACK_FINALSMASH,ATTACKTYPE_PROJECTILE, 1);
	}
	
	void Mario::Unload()
	{
		Player::Unload();
	}
	
	void Mario::addP2PData(DataVoid&data)
	{
		int total = createdProjectiles.size();
		
		if(total>0)
		{
			P2PDataManager::setReliable();
			
			bool avail = true;
			data.add(&avail, sizeof(avail));
			
			int total = createdProjectiles.size();
			data.add(&total, sizeof(total));
			
			for(int i=0; i<createdProjectiles.size(); i++)
			{
				ProjectileInfo proj = createdProjectiles.get(i);
				
				data.add(&proj.type, sizeof(proj.type));
				data.add(&proj.projID, sizeof(proj.projID));
				data.add(&proj.x, sizeof(proj.x));
				data.add(&proj.y, sizeof(proj.y));
			}
			createdProjectiles.clear();
		}
		else
		{
			bool avail = false;
			data.add(&avail, sizeof(avail));
		}
	}
	
	void Mario::setP2PData(byte*&data)
	{
		bool avail = data[0];
		data += sizeof(bool);
		
		if(avail)
		{
			int total = DataVoid::toInt(data);
			data += sizeof(int);
			
			for(int i=0; i<total; i++)
			{
				byte type = data[0];
				data += sizeof(byte);
				
				int projID = DataVoid::toInt(data);
				data += sizeof(int);
				
				float x1 = DataVoid::toFloat(data);
				data += sizeof(float);
				float y1 = DataVoid::toFloat(data);
				data += sizeof(float);
				
				switch(type)
				{
					case 1:
					{
						Projectile::setNextID(projID);
						createProjectile(new Fireball(getPlayerNo(), x1, y1));
					}
					break;
					
					case 2:
					{
						Projectile::setNextID(projID);
						createProjectile(new FluddWater(getPlayerNo(), x1, y1));
					}
					break;
					
					case 3:
					{
						Projectile::setNextID(projID);
						createProjectile(new FinalSmashFire(getPlayerNo(), x1, y1));
					}
					break;
				}
			}
		}
	}
	
	void Mario::Update(long gameTime)
	{
		if(chargedDownAttack)
		{
			if(chargeDownTime <= Global::getWorldTime())
			{
				chargedDownAttack = false;
				chargeDownTime = 0;
			}
		}
		Player::Update(gameTime);
		updateGravity();
		updateFrame();
		
		updateMovement();
		
		updateHanging();
		updateHurt();
		updateDrop();
		
		updateAI();
	}
	
	void Mario::Draw(Graphics2D&g, long gameTime)
	{
		Player::Draw(g, gameTime);
	}
	
	void Mario::onAnimationFinish(const String&n)
	{
		if(n.equals("finalsmash_hold_left") || n.equals("finalsmash_hold_right")
		|| n.equals("special_charge_down_left") || n.equals("special_charge_down_right")
		|| n.equals("special_attack_down_left") || n.equals("special_attack_down_right"))
		{
			//
		}
		else if(n.equals("special_attack_up_left") || n.equals("special_attack_up_right"))
		{
			xvelocity=0;
			animFinish();
		}
		else if(n.equals("finalsmash_begin_left") || n.equals("finalsmash_begin_right"))
		{
			switch(playerdir)
			{
				case LEFT:
				{
					changeAnimation("finalsmash_hold_left",FORWARD);
					
					FinalSmashFire*fire = new FinalSmashFire(getPlayerNo(), x-60, y-40);
					createProjectile(fire);
					
					addProjectileInfo(3, fire->getID(), x-60, y-40);
				}
				break;
				
				case RIGHT:
				{
					changeAnimation("finalsmash_hold_right",FORWARD);
					
					FinalSmashFire*fire = new FinalSmashFire(getPlayerNo(), x+60, y-40);
					createProjectile(fire);
					
					addProjectileInfo(3, fire->getID(), x+60, y-40);
				}
				break;
			}
		}
		else if(n.equals("finalsmash_end_left") || n.equals("finalsmash_end_right"))
		{
			animFinish();
			AttackTemplates::finishFinalSmash(this);
		}
		else
		{
			Player::onAnimationFinish(n);
		}
	}
	
	void Mario::jump()
	{
		Player::jump(4.8f,5.0f);
	}
	
	void Mario::onPlayerHit(Player*collide, byte dir)
	{
		switch(dir)
		{
			case DIR_LEFT:
			{
				switch(attacksHolder)
			    {
			        case 0:
			        //A
			        if(hitAmount==0 && playerdir==LEFT)
			        {
				        causeDamage(collide,3);
				        collide->y-=3;
				        collide->x+=3;
				        x-=1;
				        causeHurt(collide, RIGHT, 1);
				        hitAmount++;
			        }
			        break;
			 
			        case 1:
			        //A 2
		        	if(hitAmount==0 && playerdir==LEFT)
			        {
				        causeDamage(collide,2);
				        collide->y-=3;
				        collide->x+=3;
				        x-=1;
				        causeHurt(collide, RIGHT, 1);
				        hitAmount++;
			        }
			        break;
			 
			        case 2:
			        //A 3
		        	if(hitAmount==0 && playerdir==LEFT)
			        {
				        causeDamage(collide,4);
				        causeHurtLaunch(collide,-1,2,2.5f, -1,2,3);
				        causeHurt(collide, RIGHT, 4);
				        hitAmount++;
			        }
			        break;
			 
			        case 11:
			        //B side
			        if(playerdir==LEFT)
			        {
				        switch(collide->getPlayerDir())
				        {
				            case LEFT:
				            collide->setPlayerDir(RIGHT);
				            break;
				 
				            case RIGHT:
				            collide->setPlayerDir(LEFT);
				            break;
				        }
				        collide->stand();
				        causeDamage(collide,8);
			        }
			        break;
			 
			        case 14:
			        //smash left
			        if(playerdir==LEFT)
			        {
			        	causeDamage(collide,smashPower);
			        	collide->x-=5;
			        	causeHurtLaunch(collide,-1,3,((float)smashPower/5), -1,3,((float)smashPower/4));
			        	causeHurt(collide, RIGHT, smashPower/3);
			        }
			        break;
			 
			        case 15:
			        //smash up left
			        if(playerdir==LEFT)
			        {
			        	causeDamage(collide,smashPower);
			        	causeHurtLaunch(collide,-1,4,((float)smashPower/5), -1,3,((float)smashPower/5));
			        	causeHurt(collide, RIGHT, smashPower/3);
			        }
			        break;
			 
			        case 16:
			        //smash down left
			        if(playerdir==LEFT)
			        {
			        	causeDamage(collide,smashPower);
			        	causeHurtLaunch(collide,-1,4,((float)smashPower/6), -1,3,((float)smashPower/5));
			        	causeHurt(collide, RIGHT, smashPower/3);
			        }
			        break;
			    }
			}
			break;
			
			case DIR_RIGHT:
			{
				switch(attacksHolder)
			    {
			        case 0:
			        //A
		        	if(hitAmount==0 && playerdir==RIGHT)
			        {
				        causeDamage(collide,3);
				        collide->y-=3;
				        collide->x-=3;
				        x+=1;
				        causeHurt(collide, LEFT, 1);
				        hitAmount++;
			        }
			        break;
			 
			        case 1:
			        //A 2
			        if(hitAmount==0 && playerdir==RIGHT)
			        {
				        causeDamage(collide,2);
				        collide->y-=3;
				        collide->x-=3;
				        x+=1;
				        causeHurt(collide, LEFT, 1);
				        hitAmount++;
			        }
			        break;
			 
			        case 2:
			        //A 3
			        if(hitAmount==0 && playerdir==RIGHT)
			        {
				        causeDamage(collide,4);
				        causeHurtLaunch(collide,1,2,2.5f, -1,2,3);
				        causeHurt(collide, LEFT, 4);
				        hitAmount++;
			        }
			        break;
			 
			        case 11:
			        //B side
			        if(playerdir==RIGHT)
			        {
			        	causeDamage(collide,8);
				        switch(collide->getPlayerDir())
				        {
				            case LEFT:
				            collide->setPlayerDir(RIGHT);
				            break;
				 
				            case RIGHT:
				            collide->setPlayerDir(LEFT);
				            break;
				        }
				        collide->stand();
				        
			        }
			        break;
			 
			        case 14:
			        //smash right
			        if(playerdir==RIGHT)
			        {
				        causeDamage(collide,smashPower);
				        collide->x+=5;
				        causeHurtLaunch(collide,1,3,((float)smashPower/5), -1,3,((float)smashPower/4));
				        causeHurt(collide, LEFT, smashPower/3);
			        }
			        break;
			 
			        case 15:
			        //smash up right
			        if(playerdir==RIGHT)
			        {
				        causeDamage(collide,smashPower);
				        causeHurtLaunch(collide,1,4,((float)smashPower/5), -1,2,((float)smashPower/5));
				        causeHurt(collide, LEFT, smashPower/3);
			        }
			        break;
			 
			        case 16:
			        //smash down right
			        if(playerdir==RIGHT)
			        {
				        causeDamage(collide,smashPower);
				        causeHurtLaunch(collide,1,4,((float)smashPower/6), -1,3,((float)smashPower/5));
				        causeHurt(collide, LEFT, smashPower/3);
			        }
			        break;
			    }
			}
			break;
			
			case DIR_UP:
			{
				switch(attacksHolder)
			    {
			        case 14:
			        //smash
			        causeDamage(collide,smashPower);
				    causeHurtLaunch(collide,0,0,0, -1,3,((float)smashPower/4));
				    causeHurt(collide, collide->getPlayerDir(), smashPower/3);
			        break;
			 
			        case 15:
			        //smash up
			        causeDamage(collide,smashPower);
				    causeHurtLaunch(collide,0,0,0, -1,4,((float)smashPower/4));
				    causeHurt(collide, collide->getPlayerDir(), smashPower/3);
			        break;
			 
			        case 16:
			        //smash down left
			        causeDamage(collide,smashPower);
			        causeHurtLaunch(collide,0,0,0, -1,4.5f,((float)smashPower/4));
			        causeHurt(collide, collide->getPlayerDir(), smashPower/3);
			        break;
			    }
			}
			break;
			
			case DIR_DOWN:
			{
				switch(attacksHolder)
			    {
			        case 5:
			        //A down left
			        causeDamage(collide,5);
			        if(collide->y<=y)
			        {
			        	switch(playerdir)
			        	{
			        		case LEFT:
			        		causeHurtLaunch(collide,-1,1,1, -1,2.3f,3.1f);
			        		causeHurt(collide, RIGHT, 5);
			        		break;
			        		
			        		case RIGHT:
			        		causeHurtLaunch(collide,1,1,1, -1,2.3f,3.1f);
			        		causeHurt(collide, LEFT, 5);
			        		break;
			        	}
			        }
			        else
			        {
			        	causeHurtLaunch(collide,0,0,0, 1,3,3);
			        	causeHurt(collide, collide->getPlayerDir(), 5);
			        }
			        break;
			        
			        case 9:
		            //A air down
		            collide->y-=5;
		            break;
		            
			        case 16:
			        //smash down left
			        causeDamage(collide,smashPower);
			        causeHurtLaunch(collide,0,0,0, 1,3.9f,((float)smashPower/4));
			        causeHurt(collide, collide->getPlayerDir(), smashPower/3);
			        break;
			    }
			}
			break;
		}
	}
	
	void Mario::onPlayerRectHit(Player*collide, byte dir)
	{
		if(attacksHolder==12)
		{
			switch(playerdir)
			{
				case LEFT:
		        switch(hitAmount)
		        {
		            case 0:
		            if(collide->x > x)
		            {
		            	return;
		            }
		            case 1:
		            case 2:
		            case 3:
		            case 4:
		            changeAnimation("special_attack_up_left", FORWARD);
		            causeDamage(collide,2);
		            collide->y=(y - ((height/2) + (collide->height/2) + 16));
		            collide->x=x;
		            collide->xvelocity=0;
		            collide->yvelocity=0;
		            hitAmount+=1;
		            yvelocity=-4;
		            causeHurt(collide, collide->getPlayerDir(), 0);
		            break;
		 
		            case 5:
		            changeAnimation("special_attack_up_left", FORWARD);
		            causeDamage(collide,2);
		            yvelocity=-2;
		            attacksHolder=-1;
		            hitAmount+=1;
		            collide->yvelocity=0;
		            causeHurtLaunch(collide,0,0,0, -1,2.4f,2);
		            causeHurt(collide, collide->getPlayerDir(), 3);
		            break;
		        }
		        break;
		 
		        case RIGHT:
		        switch(hitAmount)
		        {
		            case 0:
	            	if(collide->x < this->x)
		            {
		            	return;
		            }
		            case 1:
		            case 2:
		            case 3:
		            case 4:
		            changeAnimation("special_attack_up_right", FORWARD);
		            causeDamage(collide,2);
		            collide->y=(this->y - ((this->height/2) + (collide->height/2) + 16));
		            collide->x=x;
		            collide->xvelocity=0;
		            collide->yvelocity=0;
		            hitAmount+=1;
		            yvelocity=-4;
		            causeHurt(collide, collide->getPlayerDir(), 0);
		            break;
		 
		            case 5:
		            changeAnimation("special_attack_up_right", FORWARD);
		            causeDamage(collide,2);
		            yvelocity=-2;
		            attacksHolder=-1;
		            hitAmount+=1;
		            collide->yvelocity=0;
		            causeHurtLaunch(collide,0,0,0, -1,3,4);
		            causeHurt(collide, collide->getPlayerDir(), 3);
		            break;
		        }
		        break;
			}
	    }
	}
	
	boolean Mario::onPlayerDeflectDamage(Player*collide, int damage)
	{
		return false;
	}
	
	void Mario::onFinishCharge()
	{
		destroyCharge();
		chargeDownTime = Global::getWorldTime() + 100;
		chargedDownAttack = true;
		charging_attack = 0;
		animFinish();
	}
	
	void Mario::doChargingAttack(byte button)
	{
		destroyCharge();
		chargingAttack = false;
		chargedDownAttack = false;
		charging_attack = 0;
		animFinish();
	}
	
	void Mario::attackA()
	{
		addAttackInfo(DIR_LEFT, 6, LEFT, 10, 5, -1,1,1.5f, -1,1.1f,2.1f);
		addAttackInfo(DIR_RIGHT,6,RIGHT, 10, 5,  1,1,1.5f, -1,1.1f,2.1f);
		addAttackInfo(DIR_DOWN, 6, LEFT, 10, 4, 0,0,0, 1,3,2);
		addAttackInfo(DIR_DOWN, 6,RIGHT, 10, 4, 0,0,0, 1,3,2);
		
	    if(!checkItemUse())
	    {
	        if(isOnGround())
	        {
	        	AttackTemplates::combo3A(this, 6, 0,1, 1,1, 2,1.8);
	        }
	        else
	        {
	            if(!bUp)
	            {
	                AttackTemplates::normalAirA(this, 6,1.2);
	            }
	        }
	    }
	}
	
	void Mario::attackSideA()
	{
		addAttackInfo(DIR_LEFT, 3, LEFT, 8, 5, -1,2,2.6f, -1,1.5f,2.5f);
		addAttackInfo(DIR_RIGHT,3,RIGHT, 8, 5,  1,2,2.6f, -1,1.5f,2.5f);
		addAttackInfo(DIR_DOWN, 3, LEFT, 8, 5, -1,2,2.6f, -1,1.5f,2.5f);
		addAttackInfo(DIR_DOWN, 3,RIGHT, 8, 5,  1,2,2.6f, -1,1.5f,2.5f);
		addAttackInfo(DIR_LEFT, 7, LEFT, 10, 6, -1,2,2.9f, -1,0.5f,0);
		addAttackInfo(DIR_RIGHT,7,RIGHT, 10, 6,  1,2,2.9f, -1,0.5f,0);
		addAttackInfo(DIR_DOWN, 7, LEFT, 10, 4, 0,0,0, 1,6,6);
		addAttackInfo(DIR_DOWN, 7,RIGHT, 10, 4, 0,0,0, 1,6,6);
		
	    if(((getMoveLeft()==2) || (getMoveRight()==2)) && (isOnGround()))
	    {
	        AttackTemplates::normalDashA(this, 3,2.3, 4.3f);
	    }
	    else
	    {
	        if(!checkItemUseSide())
	        {
	            if(isOnGround())
	            {
	            	AttackTemplates::normalSideA(this, 3,2.1);
	            }
	            else
	            {
	                if(!bUp)
	                {
	                	AttackTemplates::normalAirSideA(this, 7,2.8);
	                }
	            }
	        }
	    }
	}
	
	void Mario::attackUpA()
	{
		addAttackInfo(DIR_LEFT, 8, LEFT, 10, 6, -1,2,2.7f, -1,1,2.2f);
		addAttackInfo(DIR_RIGHT,8,RIGHT, 10, 6,  1,2,2.7f, -1,1,2.2f);
		addAttackInfo(DIR_UP, 8, LEFT, 10, 6, 0,0,0, -1,2,3.6f);
		addAttackInfo(DIR_UP, 8,RIGHT, 10, 6, 0,0,0, -1,2,3.6f);
		addAttackInfo(DIR_DOWN, 8, LEFT, 10, 6, 0,0,0, 1,4,5);
		addAttackInfo(DIR_DOWN, 8,RIGHT, 10, 6, 0,0,0, 1,4,5);
		addAttackInfo(DIR_UP, 4, LEFT, 7, 4, 0,0,0, -1,2,3);
		addAttackInfo(DIR_UP, 4,RIGHT, 7, 4, 0,0,0, -1,2,3);
		addAttackInfo(DIR_LEFT, 4, LEFT, 7, 4, -1,1,2, -1,1,1.6f);
		addAttackInfo(DIR_RIGHT, 4,RIGHT, 7, 4, 1,1,2, -1,1,1.6f);
		
	    if(isOnGround())
	    {
	    	AttackTemplates::normalUpA(this, 4, 0.95);
	    }
	    else
	    {
	        if(!bUp)
	        {
	        	AttackTemplates::normalAirUpA(this, 8,2.349);
	        }
	    }
	}
	
	void Mario::attackDownA()
	{
		addAttackInfo(DIR_LEFT, 5, LEFT, 5, 5, -1,2,1.8f, -1,2.5f,2);
		addAttackInfo(DIR_RIGHT,5,RIGHT, 5, 5,  1,2,1.8f, -1,2.5f,2);
		addAttackInfo(DIR_UP,   5, LEFT, 5, 5,  0,0,0, -1,2.3f,3.1f);
		addAttackInfo(DIR_UP,   5,RIGHT, 5, 5,  0,0,0, -1,2.3f,3.1f);
		addAttackInfo(DIR_LEFT, 9, LEFT, 7, 6, -1,3,3.1f, -1,1,3);
		addAttackInfo(DIR_LEFT, 9,RIGHT, 7, 6, -1,3,3.1f, -1,1,3);
		addAttackInfo(DIR_RIGHT,9,LEFT, 7, 6,  1,3,3.1f, -1,1,3);
		addAttackInfo(DIR_RIGHT,9,RIGHT, 7, 6,  1,3,3.1f, -1,1,3);
		addAttackInfo(DIR_UP, 9, LEFT, 7, 6,  0,0,0, -1,3,2);
		addAttackInfo(DIR_UP, 9,RIGHT, 7, 6,  0,0,0, -1,3,2);
		addAttackInfo(DIR_DOWN, 9, LEFT, 7, 3, 0,0,0, 1,4,5);
		addAttackInfo(DIR_DOWN, 9,RIGHT, 7, 3, 0,0,0, 1,4,5);
		
		if(isOnGround())
		{
			AttackTemplates::normalDownA(this, 5,2.15);
		}
		else
		{
	        if(!bUp)
	        {
	        	AttackTemplates::singleAirDownA(this, 9,2.65);
	        }
	    }
	}
	
	void Mario::attackB()
	{
	    if(!bUp)
	    {
	        if((canFinalSmash())&&(isOnGround()))
	        {
	            attackFinalSmash();
	        }
	        else
	        {
				Fireball*fireball = new Fireball(this->getPlayerNo(),x,y);
	        	AttackTemplates::singleProjectile(this, 10,0, fireball);
				
				addProjectileInfo(1, fireball->getID(), x, y);
				
	            switch(playerdir)
	            {
	                case 1:
	                changeAnimation("special_attack_left",FORWARD);
	                break;
	 
	                case 2:
	                changeAnimation("special_attack_right",FORWARD);
	                break;
	            }
	        }
	    }
	}
	
	void Mario::attackSideB()
	{
	    if(!bUp)
	    {
	        AttackTemplates::normalSideB(this, 11,1.83f, 2.99f);
	        if(!isOnGround())
	        {
	        	switch(playerdir)
	        	{
	        		case LEFT:
	        		xvelocity-=2;
	        		break;
	        		
	        		case RIGHT:
	        		xvelocity+=2;
	        		break;
	        	}
	        }
	    }
	}
	
	void Mario::attackUpB()
	{
	    if(!bUp)
	    {
	        AttackTemplates::rehitUpB(this, 12, 3.1f, 5.5f, 5.5f);
	        if(isOnGround())
	        {
	        	switch(playerdir)
		        {
		        	case LEFT:
		        	xvelocity=-0.8f;
		        	break;
		        	
		        	case RIGHT:
		        	xvelocity=0.8f;
		        	break;
		        }
	        }
	        else
	        {
	        	switch(playerdir)
		        {
		        	case LEFT:
		        	xvelocity=-2.1f;
		        	break;
		        	
		        	case RIGHT:
		        	xvelocity=2.1f;
		        	break;
		        }
	        }
	    }
	}
	
	void Mario::attackDownB()
	{
		if(!bUp)
		{
			if(charging_attack==0)
			{
				if(chargedDownAttack)
				{
					switch(playerdir)
					{
						case LEFT:
						{
							FluddWater*fludd = new FluddWater(getPlayerNo(),this->x-66,this->y-1);
							AttackTemplates::singleProjectile(this, 13, 0, fludd);
							
							addProjectileInfo(2, fludd->getID(), this->x-66, this->y-1);
							
							changeAnimation("special_attack_down_left", FORWARD);
						}
						break;
						
						case RIGHT:
						{
							FluddWater*fludd = new FluddWater(getPlayerNo(),this->x+66,this->y-1);
							AttackTemplates::singleProjectile(this, 13, 0, fludd);
							
							addProjectileInfo(2, fludd->getID(), this->x+66, this->y-1);
							
							changeAnimation("special_attack_down_right", FORWARD);
						}
						break;
					}
					chargedDownAttack = false;
				}
				else
				{
					AttackTemplates::chargeB(this, 0, 100, 10);
					switch(playerdir)
					{
						case LEFT:
						changeAnimation("special_charge_down_left",FORWARD);
						break;
						
						case RIGHT:
						changeAnimation("special_charge_down_right",FORWARD);
						break;
					}
					charging_attack = 1;
				}
			}
		}
	}
	
	void Mario::attackSideSmash(byte type)
	{
		if(!checkItemUseSmash(type) && !bUp)
		{
			if(isOnGround())
			{
				AttackTemplates::normalSmash(this, 14, 3.28, type, 1, 15, 11, 20);
			}
			else
			{
				attackSideA();
			}
		}
	}
	
	void Mario::attackUpSmash(byte type)
	{
		if(!bUp)
		{
			if(isOnGround())
			{
				AttackTemplates::normalSmash(this, 15, 3.26, type, 2, 15, 10, 20);
			}
			else
			{
				attackUpA();
			}
		}
	}
	
	void Mario::attackDownSmash(byte type)
	{
		if(!bUp)
		{
			if(isOnGround())
			{
				AttackTemplates::normalSmash(this, 16, 3.27, type, 3, 15, 10, 20);
			}
			else
			{
				attackDownA();
			}
		}
	}
	
	void Mario::attackFinalSmash()
	{
        addAttackInfo(DIR_LEFT, 17, LEFT, 30, 9, -1,7,4.5f, -1,6,5);
        addAttackInfo(DIR_RIGHT,17,RIGHT, 30, 9,  1,7,4.5f, -1,6,5);
        addAttackInfo(DIR_UP,   17, LEFT, 30, 9, 0,0,0, -1,5,6);
        addAttackInfo(DIR_UP,   17,RIGHT, 30, 9, 0,0,0, -1,5,6);
        addAttackInfo(DIR_DOWN, 17, LEFT, 30, 9, 0,0,0,  1,5,6);
        addAttackInfo(DIR_DOWN, 17,RIGHT, 30, 9, 0,0,0,  1,5,6);
        
	    if(isOnGround())
	    {
	    	AttackTemplates::finalSmash(this, 17);
	        switch(playerdir)
	        {
	            case 1:
	            changeAnimation("finalsmash_begin_left", FORWARD);
	            break;
	 
	            case 2:
	            changeAnimation("finalsmash_begin_right", FORWARD);
	            break;
	        }
	    }
	    else
	    {
	        attackB();
	    }
	}
	
	Mario::Fireball::Fireball(byte playerNo, float x1, float y1) : Projectile(playerNo,x1,y1)
	{
		xspeed = 3.1f;
		yspeed = 2;

		Animation*anim;
		anim = new Animation("left", 8, 4, 1);
		anim->addFrame("Images/Game/Characters/Mario/fireball.png");
		addAnimation(anim);
		
		anim = new Animation("right", 8, 4, 1);
		anim->addFrame("Images/Game/Characters/Mario/fireball.png");
		anim->mirror(true);
		addAnimation(anim);
		
		switch(itemdir)
		{
			case LEFT:
			xvelocity=-xspeed;
			changeAnimation("left",FORWARD);
			break;
				
			case RIGHT:
			xvelocity=xspeed;
			changeAnimation("right",FORWARD);
			break;
		}
		liveTime = Global::getWorldTime() + 15;
	}

	Mario::Fireball::~Fireball()
	{
		//
	}
	
	void Mario::Fireball::Update(long gameTime)
	{
		Projectile::Update(gameTime);
		yvelocity += 0.2f;
		if(liveTime <= Global::getWorldTime())
		{
			this->destroy();
		}
	}
	
	void Mario::Fireball::onPlayerHit(Player*collide, byte dir)
	{
		if(isHittable(collide,dir))
		{
			if(collide->getAttacksPriority()==5)
			{
			    if(collide->getPlayerDir()==1)
			    {
			        xvelocity=-xvelocity;
			        yvelocity=-yvelocity;
			    }
			    else
			    {
			        destroy();
			        causeDamage(collide,5);
			        collide->y-=3;
			        switch(itemdir)
			        {
			            case LEFT:
			            causeHurtLaunch(collide,-1,1,3, -1,1,3);
			            causeHurt(collide, RIGHT, 2);
			            break;
			 
			            case RIGHT:
			            causeHurtLaunch(collide, 1,1,3, -1,1,3);
			            causeHurt(collide, LEFT, 2);
			            break;
			        }
			    }
			}
				
			else if(collide->getAttacksPriority()==6)
			{
			    xvelocity=-xvelocity;
			    yvelocity=-yvelocity;
			}
				
			else if(collide->getAttacksPriority()==7)
			{
			    destroy();
			}
				
			else
			{
			    destroy();
			    causeDamage(collide,5);
			    collide->y-=3;
			    switch(itemdir)
			    {
			        case LEFT:
			        causeHurtLaunch(collide, -1,1,3, -1,1,3);
			        causeHurt(collide, RIGHT, 2);
			        break;
			 
			        case RIGHT:
			        causeHurtLaunch(collide, 1,1,3, -1,1,3);
			        causeHurt(collide, LEFT, 2);
			        break;
			    }
			}
		}
	}
	
	void Mario::Fireball::whilePlatformColliding(Platform*collide, byte dir)
	{
		switch(dir)
		{
			case DIR_UP:
			yvelocity=-yspeed;
			break;
				
			case DIR_DOWN:
			yvelocity=yspeed;
			break;
				
			case DIR_LEFT:
			xvelocity=-xspeed;
			break;
				
			case DIR_RIGHT:
			xvelocity=xspeed;
			break;
		}
	}
	
	Mario::FluddWater::FluddWater(byte playerNo, float x1, float y1) : Projectile(playerNo, x1, y1)
	{
		Animation*anim;
			
		anim = new Animation("left",10,10,1);
		anim->addFrame("Images/Game/Characters/Mario/fludd_water.png");
		addAnimation(anim);
			
		anim = new Animation("right",10,10,1);
		anim->addFrame("Images/Game/Characters/Mario/fludd_water.png");
		anim->mirror(true);
		addAnimation(anim);
			
		switch(itemdir)
		{
			case LEFT:
			changeAnimation("left",FORWARD);
			break;
				
			case RIGHT:
			changeAnimation("right",FORWARD);
			break;
		}
	}
	
	Mario::FluddWater::~FluddWater()
	{
		//
	}

	void Mario::FluddWater::Update(long gameTime)
	{
		Projectile::Update(gameTime);
		Player*playr = Global::getPlayerActor(this->getPlayerNo());
		if(!playr->isAlive() && !playr->isHurt())
		{
			destroy();
		}
	}
	
	void Mario::FluddWater::whilePlayerHitting(Player*collide, byte dir)
	{
		if(collide->x < Global::getPlayerActor(getPlayerNo())->x)
		{
			collide->x -= 2;
		}
		else
		{
			collide->x += 2;
		}
	}
		
	void Mario::FluddWater::onAnimationFinish(const String&aName)
	{
		destroy();
		Mario*playr = (Mario*)Global::getPlayerActor(getPlayerNo());
		playr->animFinish();
	}
	
	Mario::FinalSmashFire::FinalSmashFire(byte playerNo, float x1, float y1) : Projectile(playerNo,x1,y1)
	{
		Animation*anim;
		
		anim = new Animation("left", 12, 5, 2);
		anim->addFrame("Images/Game/Characters/Mario/finalsmash_fire.png");
		addAnimation(anim);
		
		anim = new Animation("right", 12, 5, 2);
		anim->addFrame("Images/Game/Characters/Mario/finalsmash_fire.png");
		anim->mirror(true);
		addAnimation(anim);
		
		switch(itemdir)
		{
			case LEFT:
			changeAnimation("left",FORWARD);
			break;
				
			case RIGHT:
			changeAnimation("right",FORWARD);
			break;
		}
	}

	Mario::FinalSmashFire::~FinalSmashFire()
	{
		//
	}
		
	void Mario::FinalSmashFire::onPlayerHit(Player*collide, byte dir)
	{
		if(isHittable(collide,dir))
		{
			switch(dir)
			{
				case DIR_UP:
				causeDamage(collide,30);
				causeHurtLaunch(collide, 0,0,0, -1,6,7);
				causeHurt(collide, collide->getPlayerDir(), 9);
				break;
					
				case DIR_DOWN:
				causeDamage(collide,30);
				causeHurtLaunch(collide, 0,0,0, 1,6,7);
				causeHurt(collide, collide->getPlayerDir(), 9);
				break;
					
				case DIR_LEFT:
				causeDamage(collide,30);
				causeHurtLaunch(collide, -1,7,6.5f, -1,6,7);
				causeHurt(collide, RIGHT, 9);
				break;
					
				case DIR_RIGHT:
				causeDamage(collide,30);
				causeHurtLaunch(collide, 1,7,6.5f, -1,6,7);
				causeHurt(collide, LEFT, 9);
				break;
			}
		}
	}
		
	void Mario::FinalSmashFire::onAnimationFinish(const String&n)
	{
		Player*playr = Global::getPlayerActor(this->getPlayerNo());
		switch(playr->getPlayerDir())
		{
			case LEFT:
			playr->changeAnimation("finalsmash_end_left", FORWARD);
			break;
				
			case RIGHT:
			playr->changeAnimation("finalsmash_end_right", FORWARD);
			break;
		}
		destroy();
	}
}