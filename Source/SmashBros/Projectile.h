
#include "GameElement.h"
#include "Game/Stages/StagePieces/Platform.h"
#include "CollisionManager.h"
#include "SmashForwards.h"

#pragma once

namespace SmashBros
{
	class Projectile : public GameElement
	{
		friend class P2PDataManager;
		friend class Player;
		friend class ProjectileManager;
		friend class Stage;
	private:
		
		static int nextID;
		int id;
		
		boolean dead;
		byte playerNo;
		byte team;
		boolean solid;
		boolean solidOwner;
		byte layer;
		boolean allPlatsSolid;
		boolean deflectable;
		
		Platform*platform;
		
		CollisionManager playersColliding;
		
		byte solidPlatformCollision(Platform*collide);
		byte solidPlayerCollision(Player*collide);
		
		byte isPlatformColliding(Platform*collide);
		
		void handleAddP2PData(DataVoid&data);
		void handleSetP2PData(byte*&data);
		
	protected:
		byte itemdir;
		
		void setSolid(boolean toggle);
		void setOwnerSolid(boolean toggle);
		void detectAllPlatformsSolid(boolean toggle);
		void setDeflectable(boolean toggle);
		
		boolean isHittable(Player*collide, byte dir);
		void createProjectile(Projectile*p);
		void causeDamage(Player*collide, int amount);
		void causeHurtLaunch(Player*collide, int xDir, float xAmount, float xMult, int yDir, float yAmount, float yMult);
		void causeHurt(Player*collide, byte dir, int time);
		
	public:
		static const byte LEFT = 1;
		static const byte RIGHT = 2;
		
		static const byte LAYER_BOTTOM = 1;
		static const byte LAYER_MIDDLELOWER = 2;
		static const byte LAYER_MIDDLEUPPER = 3;
		static const byte LAYER_TOP = 4;
		
		Projectile(byte playerNo, float x1, float y1);
		virtual ~Projectile();
		
		int getID();
		static void setNextID(int projID);
		
		virtual void addP2PData(DataVoid&data);
		virtual void setP2PData(byte*&data);
		
		virtual void Update(long gameTime);
		virtual void Draw(Graphics2D&g, long gameTime);
		virtual void onDestroy();
		virtual void deflect(byte dir);
		virtual void setOwner(Player*owner);
		virtual void onPlayerHit(Player*collide, byte dir);
		virtual void whilePlayerHitting(Player*collide, byte dir);
		virtual void whileGroundColliding();
		virtual void whilePlatformColliding(Platform*collide, byte dir);
		
		byte getTeam();
		byte getItemDir();
		byte getPlayerNo();
		boolean isDead();
		boolean isSolid();
		boolean isOwnerSolid();
		void destroy();
		void setLayer(byte layer);
	};
}