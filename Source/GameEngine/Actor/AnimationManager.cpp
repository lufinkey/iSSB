
#include "AnimationManager.h"
#include "../Output/Console.h"

namespace GameEngine
{
	AnimationManager::AnimationManager()
	{
		animations = ArrayList<Animation*>();
		totalAnimations=0;
	}

	AnimationManager::AnimationManager(const AnimationManager&animMgr)
	{
		totalAnimations = animMgr.totalAnimations;
		animations = ArrayList<Animation*>();
		for(int i=0; i<animMgr.animations.size(); i++)
		{
			animations.add(new Animation(*animMgr.animations.get(i)));
		}
	}

	AnimationManager::~AnimationManager()
	{
		for(int i=0; i<animations.size(); i++)
		{
			delete animations[i];
		}
		animations.clear();
	}

	void AnimationManager::add(Animation*a)
	{
		animations.add(a);
	    totalAnimations++;
	}

	bool AnimationManager::remove(String aName)
	{
		for(int i=(totalAnimations-1); i>=0; i--)
		{
			Animation*cAnim = animations.get(i);
			if(aName.equals(cAnim->name))
			{
				animations.remove(i);
				return true;
			}
		}
		Console::WriteLine((String)"Error: animation " + aName + (String)" could not be removed");
		return false;
	}

	Animation*AnimationManager::get(String aName)
	{
		for(int i=0; i<totalAnimations; i++)
		{
			Animation*cAnim = animations.get(i);
			if(aName.equals(cAnim->name))
			{
				return cAnim;
			}
		}
		Console::WriteLine((String)"Error: animation " + aName + (String)" does not exist!");
		return NULL;
	}

	AnimationManager&AnimationManager::operator=(const AnimationManager& animMgr)
	{
		for(int i=0; i<animations.size(); i++)
		{
			delete animations[i];
		}
		animations.clear();

		totalAnimations = animMgr.totalAnimations;
		for(int i=0; i<animMgr.animations.size(); i++)
		{
			animations.add(new Animation(*animMgr.animations.get(i)));
		}
			
		return *this;
	}
}