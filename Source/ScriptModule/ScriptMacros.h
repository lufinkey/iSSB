
#ifndef SMASHBROS_SCRIPT_DISABLE

#include <chaiscript/chaiscript.hpp>
#include "ScriptEntity.h"

#pragma once

namespace ScriptModule
{
	void ScriptManager_showErrorMessage(const chaiscript::exception::eval_error& e, const String& fileName);
	void ScriptManager_showErrorMessage(const chaiscript::exception::bad_boxed_cast& e, const String& fileName);
	void ScriptManager_showErrorMessage(const chaiscript::exception::dispatch_error& e, const String& fileName);
	void ScriptManager_showErrorMessage(const chaiscript::exception::file_not_found_error& e, const String& fileName);
	void ScriptManager_showErrorMessage(const chaiscript::exception::guard_error& e, const String& fileName);
	void ScriptManager_showErrorMessage(const chaiscript::exception::load_module_error& e, const String& fileName);
	void ScriptManager_showErrorMessage(const std::exception& e, const String& fileName);

	template<typename T>
	bool ScriptManager_loadScriptedClassMemberFunction(std::function<T>& func, chaiscript::ChaiScript*script, const char* funcName)
	{
		try
		{
			func = script->eval<std::function<T>>(funcName);
		}
		catch(const std::exception&)
		{
			//function is not defined in script
			return false;
		}
		return true;
	}
}



#define SCRIPTMGR_ERRORMSG(e, fileName) ScriptModule::ScriptManager_showErrorMessage(e, fileName)



#define SCRIPTMGR_ERRORHANDLE(expression, fileName, catchExpression) \
	try \
	{ \
		expression \
	} \
	catch(const chaiscript::exception::eval_error& e) \
	{ \
		SCRIPTMGR_ERRORMSG(e, fileName); \
		catchExpression \
	} \
	catch(const chaiscript::exception::bad_boxed_cast& e) \
	{ \
		SCRIPTMGR_ERRORMSG(e, fileName); \
		catchExpression \
	} \
	catch(const chaiscript::exception::dispatch_error& e) \
	{ \
		SCRIPTMGR_ERRORMSG(e, fileName); \
		catchExpression \
	} \
	catch(const chaiscript::exception::file_not_found_error& e) \
	{ \
		SCRIPTMGR_ERRORMSG(e, fileName); \
		catchExpression \
	} \
	catch(const chaiscript::exception::guard_error& e) \
	{ \
		SCRIPTMGR_ERRORMSG(e, fileName); \
		catchExpression \
	} \
	catch(const chaiscript::exception::load_module_error& e) \
	{ \
		SCRIPTMGR_ERRORMSG(e, fileName); \
		catchExpression \
	} \
	catch(const std::exception& e) \
	{ \
		SCRIPTMGR_ERRORMSG(e, fileName); \
		catchExpression \
	} \
	catch(...) \
	{ \
		GameEngine::Application::showMessage("Error", (String)"Unknown exception in file " + fileName); \
		catchExpression \
	}



#define SCRIPTEDCLASS_CLASSNAME(className) Scripted##className



#define SCRIPTEDCLASS_CLASSNAME_FULL(namespaceName, className) namespaceName::SCRIPTEDCLASS_CLASSNAME(className)



#define SCRIPTEDCLASS_CLASSNAME_PREFIXED(prefix, className) _CONCAT_TOKENS(prefix, SCRIPTEDCLASS_CLASSNAME(className))



#define SCRIPTMGR_LOADTYPEFUNCTIONSCHECK(namespaceName, className) \
	if(scriptInfo.type.equals(#className)) \
	{ \
		namespaceName::SCRIPTEDCLASS_CLASSNAME(className)::loadScriptTypeFunctions(script, scriptData, scriptInfo.name); \
	}



#define SCRIPTMGR_ADDSHAREDFUNCTIONS(module, className) \
	SCRIPTEDCLASS_CLASSNAME(className)::loadScriptSharedFunctions(module);



#define SCRIPTMGR_ADDSCRIPTEDCLASSINHERITENCE(module, namespaceName, className) \
	module->add(chaiscript::user_type<namespaceName::SCRIPTEDCLASS_CLASSNAME(className)>(), #className); \
	module->add(chaiscript::base_class<namespaceName::className, namespaceName::SCRIPTEDCLASS_CLASSNAME(className)>());



#define SCRIPTEDCLASS_CLASSHEADER(namespaceName, className) \
	class SCRIPTEDCLASS_CLASSNAME(className) : public namespaceName::className



#define SCRIPTEDCLASS_NEWFUNCTION_NAME(className) _CONCAT_TOKENS(new_, SCRIPTEDCLASS_CLASSNAME(className))



#define SCRIPTEDCLASS_DELETEFUNCTION_NAME(className) _CONCAT_TOKENS(delete_, SCRIPTEDCLASS_CLASSNAME(className))



#define SCRIPTEDCLASS_CONSTRUCTOR_HEADER(className, args, ...) \
	SCRIPTEDCLASS_CLASSNAME(className)::SCRIPTEDCLASS_CLASSNAME(className)(ScriptModule::ScriptData*scriptData, ##__VA_ARGS__) : className (args)



#define SCRIPTEDCLASS_CONSTRUCTOR_HEADER_NOBASE(className, ...) \
	SCRIPTEDCLASS_CLASSNAME(className)::SCRIPTEDCLASS_CLASSNAME(className)(ScriptModule::ScriptData*scriptData, ##__VA_ARGS__)



#define SCRIPTEDCLASS_NEWFUNCTION_HEADER(className, ...) \
	SCRIPTEDCLASS_CLASSNAME(className)* SCRIPTEDCLASS_NEWFUNCTION_NAME(className) (ScriptModule::ScriptData*scriptData, ##__VA_ARGS__, std::vector<chaiscript::Boxed_Value>&args)



#define SCRIPTEDCLASS_DELETEFUNCTION_HEADER(className) \
	void SCRIPTEDCLASS_DELETEFUNCTION_NAME(className) (SCRIPTEDCLASS_CLASSNAME(className)*scriptObj)



#define SCRIPTEDCLASS_LOADSHAREDFUNCTIONS_HEADER(className) \
	void SCRIPTEDCLASS_CLASSNAME(className)::loadScriptSharedFunctions(chaiscript::Module* module)



#define SCRIPTEDCLASS_LOADTYPEFUNCTIONS_HEADER(className) \
	void SCRIPTEDCLASS_CLASSNAME(className)::loadScriptTypeFunctions(chaiscript::ChaiScript& script, ScriptModule::ScriptData*scriptData, const String& typeName)



#define SCRIPTEDCLASS_LOADPROTECTEDMODULE_HEADER(namespaceName, className) \
	chaiscript::ModulePtr load_module_##namespaceName##_##className##_protected()



#define SCRIPTEDCLASS_CONSTRUCTOR_DECLARE(className, ...) \
	public: \
		SCRIPTEDCLASS_CLASSNAME(className) (ScriptModule::ScriptData*scriptData, ##__VA_ARGS__);



#define SCRIPTEDCLASS_MEMBERS_DECLARE(namespaceName, className) \
		friend class ScriptModule::ScriptManager; \
		friend SCRIPTEDCLASS_LOADPROTECTEDMODULE_HEADER(namespaceName, className); \
	public: \
		virtual ~SCRIPTEDCLASS_CLASSNAME(className)(); \
		chaiscript::ChaiScript* getScriptEngine(); \
		static void loadScriptSharedFunctions(chaiscript::Module* module); \
	private: \
		boolean usable; \
		chaiscript::ChaiScript* script; \
		ScriptModule::ScriptData* scriptData; \
		std::function<SCRIPTEDCLASS_CLASSNAME(className)*()> func_constructor; \
		std::function<void()> func_destructor; \
		static void loadScriptTypeFunctions(chaiscript::ChaiScript& script, ScriptModule::ScriptData*scriptData, const String& typeName); \
		chaiscript::Boxed_Value callFunction(const String& name, std::vector<chaiscript::Boxed_Value>& args); \
		chaiscript::Boxed_Value callFunction(const std::string& name, std::vector<chaiscript::Boxed_Value>& args); \
		chaiscript::Boxed_Value getVariable(const String& name); \
		chaiscript::Boxed_Value getVariable(const std::string& name); \
		void setVariable(const String& name, const chaiscript::Boxed_Value& value); \
		void setVariable(const std::string& name, const chaiscript::Boxed_Value& value);



#define SCRIPTEDCLASS_FUNCTION_DECLARE(returnType, className, functionName, ...) \
	private: \
		std::function<returnType(__VA_ARGS__)> func_##functionName; \
		static returnType base_##functionName( SCRIPTEDCLASS_CLASSNAME(className)* scriptObj, ##__VA_ARGS__); \
	public: \
		virtual returnType functionName(__VA_ARGS__);



#define SCRIPTEDCLASS_LOADSHAREDFUNCTIONS_BODY(className) \
	module->add(chaiscript::fun((chaiscript::Boxed_Value(SCRIPTEDCLASS_CLASSNAME(className)::*)(const String&,std::vector<chaiscript::Boxed_Value>&))&SCRIPTEDCLASS_CLASSNAME(className)::callFunction), "callFunction"); \
	module->add(chaiscript::fun((chaiscript::Boxed_Value(SCRIPTEDCLASS_CLASSNAME(className)::*)(const std::string&,std::vector<chaiscript::Boxed_Value>&))&SCRIPTEDCLASS_CLASSNAME(className)::callFunction), "callFunction"); \
	module->add(chaiscript::fun((chaiscript::Boxed_Value(SCRIPTEDCLASS_CLASSNAME(className)::*)(const String&))&SCRIPTEDCLASS_CLASSNAME(className)::getVariable), "getVariable"); \
	module->add(chaiscript::fun((chaiscript::Boxed_Value(SCRIPTEDCLASS_CLASSNAME(className)::*)(const std::string&))&SCRIPTEDCLASS_CLASSNAME(className)::getVariable), "getVariable"); \
	module->add(chaiscript::fun((void(SCRIPTEDCLASS_CLASSNAME(className)::*)(const String&,const chaiscript::Boxed_Value&))&SCRIPTEDCLASS_CLASSNAME(className)::setVariable), "setVariable"); \
	module->add(chaiscript::fun((void(SCRIPTEDCLASS_CLASSNAME(className)::*)(const std::string&,const chaiscript::Boxed_Value&))&SCRIPTEDCLASS_CLASSNAME(className)::setVariable), "setVariable");



#define SCRIPTEDCLASS_LOADTYPEFUNCTIONS_BODY(className) \
	script.add(chaiscript::fun(&SCRIPTEDCLASS_DELETEFUNCTION_NAME(className)), (String)"delete_" + typeName); \



#define SCRIPTEDCLASS_NEWFUNCTION_ADD(className, ...) \
	script.add(chaiscript::fun((SCRIPTEDCLASS_CLASSNAME(className)* (*)(ScriptModule::ScriptData*, ##__VA_ARGS__, std::vector<chaiscript::Boxed_Value>&))&SCRIPTEDCLASS_NEWFUNCTION_NAME(className), scriptData), (String)"new_" + typeName);



#define SCRIPTEDCLASS_CONSTRUCTOR_LOADSCRIPT(className) \
		ScriptModule::ScriptEntityInfo::ScriptInfo* scriptInfo = scriptData->getScriptInfo(); \
		this->usable = true; \
		this->scriptData = scriptData; \
		this->script = new chaiscript::ChaiScript(ScriptModule::ScriptManager::module_stdlib); \
		SCRIPTMGR_ERRORHANDLE(this->script->eval(this->scriptData->getContents());, scriptData->getFilePath(), this->usable = false;); \
		if(!(this->usable)) \
		{ \
			return; \
		} \
		ScriptModule::ScriptManager::addScriptEntityMembers(*script, scriptData); \
		loadScriptTypeFunctions(*script, scriptData, scriptInfo->name); \
		if(!ScriptModule::ScriptManager_loadScriptedClassMemberFunction(func_constructor, this->script, "constructor")) \
		{ \
			this->script->eval("def constructor(){return this;}"); \
			ScriptModule::ScriptManager_loadScriptedClassMemberFunction(func_constructor, this->script, "constructor"); \
		} \
		ScriptModule::ScriptManager_loadScriptedClassMemberFunction(func_destructor, script, "destructor"); \



#define SCRIPTEDCLASS_FUNCTION_LOAD(returnType, className, memberName,...) \
	ScriptModule::ScriptManager_loadScriptedClassMemberFunction(func_##memberName, script, #memberName); \
	script->add(chaiscript::fun(( returnType(*)(SCRIPTEDCLASS_CLASSNAME(className)*, ##__VA_ARGS__) )&SCRIPTEDCLASS_CLASSNAME(className)::base_##memberName, this), "base_" #memberName); \



#define SCRIPTEDCLASS_CONSTRUCTOR_ADDMODULES(...) \
	{ \
		std::vector<chaiscript::ModulePtr> scriptedclass_modules = {__VA_ARGS__}; \
		for(unsigned int i=0; i<scriptedclass_modules.size(); i++) \
		{ \
			this->script->add(scriptedclass_modules[i]); \
		} \
		scriptedclass_modules.resize(0); \
		this->script->add_global(chaiscript::var(this), "this"); \
	}



#define SCRIPTEDCLASS_FUNCTION_CALL(expression, functionName, ...) \
	if(func_##functionName) \
	{ \
		SCRIPTMGR_ERRORHANDLE(expression func_##functionName ( __VA_ARGS__ );, scriptData->getFilePath(), ); \
	} \
	else \
	{ \
		expression base_##functionName (this, ##__VA_ARGS__ ); \
	}



#define SCRIPTEDCLASS_NEWFUNCTION_CALL(className) \
	SCRIPTEDCLASS_CLASSNAME_PREFIXED(new_, className)



#define SCRIPTEDCLASS_MEMBERS_DEFINE(className) \
	SCRIPTEDCLASS_CLASSNAME(className)::~SCRIPTEDCLASS_CLASSNAME(className)() \
	{ \
		if(func_destructor) \
		{ \
			SCRIPTMGR_ERRORHANDLE(func_destructor();, scriptData->getFilePath(), ) \
		} \
		delete script; \
	} \
	chaiscript::ChaiScript* SCRIPTEDCLASS_CLASSNAME(className)::getScriptEngine() \
	{ \
		return script; \
	} \
	chaiscript::Boxed_Value SCRIPTEDCLASS_CLASSNAME(className)::callFunction(const String& name, std::vector<chaiscript::Boxed_Value>& args) \
	{ \
		return ScriptModule::ScriptManager::callFunction(*script, name, args); \
	} \
	chaiscript::Boxed_Value SCRIPTEDCLASS_CLASSNAME(className)::callFunction(const std::string& name, std::vector<chaiscript::Boxed_Value>& args) \
	{ \
		return callFunction(String(name), args); \
	} \
	chaiscript::Boxed_Value SCRIPTEDCLASS_CLASSNAME(className)::getVariable(const String& name) \
	{ \
		return ScriptModule::ScriptManager::getVariable(*script, name); \
	} \
	chaiscript::Boxed_Value SCRIPTEDCLASS_CLASSNAME(className)::getVariable(const std::string& name) \
	{ \
		return getVariable(String(name)); \
	} \
	void SCRIPTEDCLASS_CLASSNAME(className)::setVariable(const String& name, const chaiscript::Boxed_Value& value) \
	{ \
		ScriptModule::ScriptManager::setVariable(*script, name, value); \
	} \
	void SCRIPTEDCLASS_CLASSNAME(className)::setVariable(const std::string& name, const chaiscript::Boxed_Value& value) \
	{ \
		setVariable(String(name), value); \
	} \
	SCRIPTEDCLASS_LOADSHAREDFUNCTIONS_HEADER(className) \
	{ \
		SCRIPTEDCLASS_LOADSHAREDFUNCTIONS_BODY(className); \
	}



#define SCRIPTEDCLASS_FUNCTION_DEFINE(returnType, className, functionName, expressionLeft, expressionRight, args, ...) \
	returnType SCRIPTEDCLASS_CLASSNAME(className)::base_##functionName ( SCRIPTEDCLASS_CLASSNAME(className) *scriptObj, ##__VA_ARGS__) \
	{ \
		expressionLeft scriptObj->className::functionName(args); \
	} \
	returnType SCRIPTEDCLASS_CLASSNAME(className)::functionName(__VA_ARGS__) \
	{ \
		SCRIPTEDCLASS_FUNCTION_CALL(expressionLeft, functionName, args); \
		expressionLeft expressionRight; \
	}



#define SCRIPTEDCLASS_NEWFUNCTION_BODY(className, ...) \
	SCRIPTEDCLASS_CLASSNAME(className)* scriptObj = new SCRIPTEDCLASS_CLASSNAME(className)(scriptData, ##__VA_ARGS__); \
	if(!scriptObj->usable) \
	{ \
		return NULL; \
	} \
	return (SCRIPTEDCLASS_CLASSNAME(className)*)scriptObj->callFunction(String("constructor"), args).get_ptr();



#define SCRIPTEDCLASS_DELETEFUNCTION_BODY(className) delete scriptObj;



#define SCRIPTEDCLASS_PROTECTEDMODULE_ADD(module, className, memberName, typecast) \
	module->add(chaiscript::fun(typecast &SCRIPTEDCLASS_CLASSNAME(className)::memberName), #memberName);



#define SCRIPTEDCLASS_PROTECTEDMODULE_ADDSTATIC(module, className, memberName, typecast) \
	module->add(chaiscript::fun(typecast &SCRIPTEDCLASS_CLASSNAME(className)::memberName), #className "_" #memberName);

#endif //SMASHBROS_SCRIPT_DISABLE
