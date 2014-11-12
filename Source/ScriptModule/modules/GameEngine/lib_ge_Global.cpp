
#ifndef SMASHBROS_SCRIPT_DISABLE

#include "lib_GameEngine.h"

#include "../../ScriptOperatorOverloads.h"

namespace GameEngine
{
	float View_getX()
	{
		return View::x;
	}

	float View_getY()
	{
		return View::y;
	}

	float View_getZoom()
	{
		return View::Zoom;
	}

	void View_setX(float x)
	{
		View::x = x;
	}

	void View_setY(float y)
	{
		View::y = y;
	}

	void View_setZoom(float zoom)
	{
		View::Zoom = zoom;
	}


	chaiscript::ModulePtr load_module_GameEngine_Global()
	{
		chaiscript::Module* m_gameengine_global = new chaiscript::Module();

		//Application
		m_gameengine_global->add(chaiscript::fun(&GameEngine::Application::Exit), "Application_Exit");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::Application::GetLastKey), "Application_GetLastKey");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::Application::KeyPressed), "Application_KeyPressed");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::Application::PrevKeyPressed), "Application_PrevKeyPressed");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::Application::MouseState), "Application_MouseState");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::Application::PrevMouseState), "Application_PrevMouseState");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::Application::MouseX), "Application_MouseX");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::Application::MouseY), "Application_MouseY");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::Application::PrevMouseX), "Application_PrevMouseX");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::Application::PrevMouseY), "Application_PrevMouseY");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::Application::setWindowTitle), "Application_setWindowTitle");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::Application::setUpdatesPerFrame), "Application_setUpdatesPerFrame");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::Application::getFrame), "Application_getFrame");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::Application::setFPS), "Application_setFPS");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::Application::showRealFPS), "Application_showRealFPS");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::Application::getGameTime), "Application_getGameTime");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::Application::getSystemTime), "Application_getSystemTime");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::Application::Suspend), "Application_Suspend");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::Application::Resume), "Application_Resume");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::Application::showBackground), "Application_showBackground");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::Application::setBackgroundImage), "Application_setBackgroundImage");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::Application::setFullScreen), "Application_setFullScreen");



		//AssetManager
		m_gameengine_global->add(chaiscript::fun(&GameEngine::AssetManager::loadStringFromFile), "AssetManager_loadStringFromFile");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::AssetManager::loadImage), "AssetManager_loadImage");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::AssetManager::getImage), "AssetManager_getImage");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::AssetManager::unloadImage), "AssetManager_unloadImage");
		m_gameengine_global->add(chaiscript::fun((bool(*)(const GameEngine::String&)) &GameEngine::AssetManager::loadFont), "AssetManager_loadFont");
		m_gameengine_global->add(chaiscript::fun((bool(*)(const GameEngine::String&, int)) &GameEngine::AssetManager::loadFont), "AssetManager_loadFont");
		m_gameengine_global->add(chaiscript::fun((bool(*)(const GameEngine::String&, int, int)) &GameEngine::AssetManager::loadFont), "AssetManager_loadFont");
		m_gameengine_global->add(chaiscript::fun((GameEngine::Font*(*)(const GameEngine::String&)) &GameEngine::AssetManager::getFont), "AssetManager_getFont");
		m_gameengine_global->add(chaiscript::fun((GameEngine::Font*(*)(const GameEngine::String&, int, int)) &GameEngine::AssetManager::getFont), "AssetManager_getFont");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::AssetManager::unloadFont), "AssetManager_unloadFont");



		//Rect
		m_gameengine_global->add(chaiscript::constructor<GameEngine::Rect()>(), "Rect");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::Rect::left), "left");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::Rect::top), "top");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::Rect::right), "right");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::Rect::bottom), "bottom");



		//RectF
		m_gameengine_global->add(chaiscript::constructor<GameEngine::RectF()>(), "RectF");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::RectF::left), "left");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::RectF::top), "top");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::RectF::right), "right");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::RectF::bottom), "bottom");



		//Rectangle
		m_gameengine_global->add(chaiscript::constructor<GameEngine::Rectangle()>(), "Rectangle");
		m_gameengine_global->add(chaiscript::constructor<GameEngine::Rectangle(int, int, int, int)>(), "Rectangle");
		m_gameengine_global->add(chaiscript::constructor<GameEngine::Rectangle(const GameEngine::Rectangle&)>(), "Rectangle");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::Rectangle::x), "x");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::Rectangle::y), "y");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::Rectangle::width), "width");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::Rectangle::height), "height");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::Rectangle::operator=), "=");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::Rectangle::operator-), "-");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::Rectangle::operator-=), "-=");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::Rectangle::equals), "equals");
		m_gameengine_global->add(chaiscript::fun((void(GameEngine::Rectangle::*)(int))&GameEngine::Rectangle::expand), "expand");
		m_gameengine_global->add(chaiscript::fun((void(GameEngine::Rectangle::*)(int, const GameEngine::Rectangle&))&GameEngine::Rectangle::expand), "expand");



		//RectangleF
		m_gameengine_global->add(chaiscript::constructor<GameEngine::RectangleF()>(), "RectangleF");
		m_gameengine_global->add(chaiscript::constructor<GameEngine::RectangleF(float, float, float, float)>(), "RectangleF");
		m_gameengine_global->add(chaiscript::constructor<GameEngine::RectangleF(const GameEngine::RectangleF&)>(), "RectangleF");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::RectangleF::x), "x");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::RectangleF::y), "y");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::RectangleF::width), "width");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::RectangleF::height), "height");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::RectangleF::operator=), "=");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::RectangleF::operator-), "-");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::RectangleF::operator-=), "-=");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::RectangleF::equals), "equals");
		m_gameengine_global->add(chaiscript::fun((void(GameEngine::RectangleF::*)(float))&GameEngine::RectangleF::expand), "expand");
		m_gameengine_global->add(chaiscript::fun((void(GameEngine::RectangleF::*)(float, const GameEngine::RectangleF&))&GameEngine::RectangleF::expand), "expand");



		//View
		m_gameengine_global->add(chaiscript::fun(&GameEngine::View_getX), "View_getX");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::View_getY), "View_getY");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::View_getZoom), "View_getZoom");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::View_setX), "View_setX");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::View_setY), "View_setY");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::View_setZoom), "View_setZoom");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::View::setSize), "View_setSize");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::View::Width), "View_getWidth");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::View::Height), "View_getHeight");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::View::ScaleWidth), "View_getScaleWidth");
		m_gameengine_global->add(chaiscript::fun(&GameEngine::View::ScaleHeight), "View_getScaleHeight");

		return chaiscript::ModulePtr(m_gameengine_global);
	}
}

#endif //SMASHBROS_SCRIPT_DISABLE
