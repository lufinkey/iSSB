
#ifndef SMASHBROS_SCRIPT_DISABLE

#include "../../../ScriptManager.h"

#include "../lib_SmashBros.h"

#include "../../../../SmashBros/GameElement.h"

#pragma once

namespace SmashBros
{
	SCRIPTEDCLASS_CLASSHEADER(SmashBros, GameElement)
	{
		friend SCRIPTEDCLASS_NEWFUNCTION_HEADER(GameElement);
		friend SCRIPTEDCLASS_NEWFUNCTION_HEADER(GameElement, float, float);
		
		SCRIPTEDCLASS_CONSTRUCTOR_DECLARE(GameElement)
		SCRIPTEDCLASS_CONSTRUCTOR_DECLARE(GameElement, float x1, float y1)

		SCRIPTEDCLASS_MEMBERS_DECLARE(SmashBros, GameElement)

		SCRIPTEDCLASS_FUNCTION_DECLARE(void, GameElement, Update, long gameTime)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, GameElement, Draw, Graphics2D&g, long gameTime)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, GameElement, onAnimationFinish, const String& name)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, GameElement, onMouseEnter)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, GameElement, onMouseLeave)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, GameElement, onClick)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, GameElement, onRelease)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, GameElement, onMoveFinish)
		SCRIPTEDCLASS_FUNCTION_DECLARE(bool, GameElement, isOnScreen)
	};

	SCRIPTEDCLASS_NEWFUNCTION_HEADER(GameElement);
	SCRIPTEDCLASS_NEWFUNCTION_HEADER(GameElement, float, float);
	SCRIPTEDCLASS_DELETEFUNCTION_HEADER(GameElement);
}

#endif //SMASHBROS_SCRIPT_DISABLE
