
#ifndef SMASHBROS_SCRIPT_DISABLE

#include "ScriptManager.h"
#include "ScriptMacros.h"
#include "ScriptOperatorOverloads.h"

#include <chaiscript/dispatchkit/bootstrap.hpp>
#include <chaiscript/dispatchkit/bootstrap_stl.hpp>

#include "modules/GameEngine/lib_GameEngine.h"
#include "modules/GameEngine/inherit/lib_ge_inherit_Actor.h"
#include "modules/GameEngine/inherit/lib_ge_inherit_TextActor.h"
#include "modules/GameEngine/inherit/lib_ge_inherit_WireframeActor.h"

#include "modules/SmashBros/lib_SmashBros.h"
#include "modules/SmashBros/inherit/lib_sb_inherit_GameElement.h"
#include "modules/SmashBros/inherit/lib_sb_inherit_Player.h"
#include "modules/SmashBros/inherit/lib_sb_inherit_Stage.h"

namespace ScriptModule
{
	chaiscript::ModulePtr load_module_ChaiScript_stdlib()
	{
		chaiscript::ModulePtr m_chaiscript_stdlib = chaiscript::bootstrap::Bootstrap::bootstrap();
		
		m_chaiscript_stdlib->add(chaiscript::bootstrap::standard_library::vector_type<std::vector<chaiscript::Boxed_Value>>("std_vector"));
		m_chaiscript_stdlib->add(chaiscript::bootstrap::standard_library::string_type<std::string>("std_string"));
		m_chaiscript_stdlib->add(chaiscript::bootstrap::standard_library::map_type<std::map<std::string, chaiscript::Boxed_Value>>("std_map"));
		m_chaiscript_stdlib->add(chaiscript::bootstrap::standard_library::pair_type<std::pair<chaiscript::Boxed_Value, chaiscript::Boxed_Value>>("std_pair"));

		return m_chaiscript_stdlib;
	}

	bool ScriptManager::loaded = false;

	chaiscript::ModulePtr ScriptManager::module_stdlib;

	chaiscript::ModulePtr ScriptManager::module_GameEngine;

	chaiscript::ModulePtr ScriptManager::module_GameEngine_Actor_protected;
	chaiscript::ModulePtr ScriptManager::module_GameEngine_TextActor_protected;
	chaiscript::ModulePtr ScriptManager::module_GameEngine_WireframeActor_protected;
	chaiscript::ModulePtr ScriptManager::module_GameEngine_MenuScreen_protected;

	chaiscript::ModulePtr ScriptManager::module_SmashBros;

	chaiscript::ModulePtr ScriptManager::module_SmashBros_GameElement_protected;
	chaiscript::ModulePtr ScriptManager::module_SmashBros_Player_protected;
	chaiscript::ModulePtr ScriptManager::module_SmashBros_Stage_protected;
	chaiscript::ModulePtr ScriptManager::module_SmashBros_Item_protected;
	chaiscript::ModulePtr ScriptManager::module_SmashBros_Projectile_protected;

	ArrayList<ScriptEntityInfo*> ScriptManager::scriptEntities = ArrayList<ScriptEntityInfo*>();
	ArrayList<ScriptData*> ScriptManager::loadedScripts = ArrayList<ScriptData*>();

	void ScriptManager::load()
	{
		if(loaded)
		{
			return;
		}

		module_stdlib = load_module_ChaiScript_stdlib();

		module_GameEngine = GameEngine::load_module_GameEngine();
		module_GameEngine_Actor_protected = GameEngine::load_module_GameEngine_Actor_protected();
		module_GameEngine_TextActor_protected = GameEngine::load_module_GameEngine_TextActor_protected();
		module_GameEngine_WireframeActor_protected = GameEngine::load_module_GameEngine_WireframeActor_protected();

		module_SmashBros = SmashBros::load_module_SmashBros();
		module_SmashBros_GameElement_protected = SmashBros::load_module_SmashBros_GameElement_protected();
		module_SmashBros_Player_protected = SmashBros::load_module_SmashBros_Player_protected();
		module_SmashBros_Stage_protected = SmashBros::load_module_SmashBros_Stage_protected();

		loaded = true;
	}

	void ScriptManager::addScriptEntityMembers(chaiscript::ChaiScript& script, ScriptData* scriptData)
	{
		ArrayList<ScriptEntityInfo::ScriptInfo*> scriptInfos;

		const String& dataFilePath = scriptData->getFilePath();

		ScriptEntityInfo* entityInfo = scriptData->getScriptEntityInfo();
		ScriptEntityInfo::ScriptInfo* mainScriptInfo = (ScriptEntityInfo::ScriptInfo*)&entityInfo->getMainScript();

		String entityPath = entityInfo->getPath() + '/';

		if(!dataFilePath.equals(entityPath + mainScriptInfo->script))
		{
			scriptInfos.add(mainScriptInfo);
		}

		const ArrayList<ScriptEntityInfo::ScriptInfo>& otherScripts = entityInfo->getScripts();
		for(int i=0; i<otherScripts.size(); i++)
		{
			ScriptEntityInfo::ScriptInfo* otherScriptInfo = (ScriptEntityInfo::ScriptInfo*)&otherScripts.get(i);
			if(!dataFilePath.equals(entityPath + otherScriptInfo->script))
			{
				scriptInfos.add(otherScriptInfo);
			}
		}

		for(int i=0; i<scriptInfos.size(); i++)
		{
			ScriptEntityInfo::ScriptInfo* otherScriptInfo = scriptInfos.get(i);
			ScriptData* otherScriptData = ScriptManager::getScriptData(entityPath + otherScriptInfo->script);
			addScriptInfoMembers(script, otherScriptData, *otherScriptInfo);
		}
	}

	void ScriptManager::addScriptInfoMembers(chaiscript::ChaiScript& script, ScriptData* scriptData, const ScriptEntityInfo::ScriptInfo& scriptInfo)
	{
		SCRIPTMGR_LOADTYPEFUNCTIONSCHECK(GameEngine, Actor)
		else SCRIPTMGR_LOADTYPEFUNCTIONSCHECK(GameEngine, TextActor)
		else SCRIPTMGR_LOADTYPEFUNCTIONSCHECK(GameEngine, WireframeActor)
		else SCRIPTMGR_LOADTYPEFUNCTIONSCHECK(SmashBros, GameElement)
		else SCRIPTMGR_LOADTYPEFUNCTIONSCHECK(SmashBros, Player)
		else SCRIPTMGR_LOADTYPEFUNCTIONSCHECK(SmashBros, Stage)
	}

	boolean ScriptManager::loadScript(const String& scriptPath, const ScriptEntityInfo& scriptInfo)
	{
		for(int i=0; i<loadedScripts.size(); i++)
		{
			if(loadedScripts.get(i)->getFilePath().equals(scriptPath))
			{
				return true;
			}
		}

		ScriptData* data = new ScriptData(scriptInfo);
		boolean success = data->loadFromFile(scriptPath);
		if(success)
		{
			loadedScripts.add(data);
			return true;
		}
		delete data;
		return false;
	}

	boolean ScriptManager::loadScriptEntity(const ScriptEntityInfo& entityInfo, String& error)
	{
		String entityPath = entityInfo.getPath();

		String errorMessage;
		
		ScriptData* mainScriptData = new ScriptData(entityInfo);
		boolean success = mainScriptData->loadFromFile(entityPath + '/' + entityInfo.getMainScript().script, errorMessage);
		if(!success)
		{
			delete mainScriptData;
			error = (String)"Unable to load file \"" + entityPath + '/' + entityInfo.getMainScript().script + "\": " + errorMessage;
			return false;
		}

		const ArrayList<ScriptEntityInfo::ScriptInfo>& otherScripts = entityInfo.getScripts();

		ArrayList<ScriptData*> otherScriptData;

		for(int i=0; i<otherScripts.size(); i++)
		{
			ScriptEntityInfo::ScriptInfo scriptInfo = otherScripts.get(i);
			ScriptData* scriptData = new ScriptData(entityInfo);
			if(scriptData->loadFromFile(entityPath + '/' + scriptInfo.script, errorMessage))
			{
				otherScriptData.add(scriptData);
			}
			else
			{
				delete mainScriptData;
				delete scriptData;
				for(int j=0; j<otherScriptData.size(); j++)
				{
					delete otherScriptData.get(j);
				}
				error = (String)"Unable to load file \"" + entityPath + '/' + scriptInfo.script + "\": " + errorMessage;
				return false;
			}
		}

		loadedScripts.add(mainScriptData);
		for(int i=0; i<otherScriptData.size(); i++)
		{
			loadedScripts.add(otherScriptData.get(i));
		}

		Console::WriteLine((String)"Loaded Script Entity: " + entityInfo.getMainScript().name);

		return true;
	}

	ScriptData* ScriptManager::getScriptData(const String& path)
	{
		for(int i=0; i<loadedScripts.size(); i++)
		{
			ScriptData* scriptData = loadedScripts.get(i);
			if(scriptData->getFilePath().equals(path))
			{
				return scriptData;
			}
		}
		return NULL;
	}

	void ScriptManager::unloadScript(const String& scriptPath)
	{
		for(int i=0; i<loadedScripts.size(); i++)
		{
			ScriptData* scriptData = loadedScripts.get(i);
			if(scriptPath.equals(scriptData->getFilePath()))
			{
				delete scriptData;
				loadedScripts.remove(i);
				return;
			}
		}
	}

	void ScriptManager::unloadScriptEntity(const ScriptEntityInfo& entityInfo)
	{
		String entityPath = entityInfo.getPath();
		unloadScript(entityPath + '/' + entityInfo.getMainScript().script);

		const ArrayList<ScriptEntityInfo::ScriptInfo>& otherScripts = entityInfo.getScripts();

		for(int i=0; i<otherScripts.size(); i++)
		{
			unloadScript(entityPath + '/' + otherScripts.get(i).script);
		}
	}

	chaiscript::Boxed_Value ScriptManager::callFunction(chaiscript::ChaiScript& script, const String& name, std::vector<chaiscript::Boxed_Value>& args)
	{
		String argsName = "args";
		if(name.equals(argsName))
		{
			argsName = "params";
		}
		String callHead = (String)"fun(" + argsName + "){ return ";
		String callString =  name + "(";
		for(unsigned int i = 0; i < args.size(); i++)
		{
			callString += argsName + "[" + i + "]";
			if(i != (args.size() - 1))
			{
				callString += ",";
			}
		}
		callString += ");}";

		std::function<chaiscript::Boxed_Value(std::vector<chaiscript::Boxed_Value>&)> func_constructor;

		//first try calling it with "this" keyword.
		try
		{
			func_constructor = script.eval<std::function<chaiscript::Boxed_Value(std::vector<chaiscript::Boxed_Value>&)>>(callHead + "this." + callString);
		}
		catch(const chaiscript::exception::eval_error&)
		{
			//No function with that name exists in that class.
		}

		//try again without "this" keyword"
		try
		{
			func_constructor = script.eval<std::function<chaiscript::Boxed_Value(std::vector<chaiscript::Boxed_Value>&)>>(callHead + callString);
		}
		catch(const chaiscript::exception::eval_error&)
		{
			throw chaiscript::exception::eval_error((String)"no function exists with the name " + name);
		}

		return func_constructor(args);
	}

	chaiscript::Boxed_Value ScriptManager::callFunction(chaiscript::ChaiScript& script, const std::string& name, std::vector<chaiscript::Boxed_Value>& args)
	{
		return callFunction(script, String(name), args);
	}

	chaiscript::Boxed_Value ScriptManager::getVariable(chaiscript::ChaiScript& script, const String& name)
	{
		String callHead = (String)"fun(){ return ";
		String callString =  name + ";}";

		//try getting it with "this" keyword.
		try
		{
			return script.eval<std::function<chaiscript::Boxed_Value()>>(callHead + "this." + callString)();
		}
		catch(const chaiscript::exception::eval_error&)
		{
			//No variable with that name exists.
		}

		//try again without "this" keyword
		try
		{
			return script.eval<std::function<chaiscript::Boxed_Value()>>(callHead + callString)();
		}
		catch(const chaiscript::exception::eval_error&)
		{
			throw chaiscript::exception::eval_error((String)"no variable exists with the name " + name);
		}
	}

	chaiscript::Boxed_Value ScriptManager::getVariable(chaiscript::ChaiScript& script, const std::string&name)
	{
		return getVariable(script, String(name));
	}

	void ScriptManager::setVariable(chaiscript::ChaiScript& script, const String& name, const chaiscript::Boxed_Value& value)
	{
		String argName = "arg";
		if(name.equals(argName))
		{
			argName = "param";
		}
		String callHead = (String)"fun(" + argName + "){ ";
		String callString =  name + "=" + argName + ";}";

		//first try calling it with "this" keyword.
		try
		{
			script.eval<std::function<void(const chaiscript::Boxed_Value&)>>(callHead + "this." + callString)(value);
		}
		catch(const chaiscript::exception::eval_error&)
		{
			//No function with that name exists in that class.
		}

		//try again without "this" keyword"
		try
		{
			script.eval<std::function<void(const chaiscript::Boxed_Value&)>>(callHead + callString)(value);
		}
		catch(const chaiscript::exception::eval_error&)
		{
			throw chaiscript::exception::eval_error((String)"no variable exists with the name " + name);
		}
	}
	
	void ScriptManager::setVariable(chaiscript::ChaiScript& script, const std::string& name, const chaiscript::Boxed_Value& value)
	{
		setVariable(script, String(name), value);
	}



	void ScriptManager_showErrorMessage(const chaiscript::exception::eval_error& evalError, const String& fileName)
	{
		String message;
		if(!(evalError.start_position.line==0 && evalError.start_position.column==0))
		{
			message = (String)"ChaiScript threw an error in file \"" + fileName + "\" at line "
				+ evalError.start_position.line + " at column " + evalError.start_position.column
				+ "\nReason: " + evalError.reason;
		}
		else
		{
			message = (String)"ChaiScript threw an exception in file \"" + fileName + "\" at line "
				+ evalError.call_stack.at(0)->start.line + " at column " + evalError.call_stack.at(0)->start.column
				+ "\nReason: " + evalError.reason;
		}
		Application::showMessage("Error", message);
	}

	void ScriptManager_showErrorMessage(const chaiscript::exception::bad_boxed_cast& e, const String& fileName)
	{
		Application::showMessage("Error", (String)"ChaiScript threw a bad_boxed_cast exception in file " + fileName + "\n" + e.what());
	}

	void ScriptManager_showErrorMessage(const chaiscript::exception::dispatch_error& e, const String& fileName)
	{
		Application::showMessage("Error", (String)"ChaiScript threw a dispatch_error exception in file " + fileName + "\n" + e.what());
	}

	void ScriptManager_showErrorMessage(const chaiscript::exception::file_not_found_error& e, const String& fileName)
	{
		Application::showMessage("Error", (String)"ChaiScript threw a file_not_found_error exception in file " + fileName + "\n" + e.what());
	}

	void ScriptManager_showErrorMessage(const chaiscript::exception::guard_error& e, const String& fileName)
	{
		Application::showMessage("Error", (String)"ChaiScript threw a guard_error exception in file " + fileName + "\n" + e.what());
	}

	void ScriptManager_showErrorMessage(const chaiscript::exception::load_module_error& e, const String& fileName)
	{
		Application::showMessage("Error", (String)"ChaiScript threw a load_module_error exception in file " + fileName + "\n" + e.what());
	}

	void ScriptManager_showErrorMessage(const std::exception& e, const String& fileName)
	{
		Application::showMessage("Error", (String)"ChaiScript threw an exception in file " + fileName + "\n" + e.what());
	}
}

#endif //SMASHBROS_SCRIPT_DISABLE
