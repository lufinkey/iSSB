
#include "HillsideBattleground.h"

namespace SmashBros
{
	HillsideBattleground::HillsideBattleground(float x1, float y1) : Stage(x1, y1)
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
		
		setBackground("Images/Game/Stages/HillsideBattleground/bg.png");
		setBackgroundScale(1.45);
		setBackgroundType(BG_FIXED);
		
		//setWireframeColor(Color.blue);
		//showWireframes(true);
		
		MusicManager::loadSong("Battlefield v2");
	}

	HillsideBattleground::~HillsideBattleground()
	{
		//
	}
	
	void HillsideBattleground::loadGameElements()
	{
		GameElement*bg;
		
		bg = new GameElement(0,80);
		Animation*anim = new Animation("normal", 1,1,1);
		anim->addFrame("Images/Game/Stages/HillsideBattleground/bg2.png");
		bg->addAnimation(anim);
		bg->changeAnimation("normal", FORWARD);
		bg->setScale(1.05f);
		addElement(bg);
		
		bg = new GameElement(0,20);
		anim = new Animation("normal", 1,1,1);
		anim->addFrame("Images/Game/Stages/HillsideBattleground/mainstage.png");
		bg->addAnimation(anim);
		bg->changeAnimation("normal", FORWARD);
		addElement(bg);
		
		bg = new GameElement(-4,-92);
		bg->addAnimation(new Animation("normal",1,"Images/Game/Stages/HillsideBattleground/fplat2.png"));
		bg->changeAnimation("normal", FORWARD);
		bg->setVisible(false);
		addElement(bg);
		
		bg = new GameElement(-105, -33);
		bg->addAnimation(new Animation("normal",1,"Images/Game/Stages/HillsideBattleground/fplat1.png"));
		bg->changeAnimation("normal", FORWARD);
		bg->setVisible(false);
		addElement(bg);
		
		bg = new GameElement(98, -33);
		bg->addAnimation(new Animation("normal",1,"Images/Game/Stages/HillsideBattleground/fplat1.png"));
		bg->changeAnimation("normal", FORWARD);
		bg->setVisible(false);
		addElement(bg);
	}
	
	void HillsideBattleground::loadPlatforms()
	{
		Platform*plat;
		
		plat = new Platform(Platform::TYPE_NORMAL, 0,20);
		plat->addAnimation(new Animation("normal",1,"Images/Game/Stages/HillsideBattleground/plat.png"));
		plat->changeAnimation("normal", FORWARD);
		plat->setVisible(false);
		addPlatform(plat);
		
		plat = new Platform(Platform::TYPE_GOTHROUGH, -46.5f, -99.5f, 85, 15);
		addPlatform(plat);
		
		plat = new Platform(Platform::TYPE_GOTHROUGH, -128, -39, 46, 14);
		addPlatform(plat);
		
		plat = new Platform(Platform::TYPE_GOTHROUGH, 75, -39, 46, 14);
		addPlatform(plat);
	}
	
	void HillsideBattleground::loadHangPoints()
	{
		HangPoint*hp;
		
		hp = new HangPoint(HangPoint::LEFT,-217,88);
		addHangPoint(hp);
		
		hp = new HangPoint(HangPoint::RIGHT,197,99);
		addHangPoint(hp);
	}
	
	void HillsideBattleground::loadGround()
	{
		GameElement*ground;
		
		ground = new GameElement(0,70);
		ground->addAnimation(new Animation("normal",1,"Images/Game/Stages/HillsideBattleground/ground.png"));
		ground->changeAnimation("normal", FORWARD);
		addGround(ground);
	}
	
	void HillsideBattleground::Draw(Graphics2D&g, long gameTime)
	{
		Stage::Draw(g, gameTime);
	}
}