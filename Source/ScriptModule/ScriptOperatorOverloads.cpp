
#ifndef SMASHBROS_SCRIPT_DISABLE

#include "ScriptOperatorOverloads.h"

bool operator==(const chaiscript::Boxed_Value&val, const chaiscript::Boxed_Value&cmp)
{
	if (chaiscript::Boxed_Number(val) == chaiscript::Boxed_Number(cmp))
	{
		return true;
	}
	return false;
}

bool operator!=(const chaiscript::Boxed_Value&val, const chaiscript::Boxed_Value&cmp)
{
	if (chaiscript::Boxed_Number(val) != chaiscript::Boxed_Number(cmp))
	{
		return true;
	}
	return false;
}

/*bool operator==(const GameEngine::String&val, const chaiscript::Boxed_Value&cmp)
{
	if (val.equals(chaiscript::boxed_cast<const String&>(cmp)))
	{
		return true;
	}
	return false;
}

bool operator==(const GameEngine::Vector2<chaiscript::Boxed_Value>&val, const chaiscript::Boxed_Value&cmp)
{
	const GameEngine::Vector2<chaiscript::Boxed_Value>& cmpVal = chaiscript::boxed_cast<const GameEngine::Vector2<chaiscript::Boxed_Value>&>(cmp);
	if (val.equals(cmpVal))
	{
		return true;
	}
	return false;
}*/

chaiscript::Boxed_Value operator+(const chaiscript::Boxed_Value&val1, const chaiscript::Boxed_Value&val2)
{
	return chaiscript::Boxed_Value(chaiscript::Boxed_Number(val1) + chaiscript::Boxed_Value(val2));
}

chaiscript::Boxed_Value operator-(const chaiscript::Boxed_Value&val1, const chaiscript::Boxed_Value&val2)
{
	return chaiscript::Boxed_Value(chaiscript::Boxed_Number(val1) - chaiscript::Boxed_Number(val2));
}

chaiscript::Boxed_Value operator*(const chaiscript::Boxed_Value&val1, const chaiscript::Boxed_Value&val2)
{
	return chaiscript::Boxed_Value(chaiscript::Boxed_Number(val1) * chaiscript::Boxed_Value(val2));
}

chaiscript::Boxed_Value operator/(const chaiscript::Boxed_Value&val1, const chaiscript::Boxed_Value&val2)
{
	return chaiscript::Boxed_Value(chaiscript::Boxed_Number(val1) / chaiscript::Boxed_Number(val2));
}

chaiscript::Boxed_Value& operator+=(chaiscript::Boxed_Value&val1, const chaiscript::Boxed_Value&val2)
{
	chaiscript::Boxed_Number num1(val1);
	num1 += chaiscript::Boxed_Number(val2);
	return val1;
}

chaiscript::Boxed_Value& operator-=(chaiscript::Boxed_Value&val1, const chaiscript::Boxed_Value&val2)
{
	chaiscript::Boxed_Number num1(val1);
	num1 -= chaiscript::Boxed_Number(val2);
	return val1;
}

chaiscript::Boxed_Value& operator*=(chaiscript::Boxed_Value&val1, const chaiscript::Boxed_Value&val2)
{
	chaiscript::Boxed_Number num1(val1);
	num1 *= chaiscript::Boxed_Number(val2);
	return val1;
}

chaiscript::Boxed_Value& operator/=(chaiscript::Boxed_Value&val1, const chaiscript::Boxed_Value&val2)
{
	chaiscript::Boxed_Number num1(val1);
	num1 /= chaiscript::Boxed_Number(val2);
	return val1;
}

#endif //SMASHBROS_SCRIPT_DISABLE
