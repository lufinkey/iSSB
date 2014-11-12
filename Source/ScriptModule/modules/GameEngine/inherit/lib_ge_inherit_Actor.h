
#ifndef SMASHBROS_SCRIPT_DISABLE

#include "../../../ScriptManager.h"

#include "../lib_GameEngine.h"

#pragma once

namespace GameEngine
{
	SCRIPTEDCLASS_CLASSHEADER(GameEngine, Actor)
	{
		friend SCRIPTEDCLASS_NEWFUNCTION_HEADER(Actor);
		friend SCRIPTEDCLASS_NEWFUNCTION_HEADER(Actor, float, float);

		SCRIPTEDCLASS_CONSTRUCTOR_DECLARE(Actor)
		SCRIPTEDCLASS_CONSTRUCTOR_DECLARE(Actor, float x1, float y1)

		SCRIPTEDCLASS_MEMBERS_DECLARE(GameEngine, Actor)

		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Actor, Update, long gameTime)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Actor, Draw, Graphics2D&g, long gameTime)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Actor, onAnimationFinish, const String& name)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Actor, onMouseEnter)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Actor, onMouseLeave)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Actor, onClick)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Actor, onRelease)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Actor, onMoveFinish)
		SCRIPTEDCLASS_FUNCTION_DECLARE(bool, Actor, isOnScreen)
	};

	SCRIPTEDCLASS_NEWFUNCTION_HEADER(Actor);
	SCRIPTEDCLASS_NEWFUNCTION_HEADER(Actor, float, float);
	SCRIPTEDCLASS_DELETEFUNCTION_HEADER(Actor);
}

#endif //SMASHBROS_SCRIPT_DISABLE
