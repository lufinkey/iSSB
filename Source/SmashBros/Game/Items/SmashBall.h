
#include "../../Item.h"

#pragma once

namespace SmashBros
{
	class SmashBall : public Item
	{
	private:
		Projectile*readyFire;
		long moveTime;
		float speed;
		boolean hittable;
		long unHittableTime;
		boolean active;
		int health;
		
		boolean createdReadyFire;
		byte readyFirePno;
		float readyFireX;
		float readyFireY;

		void hitSmashBall(Player*collide, byte dir);
		void setDirection(byte dir, float speed);
		void setDirection();

	public:
		SmashBall(float x1, float y1);
		virtual ~SmashBall();
		
		virtual void addP2PData(DataVoid&data);
		virtual void setP2PData(byte*&data);

		virtual void Update(long gameTime);
		virtual void Draw(Graphics2D&g, long gameTime);
		virtual void onAnimationFinish(const String&n);
		virtual void onCreate();
		virtual void onDestroy();
		virtual void onPickUp(Player*collide);
		virtual boolean canPickUp();
		virtual void whilePlatformColliding(Platform*collide, byte dir);
		virtual void whilePlayerColliding(Player*collide);
	};
}