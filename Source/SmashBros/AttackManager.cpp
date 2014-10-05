
#include "AttackManager.h"

namespace SmashBros
{
	AttackManager::AttackInfo::AttackInfo()
	{
		//
	}
	
	AttackManager::AttackInfo::AttackInfo(int attackNo, byte playerdir, int damage, long delayTime, int xDir,float xAmount,float xMult,int yDir,float yAmount,float yMult, boolean dirIsPixelBased)
	{
		this->attackNo = attackNo;
		this->playerdir = playerdir;
		this->damage = damage;
		this->delayTime = delayTime;
		this->xDir = xDir;
		this->xAmount = xAmount;
		this->xMult = xMult;
		this->yDir = yDir;
		this->yAmount = yAmount;
		this->yMult = yMult;
		this->dirIsPixelBased = dirIsPixelBased;
	}

	AttackManager::AttackInfo::~AttackInfo()
	{
		//
	}

	AttackManager::AttackInfo::operator String()
	{
		String str = "";
		str += "attackNo: ";
		str += attackNo;
		str += ", playerdir: ";
		str += playerdir;
		return str;
	}

	AttackManager::AttackManager()
	{
		//
	}

	AttackManager::~AttackManager()
	{
		//
	}

	void AttackManager::addUpAttackInfo(int attackNo, byte playerdir, int damage, long delayTime, int xDir,float xAmount,float xMult,int yDir,float yAmount,float yMult, boolean dirIsPixelBased)
	{
		if(!attackExists(up,attackNo,playerdir))
		{
			up.add(AttackInfo(attackNo,playerdir,damage,delayTime,xDir,xAmount,xMult,yDir,yAmount,yMult,dirIsPixelBased));
		}
	}

	void AttackManager::addDownAttackInfo(int attackNo, byte playerdir, int damage, long delayTime, int xDir,float xAmount,float xMult,int yDir,float yAmount,float yMult, boolean dirIsPixelBased)
	{
		if(!attackExists(down,attackNo,playerdir))
		{
			down.add(AttackInfo(attackNo,playerdir,damage,delayTime,xDir,xAmount,xMult,yDir,yAmount,yMult,dirIsPixelBased));
		}
	}

	void AttackManager::addLeftAttackInfo(int attackNo, byte playerdir, int damage, long delayTime, int xDir,float xAmount,float xMult,int yDir,float yAmount,float yMult, boolean dirIsPixelBased)
	{
		if(!attackExists(left,attackNo,playerdir))
		{
			left.add(AttackInfo(attackNo,playerdir,damage,delayTime,xDir,xAmount,xMult,yDir,yAmount,yMult,dirIsPixelBased));
		}
	}

	void AttackManager::addRightAttackInfo(int attackNo, byte playerdir, int damage, long delayTime, int xDir,float xAmount,float xMult,int yDir,float yAmount,float yMult, boolean dirIsPixelBased)
	{
		if(!attackExists(right,attackNo,playerdir))
		{
			right.add(AttackInfo(attackNo,playerdir,damage,delayTime,xDir,xAmount,xMult,yDir,yAmount,yMult,dirIsPixelBased));
		}
	}

	AttackManager::AttackInfo*AttackManager::getAttackInfo(byte hitDir, int attackNo, byte playerdir)
	{
		switch(hitDir)
		{
			case PrimitiveActor::DIR_UP:
			return searchAttackList(up,attackNo,playerdir);
			
			case PrimitiveActor::DIR_DOWN:
			return searchAttackList(down,attackNo,playerdir);
			
			case PrimitiveActor::DIR_LEFT:
			return searchAttackList(left,attackNo,playerdir);
			
			case PrimitiveActor::DIR_RIGHT:
			return searchAttackList(right,attackNo,playerdir);
		}
		return null;
	}

	boolean AttackManager::attackExists(ArrayList<AttackInfo>&list, int attackNo, byte playerdir)
	{
		for(int i=0; i<list.size(); i++)
		{
			AttackInfo&info = list.get(i);
			if(info.attackNo==attackNo && info.playerdir == playerdir)
			{
				return true;
			}
		}
		return false;
	}

	AttackManager::AttackInfo*AttackManager::searchAttackList(ArrayList<AttackInfo>&list, int attackNo, byte playerdir)
	//use pointer or reference
	{
		for(int i=0; i<list.size(); i++)
		{
			AttackInfo&info = list.get(i);
			if(info.attackNo==attackNo && info.playerdir==playerdir)
			{
				return &info;
			}
		}
		return null;
	}
}