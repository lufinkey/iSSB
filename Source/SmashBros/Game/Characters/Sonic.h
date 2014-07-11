
#include "../../Player.h"

#pragma once

namespace SmashBros
{
	class Sonic : public Player
	{
	private:
		typedef struct
		{
			byte type;
			int projID;
			float x;
			float y;
		} ProjectileInfo;
		
		void addProjectileInfo(byte type, int projID, float x, float y);
		
		ArrayList<ProjectileInfo> createdProjectiles;
		
		class Spring : public Projectile
		{
		private:
			long deadTime;

		public:
			Spring(byte playerNo, float x1, float y1);
			virtual ~Spring();

			virtual void Update(long gameTime);

			virtual void onAnimationFinish(const String&n);
			virtual void onPlayerHit(Player*collide, byte dir);
			virtual void whilePlatformColliding(Platform*collide, byte dir);

		};

		class Emeralds : public Projectile
		{
		public:
			Emeralds(byte playerNo, float x1, float y1);
			virtual ~Emeralds();

			virtual void onAnimationFinish(const String&n);
		};

		boolean turning;
		boolean winding;
		boolean finalSmashing;
		byte chargeAttack;

		float xprevious;
		float yprevious;

		float rollSpeed;
		float rocketSpeed;
		float sonicSpeedRun;

	public:
		Sonic(float x1, float y1, byte playerNo, byte team);
		virtual ~Sonic();
		
		virtual void addP2PData(DataVoid&data);
		virtual void setP2PData(byte*&data);

		virtual void Update(long gameTime);
		virtual void Draw(Graphics2D&g, long gameTime);

		virtual void Load();
		virtual void LoadAttackTypes();
		virtual void setToDefaultValues();
		virtual void onDestroy();
		virtual boolean checkIfAble();
		
		virtual void onAnimationFinish(const String&n);
		virtual void onGroundCollide();
		virtual void jump();
		virtual void onPlayerHit(Player*collide, byte dir);
		virtual void onPlayerRectHit(Player*collide, byte dir);

		virtual void onFinishCharge();
		virtual void doChargingAttack(byte button);

		virtual void attackA();
		virtual void attackSideA();
		virtual void attackUpA();
		virtual void attackDownA();
		virtual void attackB();
		virtual void attackSideB();
		virtual void attackUpB();
		virtual void attackDownB();
		virtual void attackSideSmash(byte type);
		virtual void attackUpSmash(byte type);
		virtual void attackDownSmash(byte type);
		virtual void attackFinalSmash();
	};
}