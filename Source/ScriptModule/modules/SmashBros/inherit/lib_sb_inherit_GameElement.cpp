
#ifndef SMASHBROS_SCRIPT_DISABLE

#include "lib_sb_inherit_GameElement.h"

namespace SmashBros
{
	SCRIPTEDCLASS_CONSTRUCTOR_HEADER_NOBASE(GameElement) : SCRIPTEDCLASS_CLASSNAME(GameElement)(scriptData, 0, 0)
	{
		//default constructor
	}

	SCRIPTEDCLASS_CONSTRUCTOR_HEADER(GameElement, x1 _COMMA y1, float x1, float y1)
	{
		SCRIPTEDCLASS_CONSTRUCTOR_LOADSCRIPT(GameElement)

		SCRIPTEDCLASS_FUNCTION_LOAD(void, GameElement, Update, long)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, GameElement, Draw, Graphics2D&, long)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, GameElement, onAnimationFinish, const String&)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, GameElement, onMouseEnter)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, GameElement, onMouseLeave)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, GameElement, onClick)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, GameElement, onRelease)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, GameElement, onMoveFinish)
		SCRIPTEDCLASS_FUNCTION_LOAD(bool, GameElement, isOnScreen)

		SCRIPTEDCLASS_CONSTRUCTOR_ADDMODULES(
			ScriptModule::ScriptManager::module_GameEngine,
			ScriptModule::ScriptManager::module_SmashBros,
			ScriptModule::ScriptManager::module_GameEngine_Actor_protected,
			ScriptModule::ScriptManager::module_SmashBros_GameElement_protected)
	}

	SCRIPTEDCLASS_LOADTYPEFUNCTIONS_HEADER(GameElement)
	{
		SCRIPTEDCLASS_LOADTYPEFUNCTIONS_BODY(GameElement)
		SCRIPTEDCLASS_NEWFUNCTION_ADD(GameElement)
		SCRIPTEDCLASS_NEWFUNCTION_ADD(GameElement, float, float)
	}

	SCRIPTEDCLASS_MEMBERS_DEFINE(GameElement)

	SCRIPTEDCLASS_FUNCTION_DEFINE(void, GameElement, Update, , , gameTime, long gameTime)
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, GameElement, Draw, , , g _COMMA gameTime, Graphics2D&g, long gameTime)
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, GameElement, onAnimationFinish, , , name, const String& name)
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, GameElement, onMouseEnter , , , )
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, GameElement, onMouseLeave, , , )
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, GameElement, onClick, , , )
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, GameElement, onRelease, , , )
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, GameElement, onMoveFinish, , , )
	SCRIPTEDCLASS_FUNCTION_DEFINE(bool, GameElement, isOnScreen, return, true, )



	SCRIPTEDCLASS_LOADPROTECTEDMODULE_HEADER(SmashBros, GameElement)
	{
		chaiscript::Module* m_sb_gameelement_protected = new chaiscript::Module();

		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_gameelement_protected, GameElement, isColliding2, )
		SCRIPTEDCLASS_PROTECTEDMODULE_ADDSTATIC(m_sb_gameelement_protected, GameElement, getOverlapRect, (GameEngine::Rectangle(*)(GameEngine::Rectangle, GameEngine::Rectangle)))
		SCRIPTEDCLASS_PROTECTEDMODULE_ADDSTATIC(m_sb_gameelement_protected, GameElement, getOverlapRect, (GameEngine::RectangleF(*)(GameEngine::RectangleF, GameEngine::RectangleF)))

		return chaiscript::ModulePtr(m_sb_gameelement_protected);
	}



	SCRIPTEDCLASS_NEWFUNCTION_HEADER(GameElement)
	{
		SCRIPTEDCLASS_NEWFUNCTION_BODY(GameElement)
	}

	SCRIPTEDCLASS_NEWFUNCTION_HEADER(GameElement, float x1, float y1)
	{
		SCRIPTEDCLASS_NEWFUNCTION_BODY(GameElement, x1, y1)
	}

	SCRIPTEDCLASS_DELETEFUNCTION_HEADER(GameElement)
	{
		SCRIPTEDCLASS_DELETEFUNCTION_BODY(GameElement)
	}
}

#endif //SMASHBROS_SCRIPT_DISABLE
