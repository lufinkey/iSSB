
#ifndef SMASHBROS_SCRIPT_DISABLE

#include "lib_sb_inherit_Stage.h"

namespace SmashBros
{
	SCRIPTEDCLASS_CONSTRUCTOR_HEADER(Stage, x1 _COMMA y1, float x1, float y1)
	{
		SCRIPTEDCLASS_CONSTRUCTOR_LOADSCRIPT(Stage)

		SCRIPTEDCLASS_FUNCTION_LOAD(void, Stage, Update, long)
		SCRIPTEDCLASS_FUNCTION_LOAD(void, Stage, Draw, Graphics2D&, long)

		SCRIPTEDCLASS_CONSTRUCTOR_ADDMODULES(
			ScriptModule::ScriptManager::module_GameEngine,
			ScriptModule::ScriptManager::module_SmashBros,
			ScriptModule::ScriptManager::module_SmashBros_Stage_protected)
	}

	SCRIPTEDCLASS_LOADTYPEFUNCTIONS_HEADER(Stage)
	{
		SCRIPTEDCLASS_LOADTYPEFUNCTIONS_BODY(Stage)
		SCRIPTEDCLASS_NEWFUNCTION_ADD(Stage, float, float)
	}

	SCRIPTEDCLASS_MEMBERS_DEFINE(Stage)

	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Stage, Update, , , gameTime, long gameTime)
	SCRIPTEDCLASS_FUNCTION_DEFINE(void, Stage, Draw, , , g _COMMA gameTime, Graphics2D&g, long gameTime)



	//SCRIPTEDCLASS_LOADPROTECTEDMODULE_HEADER(SmashBros, Stage)
	chaiscript::ModulePtr load_module_SmashBros_Stage_protected()
	{
		chaiscript::Module* m_sb_gameelement_protected = new chaiscript::Module();

		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_gameelement_protected, Stage, topBorder, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_gameelement_protected, Stage, bottomBorder, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_gameelement_protected, Stage, leftBorder, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_gameelement_protected, Stage, rightBorder, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_gameelement_protected, Stage, topViewBorder, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_gameelement_protected, Stage, bottomViewBorder, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_gameelement_protected, Stage, leftViewBorder, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_gameelement_protected, Stage, rightViewBorder, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_gameelement_protected, Stage, setItemBoundaries, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_gameelement_protected, Stage, showItemBoundaries, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_gameelement_protected, Stage, setBackgroundScale, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_gameelement_protected, Stage, loadFile, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_gameelement_protected, Stage, drawBackground, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_gameelement_protected, Stage, drawBottomLayer, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_gameelement_protected, Stage, drawMiddleLayer, );
		SCRIPTEDCLASS_PROTECTEDMODULE_ADD(m_sb_gameelement_protected, Stage, drawTopLayer, );
		
		return chaiscript::ModulePtr(m_sb_gameelement_protected);
	}



	SCRIPTEDCLASS_NEWFUNCTION_HEADER(Stage, float x1, float y1)
	{
		SCRIPTEDCLASS_NEWFUNCTION_BODY(Stage, x1, y1)
	}

	SCRIPTEDCLASS_DELETEFUNCTION_HEADER(Stage)
	{
		SCRIPTEDCLASS_DELETEFUNCTION_BODY(Stage)
	}
}

#endif //SMASHBROS_SCRIPT_DISABLE
