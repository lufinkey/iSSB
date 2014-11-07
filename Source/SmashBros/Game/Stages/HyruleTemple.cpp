
#include "HyruleTemple.h"

namespace SmashBros
{
	HyruleTemple::HyruleTemple(float x1, float y1) : Stage(x1,y1)
	{
		watchPlat = null;
		
		setSpawnPoint(0, 0,0);
		setSpawnPoint(1, -115, -95);
		setSpawnPoint(2,  198,-162);
		setSpawnPoint(3, -288,-186);
		setSpawnPoint(4, -121,  44);
		
		topViewBorder = -330;
		bottomViewBorder = 315;
		leftViewBorder = -515;
		rightViewBorder = 515;
		
		topBorder = -485;
		bottomBorder = 440;
		leftBorder = -560;
		rightBorder = 560;
		
		setItemBoundaries(-348, -262, 348, -60);
		
		loadGameElements();
		loadPlatforms();
		loadHangPoints();
		loadForeground();
		loadGround();
		
		setBackground("Images/Game/Stages/HyruleTemple/bg.png");
		setBackgroundScale(1.0);
		setBackgroundType(BG_FIXED);
		
		setWireframeColor(Color::BLUE);
		//showWireframes(true);
		
		MusicManager::loadSong("Zelda Theme");
	}

	HyruleTemple::~HyruleTemple()
	{
		//
	}
	
	void HyruleTemple::loadGameElements()
	{
		GameElement*bg;
		
		bg = new GameElement(0,0);
		Animation*anim = new Animation("normal", 1,1,1);
		anim->addFrame("Images/Game/Stages/HyruleTemple/mainstage.png");
		bg->addAnimation(anim);
		bg->changeAnimation("normal", FORWARD);
		addElement(bg);
	}
	
	void HyruleTemple::loadPlatforms()
	{
		Platform*plat;
		
		plat = new Platform(Platform::TYPE_NORMAL, -278, -25);
		plat->addAnimation(new Animation("normal",1,"Images/Game/Stages/HyruleTemple/plat1.png"));
		plat->changeAnimation("normal", FORWARD);
		plat->setVisible(false);
		addPlatform(plat);
		
		plat = new Platform(Platform::TYPE_NORMAL, -85, -59);
		plat->addAnimation(new Animation("normal",1,"Images/Game/Stages/HyruleTemple/plat2.png"));
		plat->changeAnimation("normal", FORWARD);
		plat->setVisible(false);
		addPlatform(plat);
		
		plat = new Platform(Platform::TYPE_NORMAL, 157, 9);
		plat->addAnimation(new Animation("normal",1,"Images/Game/Stages/HyruleTemple/plat3.png"));
		plat->changeAnimation("normal", FORWARD);
		plat->setVisible(false);
		addPlatform(plat);
		
		plat = new Platform(Platform::TYPE_NORMAL, -95, 195.5f);
		plat->addAnimation(new Animation("normal",1,"Images/Game/Stages/HyruleTemple/plat4.png"));
		plat->changeAnimation("normal", FORWARD);
		plat->setVisible(false);
		addPlatform(plat);
		
		plat = new Platform(Platform::TYPE_NORMAL, 65, 209);
		plat->addAnimation(new Animation("normal",1,"Images/Game/Stages/HyruleTemple/plat5.png"));
		plat->changeAnimation("normal", FORWARD);
		plat->setVisible(false);
		addPlatform(plat);
		
		watchPlat = new Platform(Platform::TYPE_NORMAL, 68, -70, 30, 50);
		addPlatform(watchPlat);
		
        plat = new Platform(Platform::TYPE_GOTHROUGH, -292, -97);
		plat->addAnimation(new Animation("normal",1,"Images/Game/Stages/HyruleTemple/float_plat1.png"));
		plat->changeAnimation("normal", FORWARD);
		plat->setVisible(false);
		addPlatform(plat);
		
		plat = new Platform(Platform::TYPE_GOTHROUGH, -193, -41);
		plat->addAnimation(new Animation("normal",1,"Images/Game/Stages/HyruleTemple/float_plat2.png"));
		plat->changeAnimation("normal", FORWARD);
		plat->setVisible(false);
		addPlatform(plat);
		
		plat = new Platform(Platform::TYPE_GOTHROUGH, -201, 11);
		plat->addAnimation(new Animation("normal",1,"Images/Game/Stages/HyruleTemple/float_plat3.png"));
		plat->changeAnimation("normal", FORWARD);
		plat->setVisible(false);
		addPlatform(plat);
		
		plat = new Platform(Platform::TYPE_GOTHROUGH, -67, -136);
		plat->addAnimation(new Animation("normal",1,"Images/Game/Stages/HyruleTemple/float_plat4.png"));
		plat->changeAnimation("normal", FORWARD);
		plat->setVisible(false);
		addPlatform(plat);
		
		plat = new Platform(Platform::TYPE_GOTHROUGH, 196, -80);
		plat->addAnimation(new Animation("normal",1,"Images/Game/Stages/HyruleTemple/float_plat5.png"));
		plat->changeAnimation("normal", FORWARD);
		plat->setVisible(false);
		addPlatform(plat);
		
		plat = new Platform(Platform::TYPE_GOTHROUGH, 284, -172);
		plat->addAnimation(new Animation("normal",1,"Images/Game/Stages/HyruleTemple/float_plat6.png"));
		plat->changeAnimation("normal", FORWARD);
		plat->setVisible(false);
		addPlatform(plat);
		
		plat = new Platform(Platform::TYPE_GOTHROUGH, 283, -103);
		plat->addAnimation(new Animation("normal",1,"Images/Game/Stages/HyruleTemple/float_plat7.png"));
		plat->changeAnimation("normal", FORWARD);
		plat->setVisible(false);
		addPlatform(plat);
	}
	
	void HyruleTemple::loadForeground()
	{
		GameElement*foreground;
		
		foreground = new GameElement(242, -121);
		foreground->addAnimation(new Animation("normal",1,"Images/Game/Stages/HyruleTemple/foreground1.png"));
		foreground->changeAnimation("normal", FORWARD);
		addForeground(foreground);
		
		foreground = new GameElement(-281, -72);
		foreground->addAnimation(new Animation("normal",1,"Images/Game/Stages/HyruleTemple/foreground2.png"));
		foreground->changeAnimation("normal", FORWARD);
		addForeground(foreground);
		
		foreground = new GameElement(-108, -62);
		foreground->addAnimation(new Animation("normal",1,"Images/Game/Stages/HyruleTemple/foreground3.png"));
		foreground->changeAnimation("normal", FORWARD);
		addForeground(foreground);
		
		foreground = new GameElement(-136, 70);
		foreground->addAnimation(new Animation("normal",1,"Images/Game/Stages/HyruleTemple/foreground4.png"));
		foreground->changeAnimation("normal", FORWARD);
		addForeground(foreground);
		
		foreground = new GameElement(2, 87);
		foreground->addAnimation(new Animation("normal",1,"Images/Game/Stages/HyruleTemple/foreground5.png"));
		foreground->changeAnimation("normal", FORWARD);
		addForeground(foreground);
	}
	
	void HyruleTemple::loadHangPoints()
	{
        HangPoint*hp;
		
		hp = new HangPoint(HangPoint::LEFT,-358,-40);
		addHangPoint(hp);
		
		hp = new HangPoint(HangPoint::LEFT,-213,100);
		addHangPoint(hp);
		
		hp = new HangPoint(HangPoint::LEFT,36,181);
		addHangPoint(hp);
		
		hp = new HangPoint(HangPoint::RIGHT,9,137);
		addHangPoint(hp);
		
		hp = new HangPoint(HangPoint::RIGHT,83,181);
		addHangPoint(hp);
		
		hp = new HangPoint(HangPoint::RIGHT,349,-20);
		addHangPoint(hp);
	}
	
	void HyruleTemple::loadGround()
	{
		GameElement*ground;
		
		ground = new GameElement(157, -5);
		ground->addAnimation(new Animation("normal",1,"Images/Game/Stages/HyruleTemple/ground1.png"));
		ground->changeAnimation("normal", FORWARD);
		addGround(ground);
		
		ground = new GameElement(-100, -60);
		ground->addAnimation(new Animation("normal",1,"Images/Game/Stages/HyruleTemple/ground2.png"));
		ground->changeAnimation("normal", FORWARD);
		addGround(ground);
		
		ground = new GameElement(-30, 110);
		ground->addAnimation(new Animation("normal",1,"Images/Game/Stages/HyruleTemple/ground3.png"));
		ground->changeAnimation("normal", FORWARD);
		addGround(ground);
		
		ground = new GameElement(196, -85);
		ground->addAnimation(new Animation("normal",1,"Images/Game/Stages/HyruleTemple/ground4.png"));
		ground->changeAnimation("normal", FORWARD);
		addGround(ground);
	}
	
	void HyruleTemple::Update(long gameTime)
	{
		Stage::Update(gameTime);
	}
	
	void HyruleTemple::Draw(Graphics2D&g, long gameTime)
	{
		Stage::Draw(g, gameTime);
		
	}
}