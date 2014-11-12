
#ifndef SMASHBROS_SCRIPT_DISABLE

#include "lib_ge_inherit_Actor.h"

namespace GameEngine
{
	SCRIPTEDCLASS_CONSTRUCTOR_HEADER_NOBASE(Actor) : SCRIPTEDCLASS_CLASSNAME(Actor)(scriptData, 0, 0)
	{
		//default constructor
	}

	SCRIPTEDCLASS_CONSTRUCTOR_HEADER(Actor, x1 _COMMA y1, float x1, float y1)
	{
		SCRIPTEDCLASS_CONSTRUCTOR_LOADSCRIPT(Actor)

		SCRIPTEDCLASS_FUNCTION_LOAD(void, Actor, Update, long)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Actor, Draw, Graphics2D&, long)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Actor, onAnimationFinish, const String&)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Actor, onMouseEnter)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Actor, onMouseLeave)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Actor, onClick)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Actor, onRelease)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Actor, onMoveFinish)
		SCRIPTEDCLASS_FUNCTION_LOAD(bool, Actor, isOnScreen)

		SCRIPTEDCLASS_CONSTRUCTOR_ADDMODULES(
			ScriptModule::ScriptManager::module_GameEngine,
			ScriptModule::ScriptManager::module_SmashBros,
			ScriptModule::ScriptManager::module_GameEngine_Actor_protected)
	}

	SCRIPTEDCLASS_LOADTYPEFUNCTIONS_HEADER(Actor)
	{
		SCRIPTEDCLASS_LOADTYPEFUNCTIONS_BODY(Actor)
		SCRIPTEDCLASS_NEWFUNCTION_ADD(Actor)
		SCRIPTEDCLASS_NEWFUNCTION_ADD(Actor, float, float)
	}

	SCRIPTEDCLASS_MEMBERS_DEFINE(Actor)

	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Actor, Update, , , gameTime, long gameTime)
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Actor, Draw, , , g _COMMA gameTime, Graphics2D&g, long gameTime)
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Actor, onAnimationFinish, , , name, const String& name)
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Actor, onMouseEnter , , , )
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Actor, onMouseLeave, , , )
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Actor, onClick, , , )
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Actor, onRelease, , , )
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Actor, onMoveFinish, , , )
	SCRIPTEDCLASS_FUNCTION_DEFINE(bool, Actor, isOnScreen, return, true, )



	SCRIPTEDCLASS_LOADPROTECTEDMODULE_HEADER(GameEngine, Actor)
	{
		chaiscript::Module* m_ge_actor_protected = new chaiscript::Module();

		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_ge_actor_protected, Actor, drawActor, )

		return chaiscript::ModulePtr(m_ge_actor_protected);
	}



	SCRIPTEDCLASS_NEWFUNCTION_HEADER(Actor)
	{
		SCRIPTEDCLASS_NEWFUNCTION_BODY(Actor)
	}

	SCRIPTEDCLASS_NEWFUNCTION_HEADER(Actor, float x1, float y1)
	{
		SCRIPTEDCLASS_NEWFUNCTION_BODY(Actor, x1, y1)
	}

	SCRIPTEDCLASS_DELETEFUNCTION_HEADER(Actor)
	{
		SCRIPTEDCLASS_DELETEFUNCTION_BODY(Actor)
	}
}

#endif //SMASHBROS_SCRIPT_DISABLE
