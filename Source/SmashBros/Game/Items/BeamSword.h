
#include "../../Item.h"

#pragma once

namespace SmashBros
{
	class BeamSword : public Item
	{
	private:
		boolean active;
		byte attackDir;
		int smashPower;

	public:
		BeamSword(float x1, float y1);
		virtual ~BeamSword();

		virtual void Update(long gameTime);

		virtual boolean holderCanDo();
		virtual void onDiscard(Player*discarder);
		virtual boolean chargeSmash();
		virtual boolean use(byte attackDir);
		virtual void onPlayerHit(Player*collide, byte dir);
		virtual void onAnimationFinish(const String&name);
	};
}