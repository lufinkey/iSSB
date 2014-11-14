
#include "Stage.h"
#include "Global.h"
#include "ProjectileManager.h"
#include "ItemManager.h"
#include "Camera.h"
#include "Magnifier.h"
#include <cmath>

namespace SmashBros
{
	Stage::Stage(float x1, float y1)
	{
		x = x1;
		y = y1;

		bgScale = 1;
		
		background = null;

		topBorder = -350;
		bottomBorder = 350;
		leftBorder = -500;
		rightBorder = 500;
	
		topViewBorder = -300;
		bottomViewBorder = 300;
		leftViewBorder = -450;
		rightViewBorder = 450;

		showItemBounds = false;
		showWires = false;

		bgType = 0;

		gravity = 0.18;
		terminalVelocity = 9;
		
		MusicManager::loadSong("Main Theme Remix");
	}

	Stage::~Stage()
	{
		if(background!=null)
		{
			delete background;
		}

		for(int i=0; i<platforms.size(); i++)
		{
			delete platforms.get(i);
		}
		platforms.clear();

		for(int i=0; i<elements.size(); i++)
		{
			delete elements.get(i);
		}
		elements.clear();

		for(int i=0; i<hangs.size(); i++)
		{
			delete hangs.get(i);
		}
		hangs.clear();

		for(int i=0; i<foregrounds.size(); i++)
		{
			delete foregrounds.get(i);
		}
		foregrounds.clear();

		for(int i=0; i<ground.size(); i++)
		{
			delete ground.get(i);
		}
		ground.clear();
	}

	void Stage::Unload()
	{
		for(int i=0; i<files.size(); i++)
		{
			AssetManager::unloadImage(files.get(i));
		}
	}
	
	void Stage::handleAddP2PData(DataVoid&data)
	{
		addP2PData(data);
	}
	
	void Stage::handleSetP2PData(byte*&data)
	{
		setP2PData(data);
	}
	
	void Stage::addP2PData(DataVoid&data)
	{
		//Open for implementation
	}
	
	void Stage::setP2PData(byte*&data)
	{
		//Open for implementation
	}
	
	void Stage::loadFile(const String&fileName)
	{
		files.add(fileName);
		AssetManager::loadImage(fileName);
	}

	void Stage::setBackground(const String& imgName)
	{
		files.add(imgName);
		AssetManager::loadImage(imgName);
		background = new Animation("normal",1,imgName);
	}

	void Stage::setBackgroundType(byte type)
	{
		bgType = type;
	}

	void Stage::setItemBoundaries(float x1, float y1, float x2, float y2)
	{
		itemBounds.x = x + x1;
		itemBounds.y = y + y1;
		itemBounds.width = x2 - x1;
		itemBounds.height = y2 - y1;
	}

	RectangleF Stage::getItemBoundaries()
	{
		return itemBounds;
	}

	void Stage::showItemBoundaries(boolean toggle)
	{
		showItemBounds = true;
	}
	
	void Stage::setBackgroundScale(double scale)
	{
		bgScale = scale;
	}
	
	void Stage::showWireframes(boolean toggle)
	{
		for(int i=0; i<platforms.size(); i++)
		{
			platforms.get(i)->setVisible(toggle);
		}
		for(int i=0; i<hangs.size(); i++)
		{
			hangs.get(i)->setVisible(toggle);
		}
		showItemBounds = toggle;
		showWires = toggle;
	}
	
	void Stage::setWireframeColor(const Color&color)
	{
		for(int i=0; i<platforms.size(); i++)
		{
			switch(platforms.get(i)->getCollideType())
			{
				case Platform::COLLIDE_BOX:
				platforms.get(i)->getBox()->setColor(color);
				break;
				
				case Platform::COLLIDE_SOLID:
				platforms.get(i)->setWireframeColor(color);
				break;
			}
		}
		for(int i=0; i<hangs.size(); i++)
		{
			hangs.get(i)->setColor(color);
		}
	}
	
	void Stage::setElementColor(const Color&color)
	{
		for(int i=0; i<elements.size(); i++)
		{
			elements.get(i)->setColor(color);
		}
	}
	
	void Stage::Update(long gameTime)
	{
		for(int i=1; i<=Global::possPlayers; i++) //TODO: loop characters
		{
			if(Global::characters[i]!=null)
			{
				Global::characters[i]->Update(gameTime);
			}
		}
		
		for(int i=0; i<platforms.size(); i++)
		{
			updatePlatform(i);
			platforms.get(i)->Update(gameTime);
		}
		for(int i=0; i<elements.size(); i++)
		{
			elements.get(i)->Update(gameTime);
			updateElement(i);
		}
		for(int i=0; i<hangs.size(); i++)
		{
			hangs.get(i)->Update(gameTime);
			updateHangPoint(i);
		}
		for(int i=0; i<ground.size(); i++)
		{
			ground.get(i)->Update(gameTime);
			updateGround(i);
		}
		
		ProjectileManager::Update(gameTime);
		ItemManager::Update(gameTime);
		
		for(int i=0; i<=Global::possPlayers; i++) //TODO: loop characters
		{
			if(Global::characters[i]!=null)
			{
				
				checkPlayerCollisions(Global::characters[i]);
			}
		}
	}
	
	void Stage::Draw(Graphics2D&g, long gameTime)
	{
		drawBackground(g,gameTime);
		drawBottomLayer(g,gameTime);
		drawMiddleLayer(g,gameTime);
		drawTopLayer(g,gameTime);
	}
	
	void Stage::drawBackground(Graphics2D&g, long gameTime)
	{
		if(background!=null)
		{
			switch(bgType)
			{
				case BG_NORMAL:
				background->drawFrame(null, g, (float)(x*Camera::Zoom), (float)(y*Camera::Zoom), bgScale*Camera::Zoom);
				break;
				
				case BG_FIXED:
				background->drawFrame(null, g, 0, View::x, View::y, View::x + (float)View::getScalingWidth() + 1, View::y + (float)View::getScalingHeight() + 1);
				//background->drawFrame(null, g, 0, View::x, View::y, (float)View::getScalingWidth(), (float)View::getScalingHeight());
				break;
			}
		}
	}
	
	void Stage::drawBottomLayer(Graphics2D&g, long gameTime)
	{
		for(int i=0; i<elements.size(); i++)
		{
			updateElement(i);
			elements.get(i)->Draw(g, gameTime);
		}
		
		ProjectileManager::DrawBottomLayer(g, gameTime);
		
		for(int i=0; i<ground.size(); i++)
		{
			if(showWires)
			{
				ground.get(i)->setVisible(true);
				ground.get(i)->setAlpha(0.5f);
			}
			else
			{
				ground.get(i)->setVisible(false);
				ground.get(i)->setAlpha(0);
			}
			ground.get(i)->Draw(g, gameTime);
		}
		for(int i=0; i<platforms.size(); i++)
		{
			updatePlatform(i);
			platforms.get(i)->Draw(g, gameTime);
		}
	}
	
	void Stage::drawMiddleLayer(Graphics2D&g, long gameTime)
	{
		ItemManager::Draw(g, gameTime);
		
		for(int i=0; i<hangs.size(); i++)
		{
			updateHangPoint(i);
			hangs.get(i)->Draw(g, gameTime);
		}
		if(showItemBounds)
		{
			g.setColor(Color::GREEN);
			g.drawRect((itemBounds.x*Camera::Zoom - View::x), (itemBounds.y*Camera::Zoom - View::y), (itemBounds.width*Camera::Zoom), (itemBounds.height*Camera::Zoom));
		}
		for(int i=1; i<=Global::possPlayers; i++) //TODO: loop characters
		{
			if(Global::characters[i]!=null)
			{
				Global::characters[i]->Draw(g, gameTime);
			}
		}
		ProjectileManager::DrawMiddleLowerLayer(g, gameTime);
	}
	
	void Stage::drawTopLayer(Graphics2D&g, long gameTime)
	{
		ProjectileManager::DrawMiddleUpperLayer(g, gameTime);
		for(int i=0; i<foregrounds.size(); i++)
		{
			updateForeground(i);
			foregrounds.get(i)->Draw(g, gameTime);
		}
		ProjectileManager::DrawTopLayer(g, gameTime);
		
		for(int i=0; i<=Global::possPlayers; i++)
		{
			if(Global::characters[i]!=NULL && Global::characters[i]->isAlive())
			{
				Magnifier::Draw(g, gameTime, Global::characters[i]);
			}
		}
	}
	
	void Stage::checkPlayerCollisions(Player*playr)
	{
		boolean setGrounded = playr->groundCheck;
		for(byte j=1; j<8; j++)
		{
			playr->prevCollidePlatform[j-1] = playr->currentCollidePlatform[j-1];
		}
		byte borderDir = borderColliding(playr);
		if(borderDir > 0)
		{
			playr->onBorderCollide(borderDir);
		}
		else
		{
			for(int j=0; j<hangs.size(); j++)
			{
				if(wireframeCollision(playr,hangs.get(j))&&!playr->groundColliding)
				{
					if(!playr->prevHangColliding)
					{
						playr->hangColliding = true;
						playr->currentHangPoint = hangs.get(j);
						playr->onHang(hangs.get(j));
						j = hangs.size();
					}
					else
					{
						playr->whileHanging(playr->currentHangPoint);
					}
				}
				else if(playr->currentHangPoint == hangs.get(j) && playr->prevHangColliding)
				{
					playr->hangColliding = false;
					playr->finishHang(playr->currentHangPoint);
					j = hangs.size();
				}
			}
			if(!playr->hangColliding)
			{
				for(int j=0; j<ground.size(); j++)
				{
					if(!playr->heldByPlayer && playr->isColliding(ground.get(j)))
					{
						if(setGrounded)
						{
							playr->whileGroundColliding();
						}
						playr->groundColliding = true;
						if(!playr->prevGroundColliding)
						{
							playr->onGroundCollide();
						}
						setGrounded = true;
					}
				}
			}
			for(int i=0; i<8; i++)
			{
				playr->currentCollidePlatformActor[i] = null;
			}
			for(int j=0; j<platforms.size(); j++)
			{
				byte dir = 0;
				dir = checkPlatformCollision(playr,platforms.get(j));
				if(dir>0)
				{
					playr->platformCollision(platforms.get(j), dir);
					playr->setCurrentCollidePlatformActor(dir, platforms.get(j));
					playr->collideQueue.add(dir);
				}
				boolean grounded = false;
				if(dir == PrimitiveActor::DIR_UP || platforms.get(j)->checkGroundCollision(playr))
				{
					grounded = true;
				}
				if(grounded && !playr->hangColliding)
				{
					playr->groundColliding = true;
					if(playr->prevGroundColliding || setGrounded)
					{
						playr->whileGroundColliding();
					}
					else
					{
						playr->onGroundCollide();
					}
					setGrounded = true;
				}
			}
			if(playr->prevGroundColliding && !setGrounded)
			{
				playr->groundColliding = false;
				playr->finishGroundCollide();
			}
			for(byte j=1; j<=8; j++)
			{
				playr->currentCollidePlatform[j-1] = false;
			}
			for(int j=0; j<playr->collideQueue.size(); j++)
			{
				playr->currentCollidePlatform[playr->collideQueue.get(j)-1] = true;
			}
			for(byte j=1; j<=8; j++)
			{
				if(!playr->currentCollidePlatform[j-1] && playr->prevCollidePlatform[j-1])
				{
					playr->finishPlatformCollide(playr->getCurrentCollidePlatformActor(j), j);
				}
			}
			playr->prevGroundColliding = playr->groundColliding;
			playr->prevHangColliding = playr->hangColliding;
		}
	}
	
	void Stage::setGravity(double grav)
	{
		gravity = grav;
	}
	
	double Stage::getGravity()
	{
		return gravity;
	}
	
	void Stage::setTerminalVelocity(double vel)
	{
		terminalVelocity = vel;
	}
	
	double Stage::getTerminalVelocity()
	{
		return terminalVelocity;
	}
	
	void Stage::addElement(GameElement*a)
	{
		Vector2<Vector2f> pnt;
		
		pnt.x.x = a->x;
		pnt.x.y = a->y;
		pnt.y.x = a->x + x;
		pnt.y.y = a->y + y;
		
		a->x += x;
		a->y += y;
		
		ArrayList<String> animFiles = a->getAnimation()->getAllFilenames();
		for(int i=0; i<animFiles.size(); i++)
		{
			files.add(animFiles[i]);
		}
		
		elementCoords.add(pnt);
		elements.add(a);
	}
	
	void Stage::addPlatform(Platform*plat)
	{
		Vector2<Vector2f> pnt;
		
		if(plat->getCollideType() == Platform::COLLIDE_SOLID)
		{
			ArrayList<String> animFiles = plat->getAnimation()->getAllFilenames();
			for(int i=0; i<animFiles.size(); i++)
			{
				files.add(animFiles[i]);
			}
		}
		
		pnt.x.x = plat->x;
		pnt.x.y = plat->y;
		pnt.y.x = plat->x + x;
		pnt.y.y = plat->y + y;
		
		plat->x += x;
		plat->y += y;
		
		platCoords.add(pnt);
		platforms.add(plat);
	}
	
	void Stage::addForeground(GameElement*a)
	{
		Vector2<Vector2f> pnt;
		
		pnt.x.x = a->x;
		pnt.x.y = a->y;
		pnt.y.x = a->x + x;
		pnt.y.y = a->y + y;
		
		a->x += x;
		a->y += y;
		
		ArrayList<String> animFiles = a->getAnimation()->getAllFilenames();
		for(int i=0; i<animFiles.size(); i++)
		{
			files.add(animFiles[i]);
		}
		
		fgCoords.add(pnt);
		foregrounds.add(a);
	}
	
	void Stage::addHangPoint(HangPoint*hp)
	{
		Vector2<Vector2f> pnt;
		
		pnt.x.x = hp->x;
		pnt.x.y = hp->y;
		pnt.y.x = hp->x + x;
		pnt.y.y = hp->y + y;
		
		hp->x += x;
		hp->y += y;
		
		hangCoords.add(pnt);
		hangs.add(hp);
	}
	
	void Stage::addGround(GameElement*gr)
	{
		Vector2<Vector2f> pnt;
		
		pnt.x.x = gr->x;
		pnt.x.y = gr->y;
		pnt.y.x = gr->x + x;
		pnt.y.y = gr->y + y;
		
		gr->x += x;
		gr->y += y;
		
		groundCoords.add(pnt);
		ground.add(gr);
	}
	
	void Stage::updatePlatform(int index)
	{
		Platform*plat = platforms.get(index);
		Vector2<Vector2f> pnt = platCoords.get(index);
		
		if(plat->x != (float)pnt.y.x)
		{
			float dif = plat->x - pnt.y.x;
			pnt.x.x += dif;
		}
		if(plat->y != (float)pnt.y.y)
		{
			float dif = plat->y - pnt.y.y;
			pnt.x.y += dif;
		}
		
		pnt.y.x = (x + pnt.x.x);
		pnt.y.y = (y + pnt.x.y);
		
		plat->x = pnt.y.x;
		plat->y = pnt.y.y;
	}
	
	void Stage::updateElement(int index)
	{
		Actor*a = elements.get(index);
		Vector2<Vector2f> pnt = elementCoords.get(index);
		
		if(a->x != (float)pnt.y.x)
		{
			float dif = a->x - pnt.y.x;
			pnt.x.x += dif;
		}
		if(a->y != (float)pnt.y.y)
		{
			float dif = a->y - pnt.y.y;
			pnt.x.y += dif;
		}
		
		pnt.y.x = (x + pnt.x.x);
		pnt.y.y = (y + pnt.x.y);
		
		a->x = pnt.y.x;
		a->y = pnt.y.y;
	}
	
	void Stage::updateForeground(int index)
	{
		GameElement*a = foregrounds.get(index);
		Vector2<Vector2f> pnt = fgCoords.get(index);
		
		if(a->x != (float)pnt.y.x)
		{
			float dif = a->x - pnt.y.x;
			pnt.x.x += dif;
		}
		if(a->y != (float)pnt.y.y)
		{
			float dif = a->y - pnt.y.y;
			pnt.x.y += dif;
		}
		
		pnt.y.x = (x + pnt.x.x);
		pnt.y.y = (y + pnt.x.y);
		
		a->x = pnt.y.x;
		a->y = pnt.y.y;
	}
	
	void Stage::updateHangPoint(int index)
	{
		HangPoint*hp = hangs.get(index);
		Vector2<Vector2f> pnt = hangCoords.get(index);
		
		if(hp->x != (float)pnt.y.x)
		{
			float dif = hp->x - pnt.y.x;
			pnt.x.x += dif;
		}
		if(hp->y != (float)pnt.y.y)
		{
			float dif = hp->y - pnt.y.y;
			pnt.x.y += dif;
		}
		
		pnt.y.x = (x + pnt.x.x);
		pnt.y.y = (y + pnt.x.y);
		
		hp->x = pnt.y.x;
		hp->y = pnt.y.y;
	}
	
	void Stage::updateGround(int index)
	{
		GameElement*gr = ground.get(index);
		Vector2<Vector2f> pnt = groundCoords.get(index);
		
		if(gr->x != (float)pnt.y.x)
		{
			float dif = gr->x - pnt.y.x;
			pnt.x.x += dif;
		}
		if(gr->y != (float)pnt.y.y)
		{
			float dif = gr->y - pnt.y.y;
			pnt.x.y += dif;
		}
		
		pnt.y.x = (x + pnt.x.x);
		pnt.y.y = (y + pnt.x.y);
		
		gr->x = pnt.y.x;
		gr->y = pnt.y.y;
	}
	
	void Stage::setSpawnPoint(int spawnNo, float x1, float y1)
	{
		spawns[spawnNo].x = x1;
		spawns[spawnNo].y = y1;
	}
	
	Vector2f Stage::getSpawnPoint(int spawnNo)
	{
		Vector2f pnt;
		pnt.x = x + spawns[spawnNo].x;
		pnt.y = y + spawns[spawnNo].y;
		return pnt;
	}
	
	RectF Stage::getBorders()
	{
		RectF borders = {leftBorder,topBorder,rightBorder,bottomBorder};
		return borders;
	}
	
	RectF Stage::getViewBorders()
	{
		RectF borders = {leftViewBorder,topViewBorder,rightViewBorder,bottomViewBorder};
		return borders;
	}
	
	boolean Stage::checkSafeArea(Player*playr)
	{
		/*if(safe.size()==0)
		{
			if(playr->isOnGround())
			{
				return true;
			}
			return false;
		}
		Rectangle playrRect = new Rectangle((int)(playr->x - playr->width/2 - x),(int)(playr->y - playr->height/2 - y),playr->width,playr->height);
		
		for(int i=0; i<safe.size(); i++)
		{
			if(GameElement.rectsColliding(playrRect, safe.get(i)))
			{
				return true;
			}
		}
		return false;*/
		
		playr->updateHitbox();
		
		if(playr->isOnGround())
		{
			return true;
		}
		
		for(int i=0; i<platforms.size(); i++)
		{
			Platform*plat = platforms.get(i);
			Rectangle platRect;
			if(plat->getCollideType()==Platform::COLLIDE_SOLID)
			{
				platRect = Rectangle((int)(plat->x - plat->width/2),(int)(plat->y - plat->height/2),plat->width,plat->height);
			}
			else
			{
				platRect = Rectangle((int)plat->x,(int)plat->y,plat->width,plat->height);
			}
			
			float middleY = platRect.y + (float)platRect.height/2;
			
			if(playr->hitbox->y<middleY && playr->hitbox->x>platRect.x && (playr->hitbox->x+playr->hitbox->width)<(platRect.x+platRect.width))
			{
				return true;
			}
		}
		return false;
	}
	
	byte Stage::checkPlatformCollision(Player*p, Platform*collide)
	{
		switch(collide->getCollideType())
		{
			case Platform::COLLIDE_BOX:
			if(p->hitboxRectsColliding(collide->getBox()))
			{
				if(collide->getType()==Platform::TYPE_NORMAL || (collide->getType()==Platform::TYPE_GOTHROUGH && !p->dropping))
				{
					byte dir = collide->getBoxDirection(p);
					switch(dir)
					{
						case PrimitiveActor::DIR_UP:
						if(p->yvelocity>=0)
						{
							p->y = (collide->getBox()->y - (float)((float)(p->hitboxPoint.height + p->hitboxPoint.y)*p->getScale()) + 1);
						}
						break;
						
						case PrimitiveActor::DIR_DOWN:
						if(collide->getType()!=Platform::TYPE_GOTHROUGH)
						{
							p->y=(collide->getBox()->y+collide->getBox()->height - (float)((float)p->hitboxPoint.y*p->getScale()));
						}
						break;
						
						case PrimitiveActor::DIR_LEFT:
						if(collide->getType()!=Platform::TYPE_GOTHROUGH)
						{
							p->x = (collide->getBox()->x - (float)(((float)p->hitboxPoint.width*p->getScale())/2));
						}
						break;
						
						case PrimitiveActor::DIR_RIGHT:
						if(collide->getType()!=Platform::TYPE_GOTHROUGH)
						{
							p->x = (collide->getBox()->x + collide->getBox()->width + (float)(((float)p->hitboxPoint.width*p->getScale())/2));
						}
						break;
					}
					p->updateHitbox();
					return dir;
				}
			}
			return 0;
			
			case Platform::COLLIDE_SOLID:
			if(collide->getType()==Platform::TYPE_NORMAL || (collide->getType()==Platform::TYPE_GOTHROUGH && !p->dropping))
			{
				return p->solidPlatformCollision(collide);
			}
			else if(p->dropping)
			{
				byte dir = p->isColliding2(collide);
				switch(dir)
				{
					case PrimitiveActor::DIR_UP:
					return PrimitiveActor::DIR_DOWN;
					
					case PrimitiveActor::DIR_DOWN:
					return PrimitiveActor::DIR_UP;
					
					case PrimitiveActor::DIR_LEFT:
					return PrimitiveActor::DIR_RIGHT;
					
					case PrimitiveActor::DIR_RIGHT:
					return PrimitiveActor::DIR_LEFT;
				}
				return 0;
			}
			return 0;
		}
		return 0;
	}
	
	byte Stage::checkItemPlatformCollision(Item*item, Platform*collide)
	{
		switch(collide->getCollideType())
		{
			case Platform::COLLIDE_BOX:
			if(item->Actor::rectsColliding(collide->getBox()))
			{
				if(collide->getType()==Platform::TYPE_NORMAL || (collide->getType()==Platform::TYPE_GOTHROUGH && !item->ignoreGoThrough))
				{
					byte dir = 0;
					dir = item->normalPlatformCollision(collide);
					switch(dir)
					{
						case PrimitiveActor::DIR_UP:
						item->yvelocity = 0;
						item->xvelocity = 0;
						break;
						
						case PrimitiveActor::DIR_DOWN:
						if(collide->getType()!=Platform::TYPE_GOTHROUGH)
						{
							item->yvelocity = std::abs(item->yvelocity);
						}
						break;
						
						case PrimitiveActor::DIR_LEFT:
						if(collide->getType()!=Platform::TYPE_GOTHROUGH)
						{
							item->xvelocity = -std::abs(item->xvelocity);
						}
						break;
						
						case PrimitiveActor::DIR_RIGHT:
						if(collide->getType()!=Platform::TYPE_GOTHROUGH)
						{
							item->xvelocity = std::abs(item->xvelocity);
						}
						break;
					}
					return dir;
				}
			}
			return 0;
			
			case Platform::COLLIDE_SOLID:
			if(collide->getType()==Platform::TYPE_NORMAL || (collide->getType()==Platform::TYPE_GOTHROUGH && !item->ignoreGoThrough))
			{
				byte dir = item->solidPlatformCollision(collide);
				if(dir==PrimitiveActor::DIR_UP)
				{
					item->yvelocity = 0;
					item->xvelocity = 0;
				}
				else if(dir==PrimitiveActor::DIR_LEFT)
				{
					item->xvelocity = -std::abs(item->xvelocity);
				}
				else if(dir==PrimitiveActor::DIR_RIGHT)
				{
					item->xvelocity = std::abs(item->xvelocity);
				}
				else if(dir==PrimitiveActor::DIR_DOWN)
				{
					item->yvelocity = std::abs(item->yvelocity);
				}
				return dir;
			}
			return 0;
		}
		return 0;
	}
	
	void Stage::itemPlatformCollisions(Item*item)
	{
		boolean setGrounded = false;
		ArrayList<byte> collides = ArrayList<byte>();
		for(int i=0; i<8; i++)
		{
			item->platformColliding[i] = false;
		}
		for(int j=0; j<platforms.size(); j++)
		{
			byte dir = 0;
			if(!item->isHeld())
			{
				dir = checkItemPlatformCollision(item,platforms.get(j));
			}
			if(dir>0)
			{
				item->platformCollision(platforms.get(j), dir);
				item->currentCollidePlatform[dir] = platforms.get(j);
				collides.add(dir);
			}
			boolean grounded = false;
			switch(dir)
			{
				case PrimitiveActor::DIR_UP:
				grounded = true;
				if(item->weight>0)
				{
					item->yvelocity = 0;
				}
				break;
				
				case PrimitiveActor::DIR_LEFT:
				case PrimitiveActor::DIR_RIGHT:
				if(item->weight>0)
				{
					item->xvelocity*=-1;
				}
				break;
			}
			if(grounded)
			{
				if(!setGrounded)
				{
					item->whileGroundColliding();
				}
				item->groundColliding = true;
				if(!item->prevGroundColliding)
				{
					item->onGroundCollide();
				}
				setGrounded = true;
			}
		}
		for(int i=0; i<8; i++)
		{
			item->prevPlatformColliding[i] = item->platformColliding[i];
		}
	}
	
	byte Stage::borderColliding(Player*p)
	{
		if(p->isAlive())
		{
			if(p->x < x + leftBorder)
			{
				return PrimitiveActor::DIR_LEFT;
			}
			else if(p->x > x + rightBorder)
			{
				return PrimitiveActor::DIR_RIGHT;
			}
			else if(p->y < y + topBorder)
			{
				return PrimitiveActor::DIR_UP;
			}
			else if(p->y > y + bottomBorder)
			{
				return PrimitiveActor::DIR_DOWN;
			}
		}
		return 0;
	}
	
	boolean Stage::wireframeCollision(Player*playr, WireframeActor*collide)
	{
		if(playr->getScale()==0 || collide->width==0 || collide->height==0)
		{
			return false;
		}
		
		Rectangle r1 = Rectangle((int)(playr->x - playr->width/2), (int)(playr->y - playr->height/2), playr->width, playr->height);
		Rectangle r2 = Rectangle((int)collide->x,(int)collide->y,collide->width,collide->height);
		Rectangle overlap = Player::getOverlapRect(r1,r2);
		
		if(overlap.x!=-1)
		{
			int startX = overlap.x;
			int endX = overlap.x + overlap.width;
			int startY = overlap.y;
			int endY = overlap.y + overlap.height;
			
			float x1 = ((float)startX/playr->getScale());
			float y1 = ((float)startY/playr->getScale());
			float incr1 = (float)(1/playr->getScale());
			
			float pntX1 = x1;
			float pntY1 = y1;
			
			for(int cntY=startY; cntY<endY; cntY++)
			{
				pntX1 = x1;
				for(int cntX=startX; cntX<endX; cntX++)
				{
					if(playr->pixelAtPoint((int)pntX1, (int)pntY1))
					{
						return true;
					}
					pntX1 += incr1;
				}
				pntY1 += incr1;
			}
		}
		return false;
	}
	
	byte Stage::checkProjectileCollision(Projectile*p, Platform*collide)
	{
		switch(collide->getCollideType())
		{
			case Platform::COLLIDE_BOX:
			{
				if(p->isSolid())
				{
					byte dir = p->solidPlatformCollision(collide);
					return dir;
				}
				else if(p->Actor::rectsColliding(collide->getBox()))
				{
					byte dir = collide->getBoxDirection(p);
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
					if(p->isSolid())
					{
						switch(dir)
						{
							case PrimitiveActor::DIR_UP:
							p->y = collide->getBox()->y - p->height/2;
							break;
							
							case PrimitiveActor::DIR_DOWN:
							p->y = collide->getBox()->y + collide->getBox()->height + p->height/2;
							break;
							
							case PrimitiveActor::DIR_LEFT:
							p->x = collide->getBox()->x - p->width/2;
							break;
							
							case PrimitiveActor::DIR_RIGHT:
							p->x = collide->getBox()->x + collide->getBox()->width + p->width/2;
							break;
						}
					}
					return dir;
				}
			}
			return 0;
			
			case Platform::COLLIDE_SOLID:
			byte dir = 0;
			if(p->isSolid())
			{
				dir = p->solidPlatformCollision(collide);
			}
			else
			{
				dir = p->isPlatformColliding(collide);
			}
			return dir;
		}
		return 0;
	}
}