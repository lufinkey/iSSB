
#ifndef SMASHBROS_SCRIPT_DISABLE

#include "../../../ScriptManager.h"

#include "../lib_GameEngine.h"

#pragma once

namespace GameEngine
{
	SCRIPTEDCLASS_CLASSHEADER(GameEngine, TextActor)
	{
		friend SCRIPTEDCLASS_NEWFUNCTION_HEADER(TextActor, const String&, Font*, const Color&);
		friend SCRIPTEDCLASS_NEWFUNCTION_HEADER(TextActor, float, float, const String&, Font*, const Color&);

		SCRIPTEDCLASS_CONSTRUCTOR_DECLARE(TextActor, const String&str, Font*font, const Color&color)
		SCRIPTEDCLASS_CONSTRUCTOR_DECLARE(TextActor, float x1, float y1, const String&str, Font*font, const Color&color)

		SCRIPTEDCLASS_MEMBERS_DECLARE(GameEngine, TextActor)

		SCRIPTEDCLASS_FUNCTION_DECLARE(void, TextActor, Update, long gameTime)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, TextActor, Draw, Graphics2D&g, long gameTime)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, TextActor, onMouseEnter)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, TextActor, onMouseLeave)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, TextActor, onClick)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, TextActor, onRelease)
		SCRIPTEDCLASS_FUNCTION_DECLARE(bool, TextActor, isOnScreen)
	};

	SCRIPTEDCLASS_NEWFUNCTION_HEADER(TextActor, const String&, Font*, const Color&);
	SCRIPTEDCLASS_NEWFUNCTION_HEADER(TextActor, float, float, const String&, Font*, const Color&);
	SCRIPTEDCLASS_DELETEFUNCTION_HEADER(TextActor);
};

#endif //SMASHBROS_SCRIPT_DISABLE
