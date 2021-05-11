
#include "Kirby.h"
#include "../../AttackTemplates.h"
#include "../../Global.h"
#include "../../Item.h"

namespace SmashBros
{
#define KIRBY_PUNCHOFFSET 20

	Kirby::Kirby(float x1, float y1, byte playerNo, byte team) : Player(x1, y1, playerNo, team)
	{
		queueStandardCombo = false;
		prepping = false;
		finishing = false;

		weight = 0.08;

		maxDoubleJumps = 5;
		
		name = "Kirby";
		
		setHitbox(-8, -2, 16, 22);
		setHitboxColor(Color::GREEN);
		//showHitboxWireframe(true);
		//setWireframeColor(Color::RED);
		//showWireframe(true);
		
		setHangPoint(2, 10);
		
		Console::WriteLine((String)"finished creating player " + playerNo);
	}

	Kirby::~Kirby()
	{
		//
	}

	boolean Kirby::checkIfAble()
	{
		if(prepping || finishing)
		{
			return false;
		}
		return true;
	}
	
	void Kirby::setToDefaultValues()
	{
		queueStandardCombo = false;
		prepping = false;
		finishing = false;
	}
	
	void Kirby::Load()
	{
		setFolderPath("Images/Game/Characters/Kirby/");

		loadFile("Images/Game/Characters/Kirby/fall2.png");
		addTwoSidedAnimation("stand", "stand.png", 4, 4, 1);
		addTwoSidedAnimation("walk", "walk.png", 14, 12, 1);
		addTwoSidedAnimation("run", "run.png", 14, 8, 1);
		addTwoSidedAnimation("jump", "jump.png", 16, 8, 1);
		addTwoSidedAnimation("jump2", "jump2.png", 12, 4, 1);
		addTwoSidedAnimation("land", "land.png", 14, 4, 1);
		addTwoSidedAnimation("fall", "fall.png", 30, 1, 1);
		addTwoSidedAnimation("fall2", "fall2.png", 30, 1, 1);
		addTwoSidedAnimation("hang", "hang.png", 1, 1, 1);
		addTwoSidedAnimation("crouch", "crouch.png", 1, 1, 1);
		addTwoSidedAnimation("grab", "grab.png", 14, 4, 1);
		addTwoSidedAnimation("grabbed", "grabbed.png", 30, 1, 1);
		addTwoSidedAnimation("hold", "hold.png", 30, 1, 1);
		addTwoSidedAnimation("release", "release.png", 12, 3, 1);
		addTwoSidedAnimation("toss", "toss.png", 12, 3, 1);
		addTwoSidedAnimation("toss_up", "toss_up.png", 16, 4, 1);
		addTwoSidedAnimation("toss_down", "toss_down.png", 16, 4, 1);
		addTwoSidedAnimation("grab_attack", "grab_attack.png", 10, 3, 1);
		addTwoSidedAnimation("melee_weapon", "melee_weapon.png", 12, 3, 1);
		addTwoSidedAnimation("melee_weapon_up", "melee_weapon_up.png", 17, 4, 1);
		addTwoSidedAnimation("melee_weapon_down", "melee_weapon_down.png", 17, 4, 1);
		addTwoSidedAnimation("hurt_minor", "hurt_minor.png", 30, 1, 1);
		addTwoSidedAnimation("hurt_fly", "hurt_fly.png", 30, 1, 1);
		addTwoSidedAnimation("hurt_minor", "hurt_minor.png", 30, 1, 1);
		addTwoSidedAnimation("hurt_flip", "hurt_flip.png", 20, 8, 1);
		addTwoSidedAnimation("hurt_spin", "hurt_spin.png", 20, 8, 1);
		addSingleAnimation("hurt_spin", "hurt_spin_up.png", 20, 8, 1);
		addTwoSidedAnimation("standard_attack", "standard_attack.png", 12, 3, 1);
		addTwoSidedAnimation("standard_attack2", "standard_attack2.png", 12, 3, 1);
		addTwoSidedAnimation("standard_attack3", "standard_attack3.png", 18, 6, 1);
		addTwoSidedAnimation("standard_attack_side", "standard_attack_side.png", 20, 8, 1);
		addTwoSidedAnimation("standard_attack_up", "standard_attack_up.png", 20, 5, 1);
		addTwoSidedAnimation("standard_attack_down", "standard_attack_down.png", 16, 4, 1);
		addTwoSidedAnimation("air_attack", "air_attack.png", 26, 9, 1);
		addTwoSidedAnimation("air_attack_side", "air_attack_side.png", 20, 8, 1);
		addTwoSidedAnimation("air_attack_up", "air_attack_up.png", 18, 6, 1);
		addTwoSidedAnimation("air_attack_down", "air_attack_down.png", 30, 11, 1);
		addTwoSidedAnimation("special_prep_hold_side", "special_prep_hold_side.png", 6, 1, 1);
		addTwoSidedAnimation("special_prep_side", "special_prep_side.png", 28, 5, 1);
		addTwoSidedAnimation("special_attack_side", "special_attack_side.png", 28, 4, 1);
		addTwoSidedAnimation("special_finish_side", "special_finish_side.png", 28, 2, 1);
		addTwoSidedAnimation("special_finish_hold_side", "special_finish_hold_side.png", 6, 1, 1);
		addTwoSidedAnimation("special_finish_putaway_side", "special_finish_putaway_side.png", 28, 3, 1);
	}

	void Kirby::LoadAttackTypes()
	{
		//
	}

	void Kirby::onAnimationFinish(const String&n)
	{
		if(n.equals("fall2_left") || n.equals("fall2_right"))
		{
			if(isOnGround())
			{
				Player::onAnimationFinish(n);
			}
		}
		else if(n.equals("standard_attack3_left") || n.equals("standard_attack3_right"))
		{
			if(queueStandardCombo)
			{
				changeTwoSidedAnimation("standard_attack3", FORWARD);
				createProjectile(new ComboPunches(getPlayerNo(), x + (KIRBY_PUNCHOFFSET*getScale()*getPlayerDirMult()), y));
				if(attacksPriority > 0.6)
				{
					attacksPriority -= 0.3;
				}
			}
			else
			{
				Player::onAnimationFinish(n);
			}
			queueStandardCombo = false;
		}
		else if(n.equals("special_prep_hold_side_left") || n.equals("special_prep_hold_side_right"))
		{
			changeTwoSidedAnimation("special_prep_side", FORWARD);
		}
		else if(n.equals("special_prep_side_left") || n.equals("special_prep_side_right"))
		{
			prepping = false;
			AttackTemplates::normalSideB(this, 12,3.07);
		}
		else if(n.equals("special_attack_side_left") || n.equals("special_attack_side_right"))
		{
			Player::onAnimationFinish(n);
			finishing = true;
			changeTwoSidedAnimation("special_finish_side", FORWARD);
		}
		else if(n.equals("special_finish_side_left") || n.equals("special_finish_side_right"))
		{
			changeTwoSidedAnimation("special_finish_hold_side", FORWARD);
		}
		else if(n.equals("special_finish_hold_side_left") || n.equals("special_finish_hold_side_right"))
		{
			changeTwoSidedAnimation("special_finish_putaway_side", FORWARD);
		}
		else
		{
			Player::onAnimationFinish(n);
		}
	}

	void Kirby::jump()
	{
		Player::jump(4.8f,3.6f + 0.1f*((int)doubleJump));
	}

	void Kirby::Update(long gameTime)
	{
		if(!isOnGround() && doubleJump < maxDoubleJumps && !isHurt())
		{
			weight = 0.04;
		}
		else
		{
			weight = 0.08;
		}

		if(!isOnGround() && doubleJump == 0)
		{
			String animName = getAnimName();
			if(animName.equals("fall_left") || animName.equals("fall_right"))
			{
				changeTwoSidedAnimation("fall2", NO_CHANGE);
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
	
	void Kirby::Draw(Graphics2D&g, long gameTime)
	{
		Player::Draw(g, gameTime);
	}
	
	void Kirby::onPlayerHit(Player*collide, byte dir)
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
					//A1
					causeDamage(collide, 2);
					collide->y -= 3;
					causeHurt(collide, getOppPlayerDir(), 100);
					break;
				
					case 1:
					//A2
					causeDamage(collide, 2);
					collide->y -= 3;
					causeHurt(collide, getOppPlayerDir(), 100);
					break;
				
					case 2:
					//A3
					causeDamage(collide, 2);
					collide->y -= 6;
					collide->x += 0.5f * getPlayerDirMult();
					causeHurt(collide, getOppPlayerDir(), 100);
					break;
				}
			}
			break;
		}
	}

	void Kirby::onQueueAttack(byte attackType)
	{
		if(attackType == ATTACK_A)
		{
			queueStandardCombo = true;
		}
	}

	void Kirby::attackA()
	{
		addAttackInfo(DIR_LEFT,  7, LEFT,  10, 300, -1,2.1f,3.6f, -1,1.9f,3.7f);
		addAttackInfo(DIR_RIGHT, 7, RIGHT, 10, 300,  1,2.1f,3.6f, -1,1.9f,3.7f);
		addAttackInfo(DIR_UP, 7, LEFT,  10, 300, -1,1.2f,2.95f, -1,2.75f,3.6f);
		addAttackInfo(DIR_UP, 7, RIGHT, 10, 300,  1,1.2f,2.95f, -1,2.75f,3.6f);

		if(!checkItemUse())
		{
			if(isOnGround())
			{
				int comboNo = getComboNo();
				AttackTemplates::combo3A(this, 500, 0,1.76, 1,2.48, 2,2.86, true);
				if(getComboNo() == 2 && comboNo == 2)
				{
					createProjectile(new ComboPunches(getPlayerNo(), x + (KIRBY_PUNCHOFFSET*getScale()*getPlayerDirMult()), y));
				}
			}
			else
			{
				if(!bUp)
				{
					AttackTemplates::normalAirA(this, 7,1.66);
				}
			}
		}
	}

	void Kirby::attackSideA()
	{
		addAttackInfo(DIR_LEFT, 4, LEFT, 9, 300, -1,2,2.1f, -1,3,3.3f);
		addAttackInfo(DIR_RIGHT,4,RIGHT, 9, 300,  1,2,2.1f, -1,3,3.3f);
		addAttackInfo(DIR_LEFT, 8, LEFT, 4, 200, -1,2.1f,2.5f, -1,1.2f,2.1f);
		addAttackInfo(DIR_RIGHT,8,RIGHT, 4, 200,  1,2.1f,2.5f, -1,1.2f,2.1f);

		if(!checkItemUseSide())
		{
			if(isOnGround())
			{
				AttackTemplates::normalSideA(this, 4,2.36);
			}
			else
			{
				if(!bUp)
				{
					AttackTemplates::normalAirSideA(this, 8,1.8f);
				}
			}
		}
	}

	void Kirby::attackUpA()
	{
		addAttackInfo(DIR_UP, 5, LEFT,  7, 300, -1,0,0, -1,2.9f,2.4f);
		addAttackInfo(DIR_UP, 5, RIGHT, 7, 300,  1,0,0, -1,2.9f,2.4f);
		addAttackInfo(DIR_LEFT,  5, RIGHT, 7, 300, -1,0.8f,1.7f, -1,2.8f,2.4f);
		addAttackInfo(DIR_RIGHT, 5, LEFT,  7, 300,  1,0.8f,1.7f, -1,2.8f,2.4f);
		addAttackInfo(DIR_UP, 9, LEFT,  7, 300, -1,0,0, -1,3.0f,2.5f);
		addAttackInfo(DIR_UP, 9, RIGHT, 7, 300,  1,0,0, -1,3.0f,2.5f);
		addAttackInfo(DIR_LEFT,  9, RIGHT, 7, 300, -1,0.8f,1.8f, -1,2.9f,2.6f);
		addAttackInfo(DIR_RIGHT, 9, LEFT,  7, 300,  1,0.8f,1.8f, -1,2.9f,2.6f);

		if(!checkItemUseUp())
		{
			if(isOnGround())
			{
				AttackTemplates::normalUpA(this, 5,1.6);
			}
			else
			{
				if(!bUp)
				{
					AttackTemplates::normalAirUpA(this, 9,2.066f);
				}
			}
		}
	}

	void Kirby::attackDownA()
	{
		addAttackInfo(DIR_LEFT, 6, LEFT, 6, 200, -1,3,2, -1,3,2);
		addAttackInfo(DIR_RIGHT,6,RIGHT, 6, 200,  1,3,2, -1,3,2);
		addAttackInfo(DIR_DOWN, 6, LEFT, 6, 200, -1,2,1.4f, 1,3.5f,3.4f);
		addAttackInfo(DIR_DOWN, 6,RIGHT, 6, 200,  1,2,1.4f, 1,3.5f,3.4f);
		addAttackInfo(DIR_DOWN, 10, LEFT, 6, 200, -1,0,0, 1,3.9f,3.6f);
		addAttackInfo(DIR_DOWN, 10,RIGHT, 6, 200,  1,0,0, 1,3.9f,3.6f);
		
		if(!checkItemUseDown())
		{
			if(isOnGround())
			{
				x += 3*getPlayerDirMult();
				AttackTemplates::normalDownA(this, 6,2.13);
			}
			else
			{
				if(!bUp)
				{
					AttackTemplates::normalAirDownA(this, 10,2.052f);
				}
			}
		}
	}

	void Kirby::attackB()
	{
		//
	}

	void Kirby::attackSideB()
	{
		addAttackInfo(DIR_LEFT,  12, LEFT,  17, 300, -1,3.1f,3.1f, -1,2.1f,2.2f);
		addAttackInfo(DIR_RIGHT, 12, RIGHT, 17, 300,  1,3.1f,3.1f, -1,2.1f,2.2f);

		if(!bUp)
		{
			prepping = true;
			changeTwoSidedAnimation("special_prep_hold_side", FORWARD);
		}
	}

	void Kirby::attackUpB()
	{
		//
	}

	void Kirby::attackDownB()
	{
		//
	}

	void Kirby::attackSideSmash(byte type)
	{
		//
	}

	void Kirby::attackUpSmash(byte type)
	{
		//
	}

	void Kirby::attackDownSmash(byte type)
	{
		//
	}

	void Kirby::attackFinalSmash()
	{
		//
	}

	Kirby::ComboPunches::ComboPunches(byte playerNo, float x1, float y1) : Projectile(playerNo, x1, y1)
	{
		setAlpha(0.5f);

		Animation* anim = new Animation("left", 18, 6, 1);
		anim->addFrame("Images/Game/Characters/Kirby/standard_attack3_punches.png");
		addAnimation(anim);

		anim = new Animation("right", 18, 6, 1);
		anim->addFrame("Images/Game/Characters/Kirby/standard_attack3_punches.png");
		anim->mirror(true);
		addAnimation(anim);

		Player* owner = Global::getPlayerActor(playerNo);
		switch(owner->getPlayerDir())
		{
			case LEFT:
			changeAnimation("left", FORWARD);
			break;

			case RIGHT:
			changeAnimation("right", FORWARD);
			break;
		}
	}

	Kirby::ComboPunches::~ComboPunches()
	{
		//
	}

	void Kirby::ComboPunches::onAnimationFinish(const String&n)
	{
		destroy();
	}

	void Kirby::ComboPunches::onPlayerHit(Player* collide, byte dir)
	{
		Player* owner = Global::getPlayerActor(getPlayerNo());
		if(isHittable(collide, dir) && collide->getAttacksPriority()<1)
		{
			causeDamage(collide, 2);
			collide->y -= 6;
			causeHurt(collide, owner->getOppPlayerDir(), 100);
		}
	}
}
