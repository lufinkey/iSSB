
#include "../../Player.h"

#pragma once

namespace SmashBros
{
	class Samus : public Player
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
		
		int oldSmashPower;
		
		class Blast : public Projectile
		{
		private:
			float startX;

		public:
			Blast(byte playerNo, float x1, float y1);
			virtual ~Blast();
			
			virtual void deflect(byte dir);
			virtual void Update(long gameTime);
			virtual void onPlayerHit(Player*collide, byte dir);
		};

		class SpinningBlade : public Projectile
		{
		private:
			int hits;

		public:
			SpinningBlade(byte playerNo, float x1, float y1);
			virtual ~SpinningBlade();

			virtual void Update(long gameTime);
			virtual void Draw(Graphics2D&g, long gameTime);

			virtual void onAnimationFinish(const String&n);
			virtual void onPlayerHit(Player*collide, byte dir);
		};

		class GroundStab : public Projectile
		{
		public:
			GroundStab(byte playerNo, float x1, float y1);
			virtual ~GroundStab();

			virtual void onPlayerHit(Player*collide, byte dir);
			virtual void onAnimationFinish(const String&n);
		};

		class FinalSmashFire : public Projectile
		{
		public:
			FinalSmashFire(byte playerNo, float x1, float y1);
			virtual ~FinalSmashFire();

			virtual void onPlayerHit(Player*collide, byte dir);
			virtual void onAnimationFinish(const String&n);
		};


		static const float finalsmashOffsetX;
		static const float finalsmashOffsetY;

		bool prepping;
		bool finishing;
		byte charging;
		bool finalsmash_snatching;
		int lastFinalsmashFrame;
		ArrayList<Player*> finalsmashVictims;

	public:
		Samus(float x1, float y1, byte playerNo, byte team);
		virtual ~Samus();
		
		virtual void addP2PData(DataVoid&data);
		virtual void setP2PData(byte*&data);

		virtual void Update(long gameTime);
		virtual void Draw(Graphics2D&g, long gameTime);

		virtual void Load();
		virtual void LoadAttackTypes();
		virtual void setToDefaultValues();
		virtual void onAnimationFinish(const String&n);

		virtual void jump();
		virtual void whilePlayerColliding(Player*collide, byte dir);
		virtual void onPlayerHit(Player*collide, byte dir);
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