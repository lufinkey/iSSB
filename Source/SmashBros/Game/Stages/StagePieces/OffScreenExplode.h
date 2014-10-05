
#include "../../../GameElement.h"

#pragma once

namespace SmashBros
{
	class OffScreenExplode : public GameElement
	{
	private:
		boolean active;
		int playerNo;

	public:
		OffScreenExplode(int playerNo);
		virtual ~OffScreenExplode();

		virtual void Update(long gameTime);
		virtual void Draw(Graphics2D&g, long gameTime);
		
		void setActive();
	};
}