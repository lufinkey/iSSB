
#include "PrimitiveActor.h"
#include "TextActor.h"
#include "../Output/Console.h"
#include <cmath>

namespace GameEngine
{
	PrimitiveActor::PrimitiveActor()
	{
		x = 0;
		y = 0;
		width = 0;
		height = 0;
	}
	
	PrimitiveActor::~PrimitiveActor()
	{
		//
	}
	
	unsigned char PrimitiveActor::getDir(float x1,float y1,float x2,float y2) //returns the direction of the second set of xy coords based on the first set
	{
    	x2-=x1;
    	y2-=y1;
    	
    	if(y2<0)//second set is above first set
    	{
    		if(x2 == 0)
    		{
    			return DIR_UP;
    		}
    		else
    		{
    			double ratLowLeft = .4142135624;
    			double ratHighLeft = 2.4142135624;
    			double ratLowRight = -ratLowLeft;
    			double ratHighRight = -ratHighLeft;
    			
    			double difRat =  y2/x2;
    			
    			if((difRat<ratLowRight) && (difRat>ratHighRight))
    			{
    				return DIR_UPRIGHT;
    			}
    			else if((difRat>=ratLowRight) && (difRat<=0))
    			{
    				return DIR_RIGHT;
    			}
    			else if((difRat<=ratLowLeft)&&(difRat>=0))
    			{
    				return DIR_LEFT;
    			}
    			else if((difRat<ratHighLeft) && (difRat>ratLowLeft))
    			{
    				return DIR_UPLEFT;
    			}
    			else
    			{
    				return DIR_UP;
    			}
    		}
    	}
    	else if(y2>0)
    	{
    		if(x2==0)
    		{
    			return DIR_DOWN;
    		}
    		else
    		{
    			double ratLowRight = .4142135624;
    			double ratHighRight = 2.4142135624;
    			double ratLowLeft = -ratLowRight;
    			double ratHighLeft = -ratHighRight;
    			
    			double difRat =  y2/x2;
    			
    			if((difRat>ratHighLeft)&&(difRat<ratLowLeft))
    			{
    				return DIR_DOWNLEFT;
    			}
    			else if((difRat>=ratLowLeft)&&(difRat<=0))
    			{
    				return DIR_LEFT;
    			}
    			else if((difRat<=ratLowRight)&&(difRat>=0))
    			{
    				return DIR_RIGHT;
    			}
    			else if((difRat>ratLowRight)&&(difRat<ratHighRight))
    			{
    				return DIR_DOWNRIGHT;
    			}
    			else
    			{
    				return DIR_DOWN;
    			}
    		}
    	}
    	else
    	{
    		if(x2<0)
    		{
    			return DIR_LEFT;
    		}
    		else if(x2>0)
    		{
    			return DIR_RIGHT;
    		}
    		else
    		{
    			return DIR_UP;
    		}
    	}
	}
		
	unsigned char PrimitiveActor::getActorType()
	{
		return actorType;
	}

	unsigned char PrimitiveActor::getDir2(float x1,float y1,float x2,float y2) //returns the direction of the second set of xy coords based on the first set
	{
    	double dir=correctDegrees(direction(x1,y1,x2,y2));
    	if((dir<=45)||(dir>=315))
    	{
        	return DIR_RIGHT;
    	}
    	else if((dir>=45)&&(dir<=135))
    	{
        	return DIR_UP;
    	}
    	else if((dir>=135)&&(dir<=225))
    	{
        	return DIR_LEFT;
    	}
    	else if((dir>=225)&&(dir<=315))
    	{
        	return DIR_DOWN;
    	}
    	Console::WriteLine("Error getDir2(float,float,float,float): invalid arguments for function. Returning 0");
    	return 0;
	}

	unsigned char PrimitiveActor::getDir(const RectangleF& r1, const RectangleF& r2) //returns the direction of the second set of xy coords based on the first set
	{                                                                //directions in this method are based on the corners of the bounding box
    	float rx2 = (float)((float)r2.x + (float)r2.width/2) - (float)((float)r1.x + (float)r1.width/2);
		float ry2 = (float)((float)r2.y + (float)r2.height/2) - (float)((float)r1.y + (float)r1.height/2);
		
		if(ry2<0) //r2 is above r1
		{
			if(rx2 == 0)
			{
				return DIR_UP;
			}
			else
			{
				float ratLeft = (float)(-((float)r1.height/2))/(float)(-((float)r1.width/2));
				float ratRight = (float)(-((float)r1.height/2))/(float)(((float)r1.width/2));
				
				float difRat =  ry2/rx2;
				
				if(difRat==ratRight)
				{
					return DIR_UPRIGHT;
				}
				else if(difRat==ratLeft)
				{
					return DIR_UPLEFT;
				}
				else if((difRat>ratRight)&&(difRat<0))
				{
					return DIR_RIGHT;
				}
				else if((difRat<ratLeft)&&(difRat>0))
				{
					return DIR_LEFT;
				}
				else
				{
					return DIR_UP;
				}
			}
		}
		else if(ry2>0)//r2 is below r1
		{
			if(rx2 == 0)
			{
				return DIR_DOWN;
			}
			else
			{
				float ratLeft = (float)(((float)r1.height/2))/(float)(-((float)r1.width/2));
				float ratRight = (float)(((float)r1.height/2))/(float)(((float)r1.width/2));
				
				float difRat =  ry2/rx2;
				
				if(difRat==ratRight)
				{
					return DIR_DOWNRIGHT;
				}
				else if(difRat==ratLeft)
				{
					return DIR_DOWNLEFT;
				}
				else if((difRat<ratRight)&&(difRat>0))
				{
					return DIR_RIGHT;
				}
				else if((difRat>ratLeft)&&(difRat<0))
				{
					return DIR_LEFT;
				}
				else
				{
					return DIR_DOWN;
				}
			}
		}
		else
		{
			if(rx2<0)
			{
				return DIR_LEFT;
			}
			else if(rx2>0)
			{
				return DIR_RIGHT;
			}
			else
			{
				return DIR_UP;
			}
		}
	}
		
	unsigned char PrimitiveActor::getDir(const Rectangle& r1, const Rectangle& r2) //returns the direction of the second set of xy coords based on the first set
	{                                                                //directions in this method are based on the corners of the bounding box
    	float rx2 = (float)((float)r2.x + (float)r2.width/2) - (float)((float)r1.x + (float)r1.width/2);
		float ry2 = (float)((float)r2.y + (float)r2.height/2) - (float)((float)r1.y + (float)r1.height/2);
		
		if(ry2<0) //r2 is above r1
		{
			if(rx2 == 0)
			{
				return DIR_UP;
			}
			else
			{
				float ratLeft = (float)(-((float)r1.height/2))/(float)(-((float)r1.width/2));
				float ratRight = (float)(-((float)r1.height/2))/(float)(((float)r1.width/2));
				
				float difRat =  ry2/rx2;
				
				if(difRat==ratRight)
				{
					return DIR_UPRIGHT;
				}
				else if(difRat==ratLeft)
				{
					return DIR_UPLEFT;
				}
				else if((difRat>ratRight)&&(difRat<0))
				{
					return DIR_RIGHT;
				}
				else if((difRat<ratLeft)&&(difRat>0))
				{
					return DIR_LEFT;
				}
				else
				{
					return DIR_UP;
				}
			}
		}
		else if(ry2>0)//r2 is below r1
		{
			if(rx2 == 0)
			{
				return DIR_DOWN;
			}
			else
			{
				float ratLeft = (float)(((float)r1.height/2))/(float)(-((float)r1.width/2));
				float ratRight = (float)(((float)r1.height/2))/(float)(((float)r1.width/2));
				
				float difRat =  ry2/rx2;
				
				if(difRat==ratRight)
				{
					return DIR_DOWNRIGHT;
				}
				else if(difRat==ratLeft)
				{
					return DIR_DOWNLEFT;
				}
				else if((difRat<ratRight)&&(difRat>0))
				{
					return DIR_RIGHT;
				}
				else if((difRat>ratLeft)&&(difRat<0))
				{
					return DIR_LEFT;
				}
				else
				{
					return DIR_DOWN;
				}
			}
		}
		else
		{
			if(rx2<0)
			{
				return DIR_LEFT;
			}
			else if(rx2>0)
			{
				return DIR_RIGHT;
			}
			else
			{
				return DIR_UP;
			}
		}
	}
	
	unsigned char PrimitiveActor::getDir(PrimitiveActor*a1, PrimitiveActor*a2) //returns the direction of the second set of xy coords based on the first set
	{                                                                //directions in this method are based on the corners of the bounding box
    	RectangleF r1;
    	RectangleF r2;

		if(a1==NULL || a2==NULL)
		{
			return 0;
		}

		PrimitiveActor&actor1 = *a1;
		PrimitiveActor&actor2 = *a2;

		switch(actor1.actorType)
    	{
    		default:
    		Console::WriteLine("Error getDir2(): function cannot be run on PrimitiveActor types, returning 0");
    		return 0;

    		case ACTORTYPE_ACTOR:
    		r1 = RectangleF(actor1.x - (float)actor1.width/2, actor1.y - (float)actor1.height/2, (float)actor1.width, (float)actor1.height);
    		break;

    		case ACTORTYPE_WIREFRAME:
    		r1 = RectangleF(actor1.x, actor1.y, (float)actor1.width, (float)actor1.height);
    		break;
    		
    		case ACTORTYPE_TEXT:
    		{
    			Rectangle rect = ((TextActor*)a1)->getRect();
    			r1 = RectangleF((float)rect.x, (float)rect.y, (float)rect.width, (float)rect.height);
    		}
    		break;
    	}
		
		switch(actor2.actorType)
    	{
    		default:
    		Console::WriteLine("Error getDir2(): function cannot be run on PrimitiveActor types, returning 0");
    		return 0;

    		case ACTORTYPE_ACTOR:
    		r2 = RectangleF(actor2.x - (float)actor2.width/2, actor2.y - (float)actor2.height/2, (float)actor2.width, (float)actor2.height);
    		break;

    		case ACTORTYPE_WIREFRAME:
    		r2 = RectangleF(actor2.x, actor2.y, (float)actor2.width, (float)actor2.height);
    		break;
    		
    		case ACTORTYPE_TEXT:
    		{
    			Rectangle rect = ((TextActor*)a2)->getRect();
    			r2 = RectangleF((float)rect.x, (float)rect.y, (float)rect.width, (float)rect.height);
    		}
    		break;
    	}
		
		return getDir(r1,r2);
	}
		
	double PrimitiveActor::distance(float x1,float y1,float x2,float y2) //returns distance between 2 sets of xy coordinates
	{
		float x3=x2;
		float y3=y1;
		float L1=std::abs(x3-x1);
		float L2=std::abs(y3-y2);
		return (double)(sqrt((L1*L1)+(L2*L2)));
	}
		
	double PrimitiveActor::distanceUnSqr(float x1,float y1,float x2,float y2) //does same thing as distance (see above) without square root.
	{                                                               //returns should be used relative to other returns of this method
		float x3=x2;
		float y3=y1;
		float L1=std::abs(x3-x1);
		float L2=std::abs(y3-y2);
		return (double)((L1*L1)+(L2*L2));
	}
		
	double PrimitiveActor::direction(double x1, double y1, double x2, double y2) //returns the direction (in degrees) of 1 set of xy coordinates to another
	{
		double angle = 0.0;
		if(x1 != x2 || y1 != y2)
		{
			if(y1 == y2)
			{
				if(x2 < x1)
				{
					angle = 180.0;
				}
				else
				{
					angle = 0.0;
				}
			}
			else if(x1 == x2)
			{
				if(y2 > y1)
				{
					angle = 270.0;
				}
				else
				{
					angle = 90.0;
				}
			}
			else
			{
				angle = radtodeg(atan2(y1 - y2, x2 - x1));
				if(angle < 0.0)
				{
					angle = 360.0 + angle;
				}
			}
		}
		return angle;
	}
    
	double PrimitiveActor::correctDegrees(double degrees)
	{
    	double newDegrees = degrees;
    	if(degrees<0)
    	{
    		do
    		{
    			newDegrees = 360 - std::abs(newDegrees);
    		}
    		while(newDegrees<0);
    	}
    	else if(degrees>360)
    	{
    		do
    		{
    			newDegrees = newDegrees - 360;
    		}
    		while(newDegrees>360);
    	}
    	return newDegrees;
	}
}