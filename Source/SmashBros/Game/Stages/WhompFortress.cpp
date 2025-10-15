
#include "WhompFortress.h"

namespace SmashBros
{
	WhompFortress::WhompFortress(float x1, float y1) : Stage(x1, y1)
	{
		setSpawnPoint(0, 0,0);
		setSpawnPoint(1, -110,-110);
		setSpawnPoint(2,  110,-110);
		setSpawnPoint(3,   50, -10);
		setSpawnPoint(4,  -50, -10);
		
		bottomViewBorder = 295;
		topViewBorder = -340;
		leftViewBorder = -372;
		rightViewBorder = 372;
		
		leftBorder = -500;
		topBorder = -430;
		rightBorder = 500;
		bottomBorder = 250;
		
		setItemBoundaries(-350, -160, 350, 100);
		//showItemBoundaries(true);
		
		loadGameElements();
		loadPlatforms();
		loadHangPoints();
		loadForeground();
		loadGround();
		
		setBackground("Images/Game/Stages/WhompFortress/bg.png");
		setBackgroundScale(1.45);
		setBackgroundType(BG_FIXED);
		
		//setWireframeColor(Color.blue);
		//showWireframes(true);
		
		MusicManager::loadSong("Whomp Fortress");
	}

	WhompFortress::~WhompFortress()
	{
		//
	}
	
	void WhompFortress::loadGameElements()
	{
		GameElement* bg;

		bg = new GameElement(-15, -100);
		Animation* anim = new Animation("normal", 1, 1, 1);
		anim->addFrame("Images/Game/Stages/WhompFortress/mg.png");
		bg->addAnimation(anim);
		bg->changeAnimation("normal", FORWARD);
		addElement(bg);
	}
	
	void WhompFortress::loadPlatforms()
	{
		Platform* plat;

		plat = new Platform(Platform::TYPE_GOTHROUGH, 1, 25);
		plat->addAnimation(new Animation("normal", 1, "Images/Game/Stages/WhompFortress/floatplat.png"));
		plat->changeAnimation("normal", FORWARD);
		plat->setVisible(false);
		addPlatform(plat);

		plat = new Platform(Platform::TYPE_NORMAL, 0,100);
		Animation*anim;
		anim = new Animation("normal", 5, 38, 1);
		anim->addFrame("Images/Game/Stages/WhompFortress/platform.png");
		plat->addAnimation(anim);
		plat->changeAnimation("normal", FORWARD);
		plat->setVisible(false);
		addPlatform(plat);

		plat = new Platform(Platform::TYPE_NORMAL, 1, 25);
		plat->addAnimation(new Animation("normal", 1, "Images/Game/Stages/WhompFortress/plat.png"));
		plat->changeAnimation("normal", FORWARD);
		plat->setVisible(false);
		addPlatform(plat);

		plat = new Platform(Platform::TYPE_NORMAL, -15, -83);
		plat->addAnimation(new Animation("normal", 1, "Images/Game/Stages/WhompFortress/plat2.png"));
		plat->changeAnimation("normal", FORWARD);
		plat->setVisible(false);
		addPlatform(plat);

		plat = new Platform(Platform::TYPE_NORMAL, 0,-140);
		plat->addAnimation(new Animation("normal",1,"Images/Game/Stages/WhompFortress/slides.png"));
		plat->changeAnimation("normal", FORWARD);
		plat->setVisible(false);
		addPlatform(plat);

		plat = new Platform(Platform::TYPE_NORMAL, -15, -240);
		plat->addAnimation(new Animation("normal", 1, "Images/Game/Stages/WhompFortress/bumper.png"));
		plat->changeAnimation("normal", FORWARD);
		plat->setVisible(false);
		addPlatform(plat);
	}
	
	void WhompFortress::loadForeground()
	{
		GameElement* foreground;

		foreground = new GameElement(0, 180);
		foreground->addAnimation(new Animation("normal", 4, "Images/Game/Stages/WhompFortress/bgplatform.png"));
		foreground->changeAnimation("normal", FORWARD);
		addForeground(foreground);
		
		foreground = new GameElement(1, 25);
		foreground->addAnimation(new Animation("normal", 4, "Images/Game/Stages/WhompFortress/fg.png"));
		foreground->changeAnimation("normal", FORWARD);
		addForeground(foreground);
	}
	
	void WhompFortress::loadHangPoints()
	{
		HangPoint*hp;
		
		// left platform
		hp = new HangPoint(HangPoint::LEFT,-140,25);
		//hp->setVisible(true);
		//hp->setFilled(true);
		//hp->setColor(Color::GREEN);
		addHangPoint(hp);
		
		// right platform
		hp = new HangPoint(HangPoint::RIGHT,105,25);
		//hp->setVisible(true);
		//hp->setFilled(true);
		//hp->setColor(Color::GREEN);
		addHangPoint(hp);
	}
	
	void WhompFortress::loadGround()
	{
	}
	
	void WhompFortress::Draw(Graphics2D&g, long gameTime)
	{
		Stage::Draw(g, gameTime);
	}


}
