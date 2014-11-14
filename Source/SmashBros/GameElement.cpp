
#include "GameElement.h"
#include "Camera.h"

namespace SmashBros
{
	GameElement::GameElement(float x1, float y1) : Actor(x1,y1)
	{
		prevAnim = "";
		prevFrame = 0;
	}
	
	GameElement::~GameElement()
	{
		//
	}
	
	void GameElement::Update(long gameTime)
	{
		Actor::Update(gameTime);
	}
	
	void GameElement::Draw(Graphics2D&g, long gameTime)
	{
		drawActor(g, gameTime,(float)(x*Camera::Zoom), (float)(y*Camera::Zoom), getScale()*Camera::Zoom);
	}

	bool GameElement::isOnScreen()
	{
		float left1, left2;
        float right1, right2;
        float top1, top2;
        float bottom1, bottom2;
        
        Animation*anim = getAnimation();
        
        float w = (float)anim->getWidth()*getScale()*Camera::Zoom;
        float h = (float)anim->getHeight()*getScale()*Camera::Zoom;
		
        left1 = ((x*Camera::Zoom)-(((float)w/2)*Camera::Zoom));
        left2 = View::x;
        right1 = ((x*Camera::Zoom)+(((float)w/2)*Camera::Zoom));
        right2 = (View::x+(View::getScalingWidth()));
        top1 = ((y*Camera::Zoom)-(((float)h/2)*Camera::Zoom));
        top2 = View::y;
        bottom1 = ((y*Camera::Zoom)+(((float)h/2)*Camera::Zoom));
        bottom2 = (View::y+(View::getScalingHeight()));
		
        if (bottom1 < top2)
        {
        	return false;
        }
        if (top1 > bottom2)
        {
        	return false;
        }
        
        if (right1 < left2)
        {
        	return false;
        }
        if (left1 > right2)
        {
        	return false;
        }

        return true;
	}

	byte GameElement::isColliding2(GameElement*collide)
	{
		if(getScale()==0 || collide->getScale()==0)
		{
			return 0;
		}
		RectF overlap = getOverlapArea(collide);
		if(overlap.left != -1)
		{
			RectF overlap2 = collide->getOverlapArea(this);
			
			int w = (int)(overlap.right - overlap.left);
			int h = (int)(overlap.bottom - overlap.top);
			
			float x1 = ((float)overlap.left/getScale());
			float y1 = ((float)overlap.top/getScale());
			float x2 = ((float)overlap2.left/collide->getScale());
			float y2 = ((float)overlap2.top/collide->getScale());
			
			float incr1 = (float)(1/getScale());
			float incr2 = (float)(1/collide->getScale());
			
			boolean colliding = false;
			
			boolean g1 = false;
			boolean g2 = false;
			
			int left1 = 0;
			int right1 = 0;
			int top1 = 0;
			int bottom1 = 0;
			
			int left2 = 0;
			int right2 = 0;
			int top2 = 0;
			int bottom2 = 0;

			PixelIterator pxlIter(this);
			pxlIter.reset(x1,y1,incr1,incr1,(int)w,(int)h);
			PixelIterator colPxlIter(collide);
			colPxlIter.reset(x2,y2,incr2,incr2,(int)w,(int)h);

			for(int cntY = 0; cntY<h; cntY++)
			{
				for(int cntX = 0; cntX<w; cntX++)
				{
					boolean grid1 = false;
					boolean grid2 = false;
					
					grid1 = pxlIter.checkNextPixel();
					grid2 = colPxlIter.checkNextPixel();
					
					if(grid1)
					{
						if(!g1)
						{
							left1 = cntX;
							right1 = cntX;
							top1 = cntY;
							bottom1 = cntY;
						}
						else
						{
							if(cntX < left1)
							{
								left1 = cntX;
							}
							else if(cntX > right1)
							{
								right1 = cntX;
							}
							if(cntY < top1)
							{
								top1 = cntY;
							}
							else if(cntY > bottom1)
							{
								bottom1 = cntY;
							}
						}
						g1 = true;
					}
					
					if(grid2)
					{
						if(!g2)
						{
							left2 = cntX;
							right2 = cntX;
							top2 = cntY;
							bottom2 = cntY;
						}
						else
						{
							if(cntX < left2)
							{
								left2 = cntX;
							}
							else if(cntX > right1)
							{
								right2 = cntX;
							}
							if(cntY < top2)
							{
								top2 = cntY;
							}
							else if(cntY > bottom2)
							{
								bottom2 = cntY;
							}
						}
						g2 = true;
					}
					
					if(grid1 && grid2)
					{
						colliding = true;
					}
				}
			}
			
			if(colliding)
			{
				GameEngine::Rectangle r1 = GameEngine::Rectangle(left1,top1, right1-left1, bottom1-top1);
				GameEngine::Rectangle r2 = GameEngine::Rectangle(left2,top2, right2-left2, bottom2-top2);
				
				byte dir = getDir(r1,r2);
				
				if(dir==DIR_UPLEFT)
				{
					dir = DIR_UP;
				}
				else if(dir==DIR_UPRIGHT)
				{
					dir = DIR_UP;
				}
				else if(dir==DIR_DOWNLEFT)
				{
					dir = DIR_DOWN;
				}
				else if(dir==DIR_DOWNRIGHT)
				{
					dir = DIR_DOWN;
				}
				
				return dir;
			}
		}
		return 0;
	}

	boolean GameElement::rectsColliding(Rectangle r1, Rectangle r2)
	{
		float left1, left2;
        float right1, right2;
        float top1, top2;
        float bottom1, bottom2;

        left1 = (float)r1.x;
        left2 = (float)r2.x;
        right1 = (float)r1.x + r1.width;
        right2 = (float)r2.x + r2.width;
        top1 = (float)r1.y;
        top2 = (float)r2.y;
        bottom1 = (float)r1.y+ r1.height;
        bottom2 = (float)r2.y + r2.height;

        if (bottom1 < top2)
        {
        	return false;
        }
        if (top1 > bottom2)
        {
        	return false;
        }

        if (right1 < left2)
        {
        	return false;
        }
        if (left1 > right2)
        {
        	return false;
        }

        return true;
	}

	boolean GameElement::rectsColliding(RectangleF r1, RectangleF r2)
	{
		float left1, left2;
        float right1, right2;
        float top1, top2;
        float bottom1, bottom2;

        left1 = (float)r1.x;
        left2 = (float)r2.x;
        right1 = (float)r1.x + r1.width;
        right2 = (float)r2.x + r2.width;
        top1 = (float)r1.y;
        top2 = (float)r2.y;
        bottom1 = (float)r1.y+ r1.height;
        bottom2 = (float)r2.y + r2.height;

        if (bottom1 < top2)
        {
        	return false;
        }
        if (top1 > bottom2)
        {
        	return false;
        }

        if (right1 < left2)
        {
        	return false;
        }
        if (left1 > right2)
        {
        	return false;
        }

        return true;
	}

	RectangleF GameElement::getOverlapRect(RectangleF r1, RectangleF r2)
	{
		RectangleF overlap;
		
		if(rectsColliding(r1,r2))
		{
			if(r1.x <= r2.x)
			{
				if((r1.x + r1.width) <= (r2.x + r2.width))
				{
					overlap.x = r2.x - r1.x;
					overlap.width = r1.width;
				}
				else
				{
					overlap.x = r2.x - r1.x;
					overlap.width = overlap.x + r2.width;
				}
			}
			else
			{
				if((r1.x + r1.width) <= (r2.x + r2.width))
				{
					overlap.x = 0;
					overlap.width = r1.width;
				}
				else
				{
					overlap.x = 0;
					overlap.width = (r2.x + r2.width) - r1.x;
				}
			}
			
			if(r1.y <= r2.y)
			{
				if((r1.y + r1.height) <= (r2.y + r2.height))
				{
					overlap.y = r2.y - r1.y;
					overlap.height = r1.height;
				}
				else
				{
					overlap.y = r2.y - r1.y;
					overlap.height = overlap.y + r2.height;
				}
			}
			else
			{
				if((r1.y + r1.height)<= (r2.y + r2.height))
				{
					overlap.y = 0;
					overlap.height = r1.height;
				}
				else
				{
					overlap.y = 0;
					overlap.height = (r2.y + r2.height) - r1.y;
				}
			}
		}
		else
		{
			overlap.x = -1;
			overlap.y = -1;
			overlap.width = -1;
			overlap.height = -1;
		}
		return RectangleF(overlap.x,overlap.y, overlap.width - overlap.x, overlap.height - overlap.y);
	}

	Rectangle GameElement::getOverlapRect(Rectangle r1, Rectangle r2)
	{
		Rectangle overlap;
		
		if(rectsColliding(r1,r2))
		{
			if(r1.x <= r2.x)
			{
				if((r1.x + r1.width) <= (r2.x + r2.width))
				{
					overlap.x = r2.x - r1.x;
					overlap.width = r1.width;
				}
				else
				{
					overlap.x = r2.x - r1.x;
					overlap.width = overlap.x + r2.width;
				}
			}
			else
			{
				if((r1.x + r1.width) <= (r2.x + r2.width))
				{
					overlap.x = 0;
					overlap.width = r1.width;
				}
				else
				{
					overlap.x = 0;
					overlap.width = (r2.x + r2.width) - r1.x;
				}
			}
			
			if(r1.y <= r2.y)
			{
				if((r1.y + r1.height) <= (r2.y + r2.height))
				{
					overlap.y = r2.y - r1.y;
					overlap.height = r1.height;
				}
				else
				{
					overlap.y = r2.y - r1.y;
					overlap.height = overlap.y + r2.height;
				}
			}
			else
			{
				if((r1.y + r1.height)<= (r2.y + r2.height))
				{
					overlap.y = 0;
					overlap.height = r1.height;
				}
				else
				{
					overlap.y = 0;
					overlap.height = (r2.y + r2.height) - r1.y;
				}
			}
		}
		else
		{
			overlap.x = -1;
			overlap.y = -1;
			overlap.width = -1;
			overlap.height = -1;
		}
		return Rectangle(overlap.x,overlap.y, overlap.width - overlap.x, overlap.height - overlap.y);
	}
	
	byte GameElement::solidElementCollision(GameElement*collide)
	{
		if(getScale()==0 || collide->getScale()==0)
		{
			return 0;
		}
		
		GameEngine::Rectangle r1 = GameEngine::Rectangle((int)x - width/2, (int)y - height/2, width, height);
		GameEngine::Rectangle r2 = GameEngine::Rectangle((int)(collide->x - collide->width/2),(int)(collide->y - collide->height/2),collide->width,collide->height);
		GameEngine::Rectangle collideOverlap = getOverlapRect(r2,r1);
		GameEngine::Rectangle overlap = getOverlapRect(r1,r2);
		
		if(collideOverlap.x!=-1)
		{
			int startX = collideOverlap.x;
			int endX = collideOverlap.x + collideOverlap.width;
			int startY = collideOverlap.y;
			int endY = collideOverlap.y + collideOverlap.height;
			
			float x1 = ((float)startX/collide->getScale());
			float y1 = ((float)startY/collide->getScale());
			float incr = (float)(1/collide->getScale());
			
			int left=0;
			int right=0;
			int top=0;
			int bottom=0;
			boolean colliding = false;

			PixelIterator colPxlIter(collide);
			colPxlIter.reset(x1,y1,incr,incr,(int)collideOverlap.width,(int)collideOverlap.height);
			
			for(int cntY=startY; cntY<endY; cntY++)
			{
				for(int cntX=startX; cntX<endX; cntX++)
				{
					if(colPxlIter.checkNextPixel())
					{
						if(!colliding)
						{
							left = cntX;
							right = cntX;
							top = cntY;
							bottom = cntY;
						}
						else
						{
							if(cntX<left)
							{
								left = cntX;
							}
							else if(cntX>right)
							{
								right = cntX;
							}
							if(cntY<top)
							{
								top = cntY;
							}
							else if(cntY>bottom)
							{
								bottom = cntY;
							}
						}
						colliding = true;
					}
				}
			}
			
			if(colliding)
			{
				int w = right - left;
				int h = bottom - top;
				GameEngine::Rectangle collideOverlap2 = GameEngine::Rectangle(left, top, w, h);
				int overlapX = (left - startX) + overlap.x + (w/2);
				int overlapY = (top - startY) + overlap.y + (h/2);
				byte dir = getDir2((float)width/2,(float)height/2,(float)overlapX, (float)overlapY);
				switch(dir)
				{
					case DIR_DOWN:
					y = (collideOverlap2.y + (collide->y - collide->height/2)) - height/2;
					return DIR_UP;
					
					case DIR_UP:
					y = ((collide->y - collide->height/2) + (collideOverlap2.y + collideOverlap2.height)) + height/2;
					return DIR_DOWN;
					
					case DIR_LEFT:
					x = ((collide->x - collide->width/2) + (collideOverlap2.x + collideOverlap2.width) + width/2);
					return DIR_RIGHT;
					
					case DIR_RIGHT:
					x = (collideOverlap2.x + (collide->x - collide->width/2)) - width/2;
					return DIR_LEFT;
				}
			}
		}
		return 0;
	}
}