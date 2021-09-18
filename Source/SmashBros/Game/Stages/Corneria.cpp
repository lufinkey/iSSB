
#include "Corneria.h"

namespace SmashBros
{
	Corneria::Corneria(float x1, float y1) : Stage(x1, y1)
	{
		setSpawnPoint(0, 0,0);
		setSpawnPoint(1, -110,-110);
		setSpawnPoint(2,  110,-110);
		setSpawnPoint(3,    0,-138);
		setSpawnPoint(4,    0, -10);
		
		bottomViewBorder = 255;
		topViewBorder = -255;
		leftViewBorder = -320;
		rightViewBorder = 320;
		
		leftBorder = -400;
		topBorder = -380;
		rightBorder = 400;
		bottomBorder = 320;
		
		setItemBoundaries(-200, -150, 190, 80);
		
		loadGameElements();
		loadPlatforms();
		loadHangPoints();
		loadGround();
		
		setBackground("Images/Game/Stages/Corneria/bg.png");
		setBackgroundScale(1.45);
		setBackgroundType(BG_FIXED);
		
		//setWireframeColor(Color.blue);
		//showWireframes(true);
		
		MusicManager::loadSong("Battlefield v2");
	}

	Corneria::~Corneria()
	{
		//
	}
	
	void Corneria::loadGameElements()
	{
		GameElement*bg;
		
		bg = new GameElement(0,80);
		Animation*anim = new Animation("normal", 1,1,1);
		anim->addFrame("Images/Game/Stages/Corneria/bg2.png");
		bg->addAnimation(anim);
		bg->changeAnimation("normal", FORWARD);
		bg->setScale(1.05f);
		addElement(bg);
		
		bg = new GameElement(0,20);
		anim = new Animation("normal", 1,1,1);
		anim->addFrame("Images/Game/Stages/Corneria/mainstage.png");
		bg->addAnimation(anim);
		bg->changeAnimation("normal", FORWARD);
		addElement(bg);
	}
	
	void Corneria::loadPlatforms()
	{
		Platform*plat;
		
		plat = new Platform(Platform::TYPE_NORMAL, 0,20);
		plat->addAnimation(new Animation("normal",1,"Images/Game/Stages/Corneria/plat.png"));
		plat->changeAnimation("normal", FORWARD);
		plat->setVisible(false);
		addPlatform(plat);
	}
	
	void Corneria::loadHangPoints()
	{
		HangPoint*hp;
		
		hp = new HangPoint(HangPoint::LEFT,-217,88);
		addHangPoint(hp);
		
		hp = new HangPoint(HangPoint::RIGHT,197,99);
		addHangPoint(hp);
	}
	
	void Corneria::loadGround()
	{
		GameElement*ground;
		
		ground = new GameElement(0,70);
		ground->addAnimation(new Animation("normal",1,"Images/Game/Stages/Corneria/ground.png"));
		ground->changeAnimation("normal", FORWARD);
		addGround(ground);
	}
	
	void Corneria::Draw(Graphics2D&g, long gameTime)
	{
		Stage::Draw(g, gameTime);
	}
}