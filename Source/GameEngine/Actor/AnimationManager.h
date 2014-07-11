
#include "../forwards.h"
#include "../Util/ArrayList.h"
#include "Animation.h"

#pragma once

namespace GameEngine
{
	class AnimationManager //handles an Actor's animations so that an Actor can switch animations using ChangeAnimation(String,String)
	{
		friend class Actor;
	private:
		ArrayList<Animation*> animations; //stores animations. all animations are identified by their String name
		int totalAnimations;

	public:
		AnimationManager();
		AnimationManager(const AnimationManager& animMgr);
		virtual ~AnimationManager();
	
		void add(Animation*a);
		bool remove(String aName);
		Animation*get(String aName);
		AnimationManager& operator=(const AnimationManager& animMgr);
	};
}