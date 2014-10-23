
#include "CollisionManager.h"

namespace SmashBros
{
	CollisionManager::CollisionManager()
	{
		collisions = ArrayList<int>();
	}
	
	CollisionManager::~CollisionManager()
	{
		collisions.clear();
	}
	
	void CollisionManager::addCollision(int id)
	{
		if(!isColliding(id))
		{
			collisions.add(id);
		}
	}
	
	void CollisionManager::removeCollision(int id)
	{
		for(int i=0; i<collisions.size(); i++)
		{
			int cmp = collisions.get(i);
			if(id==cmp)
			{
				collisions.remove(i);
				return;
			}
		}
	}
	
	void CollisionManager::clear()
	{
		collisions.clear();
	}
	
	boolean CollisionManager::isColliding(int id)
	{
		for(int i=0; i<collisions.size(); i++)
		{
			int cmp = collisions.get(i);
			if(id==cmp)
			{
				return true;
			}
		}
		return false;
	}
}