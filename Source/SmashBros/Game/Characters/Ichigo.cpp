
#include "Ichigo.h"
#include "../../AttackTemplates.h"
#include "../../Global.h"
#include "../../P2PDataManager.h"
#include <cmath>

namespace SmashBros
{
	void Ichigo::addProjectileInfo(byte type, int projID, float x, float y)
	{
		ProjectileInfo info;
		info.type = type;
		info.projID = projID;
		info.x = x;
		info.y = y;
		createdProjectiles.add(info);
	}
	
	Ichigo::Ichigo(float x1, float y1, byte playerNo, byte team) : Player(x1, y1, playerNo, team)
	{
		charging = 0;
		finalSmash = false;
		dropDownAttack = false;

		walkSpeed = 3.2f;
		runSpeed = 5;
		fallWalk = 2.8f;
		fallRun = 3;
		
		weight = 0.16;
		
		name = "Ichigo";
		
		setScale(0.95f);
		
		setHitbox(-14, 0, 28, 45);
		setHitboxColor(Color::GREEN);
		//showHitboxWireframe(true);
		//setWireframeColor(Color.red);
		//showWireframe(true);
		
		setHangPoint(7, 23);
		setIndicatorOffset(0, -10);
		setItemOffset(4, 16);
		
		oldSmashPower = 0;
		
		Console::WriteLine((String)"finished creating player " + playerNo);
	}

	Ichigo::~Ichigo()
	{
		//
	}
	
	void Ichigo::addP2PData(DataVoid&data)
	{
		int total = createdProjectiles.size();
		
		if(total>0)
		{
			P2PDataManager::setReliable();
			
			bool avail = true;
			data.add(&avail, sizeof(avail));
			
			data.add(&oldSmashPower, sizeof(oldSmashPower));
			
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
	
	void Ichigo::setP2PData(byte*&data)
	{
		bool avail = DataVoid::toBool(data);
		data += sizeof(bool);
		
		if(avail)
		{
			oldSmashPower = DataVoid::toInt(data);
			data += sizeof(int);
			
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
						Blast*blast = new Blast(getPlayerNo(), x1, y1);
						blast->setScale((float)oldSmashPower/100);
						createProjectile(blast);
					}
					break;
					
					case 2:
					{
						Projectile::setNextID(projID);
						createProjectile(new SpinningBlade(getPlayerNo(), x1, y1));
					}
					break;
					
					case 3:
					{
						Projectile::setNextID(projID);
						createProjectile(new GroundStab(getPlayerNo(), x1, y1));
					}
					break;
					
					case 4:
					{
						Projectile::setNextID(projID);
						createProjectile(new FinalSmashBlast(getPlayerNo(), x1, y1));
					}
				}
			}
		}
	}
	
	void Ichigo::Load()
	{
		setFolderPath("Images/Game/Characters/Ichigo/");
		
		loadFile("Images/Game/Characters/Ichigo/projectile.png");
		loadFile("Images/Game/Characters/Ichigo/down_blast.png");
		loadFile("Images/Game/Characters/Ichigo/finalsmash_blast.png");
		loadFile("Images/Game/Characters/Ichigo/blade.png");
		
		addTwoSidedAnimation("stand", "stand.png", 6, 4, 1);
		addTwoSidedAnimation("walk", "walk.png", 6, 4, 1);
		addTwoSidedAnimation("run", "run.png", 15, 2, 1);
		addTwoSidedAnimation("jump", "jump.png", 8, 6, 1);
		addTwoSidedAnimation("jump2", "jump2.png", 14, 6, 1);
		addTwoSidedAnimation("land", "land.png", 8, 3, 1);
		addTwoSidedAnimation("fall", "fall.png", 30, 1, 1);
		addTwoSidedAnimation("hang", "hang.png", 1, 1, 1);
		addTwoSidedAnimation("crouch", "crouch.png", 1, 1, 1);
		addTwoSidedAnimation("grab", "grab.png", 8, 3, 1);
		addTwoSidedAnimation("grabbed", "grabbed.png", 30, 1, 1);
		addTwoSidedAnimation("hold", "hold.png", 30, 1, 1);
		addTwoSidedAnimation("release", "release.png", 10, 2, 1);
		addTwoSidedAnimation("toss", "toss.png", 10, 3, 1);
		addTwoSidedAnimation("toss_up", "toss_up.png", 17, 5, 1);
		addTwoSidedAnimation("toss_down", "toss_down.png", 10, 3, 1);
		addTwoSidedAnimation("grab_attack", "grab_attack.png", 10, 3, 1);
		addTwoSidedAnimation("grab_attack_swing", "grab_attack_swing.png", 12, 4, 1);
		addTwoSidedAnimation("melee_weapon", "melee_weapon.png", 10, 6, 1);
		addTwoSidedAnimation("melee_weapon_up", "melee_weapon_up.png", 12, 5, 1);
		addTwoSidedAnimation("melee_weapon_down", "melee_weapon_down.png", 8, 3, 1);
		addTwoSidedAnimation("hurt_minor", "hurt_minor.png", 1, 1, 1);
		addTwoSidedAnimation("hurt_fly", "hurt_fly.png", 1, 1, 1);
		addTwoSidedAnimation("hurt_flip", "hurt_flip.png", 10, 4, 1);
		addTwoSidedAnimation("hurt_spin", "hurt_spin.png", 12, 4, 1);
		addSingleAnimation("hurt_spin_up", "hurt_spin_up.png", 12, 4, 1);
		addTwoSidedAnimation("standard_attack", "standard_attack.png", 14, 5, 1);
		addTwoSidedAnimation("standard_attack_finish", "standard_attack_finish.png", 14, 1, 1);
		addTwoSidedAnimation("standard_attack2", "standard_attack2.png", 14, 6, 1);
		addTwoSidedAnimation("standard_attack3", "standard_attack3.png", 14, 6, 1);
		addTwoSidedAnimation("standard_attack_side", "standard_attack_side.png", 12, 6, 1);
		addTwoSidedAnimation("standard_attack_up", "standard_attack_up.png", 10, 6, 1);
		addTwoSidedAnimation("standard_attack_down", "standard_attack_down.png", 10, 6, 1);
		addTwoSidedAnimation("air_attack", "air_attack.png", 10, 6, 1);
		addTwoSidedAnimation("air_attack_side", "air_attack_side.png", 10, 6, 1);
		addTwoSidedAnimation("air_attack_up", "air_attack_up.png", 10, 6, 1);
		addTwoSidedAnimation("air_attack_down", "air_attack_down.png", 10, 6, 1);
		addTwoSidedAnimation("special_attack", "special_attack.png", 10, 6, 1);
		addTwoSidedAnimation("special_attack_side", "special_attack_side.png", 18, 6, 1);
		addTwoSidedAnimation("special_attack_up", "special_attack_up.png", 12, 10, 1);
		addTwoSidedAnimation("special_prep_down", "special_prep_down.png", 8, 2, 1);
		addTwoSidedAnimation("special_drop_down", "special_drop_down.png", 1, 1, 1);
		addTwoSidedAnimation("special_attack_down", "special_attack_down.png", 4, 4, 1);
		addTwoSidedAnimation("smash_charge", "smash_charge.png", 8, 4, 1);
		addTwoSidedAnimation("smash_attack", "smash_attack.png", 12, 6, 1);
		addTwoSidedAnimation("smash_attack_up", "smash_attack_up.png", 12, 4, 1);
		addTwoSidedAnimation("smash_attack_down", "smash_attack_down.png", 12, 6, 1);
		addTwoSidedAnimation("finalsmash_stand", "finalsmash_stand.png", 6, 4, 1);
		addTwoSidedAnimation("finalsmash_run", "finalsmash_run.png", 8, 8, 1);
		addTwoSidedAnimation("finalsmash_shoot", "finalsmash_shoot.png", 14, 9, 1);
		addTwoSidedAnimation("finalsmash_change", "finalsmash_change.png", 9, 6, 1);
	}
	
	void Ichigo::LoadAttackTypes()
	{
		addAIAttackType(ATTACK_A,         ATTACKTYPE_MELEE, 5);
		addAIAttackType(ATTACK_SIDEA,     ATTACKTYPE_MELEE, 4);
		addAIAttackType(ATTACK_UPA,       ATTACKTYPE_UPMELEE, 2);
		addAIAttackType(ATTACK_DOWNA,     ATTACKTYPE_MELEE, 1);
		addAIAttackType(ATTACK_DOWNA,     ATTACKTYPE_DOWNMELEE, 3);
		addAIAttackType(ATTACK_B,         ATTACKTYPE_PROJECTILE, 1, true);
		addAIAttackType(ATTACK_SIDEB,     ATTACKTYPE_SIDEMOVE, 1);
		addAIAttackType(ATTACK_UPB,       ATTACKTYPE_UPMOVE, 2);
		addAIAttackType(ATTACK_UPB,       ATTACKTYPE_UPMELEE, 1);
		addAIAttackType(ATTACK_DOWNB,     ATTACKTYPE_DOWNMELEE, 1);
		addAIAttackType(ATTACK_DOWNB,     ATTACKTYPE_DOWNMOVE, 2);
		addAIAttackType(ATTACK_SIDESMASH, ATTACKTYPE_STRONGMELEE, 2);
		addAIAttackType(ATTACK_UPSMASH,   ATTACKTYPE_STRONGMELEE, 1);
		addAIAttackType(ATTACK_DOWNSMASH, ATTACKTYPE_STRONGMELEE, 1);
		addAIAttackType(ATTACK_FINALSMASH,ATTACKTYPE_PROJECTILE, 1);
	}

	void Ichigo::setToDefaultValues()
	{
		charging = 0;
		finalSmash = false;
		dropDownAttack = false;
	}

	boolean Ichigo::checkIfAble()
	{
		if(finalSmash)
		{
			return false;
		}
		return true;
	}
	
	void Ichigo::onAnimationFinish(const String&n)
	{
		if(n.equals("special_drop_down_left") || n.equals("special_drop_down_right"))
		{
			//
		}
		else if(n.equals("standard_attack_left") || n.equals("standard_attack_right"))
		{
			animFinish();
			changeTwoSidedAnimation("standard_attack_finish",FORWARD);
		}
		else if(n.equals("special_attack_side_left") || n.equals("special_attack_side_right"))
		{
			xVel = 0;
			animFinish();
			attackSideA();
		}
		else if(n.equals("special_prep_down_left") || n.equals("special_prep_down_right"))
		{
			if(isOnGround())
			{
				GroundStab*stab = new GroundStab(getPlayerNo(),x,y + 2);
	            AttackTemplates::singleProjectile(this, 14, 1.6, stab);
	            
				addProjectileInfo(3, stab->getID(), x, y + 2);
				
				changeTwoSidedAnimation("special_attack_down",FORWARD);
			}
			else
			{
				dropDownAttack = true;
				if(yvelocity < 5)
				{
					yvelocity = 5;
				}
				changeTwoSidedAnimation("special_drop_down",FORWARD);
			}
		}
		else if(n.equals("finalsmash_change_left") || n.equals("finalsmash_change_right"))
		{
			changeTwoSidedAnimation("finalsmash_stand",FORWARD);
		}
		else if(n.equals("finalsmash_stand_left") || n.equals("finalsmash_stand_right"))
		{
			changeTwoSidedAnimation("finalsmash_run", FORWARD);
			xVel = 5 * getPlayerDirMult();
		}
		else if(n.equals("finalsmash_run_left") || n.equals("finalsmash_run_right"))
		{
			xVel=0;
			changeTwoSidedAnimation("finalsmash_shoot", FORWARD);
			FinalSmashBlast*smashBlast = new FinalSmashBlast(getPlayerNo(),x,y);
			createProjectile(smashBlast);
			
			addProjectileInfo(4, smashBlast->getID(), x, y);
		}
		else if(n.equals("finalsmash_shoot_left") || n.equals("finalsmash_shoot_right"))
		{
			finalSmash = false;
			animFinish();
			AttackTemplates::finishFinalSmash(this);
		}
		else
		{
			Player::onAnimationFinish(n);
		}
	}
	
	void Ichigo::onGroundCollide()
	{
		Player::onGroundCollide();
		if(dropDownAttack)
		{
			dropDownAttack = false;
			GroundStab*stab = new GroundStab(getPlayerNo(),x,y + 2);
			AttackTemplates::singleProjectile(this, 14, 1.6, stab);
			
			addProjectileInfo(3, stab->getID(), x, y + 2);
			
            changeTwoSidedAnimation("special_attack_down",FORWARD);
		}
	}
	
	void Ichigo::Update(long gameTime)
	{
		Player::Update(gameTime);
		checkAttacks();
		
		if(attacksHolder==12 && !isOnGround())
		{
			if(moveLeft>0)
			{
				x-=3;
			}
			else if(moveRight>0)
			{
				x+=3;
			}
		}
		
		if(!finalSmash && attacksHolder!=11)
		{
			updateGravity();
		}
		updateFrame();
		
		updateMovement();
		
		updateHanging();
		updateHurt();
		updateDrop();
		updateAI();
	}
	
	void Ichigo::Draw(Graphics2D&g, long gameTime)
	{
		Player::Draw(g, gameTime);
	}
	
	void Ichigo::jump()
	{
		Player::jump(5.3f,5.9f);
	}
	
	void Ichigo::whilePlayerColliding(Player*collide, byte dir)
	{
		if(attacksHolder==11)
		{
			collide->x += (std::abs(xVel)+1) * getPlayerDirMult();
		}
	}
	
	void Ichigo::onPlayerHit(Player*collide, byte dir)
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
					causeDamage(collide,4);
					collide->y -= 8;
					collide->x -= 3 * getPlayerDirMult();
					x += 2 * getPlayerDirMult();
					causeHurt(collide, getOppPlayerDir(), 100);
					break;
					
					case 1:
					//A 2
					causeDamage(collide,4);
					collide->y -= 8;
					collide->x -= 3 * getPlayerDirMult();
					x += 4 * getPlayerDirMult();
					causeHurt(collide, getOppPlayerDir(), 100);
					break;
					
					case 11:
					//B Side
					collide->x += (std::abs(xVel)+1) * getPlayerDirMult();
					break;
					
					case 15:
					//Smash Side
					causeDamage(collide,smashPower);
					causeHurtLaunch(collide, (int)getPlayerDirMult(),5,((float)smashPower/6), -1,3,((float)smashPower/7));
					causeHurt(collide, getOppPlayerDir(), 800);
					break;
					
					case 16:
					//Smash Up
					causeDamage(collide,smashPower);
					causeHurtLaunch(collide, (int)getPlayerDirMult(),2,((float)smashPower/7), -1,5,((float)smashPower/5));
					causeHurt(collide, getOppPlayerDir(), 800);
					break;
					
					case 17:
					//Smash Down
					causeDamage(collide,smashPower);
					causeHurtLaunch(collide, (int)getPlayerDirMult(),5,((float)smashPower/5), -1,5,((float)smashPower/5));
					causeHurt(collide, getOppPlayerDir(), 800);
					break;
				}
			}
			break;
			
			case DIR_UP:
			{
				switch(attacksHolder)
				{
					case 0:
					//A
					causeDamage(collide,4);
					collide->y -= 3;
					collide->x -= 5 * getPlayerDirMult();
					x += 2 * getPlayerDirMult();
					causeHurt(collide, getOppPlayerDir(), 100);
					
					case 1:
					//A 2
					causeDamage(collide,4);
					collide->y -= 3;
					collide->x -= 5 * getPlayerDirMult();
					x += 4 * getPlayerDirMult();
					causeHurt(collide, getOppPlayerDir(), 100);
					break;
					
					case 16:
					//Smash Up
					causeDamage(collide,smashPower);
					causeHurtLaunch(collide, 0,0,0, -1,6,((float)smashPower/6));
					causeHurt(collide, collide->getPlayerDir(), 800);
					break;
				}
			}
			break;
			
			case DIR_DOWN:
			{
				switch(attacksHolder)
				{
					case 0:
					//A
					causeDamage(collide,4);
					collide->y -= 8;
					collide->x -= 5 * getPlayerDirMult();
					x += 2 * getPlayerDirMult();
					causeHurt(collide, getOppPlayerDir(), 100);
					break;
					
					case 1:
					//A 2
					causeDamage(collide,4);
					collide->y -= 8;
					collide->x -= 5 * getPlayerDirMult();
					x += 4 * getPlayerDirMult();
					causeHurt(collide, getOppPlayerDir(), 100);
					break;
					
					case 15:
					//Smash Side
					switch(playerdir)
					{
						case LEFT:
						if(collide->x < x)
						{
							causeDamage(collide,smashPower);
							causeHurtLaunch(collide,-1,5,((float)smashPower/6), -1,3,((float)smashPower/7));
							causeHurt(collide, RIGHT, 800);
						}
						break;
						
						case RIGHT:
						if(collide->x > x)
						{
							causeDamage(collide,smashPower);
							causeHurtLaunch(collide,1,5,((float)smashPower/6), -1,3,((float)smashPower/7));
							causeHurt(collide, RIGHT, 800);
						}
						break;
					}
					break;
					
					case 17:
					//Smash Down
					causeDamage(collide,smashPower);
					causeHurtLaunch(collide,0,0,0, 1,6,((float)smashPower/5));
					causeHurt(collide, collide->getPlayerDir(), 400);
					break;
				}
			}
			break;
		}
	}
	
	void Ichigo::onFinishCharge()
	{
		//
	}
	
	void Ichigo::doChargingAttack(byte button)
	{
		if(charging==1)
		{
			destroyCharge();
			Blast*blast = new Blast(getPlayerNo(), x, y);
			blast->setScale((float)smashPower/100);
			oldSmashPower = smashPower;
			createProjectile(blast);
			
			addProjectileInfo(1, blast->getID(), x, y);
			
			charging = 0;
			switch(playerdir)
			{
				case LEFT:
				changeAnimation("special_attack_left",FORWARD);
				break;
				
				case RIGHT:
				changeAnimation("special_attack_right",FORWARD);
				break;
			}
		}
	}
	
	void Ichigo::attackA()
	{
		addAttackInfo(DIR_LEFT, 2, LEFT, 4, 400, -1,3,5, -1,2,3);
		addAttackInfo(DIR_RIGHT,2,RIGHT, 4, 400,  1,3,5, -1,2,3);
		addAttackInfo(DIR_LEFT, 6, LEFT, 12, 400, -1,3,3, -1,2,3);
		addAttackInfo(DIR_RIGHT,6,RIGHT, 12, 400,  1,3,3, -1,2,3);
		addAttackInfo(DIR_UP, 2, LEFT, 4, 400, -1,3,5, -1,2,3);
		addAttackInfo(DIR_UP, 2,RIGHT, 4, 400,  1,3,5, -1,2,3);
		addAttackInfo(DIR_UP, 6, LEFT, 12, 400, -1,2,3, -1,3,3);
		addAttackInfo(DIR_UP, 6,RIGHT, 12, 400,  1,2,3, -1,3,3);
		addAttackInfo(DIR_DOWN, 2, LEFT, 4, 400, -1,3,5, -1,2,3);
		addAttackInfo(DIR_DOWN, 2,RIGHT, 4, 400,  1,3,5, -1,2,3);
		addAttackInfo(DIR_DOWN, 6, LEFT, 12, 400, -1,2,3, 1,3,3);
		addAttackInfo(DIR_DOWN, 6,RIGHT, 12, 400,  1,2,3, 1,2,3);
		
	    if(!checkItemUse())
	    {
	        if(isOnGround())
	        {
	            AttackTemplates::combo3A(this, 700, 0,1.2, 1,1.1, 2,2.3);
	        }
	        else
	        {
	        	AttackTemplates::normalAirA(this, 6,0.9);
	        }
	    }
	}
	
	void Ichigo::attackSideA()
	{
        addAttackInfo(DIR_LEFT, 3, LEFT, 12, 500, -1,2,4, -1,4,4);
        addAttackInfo(DIR_RIGHT,3,RIGHT, 12, 500,  1,2,4, -1,4,4);
        addAttackInfo(DIR_LEFT, 7, LEFT, 10, 500, -1,3,3, -1,3,3);
        addAttackInfo(DIR_RIGHT,7,RIGHT, 10, 500,  1,3,3, -1,3,3);
        addAttackInfo(DIR_UP, 3, LEFT, 12, 500, -1,2,3, -1,5,5);
        addAttackInfo(DIR_UP, 3,RIGHT, 12, 500,  1,2,3, -1,5,5);
        addAttackInfo(DIR_UP, 7, LEFT, 10, 500, -1,3,3, -1,3,3);
        addAttackInfo(DIR_UP, 7,RIGHT, 10, 500,  1,3,3, -1,3,3);
        addAttackInfo(DIR_DOWN, 3, LEFT, 12, 500, -1,2,3, 1,5,5);
        addAttackInfo(DIR_DOWN, 3,RIGHT, 12, 500,  1,2,3, 1,5,5);
        
	    if(!checkItemUseSide())
	    {
	        if(isOnGround())
	        {
	        	AttackTemplates::normalSideA(this, 3,2.25);
	        }
	        else
	        {
	        	AttackTemplates::normalAirSideA(this, 7,2.23);
	        }
	    }
	}
	
	void Ichigo::attackUpA()
	{
        addAttackInfo(DIR_LEFT, 8, LEFT, 13, 600, -1,3.2f,3.4f, -1,2.9f,3.8f);
        addAttackInfo(DIR_RIGHT,8,RIGHT, 13, 600,  1,3.2f,3.4f, -1,2.9f,3.8f);
        addAttackInfo(DIR_UP, 4, LEFT, 9, 600, -1,1.2f,1.4f, -1,4,3.8f);
        addAttackInfo(DIR_UP, 4,RIGHT, 9, 600,  1,1.2f,1.4f, -1,4,3.8f);
        addAttackInfo(DIR_UP, 8, LEFT, 13, 600, -1,2.1f,2.3f, -1,4.5f,3.8f);
        addAttackInfo(DIR_UP, 8,RIGHT, 13, 600,  1,2.1f,2.3f, -1,4.5f,3.8f);
        addAttackInfo(DIR_DOWN, 4, LEFT, 9, 600, 0,0,0, -1,4,6);
        addAttackInfo(DIR_DOWN, 4,RIGHT, 9, 600, 0,0,0, -1,4,6);
        addAttackInfo(DIR_DOWN, 8, LEFT, 13, 600, 0,0,0, -1,4.5f,6);
        addAttackInfo(DIR_DOWN, 8,RIGHT, 13, 600, 0,0,0, -1,4.5f,6);
        
		if(!checkItemUseUp())
		{
			if(isOnGround())
			{
				AttackTemplates::normalUpA(this, 4,1.94);
			}
			else
			{
				AttackTemplates::normalAirUpA(this, 8,2.36);
			}
		}
	}
	
	void Ichigo::attackDownA()
	{
		addAttackInfo(DIR_LEFT, 5, LEFT, 9, 500, -1,3,6, -1,2,3);
		addAttackInfo(DIR_RIGHT,5,RIGHT, 9, 500,  1,3,6, -1,2,3);
		addAttackInfo(DIR_LEFT, 9, LEFT, 12, 600, 0,0,0, -1,5,6);
		addAttackInfo(DIR_RIGHT,9,RIGHT, 12, 600, 0,0,0, -1,5,6);
		addAttackInfo(DIR_DOWN, 9, LEFT, 12, 600, 0,0,0, 1,5,6);
		addAttackInfo(DIR_DOWN, 9,RIGHT, 12, 600, 0,0,0, 1,5,6);
		
		if(!checkItemUseDown())
		{
			if(isOnGround())
			{
				AttackTemplates::normalDownA(this, 5,2.24);
			}
			else
			{
				AttackTemplates::normalAirDownA(this, 9,2.83);
			}
		}
	}
	
	void Ichigo::attackB()
	{
	    if(!bUp)
	    {
	        if((canFinalSmash()) && (isOnGround()))
	        {
	            attackFinalSmash();
	        }
	        else
	        {
	        	AttackTemplates::chargeB(this, 30, 100, 3000);
	        	attacksHolder=10;
	        	attacksPriority=0;
	        	charging = 1;
	        	changeTwoSidedAnimation("smash_charge",FORWARD);
	        }
	    }
	}
	
	void Ichigo::attackSideB()
	{
		if(!bUp)
	    {
			AttackTemplates::dashSideB(this, 11, 1, 9);
	    }
	}
	
	void Ichigo::attackUpB()
	{
	    if(!bUp)
	    {
	        AttackTemplates::rehitUpB2(this, 12, 4, 2, 0);
			SpinningBlade*blade = new SpinningBlade(getPlayerNo(),x, y-((float)4*getScale()));
	        createProjectile(blade);
			
			addProjectileInfo(2, blade->getID(), x, y-((float)4*getScale()));
			
	        yvelocity=0;
	        xvelocity=0;
	    }
	}
	
	void Ichigo::attackDownB()
	{
		if(!bUp)
	    {
			AttackTemplates::prepareDownB(this, 13, 0);
	    }
	}
	
	void Ichigo::attackSideSmash(byte type)
	{
	    if(!bUp && !checkItemUseSideSmash(type))
	    {
	        if(isOnGround())
	        {
	            AttackTemplates::normalSmash(this,15,3.49,type,1,1800,11,20);
	        }
	        else
	        {
	            attackSideA();
	        }
	    }
	}
	
	void Ichigo::attackUpSmash(byte type)
	{
	    if(!bUp && !checkItemUseUpSmash(type))
	    {
	        if(isOnGround())
	        {
	            AttackTemplates::normalSmash(this,16,3.65,type,2,1700,11,20);
	        }
	        else
	        {
	            attackUpA();
	        }
	    }
	}
	
	void Ichigo::attackDownSmash(byte type)
	{
	    if(!bUp && !checkItemUseDownSmash(type))
	    {
	        if(isOnGround())
	        {
	            AttackTemplates::normalSmash(this,17,3.48,type,3,1600,11,20);
	        }
	        else
	        {
	            attackDownA();
	        }
	    }
	}
	
	void Ichigo::attackFinalSmash()
	{
        addAttackInfo(DIR_LEFT, 18, LEFT, 10, 900, -1,5,8, -1,5,8);
        addAttackInfo(DIR_RIGHT,18,RIGHT, 10, 900,  1,5,8, -1,5,8);
        
        if(isOnGround())
        {
            yVel=0;
            chargeSmash=0;
            smashPower=0;
            finalSmash = true;
            AttackTemplates::finalSmash(this, 18);
            destroyCharge();
            changeTwoSidedAnimation("finalsmash_change", FORWARD);
			attacksPriority=7;
        }
        else
        {
            attackB();
        }
	}
	
	Ichigo::Blast::Blast(byte playerNo, float x1, float y1) : Projectile(playerNo, x1, y1)
	{
		Animation*anim;
		anim = new Animation("left",1,"Images/Game/Characters/Ichigo/projectile.png");
		addAnimation(anim);
			
		anim = new Animation("right",1,"Images/Game/Characters/Ichigo/projectile.png");
		anim->mirror(true);
		addAnimation(anim);
		
		setDeflectable(true);
			
		switch(itemdir)
		{
			case LEFT:
			xvelocity = -5;
			changeAnimation("left",FORWARD);
			break;
				
			case RIGHT:
			xvelocity = 5;
			changeAnimation("right",FORWARD);
			break;
		}
		startX = x;
		
		setLayer(LAYER_MIDDLEUPPER);
	}

	Ichigo::Blast::~Blast()
	{
		//
	}
	
	void Ichigo::Blast::deflect(byte dir)
	{
		switch(dir)
		{
			case DIR_LEFT:
			case DIR_UPLEFT:
			case DIR_DOWNLEFT:
			itemdir = LEFT;
			xvelocity = -5;
			changeAnimation("left", NO_CHANGE);
			break;
			
			case DIR_RIGHT:
			case DIR_UPRIGHT:
			case DIR_DOWNRIGHT:
			itemdir = RIGHT;
			xvelocity = 5;
			changeAnimation("right", NO_CHANGE);
			break;
		}
	}
	
	void Ichigo::Blast::Update(long gameTime)
	{
		Projectile::Update(gameTime);
		if(std::abs(startX - x)>240)
		{
			destroy();
		}
	}
		
	void Ichigo::Blast::onPlayerHit(Player*collide, byte dir)
	{
		int smashPower = Global::getPlayerActor(getPlayerNo())->getSmashPower();
		if(isHittable(collide,dir))
		{
			causeDamage(collide,5);
			switch(itemdir)
			{
				case LEFT:
				causeHurtLaunch(collide, -1,2.5f,((float)smashPower/5), -1,2.5f,((float)smashPower/5));
				causeHurt(collide, RIGHT, 400);
				break;
					
				case RIGHT:
				causeHurtLaunch(collide, 1,2.5f,((float)smashPower/5), -1,2.5f,((float)smashPower/5));
				causeHurt(collide, LEFT, 400);
				break;
			}
			destroy();
		}
	}

	Ichigo::SpinningBlade::SpinningBlade(byte playerNo, float x1, float y1) : Projectile(playerNo,x1,y1)
	{
		Animation*anim;
			
		anim = new Animation("left",12,8,1);
		anim->addFrame("Images/Game/Characters/Ichigo/blade.png");
		addAnimation(anim);
			
		anim = new Animation("right",12,8,1);
		anim->addFrame("Images/Game/Characters/Ichigo/blade.png");
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
		
		setScale(Global::getPlayerActor(playerNo)->getScale());
		
		setLayer(LAYER_MIDDLELOWER);
		
		hits=0;
	}

	Ichigo::SpinningBlade::~SpinningBlade()
	{
		//
	};
	
	void Ichigo::SpinningBlade::Update(long gameTime)
	{
		Player*owner = Global::getPlayerActor(getPlayerNo());
		
		x = owner->x;
		y = owner->y - ((float)4*owner->getScale());
		
		String ownerAnim = owner->getAnimName();
		if(owner->isHurt() || owner->isHanging() || (!ownerAnim.equals("special_attack_up_left") && !ownerAnim.equals("special_attack_up_right")))
		{
			destroy();
		}
			
		Projectile::Update(gameTime);
	}
		
	void Ichigo::SpinningBlade::Draw(Graphics2D&g, long gameTime)
	{
		Player*owner = Global::getPlayerActor(getPlayerNo());
			
		x = owner->x;
		y = owner->y - ((float)4*owner->getScale());
			
		Projectile::Draw(g, gameTime);
	}
		
	void Ichigo::SpinningBlade::onAnimationFinish(const String&n)
	{
		Player*owner = Global::getPlayerActor(getPlayerNo());
		owner->yvelocity = owner->yVel;
		owner->yVel = 0;
		destroy();
	}
		
	void Ichigo::SpinningBlade::onPlayerHit(Player*collide, byte dir)
	{
		if(isHittable(collide,dir))
		{
			Player*playr = Global::getPlayerActor(getPlayerNo());
			switch(playr->getPlayerDir())
			{
			    case LEFT:
			    //B Up
			    switch(hits)
			    {
			        case 0:
			        case 1:
			        case 2:
			        case 3:
			        case 4:
			        case 5:
			        causeDamage(collide,2);
			        collide->y=y-((height/2)+(collide->height/2)+2);
			        hits+=1;
			        causeHurt(collide, collide->getPlayerDir(), 100);
			        break;
			 
			        case 6:
			        causeDamage(collide,2);
			        playr->yvelocity=-2;
			        hits+=1;
			        collide->yvelocity=0;
			        causeHurtLaunch(collide,0,0,0, -1,5,3);
			        causeHurt(collide, collide->getPlayerDir(), 300);
			        break;
			    }
			    break;
			 
			    case RIGHT:
			    //B Up
			    switch(hits)
			    {
			        case 0:
			        case 1:
			        case 2:
			        case 3:
			        case 4:
			        case 5:
			        causeDamage(collide,2);
			        //collide->y=y-((height/2)+(collide->height/2)+12);
			        collide->y=y-((height/2)+(collide->height/2)+2);
			        hits+=1;
			        causeHurt(collide, collide->getPlayerDir(), 100);
			        break;
			 
			        case 6:
			        causeDamage(collide,2);
			        playr->yvelocity=-2;
			        hits+=1;
			        collide->yvelocity=0;
			        causeHurtLaunch(collide,0,0,0, -1,5,3);
			        causeHurt(collide, collide->getPlayerDir(), 300);
			        break;
			    }
			    break;
			}
		}
	}
	
	Ichigo::GroundStab::GroundStab(byte playerNo, float x1, float y1) : Projectile(playerNo, x1,y1)
	{
		Animation*anim;
		anim = new Animation("normal",6,4,1);
		anim->addFrame("Images/Game/Characters/Ichigo/down_blast.png");
		addAnimation(anim);
		changeAnimation("normal",FORWARD);
			
		setLayer(LAYER_MIDDLEUPPER);
	}

	Ichigo::GroundStab::~GroundStab()
	{
		//
	}
		
	void Ichigo::GroundStab::onPlayerHit(Player*collide, byte dir)
	{
		dir = getDir2(x,y,collide->x,collide->y);
		if(isHittable(collide,dir))
		{
			switch(dir)
			{
				case DIR_LEFT:
				causeDamage(collide,11);
				causeHurtLaunch(collide, -1,4,3, -1,3,3);
				causeHurt(collide, RIGHT, 400);
				break;
					
				case DIR_RIGHT:
				causeDamage(collide,11);
				causeHurtLaunch(collide, 1,4,3, -1,3,3);
				causeHurt(collide, LEFT, 400);
				break;
					
				case DIR_UP:
				causeDamage(collide,11);
				causeHurtLaunch(collide, 0,0,0, -1,4,5);
				causeHurt(collide, collide->getPlayerDir(), 400);
				break;
					
				case DIR_DOWN:
				causeDamage(collide,11);
				causeHurtLaunch(collide, 0,0,0, 1,4,5);
				causeHurt(collide, collide->getPlayerDir(), 400);
				break;
			}
		}
	}
	
	void Ichigo::GroundStab::onAnimationFinish(const String&n)
	{
		if(n.equals("normal"))
		{
			destroy();
		}
	}
	
	Ichigo::FinalSmashBlast::FinalSmashBlast(byte playerNo, float x1, float y1) : Projectile(playerNo, x1,y1)
	{
		setScale(1.6f);
		
		addAnimation(new Animation("left",1,"Images/Game/Characters/Ichigo/finalsmash_blast.png"));
		Animation*anim = new Animation("right",1,"Images/Game/Characters/Ichigo/finalsmash_blast.png");
		anim->mirror(true);
		addAnimation(anim);
		
		setLayer(LAYER_MIDDLEUPPER);
		
		switch(itemdir)
		{
			case LEFT:
			changeAnimation("left",FORWARD);
			xvelocity = -5.5f;
			break;
			
			case RIGHT:
			changeAnimation("right",FORWARD);
			xvelocity = 5.5f;
			break;
		}
	}

	Ichigo::FinalSmashBlast::~FinalSmashBlast()
	{
		//
	}
		
	void Ichigo::FinalSmashBlast::onPlayerHit(Player*collide, byte dir)
	{
		if(isHittable(collide,dir))
		{
			switch(dir)
			{
				case DIR_LEFT:
				causeDamage(collide,34);
				causeHurtLaunch(collide, -1,6,8, -1,6,8);
				causeHurt(collide, RIGHT, 900);
				break;
				
				case DIR_RIGHT:
				causeDamage(collide,34);
				causeHurtLaunch(collide, 1,6,8, -1,6,8);
				causeHurt(collide, LEFT, 900);
				break;
				
				case DIR_UP:
				causeDamage(collide, 34);
				causeHurtLaunch(collide, 0,0,0, -1,6,8);
				causeHurt(collide, collide->getPlayerDir(), 900);
				break;
				
				case DIR_DOWN:
				causeDamage(collide, 34);
				causeHurtLaunch(collide, 0,0,0, 1,6,8);
				causeHurt(collide, collide->getPlayerDir(), 900);
				break;
			}
		}
	}
}