
#include "../../Player.h"
#include "../../Item.h"

#pragma once

namespace SmashBros
{
	class Link : public Player
	{
	private:
		typedef struct
		{
			byte type;
			int projID;
			float x;
			float y;
			float power;
		} ProjectileInfo;
		
		void addProjectileInfo(byte type, int projID, float x, float y, float power = 0);
		
		ArrayList<ProjectileInfo> createdProjectiles;
		
		class Arrow : public Projectile
		{
		private:
			byte arrowdir;
			float power;
			boolean onGround;
			long disappearTime;

		public:
			Arrow(byte playerNo, float x1, float y1, float power);
			virtual ~Arrow();
			
			virtual void Update(long gameTime);

			virtual void deflect(byte dir);
			virtual void onPlayerHit(Player*collide, byte dir);
			virtual void whileGroundColliding();
		};

		class Boomerang : public Projectile
		{
		private:
			static const float SPEED;
			static const float INCREMENT;

			byte boomerangdir;
			boolean returning;
			boolean canTurn;
			boolean pulling;
			long nextHitTime;
			long creationTime;

		public:
			Boomerang(byte playerNo, float x1, float y1);
			virtual ~Boomerang();

			virtual void Update(long gameTime);

			virtual void deflect(byte dir);
			virtual void onPlayerHit(Player*collide, byte dir);
			virtual void whilePlayerHitting(Player*collide, byte dir);
			virtual void whilePlatformColliding(Platform*collide, byte dir);
		};

		class Bomb : public Item
		{
		private:
			byte bombdir;
			boolean exploded;
			boolean active;
			boolean grounded;

		public:
			Bomb(float x1, float y1);
			virtual ~Bomb();

			virtual void onAnimationFinish(const String&name);
			virtual void Update(long gameTime);

			virtual boolean use(byte attackDir);
			virtual boolean canPickUp();
			virtual boolean allowsGrabDelay();
			virtual void onPickUp(Player*collide);
			virtual void onDiscard(Player*discarder);
			virtual void onPlayerHit(Player*collide, byte dir);
			virtual void onPlatformCollide(Platform*collide, byte dir);

			void explode();
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
		Link(float x1, float y1, byte playerNo, byte team);
		virtual ~Link();
		
		virtual void addP2PData(DataVoid&data);
		virtual void setP2PData(byte*&data);

		virtual void Update(long gameTime);
		virtual void Draw(Graphics2D&g, long gameTime);
		virtual void setToDefaultValues();
		virtual boolean checkIfAble();
		virtual void Load();
		virtual void LoadAttackTypes();
		virtual void Unload();
		virtual void onAnimationFinish(const String&n);
		virtual void jump();
		virtual void onPlayerHit(Player*collide, byte dir);
		virtual void finishPlayerRectHit(Player*collide);
		virtual void onGroundCollide();

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