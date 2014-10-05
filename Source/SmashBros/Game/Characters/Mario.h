
#include "../../Player.h"

#pragma once

namespace SmashBros
{
	class Mario : public Player
	{
	private:
		byte charging_attack;
		boolean chargedDownAttack;
		long chargeDownTime;
		
		typedef struct
		{
			byte type;
			int projID;
			float x;
			float y;
		} ProjectileInfo;
		
		void addProjectileInfo(byte type, int projID, float x, float y);
		
		ArrayList<ProjectileInfo> createdProjectiles;
		
		class Fireball : public Projectile
		{
		private:
			long liveTime;
			float xspeed;
			float yspeed;
			
		public:
			Fireball(byte playerNo, float x1, float y1);
			virtual ~Fireball();

			virtual void Update(long gameTime);
			
			virtual void deflect(byte dir);
			virtual void onPlayerHit(Player*collide, byte dir);
			virtual void whilePlatformColliding(Platform*collide, byte dir);
		};
		
		class FluddWater : public Projectile
		{
		public:
			FluddWater(byte playerNo, float x1, float y1);
			virtual ~FluddWater();

			virtual void Update(long gameTime);

			virtual void whilePlayerHitting(Player*collide, byte dir);
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
		
	public:
		Mario(float x1, float y1, byte playerNo, byte team);
		virtual ~Mario();
		
		virtual void addP2PData(DataVoid&data);
		virtual void setP2PData(byte*&data);
		
		virtual void Update(long gameTime);
		virtual void Draw(Graphics2D&g, long gameTime);
		virtual void setToDefaultValues();
		virtual void Load();
		virtual void LoadAttackTypes();
		virtual void Unload();
		virtual void onAnimationFinish(const String&n);
		virtual void jump();
		virtual void onPlayerHit(Player*collide, byte dir);
		virtual void onPlayerRectHit(Player*collide, byte dir);
		virtual boolean onDeflectProjectileCollision(Projectile*collide, byte dir);
		virtual boolean onDeflectItemCollision(Item*collide, byte dir);
		
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