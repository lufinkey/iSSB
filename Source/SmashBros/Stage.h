
#include "Game/Stages/StagePieces/Platform.h"
#include "Game/Stages/StagePieces/HangPoint.h"
#include "Projectile.h"
#include "MusicManager.h"
#include "SmashForwards.h"

#pragma once

namespace SmashBros
{
	class Stage
	{
		friend class Camera;
		friend class Item;
		friend class ItemManager;
		friend class Player;
		friend class ProjectileManager;
	private:
		Animation*background;
		double bgScale;

		GameEngine::Rectangle itemBounds;
		boolean showItemBounds;
		boolean showWires;

		byte bgType;

		ArrayList<String> files;

		ArrayList<Platform*> platforms;
		ArrayList<Vector2<Vector2f> > platCoords;

		ArrayList<GameElement*> elements;
		ArrayList<Vector2<Vector2f> > elementCoords;

		ArrayList<HangPoint*> hangs;
		ArrayList<Vector2<Vector2f> > hangCoords;

		ArrayList<GameElement*> foregrounds;
		ArrayList<Vector2<Vector2f> > fgCoords;

		ArrayList<GameElement*> ground;
		ArrayList<Vector2<Vector2f> > groundCoords;

		Vector2i spawns[7];

		double gravity;
		double terminalVelocity;

		void checkPlayerCollisions(Player*playr);
		
		void updatePlatform(int index);
		void updateElement(int index);
		void updateForeground(int index);
		void updateHangPoint(int index);
		void updateGround(int index);

		byte checkPlatformCollision(Player*p, Platform*collide);
		byte checkItemPlatformCollision(Item*item, Platform*collide);
		void itemPlatformCollisions(Item*item);
		boolean wireframeCollision(Player*playr, WireframeActor*collide);
		byte checkProjectileCollision(Projectile*p, Platform*collide);

		byte borderColliding(Player*p);

	protected:
		int topBorder;
		int bottomBorder;
		int leftBorder;
		int rightBorder;

		int topViewBorder;
		int bottomViewBorder;
		int leftViewBorder;
		int rightViewBorder;

		void setItemBoundaries(int x1, int y1, int x2, int y2);
		void showItemBoundaries(boolean toggle);
		void setBackgroundScale(double scale);
		void loadFile(const String&fileName);

		void drawBackground(Graphics2D&g, long gameTime);
		void drawBottomLayer(Graphics2D&g, long gameTime);
		void drawMiddleLayer(Graphics2D&g, long gameTime);
		void drawTopLayer(Graphics2D&g, long gameTime);

	public:
		static const byte BG_NORMAL = 0;
		static const byte BG_FIXED = 1;

		int x,y;

		Stage(int x1, int y1);
		virtual ~Stage();

		virtual void Update(long gameTime);
		virtual void Draw(Graphics2D&g, long gameTime);

		void Unload();
		void setBackground(String imgName);
		void setBackgroundType(byte type);
		GameEngine::Rectangle getItemBoundaries();
		
		void showWireframes(boolean toggle);
		void setWireframeColor(const Color&color);
		void setElementColor(const Color&color);

		void setGravity(double grav);
		double getGravity();
		
		void setTerminalVelocity(double terminalVelocity);
		double getTerminalVelocity();

		void addElement(GameElement*a);
		void addPlatform(Platform*plat);
		void addForeground(GameElement*a);
		void addHangPoint(HangPoint*hp);
		void addGround(GameElement*gr);

		void setSpawnPoint(int spawnNo, int x1, int y1);
		Vector2i getSpawnPoint(int spawnNo);
		Rect getBorders();
		Rect getViewBorders();
		boolean checkSafeArea(Player*playr);
	};
}