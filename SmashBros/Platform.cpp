#include "Platform.h"
#include "Camera.h"
#include "Player.h"

namespace SmashBros
{
	Platform::WireframeElement::WireframeElement(float x1, float y1, int width, int height) : WireframeActor(x1,y1,width,height)
	{
		//
	}

	Platform::WireframeElement::~WireframeElement()
	{
		//
	}

	void Platform::WireframeElement::Draw(Graphics2D&g, long gameTime)
	{
		drawActor(g, gameTime, (float)(x*Camera::Zoom), (float)(y*Camera::Zoom), Camera::Zoom);
	}

	Platform::Platform(byte type, float x1, float y1) : GameElement(x1,y1)
	{
		box = null;
		ground = null;
		this->type = type;
		this->collideType = COLLIDE_SOLID;
	}

	Platform::Platform(byte type, float x1, float y1, int width, int height) : GameElement(x1,y1)
	{
		this->type = type;
		this->collideType = COLLIDE_BOX;
		box = new WireframeElement(x1,y1,width,height);
		ground = new WireframeElement(x1,y1-5,width, 6);

		this->width = width;
		this->height = height;
	}

	Platform::~Platform()
	{
		if(box!=null)
		{
			delete box;
		}
		if(ground!=null)
		{
			delete ground;
		}
	}

	void Platform::Update(long gameTime)
	{
		GameElement::Update(gameTime);
		if(collideType == COLLIDE_BOX)
		{
			box->x = x;
			box->y = y;
		}
	}

	void Platform::Draw(Graphics2D&g, long gameTime)
	{
		switch(collideType)
		{
			case COLLIDE_SOLID:
			GameElement::Draw(g, gameTime);
			break;
			
			case COLLIDE_BOX:
			box->x = x;
			box->y = y;
			box->Draw(g, gameTime);
			width = box->width;
			height = box->height;
			break;
		}
	}

	boolean Platform::checkGroundCollision(SmashBros::Player*playr)
	{
		if(collideType == COLLIDE_BOX)
		{
			if(playr->hitboxRectsColliding(ground))
			{
				return true;
			}
			return false;
		}
		return false;
	}

	byte Platform::getType()
	{
		return type;
	}

	byte Platform::getBoxDirection(GameElement*collide)
	{
		byte dir = PrimitiveActor::getDir(box, collide);
		if(dir==PrimitiveActor::DIR_UPLEFT || dir==PrimitiveActor::DIR_UPRIGHT)
		{
			dir = PrimitiveActor::DIR_UP;
		}
		else if(dir==PrimitiveActor::DIR_DOWNLEFT)
		{
			dir = PrimitiveActor::DIR_LEFT;
		}
		else if(dir==PrimitiveActor::DIR_DOWNRIGHT)
		{
			dir = PrimitiveActor::DIR_RIGHT;
		}
		return dir;
	}

	WireframeActor*Platform::getBox()
	{
		return (WireframeActor*)box;
	}

	byte Platform::getCollideType()
	{
		return collideType;
	}

	void Platform::setVisible(boolean toggle)
	{
		if(collideType == COLLIDE_BOX)
		{
			box->setVisible(toggle);
		}
		else
		{
			showWireframe(toggle);
		}
	}

	void Platform::onPlayerCollide(SmashBros::Player*collide, byte dir)
	{
		//Open for implementation
	}

	void Platform::whilePlayerColliding(SmashBros::Player*collide, byte dir)
	{
		//Open for implementation
	}

	void Platform::finishPlayerCollide(SmashBros::Player*collide, byte dir)
	{
		//Open for implementation
	}
}