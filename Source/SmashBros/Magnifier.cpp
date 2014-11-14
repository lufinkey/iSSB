
#include "Magnifier.h"
#include "Global.h"
#include "Stage.h"
#include "Camera.h"

namespace SmashBros
{
	Actor*Magnifier::magnifier = NULL;
	
	void Magnifier::load()
	{
		if(magnifier==NULL)
		{
			magnifier = new Actor(0,0);
			magnifier->setScale(0.8f);
			magnifier->addAnimation(new Animation("normal", 1, "Images/Game/Misc/magnifier.png"));
			magnifier->changeAnimation("normal", FORWARD);
			magnifier->setRelativeToView(false);
		}
	}
	
	void Magnifier::Draw(Graphics2D&g, long gameTime, GameElement*element)
	{
		if(Global::currentStage!=NULL && element!=NULL)
		{
			float x = (element->x*Camera::Zoom - View::x);
			float y = (element->y*Camera::Zoom - View::y);
			float w = element->width*Camera::Zoom;
			float h = element->height*Camera::Zoom;
			
			byte dir = 0;
			
			if((y-(h/2)) <= 0)
			{
				if((x-(w/2)) <= 0)
				{
					dir = PrimitiveActor::DIR_UPLEFT;
				}
				else if((x+(w/2)) >= View::getScalingWidth())
				{
					dir = PrimitiveActor::DIR_UPRIGHT;
				}
				else
				{
					dir = PrimitiveActor::DIR_UP;
				}
			}
			else if((y+(h/2)) >= View::getScalingHeight())
			{
				if((x-(w/2)) <= 0)
				{
					dir = PrimitiveActor::DIR_DOWNLEFT;
				}
				else if((x+(w/2)) >= View::getScalingWidth())
				{
					dir = PrimitiveActor::DIR_DOWNRIGHT;
				}
				else
				{
					dir = PrimitiveActor::DIR_DOWN;
				}
			}
			else if((x-(w/2)) <= 0)
			{
				dir = PrimitiveActor::DIR_LEFT;
			}
			else if((x+(w/2)) >= View::getScalingWidth())
			{
				dir = PrimitiveActor::DIR_RIGHT;
			}

			if(dir>0)
			{
				Animation*anim = element->getAnimation();
				float width = (float)anim->getWidth();
				float height = (float)anim->getHeight();
				float scale = 1;
				if(width>height)
				{
					float newWidth = 120*magnifier->getScale();
					scale = newWidth/width;

					width = newWidth;
					height = height*scale;
				}
				else
				{
					float newHeight = 120*magnifier->getScale();
					scale = newHeight/height;

					height = newHeight;
					width = width*scale;
				}
				
				switch(dir)
				{
					case PrimitiveActor::DIR_UP:
					{
						magnifier->x = x;
						magnifier->y = (float)(magnifier->height)/2;
						magnifier->setRotation(0);
					}
					break;
					
					case PrimitiveActor::DIR_UPLEFT:
					{
						magnifier->x = (float)(magnifier->width)/2;
						magnifier->y = (float)(magnifier->height)/2;
						magnifier->setRotation(-45);
					}
					break;
					
					case PrimitiveActor::DIR_UPRIGHT:
					{
						magnifier->x = (float)View::getScalingWidth() - (float)(magnifier->width)/2;
						magnifier->y = (float)(magnifier->height)/2;
						magnifier->setRotation(45);
					}
					break;
					
					case PrimitiveActor::DIR_LEFT:
					{
						magnifier->x = (float)(magnifier->width)/2;
						magnifier->y = y;
						magnifier->setRotation(-90);
					}
					break;
					
					case PrimitiveActor::DIR_RIGHT:
					{
						magnifier->x = View::getScalingWidth() - (float)(magnifier->width)/2;
						magnifier->y = y;
						magnifier->setRotation(90);
					}
					break;
					
					case PrimitiveActor::DIR_DOWNLEFT:
					{
						magnifier->x = (float)(magnifier->width)/2;
						magnifier->y = View::getScalingHeight() - (float)(magnifier->height)/2;
						magnifier->setRotation(-135);
					}
					break;
					
					case PrimitiveActor::DIR_DOWNRIGHT:
					{
						magnifier->x = View::getScalingWidth() - (float)(magnifier->width)/2;
						magnifier->y = View::getScalingHeight() - (float)(magnifier->height)/2;
						magnifier->setRotation(135);
					}
					break;
					
					case PrimitiveActor::DIR_DOWN:
					{
						magnifier->x = x;
						magnifier->y = View::getScalingHeight() - (float)(magnifier->height)/2;
						magnifier->setRotation(180);
					}
					break;
				}
				magnifier->Update(gameTime);
				magnifier->Draw(g, gameTime);
				
				float x1 = View::x + magnifier->x - (width/2);
				float y1 = View::y + magnifier->y - (height/2);
				float x2 = x1 + width;
				float y2 = y1 + height;
				
				//anim->drawFrame(NULL, g, anim->getCurrentFrame(), magnifier->x, magnifier->y, (double)scale, false);
				anim->drawFrame(NULL, g, anim->getCurrentFrame(), x1, y1, x2, y2);
			}
		}
	}
}