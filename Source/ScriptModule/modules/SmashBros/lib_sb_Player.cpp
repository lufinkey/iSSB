
#ifndef SMASHBROS_SCRIPT_DISABLE

#include "lib_smashbros.h"

#include "../../../SmashBros/Player.h"
#include "../../../SmashBros/Item.h"

namespace SmashBros
{
	chaiscript::ModulePtr load_module_SmashBros_Player()
	{
		chaiscript::Module* m_smashbros_player = new chaiscript::Module();

		//attributes
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::xVel), "xVel");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::yVel), "yVel");

		//functions
		//m_smashbros_player->add(chaiscript::constructor<Player(float,float,byte,byte)>(), "Player");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::setToDefaultValues), "setToDefaultValues");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::Update), "Update");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::Draw), "Draw");

		m_smashbros_player->add(chaiscript::fun((void(SmashBros::Player::*)()) &SmashBros::Player::jump), "jump");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::grab), "grab");

		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::onGrab), "onGrab");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::onGrabbed), "onGrabbed");

		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::onFinishCharge), "onFinishCharge");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::doChargingAttack), "doChargingAttack");

		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::grabAttack), "grabAttack");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::grabAttackSide), "grabAttackSide");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::grabAttackSwing), "grabAttackSwing");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::grabAttackUp), "grabAttackUp");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::grabAttackDown), "grabAttackDown");

		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::attackA), "attackA");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::attackSideA), "attackSideA");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::attackUpA), "attackUpA");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::attackDownA), "attackDownA");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::attackB), "attackB");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::attackSideB), "attackSideB");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::attackUpB), "attackUpB");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::attackDownB), "attackDownB");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::attackSideSmash), "attackSideSmash");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::attackUpSmash), "attackUpSmash");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::attackDownSmash), "attackDownSmash");

		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::respawn), "respawn");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::addAnimation), "addAnimation");
		m_smashbros_player->add(chaiscript::fun((void(SmashBros::Player::*)(const String&,byte)) &SmashBros::Player::changeTwoSidedAnimation), "changeTwoSidedAnimation");
		m_smashbros_player->add(chaiscript::fun((void(SmashBros::Player::*)(const String&,byte,byte)) &SmashBros::Player::changeTwoSidedAnimation), "changeTwoSidedAnimation");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::setColor), "setColor");

		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::isCPU), "isCPU");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::isAlive), "isAlive");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::isHurt), "isHurt");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::isHoldingItem), "isHoldingItem");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::isWearingItem), "isWearingItem");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::isHattingItem), "isHattingItem");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::isWieldingItem), "isWieldingItem");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::isInvincible), "isInvincible");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::getName), "getName");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::getPercent), "getPercent");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::getLastHitIndex), "getLastHitIndex");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::getAttacksHolder), "getAttacksHolder");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::getAttacksPriority), "getAttacksPriority");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::getComboNo), "getComboNo");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::isOnGround), "isOnGround");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::getPlayerDir), "getPlayerDir");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::getDirFacing), "getDirFacing");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::getTeam), "getTeam");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::canFinalSmash), "canFinalSmash");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::setPlayerDir), "setPlayerDir");
		m_smashbros_player->add(chaiscript::fun((float(SmashBros::Player::*)()) &SmashBros::Player::getPlayerDirMult), "getPlayerDirMult");
		m_smashbros_player->add(chaiscript::fun((float(*)(byte)) &SmashBros::Player::getPlayerDirMult), "Player_getPlayerDirMult");
		m_smashbros_player->add(chaiscript::fun((String(SmashBros::Player::*)()) &SmashBros::Player::getPlayerDirSuffix), "getPlayerDirSuffix");
		m_smashbros_player->add(chaiscript::fun((String(*)(byte)) &SmashBros::Player::getPlayerDirSuffix), "Player_getPlayerDirSuffix");
		m_smashbros_player->add(chaiscript::fun((byte(SmashBros::Player::*)()) &SmashBros::Player::getOppPlayerDir), "getOppPlayerDir");
		m_smashbros_player->add(chaiscript::fun((byte(*)(byte)) &SmashBros::Player::getOppPlayerDir), "Player_getOppPlayerDir");
		m_smashbros_player->add(chaiscript::fun((byte(SmashBros::Player::*)(SmashBros::GameElement*)) &SmashBros::Player::getRelPlayerDir), "getRelPlayerDir");
		m_smashbros_player->add(chaiscript::fun((byte(*)(SmashBros::GameElement*, SmashBros::GameElement*)) &SmashBros::Player::getRelPlayerDir), "Player_getRelPlayerDir");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::compareDirPlayerDir), "Player_compareDirPlayerDir");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::getPlayerNo), "getPlayerNo");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::CanDo), "canDo");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::getStock), "getStock");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::isJumping), "isJumping");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::isHanging), "isHanging");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::getSmashPower), "getSmashPower");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::getMoveLeft), "getMoveLeft");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::getMoveRight), "getMoveRight");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::setPoint), "setPoint");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::getGrabbedPlayer), "getGrabbedPlayer");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::getHitbox), "getHitbox");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::getFolderPath), "getFolderPath");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::pickUpItem), "pickUpItem");
		m_smashbros_player->add(chaiscript::fun((boolean(SmashBros::Player::*)(SmashBros::HitBox*)) &SmashBros::Player::hitboxRectsColliding), "hitboxRectsColliding");
		m_smashbros_player->add(chaiscript::fun((boolean(SmashBros::Player::*)(GameEngine::WireframeActor*)) &SmashBros::Player::hitboxRectsColliding), "hitboxRectsColliding");
		m_smashbros_player->add(chaiscript::fun((boolean(SmashBros::Player::*)(GameEngine::Actor*)) &SmashBros::Player::hitboxRectsColliding), "hitboxRectsColliding");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::stand), "stand");
		m_smashbros_player->add(chaiscript::fun(&SmashBros::Player::moveDown), "moveDown");

		//constants
		m_smashbros_player->add_global_const(chaiscript::const_var(SmashBros::Player::LEFT), "LEFT");
		m_smashbros_player->add_global_const(chaiscript::const_var(SmashBros::Player::RIGHT), "RIGHT");

		m_smashbros_player->add_global_const(chaiscript::const_var(SmashBros::Player::CMPDIRPDIR_EQUAL), "CMPDIRPDIR_EQUAL");
		m_smashbros_player->add_global_const(chaiscript::const_var(SmashBros::Player::CMPDIRPDIR_OPP), "CMPDIRPDIR_OPP");
		m_smashbros_player->add_global_const(chaiscript::const_var(SmashBros::Player::CMPDIRPDIR_INVALID), "CMPDIRPDIR_INVALID");

		m_smashbros_player->add_global_const(chaiscript::const_var(SmashBros::Player::ATTACK_A), "ATTACK_A");
		m_smashbros_player->add_global_const(chaiscript::const_var(SmashBros::Player::ATTACK_SIDEA), "ATTACK_SIDEA");
		m_smashbros_player->add_global_const(chaiscript::const_var(SmashBros::Player::ATTACK_UPA), "ATTACK_UPA");
		m_smashbros_player->add_global_const(chaiscript::const_var(SmashBros::Player::ATTACK_DOWNA), "ATTACK_DOWNA");
		m_smashbros_player->add_global_const(chaiscript::const_var(SmashBros::Player::ATTACK_B), "ATTACK_B");
		m_smashbros_player->add_global_const(chaiscript::const_var(SmashBros::Player::ATTACK_SIDEB), "ATTACK_SIDEB");
		m_smashbros_player->add_global_const(chaiscript::const_var(SmashBros::Player::ATTACK_UPB), "ATTACK_UPB");
		m_smashbros_player->add_global_const(chaiscript::const_var(SmashBros::Player::ATTACK_DOWNB), "ATTACK_DOWNB");
		m_smashbros_player->add_global_const(chaiscript::const_var(SmashBros::Player::ATTACK_SIDESMASH), "ATTACK_SIDESMASH");
		m_smashbros_player->add_global_const(chaiscript::const_var(SmashBros::Player::ATTACK_UPSMASH), "ATTACK_UPSMASH");
		m_smashbros_player->add_global_const(chaiscript::const_var(SmashBros::Player::ATTACK_DOWNSMASH), "ATTACK_DOWNSMASH");

		m_smashbros_player->add_global_const(chaiscript::const_var(SmashBros::Player::ATTACKTYPE_MELEE), "ATTACKTYPE_MELEE");
		m_smashbros_player->add_global_const(chaiscript::const_var(SmashBros::Player::ATTACKTYPE_UPMELEE), "ATTACKTYPE_UPMELEE");
		m_smashbros_player->add_global_const(chaiscript::const_var(SmashBros::Player::ATTACKTYPE_DOWNMELEE), "ATTACKTYPE_DOWNMELEE");
		m_smashbros_player->add_global_const(chaiscript::const_var(SmashBros::Player::ATTACKTYPE_STRONGMELEE), "ATTACKTYPE_STRONGMELEE");
		m_smashbros_player->add_global_const(chaiscript::const_var(SmashBros::Player::ATTACKTYPE_SIDEMOVE), "ATTACKTYPE_SIDEMOVE");
		m_smashbros_player->add_global_const(chaiscript::const_var(SmashBros::Player::ATTACKTYPE_UPMOVE), "ATTACKTYPE_UPMOVE");
		m_smashbros_player->add_global_const(chaiscript::const_var(SmashBros::Player::ATTACKTYPE_DOWNMOVE), "ATTACKTYPE_DOWNMOVE");
		m_smashbros_player->add_global_const(chaiscript::const_var(SmashBros::Player::ATTACKTYPE_PROJECTILE), "ATTACKTYPE_PROJECTILE");
		m_smashbros_player->add_global_const(chaiscript::const_var(SmashBros::Player::ATTACKTYPE_DEFENSIVE), "ATTACKTYPE_DEFENSIVE");

		m_smashbros_player->add_global_const(chaiscript::const_var(SmashBros::Player::AI_STOP), "AI_STOP");
		m_smashbros_player->add_global_const(chaiscript::const_var(SmashBros::Player::AI_WALK), "AI_WALK");
		m_smashbros_player->add_global_const(chaiscript::const_var(SmashBros::Player::AI_RUN), "AI_RUN");
		m_smashbros_player->add_global_const(chaiscript::const_var(SmashBros::Player::AI_JUMP), "AI_JUMP");
		m_smashbros_player->add_global_const(chaiscript::const_var(SmashBros::Player::AI_NORMAL), "AI_NORMAL");
		m_smashbros_player->add_global_const(chaiscript::const_var(SmashBros::Player::AI_FOLLOW), "AI_FOLLOW");

		return chaiscript::ModulePtr(m_smashbros_player);
	}
}

#endif //SMASHBROS_SCRIPT_DISABLE
