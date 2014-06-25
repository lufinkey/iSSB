
#include "../GameEngine/GameEngine.h"

#pragma once

namespace SmashBros
{
	class AttackRandomizer
	{
	private:
		class AttackProbability
		{
		private:
			byte attack;
			float probability;
			boolean charge;
			AttackRandomizer*randomizer;

		public:
			AttackProbability();
			AttackProbability(AttackRandomizer*randomizer, byte attack, float probability, boolean charge);
			virtual ~AttackProbability();

			void doAttack();
			byte getAttackNo();
			float getProbability();
			boolean mustCharge();
		};
		
		ArrayList<AttackProbability>*melee;
		float meleeProb;
		ArrayList<AttackProbability>*upmelee;
		float upmeleeProb;
		ArrayList<AttackProbability>*downmelee;
		float downmeleeProb;
		ArrayList<AttackProbability>*strongmelee;
		float strongmeleeProb;
		ArrayList<AttackProbability>*sidemove;
		float sidemoveProb;
		ArrayList<AttackProbability>*upmove;
		float upmoveProb;
		ArrayList<AttackProbability>*downmove;
		float downmoveProb;
		ArrayList<AttackProbability>*projectile;
		float projectileProb;
		ArrayList<AttackProbability>*defensive;
		float defensiveProb;

		byte currentlyChargingAttack;
		
		boolean finalsmashCharge;

		int playerNo;

		byte doRandomAttack(byte attacktype);
		ArrayList<AttackProbability>*getAttackList(byte attacktype);
		float getTotalAttackProbability(byte attacktype);
		int getAttackIndex(ArrayList<AttackProbability>*list, byte attack);

	public:
		AttackRandomizer(int playerNo = 0);
		virtual ~AttackRandomizer();

		void setPlayerNo(int playerNo);
		void setAttack(byte attack, byte attacktype, float probability, boolean charge);
		void doFinalSmash();
		byte doAttack(byte attacktype);
		boolean doChargingAttack();
		int totalAttacks(byte attacktype);
		boolean attackMustCharge(byte attack);
		boolean checkAttackType(byte attack, byte attacktype);
	};
}