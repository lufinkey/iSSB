
#ifndef SMASHBROS_SCRIPT_DISABLE

#include "lib_SmashBros.h"

#include "../../../SmashBros/GameElement.h"
#include "../../../SmashBros/Item.h"
#include "../../../SmashBros/Player.h"
#include "../../../SmashBros/Projectile.h"
#include "../../../SmashBros/Stage.h"

#include "../../ScriptMacros.h"
#include "inherit/lib_sb_inherit_GameElement.h"
#include "inherit/lib_sb_inherit_Player.h"
#include "inherit/lib_sb_inherit_Stage.h"

namespace SmashBros
{
	chaiscript::ModulePtr load_module_SmashBros()
	{
		chaiscript::Module* m_smashbros = new chaiscript::Module();

		m_smashbros->add(load_module_SmashBros_types());
		m_smashbros->add(load_module_SmashBros_GameElement());
		m_smashbros->add(load_module_SmashBros_Global());
		m_smashbros->add(load_module_SmashBros_Player());
		m_smashbros->add(load_module_SmashBros_Stage());

		return chaiscript::ModulePtr(m_smashbros);
	}

	chaiscript::ModulePtr load_module_SmashBros_types()
	{
		chaiscript::Module* m_smashbros_types = new chaiscript::Module();
		
		//classes
		m_smashbros_types->add(chaiscript::user_type<SmashBros::GameElement>(), "GameElement");
		m_smashbros_types->add(chaiscript::base_class<GameEngine::Actor, SmashBros::GameElement>());
		m_smashbros_types->add(chaiscript::user_type<SmashBros::HangPoint>(), "HangPoint");
		m_smashbros_types->add(chaiscript::base_class<GameEngine::WireframeActor, SmashBros::HangPoint>());
		m_smashbros_types->add(chaiscript::user_type<SmashBros::Item>(), "Item");
		m_smashbros_types->add(chaiscript::base_class<SmashBros::GameElement, SmashBros::Item>());
		m_smashbros_types->add(chaiscript::user_type<SmashBros::Platform>(), "Platform");
		m_smashbros_types->add(chaiscript::base_class<SmashBros::GameElement, SmashBros::Platform>());
		m_smashbros_types->add(chaiscript::base_class<GameEngine::Actor, SmashBros::Platform>());
		m_smashbros_types->add(chaiscript::user_type<SmashBros::Player>(), "Player");
		m_smashbros_types->add(chaiscript::base_class<SmashBros::GameElement, SmashBros::Player>());
		m_smashbros_types->add(chaiscript::user_type<SmashBros::Projectile>(), "Projectile");
		m_smashbros_types->add(chaiscript::base_class<SmashBros::GameElement, SmashBros::Projectile>());
		m_smashbros_types->add(chaiscript::user_type<SmashBros::Stage>(), "Stage");

		//scripted classes
		SCRIPTMGR_ADDSCRIPTEDCLASSINHERITENCE(m_smashbros_types, SmashBros, GameElement)
		SCRIPTMGR_ADDSCRIPTEDCLASSINHERITENCE(m_smashbros_types, SmashBros, Player)
		SCRIPTMGR_ADDSCRIPTEDCLASSINHERITENCE(m_smashbros_types, SmashBros, Stage)
		SCRIPTMGR_ADDSHAREDFUNCTIONS(m_smashbros_types, GameElement)
		SCRIPTMGR_ADDSHAREDFUNCTIONS(m_smashbros_types, Player)
		SCRIPTMGR_ADDSHAREDFUNCTIONS(m_smashbros_types, Stage)

		return chaiscript::ModulePtr(m_smashbros_types);
	}
}

#endif //SMASHBROS_SCRIPT_DISABLE
