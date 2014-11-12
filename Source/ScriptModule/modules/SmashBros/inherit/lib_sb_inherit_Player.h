
#ifndef SMASHBROS_SCRIPT_DISABLE

#include "../../../ScriptManager.h"

#include "../lib_SmashBros.h"

#include "../../../../SmashBros/Player.h"
#include "../../../../SmashBros/Item.h"
#include "../../../../SmashBros/Projectile.h"

#pragma once

namespace SmashBros
{
	SCRIPTEDCLASS_CLASSHEADER(SmashBros, Player)
	{
		friend SCRIPTEDCLASS_NEWFUNCTION_HEADER(Player, float, float, byte, byte);

		SCRIPTEDCLASS_CONSTRUCTOR_DECLARE(Player, float x1, float y1, byte playerNo, byte team)

		SCRIPTEDCLASS_MEMBERS_DECLARE(SmashBros, Player)

		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, onMouseEnter)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, onMouseLeave)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, onClick)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, onRelease)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, onMoveFinish)
		SCRIPTEDCLASS_FUNCTION_DECLARE(bool, Player, isOnScreen)

		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, onCreate)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, Load)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, LoadAttackTypes)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, onAnimationFinish, const String&name)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, setToDefaultValues)
		SCRIPTEDCLASS_FUNCTION_DECLARE(boolean, Player, checkIfAble)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, onDestroy)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, Update, long gameTime)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, Draw, Graphics2D&g, long gameTime)

		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, onPlatformCollide, Platform*collide, byte dir)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, finishPlatformCollide, Platform*collide, byte dir)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, onGroundCollide)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, whilePlayerColliding, Player*collide, byte dir)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, onPlayerHit, Player*collide, byte dir)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, whilePlayerHitting, Player*collide, byte dir)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, finishPlayerHit, Player*collide)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, onPlayerRectHit, Player*collide, byte dir)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, whilePlayerRectHitting, Player*collide, byte dir)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, finishPlayerRectHit, Player*collide)
		
		SCRIPTEDCLASS_FUNCTION_DECLARE(boolean, Player, onDeflectPlayerDamage, Player*collide, int damage)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, onDeflectPlayerLaunch, Player*collide, int xDir, float xAmount, float xMult, int yDir, float yAmount, float yMult)
		SCRIPTEDCLASS_FUNCTION_DECLARE(boolean, Player, onDeflectItemCollision, Item*item, byte dir)
		SCRIPTEDCLASS_FUNCTION_DECLARE(boolean, Player, onDeflectItemDamage, Item*collide, int damage)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, onDeflectItemLaunch, Item*collide, int xDir, float xAmount, float xMult, int yDir, float yAmount, float yMult)
		SCRIPTEDCLASS_FUNCTION_DECLARE(boolean, Player, onDeflectProjectileCollision, Projectile*collide, byte dir)
		SCRIPTEDCLASS_FUNCTION_DECLARE(boolean, Player, onDeflectProjectileDamage, Projectile*collide, int damage)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, onDeflectProjectileLaunch, Projectile*collide, int xDir, float xAmount, float xMult, int yDir, float yAmount, float yMult)

		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, jump)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, grab)

		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, onGrab, Player*held)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, onGrabbed, Player*holder)

		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, onFinishCharge)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, doChargingAttack, byte button)

		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, grabAttack)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, grabAttackSide)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, grabAttackSwing)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, grabAttackUp)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, grabAttackDown)

		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, attackA)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, attackSideA)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, attackUpA)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, attackDownA)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, attackB)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, attackSideB)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, attackUpB)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, attackDownB)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, attackSideSmash, byte type)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, attackUpSmash, byte type)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, attackDownSmash, byte type)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Player, attackFinalSmash)
	};

	SCRIPTEDCLASS_NEWFUNCTION_HEADER(Player, float, float, byte, byte);
	SCRIPTEDCLASS_DELETEFUNCTION_HEADER(Player);
}

#endif //SMASHBROS_SCRIPT_DISABLE
