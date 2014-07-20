
#include "Projectile.h"

#pragma once

namespace SmashBros
{
	class ProjectileManager
	{
		friend class Global;
		friend class Player;
		friend class P2PDataManager;
		friend class Projectile;
	private:
		static ArrayList<Projectile*> projectiles;
		static ArrayList<int> destroyedProjectiles;
		
		static void handleAddP2PData(DataVoid&data);
		static void handleSetP2PData(byte*&data);
		
		static void CheckProjectileCollision(Projectile*projectile, Player*playr);
		
		static bool checkIDAvailable(int projID);
	public:
		static Projectile* GetProjectile(int projID);
		
		static void AddProjectile(Projectile*p);
		static void RemoveAll();
		static void Update(long gameTime);
		static void DrawBottomLayer(Graphics2D&g, long gameTime);
		static void DrawMiddleLowerLayer(Graphics2D&g, long gameTime);
		static void DrawMiddleUpperLayer(Graphics2D&g, long gameTime);
		static void DrawTopLayer(Graphics2D&g, long gameTime);
	};
}