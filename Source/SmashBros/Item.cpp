
#include "Item.h"
#include "Global.h"
#include "ItemManager.h"
#include "ProjectileManager.h"
#include "Global.h"
#include "P2PDataManager.h"
#include <cmath>

namespace SmashBros
{
	int Item::nextID = 0;
	
	Item::Item(float x1, float y1, long liveTime, byte type) : GameElement(x1,y1)
	{
		this->id = nextID;
		nextID++;
		if(nextID == INTEGER_MAX)
		{
			nextID = 0;
		}
		while(!ItemManager::checkIDAvailable(nextID))
		{
			nextID++;
			if(nextID == INTEGER_MAX)
			{
				nextID = 0;
			}
		}
		
		Console::WriteLine((String)"Item created with ID " + id);
		
		index = 0;
		
		this->type = type;
		this->collideType = COLLIDE_BOX;
		
		itemNo = 0;
		weight = 0;
		finishTime = 0;
		dead = false;
		isSolid = false;
		accelGrav = true;
		ignoreGoThrough = false;
		bound = true;
		canCarry = true;
		held = false;
		deflectable = false;
		tossOnDiscard = false;
		tossing = false;
		ownerNo = 0;
		holderNo = 0;
		offsetX = 0;
		offsetY = 0;
		
		groundColliding = false;
		prevGroundColliding = false;
		
		playerCollisions = CollisionManager();
		playerHits = CollisionManager();
		
		this->finishTime = Global::getWorldTime() + liveTime;
		
		dead = false;
	}
	
	Item::~Item()
	{
		if(!dead && P2PDataManager::isEnabled())
		{
			ItemManager::destroyedItems.add(this->id);
		}
		dead = true;
	}
	
	int Item::getID()
	{
		return this->id;
	}
	
	void Item::setNextID(int itemID)
	{
		nextID = itemID;
	}
	
	//x, y, animIndex, frame, bools, ownerNo, holderNo
	//4, 4, 4,         4,     1,     1        1        = 31
	void Item::handleAddP2PData(DataVoid&data)
	{
		int frame = getAnimation()->getCurrentFrame();
		int animIndex = getAnimIndex();
		float scale = getScale();
		Bitset bools;
		//visible
		if(isVisible())
		{
			bools.set(0, true);
		}
		else
		{
			bools.set(0, false);
		}
		byte boolsByte = bools.getByte();
		
		data.add(&x, sizeof(x));
		data.add(&y, sizeof(y));
		data.add(&animIndex, sizeof(animIndex));
		data.add(&frame, sizeof(frame));
		data.add(&scale, sizeof(scale));
		data.add(&boolsByte, sizeof(boolsByte));
		data.add(&ownerNo, sizeof(ownerNo));
		data.add(&holderNo, sizeof(holderNo));
		
		DataVoid newData;
		addP2PData(newData);
		data.add(newData);
	}
	
	void Item::handleSetP2PData(byte*&data)
	{
		//x
		x = DataVoid::toFloat(data);
		data += sizeof(float);
		
		//y
		y = DataVoid::toFloat(data);
		data += sizeof(float);
		
		//animIndex
		int animIndex = DataVoid::toInt(data);
		changeAnimation(animIndex, STOPPED);
		data += sizeof(int);
		
		//frame
		int frame = DataVoid::toInt(data);
		getAnimation()->setCurrentFrame(frame);
		data += sizeof(int);
		
		//Scale
		float scale = DataVoid::toFloat(data);
		setScale(scale);
		data += sizeof(float);
		
		//bools
		byte boolsByte = data[0];
		Bitset bools(boolsByte);
		//visibility
		if(bools.get(0))
		{
			setVisible(true);
		}
		else
		{
			setVisible(false);
		}
		data += sizeof(byte);
		
		//ownerNo
		ownerNo = data[0];
		data += sizeof(byte);
		
		//holderNo
		holderNo = data[0];
		data += sizeof(byte);
		
		setP2PData(data);
	}
	
	void Item::addP2PData(DataVoid&data)
	{
		//Open for implementation
	}
	
	void Item::setP2PData(byte*&data)
	{
		//Open for implementation
	}
	
	void Item::addAnimation(Animation*a)
	{
		ArrayList<String> animFiles = a->getAllFilenames();
		for(int i=0; i<animFiles.size(); i++)
		{
			ItemManager::addFile(animFiles[i]);
		}
		Actor::addAnimation(a);
	}
	
	void Item::addFileResource(String file)
	{
		ItemManager::addFile(file);
	}
	
	void Item::canBeCarried(boolean toggle)
	{
		this->canCarry = toggle;
	}
	
	boolean Item::canPickUp()
	{
		return true;
	}
	
	boolean Item::allowsGrabDelay()
	{
		return false;
	}
	
	int Item::getItemNo()
	{
		return itemNo;
	}
	
	void Item::setItemOwner(byte owner)
	{
		this->ownerNo = owner;
	}
	
	byte Item::getItemOwner()
	{
		return ownerNo;
	}
	
	byte Item::getItemHolder()
	{
		return holderNo;
	}
	
	void Item::setBoundToHolder(boolean toggle)
	{
		bound = toggle;
		if(held)
		{
			Player*playr = getPlayer();
			if(playr!=null)
			{
				switch(playr->getPlayerDir())
				{
					case Player::LEFT:
					x = playr->x - (float)((playr->itemOffsetX + offsetX)*playr->getScale());
					break;
					
					case Player::RIGHT:
					x = playr->x + (float)((playr->itemOffsetX + offsetX)*playr->getScale());
				}
				y = playr->y + (float)((playr->itemOffsetY + offsetY)*playr->getScale());
			}
		}
	}
	
	void Item::setHoldOffset(float x1, float y1)
	{
		offsetX = x1;
		offsetY = y1;
	}
	
	Player*Item::getPlayer()
	{
		if(held)
		{
			return Global::getPlayerActor(getItemHolder());
		}
		return null;
	}
	
	boolean Item::isHeld()
	{
		return held;
	}
	
	void Item::setDeflectable(boolean toggle)
	{
		deflectable = toggle;
	}
	
	void Item::setSolid(boolean toggle)
	{
		isSolid = toggle;
	}
	
	boolean Item::chargeSmash(byte attackType)
	{
		return false;
	}
	
	boolean Item::use(byte attackType)
	{
		return false;
	}
	
	void Item::discard()
	{
		if(isHeld())
		{
			Player* owner = Global::getPlayerActor(getItemHolder());
			owner->discardItem();
		}
	}
	
	void Item::toss(byte tossAttackType)
	{
		if(isHeld())
		{
			Player* owner = Global::getPlayerActor(getItemHolder());
			if(owner->itemHolding==this)
			{
				owner->tossItem(tossAttackType);
			}
		}
	}
	
	void Item::whenPickedUp(Player*collide)
	{
		if(type!= TYPE_FOOD)
		{
			if(bound)
			{
				x = collide->x;
				y = collide->y;
			}
			yvelocity = 0;
			xvelocity = 0;
			held = true;
			holderNo = collide->getPlayerNo();
			ownerNo = collide->getPlayerNo();
		}
		onPickUp(collide);
	}
	
	void Item::whenDiscarded()
	{
		if(tossing)
		{
			Player*playr = getPlayer();
			held = false;
			holderNo = 0;
			playr->itemHolding = null;
			
			onDiscard(playr);
		}
		else
		{
			if(tossOnDiscard)
			{
				boolean prevTossing = tossing;
				tossing = true;
				
				toss(Player::ATTACK_A);
				
				tossing = prevTossing;
			}
			else
			{
				Player*playr = getPlayer();
				held = false;
				holderNo = 0;
				playr->itemHolding = null;
				
				switch(playr->getPlayerDir())
				{
					case Player::LEFT:
					xvelocity = 1.5f;
					break;
						
					case Player::RIGHT:
					xvelocity = -1.5f;
					break;
				}
				yvelocity = -2;
				
				onDiscard(playr);
			}
		}
	}
	
	void Item::whenTossed(byte tossAttackType)
	{
		boolean prevTossing = tossing;
		tossing = true;
		
		Player* holder = Global::getPlayerActor(getItemHolder());
		if(type==Item::TYPE_HOLD)
		{
			discard();
			switch(tossAttackType)
			{
				case Player::ATTACK_A:
				switch(holder->getPlayerDir())
				{
					case Player::LEFT:
					xvelocity = -5.2f;
					break;
					
					case Player::RIGHT:
					xvelocity = 5.2f;
					break;
				}
				yvelocity = -2;
				break;
				
				case Player::ATTACK_SIDEA:
				case Player::ATTACK_SIDESMASH:
				switch(holder->getPlayerDir())
				{
					case Player::LEFT:
					xvelocity = -6.6f;
					break;
					
					case Player::RIGHT:
					xvelocity = 6.6f;
					break;
				}
				yvelocity = -1.7f;
				break;
				
				case Player::ATTACK_UPA:
				yvelocity = -6.2f;
				break;
				
				case Player::ATTACK_DOWNA:
				yvelocity = 6.2f;
				break;
			}
		}
		else
		{
			discard();
		}
		
		tossing = prevTossing;
		
		onToss(holder, tossAttackType);
	}
	
	void Item::onPickUp(Player*collide)
	{
		//Open for implementation
	}
	
	void Item::onDiscard(Player*discarder)
	{
		//Open for implementation
	}
	
	void Item::onToss(Player*tosser, byte tossAttackType)
	{
		//Open for implementation
	}
	
	void Item::onPlayerCollide(Player*collide)
	{
		//Open for implementation
	}
	
	void Item::whilePlayerColliding(Player*collide)
	{
		//Open for implementation
	}
	
	void Item::finishPlayerCollide(Player*collide)
	{
		//Open for implementation
	}
	
	void Item::onPlayerHit(Player*collide, byte dir)
	{
		//Open for implementation
	}
	
	void Item::whilePlayerHitting(Player*collide, byte dir)
	{
		//Open for implementation
	}
	
	void Item::finishPlayerHit(Player*collide)
	{
		//Open for implementation
	}
	
	void Item::onPlatformCollide(Platform*collide, byte dir)
	{
		//Open for implementation
	}
	
	void Item::whilePlatformColliding(Platform*collide, byte dir)
	{
		//Open for implementation
	}
	
	void Item::finishPlatformCollide(Platform*collide, byte dir)
	{
		//Open for implementation
	}
	
	void Item::onGroundCollide()
	{
		//Open for implementation
	}
	
	void Item::whileGroundColliding()
	{
		//Open for implementation
	}
	
	void Item::finishGroundCollide()
	{
		//Open for implementation
	}
	
	void Item::onHolderHurt()
	{
		//Open for implementation
	}

	boolean Item::holderCanDo()
	{
		return true;
	}

	void Item::onCreate()
	{
		//Open for implementation
	}

	void Item::onDestroy()
	{
		//Open for implementation
	}
	
	void Item::deflect(byte dir)
	{
		//Open for implementation
	}
	
	void Item::doPowerUp(Player*collide, byte type, float value)
	{
		switch(type)
		{
			case POWERUP_FINALSMASH:
			Global::smashBallOnField = false;
			Global::playerHasSmashBall = true;
			collide->canFinalsmash = true;
			break;
			
			case POWERUP_HEAL:
			collide->percent-=(int)value;
			if(collide->percent<0)
			{
				collide->percent = 0;
			}
			break;
		}
	}

	void Item::platformCollision(Platform*collide, byte dir)
	{
		if(dir>0)
		{
			if(prevPlatformColliding[dir-1])
			{
				whilePlatformColliding(collide, dir);
			}
			else
			{
				onPlatformCollide(collide, dir);
				whilePlatformColliding(collide, dir);
			}
		}
		else
		{
			if(prevPlatformColliding[dir-1])
			{
				finishPlatformCollide(collide,dir);
			}
		}
	}

	void Item::ignoreGoThroughPlatforms(boolean toggle)
	{
		ignoreGoThrough = toggle;
	}

	void Item::Update(long gameTime)
	{
		while(playerCollideDelays.size()>0)
		{
			PlayerCollisionArgs args = playerCollideDelays.get(0);
			if(isHeld() && getItemOwner()==args.playerNo)
			{
				playerHits.removeCollision(args.playerNo);
			}
			else
			{
				onPlayerHit(Global::getPlayerActor(args.playerNo),args.dir);
			}
			playerCollideDelays.remove(0);
		}
		GameElement::Update(gameTime);
		if(!held)
		{
			if(accelGrav)
			{
				yvelocity+=weight;
			}
			else
			{
				yvelocity = weight;
			}
			Global::currentStage->itemPlatformCollisions(this);
		}
		for(int j=0; j<=Global::possPlayers; j++)
		{
			if(Global::characters[j]!=null)
			{
				checkPlayerCollision(Global::characters[j]);
			}
		}
		if(held)
		{
			if(bound)
			{
				Player*playr = getPlayer();
				if(playr!=null)
				{
					switch(playr->getPlayerDir())
					{
						case Player::LEFT:
						x = playr->x - (float)((playr->itemOffsetX + offsetX)*playr->getScale());
						break;
						
						case Player::RIGHT:
						x = playr->x + (float)((playr->itemOffsetX + offsetX)*playr->getScale());
						break;
					}
					y = playr->y + (float)((playr->itemOffsetY + offsetY)*playr->getScale());
				}
			}
		}
		if(Global::getWorldTime() >= finishTime && !held)
		{
			destroy();
		}
		RectF borders = Global::currentStage->getBorders();
		float left = Global::currentStage->x + borders.left;
		float top = Global::currentStage->y + borders.top;
		float right = Global::currentStage->x + borders.right;
		float bottom = Global::currentStage->y + borders.bottom;
		if((x+width/2)<left || (x-width/2)>right || (y+height/2)<top || (y-height/2)>bottom)
		{
			destroy();
		}
	}

	void Item::Draw(Graphics2D&g, long gameTime)
	{
		if(held && bound)
		{
			Player*playr = getPlayer();
			if(playr!=null)
			{
				switch(playr->getPlayerDir())
				{
					case Player::LEFT:
					x = playr->x - (float)((playr->itemOffsetX + offsetX)*playr->getScale());
					break;
					
					case Player::RIGHT:
					x = playr->x + (float)((playr->itemOffsetX + offsetX)*playr->getScale());
				}
				y = playr->y + (float)((playr->itemOffsetY + offsetY)*playr->getScale());
			}
		}
		GameElement::Draw(g, gameTime);
	}
	
	void Item::checkPlayerCollision(Player*playr)
	{
		boolean colliding = false;
		boolean pxlColliding = false;
		byte pxlDir = 0;
		if(isSolid)
		{
			byte dir = 0;
			if(held)
			{
				dir = isColliding2(playr);
			}
			else
			{
				dir = solidElementCollision(playr);
			}
			if(dir>0)
			{
				colliding = true;
				if(hitState)
				{
					pxlColliding = true;
					pxlDir = dir;
				}
			}
		}
		else
		{
			if(Actor::rectsColliding(playr->getHitbox()))
			{
				colliding = true;
			}
			if(hitState)
			{
				pxlDir = isColliding2(playr);
				if(pxlDir>0)
				{
					pxlColliding = true;
				}
			}
		}
		if(colliding)
		{
			if(playerCollisions.isColliding(playr->playerNo))
			{
				whilePlayerColliding(playr);
			}
			else
			{
				onPlayerCollide(playr);
			}
			playerCollisions.addCollision(playr->playerNo);
			
			if(canCarry)
			{
				playr->itemCollidingIndex=this->index;
			}
		}
		else
		{
			if(playerCollisions.isColliding(playr->playerNo))
			{
				playerCollisions.removeCollision(playr->playerNo);
				finishPlayerCollide(playr);
			}
		}
		
		if(pxlColliding && hitState && holderNo != playr->getPlayerNo())
		{
			if(playerHits.isColliding(playr->playerNo))
			{
				if(isHittable(playr))
				{
					whilePlayerHitting(playr, pxlDir);
				}
			}
			else
			{
				if(isHittable(playr))
				{
					byte pDir = 0;
					switch(pxlDir)
					{
						case PrimitiveActor::DIR_DOWN:
						pDir = PrimitiveActor::DIR_UP;
						break;
						
						case PrimitiveActor::DIR_UP:
						pDir = PrimitiveActor::DIR_DOWN;
						break;
						
						case PrimitiveActor::DIR_LEFT:
						pDir = PrimitiveActor::DIR_RIGHT;
						break;
						
						case PrimitiveActor::DIR_RIGHT:
						pDir = PrimitiveActor::DIR_LEFT;
						break;
					}
					if(!(deflectable && playr->onDeflectItemCollision(this, pDir)))
					{
						if(allowsGrabDelay())
						{
							PlayerCollisionArgs args;
							args.playerNo = playr->getPlayerNo();
							args.dir = pxlDir;
							playerCollideDelays.add(args);
						}
						else
						{
							onPlayerHit(playr, pxlDir);
						}
						playerHits.addCollision(playr->playerNo);
					}
				}
			}
		}
		else if(hitState && playerHits.isColliding(playr->playerNo))
		{
			finishPlayerHit(playr);
			playerHits.removeCollision(playr->playerNo);
		}
	}

	void Item::destroy()
	{
		if(!dead && P2PDataManager::isEnabled())
		{
			ItemManager::destroyedItems.add(this->id);
		}
		dead = true;
		setVisible(false);
	}

	void Item::createProjectile(Projectile*p)
	{
		ProjectileManager::AddProjectile(p);
	}

	void Item::setHitState(boolean toggle)
	{
		hitState = toggle;
		if(!toggle)
		{
			playerHits.clear();
		}
	}
	
	void Item::setCollideType(byte type)
	{
		collideType = type;
	}

	void Item::accelerateGravity(boolean toggle)
	{
		accelGrav = toggle;
	}
	
	void Item::enableTossOnDiscard(boolean toggle)
	{
		tossOnDiscard = toggle;
	}
	
	boolean Item::isHittable(Player*collide)
	{
		byte team = 0;
		
		Player*playr = getPlayer();
		if(playr!=null)
		{
			team = playr->getTeam();
		}
		
		if((collide->getPlayerNo()>0)&&!((Global::teamBattle)&&(team>0)&&(team==collide->getTeam()))
		   &&(!held || (held && holderNo!=collide->getPlayerNo()))&&(!collide->isInvincible()))
		{
			return true;
		}
		return false;
	}
	
	void Item::causeDamage(Player*collide, int amount)
	{
		boolean canInflict = true;
		if(collide->attacksPriority==5)
		{
			collide->updateHitbox();
			switch(collide->playerdir)
			{
				case Player::LEFT:
				if(x<collide->x && PrimitiveActor::getDir(collide,this)==PrimitiveActor::DIR_LEFT)
				{
					boolean inflicted = false;
					if(deflectable)
					{
						inflicted = collide->onDeflectItemDamage(this, amount);
					}
					if(inflicted)
					{
						canInflict = false;
						collide->deflectState = true;
					}
				}
				break;
				
				case Player::RIGHT:
				if(x>collide->x && PrimitiveActor::getDir(collide,this)==PrimitiveActor::DIR_RIGHT)
				{
					boolean inflicted = false;
					if(deflectable)
					{
						inflicted = collide->onDeflectItemDamage(this, amount);
					}
					if(inflicted)
					{
						canInflict = false;
						collide->deflectState = true;
					}
				}
				break;
			}
		}
		else if(collide->attacksPriority==6)
		{
			boolean inflicted = false;
			if(deflectable)
			{
				inflicted = collide->onDeflectItemDamage(this, amount);
			}
			if(inflicted)
			{
				canInflict = false;
				collide->deflectState = true;
			}
		}
		if(canInflict)
		{
			collide->percent+=amount;
			if(collide->percent>999)
			{
				collide->percent=999;
			}
		}
	}
	
	void Item::causeHurtLaunch(Player*collide, int xDir, float xAmount, float xMult, int yDir, float yAmount, float yMult)
	{
		if(collide->deflectState)
		{
			collide->onDeflectItemLaunch(this, xDir, xAmount, xMult, yDir, yAmount, yMult);
		}
		else
		{
			if(collide->holdingPlayer)
			{
				collide->releasePlayer();
			}
			
		    //float oldXvel;
		    //float oldYvel;
		    float newyVel=(float)(yDir*(yAmount+(yMult*(collide->percent))/75));
		    float newxVel=(float)(xDir*(xAmount+(xMult*(collide->percent))/75));
		    //Console.WriteLine(this.attacksHolder + ": " + newyVel + "");
		    if(newyVel>0)
		    {
		        if(newyVel>collide->yvelocity)
		        {
		            collide->yvelocity=newyVel;
		        }
		    }
		    else if(newyVel<0)
		    {
		        if(newyVel<collide->yvelocity)
		        {
		            collide->yvelocity=newyVel;
		        }
		    }
		    if(newxVel>0)
		    {
		        if(newxVel>collide->xvelocity)
		        {
		            collide->xvelocity=newxVel;
		        }
		    }
		    else if(newxVel<0)
		    {
		        if(newxVel<collide->xvelocity)
		        {
		            collide->xvelocity=newxVel;
		        }
		    }
		    collide->y-=1;
		    if(collide->yvelocity>0 && collide->isOnGround())
		    {
		    	collide->yvelocity = -(collide->yvelocity/2);
		    }
		}
	}

	void Item::causeHurt(Player*collide, byte dir, int time)
	{
		if(collide->deflectState)
		{
			collide->deflectState = false;
		}
		else
		{
			if(std::abs(collide->xvelocity)<=3)
			{
				if(std::abs(collide->yvelocity)<=3)
				{
					collide->changeTwoSidedAnimation("hurt_minor", FORWARD, dir);
				}
				else if((std::abs(collide->yvelocity)>3)&&(std::abs(collide->yvelocity)<7))
				{
					collide->changeTwoSidedAnimation("hurt_minor", FORWARD, dir);
				}
				else if((std::abs(collide->yvelocity)>=7)&&(std::abs(collide->yvelocity)<12))
				{
					collide->changeTwoSidedAnimation("hurt_flip", FORWARD, dir);
				}
				else if(std::abs(collide->yvelocity)>=12)
				{
					collide->changeAnimation("hurt_spin_up", FORWARD);
				}
			}
			else if((std::abs(collide->xvelocity)>3)&&(std::abs(collide->xvelocity)<7))
			{
				if(std::abs(collide->yvelocity)<=3)
				{
					collide->changeTwoSidedAnimation("hurt_fly", FORWARD, dir);
				}
				else if((std::abs(collide->yvelocity)>3)&&(std::abs(collide->yvelocity)<7))
				{
					collide->changeTwoSidedAnimation("hurt_minor", FORWARD, dir);
				}
				else if((std::abs(collide->yvelocity)>=7)&&(std::abs(collide->yvelocity)<12))
				{
					collide->changeTwoSidedAnimation("hurt_fly", FORWARD, dir);
				}
				else if(std::abs(collide->yvelocity)>=12)
				{
					collide->changeTwoSidedAnimation("hurt_flip", FORWARD, dir);
				}
			}
			else if(std::abs(collide->xvelocity)>=7)
			{
				if(std::abs(collide->yvelocity)<=3)
				{
					collide->changeTwoSidedAnimation("hurt_spin", FORWARD, dir);
				}
				else if((std::abs(collide->yvelocity)>3)&&(std::abs(collide->yvelocity)<7))
				{
					collide->changeTwoSidedAnimation("hurt_spin", FORWARD, dir);
				}
				else if((std::abs(collide->yvelocity)>=7)&&(std::abs(collide->yvelocity)<12))
				{
					collide->changeTwoSidedAnimation("hurt_spin", FORWARD, dir);
				}
				else if(std::abs(collide->yvelocity)>=12)
				{
					collide->changeTwoSidedAnimation("hurt_flip", FORWARD, dir);
				}
			}
		    collide->xVel=0;
		    collide->yVel=0;
		    collide->attackTime=0;
		    collide->chargingAttack=false;
		    collide->bUp=false;
		    collide->up=false;
		    collide->hurt=2;
		    collide->landing=false;
		    collide->jumping=false;
			collide->tossing=false;
			collide->grabbing=false;
		    //collide->moveLeft=0;
		    //collide->moveRight=0;
		    collide->hanging=false;
		    collide->attacksHolder=-1;
		    collide->attacksPriority=0;
		    collide->canDo=false;
		    collide->hurtTime=Global::worldTime+time;
		    collide->hurtFrame=4;
		    collide->runTime=0;
		    collide->chargeSmash=0;
			collide->destroyCharge();
			collide->setToDefaultValues();
			
		    if(holderNo>0)
		    {
		    	collide->lastHit = holderNo;
		    }
		    else if(ownerNo>0)
		    {
		    	collide->lastHit = ownerNo;
		    }
		    
		    if(collide->itemHolding!=null)
		    {
		        collide->itemHolding->onHolderHurt();
		    }
		    /*if(itemActor->itemOwner>0)
		    {
		        collide.lastHit=itemOwner;
		    }*/
		}
	}

	byte Item::solidPlatformCollision(Platform*collide)
	{
		if(getScale()==0 || collide->getScale()==0)
		{
			return 0;
		}
		
		if(collideType==COLLIDE_SOLID)
		{
			//Rectangle rect = this.grid.getAreaRect();
			GameEngine::Rectangle r1 = GameEngine::Rectangle((int)(x-(float)width/2), (int)(y-(float)height/2), width, height);
			GameEngine::Rectangle r2 = GameEngine::Rectangle((int)(collide->x - collide->width/2),(int)(collide->y - collide->height/2),collide->width,collide->height);
			GameEngine::Rectangle collideOverlap = getOverlapRect(r2,r1);
			GameEngine::Rectangle overlap = getOverlapRect(r1,r2);
			
			if(collideOverlap.x!=-1)
			{
				int startX2 = collideOverlap.x;
				int endX2 = collideOverlap.x + collideOverlap.width;
				int startY2 = collideOverlap.y;
				int endY2 = collideOverlap.y + collideOverlap.height;
				
				int left1=0;
				int right1=0;
				int top1=0;
				int bottom1=0;
				
				int left2=0;
				int right2=0;
				int top2=0;
				int bottom2=0;
				
				int left2_1=0;
				int right2_1=0;
				int top2_1=0;
				int bottom2_1=0;
				
				int startX1 = overlap.x;
				int startY1 = overlap.y;
				
				int xPnt = startX1; // bounds checker for this
				int yPnt = startY1;
				
				float x1 = ((float)startX1/getScale());//pixel checker starter for this
				float y1 = ((float)startY1/getScale());
				float incr1 = (float)(1/getScale());
				
				float x2 = ((float)startX2/collide->getScale());//pixel checker starter for collide
				float y2 = ((float)startY2/collide->getScale());
				float incr2 = (float)(1/collide->getScale());
				
				boolean itemCol = false;
				boolean colliding = false;
				boolean anyCol = false;

				PixelIterator pxlIter(this);
				pxlIter.reset(x1,y1,incr1,incr1,(int)collideOverlap.width,(int)collideOverlap.height);
				PixelIterator colPxlIter(collide);
				colPxlIter.reset(x2,y2,incr2,incr2,(int)collideOverlap.width,(int)collideOverlap.height);
				
				for(int cntY=startY2; cntY<endY2; cntY++)
				{
					xPnt = startX1;
					for(int cntX=startX2; cntX<endX2; cntX++)
					{
						boolean atPoint = pxlIter.checkNextPixel();
						boolean collideAtPoint = colPxlIter.checkNextPixel();
						if(atPoint)
						{
							if(!itemCol)
							{
								left1 = xPnt;
								right1 = xPnt;
								top1 = yPnt;
								bottom1 = yPnt;
							}
							else
							{
								if(xPnt<left1)
								{
									left1 = xPnt;
								}
								else if(xPnt>right1)
								{
									right1 = xPnt;
								}
								if(yPnt<top1)
								{
									top1 = yPnt;
								}
								else if(yPnt>bottom1)
								{
									bottom1 = yPnt;
								}
							}
							itemCol = true;
							
							if(collideAtPoint)
							{
								if(!colliding)
								{
									left2 = cntX;
									right2 = cntX;
									top2 = cntY;
									bottom2 = cntY;
								}
								else
								{
									if(cntX<left2)
									{
										left2 = cntX;
									}
									else if(cntX>right2)
									{
										right2 = cntX;
									}
									if(cntY<top2)
									{
										top2 = cntY;
									}
									else if(cntY>bottom2)
									{
										bottom2 = cntY;
									}
								}
								colliding = true;
							}
						}
						if(collideAtPoint)
						{
							if(!anyCol)
							{
								left2_1 = cntX;
								right2_1 = cntX;
								top2_1 = cntY;
								bottom2_1 = cntY;
							}
							else
							{
								if(cntX<left2_1)
								{
									left2_1 = cntX;
								}
								else if(cntX>right2_1)
								{
									right2_1 = cntX;
								}
								if(cntY<top2_1)
								{
									top2_1 = cntY;
								}
								else if(cntY>bottom2_1)
								{
									bottom2_1 = cntY;
								}
							}
							anyCol = true;
						}
						xPnt++;
					}
					yPnt++;
				}
				
				if(colliding)
				{
					int w2 = (int)(right2 - left2);
					int h2 = (int)(bottom2 - top2);
					int w2_1 = (int)(right2_1 - left2_1);
					int h2_1 = (int)(bottom2_1 - top2_1);
					GameEngine::Rectangle collideOverlap2 = GameEngine::Rectangle((int)left2, top2, w2, h2);
					int overlapX = (int)(left2_1 - startX2) + overlap.x + (w2_1/2);
					int overlapY = (int)(top2_1 - startY2) + overlap.y + (h2_1/2);
					byte dir = getDir2((float)width/2,(float)height/2,(float)overlapX, (float)overlapY);
					
					byte type = collide->getType();
					if((type == Platform::TYPE_NORMAL)||(type == Platform::TYPE_GOTHROUGH && !ignoreGoThrough && dir == DIR_DOWN))
					{
						switch(dir)
						{
							case DIR_DOWN:
							y = (collideOverlap2.y + (collide->y - collide->height/2)) - (float)(bottom1 - (height/2)) + 1;
							return DIR_UP;
							
							case DIR_UP:
							y = ((collide->y - collide->height/2) + (collideOverlap2.y + collideOverlap2.height)) + (float)((height/2) - top1) + 1;
							return DIR_DOWN;
							
							case DIR_LEFT:
							x = ((collide->x - collide->width/2) + (collideOverlap2.x + collideOverlap2.width)) + (float)((right1) - (width/2));
							xvelocity = 0;
							return DIR_RIGHT;
							
							case DIR_RIGHT:
							x = (collideOverlap2.x + (collide->x - collide->width/2)) - (float)((width/2) - left1);
							xvelocity = 0;
							return DIR_LEFT;
						}
					}
				}
			}
		}
		else if(collideType == COLLIDE_BOX)
		{
			GameEngine::Rectangle r1 = GameEngine::Rectangle((int)x-width/2, (int)y-height/2, width, height);
			GameEngine::Rectangle r2 = GameEngine::Rectangle((int)(collide->x - collide->width/2),(int)(collide->y - collide->height/2),collide->width,collide->height);
			GameEngine::Rectangle collideOverlap = getOverlapRect(r2,r1);
			GameEngine::Rectangle overlap = getOverlapRect(r1,r2);
			
			if(collideOverlap.x!=-1)
			{
				int startX = collideOverlap.x;
				int endX = collideOverlap.x + collideOverlap.width;
				int startY = collideOverlap.y;
				int endY = collideOverlap.y + collideOverlap.height;
				
				int left=0;
				int right=0;
				int top=0;
				int bottom=0;
				boolean colliding = false;
				
				float x2 = ((float)startX/collide->getScale());//pixel checker starter for collide
				float y2 = ((float)startY/collide->getScale());
				float incr2 = (float)(1/collide->getScale());
				
				PixelIterator colPxlIter(collide);
				colPxlIter.reset(x2,y2,incr2,incr2,(int)collideOverlap.width,(int)collideOverlap.height);
				
				for(int cntY=startY; cntY<endY; cntY++)
				{
					for(int cntX=startX; cntX<endX; cntX++)
					{
						if(colPxlIter.checkNextPixel())
						{
							if(!colliding)
							{
								left = cntX;
								right = cntX;
								top = cntY;
								bottom = cntY;
							}
							else
							{
								if(cntX<left)
								{
									left = cntX;
								}
								else if(cntX>right)
								{
									right = cntX;
								}
								if(cntY<top)
								{
									top = cntY;
								}
								else if(cntY>bottom)
								{
									bottom = cntY;
								}
							}
							colliding = true;
						}
					}
				}
				
				if(colliding)
				{
					int w = right - left;
					int h = bottom - top;
					GameEngine::Rectangle collideOverlap2 = GameEngine::Rectangle(left, top, w, h);
					int overlapX = (left - startX) + overlap.x + (w/2);
					int overlapY = (top - startY) + overlap.y + (h/2);
					byte dir = getDir2((float)width/2,(float)height/2,(float)overlapX, (float)overlapY);
					
					byte type = collide->getType();
					if((type == Platform::TYPE_NORMAL)||(type == Platform::TYPE_GOTHROUGH && !ignoreGoThrough && dir == DIR_DOWN))
					{
						switch(dir)
						{
							case DIR_DOWN:
							y = (collideOverlap2.y + (collide->y - (float)collide->height/2)) - ((float)height/2) + 1;
							return DIR_UP;
							
							case DIR_UP:
							y = ((collide->y - collide->height/2) + (collideOverlap2.y + collideOverlap2.height)) + height/2 -  + height/2;
							return DIR_DOWN;
							
							case DIR_LEFT:
							x = ((collide->x - collide->width/2) + (collideOverlap2.x + collideOverlap2.width) + width/2);
							return DIR_RIGHT;
							
							case DIR_RIGHT:
							x = (collideOverlap2.x + (collide->x - collide->width/2)) - width/2;
							return DIR_LEFT;
						}
					}
				}
			}
		}
		return 0;
	}
	
	byte Item::normalPlatformCollision(Platform*collide)
	{
		if(getScale()==0 || collide->getScale()==0)
		{
			return 0;
		}
		
		if(collideType == COLLIDE_SOLID)
		{
			//Rectangle rect = this.grid.getAreaRect();
			GameEngine::Rectangle r1 = GameEngine::Rectangle((int)(x-(float)width/2), (int)(y-(float)height/2), width, height);
			WireframeActor*collideBox = collide->getBox();
			GameEngine::Rectangle r2 = GameEngine::Rectangle((int)collideBox->x,(int)collideBox->y,collideBox->width,collideBox->height);
			GameEngine::Rectangle overlap = getOverlapRect(r1,r2);
			if(overlap.x!=-1)
			{
				int left=0;
				int right=0;
				int top=0;
				int bottom=0;
				
				int startX = overlap.x;
				int startY = overlap.y;
				int endX = overlap.x + overlap.width;
				int endY = overlap.y + overlap.height;
				
				float x1 = ((float)startX/getScale());//pixel checker starter for this
				float y1 = ((float)startY/getScale());
				float incr1 = (float)(1/getScale());
				
				boolean itemCol = false;

				PixelIterator pxlIter(this);
				pxlIter.reset(x1,y1,incr1,incr1,(int)overlap.width,(int)overlap.height);
				
				for(int cntY=startY; cntY<endY; cntY++)
				{
					for(int cntX=startX; cntX<endX; cntX++)
					{
						if(pxlIter.checkNextPixel())
						{
							if(!itemCol)
							{
								left = cntX;
								right = cntX;
								top = cntY;
								bottom = cntY;
							}
							else
							{
								if(cntX<left)
								{
									left = cntX;
								}
								else if(cntX>right)
								{
									right = cntX;
								}
								if(cntY<top)
								{
									top = cntY;
								}
								else if(cntY>bottom)
								{
									bottom = cntY;
								}
							}
							itemCol = true;
						}
					}
				}
				
				if(!itemCol)
				{
					return 0;
				}
				
				byte dir = getDir(r2,r1);
				switch(dir)
				{
					case DIR_UP:
					y = (collideBox->y - (float)(bottom - (height/2)));
					return DIR_UP;
					
					case DIR_DOWN:
					if(collide->getType()!=Platform::TYPE_GOTHROUGH)
					{
						y=(collideBox->y+collideBox->height) + (float)((height/2) - top);
					}
					return DIR_DOWN;
					
					case DIR_UPLEFT:
					case DIR_DOWNLEFT:
					case DIR_LEFT:
					if(collide->getType()!=Platform::TYPE_GOTHROUGH)
					{
						x = collideBox->x - (float)((width/2) - left);
					}
					return DIR_LEFT;
					
					case DIR_UPRIGHT:
					case DIR_DOWNRIGHT:
					case DIR_RIGHT:
					if(collide->getType()!=Platform::TYPE_GOTHROUGH)
					{
						x = (collideBox->x + collideBox->width) + (float)(right - (width/2));
					}
					return DIR_RIGHT;
				}
			}
		}
		else if(collideType == COLLIDE_BOX)
		{
			GameEngine::Rectangle rect = GameEngine::Rectangle((int)(x - (float)width/2),(int)(y - (float)height/2), width, height);
			WireframeActor*collideBox = collide->getBox();
			GameEngine::Rectangle rect2 = GameEngine::Rectangle((int)collideBox->x,(int)collideBox->y,collideBox->width,collideBox->height);
			byte dir = getDir(rect2,rect);
			switch(dir)
			{
				case DIR_UP:
				y = ((float)collideBox->y - ((float)((float)rect.height - (y - (float)rect.y)))  + 1);
				yvelocity=0;
				return DIR_UP;
				
				case DIR_DOWN:
				if(collide->getType()!=Platform::TYPE_GOTHROUGH)
				{
					y=(collideBox->y+collideBox->height - (float)((float)(-(y - rect.y))));
				}
				return DIR_DOWN;
				
				case DIR_UPLEFT:
				case DIR_DOWNLEFT:
				case DIR_LEFT:
				if(collide->getType()!=Platform::TYPE_GOTHROUGH)
				{
					x = (collideBox->x - (float)(((float)rect.width)/2));
				}
				return DIR_LEFT;
				
				case DIR_UPRIGHT:
				case DIR_DOWNRIGHT:
				case DIR_RIGHT:
				if(collide->getType()!=Platform::TYPE_GOTHROUGH)
				{
					x = (collideBox->x + collideBox->width + (float)(((float)rect.width)/2));
				}
				return DIR_RIGHT;
			}
		}
		return 0;
	}
}