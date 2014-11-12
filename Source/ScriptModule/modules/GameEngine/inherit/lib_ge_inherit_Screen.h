
#ifndef SMASHBROS_SCRIPT_DISABLE

#include "../../../ScriptManager.h"

#include "../lib_GameEngine.h"

#pragma once

namespace GameEngine
{
	SCRIPTEDCLASS_CLASSHEADER(GameEngine, Screen)
	{
		friend SCRIPTEDCLASS_NEWFUNCTION_HEADER(Screen, const String&);

		SCRIPTEDCLASS_CONSTRUCTOR_DECLARE(Screen, const String&)

		SCRIPTEDCLASS_MEMBERS_DECLARE(GameEngine, Screen)

		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Screen, Initialize)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Screen, LoadContent)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Screen, UnloadContent)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Screen, Update, long gameTime)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Screen, Draw, Graphics2D&g, long gameTime)
	};

	SCRIPTEDCLASS_NEWFUNCTION_HEADER(Screen, const String&);
	SCRIPTEDCLASS_DELETEFUNCTION_HEADER(Screen);
}

#endif //SMASHBROS_SCRIPT_DISABLE
