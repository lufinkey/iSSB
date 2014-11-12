
#ifndef SMASHBROS_SCRIPT_DISABLE

#include "lib_ge_inherit_MenuScreen.h"

namespace GameEngine
{
	SCRIPTEDCLASS_CONSTRUCTOR_HEADER(MenuScreen, name, const String& name)
	{
		SCRIPTEDCLASS_CONSTRUCTOR_LOADSCRIPT(MenuScreen)

		SCRIPTEDCLASS_FUNCTION_LOAD(void, MenuScreen, Initialize)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, MenuScreen, LoadContent)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, MenuScreen, UnloadContent)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, MenuScreen, Update, long)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, MenuScreen, Draw, Graphics2D&, long)

		SCRIPTEDCLASS_CONSTRUCTOR_ADDMODULES(
			ScriptModule::ScriptManager::module_GameEngine,
			ScriptModule::ScriptManager::module_SmashBros)
	}

	SCRIPTEDCLASS_LOADTYPEFUNCTIONS_HEADER(MenuScreen)
	{
		SCRIPTEDCLASS_LOADTYPEFUNCTIONS_BODY(MenuScreen)
		SCRIPTEDCLASS_NEWFUNCTION_ADD(MenuScreen, const String&)
	}

	SCRIPTEDCLASS_MEMBERS_DEFINE(MenuScreen)

	SCRIPTEDCLASS_FUNCTION_DEFINE(void, MenuScreen, Initialize, , , )
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, MenuScreen, LoadContent, , , )
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, MenuScreen, UnloadContent, , , )
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, MenuScreen, Update, , , gameTime, long gameTime)
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, MenuScreen, Draw, , , g _COMMA gameTime, Graphics2D&g, long gameTime)
	


	SCRIPTEDCLASS_LOADPROTECTEDMODULE_HEADER(GameEngine, MenuScreen)
	{
		chaiscript::Module* m_ge_menuscreen_protected = new chaiscript::Module();

		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_ge_menuscreen_protected, MenuScreen, selectedIndex, )
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_ge_menuscreen_protected, MenuScreen, selecting, )

		return chaiscript::ModulePtr(m_ge_menuscreen_protected);
	}



	SCRIPTEDCLASS_NEWFUNCTION_HEADER(MenuScreen, const String&name)
	{
		SCRIPTEDCLASS_NEWFUNCTION_BODY(MenuScreen, name)
	}

	SCRIPTEDCLASS_DELETEFUNCTION_HEADER(MenuScreen)
	{
		SCRIPTEDCLASS_DELETEFUNCTION_BODY(MenuScreen)
	}
}

#endif //SMASHBROS_SCRIPT_DISABLE
