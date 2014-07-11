
#include "../Util/String.h"
#include "../Graphics/Graphics2D.h"

#pragma once

namespace GameEngine
{
	class Screen
	{
		private:
			String name;
			friend class ScreenManager;
		public:
			Screen(const String&name);
			virtual ~Screen();
			virtual void Initialize();
			virtual void LoadContent();
			virtual void UnloadContent();
			virtual void Update(long gameTime);
			virtual void Draw(Graphics2D& g,long gameTime);
	};
}