
#include "../../../GameEngine/GameEngine.h"

#pragma once

namespace SmashBros
{
	class TogglePane : public Actor
	{
	private:
		boolean toggle;

	public:
		TogglePane(float x1, float y1, boolean toggle = false);
		virtual ~TogglePane();

		virtual void Update(long gameTime);
		virtual void onRelease();
		virtual void onToggle(boolean toggle);

		void setToggle(boolean toggle);
		boolean getToggle();
	};
}