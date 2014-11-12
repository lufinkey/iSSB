
#ifndef SMASHBROS_SCRIPT_DISABLE

#include "ScriptMacros.h"

#pragma once

namespace ScriptModule
{
	CHAISCRIPT_MODULE_EXPORT chaiscript::ModulePtr load_module_ChaiScript_stdlib();

	class ScriptManager
	{
		friend chaiscript::ModulePtr load_module_ChaiScript_stdlib();
	private:
		static bool loaded;

		static ArrayList<ScriptEntityInfo*> scriptEntities;
		static ArrayList<ScriptData*> loadedScripts;

	public:
		static chaiscript::ModulePtr module_stdlib;

		static chaiscript::ModulePtr module_GameEngine;

		static chaiscript::ModulePtr module_GameEngine_Actor_protected;
		static chaiscript::ModulePtr module_GameEngine_TextActor_protected;
		static chaiscript::ModulePtr module_GameEngine_WireframeActor_protected;
		static chaiscript::ModulePtr module_GameEngine_MenuScreen_protected;
		
		static chaiscript::ModulePtr module_SmashBros;

		static chaiscript::ModulePtr module_SmashBros_GameElement_protected;
		static chaiscript::ModulePtr module_SmashBros_Player_protected;
		static chaiscript::ModulePtr module_SmashBros_Stage_protected;
		static chaiscript::ModulePtr module_SmashBros_Item_protected;
		static chaiscript::ModulePtr module_SmashBros_Projectile_protected;

		static void load();

		static void addScriptEntityMembers(chaiscript::ChaiScript& script, ScriptData* scriptData);
		static void addScriptInfoMembers(chaiscript::ChaiScript& script, ScriptData* scriptData, const ScriptEntityInfo::ScriptInfo& scriptInfo);

		static boolean loadScript(const String& scriptPath, const ScriptEntityInfo& entityInfo);
		static boolean loadScriptEntity(const ScriptEntityInfo& entityInfo, String& error=String(""));

		static ScriptData* getScriptData(const String&path);

		static void unloadScript(const String& scriptPath);
		static void unloadScriptEntity(const ScriptEntityInfo& entityInfo);

		static chaiscript::Boxed_Value callFunction(chaiscript::ChaiScript& script, const String& name, std::vector<chaiscript::Boxed_Value>& args);
		static chaiscript::Boxed_Value callFunction(chaiscript::ChaiScript& script, const std::string& name, std::vector<chaiscript::Boxed_Value>& args);

		static chaiscript::Boxed_Value getVariable(chaiscript::ChaiScript& script, const String& name);
		static chaiscript::Boxed_Value getVariable(chaiscript::ChaiScript& script, const std::string& name);

		static void setVariable(chaiscript::ChaiScript& script, const String& name, const chaiscript::Boxed_Value& value);
		static void setVariable(chaiscript::ChaiScript& script, const std::string& name, const chaiscript::Boxed_Value& value);
	};
}

#endif //SMASHBROS_SCRIPT_DISABLE
