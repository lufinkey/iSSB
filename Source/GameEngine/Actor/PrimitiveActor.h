
#include "../forwards.h"
#include "../GlobalDefs.h"

#pragma once

namespace GameEngine
{
	class PrimitiveActor //just made this so that I didn't have to reference a class everytime i wanted to call these methods and variables
	{
	private:
		unsigned char actorType;
		friend class Actor;
		friend class WireframeActor;
		friend class TextActor;
		
	public:
		static const unsigned char ACTORTYPE_PRIMITIVE = 0;
		static const unsigned char ACTORTYPE_ACTOR = 1;
		static const unsigned char ACTORTYPE_WIREFRAME = 2;
		static const unsigned char ACTORTYPE_TEXT = 3;
		
		static const char DIR_UP = 1;
		static const char DIR_UPRIGHT = 2;
		static const char DIR_RIGHT = 3;
		static const char DIR_DOWNRIGHT = 4;
		static const char DIR_DOWN = 5;
		static const char DIR_DOWNLEFT = 6;
		static const char DIR_LEFT = 7;
		static const char DIR_UPLEFT = 8;
		
		float x;
		float y;
		
		int width;
		int height;
		
		PrimitiveActor();
		virtual ~PrimitiveActor();
		
		unsigned char getActorType();
		
		static unsigned char getDir(float x1,float y1,float x2,float y2);
		static unsigned char getDir2(float x1,float y1,float x2,float y2);
		static unsigned char getDir(const Rectangle& r1, const Rectangle& r2);
		static unsigned char getDir(const RectangleF& r1, const RectangleF& r2);
		static unsigned char getDir(PrimitiveActor*a1, PrimitiveActor*a2);
		
		static double distance(float x1,float y1,float x2,float y2);
		static double distanceUnSqr(float x1,float y1,float x2,float y2);
		
		static double direction(double x1, double y1, double x2, double y2);
		static double correctDegrees(double degrees);
	};
}