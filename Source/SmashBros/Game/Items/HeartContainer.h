
#include "../../Item.h"

#pragma once

namespace SmashBros
{
	class HeartContainer : public Item
	{
	private:
		boolean available;

	public:
		HeartContainer(float x1, float y1);
		virtual ~HeartContainer();

		virtual void Update(long gameTime);
		
		virtual void onPickUp(Player*collide);
		virtual boolean canPickUp();
		virtual void onAnimationFinish(const String&n);

	};
}