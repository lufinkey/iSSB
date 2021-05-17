
#include "Actor.h"
#include "../Application.h"
#include "WireframeActor.h"
#include "../Util/PixelIterator.h"
#include "../View.h"
#include "../Output/Console.h"
#include "../Input/Mouse.h"
#include <math.h>

#if defined(__APPLE__)
	#include "TargetConditionals.h"
#endif

namespace GameEngine
{
	void Actor::createActor(float x, float y) //common method called by 2 constructors
	{
		anim = NULL;
		currentImageX = 0;
		currentImageY = 0;
		currentImageW = 0;
		currentImageH = 0;
		moving = false;
		moveSpeed = 0;
		showwire=false;
		visible = true;
		mirrored = false;
		mirroredVertical = false;
		mouseover = false;
		prevMouseover = false;
		mouseOverPixel = false;
		relative = true;
		wireframeColor = Color::GREEN;
		clicked = false;
		prevclicked = false;
		firstAnimChange = true;
		touchId = 0;
		currentTouchId = 0;

	    animMgr = new AnimationManager();
	    Scale = 1;
	    Alpha = 0;
	    this->x=x;
	    this->y=y;
	    xprev=x;
	    yprev=y;
		xSpeed = 0;
		ySpeed = 0;
	    xvelocity=0;
	    yvelocity=0;
	    width=1;
	    height=1;
	    color = Color(255,255,255,255);
	    frameTime=0;
		lastFrameTime=0;
	    Rotation=0;

	    actorType=1;
	    for(int i=0; i<totalEvents; i++)
	    {
	        enabledEvents[i]=true;
	    }
	}

	void Actor::updateMoveTo()
	{
	    if(moving)
    	{
    		double dist = distance(x, y, movePoint[0], movePoint[1]);
    		float xPnt = (float)(((movePoint[0] - x)/dist)*moveSpeed);
	    	float yPnt = (float)(((movePoint[1] - y)/dist)*moveSpeed);
	    	bool finished = false;
	    	float newX = x + xPnt;
	    	float newY = y + yPnt;
	    	if(((x<movePoint[0])&&(newX>=movePoint[0])) || ((y<movePoint[1])&&(newY>=movePoint[1]))
	    	|| ((x>movePoint[0])&&(newX<=movePoint[0])) || ((y>movePoint[1])&&(newY<=movePoint[1])))
	    	{
	    		finished = true;
	    	}
	    	
	    	if(finished)
	    	{
	    		x = movePoint[0];
	    		y = movePoint[1];
	    		moving = false;
	    		if(isEventEnabled(EVENT_MOVEFINISH))
    			{
	    			onMoveFinish();
    			}
	    	}
	    	else
	    	{
	    		x = newX;
	    		y = newY;
	    	}
    	}
	}

	bool Actor::pixelAtPoint(int col, int row)
	{
		BufferedImage*currentImage = anim->getCurrentImage();
		int x1 = 0;
		int y1 = 0;
		bool mirror = false;
		bool mirrorVertical = false;

		if((anim->isMirrored() && !this->mirrored) || (!anim->isMirrored() && this->mirrored))
		{
			mirror = true;
		}
		if((anim->isMirroredVertical() && !this->mirroredVertical) || (!anim->isMirroredVertical() && this->mirroredVertical))
		{
			mirrorVertical = true;
		}

		if(mirror)
		{
			x1 = currentImageX + ((currentImageW-1) - col);
		}
		else
		{
			x1 = currentImageX + col;
		}

		if(mirrorVertical)
		{
			y1 = currentImageY + ((currentImageH-1) - row);
		}
		else
		{
			y1 = currentImageY + row;
		}

	    if(col < currentImageW && row < currentImageH)
    	{
	    	return currentImage->pixelAtPoint(x1, y1);
    	}
    	return false;
	}

	void Actor::updateSize()
	{
	    if(anim!=NULL)
    	{
			BufferedImage*img = anim->getCurrentImage();
			switch(anim->getType())
			{
				default:
				this->width = (int)((float)(img->getWidth()/anim->getCols())*Scale);
				this->height = (int)((float)(img->getHeight()/anim->getRows())*Scale);
				break;
				
				case 0:
				this->width = (int)(img->getWidth()*Scale);
				this->height = (int)(img->getHeight()*Scale);
				break;
			}
    	}
	}

	void Actor::updateAnim()
	{
		if(anim!=NULL)
    	{
	    	BufferedImage*currentImage = anim->getCurrentImage();
	        int imgW = currentImage->getWidth();
	    	int imgH = currentImage->getHeight();
	    	switch(anim->getType())
	    	{
	    		case 0:
	    		currentImageW = imgW;
	    		currentImageH = imgH;
	    		currentImageX = 0;
	    		currentImageY = 0;
	    		break;
	    		
	    		case 1:
	    		currentImageW = imgW/anim->getCols();
	        	currentImageH = imgH/anim->getRows();
	    		currentImageX = (anim->getCurrentFrame()%anim->getCols())*currentImageW;
	            currentImageY = (anim->getCurrentFrame()/anim->getCols())*currentImageH;
	    		break;
				
				case 2:
				currentImageW = imgW/anim->getCols();
				currentImageH = imgH/anim->getRows();
				currentImageX = (anim->getSequenceFrame(anim->getCurrentFrame())%anim->getCols())*currentImageW;
				currentImageY = (anim->getSequenceFrame(anim->getCurrentFrame())/anim->getCols())*currentImageH;
				break;
	    	}
	    	updateSize();
    	}
	}

	void Actor::drawActor(Graphics2D& g, long gameTime, float x1, float y1, double scale, bool relativeToScreen)
	{
		if(scale==0)
		{
			updateAnim();
			return;
		}
		
		if(frameTime==0)
		{
			int addTime;
        		if(anim->fps == 0)
			{
				addTime = 0;
			}
			else
            {
            	addTime=1000/anim->fps;
            }
            frameTime=gameTime+addTime;
			lastFrameTime=gameTime;
            anim->drawFrame(this,g,anim->getCurrentFrame(),x1,y1,scale,relativeToScreen);
        }
        else if(frameTime<=gameTime)
        {
            int addTime;
            if(anim->fps == 0)
            {
            	addTime = 0;
            }
            else
            {
            	addTime=1000/anim->fps;
            }
            frameTime+=addTime; //frameTime = lastFrameTime + (addTime*2); //frameTime = gameTime+addTime;
			lastFrameTime=gameTime;
            anim->nextFrame(this,g,gameTime, x1,y1,scale,relativeToScreen);
        }
        else
        {
            anim->drawFrame(this,g, anim->getCurrentFrame(),x1,y1,scale,relativeToScreen);
        }
        if(showwire)
        {
			Color color = g.getColor();
        	int w = (int)(anim->width*scale);
        	int h = (int)(anim->height*scale);
        	g.setColor(wireframeColor);
        	g.drawRect((x1-View::x-w/2), (y1-View::y-h/2), (float)w, (float)h);
			g.setColor(color);
        }
        updateSize();
	}
	
	bool Actor::checkHover(float x1, float y1)
	{
		int mousex = 0;
		int mousey = 0;
		if(relative)
		{
			mousex = (int)((float)x1 + View::x);
    		mousey = (int)((float)y1 + View::y);
		}
		else
		{
    		mousex = (int)x1;
    		mousey = (int)y1;
		}
	    if(mouseOverPixel)
    	{
    		if (mousex<(x+(width/2)) && mousex>(x-(width/2)) && mousey<(y+(height/2)) && mousey>(y-(height/2)))
	    	{
	    		int rX = (int)((mousex - (x-(width/2)))/Scale);
	    		int rY = (int)((mousey - (y-(height/2)))/Scale);
	    		if(pixelAtPoint(rX, rY))
	    		{
	    			return true;
	    		}
	    		return false;
	    	}
	    	return false;
    	}
    	else
    	{
    		if (mousex<(x+(width/2)) && mousex>(x-(width/2)) && mousey<(y+(height/2)) && mousey>(y-(height/2)))
	    	{
	    		return true;
	    	}
    		return false;
    	}
	}
	
	Actor::~Actor()
	{
		delete animMgr;
	}
	
	Actor::Actor()
	{
	    createActor(0,0);
	}
	
	Actor::Actor(const Actor& actor)
	{
		xprev = actor.xprev;
		yprev = actor.yprev;

		xSpeed = actor.xSpeed;
		ySpeed = actor.ySpeed;

		currentImageX = actor.currentImageX;
		currentImageY = actor.currentImageY;
		currentImageW = actor.currentImageW;
		currentImageH = actor.currentImageH;

		frameTime = actor.frameTime;
		lastFrameTime = actor.lastFrameTime;
		color = Color(actor.color);

		Alpha = actor.Alpha;
		Rotation = actor.Rotation;
		Scale = actor.Scale;
		
		for(int i=0; i<totalEvents; i++)
		{
			enabledEvents[i] = actor.enabledEvents[i];
		}
		
		moving = actor.moving;
		movePoint[0] = actor.movePoint[0];
		movePoint[1] = actor.movePoint[1];
		moveSpeed = actor.moveSpeed;

		showwire = actor.showwire;
		visible = actor.visible;
		mirrored = actor.mirrored;
		mirroredVertical = actor.mirroredVertical;
		relative = actor.relative;

		mouseover = actor.mouseover;
		prevMouseover = actor.mouseover;
		mouseOverPixel = actor.mouseOverPixel;
		
		touchId = actor.touchId;
		currentTouchId = actor.currentTouchId;

		wireframeColor = Color(actor.wireframeColor);

		animMgr = new AnimationManager(*actor.animMgr);
		clicked = actor.clicked;
		prevclicked = actor.prevclicked;
		firstAnimChange = actor.firstAnimChange;

		anim = animMgr->get(actor.anim->name);

		xvelocity = actor.xvelocity;
		yvelocity = actor.yvelocity;
	}

	Actor::Actor(float x1,float y1)
	{
	    createActor(x1,y1);
	}

	Actor& Actor::operator=(const Actor& actor)
	{
		delete animMgr;

		xprev = actor.xprev;
		yprev = actor.yprev;

		xSpeed = actor.xSpeed;
		ySpeed = actor.ySpeed;

		currentImageX = actor.currentImageX;
		currentImageY = actor.currentImageY;
		currentImageW = actor.currentImageW;
		currentImageH = actor.currentImageH;

		frameTime = actor.frameTime;
		lastFrameTime = actor.lastFrameTime;
		color = Color(actor.color);

		Alpha = actor.Alpha;
		Rotation = actor.Rotation;
		
		for(int i=0; i<totalEvents; i++)
		{
			enabledEvents[i] = actor.enabledEvents[i];
		}
		
		moving = actor.moving;
		movePoint[0] = actor.movePoint[0];
		movePoint[1] = actor.movePoint[1];
		moveSpeed = actor.moveSpeed;

		showwire = actor.showwire;
		visible = actor.visible;
		mirrored = actor.mirrored;
		relative = actor.relative;

		mouseover = actor.mouseover;
		mouseover = actor.prevMouseover;
		mouseOverPixel = actor.mouseOverPixel;
		
		touchId = actor.touchId;
		currentTouchId = actor.currentTouchId;

		wireframeColor = Color(actor.wireframeColor);
		
		animMgr = new AnimationManager(*actor.animMgr);
		clicked = actor.clicked;
		prevclicked = actor.prevclicked;
		firstAnimChange = actor.firstAnimChange;

		anim = animMgr->get(actor.anim->name);

		xvelocity = actor.xvelocity;
		yvelocity = actor.yvelocity;

		Scale = actor.Scale;

		return *this;
	}

	void Actor::Update(long gameTime)
	{
	    updateAnim();
	    
	    prevclicked = clicked;
	    	
	    xSpeed = x - xprev;
	    ySpeed = y - yprev;
		
	    xprev = x;
	    yprev = y;
	    	
	    x+=xvelocity;
	    y+=yvelocity;
	    
	    updateMoveTo();
		
		long prevTouchId = currentTouchId;
		
		bool onmouseenter = false;
		bool onmouseleave = false;
		bool onclick = false;
		bool onrelease = false;
		
	    if(mouseOver())
	    {
			bool prevMouseOver = mouseover;
	    	if(!mouseover)
	    	{
	    		mouseover=true;
	    		if(isEventEnabled(EVENT_MOUSEENTER))
	    		{
	    			onmouseenter = true;
	    		}
	    	}

			bool clicking = false;
			if(Application::hasMultitouch())
			{
				if(!prevMouseOver && !Application::checkPrevTouchActive(touchId))
				{
					clicking = true;
				}
			}
			else
			{
				if(Application::getMouseState(Mouse::LEFTCLICK) && !Application::getPrevMouseState(Mouse::LEFTCLICK))
				{
					clicking = true;
				}
			}

			if(clicking)
	    	{
	    		clicked = true;
	    		if(isEventEnabled(EVENT_MOUSECLICK))
	    		{
	    			onclick = true;
	    		}
	    	}
	    }
	    else if(mouseover)
	    {
	    	mouseover=false;
	    	if(isEventEnabled(EVENT_MOUSELEAVE))
			{
	    		onmouseleave = true;
			}
	    }

		bool releasing = false;
		if(Application::hasMultitouch())
		{
			if(clicked && prevMouseover && !Application::checkTouchActive(prevTouchId))
			{
				releasing = true;
			}
		}
		else
		{
			if(clicked && !Application::getMouseState(Mouse::LEFTCLICK))
			{
				releasing = true;
			}
		}

		if(releasing)
	    {
	    	clicked = false;
	    	if(isEventEnabled(EVENT_MOUSERELEASE))
			{
	    		onrelease = true;
			}
	    }
		
		if(Application::hasMultitouch())
		{
			if(clicked && !Application::checkTouchActive(touchId))
			{
				clicked = false;
			}
		}
		
		currentTouchId = touchId;
		prevMouseover = mouseover;
		
		if(onmouseenter)
		{
			onMouseEnter();
		}
		if(onclick)
		{
			onClick();
		}
		if(onmouseleave)
		{
			onMouseLeave();
		}
		if(onrelease)
		{
			onRelease();
		}
	}
	
	void Actor::Draw(Graphics2D& g,long gameTime)
	{
	    drawActor(g,gameTime,x,y,Scale,relative);
	}

	void Actor::mirror(bool toggle)
	{
		this->mirrored = toggle;
	}

	void Actor::mirrorVertical(bool toggle)
	{
		this->mirroredVertical = toggle;
	}
	
	bool Actor::isMirrored()
	{
		return mirrored;
	}
	
	bool Actor::isMirroredVertical()
	{
		return mirroredVertical;
	}
	
	bool Actor::isEventEnabled(unsigned char eventCode)
	{
		if(eventCode>totalEvents)
		{
			Console::WriteLine((String)"Error: EventEnabled(unsigned char). Invalid argument " + eventCode + (String)". Event does not exist");
			return false;
		}
		else
		{
			return enabledEvents[eventCode];
		}
	}
	
	void Actor::setEventEnabled(unsigned char eventCode, bool toggle)
	{
	    if(eventCode>totalEvents)
	    {
	    	Console::WriteLine((String)"Error: EventEnable(unsigned char). Invalid argument " + eventCode + (String)". Event does not exist");
	    }
	    else
	    {
	    	enabledEvents[eventCode]=toggle;
	    }
	}
	
	void Actor::changeAnimation(Animation*animation, unsigned char dir)
	{
		if(animation == NULL)
		{
			return;
		}
		if(dir==NO_CHANGE)
	    {
	        String aName=animation->name;
			if(firstAnimChange)
			{
				this->anim=animation;
				this->anim->setCurrentFrame(0);
				frameTime=0;
				//anim.drawFrame(graphics,0,x,y);
				this->anim->direction=FORWARD;
			}
	        else if(anim==NULL || !(aName.equals(this->anim->name)))
	        {
	            this->anim=animation;
	            //anim.drawFrame(graphics,0,x,y);
	            frameTime = 0;
				/*long newFrameTime = lastFrameTime + (1000/anim->fps);
            	if(newFrameTime<frameTime)
            	{
            		frameTime = newFrameTime;
            	}*/
	        }
	    }
	    else if(dir==STOPPED)
	    {
	        this->anim=animation;
	        this->anim->setCurrentFrame(0);
	        frameTime=0;
	        //anim.drawFrame(graphics,0,x,y);
	        this->anim->direction=STOPPED;
	    }
	    else if(dir==FORWARD)
	    {
	        this->anim=animation;
	        this->anim->setCurrentFrame(0);
	        frameTime=0;
	        //anim.drawFrame(graphics,0,x,y);
	        this->anim->direction=FORWARD;
	    }
	    else if(dir==BACKWARD)
	    {
	        this->anim=animation;
	        this->anim->setCurrentFrame(0);
	        frameTime=0;
	        //anim.drawFrame(graphics,anim.frames,x,y);
	        this->anim->direction=BACKWARD;
	    }
		updateAnim();
	    firstAnimChange = false;
	}

	void Actor::changeAnimation(const String&animName, unsigned char dir)
	{
		Animation*animation = animMgr->get(animName);
		if(animation == NULL)
		{
			return;
		}
		changeAnimation(animation, dir);
	}
	
	void Actor::changeAnimation(unsigned int index, unsigned char dir)
	{
		Animation*animation = animMgr->animations[index];
		if(animation == NULL)
		{
			return;
		}
		changeAnimation(animation, dir);
	}

	void Actor::changeAnimationDirection(unsigned char dir)
	{
	    if(dir==FORWARD || dir==BACKWARD || dir==STOPPED)
	    {
	    	this->anim->direction = dir;
	    }
	}
	
	void Actor::onAnimationFinish(const String&n) //inherited user-defined method. is called when an animation ends and String is name of animation
	{
	    //Open for implementation
	}
	
	void Actor::addAnimation(Animation*a) //add an animation to Actor's AnimationManager
	{
	    animMgr->add(a);
		if(anim == NULL)
		{
			changeAnimation(a->name, FORWARD);
		}
	}
	
	void Actor::removeAnimation(const String&animName) //removes an animation from Actor's AnimationManager
	{
		if(anim != NULL && anim->name.equals(animName))
		{
			anim = NULL;
		}
	    animMgr->remove(animName);
	}
	
	bool Actor::hasAnimation(const String&animName) //checks if Actor has an Animation with the specified name
	{
		return animMgr->contains(animName);
	}
	
	Animation*Actor::getAnimation()
	{
		return anim;
	}

	void Actor::setRelativeToView(bool toggle)
	{
		relative = toggle;
	}
	
	bool Actor::isRelativeToView()
	{
		return relative;
	}

	void Actor::mouseOverUsesPixel(bool toggle)
    {
    	mouseOverPixel = toggle;
    }

	bool Actor::mouseOver()
	{
		if(Application::hasMultitouch()) {
			if(mouseover)
			{
				if(Application::checkTouchActive(currentTouchId))
				{
					float mousex = 0;
					float mousey = 0;
					if(relative)
					{
						mousex = (float)Application::getTouchX(currentTouchId) + View::x;
						mousey = (float)Application::getTouchY(currentTouchId) + View::y;
					}
					else
					{
						mousex = (float)Application::getTouchX(currentTouchId);
						mousey = (float)Application::getTouchY(currentTouchId);
					}

					if(checkHover(mousex, mousey))
					{
						return true;
					}
				}
			}

			ArrayList<TouchPoint> points = Application::getTouchPoints();
			for(int i=0; i<points.size(); i++)
			{
				TouchPoint&point = points.get(i);
				if(checkHover(point.x, point.y))
				{
					touchId = point.ID;
					return true;
				}
			}
			return false;
		}
		else {
			float mousex = 0;
			float mousey = 0;
			if(relative)
			{
				mousex = (float)Application::getMouseX() + View::x;
				mousey = (float)Application::getMouseY() + View::y;
			}
			else
			{
				mousex = (float)Application::getMouseX();
				mousey = (float)Application::getMouseY();
			}

			return checkHover(mousex, mousey);
		}
	}
	
	void Actor::onMouseEnter() //When mouse enters Actor
	{
	    //Open for implementation
	}
	
	void Actor::onMouseLeave() //When mouse enters Actor
	{
	    //Open for implementation
	}
	
	void Actor::onClick() //When an Actor is clicked
	{
	    //Open for implementation
	}
	
	void Actor::onRelease() //When an Actor's click is released
	{
	    //Open for implementation
	}
	
	bool Actor::isClicked()
	{
	    return clicked;
	}
	
	bool Actor::wasClicked()
	{
	    return prevclicked;
	}
	
	long Actor::getTouchId()
	{
		return currentTouchId;
	}
	
	void Actor::moveTo(float x1, float y1, float speed)
	{
	    if(x1!=x && y1!=y)
	    {
	    	moving = true;
	    	movePoint[0]=x1;
	    	movePoint[1]=y1;
	    	moveSpeed=speed;
	    }
	}
	
	void Actor::onMoveFinish() //When a MoveTo finishes
	{
	    //Open for implementation
	}
	
	/*bool Actor::isColliding(Actor*collide)
	{
		Rect overlap = getOverlapArea(collide);
		if(overlap.left != -1)
		{
			Rect overlap2 = collide->getOverlapArea(this);
			
			int w = overlap.right - overlap.left;
			int h = overlap.bottom - overlap.top;
			
			float x1 = ((float)overlap.left/Scale);
			float y1 = ((float)overlap.top/Scale);
			float x2 = ((float)overlap2.left/collide->Scale);
			float y2 = ((float)overlap2.top/collide->Scale);
			
			float incr1 = (float)(1/Scale);
			float incr2 = (float)(1/collide->Scale);
			
			float pntX1 = x1;
			float pntY1 = y1;
			float pntX2 = x2;
			float pntY2 = y2;
			
			for(int cntY = 0; cntY<h; cntY++)
			{
				pntX1 = x1;
				pntX2 = x2;
				for(int cntX = 0; cntX<w; cntX++)
				{
					if(pixelAtPoint((int)(pntX1),(int)(pntY1)) && collide->pixelAtPoint((int)(pntX2),(int)(pntY2)))
					{
						return true;
					}
					pntX1+=incr1;
					pntX2+=incr2;
				}
				pntY1+=incr1;
				pntY2+=incr2;
			}
			return false;
		}
		return false;
	}*/

	bool Actor::isColliding(Actor*collide)
	{
		if(Scale==0 || collide->Scale==0)
		{
			return false;
		}
		RectF overlap = getOverlapArea(collide);
		if(overlap.left != -1)
		{
			RectF overlap2 = collide->getOverlapArea(this);
			
			int w = (int)(overlap.right - overlap.left);
			int h = (int)(overlap.bottom - overlap.top);
			
			float x1 = ((float)overlap.left/Scale);
			float y1 = ((float)overlap.top/Scale);
			float x2 = ((float)overlap2.left/collide->Scale);
			float y2 = ((float)overlap2.top/collide->Scale);
			
			float incr1 = (float)(1/Scale);
			float incr2 = (float)(1/collide->Scale);

			PixelIterator pxlIter(this);
			pxlIter.reset(x1,y1,incr1,incr1,(int)w,(int)h);
			PixelIterator colPxlIter(collide);
			colPxlIter.reset(x2,y2,incr2,incr2,(int)w,(int)h);

			for(int cntY = 0; cntY<h; cntY++)
			{
				for(int cntX = 0; cntX<w; cntX++)
				{
					bool b1 = pxlIter.checkNextPixel();
					bool b2 = colPxlIter.checkNextPixel();
					if(b1 && b2)
					{
						return true;
					}
				}
			}
			return false;
		}
		return false;
	}
	
	String Actor::getAnimName()
	{
	    return anim->name;
	}
	
	unsigned int Actor::getAnimIndex()
	{
		if(anim!=NULL)
		{
			for(int i=0; i<animMgr->animations.size(); i++)
			{
				Animation*cmp = animMgr->animations.get(i);
				if(anim == cmp)
				{
					return (unsigned int)i;
				}
			}
		}
		return 0;
	}

	int Actor::getCurrentFrame()
	{
		return anim->currentFrame;
	}
	    
	bool Actor::rectsColliding(Actor*collide) //tells if Actor's bounding boxes are colliding
	{
	    int left1, left2;
	    int right1, right2;
	    int top1, top2;
	    int bottom1, bottom2;
	
	    left1 = (int)x-(width/2);
	    left2 = (int)collide->x-(collide->width/2);
	    right1 = (int)x+(width/2);
	    right2 = (int)collide->x+(collide->width/2);
	    top1 = (int)y-(height/2);
	    top2 = (int)collide->y-(collide->height/2);
	    bottom1 = (int)y+(height/2);
	    bottom2 = (int)collide->y+(collide->height/2);
	
	    if (bottom1 < top2)
	    {
	        return false;
	    }
	    if (top1 > bottom2)
	    {
	        return false;
	    }
	
	    if (right1 < left2)
	    {
	        return false;
	    }
	    if (left1 > right2)
	    {
	        return false;
	    }
	
	    return true;
	}
	    
	bool Actor::rectsColliding(WireframeActor*collide) //tells if WireframeActor's bounding boxes are colliding
	{
	    int left1, left2;
	    int right1, right2;
	    int top1, top2;
	    int bottom1, bottom2;
	
	    left1 = (int)x-(width/2);
	    left2 = (int)collide->x;
	    right1 = (int)x+(width/2);
	    right2 = (int)collide->x + collide->width;
	    top1 = (int)y-(height/2);
	    top2 = (int)collide->y;
	    bottom1 = (int)y+(height/2);
	    bottom2 = (int)collide->y + collide->height;
	
	    if (bottom1 < top2)
	    {
	        return false;
	    }
	    if (top1 > bottom2)
	    {
	        return false;
	    }
	
	    if (right1 < left2)
	    {
	        return false;
	    }
	    if (left1 > right2)
	    {
	        return false;
	    }
	
	    return true;
	}
		
	bool Actor::circlesColliding(WireframeActor*collide) //tells if WireframeActor's "bounding circles" are colliding
	{
		double r1 = distanceUnSqr(x,y,x-(width/2),y-(height/2));
		double r2 = distanceUnSqr(collide->x,collide->y,collide->x+(collide->width/2),collide->y+(collide->height/2));
		double dist = r1+r2;
		double realDist = distanceUnSqr(x,y,collide->x+(collide->width/2),collide->y+(collide->height/2));
		if(realDist<dist)
		{
			return true;
		}
		return false;
	}
		
	bool Actor::circlesColliding(Actor*collide) //tells if Actor's "bounding circles" are colliding
	{
		double r1 = distanceUnSqr(x,y,x-(width/2),y-(height/2));
		double r2 = distanceUnSqr(collide->x,collide->y,collide->x-(collide->width/2),collide->y-(collide->height/2));
		double dist = r1+r2;
		double realDist = distanceUnSqr(x,y,collide->x,collide->y);
		if(realDist<dist)
		{
			return true;
		}
		return false;
	}
		
	bool Actor::circlesColliding(WireframeActor*collide, double mult) //tells if WireframeActor's "bounding circles" are colliding. can define scale of circle
	{
		double r1 = distanceUnSqr(x,y,x-(width/2),y-(height/2));
		double r2 = distanceUnSqr(collide->x,collide->y,collide->x+(collide->width/2),collide->y+(collide->height/2));
		double dist = (r1+r2)*mult;
		double realDist = mult*distanceUnSqr(x,y,collide->x+(collide->width/2),collide->y+(collide->height/2));
		if(realDist<dist)
		{
			return true;
		}
		return false;
	}
		
	bool Actor::circlesColliding(Actor*collide, double mult) //tells if Actor's "bounding circles" are colliding. can define scale of circle
	{
		double r1 = distanceUnSqr(x,y,x-(width/2),y-(height/2));
		double r2 = distanceUnSqr(collide->x,collide->y,collide->x-(collide->width/2),collide->y-(collide->height/2));
		double dist = (r1+r2)*mult;
		double realDist = mult*distanceUnSqr(x,y,collide->x,collide->y);
		if(realDist<dist)
		{
			return true;
		}
		return false;
	}
		
	void Actor::circleResponse(Actor*collide)
	{
		double r1 = distance(x,y,x-(width/2),y-(height/2));
		double r2 = distance(collide->x,collide->y,collide->x-(collide->width/2),collide->y-(collide->height/2));
		double dist = (r1+r2);
		double dir = direction(x,y,collide->x,collide->y);
		double xIncr = (-cos(degtorad(dir))*(dist*0.71));
		double yIncr = (sin(degtorad(dir))*(dist*0.71));
		x=collide->x+(int)xIncr;
		y=collide->y+(int)yIncr;
		/*if(y<collide->y)
		{
			if(yvelocity>0)
			{
				yvelocity=0;
			}
			xvelocity=0;
			onGround=true;
		}*/
	}
		
	void Actor::circleResponse(WireframeActor*collide) //response to circle collision. commented out things are recommended for use by inherited Actor's in platformer games
	{
		double r1 = distance(x,y,x-(width/2),y-(height/2));
		double r2 = distance(collide->x+(collide->width/2),collide->y+(collide->width/2),collide->x,collide->y);
		double dist = (r1+r2);
		double dir = direction(x,y,collide->x+(collide->width/2),collide->y+(collide->height/2));
		double xIncr = (-cos(degtorad(dir))*(dist*0.71));
		double yIncr = (sin(degtorad(dir))*(dist*0.71));
		x=collide->x + collide->width/2 + (int)xIncr;
		y=collide->y + collide->height/2 + (int)yIncr;
		/*if(y<(collide->y+(collide->height/2)))
		{
			if(yvelocity>0)
			{
				yvelocity=0;
			}
			xvelocity=0;
			onGround=true;
		}*/
	}
		
	void Actor::rectResponse(Actor*collide, unsigned char d) //response to box collision. commented out things are recommended for use by inherited Actor's in platformer games. can pass in direction (defined in PrimitiveActor)
	{
		//unsigned char d = CheckSide(collide,this);
		if(d==DIR_UP)
		{
			y=((collide->y-(collide->height/2))-(height/2));
		}
		else if(d==DIR_UPRIGHT)
		{
			y=((collide->y-(collide->height/2))-(height/2));
			x=(collide->x+(collide->width/2)+(width/2));
		}
		else if(d==DIR_RIGHT)
		{
			x=(collide->x+(collide->width/2)+(width/2));
		}
		else if(d==DIR_DOWNRIGHT)
		{
			y=((collide->y+(collide->height/2))+(height/2));
			x=(collide->x+(collide->width/2)+(width/2));
		}
		else if(d==DIR_DOWN)
		{
			y=((collide->y+(collide->height/2))+(height/2));
		}
		else if(d==DIR_DOWNLEFT)
		{
			y=((collide->y+(collide->height/2))+(height/2));
			x=((collide->x-(collide->width/2))-(width/2));
		}
		else if(d==DIR_LEFT)
		{
			x=((collide->x-(collide->width/2))-(width/2));
		}
		else if(d==DIR_UPLEFT)
		{
			y=((collide->y-(collide->height/2))-(height/2));
			x=((collide->x-(collide->width/2))-(width/2));
		}
		/*if(d==DIR_UP)
		{
			if(yvelocity>0)
			{
				yvelocity=0;
			}
			xvelocity=0;
			onGround=true;
		}
		else if(d==DIR_RIGHT)
		{
			xvelocity=0;
		}
		else if(d==DIR_LEFT)
		{
			xvelocity=0;
		}*/
	}
		
	void Actor::rectResponse(WireframeActor*collide, unsigned char d) //response to box collision. commented out things are recommended for use by inherited Actor's in platformer games. can pass in direction (defined in PrimitiveActor)
	{
		//unsigned char d = CheckSide(collide,this);
		if(d==DIR_UP)
		{
			y=(collide->y-(height/2));
		}
		else if(d==DIR_UPRIGHT)
		{
			y=(collide->y-(height/2));
			x=(collide->x+collide->width+(width/2));
		}
		else if(d==DIR_RIGHT)
		{
			x=(collide->x+collide->width+(width/2));
		}
		else if(d==DIR_DOWNRIGHT)
		{
			y=(collide->y+collide->height+(height/2));
			x=(collide->x+collide->width+(width/2));
		}
		else if(d==DIR_DOWN)
		{
			y=(collide->y+collide->height+(height/2));
		}
		else if(d==DIR_DOWNLEFT)
		{
			y=(collide->y+collide->height+(height/2));
			x=(collide->x-(width/2));
		}
		else if(d==DIR_LEFT)
		{
			x=(collide->x-(width/2));
		}
		else if(d==DIR_UPLEFT)
		{
			y=(collide->y-(height/2));
			x=(collide->x-(width/2));
		}
		/*if(d==DIR_UP)
		{
			if(yvelocity>0)
			{
				yvelocity=0;
			}
			xvelocity=0;
			onGround=true;
		}
		else if(d==DIR_RIGHT)
		{
			xvelocity=0;
		}
		else if(d==DIR_LEFT)
		{
			xvelocity=0;
		}*/
	}
		
	bool Actor::isOnScreen()
	{
		int left1, left2;
	    int right1, right2;
	    int top1, top2;
	    int bottom1, bottom2;

		float w = anim->width*Scale;
		float h = anim->height*Scale;
		
	    left1 = (int)(x-(w/2));
	    left2 = (int)View::x;
	    right1 = (int)(x+(w/2));
	    right2 = (int)(View::x+(View::getScalingWidth()));
	    top1 = (int)(y-(h/2));
	    top2 = (int)View::y;
	    bottom1 = (int)(y+(h/2));
	    bottom2 = (int)(View::y+(View::getScalingHeight()));
	
	    if (bottom1 < top2)
	    {
	        return false;
	    }
	    if (top1 > bottom2)
	    {
	        return false;
	    }
	
	    if (right1 < left2)
	    {
	        return false;
	    }
	    if (left1 > right2)
	    {
	        return false;
	    }
	
	    return true;
	}
		
	RectF Actor::getOverlapArea(Actor*a2)
	{
		RectangleF r1 = RectangleF();
		r1.x = this->x - ((float)this->width/2);
		r1.y = this->y - ((float)this->height/2);
		r1.width = (float)this->width;
		r1.height = (float)this->height;
		RectangleF r2 = RectangleF();
		r2.x = a2->x - ((float)a2->width/2);
		r2.y = a2->y - ((float)a2->height/2);
		r2.width = (float)a2->width;
		r2.height = (float)a2->height;
			
		RectF overlap;
			
		if(this->rectsColliding(a2))
		{
			if(r1.x <= r2.x)
			{
				if((r1.x + r1.width) <= (r2.x + r2.width))
				{
					overlap.left = r2.x - r1.x;
					overlap.right = r1.width;
				}
				else
				{
					overlap.left = r2.x - r1.x;
					overlap.right = overlap.left + r2.width;
				}
			}
			else
			{
				if((r1.x + r1.width) <= (r2.x + r2.width))
				{
					overlap.left = 0;
					overlap.right = r1.width;
				}
				else
				{
					overlap.left = 0;
					overlap.right = (r2.x + r2.width) - r1.x;
				}
			}
				
			if(r1.y <= r2.y)
			{
				if((r1.y + r1.height) <= (r2.y + r2.height))
				{
					overlap.top = r2.y - r1.y;
					overlap.bottom = r1.height;
				}
				else
				{
					overlap.top = r2.y - r1.y;
					overlap.bottom = overlap.top + r2.height;
				}
			}
			else
			{
				if((r1.y + r1.height)<= (r2.y + r2.height))
				{
					overlap.top = 0;
					overlap.bottom = r1.height;
				}
				else
				{
					overlap.top = 0;
					overlap.bottom = (r2.y + r2.height) - r1.y;
				}
			}
		}
		else
		{
			overlap.left = -1;
			overlap.top = -1;
			overlap.right = -1;
			overlap.bottom = -1;
		}
		return overlap;
	}
		
	void Actor::showWireframe(bool toggle)
	{
		showwire = toggle;
	}
		
	void Actor::setWireframeColor(const Color&c)
	{
		wireframeColor = c;
	}
	
	float Actor::getXSpeed()
	{
		return xSpeed;
	}
		
	float Actor::getYSpeed()
	{
		return ySpeed;
	}
	
	float Actor::getXPrev()
	{
		return xprev;
	}
	
	float Actor::getYPrev()
	{
		return yprev;
	}
		
	void Actor::setColor(const Color&c) //sets the actor's color tint
	{
	    color = c;
	}
	    
	const Color& Actor::getColor() //returns the current color of the actor
	{
	    return color;
	}
	    
	void Actor::setRotation(float degrees) //sets rotation of Actor in degrees
	{
	    Rotation = degrees;
	}
	    
	float Actor::getRotation() //returns current rotation of Actor in degrees
	{
	    return Rotation;
	}
	
	void Actor::setAlpha(float alpha)
	{
		Alpha = alpha;
	}
	    
	float Actor::getAlpha()
	{
	    return Alpha;
	}
	
	void Actor::setScale(float scale)
	{
		Scale = scale;
		updateAnim();
	}
	
	float Actor::getScale()
	{
		return Scale;
	}
	    
	void Actor::setVisible(bool toggle)
	{
	    visible = toggle;
	}
	
	bool Actor::isVisible()
	{
		return visible;
	}
}
