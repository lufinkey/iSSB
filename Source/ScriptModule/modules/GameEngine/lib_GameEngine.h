
#ifndef SMASHBROS_SCRIPT_DISABLE

#include "../../../GameEngine/GameEngine.h"
#include <chaiscript/chaiscript.hpp>

#pragma once

namespace GameEngine
{
	CHAISCRIPT_MODULE_EXPORT chaiscript::ModulePtr load_module_GameEngine();

	chaiscript::ModulePtr load_module_GameEngine_types();
	chaiscript::ModulePtr load_module_GameEngine_Actor();
	chaiscript::ModulePtr load_module_GameEngine_Global();
	chaiscript::ModulePtr load_module_GameEngine_Graphics();
	chaiscript::ModulePtr load_module_GameEngine_IO();
	chaiscript::ModulePtr load_module_GameEngine_Math();
	chaiscript::ModulePtr load_module_GameEngine_ScreenManager();
	chaiscript::ModulePtr load_module_GameEngine_Util();

	CHAISCRIPT_MODULE_EXPORT chaiscript::ModulePtr load_module_GameEngine_Actor_protected();
	CHAISCRIPT_MODULE_EXPORT chaiscript::ModulePtr load_module_GameEngine_TextActor_protected();
	CHAISCRIPT_MODULE_EXPORT chaiscript::ModulePtr load_module_GameEngine_WireframeActor_protected();
	CHAISCRIPT_MODULE_EXPORT chaiscript::ModulePtr load_module_GameEngine_MenuScreen_protected();
}

#endif //SMASHBROS_SCRIPT_DISABLE
