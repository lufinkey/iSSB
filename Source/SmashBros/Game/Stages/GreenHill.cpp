
#include "GreenHill.h"

namespace SmashBros
{
	GreenHill::GreenHill(float x1, float y1) : Stage(x1, y1)
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
		
		setBackground("Images/Game/Stages/GreenHill/bg.jpg");
		setBackgroundScale(1.45);
		setBackgroundType(BG_FIXED);
		
		//this.setWireframeColor(Color.blue);
		//this.showWireframes(true);
		
		MusicManager::loadSong("Green Hill Zone");
	}

	GreenHill::~GreenHill()
	{
		//
	}
	
	void GreenHill::loadGameElements()
	{
		GameElement*bg;
		
		bg = new GameElement(0,30);
		Animation*anim = new Animation("normal", 1,1,1);
		anim->addFrame("Images/Game/Stages/GreenHill/mainstage.png");
		bg->addAnimation(anim);
		bg->changeAnimation("normal", FORWARD);
		addElement(bg);
	}
	
	void GreenHill::loadPlatforms()
	{
	}
	
	void GreenHill::loadHangPoints()
	{
	}
	
	void GreenHill::Draw(Graphics2D&g, long gameTime)
	{
		Stage::Draw(g, gameTime);
	}
}
