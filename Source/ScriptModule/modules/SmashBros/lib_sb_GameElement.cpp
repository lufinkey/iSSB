
#ifndef SMASHBROS_SCRIPT_DISABLE

#include "lib_smashbros.h"

#include "../../../SmashBros/Global.h"

namespace SmashBros
{
	GameElement* new_GameElement()
	{
		return new GameElement(0, 0);
	}

	GameElement* new_GameElement(float x1, float y1)
	{
		return new GameElement(x1, y1);
	}

	void delete_GameElement(GameElement* gameElement)
	{
		delete gameElement;
	}

	chaiscript::ModulePtr load_module_SmashBros_GameElement()
	{
		chaiscript::Module* m_smashbros_gameelement = new chaiscript::Module();

		m_smashbros_gameelement->add(chaiscript::constructor<SmashBros::GameElement(float, float)>(), "GameElement");
		m_smashbros_gameelement->add(chaiscript::fun((SmashBros::GameElement*(*)()) &new_GameElement), "new_GameElement");
		m_smashbros_gameelement->add(chaiscript::fun((SmashBros::GameElement*(*)(float,float)) &new_GameElement), "new_GameElement");
		m_smashbros_gameelement->add(chaiscript::fun(&delete_GameElement), "delete_GameElement");
		m_smashbros_gameelement->add(chaiscript::fun(&GameElement::Update), "Update");
		m_smashbros_gameelement->add(chaiscript::fun(&GameElement::Draw), "Draw");
		m_smashbros_gameelement->add(chaiscript::fun(&GameElement::isOnScreen), "isOnScreen");
		m_smashbros_gameelement->add(chaiscript::fun((boolean(*)(GameEngine::Rectangle,GameEngine::Rectangle)) &GameElement::rectsColliding), "GameElement_rectsColliding");

		return chaiscript::ModulePtr(m_smashbros_gameelement);
	}
}

#endif //SMASHBROS_SCRIPT_DISABLE
