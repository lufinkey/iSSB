
#ifndef SMASHBROS_SCRIPT_DISABLE

#include "../../../ScriptManager.h"

#include "../lib_SmashBros.h"

#include "../../../../SmashBros/Stage.h"

#pragma once

namespace SmashBros
{
	SCRIPTEDCLASS_CLASSHEADER(SmashBros, Stage)
	{
		friend SCRIPTEDCLASS_NEWFUNCTION_HEADER(Stage, float, float);
		
		SCRIPTEDCLASS_CONSTRUCTOR_DECLARE(Stage, float x1, float y1)

		SCRIPTEDCLASS_MEMBERS_DECLARE(SmashBros, Stage)

		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Stage, Update, long gameTime)
		SCRIPTEDCLASS_FUNCTION_DECLARE(void, Stage, Draw, Graphics2D&g, long gameTime)
	};

	SCRIPTEDCLASS_NEWFUNCTION_HEADER(Stage, float, float);
	SCRIPTEDCLASS_DELETEFUNCTION_HEADER(Stage);
}

#endif //SMASHBROS_SCRIPT_DISABLE
