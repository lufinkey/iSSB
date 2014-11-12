
#ifndef SMASHBROS_SCRIPT_DISABLE

#include "lib_GameEngine.h"

namespace GameEngine
{
	chaiscript::ModulePtr load_module_GameEngine_ScreenManager()
	{
		chaiscript::Module* m_gameengine_screenmanager = new chaiscript::Module();

		m_gameengine_screenmanager->add(chaiscript::fun(&GameEngine::ScreenManager::Add), "ScreenManager_Add");
		m_gameengine_screenmanager->add(chaiscript::fun(&GameEngine::ScreenManager::Remove), "ScreenManager_Remove");
		m_gameengine_screenmanager->add(chaiscript::fun(&GameEngine::ScreenManager::GoToScreen), "ScreenManager_GoToScreen");
		m_gameengine_screenmanager->add(chaiscript::fun(&GameEngine::ScreenManager::Update), "ScreenManager_Update");
		m_gameengine_screenmanager->add(chaiscript::fun(&GameEngine::ScreenManager::Draw), "ScreenManager_Draw");

		m_gameengine_screenmanager->add(chaiscript::fun(&GameEngine::Screen::Initialize), "Initialize");
		m_gameengine_screenmanager->add(chaiscript::fun(&GameEngine::Screen::LoadContent), "LoadContent");
		m_gameengine_screenmanager->add(chaiscript::fun(&GameEngine::Screen::UnloadContent), "UnloadContent");
		m_gameengine_screenmanager->add(chaiscript::fun(&GameEngine::Screen::Update), "Update");
		m_gameengine_screenmanager->add(chaiscript::fun(&GameEngine::Screen::Draw), "Draw");

		m_gameengine_screenmanager->add(chaiscript::fun(&GameEngine::MenuScreen::Update), "Update");
		m_gameengine_screenmanager->add(chaiscript::fun(&GameEngine::MenuScreen::Draw), "Draw");
		m_gameengine_screenmanager->add(chaiscript::fun((void(GameEngine::MenuScreen::*)(float,float,GameEngine::Animation*,GameEngine::Animation*,const GameEngine::String&)) &GameEngine::MenuScreen::addItem), "addItem");
		m_gameengine_screenmanager->add(chaiscript::fun((void(GameEngine::MenuScreen::*)(float,float,GameEngine::Animation*,GameEngine::Animation*,GameEngine::Animation*,const GameEngine::String&)) &GameEngine::MenuScreen::addItem), "addItem");
		m_gameengine_screenmanager->add(chaiscript::fun((void(GameEngine::MenuScreen::*)(float,float,GameEngine::Animation*,const GameEngine::Color&,const GameEngine::String&)) &GameEngine::MenuScreen::addItem), "addItem");
		m_gameengine_screenmanager->add(chaiscript::fun((void(GameEngine::MenuScreen::*)(float,float,GameEngine::Animation*,const GameEngine::Color&,const GameEngine::Color&,const GameEngine::String&)) &GameEngine::MenuScreen::addItem), "addItem");
		m_gameengine_screenmanager->add(chaiscript::fun((void(GameEngine::MenuScreen::*)(float,float,const GameEngine::String&,const GameEngine::String&,const GameEngine::String&)) &GameEngine::MenuScreen::addItem), "addItem");
		m_gameengine_screenmanager->add(chaiscript::fun((void(GameEngine::MenuScreen::*)(float,float,const GameEngine::String&,const GameEngine::String&,const GameEngine::String&,const GameEngine::String&)) &GameEngine::MenuScreen::addItem), "addItem");
		m_gameengine_screenmanager->add(chaiscript::fun((void(GameEngine::MenuScreen::*)(float,float,const GameEngine::String&,const GameEngine::Color&,const GameEngine::String&)) &GameEngine::MenuScreen::addItem), "addItem");
		m_gameengine_screenmanager->add(chaiscript::fun((void(GameEngine::MenuScreen::*)(float,float,const GameEngine::String&,const GameEngine::Color&,const GameEngine::Color&,const GameEngine::String&)) &GameEngine::MenuScreen::addItem), "addItem");
		m_gameengine_screenmanager->add(chaiscript::fun((void(GameEngine::MenuScreen::*)(float,float,const GameEngine::String&,GameEngine::Font*,const GameEngine::Color&,const GameEngine::Color&,const GameEngine::String&)) &GameEngine::MenuScreen::addItem), "addItem");
		m_gameengine_screenmanager->add(chaiscript::fun((void(GameEngine::MenuScreen::*)(float,float,const GameEngine::String&,GameEngine::Font*,const GameEngine::Color&,const GameEngine::Color&,const GameEngine::Color&,const GameEngine::String&)) &GameEngine::MenuScreen::addItem), "addItem");
		m_gameengine_screenmanager->add(chaiscript::fun(&GameEngine::MenuScreen::setItemScale), "setItemScale");
		m_gameengine_screenmanager->add(chaiscript::fun(&GameEngine::MenuScreen::setItemRotation), "setItemRotation");
		m_gameengine_screenmanager->add(chaiscript::fun(&GameEngine::MenuScreen::setItemColor), "setItemColor");

		return chaiscript::ModulePtr(m_gameengine_screenmanager);
	}
}

#endif //SMASHBROS_SCRIPT_DISABLE
