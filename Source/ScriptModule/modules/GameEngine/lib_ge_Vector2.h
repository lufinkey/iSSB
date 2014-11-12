
#ifndef SMASHBROS_SCRIPT_DISABLE

#include <chaiscript/chaiscript.hpp>
#include <SFML/System/Vector2.hpp>
#include "lib_GameEngine.h"

#pragma once

namespace GameEngine
{
	template<typename T>
	void load_module_GameEngine_sfVector2(chaiscript::Module*& module, const char* typeName)
	{
		module->add(chaiscript::constructor<sf::Vector2<T>(void)>(), typeName);
		module->add(chaiscript::constructor<sf::Vector2<T>(const T&, const T&)>(), typeName);
		module->add(chaiscript::constructor<sf::Vector2<T>(const sf::Vector2<T>&)>(), typeName);

		module->add(chaiscript::fun(&sf::Vector2<T>::x), "x");
		module->add(chaiscript::fun(&sf::Vector2<T>::y), "y");
	}

	template<typename T>
	void load_module_GameEngine_Vector2(chaiscript::Module*& module, const char* typeName)
	{
		module->add(chaiscript::constructor<GameEngine::Vector2<T>()>(), typeName);
		module->add(chaiscript::constructor<GameEngine::Vector2<T>(const T&, const T&)>(), typeName);
		module->add(chaiscript::constructor<GameEngine::Vector2<T>(const GameEngine::Vector2<T>&)>(), typeName);
		module->add(chaiscript::constructor<GameEngine::Vector2<T>(const sf::Vector2<T>&)>(), typeName);

		module->add(chaiscript::fun(&Vector2<T>::x), "x");
		module->add(chaiscript::fun(&Vector2<T>::y), "y");

		module->add(chaiscript::fun((void(GameEngine::Vector2<T>::*)(const GameEngine::Vector2<T>&)) &GameEngine::Vector2<T>::operator=), "=");
		module->add(chaiscript::fun((void(GameEngine::Vector2<T>::*)(const sf::Vector2<T>&)) &GameEngine::Vector2<T>::operator=), "=");

		module->add(chaiscript::fun((GameEngine::Vector2<T>(GameEngine::Vector2<T>::*)(const GameEngine::Vector2<T>&)const) &GameEngine::Vector2<T>::operator+), "+");
		module->add(chaiscript::fun((GameEngine::Vector2<T>(GameEngine::Vector2<T>::*)(const sf::Vector2<T>&)const) &GameEngine::Vector2<T>::operator+), "+");

		module->add(chaiscript::fun((GameEngine::Vector2<T>(GameEngine::Vector2<T>::*)(const GameEngine::Vector2<T>&)const) &GameEngine::Vector2<T>::operator-), "-");
		module->add(chaiscript::fun((GameEngine::Vector2<T>(GameEngine::Vector2<T>::*)(const sf::Vector2<T>&)const) &GameEngine::Vector2<T>::operator-), "-");

		module->add(chaiscript::fun((GameEngine::Vector2<T>(GameEngine::Vector2<T>::*)(const GameEngine::Vector2<T>&)const) &GameEngine::Vector2<T>::operator*), "*");
		module->add(chaiscript::fun((GameEngine::Vector2<T>(GameEngine::Vector2<T>::*)(const sf::Vector2<T>&)const) &GameEngine::Vector2<T>::operator*), "*");
	
		module->add(chaiscript::fun((GameEngine::Vector2<T>(GameEngine::Vector2<T>::*)(const GameEngine::Vector2<T>&)const) &GameEngine::Vector2<T>::operator/), "/");
		module->add(chaiscript::fun((GameEngine::Vector2<T>(GameEngine::Vector2<T>::*)(const sf::Vector2<T>&)const) &GameEngine::Vector2<T>::operator/), "/");

		module->add(chaiscript::fun((GameEngine::Vector2<T>&(GameEngine::Vector2<T>::*)(const GameEngine::Vector2<T>&)) &GameEngine::Vector2<T>::operator+=), "+=");
		module->add(chaiscript::fun((GameEngine::Vector2<T>&(GameEngine::Vector2<T>::*)(const sf::Vector2<T>&)) &GameEngine::Vector2<T>::operator+=), "+=");

		module->add(chaiscript::fun((GameEngine::Vector2<T>&(GameEngine::Vector2<T>::*)(const GameEngine::Vector2<T>&)) &GameEngine::Vector2<T>::operator-=), "-=");
		module->add(chaiscript::fun((GameEngine::Vector2<T>&(GameEngine::Vector2<T>::*)(const sf::Vector2<T>&)) &GameEngine::Vector2<T>::operator-=), "-=");

		module->add(chaiscript::fun((GameEngine::Vector2<T>&(GameEngine::Vector2<T>::*)(const GameEngine::Vector2<T>&)) &GameEngine::Vector2<T>::operator*=), "*=");
		module->add(chaiscript::fun((GameEngine::Vector2<T>&(GameEngine::Vector2<T>::*)(const sf::Vector2<T>&)) &GameEngine::Vector2<T>::operator*=), "*=");

		module->add(chaiscript::fun((GameEngine::Vector2<T>&(GameEngine::Vector2<T>::*)(const GameEngine::Vector2<T>&)) &GameEngine::Vector2<T>::operator/=), "/=");
		module->add(chaiscript::fun((GameEngine::Vector2<T>&(GameEngine::Vector2<T>::*)(const sf::Vector2<T>&)) &GameEngine::Vector2<T>::operator/=), "/=");

		module->add(chaiscript::fun((bool(GameEngine::Vector2<T>::*)(const GameEngine::Vector2<T>&) const) &GameEngine::Vector2<T>::operator==), "==");
		module->add(chaiscript::fun((bool(GameEngine::Vector2<T>::*)(const sf::Vector2<T>&) const) &GameEngine::Vector2<T>::operator==), "==");

		module->add(chaiscript::fun((bool(GameEngine::Vector2<T>::*)(const GameEngine::Vector2<T>&) const) &GameEngine::Vector2<T>::operator!=), "!=");
		module->add(chaiscript::fun((bool(GameEngine::Vector2<T>::*)(const sf::Vector2<T>&) const) &GameEngine::Vector2<T>::operator!=), "!=");

		module->add(chaiscript::fun((bool(GameEngine::Vector2<T>::*)(const GameEngine::Vector2<T>&) const) &GameEngine::Vector2<T>::equals), "equals");
		module->add(chaiscript::fun((bool(GameEngine::Vector2<T>::*)(const sf::Vector2<T>&) const) &GameEngine::Vector2<T>::equals), "equals");
	}
}

#endif //SMASHBROS_SCRIPT_DISABLE
