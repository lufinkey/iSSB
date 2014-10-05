
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
	
		void add(Animation*anim);
		bool remove(const String&animName);
		Animation*get(const String&animName);
		bool contains(const String&animName);
		AnimationManager& operator=(const AnimationManager& animMgr);
	};
}