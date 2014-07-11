
#include "../../Item.h"

#pragma once

namespace SmashBros
{
	class PoisonMushroom : public Item
	{
	private:
		boolean moving;
		float scale;
		long finishTime;
		boolean active;
		byte dir;

	public:
		PoisonMushroom(float x1, float y1);
		virtual ~PoisonMushroom();

		virtual void Update(long gameTime);

		virtual boolean canPickUp();
		virtual void onPlayerCollide(Player*collide);
		virtual void onPlatformCollide(Platform*collide, byte dir);
		virtual void onGroundCollide();
		virtual void onDestroy();
	};
}