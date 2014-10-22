
#include "AttackRandomizer.h"
#include "Global.h"
#include "Controls.h"

namespace SmashBros
{
	AttackRandomizer::AttackProbability::AttackProbability()
	{
		//
	}

	AttackRandomizer::AttackProbability::AttackProbability(AttackRandomizer*randomizer, byte attack, float probability, boolean charge)
	{
		this->attack = attack;
		this->probability = probability;
		this->charge = charge;
		this->randomizer = randomizer;
	}

	AttackRandomizer::AttackProbability::~AttackProbability()
	{
		randomizer = null;
	}

	void AttackRandomizer::setPlayerNo(int playerNo)
	{
		this->playerNo = playerNo;
	}

	void AttackRandomizer::AttackProbability::doAttack()
	{
		Player*playr = Global::getPlayerActor(randomizer->playerNo);
		if(playr->CanDo())
		{
			switch(attack)
			{
				case Player::ATTACK_A:
				playr->attackA();
				break;
				
				case Player::ATTACK_SIDEA:
				playr->attackSideA();
				break;
				
				case Player::ATTACK_UPA:
				playr->attackUpA();
				break;
				
				case Player::ATTACK_DOWNA:
				playr->attackDownA();
				break;
				
				case Player::ATTACK_B:
				playr->attackB();
				break;
				
				case Player::ATTACK_SIDEB:
				playr->attackSideB();
				break;
				
				case Player::ATTACK_UPB:
				playr->attackUpB();
				break;
				
				case Player::ATTACK_DOWNB:
				playr->attackDownB();
				break;
				
				case Player::ATTACK_SIDESMASH:
				playr->attackSideSmash(Player::STEP_CHARGE);
				break;
				
				case Player::ATTACK_UPSMASH:
				playr->attackUpSmash(Player::STEP_CHARGE);
				break;
				
				case Player::ATTACK_DOWNSMASH:
				playr->attackDownSmash(Player::STEP_CHARGE);
				break;
			}
		}
		if(charge)
		{
			randomizer->currentlyChargingAttack = attack;
		}
	}

	byte AttackRandomizer::AttackProbability::getAttackNo()
	{
		return attack;
	}

	float AttackRandomizer::AttackProbability::getProbability()
	{
		return probability;
	}

	boolean AttackRandomizer::AttackProbability::mustCharge()
	{
		return charge;
	}

	AttackRandomizer::AttackRandomizer(int playerNo)
	{
		melee = new ArrayList<AttackProbability>();
		upmelee = new ArrayList<AttackProbability>();
		downmelee = new ArrayList<AttackProbability>();
		strongmelee = new ArrayList<AttackProbability>();
		sidemove = new ArrayList<AttackProbability>();
		upmove = new ArrayList<AttackProbability>();
		downmove = new ArrayList<AttackProbability>();
		projectile = new ArrayList<AttackProbability>();
		defensive = new ArrayList<AttackProbability>();
		
		meleeProb = 0;
		upmeleeProb = 0;
		downmeleeProb = 0;
		strongmeleeProb = 0;
		sidemoveProb = 0;
		upmoveProb = 0;
		downmoveProb = 0;
		projectileProb = 0;
		defensiveProb = 0;
		
		finalsmashCharge = false;
		
		currentlyChargingAttack = -1;
		
		this->playerNo = playerNo;
	}

	AttackRandomizer::~AttackRandomizer()
	{
		delete melee;
		delete upmelee;
		delete downmelee;
		delete strongmelee;
		delete sidemove;
		delete upmove;
		delete downmove;
		delete projectile;
		delete defensive;
	}

	void AttackRandomizer::setAttack(byte attack, byte attacktype, float probability, boolean charge)
	{
		if(attack==Player::ATTACK_FINALSMASH)
		{
			finalsmashCharge = charge;
		}
		else
		{
			AttackProbability newAttack = AttackProbability(this, attack, probability, charge);
			switch(attacktype)
			{
				case Player::ATTACKTYPE_MELEE:
				melee->add(newAttack);
				meleeProb+=probability;
				break;
				
				case Player::ATTACKTYPE_UPMELEE:
				upmelee->add(newAttack);
				upmeleeProb+=probability;
				break;
				
				case Player::ATTACKTYPE_DOWNMELEE:
				downmelee->add(newAttack);
				downmeleeProb+=probability;
				break;
				
				case Player::ATTACKTYPE_STRONGMELEE:
				strongmelee->add(newAttack);
				strongmeleeProb+=probability;
				break;
				
				case Player::ATTACKTYPE_SIDEMOVE:
				sidemove->add(newAttack);
				sidemoveProb+=probability;
				break;
				
				case Player::ATTACKTYPE_UPMOVE:
				upmove->add(newAttack);
				upmoveProb+=probability;
				break;
				
				case Player::ATTACKTYPE_DOWNMOVE:
				downmove->add(newAttack);
				downmoveProb+=probability;
				break;
				
				case Player::ATTACKTYPE_PROJECTILE:
				projectile->add(newAttack);
				projectileProb+=probability;
				break;
				
				case Player::ATTACKTYPE_DEFENSIVE:
				defensive->add(newAttack);
				defensiveProb+=probability;
				break;
			}
		}
	}

	void AttackRandomizer::doFinalSmash()
	{
		Player*playr = Global::getPlayerActor(playerNo);
		if(playr->canFinalSmash())
		{
			playr->attackFinalSmash();
		}
	}

	byte AttackRandomizer::doAttack(byte attacktype)
	{
		if(totalAttacks(attacktype)>0)
		{
			return doRandomAttack(attacktype);
		}
		return -1;
	}

	byte AttackRandomizer::doRandomAttack(byte attacktype)
	{
		ArrayList<AttackProbability>*list = getAttackList(attacktype);
		float totalProb = getTotalAttackProbability(attacktype);
		float rand = (float)(GameEngine::random()*totalProb);
		float current = 0;
		for(int i=0; i<list->size(); i++)
		{
			current += list->get(i).getProbability();
			if(rand<=current)
			{
				AttackProbability&attackProb = list->get(i);
				attackProb.doAttack();
				return attackProb.getAttackNo();
			}
		}
		return -1;
	}

	boolean AttackRandomizer::doChargingAttack()
	{
		Player*playr = Global::getPlayerActor(playerNo);
		if(playr->chargeSmash>0)
		{
			switch(playr->chargeSmash)
			{
				case 1:
				playr->attackSideSmash(Player::STEP_GO);
				break;
				
				case 2:
				playr->attackUpSmash(Player::STEP_GO);
				break;
				
				case 3:
				playr->attackDownSmash(Player::STEP_GO);
				break;
			}
			currentlyChargingAttack = -1;
			return true;
		}
		else if(playr->chargingAttack)
		{
			switch(currentlyChargingAttack)
			{
				case Player::ATTACK_A:
				playr->doChargingAttack(Controls::BUTTON_STANDARD);
				return true;
				
				case Player::ATTACK_SIDEA:
				playr->doChargingAttack(Controls::BUTTON_STANDARD);
				return true;
				
				case Player::ATTACK_UPA:
				playr->doChargingAttack(Controls::BUTTON_STANDARD);
				return true;
				
				case Player::ATTACK_DOWNA:
				playr->doChargingAttack(Controls::BUTTON_STANDARD);
				return true;
				
				case Player::ATTACK_B:
				playr->doChargingAttack(Controls::BUTTON_SPECIAL);
				return true;
				
				case Player::ATTACK_SIDEB:
				playr->doChargingAttack(Controls::BUTTON_SPECIAL);
				return true;
				
				case Player::ATTACK_UPB:
				playr->doChargingAttack(Controls::BUTTON_SPECIAL);
				return true;
				
				case Player::ATTACK_DOWNB:
				playr->doChargingAttack(Controls::BUTTON_SPECIAL);
				return true;
				
				case Player::ATTACK_FINALSMASH:
				playr->doChargingAttack(Controls::BUTTON_SPECIAL);
				return true;
			}
			currentlyChargingAttack = -1;
		}
		return false;
	}

	int AttackRandomizer::totalAttacks(byte attacktype)
	{
		return getAttackList(attacktype)->size();
	}

	boolean AttackRandomizer::attackMustCharge(byte attack)
	{
		if(attack==Player::ATTACK_FINALSMASH)
		{
			return finalsmashCharge;
		}
		else
		{
			int indexNo = -1;
			byte type = Player::ATTACKTYPE_MELEE;
			while(type<=9)
			{
				ArrayList<AttackProbability>*list = getAttackList(type);
				indexNo = getAttackIndex(list, attack);
				if(indexNo>-1)
				{
					AttackProbability&attackProb = list->get(indexNo);
					return attackProb.mustCharge();
				}
				type++;
			}
		}
		return false;
	}

	boolean AttackRandomizer::checkAttackType(byte attack, byte attacktype)
	{
		ArrayList<AttackProbability>*list = getAttackList(attacktype);
		for(int i=0; i<list->size(); i++)
		{
			if(list->get(i).getAttackNo() == attack)
			{
				return true;
			}
		}
		return false;
	}

	ArrayList<AttackRandomizer::AttackProbability>*AttackRandomizer::getAttackList(byte attacktype)
	{
		switch(attacktype)
		{
			case Player::ATTACKTYPE_MELEE:
			return melee;
			
			case Player::ATTACKTYPE_UPMELEE:
			return upmelee;
			
			case Player::ATTACKTYPE_DOWNMELEE:
			return downmelee;
			
			case Player::ATTACKTYPE_STRONGMELEE:
			return strongmelee;
			
			case Player::ATTACKTYPE_SIDEMOVE:
			return sidemove;
			
			case Player::ATTACKTYPE_UPMOVE:
			return upmove;
			
			case Player::ATTACKTYPE_DOWNMOVE:
			return downmove;
			
			case Player::ATTACKTYPE_PROJECTILE:
			return projectile;
			
			case Player::ATTACKTYPE_DEFENSIVE:
			return defensive;
		}
		return null;
	}

	float AttackRandomizer::getTotalAttackProbability(byte attacktype)
	{
		switch(attacktype)
		{
			case Player::ATTACKTYPE_MELEE:
			return meleeProb;
			
			case Player::ATTACKTYPE_UPMELEE:
			return upmeleeProb;
			
			case Player::ATTACKTYPE_DOWNMELEE:
			return downmeleeProb;
			
			case Player::ATTACKTYPE_STRONGMELEE:
			return strongmeleeProb;
			
			case Player::ATTACKTYPE_SIDEMOVE:
			return sidemoveProb;
			
			case Player::ATTACKTYPE_UPMOVE:
			return upmoveProb;
			
			case Player::ATTACKTYPE_DOWNMOVE:
			return downmoveProb;
			
			case Player::ATTACKTYPE_PROJECTILE:
			return projectileProb;
			
			case Player::ATTACKTYPE_DEFENSIVE:
			return defensiveProb;
		}
		return 0;
	}

	int AttackRandomizer::getAttackIndex(ArrayList<AttackProbability>*list, byte attack)
	{
		for(int i=0; i<list->size(); i++)
		{
			if(list->get(i).getAttackNo() == attack)
			{
				return i;
			}
		}
		return -1;
	}
}