
#include "../../Player.h"

#pragma once

namespace SmashBros
{
	class Ichigo : public Player
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

		class FinalSmashBlast : public Projectile
		{
		public:
			FinalSmashBlast(byte playerNo, float x1, float y1);
			~FinalSmashBlast();

			virtual void onPlayerHit(Player*collide, byte dir);
		};

		byte charging;
		boolean finalSmash;
		boolean dropDownAttack;

	public:
		Ichigo(float x1, float y1, byte playerNo, byte team);
		virtual ~Ichigo();
		
		virtual void addP2PData(DataVoid&data);
		virtual void setP2PData(byte*&data);

		virtual void Update(long gameTime);
		virtual void Draw(Graphics2D&g, long gameTime);

		virtual void Load();
		virtual void LoadAttackTypes();
		virtual void setToDefaultValues();
		virtual boolean checkIfAble();
		virtual void onAnimationFinish(const String&n);
		virtual void onGroundCollide();

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