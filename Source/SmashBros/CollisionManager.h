
#include "../GameEngine/GameEngine.h"

#pragma once

namespace SmashBros
{
	class CollisionManager
	{
	private:
		ArrayList<int> collisions;
		
	public:
		CollisionManager();
		virtual ~CollisionManager();

		void addCollision(int id);
		void removeCollision(int id);
		void clear();
		boolean isColliding(int id);
	};
}