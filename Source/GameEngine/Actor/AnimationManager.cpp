
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
	
	void AnimationManager::add(Animation*anim)
	{
		animations.add(anim);
	    totalAnimations++;
	}
	
	bool AnimationManager::remove(const String&animName)
	{
		for(int i=(totalAnimations-1); i>=0; i--)
		{
			Animation*cAnim = animations.get(i);
			if(animName.equals(cAnim->name))
			{
				animations.remove(i);
				delete cAnim;
				totalAnimations--;
				return true;
			}
		}
		Console::WriteLine((String)"Error: animation " + animName + (String)" could not be removed");
		return false;
	}
	
	Animation*AnimationManager::get(const String&animName)
	{
		for(int i=0; i<totalAnimations; i++)
		{
			Animation*cAnim = animations.get(i);
			if(animName.equals(cAnim->name))
			{
				return cAnim;
			}
		}
		Console::WriteLine((String)"Error: animation " + animName + (String)" does not exist!");
		return NULL;
	}
	
	bool AnimationManager::contains(const String&animName)
	{
		for(int i=0; i<totalAnimations; i++)
		{
			Animation*cAnim = animations.get(i);
			if(animName.equals(cAnim->name))
			{
				return true;
			}
		}
		return false;
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