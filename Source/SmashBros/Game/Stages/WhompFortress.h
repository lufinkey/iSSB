
#include "../../Stage.h"

#pragma once

namespace SmashBros
{
	class WhompFortress : public Stage
	{
	private:
		class RandomThing : public GameElement
		{
		public:
			RandomThing();
			RandomThing(boolean create);
			virtual ~RandomThing();
		};
		void loadGameElements();
		void loadPlatforms();
		void loadForeground();
		void loadHangPoints();
		void loadGround();

	public:
		WhompFortress(float x1, float y1);
		~WhompFortress();

		virtual void Draw(Graphics2D&g, long gameTime);
	};
}
