
#include "../GameEngine/GameEngine.h"

#pragma once

namespace SmashBros
{
	class AttackManager
	{
		friend class Player;
	private:
		class AttackInfo
		{
		public:
			int attackNo;
			byte playerdir;
			int damage;
			long delayTime;
			int xDir,yDir;
			float xAmount,xMult,yAmount,yMult;
			boolean dirIsPixelBased;

			AttackInfo();
			AttackInfo(int attackNo, byte playerdir, int damage, long delayTime, int xDir,float xAmount,float xMult,int yDir,float yAmount,float yMult, boolean dirIsPixelBased = true);
			virtual ~AttackInfo();

			operator String();
		};

		ArrayList<AttackInfo> up;
		ArrayList<AttackInfo> down;
		ArrayList<AttackInfo> left;
		ArrayList<AttackInfo> right;

	public:
		AttackManager();
		virtual ~AttackManager();

		void addUpAttackInfo(int attackNo, byte playerdir, int damage, long delayTime, int xDir,float xAmount,float xMult,int yDir,float yAmount,float yMult, boolean dirIsPixelBased = true);
		void addDownAttackInfo(int attackNo, byte playerdir, int damage, long delayTime, int xDir,float xAmount,float xMult,int yDir,float yAmount,float yMult, boolean dirIsPixelBased = true);
		void addLeftAttackInfo(int attackNo, byte playerdir, int damage, long delayTime, int xDir,float xAmount,float xMult,int yDir,float yAmount,float yMult, boolean dirIsPixelBased = true);
		void addRightAttackInfo(int attackNo, byte playerdir, int damage, long delayTime, int xDir,float xAmount,float xMult,int yDir,float yAmount,float yMult, boolean dirIsPixelBased = true);

		AttackInfo*getAttackInfo(byte hitDir, int attackNo, byte playerdir);
		
	private:
		boolean attackExists(ArrayList<AttackInfo>&list, int attackNo, byte playerdir);
		AttackInfo*searchAttackList(ArrayList<AttackInfo>&list, int attackNo, byte playerdir);
	};
}