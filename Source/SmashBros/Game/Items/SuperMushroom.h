
#include "../../Item.h"

#pragma once

namespace SmashBros
{
	class SuperMushroom : public Item
	{
	private:
		boolean moving;
		float scale;
		long finishTime;
		boolean active;
		byte dir;

	public:
		SuperMushroom(float x1, float y1);
		virtual ~SuperMushroom();

		virtual void Update(long gameTime);

		virtual boolean canPickUp();
		virtual void onPlayerCollide(Player*collide);
		virtual void onPlatformCollide(Platform*collide, byte dir);
		virtual void onGroundCollide();
		virtual void onDestroy();
	};
}