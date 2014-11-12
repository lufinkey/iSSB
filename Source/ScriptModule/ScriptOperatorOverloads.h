
#ifndef SMASHBROS_SCRIPT_DISABLE

#include <chaiscript/chaiscript.hpp>
#include "../GameEngine/GameEngine.h"

#pragma once

bool operator==(const chaiscript::Boxed_Value&val, const chaiscript::Boxed_Value&cmp);
bool operator!=(const chaiscript::Boxed_Value&val, const chaiscript::Boxed_Value&cmp);
//bool operator==(const GameEngine::String&val, const chaiscript::Boxed_Value&cmp);
//bool operator==(const GameEngine::Vector2<chaiscript::Boxed_Value>&val, const chaiscript::Boxed_Value&cmp);
chaiscript::Boxed_Value operator+(const chaiscript::Boxed_Value&val1, const chaiscript::Boxed_Value&val2);
chaiscript::Boxed_Value operator-(const chaiscript::Boxed_Value&val1, const chaiscript::Boxed_Value&val2);
chaiscript::Boxed_Value operator*(const chaiscript::Boxed_Value&val1, const chaiscript::Boxed_Value&val2);
chaiscript::Boxed_Value operator/(const chaiscript::Boxed_Value&val1, const chaiscript::Boxed_Value&val2);
chaiscript::Boxed_Value& operator+=(chaiscript::Boxed_Value&val1, const chaiscript::Boxed_Value&val2);
chaiscript::Boxed_Value& operator-=(chaiscript::Boxed_Value&val1, const chaiscript::Boxed_Value&val2);
chaiscript::Boxed_Value& operator*=(chaiscript::Boxed_Value&val1, const chaiscript::Boxed_Value&val2);
chaiscript::Boxed_Value& operator/=(chaiscript::Boxed_Value&val1, const chaiscript::Boxed_Value&val2);

#endif //SMASHBROS_SCRIPT_DISABLE
