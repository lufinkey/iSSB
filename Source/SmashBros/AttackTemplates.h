
#include "SmashForwards.h"
#include "Player.h"

#pragma once

namespace SmashBros
{
	class AttackTemplates
	{
		friend class Player;
	private:
		//static void causeKnockback(Player*playr, Player* collide, float damage, float knockbackUnits, float knockbackAngle, float knockbackScaling, boolean fixed = false);
		static void causeDamage(Player*playr, Player*collide, int amount);
		static void causeHurtLaunch(Player*playr, Player*collide, int xDir, float xAmount, float xMult, int yDir, float yAmount, float yMult);
		static void causeHurt(Player*playr, Player*collide, byte dir, int time);

	public:
		static const byte SMASH_SIDE = 1;
		static const byte SMASH_UP = 2;
		static const byte SMASH_DOWN = 3;
		
		static void normalA(Player*playr, int aNo, double aP);
		static void combo2A(Player*playr, long comTime, int aNo,double aP,int aNo2,double aP2, boolean loopLast=false);
		static void combo3A(Player*playr, long comTime, int aNo,double aP,int aNo2,double aP2,int aNo3, double aP3, boolean loopLast=false);
		static void normalAirA(Player*playr, int aNo, double aP);
		static void normalSideA(Player*playr, int aNo, double aP);
		static void normalDashA(Player*playr, int aNo, double aP, float speed);
		static void normalAirSideA(Player*playr, int aNo, double aP);
		static void rehitAirSideA(Player*playr, int aNo, double aP);
		static void normalUpA(Player*playr, int aNo, double aP);
		static void normalAirUpA(Player*playr, int aNo, double aP);
		static void normalDownA(Player*playr, int aNo, double aP);
		static void normalAirDownA(Player*playr, int aNo, double aP);
		static void singleAirDownA(Player*playr, int aNo, double aP);
		static void dropAirDownA(Player*playr, int type, int aNo, double aP, float speedY, float speedX);
		static void normalB(Player*playr, int aNo, double aP);
		static void chargeB(Player*playr, float spMin, float spMax, long totalTime);
		static void homingB(Player*playr, int aNo, double aP, float speed);
		static void singleProjectile(Player*playr, int aNo, double aP, Projectile*projectile);
		static void normalSideB(Player*playr, int aNo, double aP);
		static void moveSideB(Player*playr, int aNo, double aP, float xDist);
		static void dashSideB(Player*playr, int aNo, double aP, float speed);
		static void rollAttack(Player*playr, int aNo, double aP, float speed, long time);
		static void launchUpB(Player*playr, int aNo, double aP, float yVeloc, float yVeloc2);
		static void rehitUpB(Player*playr, int aNo, double aP, float yVeloc, float yVeloc2);
		static void rehitUpB2(Player*playr, int aNo, double aP, float yVeloc, float yVeloc2);
		static void normalDownB(Player*playr,int aNo,double aP);
		static void prepareDownB(Player*playr, int aNo, double aP);
		static void bounceDownB(Player*playr,int aNo,double aP,float speed);
		static void normalSmash(Player*playr, int aNo, double aP, byte type, int smashType, long totalTime, int cMin, int cMax);
		static void stopSmashAttack(Player*playr);
		static void finalSmash(Player*playr, int aNo);
		static void finishFinalSmash(Player*playr);
	};
}