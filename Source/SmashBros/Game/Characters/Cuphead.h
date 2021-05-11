
#include "../../Player.h"

#pragma once

namespace SmashBros
{
	class Fox : public Player
	{
	private:
		class Ray : public Projectile
		{
		public:
			Ray(byte playerNo, float x1, float y1);
			virtual ~Ray();

			virtual void deflect(byte dir);
			virtual void onPlayerHit(Player*collide, byte dir);
		};

		class LandmasterShot : public Projectile
		{
		public:
			LandmasterShot(byte playerNo, float x1, float y1);
			virtual ~LandmasterShot();

			virtual void onPlayerHit(Player*collide, byte dir);
		};

		class LandmasterHoverBlast : public Projectile
		{
		public:
			LandmasterHoverBlast(byte playerNo, float x1, float y1);
			virtual ~LandmasterHoverBlast();

			virtual void Update(long gameTime);
			virtual void onAnimationFinish(const String&name);
		};

		class Landmaster : public Projectile
		{
		private:
			int attack;
			float weight;

		public:
			Landmaster(byte playerNo, float x1, float y1);
			virtual ~Landmaster();

			virtual void Update(long gameTime);
			virtual void onAnimationFinish(const String&n);
			int getAttackNo();
			void idle();
			void shoot();
		};

		long finalsmashTime;
		boolean finalSmashing;
		boolean finalsmashFinishing;
		boolean prevJumping;
		float oldScale;
		int lastKickFrame;
		byte lastBUpChargeDir;
		byte lastDir;
		boolean queueStandardCombo;
		Landmaster*landmaster;

	public:
		Fox(float x1, float y1, byte playerNo, byte team);
		virtual ~Fox();

		virtual void Update(long gameTime);
		virtual void setToDefaultValues();
		virtual void Load();
		virtual void LoadAttackTypes();
		virtual void onDestroy();
		virtual void onAnimationFinish(const String&n);
		virtual void jump();
		virtual boolean onDeflectPlayerDamage(Player*collide, int damage);
		virtual void onDeflectPlayerLaunch(Player*collide, int xDir, float xAmount, float xMult, int yDir, float yAmount, float yMult);
		virtual boolean onDeflectProjectileCollision(Projectile*collide, byte dir);
		virtual boolean onDeflectItemCollision(Item*collide, byte dir);

		virtual void onPlayerHit(Player*collide, byte dir);
		virtual void onQueueAttack(byte attackType);

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