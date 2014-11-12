
#ifndef SMASHBROS_SCRIPT_DISABLE

#include "lib_GameEngine.h"

namespace GameEngine
{
	chaiscript::ModulePtr load_module_GameEngine_Graphics()
	{
		chaiscript::Module* m_gameengine_graphics = new chaiscript::Module();

		m_gameengine_graphics->add(chaiscript::constructor<GameEngine::Graphics2D(const GameEngine::Graphics2D&)>(), "Graphics2D");
		m_gameengine_graphics->add(chaiscript::fun(&GameEngine::Graphics2D::create), "create");
		m_gameengine_graphics->add(chaiscript::fun((void(GameEngine::Graphics2D::*)(float)) &GameEngine::Graphics2D::setRotation), "setRotation");
		m_gameengine_graphics->add(chaiscript::fun((void(GameEngine::Graphics2D::*)(float,float,float)) &GameEngine::Graphics2D::setRotation), "setRotation");
		m_gameengine_graphics->add(chaiscript::fun(&GameEngine::Graphics2D::getRotation), "getRotation");
		m_gameengine_graphics->add(chaiscript::fun((void(GameEngine::Graphics2D::*)(float)) &GameEngine::Graphics2D::rotate), "rotate");
		m_gameengine_graphics->add(chaiscript::fun((void(GameEngine::Graphics2D::*)(float, float, float)) &GameEngine::Graphics2D::rotate), "rotate");
		m_gameengine_graphics->add(chaiscript::fun(&GameEngine::Graphics2D::setScale), "setScale");
		m_gameengine_graphics->add(chaiscript::fun(&GameEngine::Graphics2D::scale), "scale");
		m_gameengine_graphics->add(chaiscript::fun(&GameEngine::Graphics2D::getScale), "getScale");
		m_gameengine_graphics->add(chaiscript::fun(&GameEngine::Graphics2D::setTranslation), "setTranslation");
		m_gameengine_graphics->add(chaiscript::fun(&GameEngine::Graphics2D::translate), "translate");
		m_gameengine_graphics->add(chaiscript::fun(&GameEngine::Graphics2D::setColor), "setColor");
		m_gameengine_graphics->add(chaiscript::fun(&GameEngine::Graphics2D::getColor), "getColor");
		m_gameengine_graphics->add(chaiscript::fun(&GameEngine::Graphics2D::setAlpha), "setAlpha");
		m_gameengine_graphics->add(chaiscript::fun(&GameEngine::Graphics2D::getAlpha), "getAlpha");
		m_gameengine_graphics->add(chaiscript::fun(&GameEngine::Graphics2D::setFont), "setFont");
		m_gameengine_graphics->add(chaiscript::fun(&GameEngine::Graphics2D::getFont), "getFont");
		m_gameengine_graphics->add(chaiscript::fun(&GameEngine::Graphics2D::getDefaultFont), "getDefaultFont");
		m_gameengine_graphics->add(chaiscript::fun(&GameEngine::Graphics2D::drawString), "drawString");
		m_gameengine_graphics->add(chaiscript::fun(&GameEngine::Graphics2D::drawLine), "drawLine");
		m_gameengine_graphics->add(chaiscript::fun(&GameEngine::Graphics2D::drawRect), "drawRect");
		m_gameengine_graphics->add(chaiscript::fun(&GameEngine::Graphics2D::fillRect), "fillRect");
		m_gameengine_graphics->add(chaiscript::fun(&GameEngine::Graphics2D::drawOval), "drawOval");
		m_gameengine_graphics->add(chaiscript::fun(&GameEngine::Graphics2D::fillOval), "fillOval");
		m_gameengine_graphics->add(chaiscript::fun((void(GameEngine::Graphics2D::*)(GameEngine::BufferedImage*,float,float)) &GameEngine::Graphics2D::drawImage), "drawImage");
		m_gameengine_graphics->add(chaiscript::fun((void(GameEngine::Graphics2D::*)(GameEngine::BufferedImage*,float,float,float,float)) &GameEngine::Graphics2D::drawImage), "drawImage");
		m_gameengine_graphics->add(chaiscript::fun((void(GameEngine::Graphics2D::*)(GameEngine::BufferedImage*,float,float,float,float,int,int,int,int)) &GameEngine::Graphics2D::drawImage), "drawImage");

		return chaiscript::ModulePtr(m_gameengine_graphics);
	}
}

#endif //SMASHBROS_SCRIPT_DISABLE
