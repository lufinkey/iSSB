
#include "OffScreenExplode.h"
#include "../../../Global.h"

namespace SmashBros
{
	OffScreenExplode::OffScreenExplode(int playerNo) : GameElement(0,0)
	{
		this->playerNo = playerNo;
		active = false;
		addAnimation(new Animation("normal",1,"Images/Game/Misc/offscreen_explode.png"));
		changeAnimation("normal", FORWARD);
		setScale(1.1f);
	}
	
	OffScreenExplode::~OffScreenExplode()
	{
		//
	}

	void OffScreenExplode::setActive()
	{
		active = true;
		setAlpha(0);
		changeAnimation("normal", FORWARD);
		Console::WriteLine("setting OffScreenExplode Active");
	}

	void OffScreenExplode::Update(long gameTime)
	{
		if(active)
		{
			GameElement::Update(gameTime);
			setAlpha(getAlpha()+0.02f);
			if(getAlpha()>=1)
			{
				active = false;
				if(Global::characters[playerNo]->getStock() > 0)
				{
					Global::characters[playerNo]->respawn();
				}
			}
		}
	}

	void OffScreenExplode::Draw(Graphics2D&g, long gameTime)
	{
		if(active)
		{
			GameElement::Draw(g, gameTime);
		}
	}
}