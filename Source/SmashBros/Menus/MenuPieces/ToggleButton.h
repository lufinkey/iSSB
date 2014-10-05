
#include "../../../GameEngine/GameEngine.h"

#pragma once

namespace SmashBros
{
	class ToggleButton : public Actor
	{
	private:
		boolean toggle;

	public:
		ToggleButton(float x1, float y1, boolean toggle=false);
		virtual ~ToggleButton();

		virtual void Update(long gameTime);
		virtual void onRelease();
		virtual void onToggle(boolean toggle);

		void setToggle(boolean toggle);
		boolean getToggle();
	};
}