
#include "WorldTournament.h"

namespace SmashBros
{
	WorldTournament::WorldTournament(float x1, float y1) : Stage(x1, y1)
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
		
		setBackground("Images/Game/Stages/WorldTournament/bg.png");
		setBackgroundScale(1.45);
		setBackgroundType(BG_FIXED);
		
		//setWireframeColor(Color.blue);
		//showWireframes(true);
		
		MusicManager::loadSong("Battlefield v2");
	}

	WorldTournament::~WorldTournament()
	{
		//
	}
	
	void WorldTournament::loadGameElements()
	{
		bg = new GameElement(0,20);
		anim = new Animation("normal", 1,1,1);
		anim->addFrame("Images/Game/Stages/WorldTournament/mainstage.png");
		bg->addAnimation(anim);
		bg->changeAnimation("normal", FORWARD);
		addElement(bg);
	}
	
	void WorldTournament::loadPlatforms()
	{
	}
	
	void WorldTournament::loadHangPoints()
	{
	}
	
	void WorldTournament::loadGround()
	{
		GameElement*ground;
		
		ground = new GameElement(0,70);
		ground->addAnimation(new Animation("normal",1,"Images/Game/Stages/WorldTournament/ground.png"));
		ground->changeAnimation("normal", FORWARD);
		addGround(ground);
	}
	
	void WorldTournament::Draw(Graphics2D&g, long gameTime)
	{
		Stage::Draw(g, gameTime);
	}
}
