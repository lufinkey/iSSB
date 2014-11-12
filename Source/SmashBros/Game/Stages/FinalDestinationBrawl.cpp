
#include "FinalDestinationBrawl.h"

namespace SmashBros
{
	FinalDestinationBrawl::FinalDestinationBrawl(float x1, float y1) : Stage(x1,y1)
	{
		fg_left = null;
		fg_right = null;

		setSpawnPoint(0, 0,0);
		setSpawnPoint(1,  -150, -150);
		setSpawnPoint(2,   150, -150);
		setSpawnPoint(3,  -50,  -150);
		setSpawnPoint(4,   50,  -150);
		
		bottomViewBorder = 276;
		topViewBorder = -276;
		
		topBorder = - 460;
		
		setItemBoundaries(-274, -250, 274, -70);
		
		loadGameElements();
		loadPlatforms();
		loadHangPoints();
		
		setBackground("Images/Game/Stages/FinalDestinationBrawl/bg.png");
		setBackgroundScale(1.6);
		setBackgroundType(BG_FIXED);
		
		//setWireframeColor(Color.green);
		//showWireframes(true);
		
		MusicManager::loadSong("Final Destination");
	}

	FinalDestinationBrawl::~FinalDestinationBrawl()
	{
		if(fg_left!=null)
		{
			delete fg_left;
		}
		if(fg_right!=null)
		{
			delete fg_right;
		}
	}
	
	void FinalDestinationBrawl::loadGameElements()
	{
		GameElement*bg;
		
		float y1 = 30;
		
		bg = new GameElement(0,y1);
		Animation*anim = new Animation("normal", 6,6,1);
		anim->addFrame("Images/Game/Stages/FinalDestinationBrawl/mainstage.png");
		bg->addAnimation(anim);
		bg->changeAnimation("normal", FORWARD);
		bg->setScale(1.4f);
		addElement(bg);
		
		fglx = (-180*bg->getScale());
		fgly = (float)(-23.5f*bg->getScale()) + y1;
		
		fg_left = new GameElement(x + fglx, y + fgly);
		fg_left->addAnimation(new Animation("normal",1,"Images/Game/Stages/FinalDestinationBrawl/foreground_left.png"));
		fg_left->changeAnimation("normal", FORWARD);
		fg_left->setScale(bg->getScale());
		
		fgrx = (178*bg->getScale());
		fgry = (-30.5f*bg->getScale()) + y1;
		
		fg_right = new GameElement(x + fgrx, y + fgry);
		fg_right->addAnimation(new Animation("normal",1,"Images/Game/Stages/FinalDestinationBrawl/foreground_right.png"));
		fg_right->changeAnimation("normal", FORWARD);
		fg_right->setScale(bg->getScale());
	}
	
	void FinalDestinationBrawl::loadPlatforms()
	{
		Platform*plat;
		
		plat = new Platform(Platform::TYPE_NORMAL, 0 - 274, 0 - 66, 548, 50);
		addPlatform(plat);
		
		plat = new Platform(Platform::TYPE_NORMAL, 0 - 240, 0 - 30, 480, 70);
		addPlatform(plat);
		
		plat = new Platform(Platform::TYPE_NORMAL, 0 - 180, 0 + 20, 360, 70);
		addPlatform(plat);
	}
	
	void FinalDestinationBrawl::loadHangPoints()
	{
		HangPoint*hp;
		
		hp = new HangPoint(HangPoint::LEFT,-287,-64);
		addHangPoint(hp);
		
		hp = new HangPoint(HangPoint::RIGHT,277,-64);
		addHangPoint(hp);
	}
	
	void FinalDestinationBrawl::Draw(Graphics2D&g, long gameTime)
	{
		fg_left->x = x + fglx;
		fg_left->y = y + fgly;
		fg_right->x = x + fgrx;
		fg_right->y = y + fgry;
		
		drawBackground(g,gameTime);
		drawBottomLayer(g,gameTime);
		drawMiddleLayer(g,gameTime);
		
		fg_left->Draw(g, gameTime);
		fg_right->Draw(g, gameTime);
		
		drawTopLayer(g,gameTime);
	}
}