
#include "../forwards.h"
#include "PrimitiveActor.h"
#include "../Graphics/Graphics2D.h"

#pragma once

namespace GameEngine
{
	class WireframeActor : public PrimitiveActor
	{
	private:
		static const int totalEvents = 8;
		bool enabledEvents[8];
		bool clicked,prevclicked;
		bool visible;
	    bool filled;
	    Color color;
	    bool mouseover;
		bool relative;
		bool prevMouseover;
		long touchId;
		long currentTouchId;
		float xSpeed,ySpeed;
		float xprev, yprev;
		Rect getCollideOverlapArea(Actor*a2);
		
		bool checkHover(float x1, float y1);

	protected:
		void drawActor(Graphics2D& g,long gameTime,float x1, float y1,double scale);

	public:
		static const unsigned char EVENT_MOUSECLICK = 0;
		static const unsigned char EVENT_MOUSERELEASE = 1;
		static const unsigned char EVENT_MOUSEENTER = 2;
		static const unsigned char EVENT_MOUSELEAVE = 3;
		
	    float xvelocity,yvelocity;
		
		virtual ~WireframeActor();
		WireframeActor(const WireframeActor&actor);
		WireframeActor(float x1=0, float y1=0, int w=1, int h=1);
		
		void setVisible(bool toggle);
		bool isVisible();
		
		void setFilled(bool toggle);
		bool isFilled();
		
		void setColor(const Color&c);
		Color getColor();
	    
		bool isColliding(Actor*collide);
	    bool rectsColliding(WireframeActor*collide);
	    bool rectsColliding(Actor*collide);
		bool circlesColliding(WireframeActor*collide);
		bool circlesColliding(Actor*collide);
		bool circlesColliding(WireframeActor*collide, double mult);
		bool circlesColliding(Actor*collide, double mult);
		
		virtual void Update(long gameTime);
		virtual void Draw(Graphics2D& g,long gameTime);
	    
	    bool isEventEnabled(unsigned char eventCode);
	    void setEventEnabled(unsigned char eventCode, bool toggle);
	    
	    virtual void onMouseEnter();
	    virtual void onMouseLeave();
	    virtual void onClick();
	    virtual void onRelease();
		
		void relativeToView(bool toggle);
	    bool mouseOver();
	    
	    bool isClicked();
		bool wasClicked();
		
		long getTouchId();

	    virtual bool isOnScreen();

		float getXSpeed();
		float getYSpeed();
		
		float getXPrev();
		float getYPrev();
	};
}