#include "Projectile.h"
#include "Global.h"
#include "Player.h"
#include "Platform.h"
#include "ProjectileManager.h"
#include "Item.h"
#include "P2PDataManager.h"

namespace SmashBros
{
	int Projectile::nextID = 0;
	
	Projectile::Projectile(byte playerNo, float x1, float y1) : GameElement(x1,y1)
	{
		this->id = nextID;
		nextID++;
		if(nextID == INTEGER_MAX)
		{
			nextID = 0;
		}
		while(!ProjectileManager::checkIDAvailable(nextID))
		{
			nextID++;
			if(nextID == INTEGER_MAX)
			{
				nextID = 0;
			}
		}
		dead = false;
		itemdir = 0;
		team = 0;
		solid = false;
		solidOwner = true;
		this->playerNo = playerNo;
		playersColliding = CollisionManager();
		Player*owner = Global::getPlayerActor(playerNo);
		itemdir=owner->playerdir;
		team=owner->getTeam();
		layer = LAYER_MIDDLEUPPER;
		
		platform = new Platform(Platform::TYPE_GOTHROUGH, x, y, 1, 1);
	}
	
	Projectile::~Projectile()
	{
		if(!dead && P2PDataManager::isEnabled())
		{
			ProjectileManager::destroyedProjectiles.add(this->id);
		}
		dead = true;
		delete platform;
	}
	
	int Projectile::getID()
	{
		return this->id;
	}
	
	void Projectile::setNextID(int projID)
	{
		nextID = projID;
	}
	
	//x, y, animIndex, frame, bools, layer, playerNo, team
	//4, 4, 4,         4,     1      1      1         1    = 20
	void Projectile::handleAddP2PData(DataVoid&data)
	{
		int frame = getAnimation()->getCurrentFrame();
		int animIndex = getAnimIndex();
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
		data.add(&boolsByte, sizeof(boolsByte));
		data.add(&layer, sizeof(layer));
		data.add(&playerNo, sizeof(playerNo));
		data.add(&team, sizeof(team));
		
		DataVoid newData;
		addP2PData(newData);
		data.add(newData);
	}
	
	void Projectile::handleSetP2PData(byte*&data)
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
		
		//layer
		layer = data[0];
		data += sizeof(byte);
		
		//playerNo
		playerNo = data[0];
		data += sizeof(byte);
		
		//team
		team = data[0];
		data += sizeof(byte);
		
		setP2PData(data);
	}
	
	void Projectile::addP2PData(DataVoid&data)
	{
		//Open for implementation
	}
	
	void Projectile::setP2PData(byte*&data)
	{
		//Open for implementation
	}
	
	void Projectile::Update(long gameTime)
	{
		Rect borders = Global::currentStage->getBorders();
		int left = Global::currentStage->x + borders.left;
		int top = Global::currentStage->y + borders.top;
		int right = Global::currentStage->x + borders.right;
		int bottom = Global::currentStage->y + borders.bottom;
		if((x+width/2)<left || (x-width/2)>right || (y+height/2)<top || (y-height/2)>bottom)
		{
			destroy();
		}
		platform->Update(gameTime);
		platform->x = x;
		platform->y = y;
		GameElement::Update(gameTime);
	}

	void Projectile::Draw(Graphics2D&g, long gameTime)
	{
		GameElement::Draw(g,gameTime);
	}

	byte Projectile::getTeam()
	{
		return team;
	}

	byte Projectile::getItemDir()
	{
		return itemdir;
	}

	byte Projectile::getPlayerNo()
	{
		return playerNo;
	}

	boolean Projectile::isDead()
	{
		return dead;
	}

	void Projectile::setSolid(boolean toggle)
	{
		solid = toggle;
	}
	
	boolean Projectile::isSolid()
	{
		return solid;
	}
	
	void Projectile::setOwnerSolid(boolean toggle)
	{
		solidOwner = toggle;
	}
	
	boolean Projectile::isOwnerSolid()
	{
		return solidOwner;
	}
	
	void Projectile::destroy()
	{
		if(!dead && P2PDataManager::isEnabled())
		{
			ProjectileManager::destroyedProjectiles.add(this->id);
		}
		dead = true;
		setVisible(false);
	}
	
	void Projectile::setLayer(byte layer)
	{
		this->layer = layer;
	}
	
	boolean Projectile::isHittable(Player*collide, byte dir)
	{
		if((collide->getPlayerNo()>0)&&!((Global::teamBattle)&&(team==collide->getTeam()))
	    &&(playerNo!=collide->getPlayerNo())&&(!collide->isInvincible()))
	    {
	    	if(collide->attacksPriority<5)
	    	{
	    		if(collide->attacksPriority > 3)
	    		{
		    		if(collide->playerdir==LEFT && x<collide->x)
		    		{
		    			return false;
		    		}
		    		else if(collide->playerdir==RIGHT && x>collide->x)
		    		{
		    			return false;
		    		}
	    		}
	    	}
	    	return true;
	    }
	    return false;
	}

	void Projectile::createProjectile(Projectile*p)
	{
		ProjectileManager::AddProjectile(p);
	}

	void Projectile::causeDamage(Player*collide, int amount)
	{
		boolean canInflict = true;
		if(collide->attacksPriority==5)
		{
			collide->updateHitbox();
			switch(collide->playerdir)
			{
				case Player::LEFT:
				if(x<collide->x && PrimitiveActor::getDir((PrimitiveActor*)collide->getHitbox(),(PrimitiveActor*)this)!=PrimitiveActor::DIR_LEFT)
				{
					boolean inflicted = collide->onProjectileDeflectDamage(this, amount);
					if(inflicted)
					{
						canInflict = false;
						collide->deflectState = true;
					}
				}
				break;
				
				case Player::RIGHT:
				if(x>collide->x && PrimitiveActor::getDir((PrimitiveActor*)collide,(PrimitiveActor*)this)!=PrimitiveActor::DIR_RIGHT)
				{
					boolean inflicted = collide->onProjectileDeflectDamage(this, amount);
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
			boolean inflicted = collide->onProjectileDeflectDamage(this, amount);
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

	void Projectile::causeHurtLaunch(Player*collide, int xDir, float xAmount, float xMult, int yDir, float yAmount, float yMult)
	{
		if(collide->deflectState)
		{
			collide->onProjectileDeflectLaunch(this, xDir, xAmount, xMult, yDir, yAmount, yMult);
		}
		else
		{
		    //float oldXvel;
		    //float oldYvel;
		    float newyVel=(float)(yDir*(yAmount+(yMult*(collide->percent))/100));
		    float newxVel=(float)(xDir*(xAmount+(xMult*(collide->percent))/100));
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

	void Projectile::causeHurt(Player*collide, byte dir, int time)
	{
		if(!collide->deflectState)
		{
		    if(abs(collide->xvelocity)<=3)
		    {
		        if(abs(collide->yvelocity)<=3)
		        {
		            switch(dir)
		            {
						case Player::LEFT:
		                collide->changeAnimation("hurt_minor_left", FORWARD);
		                break;
		 
						case Player::RIGHT:
		                collide->changeAnimation("hurt_minor_right", FORWARD);
		                break;
		            }
		        }
		        else if((abs(collide->yvelocity)>3)&&(abs(collide->yvelocity)<7))
		        {
		            switch(dir)
		            {
						case Player::LEFT:
		                collide->changeAnimation("hurt_minor_left", FORWARD);
		                break;
		 
						case Player::RIGHT:
		                collide->changeAnimation("hurt_minor_right", FORWARD);
		                break;
		            }
		        }
		        else if((abs(collide->yvelocity)>=7)&&(abs(collide->yvelocity)<12))
		        {
		            switch(dir)
		            {
						case Player::LEFT:
		                collide->changeAnimation("hurt_flip_left", FORWARD);
		                break;
		 
						case Player::RIGHT:
		                collide->changeAnimation("hurt_flip_left", FORWARD);
		                break;
		            }
		        }
		        else if(abs(collide->yvelocity)>=12)
		        {
		            collide->changeAnimation("hurt_spin_up", FORWARD);
		        }
		    }
		 
		    else if((abs(collide->xvelocity)>3)&&(abs(collide->xvelocity)<7))
		    {
		        if(abs(collide->yvelocity)<=3)
		        {
		            switch(dir)
		            {
						case Player::LEFT:
		                collide->changeAnimation("hurt_fly_left", FORWARD);
		                break;
		 
						case Player::RIGHT:
		                collide->changeAnimation("hurt_fly_right", FORWARD);
		                break;
		            }
		        }
		        else if((abs(collide->yvelocity)>3)&&(abs(collide->yvelocity)<7))
		        {
		            switch(dir)
		            {
						case Player::LEFT:
		                collide->changeAnimation("hurt_minor_left", FORWARD);
		                break;
		 
						case Player::RIGHT:
		                collide->changeAnimation("hurt_minor_right", FORWARD);
		                break;
		            }
		        }
		        else if((abs(collide->yvelocity)>=7)&&(abs(collide->yvelocity)<12))
		        {
		            switch(dir)
		            {
						case Player::LEFT:
		                collide->changeAnimation("hurt_fly_left", FORWARD);
		                break;
		 
						case Player::RIGHT:
		                collide->changeAnimation("hurt_fly_right", FORWARD);
		                break;
		            }
		        }
		        else if(abs(collide->yvelocity)>=12)
		        {
		            switch(dir)
		            {
						case Player::LEFT:
		                collide->changeAnimation("hurt_flip_left", FORWARD);
		                break;
		 
						case Player::RIGHT:
		                collide->changeAnimation("hurt_flip_right", FORWARD);
		                break;
		            }
		        }
		    }
		 
		    else if(abs(collide->xvelocity)>=7)
		    {
		        if(abs(collide->yvelocity)<=3)
		        {
		            switch(dir)
		            {
						case Player::LEFT:
		                collide->changeAnimation("hurt_spin_left", FORWARD);
		                break;
		 
						case Player::RIGHT:
		                collide->changeAnimation("hurt_spin_right", FORWARD);
		                break;
		            }
		        }
		        else if((abs(collide->yvelocity)>3)&&(abs(collide->yvelocity)<7))
		        {
		            switch(dir)
		            {
						case Player::LEFT:
		                collide->changeAnimation("hurt_spin_left", FORWARD);
		                break;
		 
						case Player::RIGHT:
		                collide->changeAnimation("hurt_spin_right", FORWARD);
		                break;
		            }
		        }
		        else if((abs(collide->yvelocity)>=7)&&(abs(collide->yvelocity)<12))
		        {
		            switch(dir)
		            {
						case Player::LEFT:
		                collide->changeAnimation("hurt_spin_left", FORWARD);
		                break;
		 
						case Player::RIGHT:
		                collide->changeAnimation("hurt_spin_right", FORWARD);
		                break;
		            }
		        }
		        else if(abs(collide->yvelocity)>=12)
		        {
		            switch(dir)
		            {
						case Player::LEFT:
		                collide->changeAnimation("hurt_flip_left", FORWARD);
		                break;
		 
						case Player::RIGHT:
		                collide->changeAnimation("hurt_flip_right", FORWARD);
		                break;
		            }
		        }
		    }
		    collide->xVel=0;
		    collide->yVel=0;
		    collide->attackTime=0;
		    collide->setToDefaultValues();
		    collide->chargingAttack=false;
		    collide->bUp=false;
		    collide->up=false;
		    collide->hurt=2;
		    collide->landing=false;
		    collide->jumping=false;
		    collide->moveLeft=0;
		    collide->moveRight=0;
		    collide->hanging=false;
		    collide->attacksHolder=-1;
		    collide->attacksPriority=0;
		    collide->canDo=false;
		    collide->hurtTime=Global::worldTime+time;
		    collide->hurtFrame=4;
		    collide->runTime=0;
		    collide->chargeSmash=0;
		    collide->lastHit = this->playerNo;
		    
		    collide->destroyCharge();
		    
		    if(collide->itemHolding!=null)
		    {
		        collide->itemHolding->onHolderHurt();
		    }
		    /*if(itemActor->itemOwner>0)
		    {
		        collide->lastHit=itemOwner;
		    }*/
		}
	}

	void Projectile::onDestroy()
	{
		//
	}

	void Projectile::onPlayerHit(Player*collide, byte dir)
	{
		//
	}

	void Projectile::whilePlayerHitting(Player*collide, byte dir)
	{
		//
	}

	void Projectile::whileGroundColliding()
	{
		//
	}

	void Projectile::whilePlatformColliding(Platform*collide, byte dir)
	{
		//
	}

	byte Projectile::isPlatformColliding(Platform*collide)
	{
		GameEngine::Rectangle r1 = GameEngine::Rectangle((int)(x - (float)width/2), (int)(y - (float)height/2), (int)width, (int)height);
		GameEngine::Rectangle r2 = GameEngine::Rectangle((int)(collide->x - (float)collide->width/2),(int)(collide->y - (float)collide->height/2),(int)collide->width,(int)collide->height);
		GameEngine::Rectangle collideOverlap = getOverlapRect(r2,r1);
		GameEngine::Rectangle overlap = getOverlapRect(r1,r2);
		
		if(collideOverlap.x!=-1)
		{
			int startX = (int)collideOverlap.x;
			int endX = (int)(collideOverlap.x + collideOverlap.width);
			int startY = (int)collideOverlap.y;
			int endY = (int)(collideOverlap.y + collideOverlap.height);
			
			int left=0;
			int right=0;
			int top=0;
			int bottom=0;
			boolean colliding = false;
			
			float x2 = ((float)collideOverlap.x/collide->Scale);
			float y2 = ((float)collideOverlap.y/collide->Scale);
			float incr2 = (1/collide->Scale);
			
			PixelIterator colPxlIter(collide);
			colPxlIter.reset(x2,y2,incr2,incr2,(int)collideOverlap.width,(int)collideOverlap.height);
			
			for(int cntY=startY; cntY<endY; cntY++)
			{
				for(int cntX=startX; cntX<endX; cntX++)
				{
					boolean checker = false;
					
					checker = colPxlIter.checkNextPixel();
					
					if(checker)
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
				int overlapX = (int)((left - startX) + overlap.x + (w/2));
				int overlapY = (int)((top - startY) + overlap.y + (h/2));
				byte dir = getDir2((float)width/2,(float)height/2,(float)overlapX, (float)overlapY);
				
				byte type = collide->getType();
				if((type == Platform::TYPE_NORMAL)|| (type == Platform::TYPE_GOTHROUGH && dir == DIR_DOWN))
				{
					switch(dir)
					{
						case DIR_DOWN:
						return DIR_UP;
						
						case DIR_UP:
						return DIR_DOWN;
						
						case DIR_LEFT:
						return DIR_RIGHT;
						
						case DIR_RIGHT:
						return DIR_LEFT;
					}
				}
			}
		}
		return 0;
	}

	byte Projectile::solidPlatformCollision(Platform*collide)
	{
		if(collide->getCollideType() == Platform::COLLIDE_SOLID)
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
				
				int startX1 = overlap.x;
				int startY1 = overlap.y;
				
				int xPnt = startX1; // bounds checker for this
				int yPnt = startY1;
				
				float x1 = ((float)startX1/Scale);//pixel checker starter for this
				float y1 = ((float)startY1/Scale);
				float incr1 = (float)(1/Scale);
				
				float x2 = ((float)startX2/collide->Scale);//pixel checker starter for collide
				float y2 = ((float)startY2/collide->Scale);
				float incr2 = (float)(1/collide->Scale);
				
				boolean itemCol = false;
				
				boolean colliding = false;

				PixelIterator pxlIter(this);
				pxlIter.reset(x1,y1,incr1,incr1,(int)collideOverlap.width,(int)collideOverlap.height);
				PixelIterator colPxlIter(collide);
				colPxlIter.reset(x2,y2,incr2,incr2,(int)collideOverlap.width,(int)collideOverlap.height);
				
				for(int cntY=startY2; cntY<endY2; cntY++)
				{
					xPnt = startX1;
					for(int cntX=startX2; cntX<endX2; cntX++)
					{
						if(pxlIter.checkNextPixel())
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
						}
						if(colPxlIter.checkNextPixel())
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
						xPnt++;
					}
					yPnt++;
				}

				if(colliding)
				{
					int w = right2 - left2;
					int h = bottom2 - top2;
					GameEngine::Rectangle collideOverlap2 = GameEngine::Rectangle(left2, top2, w, h);
					int overlapX = (left2 - startX2) + overlap.x + (w/2);
					int overlapY = (top2 - startY2) + overlap.y + (h/2);
					byte dir = getDir2((float)width/2,(float)height/2,(float)overlapX, (float)overlapY);
					
					byte type = collide->getType();
					if((type == Platform::TYPE_NORMAL)||(type == Platform::TYPE_GOTHROUGH && dir == DIR_DOWN))
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
							x = ((collide->x - collide->width/2) + (collideOverlap2.x + collideOverlap2.width)) + (float)(right1 - (width/2));
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
		else if(collide->getCollideType() == Platform::COLLIDE_BOX)
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
				
				float x1 = ((float)startX/Scale);//pixel checker starter for this
				float y1 = ((float)startY/Scale);
				float incr1 = (float)(1/Scale);
				
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
						x = (collideBox->x + collideBox->width) + ((float)right - ((float)width/2));
					}
					return DIR_RIGHT;
				}
			}
		}
		return 0;
	}

	byte Projectile::solidPlayerCollision(Player*collide)
	{
		collide->updateHitbox();
		GameEngine::Rectangle r1 = GameEngine::Rectangle((int)collide->hitbox->x, (int)collide->hitbox->y, collide->hitbox->width, collide->hitbox->height);
		GameEngine::Rectangle r2 = GameEngine::Rectangle((int)(x - width/2),(int)(y - height/2),width,height);
		GameEngine::Rectangle collideOverlap = getOverlapRect(r2,r1);
		GameEngine::Rectangle overlap = getOverlapRect(r1,r2);
		
		if(collideOverlap.x!=-1)
		{
			int startX = collideOverlap.x;
			int endX = collideOverlap.x + collideOverlap.width;
			int startY = collideOverlap.y;
			int endY = collideOverlap.y + collideOverlap.height;
			
			float x2 = ((float)startX/Scale);
			float y2 = ((float)startY/Scale);
			float incr = (float)(1/Scale);
			
			int left=0;
			int right=0;
			int top=0;
			int bottom=0;
			boolean colliding = false;

			PixelIterator pxlIter(this);
			pxlIter.reset(x2,y2,incr,incr,(int)collideOverlap.width,(int)collideOverlap.height);
			
			for(int cntY=startY; cntY<endY; cntY++)
			{
				for(int cntX=startX; cntX<endX; cntX++)
				{
					boolean checker = false;
					
					checker = pxlIter.checkNextPixel();
					
					if(checker)
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
				byte dir = getDir2((float)collide->hitbox->width/2,(float)collide->hitbox->height/2,(float)overlapX, (float)overlapY);
				
				switch(dir)
				{
					case DIR_DOWN:
					collide->y = (collideOverlap2.y + (y - height/2)) - (float)((float)(collide->hitbox->height + ((float)collide->hitboxPoint.y*collide->Scale))) + 1;
					collide->updateHitbox();
					break;
					
					case DIR_UP:
					collide->y = ((y - height/2) + (collideOverlap2.y + collideOverlap2.height)) + collide->height/2 - ((float)((float)collide->hitboxPoint.y*collide->Scale) + collide->height/2) + 1;
					collide->updateHitbox();
					break;
					
					case DIR_LEFT:
					collide->x = ((x - width/2) + (collideOverlap2.x + collideOverlap2.width) + (float)((float)collide->hitbox->width)/2);
					collide->updateHitbox();
					break;
					
					case DIR_RIGHT:
					collide->x = (collideOverlap2.x + (x - width/2)) - (float)((float)collide->hitbox->width)/2;
					collide->updateHitbox();
					break;
				}
				return dir;
			}
		}
		return 0;
	}
}