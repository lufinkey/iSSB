
#ifndef SMASHBROS_SCRIPT_DISABLE

#include "lib_smashbros.h"

#include "../../../SmashBros/Global.h"

namespace SmashBros
{
	chaiscript::ModulePtr load_module_SmashBros_Global()
	{
		chaiscript::Module* m_smashbros_global = new chaiscript::Module();

		//functions
		m_smashbros_global->add(chaiscript::fun(&SmashBros::Global::getDirText), "Global_getDirText");
		m_smashbros_global->add(chaiscript::fun(&SmashBros::Global::getAddonsFolder), "Global_getAddonsFolder");
		m_smashbros_global->add(chaiscript::fun(&SmashBros::Global::getWorldTime), "Global_getWorldTime");
		m_smashbros_global->add(chaiscript::fun(&SmashBros::Global::getPlayerName), "Global_getPlayerName");
		m_smashbros_global->add(chaiscript::fun(&SmashBros::Global::getPlayerActor), "Global_getPlayerActor");
		m_smashbros_global->add(chaiscript::fun(&SmashBros::Global::getItemName), "Global_getItemName");

		//constants
		m_smashbros_global->add_global_const(chaiscript::const_var(SmashBros::Global::TYPE_TRAINING), "TYPE_TRAINING");
		m_smashbros_global->add_global_const(chaiscript::const_var(SmashBros::Global::TYPE_GROUPBRAWL), "TYPE_GROUPBRAWL");

		m_smashbros_global->add_global_const(chaiscript::const_var(SmashBros::Global::MODE_TIME_LIMIT), "MODE_TIME_LIMIT");
		m_smashbros_global->add_global_const(chaiscript::const_var(SmashBros::Global::MODE_STOCK), "MODE_STOCK");

		m_smashbros_global->add_global_const(chaiscript::const_var(SmashBros::Global::TEAM_RED), "TEAM_RED");
		m_smashbros_global->add_global_const(chaiscript::const_var(SmashBros::Global::TEAM_BLUE), "TEAM_BLUE");
		m_smashbros_global->add_global_const(chaiscript::const_var(SmashBros::Global::TEAM_GREEN), "TEAM_GREEN");
		m_smashbros_global->add_global_const(chaiscript::const_var(SmashBros::Global::TEAM_YELLOW), "TEAM_YELLOW");

		m_smashbros_global->add_global_const(chaiscript::const_var(SmashBros::Global::CHAR_MARIO), "CHAR_MARIO");
		m_smashbros_global->add_global_const(chaiscript::const_var(SmashBros::Global::CHAR_ICHIGO), "CHAR_ICHIGO");
		m_smashbros_global->add_global_const(chaiscript::const_var(SmashBros::Global::CHAR_SONIC), "CHAR_SONIC");
		m_smashbros_global->add_global_const(chaiscript::const_var(SmashBros::Global::CHAR_FOX), "CHAR_FOX");
		m_smashbros_global->add_global_const(chaiscript::const_var(SmashBros::Global::CHAR_PIKACHU), "CHAR_PIKACHU");
		m_smashbros_global->add_global_const(chaiscript::const_var(SmashBros::Global::CHAR_LINK), "CHAR_LINK");

		m_smashbros_global->add_global_const(chaiscript::const_var(SmashBros::Global::STAGE_FRACTALSTAGE), "STAGE_FRACTALSTAGE");
		m_smashbros_global->add_global_const(chaiscript::const_var(SmashBros::Global::STAGE_HILLSIDEBATTLEGROUND), "STAGE_HILLSIDEBATTLEGROUND");
		m_smashbros_global->add_global_const(chaiscript::const_var(SmashBros::Global::STAGE_BATTLEFIELDBRAWL), "STAGE_BATTLEFIELDBRAWL");
		m_smashbros_global->add_global_const(chaiscript::const_var(SmashBros::Global::STAGE_FINALDESTINATION), "STAGE_FINALDESTINATION");
		m_smashbros_global->add_global_const(chaiscript::const_var(SmashBros::Global::STAGE_HYRULETEMPLE), "STAGE_HYRULETEMPLE");

		m_smashbros_global->add_global_const(chaiscript::const_var(SmashBros::Global::ITEM_CUSTOM), "ITEM_CUSTOM");
		m_smashbros_global->add_global_const(chaiscript::const_var(SmashBros::Global::ITEM_SMASHBALL), "ITEM_SMASHBALL");
		m_smashbros_global->add_global_const(chaiscript::const_var(SmashBros::Global::ITEM_RAYGUN), "ITEM_RAYGUN");
		m_smashbros_global->add_global_const(chaiscript::const_var(SmashBros::Global::ITEM_HEARTCONTAINER), "ITEM_HEARTCONTAINER");
		m_smashbros_global->add_global_const(chaiscript::const_var(SmashBros::Global::ITEM_BEAMSWORD), "ITEM_BEAMSWORD");
		m_smashbros_global->add_global_const(chaiscript::const_var(SmashBros::Global::ITEM_SUPERMUSHROOM), "ITEM_SUPERMUSHROOM");
		m_smashbros_global->add_global_const(chaiscript::const_var(SmashBros::Global::ITEM_POISONMUSHROOM), "ITEM_POISONMUSHROOM");

		m_smashbros_global->add_global_const(chaiscript::const_var(SmashBros::Global::totalCharacters), "GLOBAL_TOTALCHARACTERS");
		m_smashbros_global->add_global_const(chaiscript::const_var(SmashBros::Global::totalItems), "GLOBAL_TOTALITEMS");
		m_smashbros_global->add_global_const(chaiscript::const_var(SmashBros::Global::totalStages), "GLOBAL_TOTALSTAGES");

		return chaiscript::ModulePtr(m_smashbros_global);
	}
}

#endif //SMASHBROS_SCRIPT_DISABLE
