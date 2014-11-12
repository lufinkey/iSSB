
#ifndef SMASHBROS_SCRIPT_DISABLE

#include "lib_ge_inherit_WireframeActor.h"

namespace GameEngine
{
	SCRIPTEDCLASS_CONSTRUCTOR_HEADER_NOBASE(WireframeActor) : SCRIPTEDCLASS_CLASSNAME(WireframeActor)(scriptData, 0, 0, 0, 0)
	{
		//default constructor
	}

	SCRIPTEDCLASS_CONSTRUCTOR_HEADER(WireframeActor, x1 _COMMA y1 _COMMA width _COMMA height, float x1, float y1, int width, int height)
	{
		SCRIPTEDCLASS_CONSTRUCTOR_LOADSCRIPT(WireframeActor)

		SCRIPTEDCLASS_FUNCTION_LOAD(void, WireframeActor, Update, long)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, WireframeActor, Draw, Graphics2D&, long)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, WireframeActor, onMouseEnter)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, WireframeActor, onMouseLeave)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, WireframeActor, onClick)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, WireframeActor, onRelease)
		SCRIPTEDCLASS_FUNCTION_LOAD(bool, WireframeActor, isOnScreen)

		SCRIPTEDCLASS_CONSTRUCTOR_ADDMODULES(
			ScriptModule::ScriptManager::module_GameEngine,
			ScriptModule::ScriptManager::module_SmashBros,
			ScriptModule::ScriptManager::module_GameEngine_WireframeActor_protected)
	}

	SCRIPTEDCLASS_LOADTYPEFUNCTIONS_HEADER(WireframeActor)
	{
		SCRIPTEDCLASS_LOADTYPEFUNCTIONS_BODY(WireframeActor)
		SCRIPTEDCLASS_NEWFUNCTION_ADD(WireframeActor,)
		SCRIPTEDCLASS_NEWFUNCTION_ADD(WireframeActor, float, float, int, int)
	}

	SCRIPTEDCLASS_MEMBERS_DEFINE(WireframeActor)

	SCRIPTEDCLASS_FUNCTION_DEFINE(void, WireframeActor, Update, , , gameTime, long gameTime)
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, WireframeActor, Draw, , , g _COMMA gameTime, Graphics2D&g, long gameTime)
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, WireframeActor, onMouseEnter , , , )
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, WireframeActor, onMouseLeave, , , )
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, WireframeActor, onClick, , , )
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, WireframeActor, onRelease, , , )
	SCRIPTEDCLASS_FUNCTION_DEFINE(bool, WireframeActor, isOnScreen, return, true, )



	SCRIPTEDCLASS_LOADPROTECTEDMODULE_HEADER(GameEngine, WireframeActor)
	{
		chaiscript::Module* m_ge_wireframeactor_protected = new chaiscript::Module();

		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_ge_wireframeactor_protected, WireframeActor, drawActor, )

		return chaiscript::ModulePtr(m_ge_wireframeactor_protected);
	}



	SCRIPTEDCLASS_NEWFUNCTION_HEADER(WireframeActor)
	{
		SCRIPTEDCLASS_NEWFUNCTION_BODY(WireframeActor)
	}

	SCRIPTEDCLASS_NEWFUNCTION_HEADER(WireframeActor, float x1, float y1, int width, int height)
	{
		SCRIPTEDCLASS_NEWFUNCTION_BODY(WireframeActor, x1, y1, width, height)
	}

	SCRIPTEDCLASS_DELETEFUNCTION_HEADER(WireframeActor)
	{
		SCRIPTEDCLASS_DELETEFUNCTION_BODY(WireframeActor)
	}
}

#endif //SMASHBROS_SCRIPT_DISABLE
