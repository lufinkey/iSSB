
#include "Pikachu.h"
#include "../../AttackTemplates.h"
#include "../../Global.h"
#include "../../Controls.h"
#include "../../P2PDataManager.h"
#include "../../ProjectileManager.h"
#include <cmath>

namespace SmashBros
{
	const float Pikachu::finalsmashSlow = 6;
	const float Pikachu::finalsmashFast = 12;
	
	void Pikachu::addProjectileInfo(byte type, int projID, float x, float y, byte itemdir, int ownerID)
	{
		ProjectileInfo info;
		info.type = type;
		info.projID = projID;
		info.x = x;
		info.y = y;
		info.itemdir = itemdir;
		info.ownerID = ownerID;
		createdProjectiles.add(info);
	}
	
	Pikachu::Pikachu(float x1, float y1, byte playerNo, byte team) : Player(x1, y1, playerNo, team)
	{
		walkSpeed = 2.5f;
		runSpeed = 4.6f;
		fallWalk = 1.7f;
		fallRun = 3;
		
		finishSideB = 0;
		finishFinalsmash = 0;
		finalsmashTransition = 0;
		upBDir = 0;
		upBCount = 0;
		transUpB = false;
		winding = false;
		awaitingStrike = false;
		finalsmash = false;
		
		weight = 0.12;
		
		name = "Pikachu";
		
		setScale(1.0f);
		
		xprevious = x;
		yprevious = y;
		
		setHitbox(-10, -6, 20, 28);
		setHitboxColor(Color::GREEN);
		//showHitboxWireframe(true);
		//setWireframeColor(Color.red);
		//showWireframe(true);
		
		setHangPoint(2, 8);

		chargingSideB = false;
		
		Console::WriteLine((String)"finished creating player " + playerNo);
	}
	
	Pikachu::~Pikachu()
	{
		//
	}
	
	void Pikachu::setToDefaultValues()
	{
		chargingSideB = false;
		upBDir = 0;
		upBCount = 0;
		transUpB = false;
		awaitingStrike = false;
		preppingDownB = false;
		winding = false;
	}
	
	void Pikachu::onDestroy()
	{
		finalsmash = false;
	}
	
	boolean Pikachu::checkIfAble()
	{
		if(transUpB || chargingSideB || preppingDownB || winding)
		{
			return false;
		}
		return true;
	}
	
	void Pikachu::Load()
	{
		setFolderPath("Images/Game/Characters/Pikachu/");

		loadFile("Images/Game/Characters/Pikachu/thunderbolt.png");
		loadFile("Images/Game/Characters/Pikachu/lightning_1.png");
		loadFile("Images/Game/Characters/Pikachu/lightning_2.png");
		loadFile("Images/Game/Characters/Pikachu/lightning_end_1.png");
		loadFile("Images/Game/Characters/Pikachu/lightning_end_2.png");
		loadFile("Images/Game/Characters/Pikachu/lightning_head.png");
		loadFile("Images/Game/Characters/Pikachu/lightning_cloud.png");

		addTwoSidedAnimation("stand", "stand.png", 4, 4, 1);
		addTwoSidedAnimation("walk", "walk.png", 6, 4, 1);
		addTwoSidedAnimation("run", "run.png", 8, 4, 1);
		addTwoSidedAnimation("jump", "jump.png", 8, 5, 1);
		addTwoSidedAnimation("jump2", "jump2.png", 16, 8, 1);
		addTwoSidedAnimation("land", "land.png", 8, 2, 1);
		addTwoSidedAnimation("fall", "fall.png", 10, 2, 1);
		addTwoSidedAnimation("hang", "hang.png", 1, 1, 1);
		addTwoSidedAnimation("crouch", "crouch.png", 1, 1, 1);
		addTwoSidedAnimation("grab", "grab.png", 18, 5, 1);
		addTwoSidedAnimation("grabbed", "grabbed.png", 30, 1, 1);
		addTwoSidedAnimation("hold", "hold.png", 30, 1, 1);
		addTwoSidedAnimation("release", "release.png", 12, 3, 1);
		addTwoSidedAnimation("toss", "toss.png", 12, 3, 1);
		addTwoSidedAnimation("toss_up", "toss_up.png", 12, 3, 1);
		addTwoSidedAnimation("toss_down", "toss_down.png", 12, 3, 1);
		addTwoSidedAnimation("grab_attack", "grab_attack.png", 10, 3, 1);
		addTwoSidedAnimation("grab_attack_swing", "grab_attack_swing.png", 12, 4, 1);
		addTwoSidedAnimation("melee_weapon", "melee_weapon.png", 12, 4, 1);
		addTwoSidedAnimation("melee_weapon_up", "melee_weapon_up.png", 10, 3, 1);
		addTwoSidedAnimation("melee_weapon_down", "melee_weapon_down.png", 10, 3, 1);
		addTwoSidedAnimation("hurt_minor", "hurt_minor.png", 1, 1, 1);
		addTwoSidedAnimation("hurt_fly", "hurt_fly.png", 1, 1, 1);
		addTwoSidedAnimation("hurt_flip", "hurt_flip.png", 18, 8, 1);
		addTwoSidedAnimation("hurt_spin", "hurt_spin.png", 10, 4, 1);
		addSingleAnimation("hurt_spin_up", "hurt_spin_up.png", 10, 4, 1);
		addTwoSidedAnimation("dash_attack", "dash_attack.png", 8, 3, 1);
		addTwoSidedAnimation("standard_attack", "standard_attack.png", 16, 3, 1);
		addTwoSidedAnimation("standard_attack_side", "standard_attack_side.png", 12, 5, 1);
		addTwoSidedAnimation("standard_attack_up", "standard_attack_up.png", 16, 7, 1);
		addTwoSidedAnimation("standard_attack_down", "standard_attack_down.png", 18, 8, 1);
		addTwoSidedAnimation("air_attack", "air_attack.png", 26, 10, 1);
		addTwoSidedAnimation("air_attack_side", "air_attack_side.png", 20, 11, 1);
		addTwoSidedAnimation("air_attack_up", "air_attack_up.png", 16, 7, 1);
		addTwoSidedAnimation("air_attack_down", "air_attack_down.png", 30, 16, 1);
		addTwoSidedAnimation("special_attack", "special_attack.png", 14, 7, 1);
		addTwoSidedAnimation("special_charge_side", "special_charge_side.png", 6, 4, 1);
		addTwoSidedAnimation("special_attack_side", "special_attack_side.png", 12, 4, 1);
		addTwoSidedAnimation("special_land_side", "special_land_side.png", 8, 4, 1);
		addTwoSidedAnimation("special_transition_up", "special_transition_up.png", 14, 3, 1);
		addTwoSidedAnimation("special_prep_up", "special_prep_up.png", 14, 4, 1);
		addTwoSidedAnimation("special_attack_down", "special_attack_down.png", 12, 10, 1);
		addTwoSidedAnimation("special_hold_down", "special_hold_down.png", 12, 2, 1);
		addTwoSidedAnimation("special_finish_down", "special_finish_down.png", 12, 5, 1);
		addTwoSidedAnimation("smash_charge", "smash_charge.png", 6, 4, 1);
		addTwoSidedAnimation("smash_prep", "smash_prep.png", 22, 3, 1);
		addTwoSidedAnimation("smash_attack", "smash_attack.png", 22, 9, 1);
		addTwoSidedAnimation("smash_finish", "smash_finish.png", 20, 3, 1);
		addTwoSidedAnimation("smash_prep_up", "smash_prep_up.png", 18, 4, 1);
		addTwoSidedAnimation("smash_attack_up", "smash_attack_up.png", 22, 4, 1);
		addTwoSidedAnimation("smash_finish_up", "smash_finish_up.png", 18, 3, 1);
		addTwoSidedAnimation("smash_prep_down", "smash_prep_down.png", 14, 2, 1);
		addTwoSidedAnimation("smash_attack_down", "smash_attack_down.png", 14, 8, 1);
		addTwoSidedAnimation("smash_finish_down", "smash_finish_down.png", 14, 3, 1);
		addSingleAnimation("finalsmash", "volt_tackle.png", 8, 4, 1);
		addTwoSidedAnimation("finalsmash_begin", "volt_tackle_transition.png", 12, 6, 1);
		
		Animation*anim;
		
		ArrayList<int> seq;
		for(int i=5; i>=0; i--)
		{
			seq.add(i);
		}
		
		anim = new Animation("finalsmash_end_left", 12, 6, 1, seq);
		anim->addFrame(getFolderPath() + "volt_tackle_transition.png");
		addAnimation(anim);
		
		anim = new Animation("finalsmash_end_right", 12, 6, 1, seq);
		anim->addFrame(getFolderPath() + "volt_tackle_transition.png");
		anim->mirror(true);
		addAnimation(anim);
		
		anim = new Animation("special_attack_up_side_left", 14);
		anim->addFrame(getFolderPath() + "special_attack_up_side.png");
		addAnimation(anim);
		
		anim = new Animation("special_attack_up_side_right", 14);
		anim->addFrame(getFolderPath() + "special_attack_up_side.png");
		anim->mirror(true);
		addAnimation(anim);
		
		anim = new Animation("special_attack_up_up_left", 14);
		anim->addFrame(getFolderPath() + "special_attack_up_up.png");
		addAnimation(anim);
		
		anim = new Animation("special_attack_up_up_right", 14);
		anim->addFrame(getFolderPath() + "special_attack_up_up.png");
		anim->mirror(true);
		addAnimation(anim);
		
		anim = new Animation("special_attack_up_down_left", 14);
		anim->addFrame(getFolderPath() + "special_attack_up_up.png");
		anim->mirror(true);
		anim->mirrorVertical(true);
		addAnimation(anim);
		
		anim = new Animation("special_attack_up_down_right", 14);
		anim->addFrame(getFolderPath() + "special_attack_up_up.png");
		anim->mirrorVertical(true);
		addAnimation(anim);
		
		anim = new Animation("special_attack_up_upside_left", 14);
		anim->addFrame(getFolderPath() + "special_attack_up_upside.png");
		addAnimation(anim);
		
		anim = new Animation("special_attack_up_upside_right", 14);
		anim->addFrame(getFolderPath() + "special_attack_up_upside.png");
		anim->mirror(true);
		addAnimation(anim);
		
		anim = new Animation("special_attack_up_downside_left", 14);
		anim->addFrame(getFolderPath() + "special_attack_up_downside.png");
		addAnimation(anim);
		
		anim = new Animation("special_attack_up_downside_right", 14);
		anim->addFrame(getFolderPath() + "special_attack_up_downside.png");
		anim->mirror(true);
		addAnimation(anim);
	}
	
	void Pikachu::LoadAttackTypes()
	{
		addAIAttackType(ATTACK_A,		   ATTACKTYPE_MELEE, 5);
		addAIAttackType(ATTACK_SIDEA,	   ATTACKTYPE_MELEE, 4);
		addAIAttackType(ATTACK_UPA,	       ATTACKTYPE_UPMELEE, 3);
		addAIAttackType(ATTACK_DOWNA,	   ATTACKTYPE_DOWNMELEE, 1);
		addAIAttackType(ATTACK_DOWNA,	   ATTACKTYPE_MELEE, 2);
		addAIAttackType(ATTACK_B,		   ATTACKTYPE_PROJECTILE, 1);
		addAIAttackType(ATTACK_SIDEB,	   ATTACKTYPE_SIDEMOVE, 1);
		addAIAttackType(ATTACK_UPB,	       ATTACKTYPE_STRONGMELEE, 1);
		addAIAttackType(ATTACK_UPB,	       ATTACKTYPE_UPMOVE, 1);
		addAIAttackType(ATTACK_DOWNB,	   ATTACKTYPE_STRONGMELEE, 2);
		addAIAttackType(ATTACK_SIDESMASH,  ATTACKTYPE_STRONGMELEE, 2, true);
		addAIAttackType(ATTACK_UPSMASH,    ATTACKTYPE_STRONGMELEE, 1, true);
		addAIAttackType(ATTACK_DOWNSMASH,  ATTACKTYPE_STRONGMELEE, 1, true);
		addAIAttackType(ATTACK_FINALSMASH, ATTACKTYPE_PROJECTILE, 1);
	}

	void Pikachu::Unload()
	{
		Player::Unload();
	}
	
	void Pikachu::addP2PData(DataVoid&data)
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
				
				if(proj.type==2 || proj.type==3)
				{
					data.add(&proj.itemdir, sizeof(proj.itemdir));
					data.add(&proj.ownerID, sizeof(proj.ownerID));
				}
			}
			createdProjectiles.clear();
		}
		else
		{
			bool avail = false;
			data.add(&avail, sizeof(avail));
		}
	}
	
	void Pikachu::setP2PData(byte*&data)
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
						createProjectile(new Lightning(getPlayerNo(), x1, y1));
					}
					break;
					
					case 2:
					{
						byte itemdir = data[0];
						data += sizeof(byte);
						int ownerID = DataVoid::toInt(data);
						data += sizeof(int);
						Projectile* projOwner = ProjectileManager::GetProjectile(ownerID);
						
						Projectile::setNextID(projID);
						createProjectile(new Thunderbolt::ThunderboltGhost((Thunderbolt*)projOwner, getPlayerNo(), itemdir, false, x1, y1));
					}
					break;
					
					case 3:
					{
						boolean frameOn = DataVoid::toBool(data);
						data += sizeof(bool);
						int ownerID = DataVoid::toInt(data);
						data += sizeof(int);
						Projectile* projOwner = ProjectileManager::GetProjectile(ownerID);
						
						Projectile::setNextID(projID);
						createProjectile(new Lightning::LightningBody((Lightning*)projOwner, getPlayerNo(), x1, y1, frameOn));
					}
					break;
					
					case 4:
					{
						Projectile::setNextID(projID);
						createProjectile(new Thunderbolt(getPlayerNo(), x1, y1));
					}
					break;
				}
			}
		}
	}

	void Pikachu::Update(long gameTime)
	{
		if(attacksHolder==6)
		{
			if((xvelocity * getPlayerDirMult()) > 0)
			{
				xvelocity -= 0.02f * getPlayerDirMult();
			}
			if(Global::getWorldTime()>=nextHitTime)
			{
				nextHitTime = Global::getWorldTime() + 10;
				resetAttackCollisions();
			}
		}
		else if(attacksHolder==10)
		{
			if(finishSideB<=Global::getWorldTime())
			{
				attacksHolder = -1;
				attacksPriority = 0;
			}
		}
		else if(attacksHolder==12)
		{
			if(!awaitingStrike)
			{
				attacksHolder = -1;
				attacksPriority = 0;
				changeTwoSidedAnimation("special_finish_down", FORWARD);
			}
		}
		else if(attacksHolder==15)
		{
			String animName = getAnimName();
			if(animName.equals("smash_attack_down_left"))
			{
				int frameNo = getCurrentFrame();
				if(frameNo==1 || frameNo==5)
				{
					if(playerdir==RIGHT)
					{
						resetAttackCollisions();
					}
					playerdir=LEFT;
				}
				else if(frameNo==3 || frameNo==7)
				{
					if(playerdir==LEFT)
					{
						resetAttackCollisions();
					}
					playerdir=RIGHT;
				}
			}
			else if(animName.equals("smash_attack_down_right"))
			{
				int frameNo = getCurrentFrame();
				if(frameNo==1 || frameNo==5)
				{
					if(playerdir==LEFT)
					{
						resetAttackCollisions();
					}
					playerdir=RIGHT;
				}
				else if(frameNo==3 || frameNo==7)
				{
					if(playerdir==RIGHT)
					{
						resetAttackCollisions();
					}
					playerdir=LEFT;
				}
			}
		}

		if(attacksHolder==1 || transUpB)
		{
			yvelocity = 0;
		}

		if(finalsmash)
		{
			if(isHanging())
			{
				setHanging(false);
				x = xprevious;
				y = yprevious;
			}

			attacksHolder = 16;
			attacksPriority = 7;

			if(finalsmashTransition==0)
			{
				changeAnimation("finalsmash", NO_CHANGE);

				if(moveLeft == 1)
				{
					if(xVel > -finalsmashSlow)
					{
						xVel -= 0.5;
					}
				}
				else if(moveLeft == 2)
				{
					if(xVel > -finalsmashFast)
					{
						xVel -= 0.5;
					}
				}

				if(moveRight == 1)
				{
					if(xVel < finalsmashSlow)
					{
						xVel += 0.5;
					}
				}
				else if(moveRight == 2)
				{
					if(xVel < finalsmashFast)
					{
						xVel += 0.5;
					}
				}

				if(upKey)
				{
					if(yVel > -finalsmashSlow)
					{
						yVel -= 0.5;
					}
				}
				else if(down)
				{
					if(yVel < finalsmashSlow)
					{
						yVel += 0.5;
					}
				}

				if(moveLeft==0 && moveRight==0)
				{
					if(xVel > 0)
					{
						xVel -= 0.5;
					}
					else if(xVel < 0)
					{
						xVel += 0.5;
					}
				}
				if(!upKey && !down)
				{
					if(yVel > 0)
					{
						yVel -= 0.5;
					}
					else if(yVel < 0)
					{
						yVel += 0.5;
					}
				}

				if(finishFinalsmash<=Global::getWorldTime())
				{
					finishFinalsmash = 0;
					finalsmashTransition = 2;
					changeTwoSidedAnimation("finalsmash_end", FORWARD);
				}
			}
			else if(finalsmashTransition == 1)
			{
				changeTwoSidedAnimation("finalsmash_begin", NO_CHANGE);
			}
			else if(finalsmashTransition == 2)
			{
				xVel = 0;
				yVel = 0;
				xvelocity = 0;
				yvelocity = 0;
				changeTwoSidedAnimation("finalsmash_end", NO_CHANGE);
			}

			Player::Update(gameTime);
		}
		else
		{
			Player::Update(gameTime);

			updateGravity();
			updateFrame();
			
			updateMovement();
			
			updateHanging();
		}

		updateHurt();
		updateDrop();
		
		updateAI();

		xprevious = x;
		yprevious = y;
	}

	void Pikachu::Draw(Graphics2D&g, long gameTime)
	{
		Player::Draw(g, gameTime);
	}

	void Pikachu::onAnimationFinish(const String&name)
	{
		if(name.equals("special_charge_side_left") || name.equals("special_charge_side_right")
		|| name.equals("special_hold_down_left") || name.equals("special_hold_down_right")
		|| name.equals("finalsmash"))
		{
			//
		}
		else if(name.equals("special_attack_side_left") || name.equals("special_attack_side_right"))
		{
			if(isOnGround())
			{
				Player::onAnimationFinish(name);
			}
		}
		else if(name.equals("special_prep_up_left") || name.equals("special_prep_up_right"))
		{
			landing = false;
			byte goDir = getDirFacing();
			upBIncrement(goDir);
		}
		else if(name.equals("special_attack_up_up_left") || name.equals("special_attack_up_up_right")
			|| name.equals("special_attack_up_side_left") || name.equals("special_attack_up_side_right")
			|| name.equals("special_attack_up_down_left") || name.equals("special_attack_up_down_right")
			|| name.equals("special_attack_up_upside_left") || name.equals("special_attack_up_upside_right")
			|| name.equals("special_attack_up_downside_left") || name.equals("special_attack_up_downside_right"))
		{
			attacksHolder = -1;
			attacksPriority = 0;

			BufferedImage*image = AssetManager::getImage(getAnimation()->getAllFilenames().get(0));
			switch(upBDir)
			{
				case DIR_UP:
				y = y - (image->getHeight()/2);
				break;

				case DIR_UPLEFT:
				y = y - (image->getHeight()/2);
				x = x - (image->getWidth()/2);
				break;

				case DIR_UPRIGHT:
				y = y - (image->getHeight()/2);
				x = x + (image->getWidth()/2);
				break;

				case DIR_LEFT:
				x = x - (image->getWidth()/2);
				break;

				case DIR_RIGHT:
				x = x + (image->getWidth()/2);
				break;

				case DIR_DOWNLEFT:
				y = y + (image->getHeight()/2);
				x = x - (image->getWidth()/2);
				break;

				case DIR_DOWNRIGHT:
				y = y + (image->getHeight()/2);
				x = x + (image->getWidth()/2);
				break;

				case DIR_DOWN:
				y = y + (image->getHeight()/2);
				break;
			}

			transUpB = true;
			
			changeTwoSidedAnimation("special_transition_up", FORWARD);
		}
		else if(name.equals("special_transition_up_left") || name.equals("special_transition_up_right"))
		{
			bUp = true;
			transUpB = false;

			byte goDir = getDirFacing();

			if(goDir==upBDir || upBCount>=2)
			{
				Player::onAnimationFinish(name);
			}
			else
			{
				upBIncrement(goDir);
			}
		}
		else if(name.equals("special_attack_down_left") || name.equals("special_attack_down_right"))
		{
			awaitingStrike = true;
			preppingDownB = false;
			attacksHolder = 12;
			attacksPriority = 0;
			changeTwoSidedAnimation("special_hold_down", FORWARD);
			
			Lightning* lightning = new Lightning(getPlayerNo(), x, y);
			createProjectile(lightning);
			addProjectileInfo(1, lightning->getID(), x, y, 0, 0);
		}
		else if(name.equals("smash_prep_left") || name.equals("smash_prep_right"))
		{
			winding = false;
			AttackTemplates::normalSmash(this,13,3.05,STEP_GO,1,2000,20,28);
		}
		else if(name.equals("smash_prep_up_left") || name.equals("smash_prep_up_right"))
		{
			winding = false;
			AttackTemplates::normalSmash(this,14,2.08,STEP_GO,2,1800,14,20);
		}
		else if(name.equals("smash_prep_down_left") || name.equals("smash_prep_down_right"))
		{
			winding = false;
			AttackTemplates::normalSmash(this,15,2.48,STEP_GO,3,1600,16,24);
		}
		else if(name.equals("smash_attack_left") || name.equals("smash_attack_right"))
		{
			attacksHolder = -1;
			attacksPriority = 0;
			winding = true;
			changeTwoSidedAnimation("smash_finish", FORWARD);
		}
		else if(name.equals("smash_attack_up_left") || name.equals("smash_attack_up_right"))
		{
			attacksHolder = -1;
			attacksPriority = 0;
			winding = true;
			changeTwoSidedAnimation("smash_finish_up", FORWARD);
		}
		else if(name.equals("smash_attack_down_left"))
		{
			attacksHolder = -1;
			attacksPriority = 0;
			winding = true;
			playerdir = LEFT;
			changeAnimation("smash_finish_down_left", FORWARD);
		}
		else if(name.equals("smash_attack_down_right"))
		{
			attacksHolder = -1;
			attacksPriority = 0;
			winding = true;
			playerdir = RIGHT;
			changeAnimation("smash_finish_down_right", FORWARD);
		}
		else if(name.equals("finalsmash_begin_left") || name.equals("finalsmash_begin_right"))
		{
			finalsmashTransition = 0;
			finishFinalsmash = Global::getWorldTime() + 10000;
			changeAnimation("finalsmash", FORWARD);
		}
		else if(name.equals("finalsmash_end_left") || name.equals("finalsmash_end_right"))
		{
			finalsmashTransition = 0;
			finalsmash = false;
			attacksHolder = -1;
			attacksPriority = 0;
			animFinish();
		}
		else
		{
			Player::onAnimationFinish(name);
		}
	}

	void Pikachu::jump()
	{
		Player::jump(5.1f, 4.7f);
	}
	
	void Pikachu::onPlayerHit(Player*collide, byte dir)
	{
		byte relDir = getRelPlayerDir(collide);
		if(relDir==getPlayerDir() || relDir==0)
		{
			switch(attacksHolder)
			{
				case 0:
				//A
				if(hitAmount==0)
				{
					causeDamage(collide,2);
					collide->y -= 4;
					collide->x -= 2 * getPlayerDirMult();
					x += 1 * getPlayerDirMult();
					causeHurt(collide, getOppPlayerDir(), 100);
					hitAmount++;
				}
				break;
				
				case 13:
				//Smash left
				causeDamage(collide,smashPower);
				collide->x += 5 * getPlayerDirMult();
				causeHurtLaunch(collide, (int)getPlayerDirMult(),((float)smashPower/5),4, -1,((float)smashPower/6), 4);
				causeHurt(collide, getOppPlayerDir(), 400);
				break;
			}
		}
		
		if(attacksHolder==15)
		{
			String animName = getAnimName();
			if(animName.equals("smash_attack_down_left") || animName.equals("smash_attack_down_right"))
			{
				int frameNo = getCurrentFrame();
				if(frameNo<7)
				{
					causeDamage(collide,smashPower/4);
					collide->yvelocity = -1;
					collide->y -= (5*getScale()*collide->getScale());
					collide->x = x - (5*getScale() * getPlayerDirMult());
					causeHurt(collide, getOppPlayerDir(), 200);
				}
				else if(frameNo == 7)
				{
					causeDamage(collide,smashPower/4);
					causeHurtLaunch(collide, -(int)getPlayerDirMult(),2.65f,3.87f, -1, 1.95f,3.87f);
					causeHurt(collide, getPlayerDir(), 300);//Nafe was here
				}
			}
		}
		else if(attacksHolder==16) //final smash
		{
			float dist = (float)distance(x,y,collide->x,collide->y);
			float cosVal = (collide->x - x)/dist;
			float sinVal = (collide->y - y)/dist;
			
			float velMag = sqrt((xvelocity*xvelocity) + (yvelocity*yvelocity));
			float speedAmount = velMag/finalsmashFast;
			
			causeDamage(collide, 10 + (int)(10*speedAmount));
			
			float hitXvel = std::abs(cosVal*8);
			float hitYvel = std::abs(sinVal*8);
			
			int xDir = 1;
			if(cosVal<0)
			{
				xDir = -1;
			}
			int yDir = 1;
			if(sinVal<0)
			{
				yDir = -1;
			}
			
			causeHurtLaunch(collide, xDir,hitXvel,2.8f, yDir,hitYvel,2.8f);
			
			if(collide->x < x)
			{
				causeHurt(collide, RIGHT, 300);
			}
			else
			{
				causeHurt(collide, LEFT, 300);
			}
		}
		
		switch(dir)
		{
			case DIR_LEFT:
			case DIR_RIGHT:
			{
				switch(attacksHolder)
				{
					case 6:
					//A Air Side
					nextHitTime = Global::getWorldTime() + 100;
					break;
					
					case 10:
					//B Side
					{
						byte relDir = getRelPlayerDir(collide);
						if(compareDirPlayerDir(dir, getPlayerDir())==CMPDIRPDIR_EQUAL && relDir==getPlayerDir() && relDir==0)
						{
							float amount = (float)smashPower/100;
							causeDamage(collide,(int)(38*amount) + 2);
							causeHurtLaunch(collide, (int)getPlayerDirMult(),10*amount+2,3, -1,5*amount+1,3);
							causeHurt(collide, getOppPlayerDir(), 200);
						}
					}
					break;
					
					case 14:
					//Smash up
					causeDamage(collide,smashPower);
					collide->y -= 3;
					causeHurtLaunch(collide, (int)getPlayerDirMult(),0,1, -1,((float)smashPower/5), 5);
					causeHurt(collide, getOppPlayerDir(), 300);
					break;
				}
			}
			break;
			
			case DIR_UP:
			switch(attacksHolder)
			{
				case 14:
				//Smash up
				causeDamage(collide,smashPower);
				collide->y -= 3;
				causeHurtLaunch(collide, (int)getPlayerDirMult(),0,1, -1,((float)smashPower/4), 5);
				causeHurt(collide, getOppPlayerDir(), 300);
				break;
			}
			break;
			
			case DIR_DOWN:
			break;
		}
	}

	void Pikachu::onGroundCollide()
	{
		Player::onGroundCollide();
		if(attacksHolder == 4 || attacksHolder == 10)
		{
			attacksHolder = -1;
			attacksPriority = 0;
			changeTwoSidedAnimation("special_land_side", FORWARD);
			landing = true;
		}
	}
	
	void Pikachu::doChargingAttack(byte button)
	{
		if(chargingSideB)
		{
			destroyCharge();
			float amount = (float)smashPower/100;
			
			chargingSideB = false;
			landing = false;
			bUp = true;
			setOnGround(false);
			
			attacksHolder = 10;
			attacksPriority = 3.5f*amount + 0.5f;
			xvelocity = (8*amount + 1) * getPlayerDirMult();
			changeTwoSidedAnimation("special_attack_side", FORWARD);
			
			yvelocity = -2.5f*amount - 2;
			y-=2;
			
			finishSideB = Global::getWorldTime() + 600;
		}
	}
	
	void Pikachu::onFinishCharge()
	{
		if(chargingSideB)
		{
			destroyCharge();
			float amount = (float)smashPower/100;
			
			chargingSideB = false;
			landing = false;
			bUp = true;
			setOnGround(false);
			
			attacksHolder = 10;
			attacksPriority = 3.5f*amount + 0.5f;
			xvelocity = (8*amount + 1) * getPlayerDirMult();
			changeTwoSidedAnimation("special_attack_side", FORWARD);
			
			yvelocity = -2.5f*amount - 2;
			y-=2;
			
			finishSideB = Global::getWorldTime() + 600;
		}
	}
	
	void Pikachu::upBIncrement(byte dir)
	{
		switch(dir)
		{
			default:
			//
			
			case DIR_UP:
			if(upBDir != DIR_UP)
			{
				changeTwoSidedAnimation("special_attack_up_up", FORWARD);
				BufferedImage*image = AssetManager::getImage(getAnimation()->getAllFilenames().get(0));
				xvelocity = 0;
				yvelocity = 0;
				y = y-(image->getHeight()/2);
				upBDir = DIR_UP;
				attacksHolder = 11;
				attacksPriority = 4;
			}
			break;
			
			case DIR_UPLEFT:
			if(upBDir != DIR_UPLEFT)
			{
				playerdir = LEFT;
				changeAnimation("special_attack_up_upside_left", FORWARD);
				BufferedImage*image = AssetManager::getImage(getAnimation()->getAllFilenames().get(0));
				xvelocity = 0;
				yvelocity = 0;
				y = y-(image->getHeight()/2);
				x = x-(image->getWidth()/2);
				upBDir = DIR_UPLEFT;
				attacksHolder = 11;
				attacksPriority = 4;
			}
			break;
			
			case DIR_DOWNLEFT:
			if(upBDir != DIR_DOWNLEFT)
			{
				playerdir = LEFT;
				changeAnimation("special_attack_up_downside_left", FORWARD);
				BufferedImage*image = AssetManager::getImage(getAnimation()->getAllFilenames().get(0));
				xvelocity = 0;
				yvelocity = 0;
				y = y+(image->getHeight()/2);
				x = x-(image->getWidth()/2);
				upBDir = DIR_DOWNLEFT;
				attacksHolder = 11;
				attacksPriority = 4;
			}
			break;
			
			case DIR_LEFT:
			if(upBDir != DIR_LEFT)
			{
				playerdir = LEFT;
				changeAnimation("special_attack_up_side_left", FORWARD);
				BufferedImage*image = AssetManager::getImage(getAnimation()->getAllFilenames().get(0));
				xvelocity = 0;
				yvelocity = 0;
				x = x-(image->getWidth()/2);
				upBDir = DIR_LEFT;
				attacksHolder = 11;
				attacksPriority = 4;
			}
			break;
			
			case DIR_UPRIGHT:
			if(upBDir != DIR_UPRIGHT)
			{
				playerdir = RIGHT;
				changeAnimation("special_attack_up_upside_right", FORWARD);
				BufferedImage*image = AssetManager::getImage(getAnimation()->getAllFilenames().get(0));
				xvelocity = 0;
				yvelocity = 0;
				y = y-(image->getHeight()/2);
				x = x+(image->getWidth()/2);
				upBDir = DIR_UPRIGHT;
				attacksHolder = 11;
				attacksPriority = 4;
			}
			break;
			
			case DIR_DOWNRIGHT:
			if(upBDir != DIR_UPLEFT)
			{
				playerdir = RIGHT;
				changeAnimation("special_attack_up_downside_right", FORWARD);
				BufferedImage*image = AssetManager::getImage(getAnimation()->getAllFilenames().get(0));
				xvelocity = 0;
				yvelocity = 0;
				y = y+(image->getHeight()/2);
				x = x+(image->getWidth()/2);
				upBDir = DIR_DOWNRIGHT;
				attacksHolder = 11;
				attacksPriority = 4;
			}
			break;
			
			case DIR_RIGHT:
			if(upBDir != DIR_RIGHT)
			{
				playerdir = RIGHT;
				changeAnimation("special_attack_up_side_right", FORWARD);
				BufferedImage*image = AssetManager::getImage(getAnimation()->getAllFilenames().get(0));
				xvelocity = 0;
				yvelocity = 0;
				x = x+(image->getWidth()/2);
				upBDir = DIR_RIGHT;
				attacksHolder = 11;
				attacksPriority = 4;
			}
			break;
			
			case DIR_DOWN:
			if(upBDir != DIR_DOWN)
			{
				changeTwoSidedAnimation("special_attack_up_down", FORWARD);
				BufferedImage*image = AssetManager::getImage(getAnimation()->getAllFilenames().get(0));
				xvelocity = 0;
				yvelocity = 0;
				y = y+(image->getHeight()/2);
				upBDir = DIR_DOWN;
				attacksHolder = 11;
				attacksPriority = 4;
			}
			break;
		}
		upBCount++;
	}
	
	void Pikachu::attackA()
	{
		addAttackInfo(DIR_LEFT, 5, LEFT, 12, 300, -1,2.1f,3.3f, -1,2.1f,3.3f);
		addAttackInfo(DIR_RIGHT,5, LEFT, 12, 300,  1,1.8f,2.9f, -1,1.8f,2.2f);
		addAttackInfo(DIR_LEFT, 5, RIGHT,12, 300, -1,1.8f,2.9f, -1,1.8f,2.2f);
		addAttackInfo(DIR_RIGHT,5, RIGHT,12, 300,  1,2.1f,3.3f, -1,2.1f,3.3f);
		if(!checkItemUse())
		{
			if(isOnGround())
			{
				AttackTemplates::normalA(this, 0,1.45);
			}
			else
			{
				if(!bUp)
				{
					AttackTemplates::normalAirA(this, 5,1.696);
				}
			}
		}
	}
	
	void Pikachu::attackSideA()
	{
		addAttackInfo(DIR_LEFT, 1, LEFT, 9, 200, -1,2.4f,2.8f, -1,1.6f,3.0f);
		addAttackInfo(DIR_RIGHT,1,RIGHT, 9, 200,  1,2.4f,2.8f, -1,1.6f,3.0f);
		addAttackInfo(DIR_LEFT, 4, LEFT, 9, 100, -1,2.6f,2.6f, -1,1.6f,2.6f);
		addAttackInfo(DIR_RIGHT,4,RIGHT, 9, 100,  1,2.6f,2.6f, -1,1.6f,2.6f);
		addAttackInfo(DIR_LEFT, 6, LEFT, 2, 100, -1,1.4f,3.4f, -1,1.2f,1.4f);
		addAttackInfo(DIR_RIGHT,6,RIGHT, 2, 100,  1,1.4f,3.4f, -1,1.2f,1.4f);
		if(((moveLeft==2) || (moveRight==2)) && (isOnGround()))
		{
			y-=6;
			AttackTemplates::normalDashA(this, 4,1.87, 0);
			xvelocity = 5.0f * getPlayerDirMult();
			yvelocity = -2;
		}
		else if(!checkItemUseSide())
		{
			if(isOnGround())
			{
				AttackTemplates::normalSideA(this, 1,1.87);
			}
			else
			{
				if(!bUp)
				{
					xvelocity = 4 * getPlayerDirMult();
					AttackTemplates::normalAirSideA(this, 6,2.476);
				}
			}
		}
	}
	
	void Pikachu::attackUpA()
	{
		addAttackInfo(DIR_LEFT, 2, LEFT, 7, 300, -1,0.8f,1.1f, -1,2.1f,2.8f);
		addAttackInfo(DIR_LEFT, 2,RIGHT, 7, 300,  1,0.8f,1.1f, -1,2.1f,2.8f);
		addAttackInfo(DIR_RIGHT,2, LEFT, 7, 300, -1,0.8f,1.1f, -1,2.1f,2.8f);
		addAttackInfo(DIR_RIGHT,2,RIGHT, 7, 300,  1,0.8f,1.1f, -1,2.1f,2.8f);
		addAttackInfo(DIR_UP, 2,RIGHT, 7, 300,  1,0,0, -1,2.2f,3.0f);
		addAttackInfo(DIR_UP, 2, LEFT, 7, 300, -1,0,0, -1,2.2f,3.0f);
		addAttackInfo(DIR_LEFT, 7, LEFT, 8, 200, -1,2.6f,3.1f, -1,1.4f,2.1f);
		addAttackInfo(DIR_RIGHT,7,RIGHT, 8, 200,  1,2.6f,3.1f, -1,1.4f,2.1f);
		addAttackInfo(DIR_UP, 7, LEFT, 8, 200, -1,0.4f,1.1f, -1,2.6f,3.1f);
		addAttackInfo(DIR_UP, 7,RIGHT, 8, 200,  1,0.4f,1.1f, -1,2.6f,3.1f);
		
		if(!checkItemUseUp())
		{
			if(isOnGround())
			{
				AttackTemplates::normalUpA(this, 2,2.67);
			}
			else
			{
				if(!bUp)
				{
					AttackTemplates::normalAirUpA(this, 7,1.2);
				}
			}
		}
	}

	void Pikachu::attackDownA()
	{
		addAttackInfo(DIR_LEFT, 3, LEFT, 7, 400, -1,2.1f,1.1f, -1,2.0f,3.0f);
		addAttackInfo(DIR_RIGHT,3,RIGHT, 7, 400,  1,2.1f,1.1f, -1,2.0f,3.0f);
		addAttackInfo(DIR_LEFT, 8, LEFT, 9, 300, -1,1.7f,2.7f, 1,3.0f,3.3f);
		addAttackInfo(DIR_RIGHT,8,RIGHT, 9, 300,  1,1.7f,2.7f, 1,3.0f,3.3f);
		addAttackInfo(DIR_DOWN, 8, LEFT, 12,300, -1,1.1f,1.7f, 1,3.8f,3.5f);
		addAttackInfo(DIR_DOWN, 8,RIGHT, 12,300,  1,1.1f,1.7f, 1,3.8f,3.5f);
		
		if(!checkItemUseDown())
		{
			if(isOnGround())
			{
				AttackTemplates::normalDownA(this, 3,2.92);
			}
			else
			{
				if(bUp==0)
				{
					AttackTemplates::normalAirDownA(this, 8,1.2);
				}
			}
		}
	}
	
	void Pikachu::attackB()
	{
		if(!bUp)
	    {
	        if((canFinalSmash())&&(isOnGround()))
	        {
	            attackFinalSmash();
	        }
	        else
	        {
				Thunderbolt* thunderbolt = new Thunderbolt(getPlayerNo(),x,y);
	        	AttackTemplates::singleProjectile(this, 9,0, thunderbolt);
				addProjectileInfo(4, thunderbolt->getID(), x, y, 0, 0);
	            changeTwoSidedAnimation("special_attack",FORWARD);
	        }
	    }
	}
	
	void Pikachu::attackSideB()
	{
		if(!bUp)
	    {
	        chargingSideB = true;
			landing = true;
			AttackTemplates::chargeB(this, 0, 100, 3800);
			changeTwoSidedAnimation("special_charge_side", FORWARD);
	    }
	}
	
	void Pikachu::attackUpB()
	{
		addAttackInfo(DIR_LEFT, 11, LEFT, 2, 300, -1,0.4f,1.6f, -1,2.0f,2.1f);
		addAttackInfo(DIR_LEFT, 11, RIGHT,2, 300,  1,0.4f,1.6f, -1,2.0f,2.1f);
		addAttackInfo(DIR_RIGHT,11, LEFT, 2, 300, -1,0.4f,1.6f, -1,2.0f,2.1f);
		addAttackInfo(DIR_RIGHT,11, RIGHT,2, 300,  1,0.4f,1.6f, -1,2.0f,2.1f);
		addAttackInfo(DIR_DOWN, 11, LEFT, 2, 300, -1,0.4f,1.6f, -1,2.0f,2.1f);
		addAttackInfo(DIR_DOWN, 11, RIGHT,2, 300,  1,0.4f,1.6f, -1,2.0f,2.1f);
		addAttackInfo(DIR_UP,   11, LEFT, 2, 300, -1,0.4f,1.6f, -1,2.0f,2.1f);
		addAttackInfo(DIR_UP,   11, RIGHT,2, 300,  1,0.4f,1.6f, -1,2.0f,2.1f);
		
		if(!bUp)
		{
			upBDir = 0;
			upBCount = 0;
			landing = true;
			if(yvelocity>0)
			{
				yvelocity = 0;
			}
			changeTwoSidedAnimation("special_prep_up", FORWARD);
		}
	}
	
	void Pikachu::attackDownB()
	{
		if(!bUp)
		{
			awaitingStrike = false;
			preppingDownB = true;
			changeTwoSidedAnimation("special_attack_down", FORWARD);
		}
	}
	
	void Pikachu::attackSideSmash(byte type) //13
	{
		if(!bUp && !checkItemUseSideSmash(type))
	    {
	        if(isOnGround())
	        {
	        	if(type == STEP_CHARGE)
	        	{
	        		AttackTemplates::normalSmash(this,13,3.05,type,1,2000,16,24);
	        	}
	        	else
	        	{
		        	winding = true;
					changeTwoSidedAnimation("smash_prep",FORWARD);
	        	}
	        }
	        else
	        {
	            attackSideA();
	        }
	    }
	}
	
	void Pikachu::attackUpSmash(byte type) //14
	{
		if(!bUp && !checkItemUseUpSmash(type))
	    {
	        if(isOnGround())
	        {
	        	if(type == STEP_CHARGE)
	        	{
	        		AttackTemplates::normalSmash(this,14,2.08,type,2,1800,14,20);
	        	}
	        	else
	        	{
		        	winding = true;
		        	changeTwoSidedAnimation("smash_prep_up",FORWARD);
	        	}
	        }
	        else
	        {
	            attackUpA();
	        }
	    }
	}
	
	void Pikachu::attackDownSmash(byte type) //15
	{
		if(!bUp && !checkItemUseDownSmash(type))
	    {
	        if(isOnGround())
	        {
	        	if(type == STEP_CHARGE)
	        	{
	        		AttackTemplates::normalSmash(this,15,2.48,type,3,1600,16,24);
	        	}
	        	else
	        	{
		        	winding = true;
		        	changeTwoSidedAnimation("smash_prep_down",FORWARD);
	        	}
	        }
	        else
	        {
	            attackDownA();
	        }
	    }
	}
	
	void Pikachu::attackFinalSmash()
	{
		AttackTemplates::finalSmash(this, 16);
		finalsmash = true;
		finalsmashTransition = 1;
		changeTwoSidedAnimation("finalsmash_begin", FORWARD);
		finishFinalsmash = Global::getWorldTime() + 10000;
	}
	
	//Projectiles -----------------------------------------------------------------------------------------------
	
	Pikachu::ThunderboltType::ThunderboltType(byte playerNo, float x1, float y1) : Projectile(playerNo, x1, y1)
	{
		//
	}
	
	Pikachu::ThunderboltType::~ThunderboltType()
	{
		//
	}
	
	void Pikachu::ThunderboltType::onPlayerHit(Player*collide, byte dir)
	{
		switch(dir)
		{
			case DIR_LEFT:
			causeDamage(collide,6);
			if(itemdir==LEFT)
			{
				causeHurtLaunch(collide, -1,1.4f,2.1f, -1,0.8f,1.4f);
			}
			else if(itemdir==RIGHT)
			{
				causeHurtLaunch(collide, -1,1.1f,1.4f, -1,1.1f,1.3f);
			}
			causeHurt(collide, RIGHT, 100);
			break;

			case DIR_RIGHT:
			causeDamage(collide,6);
			if(itemdir==LEFT)
			{
				causeHurtLaunch(collide, 1,1.4f,2.1f, -1,0.8f,1.4f);
			}
			else if(itemdir==RIGHT)
			{
				causeHurtLaunch(collide, 1,1.1f,1.4f, -1,1.1f,1.3f);
			}
			causeHurt(collide, LEFT, 100);
			break;

			case DIR_UP:
			causeDamage(collide,6);
			if(itemdir==LEFT)
			{
				causeHurtLaunch(collide, -1,1.2f,1.9f, -1,2.8f,2.0f);
				causeHurt(collide, RIGHT, 100);
			}
			else if(itemdir==RIGHT)
			{
				causeHurtLaunch(collide, 1,1.2f,1.9f, -1,2.8f,2.0f);
				causeHurt(collide, LEFT, 100);
			}
			break;

			case DIR_DOWN:
			causeDamage(collide,6);
			if(itemdir==LEFT)
			{
				causeHurtLaunch(collide, -1,1.2f,1.9f, 1,2.8f,2.0f);
				causeHurt(collide, RIGHT, 100);
			}
			else if(itemdir==RIGHT)
			{
				causeHurtLaunch(collide, 1,1.2f,1.9f, 1,2.8f,2.0f);
				causeHurt(collide, LEFT, 100);
			}
			break;
		}
		destroy();
	}
	
	const float Pikachu::Thunderbolt::vel = 3;
	const float Pikachu::Thunderbolt::incr = 0.6f;
	
	Pikachu::Thunderbolt::Thunderbolt(byte playerNo, float x1, float y1) : ThunderboltType(playerNo, x1, y1)
	{
		projdir = DIR_UP;
		stage = 0;
		drift = true;
		willDie = false;
		waitFrames = 0;
		destroyTime = Global::getWorldTime() + 1000;
		
		setScale(0.6f);
		
		setDeflectable(true);
		detectAllPlatformsSolid(true);
		
		Player*playr = Global::getPlayerActor(playerNo);
		itemdir = playr->getPlayerDir();
		
		Animation*anim;
		anim = new Animation("left", 12, 2, 1);
		anim->addFrame("Images/Game/Characters/Pikachu/thunderbolt.png");
		addAnimation(anim);
		
		anim = new Animation("right", 12, 2, 1);
		anim->addFrame("Images/Game/Characters/Pikachu/thunderbolt.png");
		anim->mirror(true);
		addAnimation(anim);
		
		if(itemdir==LEFT)
		{
			xvelocity = -vel;
			changeAnimation("left",FORWARD);
		}
		else if(itemdir==RIGHT)
		{
			xvelocity = vel;
			changeAnimation("right",FORWARD);
		}
		yvelocity = vel;
	}
	
	Pikachu::Thunderbolt::~Thunderbolt()
	{
		for(int i=0; i<trail.size(); i++)
		{
			trail.get(i)->leader = NULL;
		}
	}
	
	void Pikachu::Thunderbolt::deflect(byte dir)
	{
		switch(projdir)
		{
			case DIR_UP:
			switch(dir)
			{
				case DIR_LEFT:
				case DIR_UPLEFT:
				case DIR_DOWNLEFT:
				itemdir = LEFT;
				xvelocity = -std::abs(xvelocity);
				changeAnimation("left", NO_CHANGE);
				break;
				
				case DIR_RIGHT:
				case DIR_UPRIGHT:
				case DIR_DOWNRIGHT:
				itemdir = RIGHT;
				xvelocity = std::abs(xvelocity);
				changeAnimation("right", NO_CHANGE);
				break;
				
				case DIR_UP:
				yvelocity = -std::abs(yvelocity);
				break;
				
				case DIR_DOWN:
				yvelocity = std::abs(yvelocity);
				break;
			}
			break;
			
			case DIR_DOWN:
			switch(dir)
			{
				case DIR_RIGHT:
				case DIR_UPRIGHT:
				case DIR_DOWNRIGHT:
				itemdir = LEFT;
				xvelocity = std::abs(xvelocity);
				changeAnimation("left", NO_CHANGE);
				break;
				
				case DIR_LEFT:
				case DIR_UPLEFT:
				case DIR_DOWNLEFT:
				itemdir = RIGHT;
				xvelocity = -std::abs(xvelocity);
				changeAnimation("right", NO_CHANGE);
				break;
				
				case DIR_UP:
				yvelocity = -std::abs(yvelocity);
				break;
				
				case DIR_DOWN:
				yvelocity = std::abs(yvelocity);
				break;
			}
			break;
			
			case DIR_LEFT:
			switch(dir)
			{
				case DIR_DOWN:
				case DIR_DOWNLEFT:
				case DIR_DOWNRIGHT:
				itemdir = LEFT;
				yvelocity = -std::abs(yvelocity);
				changeAnimation("left", NO_CHANGE);
				break;
				
				case DIR_UP:
				case DIR_UPLEFT:
				case DIR_UPRIGHT:
				itemdir = RIGHT;
				yvelocity = std::abs(yvelocity);
				changeAnimation("right", NO_CHANGE);
				break;
				
				case DIR_LEFT:
				xvelocity = -std::abs(xvelocity);
				break;
				
				case DIR_RIGHT:
				xvelocity = std::abs(xvelocity);
				break;
			}
			break;
			
			case DIR_RIGHT:
			switch(dir)
			{
				case DIR_UP:
				case DIR_UPLEFT:
				case DIR_UPRIGHT:
				itemdir = LEFT;
				yvelocity = -std::abs(yvelocity);
				changeAnimation("left", NO_CHANGE);
				break;
				
				case DIR_DOWN:
				case DIR_DOWNLEFT:
				case DIR_DOWNRIGHT:
				itemdir = RIGHT;
				yvelocity = std::abs(yvelocity);
				changeAnimation("right", NO_CHANGE);
				break;
				
				case DIR_LEFT:
				xvelocity = std::abs(xvelocity);
				break;
				
				case DIR_RIGHT:
				xvelocity = -std::abs(xvelocity);
				break;
			}
			break;
		}
	}
	
	void Pikachu::Thunderbolt::Update(long gameTime)
	{
		Projectile::Update(gameTime);
		
		waitFrames++;
		if(waitFrames==2)
		{
			Pikachu*playr = (Pikachu*)Global::getPlayerActor(getPlayerNo());
			ThunderboltGhost*ghost = new ThunderboltGhost(this, getPlayerNo(), itemdir, drift, x, y);
			trail.add(ghost);
			createProjectile(ghost);
			playr->addProjectileInfo(2, ghost->getID(), x, y, itemdir, this->getID());
			waitFrames = 0;
		}
		
		if(Global::getWorldTime()>=destroyTime)
		{
			willDie = true;
			if(drift)
			{
				destroy();
			}
		}
		
		if(drift)
		{
			if(itemdir==LEFT)
			{
				xvelocity = -vel;
			}
			else if(itemdir==RIGHT)
			{
				xvelocity = vel;
			}
			yvelocity = vel;
		}
		else
		{
			switch(projdir)
			{
				case DIR_UP:
				{
					if(stage==0)
					{
						if(yvelocity>vel)
						{
							stage = 1;
							if(itemdir==LEFT)
							{
								xvelocity = vel;
							}
							else if(itemdir==RIGHT)
							{
								xvelocity = -vel;
							}
						}
						else
						{
							yvelocity += incr;
						}
					}
					else if(stage==1)
					{
						if(yvelocity<0)
						{
							stage = 2;
							yvelocity -= incr;
						}
						else
						{
							yvelocity -= incr;
						}
					}
					else if(stage==2)
					{
						if(yvelocity<(-vel/2))
						{
							drift = true;
							projdir = DIR_UP;
							stage = 0;
						}
						else
						{
							yvelocity -= incr;
						}
					}
				}
				break;
				
				case DIR_UPLEFT:
				{
					//
				}
				break;
				
				case DIR_UPRIGHT:
				{
					//
				}
				break;
				
				case DIR_LEFT:
				{
					if(stage==0)
					{
						if(xvelocity>vel)
						{
							stage = 1;
							if(itemdir==LEFT)
							{
								yvelocity = -vel;
							}
							else if(itemdir==RIGHT)
							{
								yvelocity = vel;
							}
						}
						else
						{
							xvelocity += incr;
						}
					}
					else if(stage==1)
					{
						if(xvelocity<0)
						{
							stage = 2;
							xvelocity -= incr;
						}
						else
						{
							xvelocity -= incr;
						}
					}
					else if(stage==2)
					{
						if(xvelocity<(-vel/2))
						{
							drift = true;
							itemdir = DIR_UP;
							stage = 0;
						}
						else
						{
							xvelocity -= incr;
						}
					}
				}
				break;
				
				case DIR_RIGHT:
				{
					if(stage==0)
					{
						if(xvelocity<(-vel))
						{
							stage = 1;
							if(itemdir==LEFT)
							{
								yvelocity = vel;
							}
							else if(itemdir==RIGHT)
							{
								yvelocity = -vel;
							}
						}
						else
						{
							xvelocity -= incr;
						}
					}
					else if(stage==1)
					{
						if(xvelocity>0)
						{
							stage = 2;
							xvelocity += incr;
						}
						else
						{
							xvelocity += incr;
						}
					}
					else if(stage==2)
					{
						if(xvelocity>(vel/2))
						{
							drift = true;
							projdir = DIR_UP;
							stage = 0;
						}
						else
						{
							xvelocity += incr;
						}
					}
				}
				break;
				
				case DIR_DOWNLEFT:
				{
					//
				}
				break;
				
				case DIR_DOWNRIGHT:
				{
					//
				}
				break;
				
				case DIR_DOWN:
				{
					if(stage==0)
					{
						if(yvelocity<(-vel))
						{
							stage=1;
							if(itemdir==LEFT)
							{
								xvelocity = -vel;
							}
							else if(itemdir==RIGHT)
							{
								xvelocity = vel;
							}
						}
						else
						{
							yvelocity -= incr;
						}
					}
					else if(stage==1)
					{
						if(yvelocity>0)
						{
							stage = 2;
							yvelocity += incr;
						}
						else
						{
							yvelocity += incr;
						}
					}
					else if(stage==2)
					{
						if(yvelocity>(vel/2))
						{
							drift = true;
							projdir = DIR_UP;
							stage = 0;
						}
						else
						{
							yvelocity += incr;
						}
					}
				}
				break;
			}
		}
	}
	
	void Pikachu::Thunderbolt::setOwner(Player*owner)
	{
		Projectile::setOwner(owner);
		for(int i=0; i<trail.size(); i++)
		{
			trail.get(i)->setOwner(owner);
		}
	}
	
	void Pikachu::Thunderbolt::whilePlatformColliding(Platform*platform, byte dir)
	{
		if(willDie)
		{
			destroy();
		}
		else
		{
			setBoltDir(dir);
		}
	}
	
	void Pikachu::Thunderbolt::setBoltDir(byte dir)
	{
		projdir = dir;
		stage = 0;
		drift = false;

		switch(projdir)
		{
			case DIR_UP:
			{
				if(itemdir==LEFT)
				{
					xvelocity = -vel;
				}
				else if(itemdir==RIGHT)
				{
					xvelocity = vel;
				}
				yvelocity = -vel;
			}
			break;

			case DIR_UPLEFT:
			{
				setBoltDir(DIR_LEFT);
			}
			break;

			case DIR_UPRIGHT:
			{
				setBoltDir(DIR_RIGHT);
			}
			break;

			case DIR_LEFT:
			{
				if(itemdir==LEFT)
				{
					yvelocity = vel;
				}
				else if(itemdir==RIGHT)
				{
					yvelocity = -vel;
				}
				xvelocity = -vel;
			}
			break;

			case DIR_RIGHT:
			{
				if(itemdir==LEFT)
				{
					yvelocity = -vel;
				}
				else if(itemdir==RIGHT)
				{
					yvelocity = vel;
				}
				xvelocity = vel;
			}
			break;

			case DIR_DOWNLEFT:
			{
				setBoltDir(DIR_LEFT);
			}
			break;

			case DIR_DOWNRIGHT:
			{
				setBoltDir(DIR_RIGHT);
			}
			break;

			case DIR_DOWN:
			{
				if(itemdir==LEFT)
				{
					xvelocity = vel;
				}
				else if(itemdir==RIGHT)
				{
					xvelocity = -vel;
				}
				yvelocity = vel;
			}
			break;
		}
	}
	
	void Pikachu::Thunderbolt::onPlayerHit(Player*collide, byte dir)
	{
		if(isHittable(collide, dir))
		{
			ThunderboltType::onPlayerHit(collide, dir);
			for(int i=0; i<trail.size(); i++)
			{
				trail.get(i)->lethal = false;
			}
		}
	}
	
	Pikachu::Thunderbolt::ThunderboltGhost::ThunderboltGhost(Thunderbolt*bolt, byte playerNo, byte dir, bool drift, float x1, float y1) : ThunderboltType(playerNo, x1, y1)
	{
		setScale(0.6f);
		waitFrames = 8;
		this->drift = drift;
		leader = bolt;
		lethal = true;
		
		Animation*anim;
		anim = new Animation("left", 12, 2, 1);
		anim->addFrame("Images/Game/Characters/Pikachu/thunderbolt.png");
		addAnimation(anim);
		
		anim = new Animation("right", 12, 2, 1);
		anim->addFrame("Images/Game/Characters/Pikachu/thunderbolt.png");
		anim->mirror(true);
		addAnimation(anim);
		
		if(dir==LEFT)
		{
			changeAnimation("left", FORWARD);
		}
		else if(dir==RIGHT)
		{
			changeAnimation("right", FORWARD);
		}
		
		itemdir = dir;
	}
	
	Pikachu::Thunderbolt::ThunderboltGhost::~ThunderboltGhost()
	{
		if(leader!=NULL)
		{
			for(int i=0; i<leader->trail.size(); i++)
			{
				ThunderboltGhost*ghost = leader->trail.get(i);
				if(ghost == this)
				{
					leader->trail.remove(i);
					i=leader->trail.size();
				}
			}
		}
	}
	
	void Pikachu::Thunderbolt::ThunderboltGhost::deflect(byte dir)
	{
		if(leader!=NULL)
		{
			leader->deflect(dir);
		}
	}
	
	void Pikachu::Thunderbolt::ThunderboltGhost::Update(long gameTime)
	{
		Projectile::Update(gameTime);
		if(drift)
		{
			float alpha = getAlpha();
			alpha += 0.2f;
			setAlpha(alpha);
			
			if(alpha>=1)
			{
				destroy();
			}
		}
		else
		{
			waitFrames--;
			
			if(waitFrames<=0)
			{
				destroy();
			}
		}
	}
	
	void Pikachu::Thunderbolt::ThunderboltGhost::onPlayerHit(Player*collide, byte dir)
	{
		if(isHittable(collide, dir) && lethal)
		{
			ThunderboltType::onPlayerHit(collide, dir);
			if(leader!=NULL)
			{
				leader->destroy();
				for(int i=0; i<leader->trail.size(); i++)
				{
					leader->trail.get(i)->lethal = false;
				}
			}
		}
	}

	Pikachu::LightningType::LightningType(byte playerNo, float x1, float y1) : Projectile(playerNo, x1, y1)
	{
		//
	}

	Pikachu::LightningType::~LightningType()
	{
		//
	}

	void Pikachu::LightningType::onPlayerHit(Player*collide, byte dir)
	{
		if(isHittable(collide, dir))
		{
			if(collide->x <= x)
			{
				causeDamage(collide,17);
				causeHurtLaunch(collide, -1,2,3.7f, -1,4.1f,2.7f);
				causeHurt(collide, RIGHT, 400);
			}
			else if(collide->x > x)
			{
				causeDamage(collide,17);
				causeHurtLaunch(collide, 1,2,3.7f, -1,4.1f,2.7f);
				causeHurt(collide, LEFT, 400);
			}
		}
	}
	
	Pikachu::Lightning::LightningBody::LightningBody(Lightning*leader, byte playerNo, float x1, float y1, boolean frameOn) : LightningType(playerNo, x1, y1)
	{
		this->frameOn = frameOn;
		isEnd = false;
		
		Animation*anim;
		
		anim = new Animation("frame0", 1, "Images/Game/Characters/Pikachu/lightning_1.png");
		addAnimation(anim);

		anim = new Animation("frame1", 1, "Images/Game/Characters/Pikachu/lightning_2.png");
		addAnimation(anim);

		anim = new Animation("end0", 1, "Images/Game/Characters/Pikachu/lightning_end_1.png");
		addAnimation(anim);

		anim = new Animation("end1", 1, "Images/Game/Characters/Pikachu/lightning_end_2.png");
		addAnimation(anim);

		if(frameOn)
		{
			changeAnimation("frame1", FORWARD);
		}
		else
		{
			changeAnimation("frame0", FORWARD);
		}

		this->leader = leader;
	}

	Pikachu::Lightning::LightningBody::~LightningBody()
	{
		if(leader!=NULL)
		{
			for(int i=0; i<leader->bodies.size(); i++)
			{
				LightningBody*cmp = leader->bodies.get(i);
				if(this == cmp)
				{
					leader->bodies.remove(i);
					i = leader->bodies.size();
				}
			}
		}
	}

	void Pikachu::Lightning::LightningBody::Update(long gameTime)
	{
		LightningType::Update(gameTime);

		if(leader == NULL)
		{
			float alpha = getAlpha();
			alpha += 0.2f;
			setAlpha(alpha);

			if(alpha>=1)
			{
				destroy();
			}
		}
	}

	void Pikachu::Lightning::LightningBody::setEnd(boolean toggle)
	{
		isEnd = toggle;
		if(isEnd)
		{
			if(frameOn)
			{
				changeAnimation("end1", FORWARD);
			}
			else
			{
				changeAnimation("end0", FORWARD);
			}
		}
		else
		{
			if(frameOn)
			{
				changeAnimation("frame1", FORWARD);
			}
			else
			{
				changeAnimation("frame0", FORWARD);
			}
		}
	}

	void Pikachu::Lightning::LightningBody::toggleFrame()
	{
		if(isEnd)
		{
			if(frameOn)
			{
				frameOn = false;
				changeAnimation("end0", FORWARD);
			}
			else
			{
				frameOn = true;
				changeAnimation("end1", FORWARD);
			}
		}
		else
		{
			if(frameOn)
			{
				frameOn = false;
				changeAnimation("frame0", FORWARD);
			}
			else
			{
				frameOn = true;
				changeAnimation("frame1", FORWARD);
			}
		}
	}
	
	Pikachu::Lightning::Lightning(byte playerNo, float x1, float y1) : LightningType(playerNo, x1, y1)
	{
		addAnimation(new Animation("lightning_head", 30, "Images/Game/Characters/Pikachu/lightning_head.png"));
		Animation*anim = new Animation("lightning_cloud", 18, 8, 1);
		anim->addFrame("Images/Game/Characters/Pikachu/lightning_cloud.png");
		addAnimation(anim);
		changeAnimation("lightning_head", FORWARD);
		
		detectAllPlatformsSolid(true);
		
		RectF borders = Global::currentStage->getBorders();
		float top = (float)Global::currentStage->y + (float)borders.top;
		
		y = top + (height/2);
		
		createdFrame = false;
		hitGround = false;
		waitFrames = 0;
	}
	
	Pikachu::Lightning::~Lightning()
	{
		for(int i=0; i<bodies.size(); i++)
		{
			LightningBody*body = bodies.get(i);
			body->leader = NULL;
		}
	}
	
	void Pikachu::Lightning::Update(long gameTime)
	{
		LightningType::Update(gameTime);
		
		if(!hitGround)
		{
			Player*playr = Global::getPlayerActor(getPlayerNo());
			if(playr!=NULL)
			{
				if(playr->hitboxRectsColliding(this))
				{
					setLayer(LAYER_MIDDLEUPPER);
					if(bodies.size()>0)
					{
						bodies.get(bodies.size()-1)->setEnd(true);
					}
					hitGround = true;
					changeAnimation("lightning_cloud", FORWARD);
				}
			}
			
			RectF borders = Global::currentStage->getBorders();
			float bottom = (float)Global::currentStage->y + (float)borders.bottom;
			if(y>=bottom)
			{
				setLayer(LAYER_MIDDLEUPPER);
				if(bodies.size()>0)
				{
					bodies.get(bodies.size()-1)->setEnd(true);
				}
				hitGround = true;
				changeAnimation("lightning_cloud", FORWARD);
			}
		}
		
		if(waitFrames>=3)
		{
			waitFrames = 0;
			
			for(int i=0; i<bodies.size(); i++)
			{
				bodies.get(i)->toggleFrame();
			}

			if(createdFrame)
			{
				createdFrame = false;
			}
			else
			{
				createdFrame = true;
			}
		}
		else
		{
			waitFrames++;
		}
	}
	
	void Pikachu::Lightning::Draw(Graphics2D&g, long gameTime)
	{
		LightningType::Draw(g, gameTime);
	}
	
	void Pikachu::Lightning::onAnimationFinish(const String&name)
	{
		if(name.equals("lightning_head"))
		{
			float h = (float)(AssetManager::getImage("Images/Game/Characters/Pikachu/lightning_1.png")->getHeight());
			float cy = y - ((float)height/2) + (h/2);
			y += h;
			
			Pikachu*playr = (Pikachu*)Global::getPlayerActor(getPlayerNo());
			LightningBody*body = new LightningBody(this, getPlayerNo(), x, cy, createdFrame);
			bodies.add(body);
			createProjectile(body);
			playr->addProjectileInfo(3, body->getID(), x, cy, (byte)createdFrame, this->getID());
		}
		else if(name.equals("lightning_cloud"))
		{
			Pikachu*owner = (Pikachu*)Global::getPlayerActor(getPlayerNo());
			if(owner!=NULL)
			{
				owner->awaitingStrike = false;
			}
			destroy();
		}
	}
	
	void Pikachu::Lightning::whilePlatformColliding(Platform*platform, byte dir)
	{
		if(!hitGround)
		{
			setLayer(LAYER_MIDDLEUPPER);
			if(bodies.size()>0)
			{
				bodies.get(bodies.size()-1)->setEnd(true);
			}
			hitGround = true;
			changeAnimation("lightning_cloud", FORWARD);
		}
	}
}