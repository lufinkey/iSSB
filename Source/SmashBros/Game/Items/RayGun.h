
#include "../../Item.h"

#pragma once

namespace SmashBros
{
	class RayGun : public Item
	{
	private:
		byte dir;
		int ammo;
		long activeTime;
		boolean active;
		byte attackType;
		
		class Ray : public Projectile
		{
		private:
			float startX;
			
		public:
			Ray(byte playerNo, float x1, float y1);
			virtual ~Ray();
			
			virtual void deflect(byte dir);
			virtual void Update(long gameTime);
			virtual void onPlayerHit(Player*collide, byte dir);
		};
		
	public:
		RayGun(float x1, float y1);
		virtual ~RayGun();
		
		virtual void Update(long gameTime);
		
		virtual void onDiscard(Player*discarder);
		virtual boolean use(byte attackType);
		virtual boolean holderCanDo();
	};
}