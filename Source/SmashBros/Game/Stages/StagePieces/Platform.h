
#include "../../../GameElement.h"
#include "../../../SmashForwards.h"

#pragma once

namespace SmashBros
{
	class Platform : public GameElement
	{
		friend class Player;
	private:
		class WireframeElement : public WireframeActor
		{
		public:
			WireframeElement(float x1, float y1, int width, int height);
			~WireframeElement();

			virtual void Draw(Graphics2D&g, long gameTime);
		};

		WireframeElement*box;
		WireframeElement*ground;

	protected:
		byte type;
		byte collideType;

	public:
		static const byte TYPE_NORMAL = 1;
		static const byte TYPE_GOTHROUGH = 2;

		static const byte COLLIDE_BOX = 1;
		static const byte COLLIDE_SOLID = 2;

		Platform(byte type, float x1, float y1);
		Platform(byte type, float x1, float y1, int width, int height);
		virtual ~Platform();

		virtual void Update(long gameTime);
		virtual void Draw(Graphics2D&g, long gameTime);

		boolean checkGroundCollision(SmashBros::Player*playr);
		byte getType();
		byte getCollideType();
		WireframeActor*getBox();
		byte getBoxDirection(GameElement*collide);
		void setVisible(boolean toggle);

		virtual void onPlayerCollide(Player*collide, byte dir);
		virtual void whilePlayerColliding(Player*collide, byte dir);
		virtual void finishPlayerCollide(Player*collide, byte dir);
	};
}