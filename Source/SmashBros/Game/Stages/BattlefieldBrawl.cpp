
#include "BattlefieldBrawl.h"

namespace SmashBros
{
	BattlefieldBrawl::BattlefieldBrawl(float x1, float y1) : Stage(x1, y1)
	{
		setSpawnPoint(0, 0,0);
		setSpawnPoint(1,  115, -70);
		setSpawnPoint(2, -115, -70);
		setSpawnPoint(3,    0,-135);
		setSpawnPoint(4,    0, -35);
		
		bottomViewBorder = 276;
		topViewBorder = -276;
		leftViewBorder = -400;
		rightViewBorder = 400;
		
		topBorder = -420;
		
		setItemBoundaries(-200, -225, 200, 60);
		
		loadGameElements();
		loadPlatforms();
		loadHangPoints();
		
		setBackground("Images/Game/Stages/BattlefieldBrawl/bg.jpg");
		setBackgroundScale(1.45);
		setBackgroundType(BG_FIXED);
		
		//this.setWireframeColor(Color.blue);
		//this.showWireframes(true);
		
		MusicManager::loadSong("Battlefield v2");
	}

	BattlefieldBrawl::~BattlefieldBrawl()
	{
		//
	}
	
	void BattlefieldBrawl::loadGameElements()
	{
		GameElement*bg;
		
		bg = new GameElement(0,30);
		Animation*anim = new Animation("normal", 1,1,1);
		anim->addFrame("Images/Game/Stages/BattlefieldBrawl/mainstage.png");
		bg->addAnimation(anim);
		bg->changeAnimation("normal", FORWARD);
		addElement(bg);
		
		bg = new GameElement(0,-70);
		bg->addAnimation(new Animation("normal",1,"Images/Game/Stages/BattlefieldBrawl/plat_middle.png"));
		bg->changeAnimation("normal", FORWARD);
		addElement(bg);
		
		bg = new GameElement(-110, -2);
		bg->addAnimation(new Animation("normal",1,"Images/Game/Stages/BattlefieldBrawl/plat_side.png"));
		bg->changeAnimation("normal", FORWARD);
		addElement(bg);
		
		bg = new GameElement(110, -2);
		anim = new Animation("normal",1,"Images/Game/Stages/BattlefieldBrawl/plat_side.png");
		anim->mirror(true);
		bg->addAnimation(anim);
		bg->changeAnimation("normal", FORWARD);
		addElement(bg);
	}
	
	void BattlefieldBrawl::loadPlatforms()
	{
		Platform*plat;
		
		plat = new Platform(Platform::TYPE_NORMAL, 0,112);
		plat->addAnimation(new Animation("normal",1,"Images/Game/Stages/BattlefieldBrawl/main_plat.png"));
		plat->changeAnimation("normal", FORWARD);
		plat->setVisible(false);
		addPlatform(plat);
		
		plat = new Platform(Platform::TYPE_GOTHROUGH, -46, -74, 92, 10);
		addPlatform(plat);
		
		plat = new Platform(Platform::TYPE_GOTHROUGH, -154, -7, 90, 10);
		addPlatform(plat);
		
		plat = new Platform(Platform::TYPE_GOTHROUGH, 66, -7, 90, 10);
		addPlatform(plat);
	}
	
	void BattlefieldBrawl::loadHangPoints()
	{
		HangPoint*hp;
		
		hp = new HangPoint(HangPoint::LEFT,-212,68);
		addHangPoint(hp);
		
		hp = new HangPoint(HangPoint::RIGHT,204,68);
		addHangPoint(hp);
	}
	
	void BattlefieldBrawl::Draw(Graphics2D&g, long gameTime)
	{
		Stage::Draw(g, gameTime);
	}
}