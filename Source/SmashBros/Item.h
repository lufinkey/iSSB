
#include "GameElement.h"
#include "CollisionManager.h"
#include "Game/Stages/StagePieces/Platform.h"
#include "Projectile.h"
#include "SmashForwards.h"

#pragma once

namespace SmashBros
{
	class Item : public GameElement
	{
		friend class P2PDataManager;
		friend class Player;
		friend class Stage;
	private:
		typedef struct
		{
			byte playerNo;
			byte dir;
		} PlayerCollisionArgs;
		
		static int nextID;
		int id;
		
		byte type;
		byte collideType;
		
		boolean accelGrav;
		boolean ignoreGoThrough;
		
		long finishTime;
		
		boolean dead;
		boolean isSolid;
		boolean bound;
		boolean canCarry;
		boolean held;
		byte ownerNo;
		byte holderNo;
		boolean hitState;
		boolean deflectable;
		boolean tossOnDiscard;
		boolean tossing;
		float offsetX;
		float offsetY;
		
		int index;
		friend class ItemManager;
		
		CollisionManager playerCollisions;
		CollisionManager playerHits;
		
		boolean platformColliding[8];
		boolean prevPlatformColliding[8];
		
		boolean groundColliding;
		boolean prevGroundColliding;
		
		Platform*currentCollidePlatform[8];
		
		ArrayList<PlayerCollisionArgs> playerCollideDelays;
		
		void whenPickedUp(Player*collide);
		void whenDiscarded();
		void whenTossed(byte tossAttackType);
		
		void platformCollision(Platform*collide, byte dir);
		void checkPlayerCollision(Player*playr);
		boolean isHittable(Player*collide);
		
		byte solidPlatformCollision(Platform*collide);
		byte normalPlatformCollision(Platform*collide);
		
		void handleAddP2PData(DataVoid&data);
		void handleSetP2PData(byte*&data);
		
	protected:
		int itemNo;
		float weight;
		
		void setItemOwner(byte owner);
		void setSolid(boolean toggle);
		void ignoreGoThroughPlatforms(boolean toggle);
		void createProjectile(Projectile*p);
		void setHitState(boolean toggle);
		void setDeflectable(boolean toggle);
		void setCollideType(byte type);
		void accelerateGravity(boolean toggle);
		void enableTossOnDiscard(boolean toggle);
		void causeDamage(Player*collide, int amount);
		void causeHurtLaunch(Player*collide, int xDir, float xAmount, float xMult, int yDir, float yAmount, float yMult);
		void causeHurt(Player*collide, byte dir, int time);
		
	public:
		static const byte TYPE_HOLD = 0;
		static const byte TYPE_WEAR = 1;
		static const byte TYPE_HAT = 2;
		static const byte TYPE_WIELD = 3;
		static const byte TYPE_FOOD = 4;
		
		static const byte POWERUP_FINALSMASH = 0;
		static const byte POWERUP_HEAL = 1;
		
		static const byte COLLIDE_BOX = 1;
		static const byte COLLIDE_SOLID = 2;
		
		Item(float x1, float y1, long liveTime, byte type);
		virtual ~Item();
		
		int getID();
		static void setNextID(int itemID);
		
		virtual void addP2PData(DataVoid&data);
		virtual void setP2PData(byte*&data);
		
		virtual void Update(long gameTime);
		virtual void Draw(Graphics2D&g, long gameTime);
		virtual void onPickUp(Player*collide);
		virtual void onDiscard(Player*discarder);
		virtual void onToss(Player*tosser, byte tossAttackType);
		virtual void onPlayerCollide(Player*collide);
		virtual void whilePlayerColliding(Player*collide);
		virtual void finishPlayerCollide(Player*collide);
		virtual void onPlayerHit(Player*collide, byte dir);
		virtual void whilePlayerHitting(Player*collide, byte dir);
		virtual void finishPlayerHit(Player*collide);
		virtual void onPlatformCollide(Platform*collide, byte dir);
		virtual void whilePlatformColliding(Platform*collide, byte dir);
		virtual void finishPlatformCollide(Platform*collide, byte dir);
		virtual void onGroundCollide();
		virtual void whileGroundColliding();
		virtual void finishGroundCollide();
		virtual void onHolderHurt();
		virtual boolean holderCanDo();
		virtual void onCreate();
		virtual void onDestroy();
		virtual void deflect(byte dir);
		
		virtual boolean canPickUp();
		virtual boolean allowsGrabDelay();
		virtual boolean use(byte attackType);
		
		void addAnimation(Animation*a);
		
		void addFileResource(String file);
		void canBeCarried(boolean toggle);
		int getItemNo();
		byte getItemOwner();
		byte getItemHolder();
		void setBoundToHolder(boolean toggle);
		void setHoldOffset(float x1, float y1);
		Player*getPlayer();
		boolean isHeld();
		boolean chargeSmash(byte attackType);
		void discard();
		void toss(byte tossAttackType);
		void destroy();
		
		void doPowerUp(Player*collide, byte type, float value);
	};
}