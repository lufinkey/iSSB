
#pragma once

namespace GameEngine
{
	typedef struct
	{
		float x,y; //the x and y coordinate of the touch
		long ID; //unique ID assigned by GameEngine (uniquely identifies a touch. touches increment until 10000 and then repeat)
		long givenID; //ID given by SDL (fingerID)
	} TouchPoint;
	
	//bullshit to get rid of the stupid "unused variable warning". You know, in a header file. Because that makes sense
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-variable"
#endif
	static long TouchPoint_currentID = 0;
#ifdef __clang__
#pragma clang diagnostic pop
#endif
	
	static TouchPoint createTouchPoint(long ID, long givenID, float x, float y)
	{
		TouchPoint point;
		point.ID = ID;
		point.givenID = givenID;
		point.x = x;
		point.y = y;
		return point;
	}
}