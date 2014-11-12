
#ifndef SMASHBROS_SCRIPT_DISABLE

#include <chaiscript/chaiscript.hpp>

#pragma once

namespace SmashBros
{
	CHAISCRIPT_MODULE_EXPORT chaiscript::ModulePtr load_module_SmashBros();

	chaiscript::ModulePtr load_module_SmashBros_types();
	chaiscript::ModulePtr load_module_SmashBros_Camera();
	chaiscript::ModulePtr load_module_SmashBros_GameElement();
	chaiscript::ModulePtr load_module_SmashBros_Global();
	chaiscript::ModulePtr load_module_SmashBros_Item();
	chaiscript::ModulePtr load_module_SmashBros_Loader();
	chaiscript::ModulePtr load_module_SmashBros_Menus();
	chaiscript::ModulePtr load_module_SmashBros_MenuPieces();
	chaiscript::ModulePtr load_module_SmashBros_Player();
	chaiscript::ModulePtr load_module_SmashBros_Preferences();
	chaiscript::ModulePtr load_module_SmashBros_Projectile();
	chaiscript::ModulePtr load_module_SmashBros_Stage();

	CHAISCRIPT_MODULE_EXPORT chaiscript::ModulePtr load_module_SmashBros_GameElement_protected();
	CHAISCRIPT_MODULE_EXPORT chaiscript::ModulePtr load_module_SmashBros_Item_protected();
	CHAISCRIPT_MODULE_EXPORT chaiscript::ModulePtr load_module_SmashBros_Player_protected();
	CHAISCRIPT_MODULE_EXPORT chaiscript::ModulePtr load_module_SmashBros_Projectile_protected();
	CHAISCRIPT_MODULE_EXPORT chaiscript::ModulePtr load_module_SmashBros_Stage_protected();

	CHAISCRIPT_MODULE_EXPORT chaiscript::ModulePtr load_module_SmashBros_CharSelectScreen_protected();
	CHAISCRIPT_MODULE_EXPORT chaiscript::ModulePtr load_module_SmashBros_StageSelectScreen_protected();
}

#endif //SMASHBROS_SCRIPT_DISABLE
