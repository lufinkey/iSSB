
#include "SmashBall.h"
#include "../../Global.h"
#include "../../Stage.h"

namespace SmashBros
{
	SmashBall::SmashBall(float x1, float y1) : Item(x1,y1, 40000,TYPE_WIELD)
	{
		moveTime = 0;
		speed = 1;
		hittable = true;
		unHittableTime = 0;
		health = 10;
		
		createdReadyFire = false;
		readyFireX = 0;
		readyFireY = 0;
		
		active = true;
		
		itemNo = Global::ITEM_SMASHBALL;

		readyFire = null;
		
		Animation*anim;
		
		anim = new Animation("normal", 5, 8, 1);
		anim->addFrame("Images/Game/Items/SmashBall/smashball.png");
		addAnimation(anim);
		
		anim = new Animation("hit", 6, 2, 1);
		anim->addFrame("Images/Game/Items/SmashBall/smashball_hit.png");
		addAnimation(anim);
		
		addFileResource("Images/Game/Items/SmashBall/finalsmash_fire.png");
		
		changeAnimation("normal",FORWARD);
		
		ignoreGoThroughPlatforms(true);
		setSolid(true);
		canBeCarried(false);
	}

	SmashBall::~SmashBall()
	{
		//
	}
	
	void SmashBall::addP2PData(DataVoid&data)
	{
		data.add(&createdReadyFire, sizeof(createdReadyFire));
		if(createdReadyFire)
		{
			data.add(&readyFirePno, sizeof(readyFirePno));
			data.add(&readyFireX, sizeof(readyFireX));
			data.add(&readyFireY, sizeof(readyFireY));
		}
	}
	
	void SmashBall::setP2PData(byte*&data)
	{
		bool createdFire = DataVoid::toBool(data);
		data+=sizeof(bool);
		
		if(createdFire)
		{
			byte pNo = data[0];
			data += sizeof(byte);
			
			float x1 = DataVoid::toFloat(data);
			data += sizeof(float);
			
			float y1 = DataVoid::toFloat(data);
			data += sizeof(float);
			
			Projectile*fire = new Projectile(pNo, x1,y1);
			fire->addAnimation(new Animation("normal",1,"Images/Game/Items/SmashBall/finalsmash_fire.png"));
			fire->changeAnimation("normal", FORWARD);
			fire->setAlpha(0.278f);
			fire->setLayer(Projectile::LAYER_MIDDLEUPPER);
			createProjectile(fire);
		}
	}

	void SmashBall::onAnimationFinish(const String&n)
	{
		if(n.equals("hit"))
		{
			changeAnimation("normal",FORWARD);
		}
	}
	
	void SmashBall::onCreate()
	{
		Global::smashBallOnField = true;
		yvelocity = 2*speed;
	}

	void SmashBall::onDestroy()
	{
		Global::smashBallOnField = false;
		Global::playerHasSmashBall = false;
		if(readyFire!=null)
		{
			readyFire->destroy();
			readyFire = null;
		}
	}

	void SmashBall::onPickUp(Player*collide)
	{
		doPowerUp(collide,POWERUP_FINALSMASH,0);
	}

	boolean SmashBall::canPickUp()
	{
		return false;
	}

	void SmashBall::whilePlatformColliding(Platform*collide, byte dir)
	{
		if(!isHeld())
		{
			setDirection(dir,speed);
		}
	}

	void SmashBall::whilePlayerColliding(Player*collide)
	{
		byte dir = getDir(collide,this);
		if(isHeld())
		{
			setDirection(dir,speed);
		}
		else
		{
			if(collide->getAttacksPriority()>0 && hittable)
			{
				hittable = false;
				unHittableTime = Global::getWorldTime() + 300;
				setDirection(dir,2*speed);
				hitSmashBall(collide,dir);
			}
			else
			{
				setDirection(dir,speed);
			}
		}
	}

	void SmashBall::hitSmashBall(Player*collide, byte dir)
	{
		Console::WriteLine((String)"" + health);
		if(((int)collide->getAttacksPriority()) == 4)
		{
		    health-=3;
		    changeAnimation("hit", FORWARD);
		}
		else if(((int)collide->getAttacksPriority()) == 5)
		{
		    health-=1;
		    changeAnimation("hit", FORWARD);
		}
		else if(((int)collide->getAttacksPriority()) == 6)
		{
		    health-=2;
		    changeAnimation("hit", FORWARD);
		}
		else if(collide->getAttacksPriority() > 0)
		{
		    health-=(int)(collide->getAttacksPriority());
		    changeAnimation("hit", FORWARD);
		}

		if(collide->getPlayerNo()>0)
		{
		    if(health<=0 && active)
		    {
				//TODO add creation of finalsmash fire for P2P
		        active=false;
		        readyFire = new Projectile(collide->getPlayerNo(), collide->x,collide->y);
		        readyFire->addAnimation(new Animation("normal",1,"Images/Game/Items/SmashBall/finalsmash_fire.png"));
		        readyFire->changeAnimation("normal", FORWARD);
		        readyFire->setAlpha(0.278f);
		        readyFire->setLayer(Projectile::LAYER_MIDDLEUPPER);
		        createProjectile(readyFire);
		        collide->pickUpItem(this);
				
				createdReadyFire = true;
				readyFirePno = collide->getPlayerNo();
				readyFireX = collide->x;
				readyFireY = collide->y;
		    }
		}
	}

	void SmashBall::Update(long gameTime)
	{
		if(isHeld())
		{
			//
		}
		else
		{
			if(!hittable)
			{
				if(unHittableTime <= Global::getWorldTime())
				{
					hittable = true;
				}
			}
			if(moveTime <= Global::getWorldTime())
			{
				setDirection();
			    
			    moveTime = Global::getWorldTime() + 1000;
			}
			
			RectangleF borders = Global::currentStage->getItemBoundaries();
			
			if(x < borders.x)
			{
				xvelocity = speed;
			}
			else if(x > (borders.x + borders.width))
			{
				xvelocity = -speed;
			}
			
			if(y < borders.y)
			{
				yvelocity = speed;
			}
			else if(y > (borders.y + borders.height))
			{
				yvelocity = -speed;
			}
		}
		Item::Update(gameTime);
	}

	void SmashBall::Draw(Graphics2D&g, long gameTime)
	{
		if(isHeld() && readyFire!=null)
		{
			Player*owner = Global::getPlayerActor(getItemHolder());
			readyFire->x = owner->x;
			readyFire->y = owner->y;
			x = 0;
			y = 0;
		}
		else
		{
			Item::Draw(g, gameTime);
		}
	}

	void SmashBall::setDirection(byte dir, float speed)
	{
		int moveDist = 1;
		switch(dir)
		{
			case DIR_UP:
			yvelocity = -speed;
			y-=moveDist;
			break;
			
			case DIR_DOWN:
			yvelocity = speed;
			y+=moveDist;
			break;
			
			case DIR_LEFT:
			xvelocity = -speed;
			x-=moveDist;
			break;
			
			case DIR_RIGHT:
			xvelocity = speed;
			x+=moveDist;
			break;
			
			case DIR_UPLEFT:
			xvelocity = -speed;
			yvelocity = -speed;
			x-=moveDist;
			y-=moveDist;
			break;
			
			case DIR_UPRIGHT:
			xvelocity = speed;
			yvelocity = -speed;
			x+=moveDist;
			y-=moveDist;
			break;
			
			case DIR_DOWNLEFT:
			xvelocity = -speed;
			yvelocity = speed;
			x-=moveDist;
			y+=moveDist;
			break;
			
			case DIR_DOWNRIGHT:
			xvelocity = speed;
			yvelocity = speed;
			x+=moveDist;
			y+=moveDist;
			break;
		}
	}

	void SmashBall::setDirection()
	{
		double rand = GameEngine::random()*6;
		 
	    //-----down-----//
	 
	    if(yvelocity>0)
	    {
	        if(xvelocity>0)
	        {
	            //down right
	            if(rand<=2)
	            {
	                //down
	                xvelocity=0;
	                yvelocity=speed;
	            }
	            else if((rand>2)&&(rand<4))
	            {
	                //down right
	                xvelocity=speed;
	                yvelocity=speed;
	            }
	            else if(rand>=4)
	            {
	                //right
	                xvelocity=speed;
	                yvelocity=0;
	            }
	        }
	        else if(xvelocity==0)
	        {
	            //down
	            if(rand<=2)
	            {
	                //down left
	                xvelocity=-speed;
	                yvelocity=speed;
	            }
	            else if((rand>2)&&(rand<4))
	            {
	                //down
	                xvelocity=0;
	                yvelocity=speed;
	            }
	            else if(rand>=4)
	            {
	                //down right
	                xvelocity=speed;
	                yvelocity=speed;
	            }
	        }
	        else if(xvelocity<0)
	        {
	            //down left
	            if(rand<=2)
	            {
	                //left
	                xvelocity=-speed;
	                yvelocity=0;
	            }
	            else if((rand>2)&&(rand<4))
	            {
	                //down left
	                xvelocity=-speed;
	                yvelocity=speed;
	            }
	            else if(rand>=4)
	            {
	                //down
	                xvelocity=0;
	                yvelocity=speed;
	            }
	        }
	    }
	 
	    //-----nowhere-----//
	 
	    else if(yvelocity==0)
	    {
	        if(xvelocity>0)
	        {
	            //right
	            if(rand<=2)
	            {
	                //down right
	                xvelocity=speed;
	                yvelocity=speed;
	            }
	            else if((rand>2)&&(rand<4))
	            {
	                //right
	                xvelocity=speed;
	                yvelocity=0;
	            }
	            else if(rand>=4)
	            {
	                //up right
	                xvelocity=speed;
	                yvelocity=-speed;
	            }
	        }
	        else if(xvelocity==0)
	        {
	            //nowhere
	            xvelocity=speed;
	        }
	        else if(xvelocity<0)
	        {
	            //left
	            if(rand<=2)
	            {
	                //up left
	                xvelocity=-speed;
	                yvelocity=-speed;
	            }
	            else if((rand>2)&&(rand<4))
	            {
	                //left
	                xvelocity=-speed;
	                yvelocity=0;
	            }
	            else if(rand>=4)
	            {
	                //down left
	                xvelocity=-speed;
	                yvelocity=speed;
	            }
	        }
	    }
	 
	    //-----up-----//
	 
	    else if(yvelocity<0)
	    {
	        if(xvelocity>0)
	        {
	            //up right
	            if(rand<=2)
	            {
	                //up
	                xvelocity=0;
	                yvelocity=-speed;
	            }
	            else if((rand>2)&&(rand<4))
	            {
	                //up right
	                xvelocity=speed;
	                yvelocity=-speed;
	            }
	            else if(rand>=4)
	            {
	                //right
	                xvelocity=speed;
	                yvelocity=0;
	            }
	        }
	        else if(xvelocity==0)
	        {
	            //up
	            if(rand<=2)
	            {
	                //up left
	                xvelocity=-speed;
	                yvelocity=-speed;
	            }
	            else if((rand>2)&&(rand<4))
	            {
	                //up
	                xvelocity=0;
	                yvelocity=-speed;
	            }
	            else if(rand>=4)
	            {
	                //up right
	                xvelocity=speed;
	                yvelocity=-speed;
	            }
	        }
	        else if(xvelocity<0)
	        {
	            //up left
	            if(rand<=2)
	            {
	                //left
	                xvelocity=-speed;
	                yvelocity=0;
	            }
	            else if((rand>2)&&(rand<4))
	            {
	                //up left
	                xvelocity=-speed;
	                yvelocity=-speed;
	            }
	            else if(rand>=4)
	            {
	                //up
	                xvelocity=0;
	                yvelocity=-speed;
	            }
	        }
	    }
	}
}