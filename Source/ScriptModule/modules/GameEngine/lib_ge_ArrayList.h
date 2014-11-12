
#ifndef SMASHBROS_SCRIPT_DISABLE

#include <chaiscript/chaiscript.hpp>
#include "lib_GameEngine.h"

#pragma once

namespace GameEngine
{
	template<typename T>
	void load_module_GameEngine_ArrayList(chaiscript::Module*& module, const char*typeName)
	{
		module->add(chaiscript::constructor<GameEngine::ArrayList<T>()>(), typeName);
		module->add(chaiscript::constructor<GameEngine::ArrayList<T>(const GameEngine::ArrayList<T>&)>(), typeName);
		module->add(chaiscript::constructor<GameEngine::ArrayList<T>(int)>(), typeName);

		module->add(chaiscript::fun((const T&(GameEngine::ArrayList<T>::*)(int) const) &GameEngine::ArrayList<T>::get), "get");
		module->add(chaiscript::fun((T&(GameEngine::ArrayList<T>::*)(int))&GameEngine::ArrayList<T>::get), "get");
		module->add(chaiscript::fun((const T&(GameEngine::ArrayList<T>::*)(int) const) &ArrayList<T>::operator[]), "[]");
		module->add(chaiscript::fun((T&(GameEngine::ArrayList<T>::*)(int)) &GameEngine::ArrayList<T>::operator[]), "[]");
		module->add(chaiscript::fun(&GameEngine::ArrayList<T>::set), "set");
		module->add(chaiscript::fun((void(GameEngine::ArrayList<T>::*)(const T&)) &GameEngine::ArrayList<T>::add), "add");
		module->add(chaiscript::fun((void(GameEngine::ArrayList<T>::*)(int, const T&)) &GameEngine::ArrayList<T>::add), "add");
		module->add(chaiscript::fun(&GameEngine::ArrayList<T>::remove), "remove");
		module->add(chaiscript::fun(&GameEngine::ArrayList<T>::clear), "clear");
		module->add(chaiscript::fun(&GameEngine::ArrayList<T>::size), "size");
		module->add(chaiscript::fun(&GameEngine::ArrayList<T>::operator=), "=");
		module->add(chaiscript::fun(&GameEngine::ArrayList<T>::contains), "contains");
	}
}

#endif //SMASHBROS_SCRIPT_DISABLE
