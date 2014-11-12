
#ifndef SMASHBROS_SCRIPT_DISABLE

#include "lib_SmashBros.h"

#include "../../../SmashBros/Player.h"
#include "../../../SmashBros/Stage.h"

namespace SmashBros
{
	Stage* new_Stage(float x1, float y1)
	{
		return new Stage(x1, y1);
	}

	void delete_Stage(Stage*stage)
	{
		delete stage;
	}

	HangPoint* new_HangPoint(byte dir, float x1, float y1)
	{
		return new HangPoint(dir, x1, y1);
	}

	void delete_HangPoint(HangPoint* hangPoint)
	{
		delete hangPoint;
	}

	Platform* new_Platorm(byte type, float x1, float y1)
	{
		return new Platform(type, x1, y1);
	}

	Platform* new_Platorm(byte type, float x1, float y1, int width, int height)
	{
		return new Platform(type, x1, y1, width, height);
	}

	void delete_Platform(Platform* platform)
	{
		delete platform;
	}

	chaiscript::ModulePtr load_module_SmashBros_Stage()
	{
		chaiscript::Module* m_smashbros_stage = new chaiscript::Module();

		//Stage
		m_smashbros_stage->add(chaiscript::constructor<SmashBros::Stage(float, float)>(), "Stage");
		m_smashbros_stage->add(chaiscript::fun(&SmashBros::new_Stage), "new_Stage");
		m_smashbros_stage->add(chaiscript::fun(&SmashBros::delete_Stage), "delete_Stage");
		m_smashbros_stage->add(chaiscript::fun(&SmashBros::Stage::x), "x");
		m_smashbros_stage->add(chaiscript::fun(&SmashBros::Stage::y), "y");
		m_smashbros_stage->add(chaiscript::fun(&SmashBros::Stage::Update), "Update");
		m_smashbros_stage->add(chaiscript::fun(&SmashBros::Stage::Draw), "Draw");
		m_smashbros_stage->add(chaiscript::fun(&SmashBros::Stage::Unload), "Unload");
		m_smashbros_stage->add(chaiscript::fun(&SmashBros::Stage::setBackground), "setBackground");
		m_smashbros_stage->add(chaiscript::fun(&SmashBros::Stage::setBackgroundType), "setBackgroundType");
		m_smashbros_stage->add(chaiscript::fun(&SmashBros::Stage::getItemBoundaries), "getItemBoundaries");
		m_smashbros_stage->add(chaiscript::fun(&SmashBros::Stage::showWireframes), "showWireframes");
		m_smashbros_stage->add(chaiscript::fun(&SmashBros::Stage::setWireframeColor), "setWireframeColor");
		m_smashbros_stage->add(chaiscript::fun(&SmashBros::Stage::setElementColor), "setElementColor");
		m_smashbros_stage->add(chaiscript::fun(&SmashBros::Stage::setGravity), "setGravity");
		m_smashbros_stage->add(chaiscript::fun(&SmashBros::Stage::getGravity), "getGravity");
		m_smashbros_stage->add(chaiscript::fun(&SmashBros::Stage::setTerminalVelocity), "setTerminalVelocity");
		m_smashbros_stage->add(chaiscript::fun(&SmashBros::Stage::getTerminalVelocity), "getTerminalVelocity");
		m_smashbros_stage->add(chaiscript::fun(&SmashBros::Stage::addElement), "addElement");
		m_smashbros_stage->add(chaiscript::fun(&SmashBros::Stage::addPlatform), "addPlatform");
		m_smashbros_stage->add(chaiscript::fun(&SmashBros::Stage::addForeground), "addForeground");
		m_smashbros_stage->add(chaiscript::fun(&SmashBros::Stage::addHangPoint), "addHangPoint");
		m_smashbros_stage->add(chaiscript::fun(&SmashBros::Stage::addGround), "addGround");
		m_smashbros_stage->add(chaiscript::fun(&SmashBros::Stage::setSpawnPoint), "setSpawnPoint");
		m_smashbros_stage->add(chaiscript::fun(&SmashBros::Stage::getSpawnPoint), "getSpawnPoint");
		m_smashbros_stage->add(chaiscript::fun(&SmashBros::Stage::getBorders), "getBorders");
		m_smashbros_stage->add(chaiscript::fun(&SmashBros::Stage::getViewBorders), "getViewBorders");
		m_smashbros_stage->add(chaiscript::fun(&SmashBros::Stage::checkSafeArea), "checkSafeArea");
		m_smashbros_stage->add_global_const(chaiscript::const_var(SmashBros::Stage::BG_FIXED), "STAGE_BG_FIXED");
		m_smashbros_stage->add_global_const(chaiscript::const_var(SmashBros::Stage::BG_NORMAL), "STAGE_BG_NORMAL");



		//HangPoint
		m_smashbros_stage->add(chaiscript::constructor<SmashBros::HangPoint(byte, float, float)>(), "HangPoint");
		m_smashbros_stage->add(chaiscript::fun(&SmashBros::new_HangPoint), "new_HangPoint");
		m_smashbros_stage->add(chaiscript::fun(&SmashBros::delete_HangPoint), "delete_HangPoint");
		m_smashbros_stage->add(chaiscript::fun(&SmashBros::HangPoint::hanging), "hanging");
		m_smashbros_stage->add(chaiscript::fun(&SmashBros::HangPoint::Update), "Update");
		m_smashbros_stage->add(chaiscript::fun(&SmashBros::HangPoint::Draw), "Draw");
		m_smashbros_stage->add(chaiscript::fun(&SmashBros::HangPoint::getHangSide), "getHangSide");



		//Platform
		m_smashbros_stage->add(chaiscript::constructor<SmashBros::Platform(byte, float, float)>(), "Platform");
		m_smashbros_stage->add(chaiscript::constructor<SmashBros::Platform(byte, float, float, int, int)>(), "Platform");
		m_smashbros_stage->add(chaiscript::fun((Platform*(*)(byte,float,float))&SmashBros::new_Platorm), "new_Platform");
		m_smashbros_stage->add(chaiscript::fun((Platform*(*)(byte,float,float,int,int))&SmashBros::new_Platorm), "new_Platform");
		m_smashbros_stage->add(chaiscript::fun(&SmashBros::delete_Platform), "delete_Platform");
		m_smashbros_stage->add(chaiscript::fun(&SmashBros::Platform::Update), "Update");
		m_smashbros_stage->add(chaiscript::fun(&SmashBros::Platform::Draw), "Draw");
		m_smashbros_stage->add(chaiscript::fun(&SmashBros::Platform::checkGroundCollision), "checkGroundCollision");
		m_smashbros_stage->add(chaiscript::fun(&SmashBros::Platform::getType), "getType");
		m_smashbros_stage->add(chaiscript::fun(&SmashBros::Platform::getCollideType), "getCollideType");
		m_smashbros_stage->add(chaiscript::fun(&SmashBros::Platform::getBox), "getBox");
		m_smashbros_stage->add(chaiscript::fun(&SmashBros::Platform::getBoxDirection), "getBoxDirection");
		m_smashbros_stage->add(chaiscript::fun(&SmashBros::Platform::setVisible), "setVisible");
		m_smashbros_stage->add(chaiscript::fun(&SmashBros::Platform::onPlayerCollide), "onPlayerCollide");
		m_smashbros_stage->add(chaiscript::fun(&SmashBros::Platform::whilePlayerColliding), "whilePlayerColliding");
		m_smashbros_stage->add(chaiscript::fun(&SmashBros::Platform::finishPlayerCollide), "finishPlayerCollide");
		m_smashbros_stage->add_global_const(chaiscript::const_var(SmashBros::Platform::TYPE_NORMAL), "PLATFORMTYPE_NORMAL");
		m_smashbros_stage->add_global_const(chaiscript::const_var(SmashBros::Platform::TYPE_GOTHROUGH), "PLATFORMTYPE_GOTHROUGH");
		m_smashbros_stage->add_global_const(chaiscript::const_var(SmashBros::Platform::COLLIDE_BOX), "PLATFORM_COLLIDE_BOX");
		m_smashbros_stage->add_global_const(chaiscript::const_var(SmashBros::Platform::COLLIDE_SOLID), "PLATFORM_COLLIDE_SOLID");

		return chaiscript::ModulePtr(m_smashbros_stage);
	}
}

#endif //SMASHBROS_SCRIPT_DISABLE
