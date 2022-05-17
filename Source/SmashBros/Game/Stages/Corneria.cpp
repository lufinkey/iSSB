
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
		
		bottomViewBorder = 295;
		topViewBorder = -340;
		leftViewBorder = -372;
		rightViewBorder = 372;
		
		leftBorder = -500;
		topBorder = -430;
		rightBorder = 500;
		bottomBorder = 370;
		
		setItemBoundaries(-300, -300, 295, -50);
		//showItemBoundaries(true);
		
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
	}
	
	void Corneria::loadPlatforms()
	{
		Platform* plat;
		plat = new Platform(Platform::TYPE_NORMAL, 0,20);
		plat->addAnimation(new Animation("normal",1,"Images/Game/Stages/Corneria/plat.png"));
		plat->changeAnimation("normal", FORWARD);
		plat->setVisible(false);
		addPlatform(plat);
	}
	
	void Corneria::loadHangPoints()
	{
		HangPoint*hp;
		
		// nose of the plane
		hp = new HangPoint(HangPoint::LEFT,-332,-8);
		//hp->setVisible(true);
		//hp->setFilled(true);
		//hp->setColor(Color::GREEN);
		addHangPoint(hp);
		
		// guns of the plane
		hp = new HangPoint(HangPoint::LEFT,-210,75);
		//hp->setVisible(true);
		//hp->setFilled(true);
		//hp->setColor(Color::GREEN);
		addHangPoint(hp);
		
		// tail of the plane
		hp = new HangPoint(HangPoint::RIGHT,286,18);
		//hp->setVisible(true);
		//hp->setFilled(true);
		//hp->setColor(Color::GREEN);
		addHangPoint(hp);
	}
	
	void Corneria::loadGround()
	{
	}
	
	void Corneria::Draw(Graphics2D&g, long gameTime)
	{
		Stage::Draw(g, gameTime);
	}
}
