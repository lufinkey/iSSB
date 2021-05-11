
#include "../../Player.h"

#pragma once

namespace SmashBros
{
	class Kirby : public Player
	{
	private:
		class ComboPunches : public Projectile
		{
		public:
			ComboPunches(byte playerNo, float x1, float y1);
			virtual ~ComboPunches();

			virtual void onAnimationFinish(const String&n);
			virtual void onPlayerHit(Player*collide, byte dir);
		};

		boolean queueStandardCombo;
		boolean prepping;
		boolean finishing;

	public:
		Kirby(float x1, float y1, byte playerNo, byte team);
		~Kirby();

		virtual void Update(long gameTime);
		virtual void Draw(Graphics2D&g, long gameTime);
		virtual void setToDefaultValues();
		virtual boolean checkIfAble();
		virtual void Load();
		virtual void LoadAttackTypes();
		virtual void onAnimationFinish(const String&n);
		virtual void jump();
		virtual void onPlayerHit(Player*collide, byte dir);

		virtual void onQueueAttack(byte attackType);

		virtual void attackA();
		virtual void attackSideA();
		virtual void attackUpA();
		virtual void attackDownA();
		virtual void attackB();
		virtual void attackSideB();
		virtual void attackUpB();
		virtual void attackDownB();
		virtual void attackSideSmash(byte type);
		virtual void attackUpSmash(byte type);
		virtual void attackDownSmash(byte type);
		virtual void attackFinalSmash();
	};
}