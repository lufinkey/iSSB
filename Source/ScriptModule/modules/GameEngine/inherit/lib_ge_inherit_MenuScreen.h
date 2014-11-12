
#ifndef SMASHBROS_SCRIPT_DISABLE

#include "../../../ScriptManager.h"

#include "../lib_GameEngine.h"

#pragma once

namespace GameEngine
{
	SCRIPTEDCLASS_CLASSHEADER(GameEngine, MenuScreen)
	{
		friend SCRIPTEDCLASS_NEWFUNCTION_HEADER(MenuScreen, const String&);

		SCRIPTEDCLASS_CONSTRUCTOR_DECLARE(MenuScreen, const String&)

		SCRIPTEDCLASS_MEMBERS_DECLARE(GameEngine, MenuScreen)

		SCRIPTEDCLASS_FUNCTION_DECLARE(void, MenuScreen, Initialize)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, MenuScreen, LoadContent)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, MenuScreen, UnloadContent)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, MenuScreen, Update, long gameTime)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, MenuScreen, Draw, Graphics2D&g, long gameTime)
	};

	SCRIPTEDCLASS_NEWFUNCTION_HEADER(MenuScreen, const String&);
	SCRIPTEDCLASS_DELETEFUNCTION_HEADER(MenuScreen);
}

#endif //SMASHBROS_SCRIPT_DISABLE
