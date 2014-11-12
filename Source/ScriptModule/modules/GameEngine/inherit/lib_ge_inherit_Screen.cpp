
#ifndef SMASHBROS_SCRIPT_DISABLE

#include "lib_ge_inherit_Screen.h"

namespace GameEngine
{
	SCRIPTEDCLASS_CONSTRUCTOR_HEADER(Screen, name, const String& name)
	{
		SCRIPTEDCLASS_CONSTRUCTOR_LOADSCRIPT(Screen)

		SCRIPTEDCLASS_FUNCTION_LOAD(void, Screen, Initialize)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Screen, LoadContent)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Screen, UnloadContent)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Screen, Update, long)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Screen, Draw, Graphics2D&, long)

		SCRIPTEDCLASS_CONSTRUCTOR_ADDMODULES(
			ScriptModule::ScriptManager::module_GameEngine,
			ScriptModule::ScriptManager::module_SmashBros)
	}

	SCRIPTEDCLASS_LOADTYPEFUNCTIONS_HEADER(Screen)
	{
		SCRIPTEDCLASS_LOADTYPEFUNCTIONS_BODY(Screen)
		SCRIPTEDCLASS_NEWFUNCTION_ADD(Screen, const String&)
	}

	SCRIPTEDCLASS_MEMBERS_DEFINE(Screen)

	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Screen, Initialize, , , )
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Screen, LoadContent, , , )
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Screen, UnloadContent, , , )
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Screen, Update, , , gameTime, long gameTime)
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Screen, Draw, , , g _COMMA gameTime, Graphics2D&g, long gameTime)



	SCRIPTEDCLASS_NEWFUNCTION_HEADER(Screen, const String&name)
	{
		SCRIPTEDCLASS_NEWFUNCTION_BODY(Screen, name)
	}

	SCRIPTEDCLASS_DELETEFUNCTION_HEADER(Screen)
	{
		SCRIPTEDCLASS_DELETEFUNCTION_BODY(Screen)
	}
}

#endif //SMASHBROS_SCRIPT_DISABLE
