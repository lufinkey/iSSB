
#ifndef SMASHBROS_SCRIPT_DISABLE

#include "lib_GameEngine.h"

#include "lib_ge_Thread.h"

#include "../../ScriptMacros.h"
#include "inherit/lib_ge_inherit_Actor.h"
#include "inherit/lib_ge_inherit_TextActor.h"
#include "inherit/lib_ge_inherit_WireframeActor.h"

namespace GameEngine
{
	String stdstringToString(const std::string& str)
	{
		return String(str);
	}

	chaiscript::ModulePtr load_module_GameEngine()
	{
		chaiscript::Module* m_gameengine = new chaiscript::Module();

		m_gameengine->add(load_module_GameEngine_types());
		m_gameengine->add(load_module_GameEngine_Actor());
		m_gameengine->add(load_module_GameEngine_Global());
		m_gameengine->add(load_module_GameEngine_Graphics());
		m_gameengine->add(load_module_GameEngine_IO());
		m_gameengine->add(load_module_GameEngine_Math());
		m_gameengine->add(load_module_GameEngine_ScreenManager());
		m_gameengine->add(load_module_GameEngine_Util());

		return chaiscript::ModulePtr(m_gameengine);
	}

	chaiscript::ModulePtr load_module_GameEngine_types()
	{
		chaiscript::Module* m_gameengine_types = new chaiscript::Module();

		//classes
		m_gameengine_types->add(chaiscript::user_type<GameEngine::PrimitiveActor>(), "PrimitiveActor");
		m_gameengine_types->add(chaiscript::user_type<GameEngine::Actor>(), "Actor");
		m_gameengine_types->add(chaiscript::user_type<GameEngine::TextActor>(), "TextActor");
		m_gameengine_types->add(chaiscript::user_type<GameEngine::WireframeActor>(), "WireframeActor");
		m_gameengine_types->add(chaiscript::user_type<GameEngine::Animation>(), "Animation");
		m_gameengine_types->add(chaiscript::base_class<GameEngine::PrimitiveActor, Actor>());
		m_gameengine_types->add(chaiscript::base_class<GameEngine::PrimitiveActor, TextActor>());
		m_gameengine_types->add(chaiscript::base_class<GameEngine::PrimitiveActor, WireframeActor>());

		m_gameengine_types->add(chaiscript::user_type<GameEngine::Graphics2D>(), "Graphics2D");

		m_gameengine_types->add(chaiscript::user_type<GameEngine::Screen>(), "Screen");
		m_gameengine_types->add(chaiscript::user_type<GameEngine::MenuScreen>(), "MenuScreen");
		m_gameengine_types->add(chaiscript::base_class<GameEngine::Screen, GameEngine::MenuScreen>());

		m_gameengine_types->add(chaiscript::user_type<GameEngine::ArrayList<chaiscript::Boxed_Value>>(), "ArrayList");
		m_gameengine_types->add(chaiscript::user_type<GameEngine::BufferedImage>(), "BufferedImage");
		m_gameengine_types->add(chaiscript::user_type<GameEngine::Color>(), "Color");
		m_gameengine_types->add(chaiscript::user_type<GameEngine::Font>(), "Font");
		m_gameengine_types->add(chaiscript::user_type<GameEngine::PixelIterator>(), "PixelIterator");
		m_gameengine_types->add(chaiscript::user_type<GameEngine::PrefManager>(), "PrefManager");
		m_gameengine_types->add(chaiscript::user_type<GameEngine::String>(), "String");
		m_gameengine_types->add(chaiscript::type_conversion<std::string, GameEngine::String>(&stdstringToString));
		m_gameengine_types->add(chaiscript::user_type<GameEngine::ScriptThread>(), "Thread");

		m_gameengine_types->add(chaiscript::user_type<GameEngine::Vector2<chaiscript::Boxed_Value>>(), "Vector2");
		m_gameengine_types->add(chaiscript::user_type<GameEngine::Rect>(), "Rect");
		m_gameengine_types->add(chaiscript::user_type<GameEngine::RectF>(), "RectF");
		m_gameengine_types->add(chaiscript::user_type<GameEngine::Rectangle>(), "Rectangle");
		m_gameengine_types->add(chaiscript::user_type<GameEngine::RectangleF>(), "RectangleF");

		//scripted classes
		SCRIPTMGR_ADDSCRIPTEDCLASSINHERITENCE(m_gameengine_types, GameEngine, Actor)
		SCRIPTMGR_ADDSCRIPTEDCLASSINHERITENCE(m_gameengine_types, GameEngine, TextActor)
		SCRIPTMGR_ADDSCRIPTEDCLASSINHERITENCE(m_gameengine_types, GameEngine, WireframeActor)
		SCRIPTMGR_ADDSHAREDFUNCTIONS(m_gameengine_types, Actor)
		SCRIPTMGR_ADDSHAREDFUNCTIONS(m_gameengine_types, TextActor)
		SCRIPTMGR_ADDSHAREDFUNCTIONS(m_gameengine_types, WireframeActor)

		return chaiscript::ModulePtr(m_gameengine_types);
	}
}

#endif //SMASHBROS_SCRIPT_DISABLE
