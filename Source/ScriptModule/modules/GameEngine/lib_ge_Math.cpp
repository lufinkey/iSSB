
#ifndef SMASHBROS_SCRIPT_DISABLE

#include "lib_GameEngine.h"

#include <math.h>

namespace GameEngine
{
	chaiscript::ModulePtr load_module_GameEngine_Math()
	{
		chaiscript::Module* m_gameengine_math = new chaiscript::Module();

		//constants
		m_gameengine_math->add_global_const(chaiscript::const_var(GameEngine::PI), "Math_PI");

		//Math
		m_gameengine_math->add(chaiscript::fun((int(*)(int)) &std::abs), "Math_abs");
		m_gameengine_math->add(chaiscript::fun((float(*)(float)) &std::abs), "Math_abs");
		m_gameengine_math->add(chaiscript::fun((double(*)(double)) &std::abs), "Math_abs");
		m_gameengine_math->add(chaiscript::fun((long double(*)(long double)) &std::abs), "Math_abs");
		m_gameengine_math->add(chaiscript::fun((long long(*)(long long)) &std::abs), "Math_abs");

		m_gameengine_math->add(chaiscript::fun((float(*)(float)) &std::acos), "Math_acos");
		m_gameengine_math->add(chaiscript::fun((double(*)(double)) &std::acos), "Math_acos");
		m_gameengine_math->add(chaiscript::fun((long double(*)(long double)) &std::acos), "Math_acos");
		m_gameengine_math->add(chaiscript::fun((float(*)(float)) &std::acosh), "Math_acosh");
		m_gameengine_math->add(chaiscript::fun((double(*)(double)) &std::acosh), "Math_acosh");
		m_gameengine_math->add(chaiscript::fun((long double(*)(long double)) &std::acosh), "Math_acosh");

		m_gameengine_math->add(chaiscript::fun((float(*)(float)) &std::asin), "Math_asin");
		m_gameengine_math->add(chaiscript::fun((double(*)(double)) &std::asin), "Math_asin");
		m_gameengine_math->add(chaiscript::fun((long double(*)(long double)) &std::asin), "Math_asin");
		m_gameengine_math->add(chaiscript::fun((float(*)(float)) &std::asinh), "Math_asinh");
		m_gameengine_math->add(chaiscript::fun((double(*)(double)) &std::asinh), "Math_asinh");
		m_gameengine_math->add(chaiscript::fun((long double(*)(long double)) &std::asinh), "Math_asinh");

		m_gameengine_math->add(chaiscript::fun((float(*)(float)) &std::atan), "Math_atan");
		m_gameengine_math->add(chaiscript::fun((double(*)(double)) &std::atan), "Math_atan");
		m_gameengine_math->add(chaiscript::fun((long double(*)(long double)) &std::atan), "Math_atan");
		m_gameengine_math->add(chaiscript::fun((float(*)(float)) &std::atanh), "Math_atanh");
		m_gameengine_math->add(chaiscript::fun((double(*)(double)) &std::atanh), "Math_atanh");
		m_gameengine_math->add(chaiscript::fun((long double(*)(long double)) &std::atanh), "Math_atanh");

		m_gameengine_math->add(chaiscript::fun((float(*)(float,float)) &std::atan2), "Math_atan2");
		m_gameengine_math->add(chaiscript::fun((double(*)(double,double)) &std::atan2), "Math_atan2");
		m_gameengine_math->add(chaiscript::fun((long double(*)(long double,long double)) &std::atan2), "Math_atan2");

		m_gameengine_math->add(chaiscript::fun(&std::atof), "Math_atof");
		m_gameengine_math->add(chaiscript::fun(&std::atoi), "Math_atoi");
		m_gameengine_math->add(chaiscript::fun(&std::atol), "Math_atol");
		m_gameengine_math->add(chaiscript::fun(&std::atoll), "Math_atoll");

		m_gameengine_math->add(chaiscript::fun((float(*)(float)) &std::cbrt), "Math_cbrt");
		m_gameengine_math->add(chaiscript::fun((double(*)(double)) &std::cbrt), "Math_cbrt");
		m_gameengine_math->add(chaiscript::fun((long double(*)(long double)) &std::cbrt), "Math_cbrt");

		m_gameengine_math->add(chaiscript::fun((float(*)(float)) &std::ceil), "Math_ceil");
		m_gameengine_math->add(chaiscript::fun((double(*)(double)) &std::ceil), "Math_ceil");
		m_gameengine_math->add(chaiscript::fun((long double(*)(long double)) &std::ceil), "Math_ceil");

		m_gameengine_math->add(chaiscript::fun((float(*)(float)) &std::cos), "Math_cos");
		m_gameengine_math->add(chaiscript::fun((double(*)(double)) &std::cos), "Math_cos");
		m_gameengine_math->add(chaiscript::fun((long double(*)(long double)) &std::cos), "Math_cos");
		m_gameengine_math->add(chaiscript::fun((float(*)(float)) &std::cosh), "Math_cosh");
		m_gameengine_math->add(chaiscript::fun((double(*)(double)) &std::cosh), "Math_cosh");
		m_gameengine_math->add(chaiscript::fun((long double(*)(long double)) &std::cosh), "Math_cosh");

		m_gameengine_math->add(chaiscript::fun((float(*)(float)) &std::exp), "Math_exp");
		m_gameengine_math->add(chaiscript::fun((double(*)(double)) &std::exp), "Math_exp");
		m_gameengine_math->add(chaiscript::fun((long double(*)(long double)) &std::exp), "Math_exp");

		m_gameengine_math->add(chaiscript::fun((float(*)(float)) &std::exp2), "Math_exp2");
		m_gameengine_math->add(chaiscript::fun((double(*)(double)) &std::exp2), "Math_exp2");
		m_gameengine_math->add(chaiscript::fun((long double(*)(long double)) &std::exp2), "Math_exp2");

		m_gameengine_math->add(chaiscript::fun((float(*)(float)) &std::expm1), "Math_expm1");
		m_gameengine_math->add(chaiscript::fun((double(*)(double)) &std::expm1), "Math_expm1");
		m_gameengine_math->add(chaiscript::fun((long double(*)(long double)) &std::expm1), "Math_expm1");

		m_gameengine_math->add(chaiscript::fun((float(*)(float)) &std::floor), "Math_floor");
		m_gameengine_math->add(chaiscript::fun((double(*)(double)) &std::floor), "Math_floor");
		m_gameengine_math->add(chaiscript::fun((long double(*)(long double)) &std::floor), "Math_floor");

		m_gameengine_math->add(chaiscript::fun((float(*)(float)) &std::log), "Math_log");
		m_gameengine_math->add(chaiscript::fun((double(*)(double)) &std::log), "Math_log");
		m_gameengine_math->add(chaiscript::fun((long double(*)(long double)) &std::log), "Math_log");

		m_gameengine_math->add(chaiscript::fun((float(*)(float)) &std::log2), "Math_log2");
		m_gameengine_math->add(chaiscript::fun((double(*)(double)) &std::log2), "Math_log2");
		m_gameengine_math->add(chaiscript::fun((long double(*)(long double)) &std::log2), "Math_log2");

		m_gameengine_math->add(chaiscript::fun((float(*)(float)) &std::log10), "Math_log10");
		m_gameengine_math->add(chaiscript::fun((double(*)(double)) &std::log10), "Math_log10");
		m_gameengine_math->add(chaiscript::fun((long double(*)(long double)) &std::log10), "Math_log10");

		m_gameengine_math->add(chaiscript::fun((float(*)(float,int)) &std::pow), "Math_pow");
		m_gameengine_math->add(chaiscript::fun((float(*)(float,float)) &std::pow), "Math_pow");
		m_gameengine_math->add(chaiscript::fun((double(*)(double,int)) &std::pow), "Math_pow");
		m_gameengine_math->add(chaiscript::fun((double(*)(double,double)) &std::pow), "Math_pow");
		m_gameengine_math->add(chaiscript::fun((long double(*)(long double,int)) &std::pow), "Math_pow");
		m_gameengine_math->add(chaiscript::fun((long double(*)(long double,long double)) &std::pow), "Math_pow");

		m_gameengine_math->add(chaiscript::fun((float(*)(float)) &std::round), "Math_round");
		m_gameengine_math->add(chaiscript::fun((double(*)(double)) &std::round), "Math_round");
		m_gameengine_math->add(chaiscript::fun((long double(*)(long double)) &std::round), "Math_round");

		m_gameengine_math->add(chaiscript::fun((float(*)(float)) &std::sin), "Math_sin");
		m_gameengine_math->add(chaiscript::fun((double(*)(double)) &std::sin), "Math_sin");
		m_gameengine_math->add(chaiscript::fun((long double(*)(long double)) &std::sin), "Math_sin");
		m_gameengine_math->add(chaiscript::fun((float(*)(float)) &std::sinh), "Math_sinh");
		m_gameengine_math->add(chaiscript::fun((double(*)(double)) &std::sinh), "Math_sinh");
		m_gameengine_math->add(chaiscript::fun((long double(*)(long double)) &std::sinh), "Math_sinh");

		m_gameengine_math->add(chaiscript::fun((float(*)(float)) &std::sqrt), "Math_sqrt");
		m_gameengine_math->add(chaiscript::fun((double(*)(double)) &std::sqrt), "Math_sqrt");
		m_gameengine_math->add(chaiscript::fun((long double(*)(long double)) &std::sqrt), "Math_sqrt");

		m_gameengine_math->add(chaiscript::fun((float(*)(float)) &std::tan), "Math_tan");
		m_gameengine_math->add(chaiscript::fun((double(*)(double)) &std::tan), "Math_tan");
		m_gameengine_math->add(chaiscript::fun((long double(*)(long double)) &std::tan), "Math_tan");
		m_gameengine_math->add(chaiscript::fun((float(*)(float)) &std::tanh), "Math_tanh");
		m_gameengine_math->add(chaiscript::fun((double(*)(double)) &std::tanh), "Math_tanh");
		m_gameengine_math->add(chaiscript::fun((long double(*)(long double)) &std::tanh), "Math_tanh");

		m_gameengine_math->add(chaiscript::fun(&GameEngine::random), "Math_random");
		m_gameengine_math->add(chaiscript::fun(&GameEngine::radtodeg), "Math_radtodeg");
		m_gameengine_math->add(chaiscript::fun(&GameEngine::degtorad), "Math_degtorad");

		m_gameengine_math->add(chaiscript::fun(&GameEngine::PrimitiveActor::distance), "Math_distance");
		m_gameengine_math->add(chaiscript::fun(&GameEngine::PrimitiveActor::distanceUnSqr), "Math_distanceUnSqr");
		m_gameengine_math->add(chaiscript::fun(&GameEngine::PrimitiveActor::direction), "Math_direction");
		m_gameengine_math->add(chaiscript::fun(&GameEngine::PrimitiveActor::correctDegrees), "Math_correctDegrees");

		return chaiscript::ModulePtr(m_gameengine_math);
	}
}

#endif //SMASHBROS_SCRIPT_DISABLE
