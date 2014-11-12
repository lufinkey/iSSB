
#ifndef SMASHBROS_SCRIPT_DISABLE

#include "lib_sb_inherit_player.h"

namespace SmashBros
{
	SCRIPTEDCLASS_CONSTRUCTOR_HEADER(Player, x1 _COMMA y1 _COMMA playerNo _COMMA team, float x1, float y1, byte playerNo, byte team)
	{
		SCRIPTEDCLASS_CONSTRUCTOR_LOADSCRIPT(Player)

		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, onMouseEnter)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, onMouseLeave)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, onClick)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, onRelease)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, onMoveFinish)
		SCRIPTEDCLASS_FUNCTION_LOAD(bool, Player, isOnScreen)

		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, onCreate)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, Load)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, LoadAttackTypes)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, onAnimationFinish, const String&)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, setToDefaultValues)
		SCRIPTEDCLASS_FUNCTION_LOAD(boolean, Player, checkIfAble)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, onDestroy)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, Update, long)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, Draw, Graphics2D&, long)

		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, onPlatformCollide, Platform*, byte)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, finishPlatformCollide, Platform*, byte)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, onGroundCollide)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, whilePlayerColliding, Player*, byte)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, onPlayerHit, Player*, byte)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, whilePlayerHitting, Player*, byte)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, finishPlayerHit, Player*)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, onPlayerRectHit, Player*, byte)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, whilePlayerRectHitting, Player*, byte)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, finishPlayerRectHit, Player*)
		
		SCRIPTEDCLASS_FUNCTION_LOAD(boolean, Player, onDeflectPlayerDamage, Player*, int)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, onDeflectPlayerLaunch, Player*, int,float,float, int,float,float)
		SCRIPTEDCLASS_FUNCTION_LOAD(boolean, Player, onDeflectItemCollision, Item*, byte)
		SCRIPTEDCLASS_FUNCTION_LOAD(boolean, Player, onDeflectItemDamage, Item*, int)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, onDeflectItemLaunch, Item*, int,float,float, int,float,float)
		SCRIPTEDCLASS_FUNCTION_LOAD(boolean, Player, onDeflectProjectileCollision, Projectile*, byte)
		SCRIPTEDCLASS_FUNCTION_LOAD(boolean, Player, onDeflectProjectileDamage, Projectile*, int)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, onDeflectProjectileLaunch, Projectile*, int,float,float, int,float,float)

		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, jump)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, grab)

		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, onGrab)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, onGrabbed)

		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, onFinishCharge)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, doChargingAttack, byte)

		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, grabAttack)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, grabAttackSide)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, grabAttackSwing)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, grabAttackUp)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, grabAttackDown)
		
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, attackA)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, attackSideA)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, attackUpA)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, attackDownA)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, attackB)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, attackSideB)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, attackUpB)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, attackDownB)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, attackSideSmash, byte)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, attackUpSmash, byte)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, attackDownSmash, byte)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Player, attackFinalSmash, byte)

		SCRIPTEDCLASS_CONSTRUCTOR_ADDMODULES(
			ScriptModule::ScriptManager::module_GameEngine,
			ScriptModule::ScriptManager::module_SmashBros,
			ScriptModule::ScriptManager::module_GameEngine_Actor_protected,
			ScriptModule::ScriptManager::module_SmashBros_GameElement_protected,
			ScriptModule::ScriptManager::module_SmashBros_Player_protected)
	}

	SCRIPTEDCLASS_LOADTYPEFUNCTIONS_HEADER(Player)
	{
		SCRIPTEDCLASS_LOADTYPEFUNCTIONS_BODY(Player)
		SCRIPTEDCLASS_NEWFUNCTION_ADD(Player, float, float, byte, byte)
	}
	
	SCRIPTEDCLASS_MEMBERS_DEFINE(Player)

	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, onMouseEnter , , , )
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, onMouseLeave, , , )
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, onClick, , , )
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, onRelease, , , )
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, onMoveFinish, , , )
	SCRIPTEDCLASS_FUNCTION_DEFINE(bool, Player, isOnScreen, return, true, )
	
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, onCreate, , , )
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, Load, , , )
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, LoadAttackTypes, , , )
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, onAnimationFinish, , , name, const String&name)
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, setToDefaultValues, , , )
	SCRIPTEDCLASS_FUNCTION_DEFINE(boolean, Player, checkIfAble, return, true, )
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, onDestroy, , , )
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, Update, , , gameTime, long gameTime)
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, Draw, , , g _COMMA gameTime, Graphics2D&g, long gameTime)

	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, onPlatformCollide, , , collide _COMMA dir, Platform*collide, byte dir)
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, finishPlatformCollide, , , collide _COMMA dir, Platform*collide, byte dir)
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, onGroundCollide, , , )
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, whilePlayerColliding, , , collide _COMMA dir, Player*collide, byte dir)
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, onPlayerHit, , , collide _COMMA dir, Player*collide, byte dir)
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, whilePlayerHitting, , , collide _COMMA dir, Player*collide, byte dir)
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, finishPlayerHit, , , collide, Player*collide)
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, onPlayerRectHit, , , collide _COMMA dir, Player*collide, byte dir)
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, whilePlayerRectHitting, , , collide _COMMA dir, Player*collide, byte dir)
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, finishPlayerRectHit, , , collide, Player*collide)

	SCRIPTEDCLASS_FUNCTION_DEFINE(boolean, Player, onDeflectPlayerDamage, return, false, collide _COMMA damage, Player*collide, int damage)
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, onDeflectPlayerLaunch, , ,
					collide _COMMA xDir _COMMA xAmount _COMMA xMult _COMMA yDir _COMMA yAmount _COMMA yMult,
					Player*collide, int xDir, float xAmount, float xMult, int yDir, float yAmount, float yMult)
	SCRIPTEDCLASS_FUNCTION_DEFINE(boolean, Player, onDeflectItemCollision, return, false, collide _COMMA dir, Item*collide, byte dir)
	SCRIPTEDCLASS_FUNCTION_DEFINE(boolean, Player, onDeflectItemDamage, return, false, collide _COMMA damage, Item*collide, int damage)
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, onDeflectItemLaunch, , ,
					collide _COMMA xDir _COMMA xAmount _COMMA xMult _COMMA yDir _COMMA yAmount _COMMA yMult,
					Item*collide, int xDir, float xAmount, float xMult, int yDir, float yAmount, float yMult)
	SCRIPTEDCLASS_FUNCTION_DEFINE(boolean, Player, onDeflectProjectileCollision, return, false, collide _COMMA dir, Projectile*collide, byte dir)
	SCRIPTEDCLASS_FUNCTION_DEFINE(boolean, Player, onDeflectProjectileDamage, return, false, collide _COMMA damage, Projectile*collide, int damage)
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, onDeflectProjectileLaunch, , ,
					collide _COMMA xDir _COMMA xAmount _COMMA xMult _COMMA yDir _COMMA yAmount _COMMA yMult,
					Projectile*collide, int xDir, float xAmount, float xMult, int yDir, float yAmount, float yMult)

	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, jump, , , )
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, grab, , , )

	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, onGrab, , , held, Player*held)
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, onGrabbed, , , holder, Player*holder)

	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, onFinishCharge, , , )
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, doChargingAttack, , , button, byte button)

	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, grabAttack, , , )
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, grabAttackSide, , , )
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, grabAttackSwing, , , )
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, grabAttackUp, , , )
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, grabAttackDown, , , )
	
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, attackA, , , )
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, attackSideA, , , )
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, attackUpA, , , )
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, attackDownA, , , )
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, attackB, , , )
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, attackSideB, , , )
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, attackUpB, , , )
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, attackDownB, , , )
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, attackSideSmash, , , type, byte type)
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, attackUpSmash, , , type, byte type)
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, attackDownSmash, , , type, byte type)
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Player, attackFinalSmash, , , )



	SCRIPTEDCLASS_LOADPROTECTEDMODULE_HEADER(SmashBros, Player)
	{
		chaiscript::Module* m_sb_player_protected = new chaiscript::Module();

		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, moveLeft, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, moveRight, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, upKey, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, down, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, name, );

		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, playerdir, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, weight, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, landing, );

		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, hitAmount, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, attackTime, );

		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, attacksHolder, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, attacksPriority, );

		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, chargeSmash, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, chargingAttack, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, smashPower, );
		
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, bUp, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, doubleJump, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, maxDoubleJumps, );

		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, walkSpeed, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, runSpeed, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, fallWalk, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, fallRun, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, walkAmount, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, runAmount, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, recoverAmount, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, recoverRunAmount, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, grabTime, );

		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, addFile, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, loadFile, );

		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, setOnGround, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, setItemOffset, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, setIndicatorOffset, );

		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, setCantDo, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, setHanging, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, setJumping, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, resetAttackCollisions, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, setHitbox, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, showHitboxWireframe, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, setHitboxColor, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, setFolderPath, );

		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, addTwoSidedAnimation, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, addSingleAnimation, );

		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, setHangPoint, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, destroyCharge, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, animFinish, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, checkAttacks, (void(Player::*)()));

		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, updateGravity, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, updateFrame, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, updateMovement, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, updateHanging, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, updateHurt, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, updateDrop, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, updateAI, );

		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, createProjectile, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, createItem, );

		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, causeDamage, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, causeHurtLaunch, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, causeHurt, );

		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, checkItemUse, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, checkItemUseSide, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, checkItemUseUp, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, checkItemUseDown, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, checkItemUseSideSmash, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, checkItemUseUpSmash, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, checkItemUseDownSmash, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, useItem, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, useItemSmash, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, discardItem, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, tossItem, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, grabPlayer, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, releasePlayer, );

		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, platformResponse, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, getCurrentCollidePlatformActor, );

		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, addAttackInfo, (void(Player::*)(byte,int,byte,int,long,int,float,float,int,float,float)));
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, addAttackInfo, (void(Player::*)(byte,int,byte,int,long,int,float,float,int,float,float,boolean)));
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, addAIAttackType, (void(Player::*)(byte,byte,float)));
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, addAIAttackType, (void(Player::*)(byte,byte,float,boolean)));

		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, jump, (void(Player::*)(float,float)));
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, climbUp, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_player_protected, Player, climbUpAttack, );

		return chaiscript::ModulePtr(m_sb_player_protected);
	}


	
	SCRIPTEDCLASS_NEWFUNCTION_HEADER(Player, float x1, float y1, byte playerNo, byte team)
	{
		SCRIPTEDCLASS_NEWFUNCTION_BODY(Player, x1, y1, playerNo, team)
	}

	SCRIPTEDCLASS_DELETEFUNCTION_HEADER(Player)
	{
		SCRIPTEDCLASS_DELETEFUNCTION_BODY(Player)
	}
}

#endif //SMASHBROS_SCRIPT_DISABLE
