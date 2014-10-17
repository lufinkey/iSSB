
#include "Animation.h"
#include "../Application.h"
#include "../AssetManager.h"
#include "../Output/Console.h"
#include "../View.h"
#include "Actor.h"

namespace GameEngine
{
	Animation::Animation(const Animation& anim)
	{
		frames = anim.frames;
		names = anim.names;
		currentFrame = anim.currentFrame;
		recentFrame = anim.recentFrame;
		mirrored = anim.mirrored;
		mirroredVertical = anim.mirroredVertical;
		rows = anim.rows;
		cols = anim.cols;
		
		if(anim.sequence!=null)
		{
			sequence = new int[anim.frames];
			for(int i=0; i<anim.frames; i++)
			{
				sequence[i] = anim.sequence[i];
			}
		}
		
		imageSize.x = anim.imageSize.x;
		imageSize.y = anim.imageSize.y;
		
		animType = anim.animType;
		
		width = anim.width;
		height = anim.height;
		
		direction = anim.direction;
		
		fps = anim.fps;
		name = anim.name;
	}
	
	Animation::Animation(const String& n, int speed)
	{
		rows = 0;
		cols = 0;
		sequence = NULL;
		names = ArrayList<String>();
		recentFrame = 0;
    	animType = 0;
		name = n;
		frames = 0;
		fps = speed;
		currentFrame = 0;
		direction = FORWARD;
		width = 1;
		height = 1;
		mirrored = false;
		mirroredVertical = false;
	}
	
	Animation::Animation(const String& n, int speed, const String& frame) //(animType 0)
	{
		rows = 0;
		cols = 0;
		sequence = NULL;
		names = ArrayList<String>();
		recentFrame = 0;
    	animType = 0;
		name = n;
		frames = 0;
		fps = speed;
		currentFrame = 0;
		direction = FORWARD;
		width = 1;
		height = 1;
		mirrored = false;
		mirroredVertical = false;
		
		addFrame(frame);
	}
    
	Animation::Animation(const String& n,int speed,int xFrames,int yFrames) //(animType 1)
	{
		sequence = NULL;
		names = ArrayList<String>();
		recentFrame = 0;
    	animType=1;
		name=n;
		fps=speed;
		currentFrame=0;
		direction=FORWARD;
		width = 1;
		height = 1;
		rows = xFrames;
		cols = yFrames;
		frames = 0;
		mirrored=false;
		mirroredVertical = false;
	}
    
	Animation::Animation(const String& n, int speed, int xFrames, int yFrames, const ArrayList<int>& seq) //(animType 2)
	{
		sequence = new int[seq.size()];
		names = ArrayList<String>();
		recentFrame = 0;
    	animType=2;
		
    	for(int i=0; i<seq.size(); i++)
    	{
    		sequence[i] = seq[i];
    	}
		name=n;
		fps=speed;
		currentFrame=0;
		direction=FORWARD;
		width = 1;
		height = 1;
		rows = xFrames;
		cols = yFrames;
		frames = seq.size();
		mirrored=false;
		mirroredVertical = false;
	}
	
	Animation::~Animation()
	{
		names.clear();
		
		if(sequence!=NULL)
		{
			delete[] sequence;
		}
	}
	
	Animation& Animation::operator=(const Animation& anim)
	{
		if(sequence!=null)
		{
			delete[] sequence;
			sequence = null;
		}
		names.clear();
		
		frames = anim.frames;
		names = anim.names;
		
		currentFrame = anim.currentFrame;
		recentFrame = anim.recentFrame;
		mirrored = anim.mirrored;
		mirroredVertical = anim.mirroredVertical;
		rows = anim.rows;
		cols = anim.cols;
		
		if(anim.sequence!=null)
		{
			sequence = new int[anim.frames];
			for(int i=0; i<anim.frames; i++)
			{
				sequence[i] = anim.sequence[i];
			}
		}
		
		imageSize.x = anim.imageSize.x;
		imageSize.y = anim.imageSize.y;
		
		animType = anim.animType;
		
		width = anim.width;
		height = anim.height;
		
		direction = anim.direction;
		
		fps = anim.fps;
		name = anim.name;
		
		return *this;
	}
	
	void Animation::mirror(bool toggle)
	{
		mirrored=toggle;
	}
	
	void Animation::mirrorVertical(bool toggle)
	{
		mirroredVertical=toggle;
	}
	
	bool Animation::isMirrored()
	{
    	return mirrored;
	}
	
	bool Animation::isMirroredVertical()
	{
    	return mirroredVertical;
	}
	
	int Animation::getWidth()
	{
    	return width;
	}
	
	int Animation::getHeight()
	{
    	return height;
	}
	
	Vector2i Animation::getSize()
	{
		Vector2i size = Vector2i();
    	BufferedImage*img;
    	switch(animType)
    	{
    		case 0:
    		img = AssetManager::getImage(names[recentFrame]);
    		size.x = img->getWidth();
    		size.y = img->getHeight();
    		break;
    		
    		default:
    		img = AssetManager::getImage(names[0]);
        	size.x = img->getWidth()/cols;
        	size.y = img->getHeight()/rows;
    		break;
    	}
    	return size;
	}
    
	void Animation::addFrame(const String& fName) //adds a frame to the animation
	{
    	bool success=AssetManager::loadImage(fName);
    	switch(animType)
    	{
    		default:
    		if(success)
    		{
        		names.add(fName);
        		frames++;
    		}
    		else
    		{
    			Console::WriteLine((String)"Error: Attempt to add image " + fName + (String)" to animation failed!");
    		}
    		break;

    		case 1:
    		if(success)
    		{
				if(names.size()>0)
				{
					names.clear();
        			names.add(fName);
				}
				else
				{
					names.add(fName);
				}
        		frames=rows*cols;
    		}
    		else
    		{
    			Console::WriteLine((String)"Error: Attempt to add image " + fName + (String)" to animation failed!");
    		}
    		break;

    		case 2:
    		if(success)
    		{
        		if(names.size()>0)
				{
					names.clear();
        			names.add(fName);
				}
				else
				{
					names.add(fName);
				}
    		}
    		else
    		{
    			Console::WriteLine((String)"Error: Attempt to add image " + fName + (String)" to animation failed!");
    		}
    		break;
    	}
	}
	
	void Animation::setFrame(int frameNo, const String&fImage)
	{
		if(frameNo < names.size())
		{
			bool success=AssetManager::loadImage(fImage);
			if(success)
			{
				names.set(frameNo,fImage);
			}
		}
	}
	
	const String& Animation::getFrame(int frameNo)
	{
		switch (animType)
		{
			default:
			return names.get(frameNo);
			
			case 1:
			case 2:
			return names.get(0);
		}
	}
	
	int Animation::getTotalFrames()
	{
		return frames;
	}
	
	BufferedImage*Animation::getCurrentImage()
	{
    	switch(animType)
    	{
    		default:
    		return AssetManager::getImage(names[0]);
    		
    		case 0:
    		return AssetManager::getImage(names[recentFrame]);
    	}
	}

	int Animation::getCols()
	{
    	return cols;
	}
		
	int Animation::getRows()
	{
    	return rows;
	}
		
	int Animation::getType()
	{
    	return animType;
	}

		
	void Animation::drawFrame(Actor*a,Graphics2D& g, float x1, float y1, double scale)
	{
    	drawFrame(a,g, 0, x1, y1, scale,true);
	}
		
	void Animation::drawFrame(Actor*a, Graphics2D& g, int fNum, float x1, float y1, double scale)
	{
    	drawFrame(a,g, fNum, x1, y1, scale,true);
	}

	void Animation::drawFrame(Actor*a,Graphics2D& graphics,int fNum, float x1, float y1, double scale, bool relativeToScreen)
	{
    	double rotation;
    	unsigned char alpha = 255;
    	Color color;
		
		bool mirrored = this->mirrored;
		bool mirroredVertical = this->mirroredVertical;
		
		Graphics2D g(graphics);
    	
    	if(a!=NULL)
    	{
	    	rotation = a->getRotation();
			alpha = (unsigned char)(255 - (a->getAlpha()*255));
	    	color = a->getColor();
			if(a->mirrored)
	    	{
	    		if(mirrored)
	    		{
	    			mirrored = false;
	    		}
	    		else
	    		{
	    			mirrored = true;
	    		}
	    	}
			if(a->mirroredVertical)
	    	{
	    		if(mirroredVertical)
	    		{
	    			mirroredVertical = false;
	    		}
	    		else
	    		{
	    			mirroredVertical = true;
	    		}
	    	}
    	}
    	else
    	{
    		rotation = 0;
    		alpha = 255;
    		color = Color::WHITE;
    	}

    	int frmPnt[2];
    	BufferedImage*img;
    	if(rotation!=0 || alpha<255)
    	{
			g.setAlpha(alpha);
			if(relativeToScreen)
			{
				g.rotate((float)rotation,x1-View::x,y1-View::y);
			}
			else
			{
				g.rotate((float)rotation,x1,y1);
			}
    	}
		g.setImageMask(color);
    	
    	int frameNum;
    	
    	switch(animType)
    	{
    		default:
    		frameNum = 0;
    		break;
    		
    		case 0:
    		frameNum = fNum;
    		break;
    	}
    	
    	img = AssetManager::getImage(names[frameNum]);
    	
    	currentFrame=fNum;
    	
    	bool singleframe = false;
    	
    	switch(animType)
    	{
    		case 0:
    		singleframe = true;
    		width = img->getWidth();
    		height = img->getHeight();
    		break;
    		
    		case 1:
    		imageSize.x = img->getWidth();
    		imageSize.y = img->getHeight();
			width=imageSize.x/cols;
        	height=imageSize.y/rows;
        	frmPnt[0]=(currentFrame%cols)*width;
        	frmPnt[1]=(currentFrame/cols)*height;
    		break;
    		
    		case 2:
    		imageSize.x = img->getWidth();
    		imageSize.y = img->getHeight();
			width=imageSize.x/cols;
        	height=imageSize.y/rows;
        	frmPnt[0]=(sequence[currentFrame]%cols)*width;
        	frmPnt[1]=(sequence[currentFrame]/cols)*height;
    		break;
    	}
    	
    	bool onScreen = true;
    	
    	if(a!=NULL)
    	{
    		//a->width = this->width;
    		//a->height = this->height;
    		
    		onScreen = a->isOnScreen();
    		if(!relativeToScreen)
    		{
    			onScreen = true;
    		}
    	}
    	
    	x1=x1-(float)((width*scale)/2);
    	y1=y1-(float)((height*scale)/2);
    	
    	int drawX1,drawY1,drawX2,drawY2;
    	if(singleframe)
    	{
    		drawX1 = 0;
    		drawY1 = 0;
    		drawX2 = width;
    		drawY2 = height;
    	}
    	else
    	{
    		drawX1 = frmPnt[0];
    		drawY1 = frmPnt[1];
    		drawX2 = frmPnt[0]+width;
    		drawY2 = frmPnt[1]+height;
    		
    	}
    	
    	if(relativeToScreen && onScreen)
    	{
    		x1 -= View::x;
    		y1 -= View::y;
    	}
    	
    	if(a!=NULL)
    	{
    		if(!a->visible)
    		{
    			onScreen = false;
    		}
    	}
    	
    	if(onScreen)
    	{
	    	if(mirrored)
	    	{
				if(mirroredVertical)
				{
					g.drawImage(img, (float)(x1+(width*scale)), (float)(y1+(height*scale)), (x1), (y1),drawX1,drawY1,drawX2,drawY2);
				}
				else
				{
	    			g.drawImage(img, (float)(x1+(width*scale)), (y1), (x1), (float)(y1+(height*scale)),drawX1,drawY1,drawX2,drawY2);
				}
	    	}
	    	else
	    	{
				if(mirroredVertical)
				{
					g.drawImage(img, (x1), (float)(y1+(height*scale)), (float)(x1+(width*scale)), (y1),drawX1,drawY1,drawX2,drawY2);
				}
				else
				{
	    			g.drawImage(img, (x1), (y1), (float)(x1+(width*scale)), (float)(y1+(height*scale)),drawX1,drawY1,drawX2,drawY2);
				}
	    	}
    	}
    	recentFrame = currentFrame;
	}
	
	void Animation::drawFrame(Actor*a,Graphics2D& graphics,int fNum, float x1, float y1, float x2, float y2)
	{
    	double rotation;
    	unsigned char alpha = 255;
    	Color color;

		bool mirrored = this->mirrored;
		bool mirroredVertical = this->mirroredVertical;
		
		Graphics2D g(graphics);
    	
    	if(a!=NULL)
    	{
	    	rotation = degtorad(a->getRotation());
	    	alpha = (unsigned char)(255 - a->getAlpha()*255);
	    	color = a->getColor();
			if(a->mirrored)
	    	{
	    		if(mirrored)
	    		{
	    			mirrored = false;
	    		}
	    		else
	    		{
	    			mirrored = true;
	    		}
	    	}
			if(a->mirroredVertical)
	    	{
	    		if(mirroredVertical)
	    		{
	    			mirroredVertical = false;
	    		}
	    		else
	    		{
	    			mirroredVertical = true;
	    		}
	    	}
    	}
    	else
    	{
    		rotation = 0;
    		alpha = 255;
    		color = Color::WHITE;
    	}

    	int frmPnt[2];
    	BufferedImage*img;
    	if(rotation!=0 || alpha!=255)
    	{
			g.setAlpha(alpha);
    		g.rotate((float)rotation,x1,y1);
    	}
		g.setImageMask(color);
    	
    	int frameNum;
    	
    	switch(animType)
    	{
    		default:
    		frameNum = 0;
    		break;
    		
    		case 0:
    		frameNum = fNum;
    		break;
    	}
    	
    	img = AssetManager::getImage(names[frameNum]);
    	
    	currentFrame=fNum;
    	
    	bool singleframe = false;
    	
    	switch(animType)
    	{
    		case 0:
    		singleframe = true;
    		width = img->getWidth();
    		height = img->getHeight();
    		break;
    		
    		case 1:
    		imageSize.x=img->getWidth();
			imageSize.y=img->getHeight();
			width=imageSize.x/cols;
        	height=imageSize.y/rows;
        	frmPnt[0]=(currentFrame%cols)*width;
        	frmPnt[1]=(currentFrame/cols)*height;
    		break;
    		
    		case 2:
    		imageSize.x=img->getWidth();
			imageSize.y=img->getHeight();
			width=imageSize.x/cols;
        	height=imageSize.y/rows;
        	frmPnt[0]=(sequence[currentFrame]%cols)*width;
        	frmPnt[1]=(sequence[currentFrame]/cols)*height;
    		break;
    	}
    	
    	bool onScreen = true;
    	
    	if(a!=NULL)
    	{
    		//a->width = width;
    		//a->height = height;
    		
    		onScreen = a->isOnScreen();
    	}
    	
    	int drawX1,drawY1,drawX2,drawY2;
    	if(singleframe)
    	{
    		drawX1 = 0;
    		drawY1 = 0;
    		drawX2 = width;
    		drawY2 = height;
    	}
    	else
    	{
    		drawX1 = frmPnt[0];
    		drawY1 = frmPnt[1];
    		drawX2 = frmPnt[0]+width;
    		drawY2 = frmPnt[1]+height;
    		
    	}
    	
    	if(onScreen)
    	{
    		x1 -= View::x;
    		y1 -= View::y;
			x2 -= View::x;
    		y2 -= View::y;
    	}
    	
    	if(a!=NULL)
    	{
    		if(!a->visible)
    		{
    			onScreen = false;
    		}
    	}
    		
    	if(onScreen)
    	{
	    	if(mirrored)
	    	{
				if(mirroredVertical)
				{
					g.drawImage(img ,(x2), (y2), (x1), (y1), drawX1,drawY1,drawX2,drawY2);
				}
				else
				{
	    			g.drawImage(img ,(x2), (y1), (x1), (y2), drawX1,drawY1,drawX2,drawY2);
				}
	    	}
	    	else
	    	{
				if(mirroredVertical)
				{
					g.drawImage(img, (x1), (y2), (x2), (y1), drawX1,drawY1,drawX2,drawY2);
				}
				else
				{
	    			g.drawImage(img, (x1), (y1), (x2), (y2), drawX1,drawY1,drawX2,drawY2);
				}
	    	}
    	}
    	recentFrame = currentFrame;
	}
	
	void Animation::nextFrame(Actor*a, Graphics2D& g, long gameTime, float x1, float y1, double scale, bool relativeToScreen)
	{
		if(direction == FORWARD)
		{
			if(currentFrame>=(frames-1))
			{
				currentFrame=0;
				if(a!=NULL)
				{
					if(a->isEventEnabled(Actor::EVENT_ANIMATIONFINISH))
	    			{
	                	a->onAnimationFinish(name); //is called when Animation has finished the last frame. defined in Actor
	                	if(!this->name.equals(a->anim->name))
	                	{
	                		a->drawActor(g, gameTime, x1, y1, scale, relativeToScreen);
	                		return;
	                	}
	    			}
				}
			}
			else
			{
				currentFrame++;
			}
		}
		else if(direction == BACKWARD)
		{
			if(currentFrame<=0)
			{
				currentFrame=(frames-1);
				if(a!=NULL)
				{
					if(a->isEventEnabled(Actor::EVENT_ANIMATIONFINISH))
	    			{
	                	a->onAnimationFinish(name); //is called when Animation has finished the last frame. defined in Actor
	                	if(!this->name.equals(a->anim->name))
	                	{
	                		a->drawActor(g, gameTime, x1, y1, scale, relativeToScreen);
	                		return;
	                	}
	    			}
				}
			}
			else
			{
				currentFrame--;
			}
		}
		else if(direction == STOPPED)
		{
			currentFrame=currentFrame+0;
		}
		drawFrame(a,g,currentFrame,x1,y1,scale,relativeToScreen);
	}
	
	void Animation::setCurrentFrame(int fNum) //sets the current frame of the Animation
	{
		if((fNum<frames)&&(fNum>=0))
		{
			currentFrame=fNum;
		}
		else
		{
			currentFrame=0;
		}
	}
	
	int Animation::getLastFrame()
	{
    	return recentFrame;
	}
    
	int Animation::getCurrentFrame() //returns the current frame of the Animation
	{
    	return currentFrame;
	}
	
	int Animation::getSequenceFrame(int seqNum)
	{
		return sequence[seqNum];
	}
	
	unsigned char Animation::getDirection()
	{
		return direction;
	}
    
	ArrayList<String> Animation::getAllFilenames()
	{
    	if(animType == 0)
    	{
    		ArrayList<String> files = ArrayList<String>();
    		for(int i=0; i<frames; i++)
    		{
    			files.add(names[i]);
    		}
    		return files;
    	}
    	else
    	{
    		ArrayList<String> files = ArrayList<String>();
    		files.add(names[0]);
    		return files;
    	}
	}
}