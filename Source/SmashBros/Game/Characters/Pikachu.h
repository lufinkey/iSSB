
#include "../../Player.h"

#pragma once

namespace SmashBros
{
	class Pikachu : public Player
	{
	private:
		class ThunderboltType : public Projectile
		{
		public:
			ThunderboltType(byte playerNo, float x1, float y1);
			virtual ~ThunderboltType();

			virtual void onPlayerHit(Player*collide, byte dir);
		};

		class Thunderbolt : public ThunderboltType
		{
			friend class Pikachu;
		private:
			class ThunderboltGhost : public ThunderboltType
			{
				friend class Thunderbolt;
			private:
				boolean drift;
				boolean lethal;
				int waitFrames;
				Thunderbolt*leader;

			public:
				ThunderboltGhost(Thunderbolt*bolt, byte playerNo, byte dir, bool drift, float x1, float y1);
				virtual ~ThunderboltGhost();
				
				virtual void deflect(byte dir);
				virtual void Update(long gameTime);
				virtual void onPlayerHit(Player*collide, byte dir);
			};

			static const float vel;
			static const float incr;

			long destroyTime;
			int waitFrames;
			byte stage;
			boolean drift;
			boolean willDie;
			byte projdir;
			ArrayList<ThunderboltGhost*> trail;

		public:
			Thunderbolt(byte playerNo, float x1, float y1);
			virtual ~Thunderbolt();
			
			virtual void deflect(byte dir);
			virtual void Update(long gameTime);
			virtual void setOwner(Player*owner);
			virtual void whilePlatformColliding(Platform*platform, byte dir);
			virtual void onPlayerHit(Player*collide, byte dir);

			void setBoltDir(byte dir);
		};

		class LightningType : public Projectile
		{
		public:
			LightningType(byte playerNo, float x1, float y1);
			virtual ~LightningType();

			virtual void onPlayerHit(Player*collide, byte dir);
		};

		class Lightning : public LightningType
		{
			friend class Pikachu;
		private:
			class LightningBody : public LightningType
			{
				friend class Pikachu::Lightning;
			private:
				boolean frameOn;
				boolean isEnd;
				Lightning*leader;

			public:
				LightningBody(Lightning*leader, byte playerNo, float x1, float y1, boolean frameNo);
				virtual ~LightningBody();

				virtual void Update(long gameTime);

				void toggleFrame();
				void setEnd(boolean toggle);
			};

			ArrayList<LightningBody*> bodies;
			int waitFrames;
			boolean hitGround;
			boolean createdFrame;
			
		public:
			Lightning(byte playerNo, float x1, float y1);
			virtual ~Lightning();

			virtual void Update(long gameTime);
			virtual void Draw(Graphics2D&g, long gameTime);

			virtual void onAnimationFinish(const String&name);
			virtual void whilePlatformColliding(Platform*platform, byte dir);
		};

		const static float finalsmashSlow;
		const static float finalsmashFast;
		
		typedef struct
		{
			byte type;
			int projID;
			float x;
			float y;
			
			byte itemdir;
			int ownerID;
		} ProjectileInfo;
		
		void addProjectileInfo(byte type, int projID, float x, float y, byte itemdir, int ownerID);
		
		ArrayList<ProjectileInfo> createdProjectiles;

		float xprevious;
		float yprevious;
		long nextHitTime;
		long finishSideB;
		long finishFinalsmash;
		boolean transUpB;
		boolean chargingSideB;
		boolean preppingDownB;
		byte upBDir;
		byte upBCount;
		boolean winding;
		boolean awaitingStrike;
		boolean finalsmash;
		byte finalsmashTransition;

		void upBIncrement(byte dir);

	public:
		Pikachu(float x1, float y1, byte playerNo, byte team);
		virtual ~Pikachu();
		
		void addP2PData(DataVoid&data);
		void setP2PData(byte*&data);

		virtual void Update(long gameTime);
		virtual void Draw(Graphics2D&g, long gameTime);
		virtual void setToDefaultValues();
		virtual void onDestroy();
		virtual boolean checkIfAble();
		virtual void Load();
		virtual void LoadAttackTypes();
		virtual void Unload();
		virtual void onAnimationFinish(const String&n);
		virtual void jump();
		virtual void onPlayerHit(Player*collide, byte dir);

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