
#include "Sonic.h"
#include "../../Global.h"
#include "../../AttackTemplates.h"
#include "../../P2PDataManager.h"
#include <cmath>

namespace SmashBros
{
	void Sonic::addProjectileInfo(byte type, int projID, float x, float y)
	{
		ProjectileInfo info;
		info.type = type;
		info.projID = projID;
		info.x = x;
		info.y = y;
		createdProjectiles.add(info);
	}
	
	Sonic::Sonic(float x1, float y1, byte playerNo, byte team) : Player(x1, y1, playerNo, team)
	{
		turning = false;
		winding = false;
		finalSmashing = false;
		chargeAttack = 0;
		
		xprevious = 0;
		yprevious = 0;
		
		rollSpeed = 6;
		rocketSpeed = 0;
		sonicSpeedRun = 12;
		
		walkSpeed = 4.2f;
		runSpeed = 10;
		fallWalk = 2.2f;
		fallRun = 2.3f;
		walkAmount = 1;
		runAmount = 1;
		
		weight = 0.1;
		
		name = "Sonic";
		
		setScale(0.95f);
		
		setHitbox(-11, -12, 22, 34);
		setHitboxColor(Color::GREEN);
		//showHitboxWireframe(true);
		//setWireframeColor(Color.red);
		//showWireframe(true);
		
		setHangPoint(6, 5);
		
		Console::WriteLine((String)"finished creating player " + playerNo);
	}

	Sonic::~Sonic()
	{
		//
	}
	
	void Sonic::addP2PData(DataVoid&data)
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
	
	void Sonic::setP2PData(byte*&data)
	{
		bool avail = DataVoid::toBool(data);
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
						createProjectile(new Spring(getPlayerNo(), x1, y1));
					}
					break;
					
					case 2:
					{
						Projectile::setNextID(projID);
						createProjectile(new Emeralds(getPlayerNo(), x1, y1));
					}
					break;
				}
			}
		}
	}
	
	void Sonic::Load()
	{
		setFolderPath("Images/Game/Characters/Sonic/");
		
		loadFile("Images/Game/Characters/Sonic/spring_normal.png");
		loadFile("Images/Game/Characters/Sonic/spring_bounce.png");
		loadFile("Images/Game/Characters/Sonic/finalsmash_emeralds.png");
		addTwoSidedAnimation("stand", "stand.png", 7, 7, 1);
		addTwoSidedAnimation("walk", "walk.png", 12, 8, 1);
		addTwoSidedAnimation("run", "run.png", 16, 4, 1);
		addTwoSidedAnimation("jump", "jump.png", 8, 7, 1);
		addTwoSidedAnimation("jump2", "jump2.png", 8, 7, 1);
		addTwoSidedAnimation("land", "land.png", 12, 4, 1);
		addTwoSidedAnimation("skid", "skid.png", 12, 2, 1);
		addTwoSidedAnimation("fall", "fall.png", 30, 1, 1);
		addTwoSidedAnimation("hang", "hang.png", 1, 1, 1);
		addTwoSidedAnimation("crouch", "crouch.png", 1, 1, 1);
		addTwoSidedAnimation("grab", "grab.png", 13, 5, 1);
		addTwoSidedAnimation("grabbed", "grabbed.png", 30, 1, 1);
		addTwoSidedAnimation("hold", "hold.png", 30, 1, 1);
		addTwoSidedAnimation("release", "release.png", 12, 3, 1);
		addTwoSidedAnimation("toss", "toss.png", 30, 10, 1);
		addTwoSidedAnimation("toss_up", "toss_up.png", 12, 3, 1);
		addTwoSidedAnimation("toss_down", "toss_down.png", 12, 3, 1);
		addTwoSidedAnimation("grab_attack", "grab_attack.png", 14, 4, 1);
		addTwoSidedAnimation("grab_attack_swing", "grab_attack_swing.png", 18, 15, 1);
		addTwoSidedAnimation("melee_weapon", "melee_weapon.png", 12, 4, 1);
		addTwoSidedAnimation("melee_weapon_up", "melee_weapon_up.png", 18, 6, 1);
		addTwoSidedAnimation("melee_weapon_down", "melee_weapon_down.png", 9, 3, 1);
		addTwoSidedAnimation("hurt_minor", "hurt_minor.png", 2, 1, 1);
		addTwoSidedAnimation("hurt_fly", "hurt_fly.png", 2, 1, 1);
		addTwoSidedAnimation("hurt_flip", "hurt_flip.png", 18, 7, 1);
		addTwoSidedAnimation("hurt_spin", "hurt_spin.png", 18, 6, 1);
		addSingleAnimation("hurt_spin_up", "hurt_spin_up.png", 18, 6, 1);
		addTwoSidedAnimation("dash_attack", "dash_attack.png", 16, 8, 1);
		addTwoSidedAnimation("standard_attack", "standard_attack.png", 16, 5, 1);
		addTwoSidedAnimation("standard_attack2", "standard_attack2.png", 16, 5, 1);
		addTwoSidedAnimation("standard_attack3", "standard_attack3.png", 16, 8, 1);
		addTwoSidedAnimation("standard_attack_side", "standard_attack_side.png", 28, 11, 1);
		addTwoSidedAnimation("standard_attack_up", "standard_attack_up.png", 20, 8, 1);
		addTwoSidedAnimation("standard_attack_down", "standard_attack_down.png", 14, 7, 1);
		addTwoSidedAnimation("air_attack", "air_attack.png", 12, 6, 1);
		addTwoSidedAnimation("air_attack_side", "air_attack_side.png", 20, 9, 1);
		addTwoSidedAnimation("air_attack_up", "air_attack_up.png", 24, 12, 1);
		addTwoSidedAnimation("air_prep_down", "air_prep_down.png", 12, 5, 1);
		addTwoSidedAnimation("air_attack_down", "air_attack_down.png", 9, 9, 1);
		addTwoSidedAnimation("air_land_down", "air_land_down.png", 6, 4, 1);
		addTwoSidedAnimation("special_prep", "special_prep.png", 10, 5, 1);
		addTwoSidedAnimation("special_attack", "special_attack.png", 16, 7, 1);
		addTwoSidedAnimation("special_finish", "special_finish.png", 12, 4, 1);
		addTwoSidedAnimation("special_attack_up", "special_attack_up.png", 14, 8, 1);
		addTwoSidedAnimation("special_prep_side", "special_prep_side.png", 16, 4, 1);
		addTwoSidedAnimation("roll", "roll.png", 12, 4, 1);
		addTwoSidedAnimation("special_charge_down", "special_charge_down.png", 16, 4, 1);
		addTwoSidedAnimation("special_attack_down", "special_attack_down.png", 10, 5, 1);
		addTwoSidedAnimation("special_land_down", "special_land_down.png", 40, 15, 1);
		addTwoSidedAnimation("smash_charge", "smash_charge.png", 1, 1, 1);
		addTwoSidedAnimation("smash_wind", "smash_wind.png", 16, 6, 1);
		addTwoSidedAnimation("smash_attack", "smash_attack.png", 16, 7, 1);
		addTwoSidedAnimation("smash_attack_up", "smash_attack_up.png", 30, 13, 1);
		addTwoSidedAnimation("smash_attack_down", "smash_attack_down.png", 40, 23, 1);
		addTwoSidedAnimation("finalsmash_transform", "finalsmash_transform.png", 10, 8, 1);
		addTwoSidedAnimation("finalsmash_stand", "finalsmash_stand.png", 8, 6, 1);
		addTwoSidedAnimation("finalsmash_run", "finalsmash_run.png", 6, 4, 1);
		addTwoSidedAnimation("finalsmash_turn", "finalsmash_turn.png", 6, 3, 1);
		addTwoSidedAnimation("finalsmash_finish", "finalsmash_finish.png", 8, 6, 1);
		
		ArrayList<int> seq;
		seq.add(2); seq.add(1); seq.add(0);

		Animation*anim = new Animation("finalsmash_stop_left", 6, 3, 1, seq);
		anim->addFrame("Images/Game/Characters/Sonic/finalsmash_turn.png");
		addAnimation(anim);
		anim = new Animation("finalsmash_stop_right", 6, 3, 1, seq);
		anim->addFrame("Images/Game/Characters/Sonic/finalsmash_turn.png");
		anim->mirror(true);
		addAnimation(anim);
	}

	void Sonic::LoadAttackTypes()
	{
		addAIAttackType(ATTACK_A,         ATTACKTYPE_MELEE, 10);
		addAIAttackType(ATTACK_SIDEA,     ATTACKTYPE_MELEE, 7);
		addAIAttackType(ATTACK_UPA,       ATTACKTYPE_MELEE, 4);
		addAIAttackType(ATTACK_UPA,       ATTACKTYPE_UPMELEE, 1);
		addAIAttackType(ATTACK_DOWNA,     ATTACKTYPE_MELEE, 3);
		addAIAttackType(ATTACK_DOWNA,     ATTACKTYPE_DOWNMELEE, 1);
		addAIAttackType(ATTACK_DOWNA,     ATTACKTYPE_DOWNMOVE, 4);
		addAIAttackType(ATTACK_B,         ATTACKTYPE_MELEE, 2);
		addAIAttackType(ATTACK_B,         ATTACKTYPE_UPMELEE, 2);
		addAIAttackType(ATTACK_B,         ATTACKTYPE_DOWNMELEE, 2);
		addAIAttackType(ATTACK_SIDEB,     ATTACKTYPE_SIDEMOVE, 3);
		addAIAttackType(ATTACK_SIDEB,     ATTACKTYPE_MELEE, 1);
		addAIAttackType(ATTACK_UPB,       ATTACKTYPE_UPMOVE, 3);
		addAIAttackType(ATTACK_DOWNB,     ATTACKTYPE_DOWNMOVE, 1, true);
		addAIAttackType(ATTACK_SIDESMASH, ATTACKTYPE_STRONGMELEE, 2, true);
		addAIAttackType(ATTACK_UPSMASH,   ATTACKTYPE_STRONGMELEE, 1, true);
		addAIAttackType(ATTACK_DOWNSMASH, ATTACKTYPE_STRONGMELEE, 1, true);
	}
	
	void Sonic::setToDefaultValues()
	{
		turning = false;
		winding = false;
		chargeAttack = 0;
	}
	
	void Sonic::onDestroy()
	{
		finalSmashing = false;
	}
	
	boolean Sonic::checkIfAble()
	{
		if(turning || winding)
		{
			return false;
		}
		return true;
	}
	
	void Sonic::Update(long gameTime)
	{
		Player::Update(gameTime);
		
		checkAttacks();
		if(!finalSmashing)
		{
			updateGravity();
			updateFrame();
		}
		
		setHitbox(-10, -12, 22, 31);
		
		if(attacksHolder==12)
		{
		    if(Global::getWorldTime()>=attackTime)
		    {
		        float oldxVel=(float)xVel;
		        animFinish();
		        changeTwoSidedAnimation("special_finish", FORWARD);
		        if(isOnGround())
		        {
		            landing=true;
		            turning=true;
		            xVel=oldxVel;
		            upKey=false;
		        }
		    }
		    else
		    {
		        if(upKey)
		        {
		            if(isOnGround())
		            {
		                yvelocity=-8;
		            }
		            else if(doubleJump>0)
		            {
		                yvelocity=-7;
		                doubleJump--;
		            }
		            upKey=false;
		        }
		        if(moveLeft>0)
		        {
		            playerdir=LEFT;
		        }
		        if(moveRight>0)
		        {
		            playerdir=RIGHT;
		        }
				
				if(xVel>(rollSpeed*getPlayerDirMult()))
				{
					turning=true;
					xVel += 0.5f * getPlayerDirMult();
					attacksHolder=12;
					moveLeft=0;
					moveRight=0;
					changeTwoSidedAnimation("roll", NO_CHANGE);
				}
				else
				{
					turning=false;
					xVel = rollSpeed * getPlayerDirMult();
					attacksHolder=12;
					moveLeft=0;
					moveRight=0;
					changeTwoSidedAnimation("roll", NO_CHANGE);
				}
		    }
		}
		
		if(attacksHolder==14)
		{
		    if(Global::getWorldTime()>=attackTime)
		    {
		        animFinish();
		        yvelocity=-3;
		        changeTwoSidedAnimation("special_finish", FORWARD);
		        chargeAttack=0;
		    }
		    else
		    {
		        if(upKey)
		        {
		            animFinish();
		            chargeAttack=0;
		            attackTime=0;
		            upKey=false;
		        }
		        if(moveLeft>0)
		        {
		            playerdir=LEFT;
		        }
		        if(moveRight>0)
		        {
		            playerdir=RIGHT;
		        }
				
				if(xVel > (rocketSpeed*getPlayerDirMult()))
				{
					turning=true;
					xVel += 1 * getPlayerDirMult();
					attacksHolder=14;
					moveLeft=0;
					moveRight=0;
					changeTwoSidedAnimation("roll", NO_CHANGE);
				}
				else
				{
					turning=false;
					xVel = rocketSpeed * getPlayerDirMult();
					attacksHolder=14;
					moveLeft=0;
					moveRight=0;
					changeTwoSidedAnimation("roll", NO_CHANGE);
				}
		    }
		}
		
		if(landing && turning && attacksPriority!=7)
		{
			xVel -= 0.2f * getPlayerDirMult();
			if((xVel*getPlayerDirMult()) <= 0)
			{
				animFinish();
			}
		}
		
		updateMovement();
		
		updateHanging();
		updateHurt();
		updateDrop();
		updateAI();
		
		if(finalSmashing)
		{
		    attacksPriority=7;
		}
		if(attacksPriority==7)
		{
		    if(Global::getWorldTime()>=attackTime)
		    {
		        if(turning)
		        {
		            changeTwoSidedAnimation("finalsmash_finish", NO_CHANGE);
		            x=xprevious;
		            y=yprevious;
		            xvelocity=0;
					yvelocity=0;
					setHanging(false);
		            landing=true;
		            turning=true;
		            setCantDo();
		            attacksHolder=-1;
		            chargeSmash=0;
		            chargeAttack=0;
		        }
		        else
		        {
					changeTwoSidedAnimation("finalsmash_finish", FORWARD);
		            Emeralds*emeralds = new Emeralds(getPlayerNo(), x, y);
		            emeralds->changeAnimation("disappear", FORWARD);
		            createProjectile(emeralds);
					
					addProjectileInfo(2, emeralds->getID(), x, y);
					
		            turning=true;
		            landing=true;
		            setCantDo();
		            attacksHolder=-1;
		            chargeSmash=0;
		            chargeAttack=0;
		        }
		    }
		    else
		    {
				setHanging(false);
				setJumping(false);
		        x=xprevious;
		        y=yprevious;
				xvelocity = 0;
				yvelocity = 0;
		        landing=false;
		        attacksHolder=-1;
		        chargeSmash=0;
		        chargeAttack=0;
		        if(turning)
		        {
		            changeTwoSidedAnimation("finalsmash_transform", NO_CHANGE);
		        }
		        else
		        {
					bool moving = false;
					if(moveLeft>0)
					{
						moving = true;
						setPlayerDir(LEFT);
					}
					else if(moveRight>0)
					{
						moving = true;
						setPlayerDir(RIGHT);
					}
					if(moving)
					{
						String animName = getAnimName();
						String suffix = getPlayerDirSuffix();
						if(animName.equals("finalsmash_stand_left") || animName.equals("finalsmash_stand_right"))
						{
							changeTwoSidedAnimation("finalsmash_turn", FORWARD);
						}
						else if(animName.equals((String)"finalsmash_turn" + suffix))
						{
							int animpos = this->getCurrentFrame();
							if(animpos<=0)
							{
								x += sonicSpeedRun*0.25f * getPlayerDirMult();
							}
							else if(animpos<=1)
							{
								x += sonicSpeedRun*0.5f * getPlayerDirMult();
							}
							else
							{
								x += sonicSpeedRun*0.75f * getPlayerDirMult();
							}
						}
						else
						{
							x += sonicSpeedRun * getPlayerDirMult();
							changeTwoSidedAnimation("finalsmash_run", NO_CHANGE);
						}
					}
					else
					{
						String animName = getAnimName();
						String suffix = getPlayerDirSuffix();
						
						if(animName.equals((String)"finalsmash_run"+suffix))
						{
							changeTwoSidedAnimation("finalsmash_stop", FORWARD);
						}
						else if(animName.equals((String)"finalsmash_stop"+suffix))
						{
							int animpos = getCurrentFrame();
							if(animpos<=0)
							{
								x += sonicSpeedRun*0.75f * getPlayerDirMult();
							}
							else if(animpos<=1)
							{
								x += sonicSpeedRun*0.5f * getPlayerDirMult();
							}
							else
							{
								x += sonicSpeedRun*0.25f * getPlayerDirMult();
							}
						}
						else
						{
							changeTwoSidedAnimation("finalsmash_stand", NO_CHANGE);
						}
					}
					if(upKey)
					{
						y-=sonicSpeedRun;
					}
					else if(down)
					{
						y+=sonicSpeedRun;
					}
		        }
		    }
		    
		    RectF borders = Global::currentStage->getViewBorders();
			if(x < (borders.left + Global::currentStage->x))
			{
				x = (float)borders.left + (float)Global::currentStage->x + (float)width/2;
			}
			else if(x > (borders.right + Global::currentStage->x))
			{
				x = (float)borders.right + (float)Global::currentStage->x - (float)width/2;
			}
			
			if(y < (borders.top + Global::currentStage->y))
			{
				y = (float)borders.top + (float)Global::currentStage->y + (float)height/2;
			}
			else if(y > (borders.bottom + Global::currentStage->y))
			{
				y = (float)borders.bottom + (float)Global::currentStage->y - (float)height/2;
			}
		}
		
		xprevious = x;
		yprevious = y;
	}
	
	void Sonic::Draw(Graphics2D&g, long gameTime)
	{
		Player::Draw(g, gameTime);
	}
	
	void Sonic::onAnimationFinish(const String&n)
	{
		if(n.equals("roll_left") || n.equals("roll_right")
		|| n.equals("special_charge_down_left") || n.equals("special_charge_down_right"))
		{
			//
		}
		else if(n.equals("finalsmash_stand_left") || n.equals("finalsmash_stand_right")
			|| n.equals("finalsmash_run_left") || n.equals("finalsmash_run_right"))
		{
			//
		}
		else if(n.equals("finalsmash_transform_left") || n.equals("finalsmash_transform_right"))
		{
			turning=false;
			landing=false;
			attacksPriority=7;
			changeTwoSidedAnimation("finalsmash_stand", FORWARD);
		}
		else if(n.equals("finalsmash_stop_left") || n.equals("finalsmash_stop_right"))
		{
			changeTwoSidedAnimation("finalsmash_stand",FORWARD);
		}
		else if(n.equals("finalsmash_turn_left") || n.equals("finalsmash_turn_right"))
		{
			changeTwoSidedAnimation("finalsmash_run",FORWARD);
		}
		else if(n.equals("finalsmash_finish_left") || n.equals("finalsmash_finish_right"))
		{
			AttackTemplates::finishFinalSmash(this);
			animFinish();
			attackTime=0;
			turning=false;
			finalSmashing=false;
		}
		else if(n.equals("smash_wind_left") || n.equals("smash_wind_right"))
		{
			winding = false;
			AttackTemplates::normalSmash(this,15,3.11,STEP_GO,1,15,14,20);
		}
		else if(n.equals("air_prep_down_left")|| n.equals("air_prep_down_right"))
		{
			if(isOnGround())
			{
				AttackTemplates::dropAirDownA(this, STEP_FINISH, 10, 3.545, 7, 3);
			}
			else
			{
				AttackTemplates::dropAirDownA(this, STEP_GO, 10, 3.545, 7, 3);
			}
		}
		else if(n.equals("air_attack_down_left")|| n.equals("air_attack_down_right"))
		{
			AttackTemplates::dropAirDownA(this, STEP_FINISH, 10, 3.545, 7, 3);
		}
		else if(n.equals("air_land_down_left")|| n.equals("air_land_down_right"))
		{
			animFinish();
			y+=5;
		}
		else if(n.equals("special_prep_left") || n.equals("special_prep_right"))
		{
			xVel=0;
			yVel=0;
			landing=false;
			AttackTemplates::homingB(this, 11, 3.88, 8.5f);
		}
		else if(n.equals("special_attack_left") || n.equals("special_attack_right"))
		{
			animFinish();
			changeTwoSidedAnimation("special_finish", FORWARD);
			xvelocity = -1 * getPlayerDirMult();
			yvelocity=-1;
		}
		else if(n.equals("special_prep_side_left") || n.equals("special_prep_side_right"))
		{
			animFinish();
	        AttackTemplates::rollAttack(this, 12, 3.09, rollSpeed, 16);
	        xvelocity=0;
	        yvelocity=-5;
		}
		else
		{
			Player::onAnimationFinish(n);
		}
	}
	
	void Sonic::onGroundCollide()
	{
		Player::onGroundCollide();
		if(attacksHolder==10)
		{
			AttackTemplates::dropAirDownA(this, STEP_FINISH, 10, 3.445, 7, 2);
		    landing=true;
		}
		else if(attacksHolder==11)
		{
		    animFinish();
			changeTwoSidedAnimation("special_finish", FORWARD);
		    landing = true;
		}
		else if((attacksHolder==13)&&(yvelocity>=0))
		{
		    yvelocity=-6;
		    changeTwoSidedAnimation("special_land_down", FORWARD);
		}
	}
	
	void Sonic::jump()
	{
		Player::jump((float)6,(float)6);
	}
	
	void Sonic::onPlayerHit(Player*collide, byte dir)
	{
		switch(dir)
		{
			case DIR_LEFT:
			case DIR_RIGHT:
			if(compareDirPlayerDir(dir, getPlayerDir())==CMPDIRPDIR_EQUAL)
			{
				switch(attacksHolder)
				{
					case 0:
					//A
					if(hitAmount==0)
					{
						causeDamage(collide,2);
						collide->y -= 3;
						collide->x -= 1 * getPlayerDirMult();
						causeHurt(collide, getOppPlayerDir(), 100);
						hitAmount++;
					}
					break;
					
					case 1:
					//A
					if(hitAmount==0)
					{
						causeDamage(collide,2);
						collide->y -= 3;
						collide->x -= 1 * getPlayerDirMult();
						causeHurt(collide, getOppPlayerDir(), 100);
						hitAmount++;
					}
					break;
					
					case 2:
					//A 3
					if(hitAmount==0)
					{
						causeDamage(collide,3);
						causeHurtLaunch(collide, (int)getPlayerDirMult(),2.2f,2.9f, -1,2,1.9f);
						causeHurt(collide, getOppPlayerDir(), 400);
						hitAmount++;
					}
					break;
					
					case 8:
					//A Air Side
					switch(hitAmount)
					{
						case 0:
						case 1:
						causeDamage(collide,4);
						collide->x += 3 * getPlayerDirMult();
						collide->y -= 4;
						x += 15 * getPlayerDirMult();
						if(yvelocity>-2)
						{
							yvelocity=-2;
						}
						hitAmount+=1;
						causeHurt(collide, getOppPlayerDir(), 300);
						break;
						
						case 2:
						causeDamage(collide,5);
						causeHurtLaunch(collide, (int)getPlayerDirMult(),3.2f,5.34f, -1,2.1f,2.9f);
						causeHurt(collide, getOppPlayerDir(), 600);
						hitAmount+=1;
						break;
					}
					break;
					
					case 15:
					//Smash Side
					causeDamage(collide,smashPower);
					causeHurtLaunch(collide, (int)getPlayerDirMult(),3.23f,((float)smashPower/4), -1,1.4f,((float)smashPower/4));
					causeHurt(collide, getOppPlayerDir(), 300);
					break;
				}
			}
			switch(attacksHolder)
			{
				case 11:
				//B
				{
					double dist;
					int multX=1;
					int multY=1;
					float distX;
					float distY;
					causeDamage(collide,8);
					dist=distance(x,y,collide->x,collide->y);
					distX=(float)(((collide->x - x)/dist)*4);
					distY=(float)(((collide->y - y)/dist)*4);
					if(distX<0)
					{
						multX=-1;
					}
					if(distY<0)
					{
						multY=-1;
					}
					causeHurtLaunch(collide, multX,std::abs(distX),3.04f, multY,std::abs(distY),3.04f);
					causeHurt(collide, RIGHT, 500);
					yvelocity /= std::abs(yvelocity);
					yvelocity *= -3;
					xvelocity /= std::abs(xvelocity);
					xvelocity *= -3;
					animFinish();
					changeTwoSidedAnimation("special_finish", FORWARD);
					bUp=false;
					landing = true;
				}
				break;
				
				case 12:
				//B side
				{
					double dist;
					int multX=1;
					int multY=1;
					float distX;
					float distY;
					causeDamage(collide,15);
					dist=distance(x,y,collide->x,collide->y);
					distX=(float)(((collide->x - x)/dist)*1.2);
					distY=(float)(((collide->y - y)/dist)*1.2);   
					if(distX<0)
					{
						multX=-1;
					}
					if(distY<0)
					{
						multY=-1;
					}
					if(collide->isOnGround())
					{
						if(compareDirPlayerDir(dir, getPlayerDir())==CMPDIRPDIR_EQUAL)
						{
							causeHurtLaunch(collide,multX,std::abs(distX),3.89f, -1,2.82f,3.89f);
						}
						else
						{
							causeHurtLaunch(collide,multX,std::abs(distX),3.89f, -1,1.12f,3.89f);
						}
					}
					else
					{
						causeHurtLaunch(collide,multX,std::abs(distX),3.89f, multY,std::abs(distY),3.89f);
					}
					causeHurt(collide, getOppPlayerDir(), 500);
				}
				break;
				
				case 13:
				//B Air Down
				{
					double dist;
					int multX=1;
					int multY=1;
					float distX;
					float distY;
					causeDamage(collide,13);
					dist=distance(x,y,collide->x,collide->y);
					distX=(float)(((collide->x - x)/dist)*3.72);
					distY=(float)(((collide->y - y)/dist)*3.72);
					if(distX<0)
					{
						multX=-1;
					}
					if(distY<0)
					{
						multY=-1;
					}
					if(collide->isOnGround())
					{
						causeHurtLaunch(collide,multX,std::abs(distX),5.98f, -1,3.72f,5.78f);
					}
					else
					{
						causeHurtLaunch(collide,multX,std::abs(distX),5.98f, multY,std::abs(distY),5.98f);
					}
					causeHurt(collide, getOppPlayerDir(), 600);
				}
				break;
				
				case 14:
				//B Down
				if(!turning)
				{
					double dist;
					int multX=1;
					float distX;
					causeDamage(collide,smashPower);
					dist=distance(x,y,collide->x,collide->y);
					distX=(float)(((collide->x - x)/dist)*1.72);
					if(distX<0)
					{
						multX=-1;
					}
					causeHurtLaunch(collide, multX,std::abs(distX),((float)smashPower/4), -1,3.4f,((float)smashPower/4));
					causeHurt(collide, getOppPlayerDir(), 600);
				}
				break;
				
				case 17:
				//Smash Down
				causeDamage(collide,smashPower);
				causeHurtLaunch(collide, (int)getPlayerDirMult(),2.43f,((float)smashPower/4), -1,5.64f,((float)smashPower/4));
				causeHurt(collide, getOppPlayerDir(), 300);
				break;
			}
			if(attacksPriority==7)
			{
				//final smash
				double dist;
				int multX=1;
				int multY=1;
				float distX;
				float distY;
				causeDamage(collide,20);
				dist=distance(x,y,collide->x,collide->y);
				distX=(float)(((collide->x - x)/dist)*6);
				distY=(float)(((collide->y - y)/dist)*6);
				if(distX<0)
				{
					multX=-1;
				}
				if(distY<0)
				{
					multY=-1;
				}
				collide->y-=5;
				causeHurtLaunch(collide, multX,std::abs(distX),6, multY,std::abs(distY),6);
				causeHurt(collide, getOppPlayerDir(), 400);
			}
			break;
			
			case DIR_UP:
			switch(attacksHolder)
			{
				case 8:
				//A Air Side
				switch(hitAmount)
				{
					case 0:
					case 1:
					causeDamage(collide,4);
					collide->y-=4;
					if(yvelocity>-2)
					{
						yvelocity=-2;
					}
					hitAmount+=1;
					causeHurt(collide, collide->getPlayerDir(), 300);
					break;
					
					case 2:
					causeDamage(collide,5);
					causeHurtLaunch(collide, (int)getPlayerDirMult(),1.2f,5.34f, -1,3.1f,2.9f);
					causeHurt(collide, getOppPlayerDir(), 600);
					hitAmount+=1;
					break;
				}
				break;
				
				case 11:
				//B
				{
					double dist;
					int multX=1;
					int multY=1;
					float distX;
					float distY;
					causeDamage(collide,8);
					dist=distance(x,y,collide->x,collide->y);
					distX=(float)(((collide->x - x)/dist)*4);
					distY=(float)(((collide->y - y)/dist)*4);
					if(distX<0)
					{
						multX=-1;
					}
					if(distY<0)
					{
						multY=-1;
					}
					causeHurtLaunch(collide, multX,std::abs(distX),3.04f, multY,std::abs(distY),3.04f);
					if(collide->x<x)
					{
						causeHurt(collide, RIGHT, 500);
					}
					else if(collide->x>x)
					{
						causeHurt(collide, LEFT, 500);
					}
					else
					{
						causeHurt(collide, collide->getPlayerDir(), 500);
					}
					yvelocity/=std::abs(yvelocity);
					yvelocity*=-3;
					xvelocity/=std::abs(xvelocity);
					xvelocity*=-3;
					animFinish();
					changeTwoSidedAnimation("special_finish", FORWARD);
					bUp=false;
					landing = true;
				}
				break;
				
				case 12:
				//B Side
				{
					double dist;
					int multX=1;
					int multY=1;
					float distX;
					float distY;
					causeDamage(collide,15);
					dist=distance(x,y,collide->x,collide->y);
					distX=(float)(((collide->x - x)/dist)*1.2);
					distY=(float)(((collide->y - y)/dist)*1.2);
					if(distX<0)
					{
						multX=-1;
					}
					if(distY<0)
					{
						multY=-1;
					}
					if(collide->isOnGround())
					{
						if(getRelPlayerDir(collide)==getPlayerDir())
						{
							causeHurtLaunch(collide, multX,std::abs(distX),3.89f, -1,2.82f,3.89f);
						}
						else
						{
							causeHurtLaunch(collide, multX,std::abs(distX),3.89f, -1,1.12f,3.89f);
						}
					}
					else
					{
						causeHurtLaunch(collide,multX,std::abs(distX),3.89f, multY,std::abs(distY),3.89f);
					}
					if(collide->x<x)
					{
						causeHurt(collide, RIGHT, 500);
					}
					else if(collide->x>x)
					{
						causeHurt(collide, LEFT, 500);
					}
					else
					{
						causeHurt(collide, collide->getPlayerDir(), 500);
					}
				}
				break;
				
				case 14:
				//B Down
				{
					double dist;
					int multX=1;
					float distX;
					causeDamage(collide,smashPower);
					dist=distance(x,y,collide->x,collide->y);
					distX=(float)(((collide->x - x)/dist)*1.72);
					if(distX<0)
					{
						multX=-1;
					}
					causeHurtLaunch(collide, multX,std::abs(distX),((float)smashPower/4), -1,3.4f,((float)smashPower/4));
					if(collide->x<x)
					{
						causeHurt(collide, RIGHT, 600);
					}
					else if(collide->x>x)
					{
						causeHurt(collide, LEFT, 600);
					}
					else
					{
						causeHurt(collide, collide->getPlayerDir(), 600);
					}
				}
				break;
				
				case 17:
				//Smash Down
				causeDamage(collide,smashPower);
				causeHurtLaunch(collide, (int)getPlayerDirMult(),0,0, -1,5.36f,((float)smashPower/4));
				causeHurt(collide, getOppPlayerDir(), 700);
				break;
			}
			if(attacksPriority==7)
			{
				//final smash
				double dist;
				int multY=1;
				float distY;
				causeDamage(collide,20);
				dist=distance(x,y,collide->x,collide->y);
				distY=(float)(((collide->y - y)/dist)*6);
				if(distY<0)
				{
					multY=-1;
				}
				collide->y-=5;
				causeHurtLaunch(collide, (int)getPlayerDirMult(),0,0, multY,std::abs(distY),6);
				causeHurt(collide, getOppPlayerDir(), 400);
			}
			break;
			
			case DIR_DOWN:
			switch(attacksHolder)
			{
				case 8:
				//A Air Side
				switch(hitAmount)
				{
					case 0:
					case 1:
					causeDamage(collide,4);
					collide->y-=4;
					if(yvelocity>-2)
					{
						yvelocity=-2;
					}
					hitAmount+=1;
					causeHurt(collide, collide->getPlayerDir(), 300);
					break;
					
					case 2:
					causeDamage(collide,5);
					causeHurtLaunch(collide, (int)getPlayerDirMult(),1.2f,5.34f, 1,3.1f,2.9f);
					causeHurt(collide, getOppPlayerDir(), 600);
					hitAmount+=1;
					break;
				}
				break;
				
				case 11:
				//B
				{
					double dist;
					int multX=1;
					int multY=1;
					float distX;
					float distY;
					causeDamage(collide,8);
					dist=distance(x,y,collide->x,collide->y);
					distX=(float)(((collide->x - x)/dist)*4);
					distY=(float)(((collide->y - y)/dist)*4);
					if(distX<0)
					{
						multX=-1;
					}
					if(distY<0)
					{
						multY=-1;
					}
					causeHurtLaunch(collide, multX,std::abs(distX),3.04f, multY,std::abs(distY),3.04f);
					if(collide->x<x)
					{
						causeHurt(collide, RIGHT, 500);
					}
					else if(collide->x>x)
					{
						causeHurt(collide, LEFT, 500);
					}
					else
					{
						causeHurt(collide, collide->getPlayerDir(), 500);
					}
					yvelocity/=std::abs(yvelocity);
					yvelocity*=-3;
					xvelocity/=std::abs(xvelocity);
					xvelocity*=-3;
					animFinish();
					changeTwoSidedAnimation("special_finish", FORWARD);
					bUp=false;
					landing = true;
				}
				break;
				
				case 12:
				//B Side
				{
					double dist;
					int multX=1;
					int multY=1;
					float distX;
					float distY;
					causeDamage(collide,15);
					dist=distance(x,y,collide->x,collide->y);
					distX=(float)(((collide->x - x)/dist)*1.2);
					distY=(float)(((collide->y - y)/dist)*1.2);
					if(distX<0)
					{
						multX=-1;
					}
					if(distY<0)
					{
						multY=-1;
					}
					if(collide->isOnGround())
					{
						if(compareDirPlayerDir(dir, getPlayerDir())==CMPDIRPDIR_EQUAL)
						{
							causeHurtLaunch(collide, multX,std::abs(distX),3.89f, 1,2.82f,3.89f);
						}
						else
						{
							causeHurtLaunch(collide, multX,std::abs(distX),3.89f, 1,1.12f,3.89f);
						}
					}
					else
					{
						causeHurtLaunch(collide, multX,std::abs(distX),3.89f, multY,std::abs(distY),3.89f);
					}
					if(collide->x<x)
					{
						causeHurt(collide, RIGHT, 500);
					}
					else if(collide->x>x)
					{
						causeHurt(collide, LEFT, 500);
					}
					else
					{
						causeHurt(collide, collide->getPlayerDir(), 500);
					}
				}
				break;
				
				case 13:
				//B Air Down
				{
					double dist;
					int multX=1;
					int multY=1;
					float distX;
					float distY;
					causeDamage(collide,13);
					dist=distance(x,y,collide->x,collide->y);
					distX=(float)(((collide->x - x)/dist)*3.72);
					distY=(float)(((collide->y - y)/dist)*3.72);
					if(distX<0)
					{
						multX=-1;
					}
					if(distY<0)
					{
						multY=-1;
					}
					if(collide->isOnGround())
					{
						causeHurtLaunch(collide, multX,std::abs(distX),5.98f, 1,3.72f,5.78f);
					}
					else
					{
						causeHurtLaunch(collide, multX,std::abs(distX),5.98f, multY,std::abs(distY),5.98f);
					}
					if(collide->x<x)
					{
						causeHurt(collide, RIGHT, 600);
					}
					else if(collide->x>x)
					{
						causeHurt(collide, LEFT, 600);
					}
					else
					{
						causeHurt(collide, collide->getPlayerDir(), 600);
					}
				}
				break;
				
				case 17:
				//Smash Down
				causeDamage(collide,smashPower);
				causeHurtLaunch(collide, (int)getPlayerDirMult(),0,0, 1,5.36f,((float)smashPower/4));
				causeHurt(collide, getOppPlayerDir(), 700);
				break;
			}
			if(attacksPriority==7)
			{
				//final smash
				double dist;
				int multY=1;
				float distY;
				causeDamage(collide,20);
				dist=distance(x,y,collide->x,collide->y);
				distY=(float)(((collide->y - y)/dist)*6);
				if(distY<0)
				{
					multY=-1;
				}
				collide->y-=5;
				causeHurtLaunch(collide, (int)getPlayerDirMult(),0,0, multY,std::abs(distY),6);
				causeHurt(collide, getOppPlayerDir(), 400);
			}
			break;
		}
	}
	
	void Sonic::onPlayerRectHit(Player*collide, byte dir)
	{
		switch(dir)
		{
			case DIR_LEFT:
			case DIR_RIGHT:
			if(attacksHolder==16)
			{
				//Smash Up
				switch(hitAmount)
				{
					case 0:
					case 1:
					case 2:
					causeDamage(collide,(int)(smashPower/3.5));
					collide->y -= collide->height;
					collide->yvelocity = 1;
					collide->x = x + (10*getPlayerDirMult());
					causeHurt(collide, getOppPlayerDir(), 300);
					hitAmount+=1;
					break;
					
					case 3:
					causeDamage(collide,(int)(smashPower/3.5));
					causeHurtLaunch(collide, (int)getPlayerDirMult(),3.43f,((float)smashPower/4), -1,2.64f,((float)smashPower/4));
					causeHurt(collide, getOppPlayerDir(), 700);
					hitAmount+=1;
					break;
				}
			}
			break;
			
			case DIR_UP:
			if(attacksHolder==16)
			{
				//Smash Up
				switch(hitAmount)
				{
					case 0:
					case 1:
					case 2:
					causeDamage(collide,(int)(smashPower/3.5));
					collide->y-=15;
					causeHurt(collide, collide->getPlayerDir(), 300);
					hitAmount+=1;
					break;
					
					case 3:
					causeDamage(collide,(int)(smashPower/3.5));
					causeHurtLaunch(collide, (int)getPlayerDirMult(),0,0, -1,5.26f,((float)smashPower/4));
					causeHurt(collide, collide->getPlayerDir(), 700);
					hitAmount+=1;
					break;
				}
			}
			break;
		}
	}
	
	void Sonic::onFinishCharge()
	{
		//
	}
	
	void Sonic::doChargingAttack(byte button)
	{
		if(chargeAttack==1)
        {
            destroyCharge();
            rocketSpeed = (float)smashPower;
            AttackTemplates::rollAttack(this, 14, 2.895, rocketSpeed, 5000);
            chargeAttack = 0;
        }
	}
	
	void Sonic::attackA()
	{
		addAttackInfo(DIR_UP, 3, LEFT, 3, 400, -1,1.2f,2.9f, -1,3,1.9f);
		addAttackInfo(DIR_UP, 3,RIGHT, 3, 400,  1,1.2f,2.9f, -1,3,1.9f);
		addAttackInfo(DIR_LEFT, 7, LEFT, 11, 500, -1,2.64f,5.7f, -1,1.4f,3);
		addAttackInfo(DIR_LEFT, 7,RIGHT, 11, 500, -1,2.3f,5.3f, -1,1.05f,2.9f);
		addAttackInfo(DIR_RIGHT,7, LEFT, 11, 500,  1,2.3f,5.3f, -1,1.05f,2.9f);
		addAttackInfo(DIR_RIGHT,7,RIGHT, 11, 500,  1,2.64f,5.7f, -1,1.4f,3);
		addAttackInfo(DIR_UP, 7, LEFT, 11, 600, -1,0.4f,2.2f, -1,3.21f,5.77f);
		addAttackInfo(DIR_UP, 7,RIGHT, 11, 600,  1,0.4f,2.2f, -1,3.21f,5.77f);
		addAttackInfo(DIR_DOWN, 7, LEFT, 11, 500, -1,2.3f,5.3f, 1,2.05f,2.6f);
		addAttackInfo(DIR_DOWN, 7,RIGHT, 11, 500,  1,2.3f,5.3f, 1,2.05f,2.6f);
		
	    if(attacksPriority!=7 && !checkItemUse())
	    {
	        if(isOnGround())
	        {
	        	AttackTemplates::combo3A(this, 500, 0,1.3, 1,1.45, 2,2.19);
	            x += 5 * getPlayerDirMult();
	        }
	        else
	        {
	            AttackTemplates::normalAirA(this, 7,2.95);
	        }
	    }
	}
	
	void Sonic::attackSideA()
	{
		addAttackInfo(DIR_LEFT, 3, LEFT, 11, 500, -1,2.1f,3.4f, -1,2.1f,3.4f);
		addAttackInfo(DIR_RIGHT,3,RIGHT, 11, 500,  1,2.1f,3.4f, -1,2.1f,3.4f);
		addAttackInfo(DIR_LEFT, 4, LEFT, 6, 600, -1,1.1f,2.8f, -1,3,5.8f);
		addAttackInfo(DIR_RIGHT,4,RIGHT, 6, 600,  1,1.1f,2.8f, -1,3,5.8f);
		addAttackInfo(DIR_UP, 3, LEFT, 11, 500, -1,1.6f,3.4f, -1,3.34f,3.4f);
		addAttackInfo(DIR_UP, 3,RIGHT, 11, 500,  1,1.6f,3.4f, -1,3.34f,3.4f);
		addAttackInfo(DIR_UP, 4, LEFT, 6, 600, -1,1.1f,1.8f, -1,3.5f,5.8f);
		addAttackInfo(DIR_UP, 4,RIGHT, 6, 600,  1,1.1f,1.8f, -1,3.5f,5.8f);
		addAttackInfo(DIR_DOWN, 4, LEFT, 6, 600, -1,1.56f,4, 1,2.2f,3.8f);
		addAttackInfo(DIR_DOWN, 4,RIGHT, 6, 600,  1,1.56f,4, 1,2.2f,3.8f);
		
		if(attacksPriority!=7)
		{
		    if(((getMoveLeft()==2) || (getMoveRight()==2)) && (isOnGround()))
		    {
		        AttackTemplates::normalDashA(this, 4,3.875, 8);
		    }
		    else
		    {
		        if(!checkItemUseSide())
		        {
		            if(isOnGround())
		            {
		                AttackTemplates::normalSideA(this, 3,2.79);
		            }
		            else
		            {
		            	AttackTemplates::rehitAirSideA(this, 8,3.12);
		            }
		        }
		    }
		}
	}
	
	void Sonic::attackUpA()
	{
		addAttackInfo(DIR_LEFT, 5, LEFT, 10, 600, -1,2,4.1f, -1,3,4.9f);
		addAttackInfo(DIR_LEFT, 5,RIGHT, 10, 600, -1,3.1f,4.3f, -1,2.2f,3.8f);
		addAttackInfo(DIR_RIGHT,5, LEFT, 10, 600,  1,3.1f,4.3f, -1,2.2f,3.8f);
		addAttackInfo(DIR_RIGHT,5,RIGHT, 10, 600,  1,2,4.1f, -1,3,4.9f);
		addAttackInfo(DIR_LEFT, 9, LEFT, 9, 400, -1,1,1.2f, -1,3,3.3f);
		addAttackInfo(DIR_RIGHT,9,RIGHT, 9, 400,  1,1,1.2f, -1,3,3.3f);
		addAttackInfo(DIR_UP, 5, LEFT, 10, 600, -1,0.4f,1.1f, -1,4.87f,6.03f);
		addAttackInfo(DIR_UP, 5,RIGHT, 10, 600,  1,0.4f,1.1f, -1,4.87f,6.03f);
		addAttackInfo(DIR_UP, 9, LEFT, 9, 400, -1,0.2f,1.2f, -1,4.23f,5.3f);
		addAttackInfo(DIR_UP, 9,RIGHT, 9, 400,  1,0.2f,1.2f, -1,4.23f,5.3f);
		
		if(attacksPriority!=7 && !checkItemUseUp())
		{
		    if(isOnGround())
		    {
		        AttackTemplates::normalUpA(this, 5,2.74);
		    }
		    else
		    {
		    	AttackTemplates::normalAirUpA(this, 9,2.53);
		    }
		}
	}
	
	void Sonic::attackDownA()
	{
		addAttackInfo(DIR_LEFT, 6, LEFT, 6, 600, -1,2.1f,5.4f, -1,3.12f,6);
		addAttackInfo(DIR_LEFT, 6,RIGHT, 6, 600, -1,1.95f,5.4f, -1,3.03f,6);
		addAttackInfo(DIR_RIGHT,6, LEFT, 6, 600,  1,1.95f,5.4f, -1,3.03f,6);
		addAttackInfo(DIR_RIGHT,6,RIGHT, 6, 600,  1,2.1f,5.4f, -1,3.12f,6);
		addAttackInfo(DIR_LEFT, 10, LEFT, 8, 600, -1,1,1.3f, -1,4.2f,5.3f);
		addAttackInfo(DIR_LEFT, 10,RIGHT, 8, 600, -1,1,1.3f, -1,4.2f,5.3f);
		addAttackInfo(DIR_RIGHT,10, LEFT, 8, 600,  1,1,1.3f, -1,4.2f,5.3f);
		addAttackInfo(DIR_RIGHT,10,RIGHT, 8, 600,  1,1,1.3f, -1,4.2f,5.3f);
		addAttackInfo(DIR_UP, 6, LEFT, 6, 600, -1,2.4f,5.1f, -1,4.92f,6.13f);
		addAttackInfo(DIR_UP, 6,RIGHT, 6, 600,  1,2.4f,5.1f, -1,4.92f,6.13f);
		addAttackInfo(DIR_UP, 10, LEFT, 8, 600, -1,0.3f,1.3f, -1,4.6f,5.3f);
		addAttackInfo(DIR_UP, 10,RIGHT, 8, 600,  1,0.3f,1.3f, -1,4.6f,5.3f);
		addAttackInfo(DIR_DOWN, 6, LEFT, 6, 600, -1,1.25f,5.4f, 1,3.2f,3);
		addAttackInfo(DIR_DOWN, 6,RIGHT, 6, 600,  1,1.25f,5.4f, 1,3.2f,3);
		addAttackInfo(DIR_DOWN, 10, LEFT, 8, 600, -1,0.3f,1.3f, -1,4.6f,5.3f);
		addAttackInfo(DIR_DOWN, 10,RIGHT, 8, 600,  1,0.3f,1.3f, -1,4.6f,5.3f);
		
		if(attacksPriority!=7 && !checkItemUseDown())
		{
			if(isOnGround())
		    {
		        AttackTemplates::normalDownA(this, 6,2.96);
		        x += 4 * getPlayerDirMult();
		    }
		    else
		    {
		        AttackTemplates::dropAirDownA(this, STEP_CHARGE, 10, 3.445, 7, 3);
		    }
		}
	}
	
	void Sonic::attackB()
	{
		if(attacksPriority!=7 && !bUp)
		{
		    if(canFinalSmash())
		    {
		        attackFinalSmash();
		    }
		    else
		    {
	            if(!bUp)
	            {
	                bUp=true;
	                yVel=-2;
	                landing=true;
					changeTwoSidedAnimation("special_prep", FORWARD);
	            }
		    }
		}
	}
	
	void Sonic::attackSideB()
	{
		
        if(attacksPriority!=7 && !bUp)
        {
            bUp=true;
            landing=true;
            changeTwoSidedAnimation("special_prep_side", FORWARD);
        }
	}
	
	void Sonic::attackUpB()
	{
	    if(attacksPriority!=7 && !bUp)
	    {
	        AttackTemplates::launchUpB(this, -1,0, 7.5f,7.5f);
	        y-=34;
			
			Spring*spring = new Spring(getPlayerNo(), x, y + ((float)height/2)+26);
	        createProjectile(spring);
			
			addProjectileInfo(1, spring->getID(), x, y + ((float)height/2)+26);
	    }
	}
	
	void Sonic::attackDownB()
	{
		if(attacksPriority!=7)
		{
			smashPower=0;
	        if(isOnGround())
	        {
	            AttackTemplates::chargeB(this, 4, 10, 1400);
	            changeTwoSidedAnimation("special_charge_down",FORWARD);
	            chargeAttack = 1;
	        }
	        else
	        {
	            AttackTemplates::bounceDownB(this,13,3.76, 10);
	        }
		}
	}
	
	void Sonic::attackSideSmash(byte type)
	{
		if(attacksPriority!=7 && !bUp && !checkItemUseSideSmash(type))
	    {
	        if(isOnGround())
	        {
	        	if(type == STEP_CHARGE)
	        	{
	        		AttackTemplates::normalSmash(this,15,2.91,type,1,1500,14,20);
	        	}
	        	else
	        	{
		        	winding = true;
		        	changeTwoSidedAnimation("smash_wind",FORWARD);
	        	}
	        }
	        else
	        {
	            attackSideA();
	        }
	    }
	}
	
	void Sonic::attackUpSmash(byte type)
	{
		if(attacksPriority!=7 && !bUp && !checkItemUseUpSmash(type))
	    {
	        hitAmount=0;
	        if(isOnGround())
	        {
	            AttackTemplates::normalSmash(this,16,3.26,type,2,1800,14,20);
	            if(type==STEP_GO)
	            {
	                y-=15;
	                yVel=-1;
	            }
	        }
	        else
	        {
	            attackUpA();
	        }
	    }
	}
	
	void Sonic::attackDownSmash(byte type)
	{
		if(attacksPriority!=7 && !bUp && !checkItemUseDownSmash(type))
	    {
	        if(isOnGround())
	        {
	            AttackTemplates::normalSmash(this,17,3.5,type,3,1800,12,20);
	        }
	        else
	        {
	            attackDownA();
	        }
	    }
	}
	
	void Sonic::attackFinalSmash()
	{
	    if(!bUp)
	    {
	    	AttackTemplates::finalSmash(this, -1);
	        attacksPriority=7;
	        landing=true;
	        turning=true;
	        xvelocity=0;
	        yvelocity=0;
	        attackTime=Global::getWorldTime()+15000;
	        chargeSmash=0;
	        smashPower=0;
	        finalSmashing = true;
			changeTwoSidedAnimation("finalsmash_transform", FORWARD);
			Emeralds*emeralds = new Emeralds(getPlayerNo(), x, y);
			emeralds->changeAnimation("appear", FORWARD);
			createProjectile(emeralds);
			
			addProjectileInfo(2, emeralds->getID(), x, y);
	    }
	}
	
	Sonic::Spring::Spring(byte playerNo, float x1, float y1) : Projectile(playerNo,x1,y1)
	{
		deadTime=Global::getWorldTime()+5000;
			
		addAnimation(new Animation("normal", 1, "Images/Game/Characters/Sonic/spring_normal.png"));
		Animation*anim = new Animation("bounce", 20, 5, 1);
		anim->addFrame("Images/Game/Characters/Sonic/spring_bounce.png");
		addAnimation(anim);
			
		changeAnimation("normal",FORWARD);
			
		setSolid(true);
	}

	Sonic::Spring::~Spring()
	{
		//
	}
		
	void Sonic::Spring::Update(long gameTime)
	{
		yvelocity+=0.5;

		if(deadTime>0)
		{
			if(deadTime<=Global::getWorldTime())
			{
			    destroy();
			}
		}
		Projectile::Update(gameTime);
	}
	
	void Sonic::Spring::onAnimationFinish(const String&n)
	{
		if(n.equals("bounce"))
		{
			changeAnimation("normal",FORWARD);
		}
	}
	
	void Sonic::Spring::onPlayerHit(Player*collide, byte dir)
	{
		if(dir==DIR_UP)
		{
			if(collide->getPlayerNo()>0 && !collide->isHanging())
			{
				if(collide->yvelocity<=5 && collide->yvelocity>=0)
				{
				    collide->yvelocity=-5;
				}
				else
				{
				    collide->yvelocity=-std::abs(collide->yvelocity);
				}
				changeAnimation("bounce", FORWARD);
			}
		}
	}
	
	void Sonic::Spring::whilePlatformColliding(Platform*collide, byte dir)
	{
		switch(dir)
		{
			case DIR_UP:
			yvelocity*=0;
			break;
				
			case DIR_DOWN:
			yvelocity*=0;
			break;
				
			case DIR_LEFT:
			xvelocity*=0;
			break;
				
			case DIR_RIGHT:
			xvelocity*=0;
			break;
		}
	}
	
	Sonic::Emeralds::Emeralds(byte playerNo, float x1, float y1) : Projectile(playerNo, x1, y1)
	{
		Animation*anim = new Animation("appear", 10, 7, 1);
		anim->addFrame("Images/Game/Characters/Sonic/finalsmash_emeralds.png");
		addAnimation(anim);
		
		ArrayList<int> seq; seq.add(6); seq.add(5); seq.add(4); seq.add(3);
		anim = new Animation("disappear", 4, 7, 1, seq);
		anim->addFrame("Images/Game/Characters/Sonic/finalsmash_emeralds.png");
		addAnimation(anim);
		
		changeAnimation("appear",FORWARD);
	}

	Sonic::Emeralds::~Emeralds()
	{
		//
	}
	
	void Sonic::Emeralds::onAnimationFinish(const String&n)
	{
		destroy();
	}
}