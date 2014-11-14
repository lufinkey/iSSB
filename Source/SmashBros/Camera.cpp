
#include "Camera.h"
#include <cmath>

namespace SmashBros
{
	float Camera::x = 0;
	float Camera::y = 0;
	float Camera::Zoom = 1;

	float Camera::prevCenterX = 0;
	float Camera::prevCenterY = 0;
	
	boolean Camera::firstUpdate = true;
	boolean Camera::firstFocus = true;
	
	const double Camera::zoomOutSpeed = 0.08;
	const double Camera::zoomInSpeed = 0.016;

	byte Camera::mode = MODE_ZOOM;
	
	//Camera::PrevP2PData Camera::prevP2PData = {true, 0,0,0,0,0};
	
	//View::x   View::y   x   y   Zoom
	//4         4         4   4   4    = 20
	/*void Camera::handleAddP2PData(DataVoid&data)
	{
		if(prevP2PData.firstTime)
		{
			Bitset bits = Bitset("11111000");
			byte active = bits.getByte();
			data.add(&active, sizeof(active));
			data.add(&View::x, sizeof(View::x));
			data.add(&View::y, sizeof(View::y));
			data.add(&x, sizeof(x));
			data.add(&y, sizeof(y));
			data.add(&Zoom, sizeof(Zoom));
			
			prevP2PData.firstTime = false;
			prevP2PData.View_x = View::x;
			prevP2PData.View_y = View::y;
			prevP2PData.x = x;
			prevP2PData.y = y;
			prevP2PData.Zoom = Zoom;
		}
		else
		{
			char*active = "00000000";
			
			if(prevP2PData.View_x!=View::x)
			{
				active[0] = '1';
			}
			if(prevP2PData.View_y!=View::y)
			{
				active[1] = '1';
			}
			if(prevP2PData.x!=x)
			{
				active[2] = '1';
			}
			if(prevP2PData.y!=y)
			{
				active[3] = '1';
			}
			if(prevP2PData.Zoom!=Zoom)
			{
				active[4] = '1';
			}
			
			String activeString = active;
			
			if(activeString.equals("00000000"))
			{
				return;
			}
			
			Bitset bits = Bitset(active);
			byte activeBytes = bits.getByte();
			data.add(&activeBytes, sizeof(activeBytes));
			
			if(active[0]=='1')
			{
				data.add(&View::x, sizeof(View::x));
			}
			if(active[1]=='1')
			{
				data.add(&View::y, sizeof(View::y));
			}
			if(active[2]=='1')
			{
				data.add(&x, sizeof(x));
			}
			if(active[3]=='1')
			{
				data.add(&y, sizeof(y));
			}
			if(active[4]=='1')
			{
				data.add(&Zoom, sizeof(Zoom));
			}
			prevP2PData.View_x = View::x;
			prevP2PData.View_y = View::y;
			prevP2PData.x = x;
			prevP2PData.y = y;
			prevP2PData.Zoom = Zoom;
		}
	}
	
	void Camera::handleSetP2PData(byte*&data)
	{
		byte active = data[0];
		data += sizeof(byte);
		Bitset bits = Bitset(active);
		
		if(bits.get(0))
		{
			//View::x
			View::x = DataVoid::toFloat(data);
			data += sizeof(float);
		}
		if(bits.get(1))
		{
			//View::y
			View::y = DataVoid::toFloat(data);
			data += sizeof(float);
		}
		if(bits.get(2))
		{
			//x
			x = DataVoid::toFloat(data);
			data += sizeof(float);
		}
		if(bits.get(3))
		{
			//y
			y = DataVoid::toFloat(data);
			data += sizeof(float);
		}
		if(bits.get(4))
		{
			//Zoom
			Zoom = DataVoid::toFloat(data);
			data += sizeof(float);
		}
	}*/
	
	void Camera::reset()
	{
		firstUpdate = true;
		firstFocus = true;
		Zoom = 1;
		x = 0;
		y = 0;
		mode = MODE_ZOOM;
	}

	void Camera::Update()
	{
		RectangleF rect = getFocusRect();
		float camX;
		float camY;
		
		RectF borders = Global::currentStage->getViewBorders();
		
		switch(mode)
		{
			default:
			case MODE_FIXED:
			{
				View::x = (float)(x + (float)Global::currentStage->x - (float)View::getScalingWidth()/2);
				View::y = (float)(y + (float)Global::currentStage->y - (float)View::getScalingHeight()/2);
				float zoomH = (float)View::getScalingHeight()/(float)(Global::currentStage->bottomViewBorder - Global::currentStage->topViewBorder);
				float zoomW = (float)View::getScalingWidth()/(float)(Global::currentStage->rightViewBorder - Global::currentStage->leftViewBorder);
				if(zoomH>zoomW)
				{
					Zoom = zoomH;
				}
				else
				{
					Zoom = zoomW;
				}
				float centerX = (float)(x + Global::currentStage->x);
				float centerY = (float)(y + Global::currentStage->y);
				
				float left = (float)(centerX - ((float)View::getScalingWidth()/((float)2*Zoom)));
				float right = (float)(centerX +((float)View::getScalingWidth()/((float)2*Zoom)));
				float top = (float)(centerY - ((float)View::getScalingHeight()/((float)2*Zoom)));
				float bottom = (float)(centerY +((float)View::getScalingHeight()/((float)2*Zoom)));
				
				if(left<(Global::currentStage->x + Global::currentStage->leftViewBorder))
				{
					centerX = (float)((Global::currentStage->x + Global::currentStage->leftViewBorder) + View::getScalingWidth()/(Zoom*2));
				}
				else if(right>(Global::currentStage->x + Global::currentStage->rightViewBorder))
				{
					centerX = (float)((Global::currentStage->x + Global::currentStage->rightViewBorder) - View::getScalingWidth()/(Zoom*2));
				}
				if(top<(Global::currentStage->y + Global::currentStage->topViewBorder))
				{
					centerY = (float)((Global::currentStage->y + Global::currentStage->topViewBorder) + View::getScalingHeight()/(Zoom*2));
				}
				else if(bottom>(Global::currentStage->y + Global::currentStage->bottomViewBorder))
				{
					centerY = (float)((Global::currentStage->y + Global::currentStage->bottomViewBorder) - View::getScalingHeight()/(Zoom*2));
				}
				camX = (float)((centerX*Zoom) - ((float)View::getScalingWidth()/2));
				camY = (float)((centerY*Zoom) - ((float)View::getScalingHeight()/2));
				
				View::x = camX;
				View::y = camY;
			}
			break;
			
			case MODE_FOLLOW:
			{
				camX = (float)(((float)rect.x*Zoom) - (((float)View::getScalingWidth() - ((float)rect.width*Zoom))/2));
				camY = (float)(((float)rect.y*Zoom) - (((float)View::getScalingHeight() - ((float)rect.height*Zoom))/2));
				
				float leftSide = (float)((Global::currentStage->x + borders.left)*Zoom);
				float rightSide = (float)((Global::currentStage->x + borders.right)*Zoom);
				float topSide = (float)((Global::currentStage->y + borders.top)*Zoom);
				float bottomSide = (float)((Global::currentStage->y + borders.bottom)*Zoom);
				
				if(camX < leftSide)
				{
					camX = leftSide;
				}
				else if((camX + View::getScalingWidth()) > rightSide)
				{
					camX = (rightSide - View::getScalingWidth());
				}
				if(camY < topSide)
				{
					camY = topSide;
				}
				else if((camY + View::getScalingHeight()) > bottomSide)
				{
					camY = (bottomSide - View::getScalingHeight());
				}
				
				View::x = (float)((x*Zoom) + camX);
				View::y = (float)((y*Zoom) + camY);
			}
			break;
				
			case MODE_ZOOM:
			{
				float zoomW = (float)View::getScalingWidth()/(float)rect.width;
				float zoomH = (float)View::getScalingHeight()/(float)rect.height;
				float expzoom;
				
				if((rect.width*zoomH) > View::getScalingWidth())
				{
					expzoom = zoomW;
					//Zoom = zoomW;
				}
				else
				{
					expzoom = zoomH;
					//Zoom = zoomH;
				}
				
				float zoomx = (float)View::getScalingWidth()/(borders.right - borders.left);
				float zoomy = (float)View::getScalingHeight()/(borders.bottom - borders.top);
				float cmpzoom;
				
				float setZoom;
				
				if(zoomx > zoomy)
				{
					cmpzoom = zoomx;
				}
				else
				{
					cmpzoom = zoomy;
				}
				
				if(expzoom < cmpzoom)
				{
					setZoom = cmpzoom;
				}
				else
				{
					setZoom = expzoom;
				}
				
				//Zoom = setZoom;
				
				if(setZoom<Zoom)
				{
					if((Zoom - setZoom)> zoomOutSpeed)
					{
						Zoom -= (float)zoomOutSpeed;
					}
					else
					{
						Zoom = setZoom;
					}
				}
				else if(setZoom>Zoom)
				{
					if((setZoom - Zoom)> zoomInSpeed)
					{
						Zoom += (float)zoomInSpeed;
					}
					else
					{
						Zoom = setZoom;
					}
				}
				
				//g.setColor(Color::BLUE);
				//g.drawRect((int)(rect.x*Zoom), (int)(rect.y*Zoom), (int)(rect.width*Zoom), (int)(rect.height*Zoom));
				
				camX = (float)(((float)rect.x*Zoom) - (((float)View::getScalingWidth() - ((float)rect.width*Zoom))/2));
				camY = (float)(((float)rect.y*Zoom) - (((float)View::getScalingHeight() - ((float)rect.height*Zoom))/2));
				
				float leftSide = (float)((Global::currentStage->x + borders.left)*Zoom);
				float rightSide = (float)((Global::currentStage->x + borders.right)*Zoom);
				float topSide = (float)((Global::currentStage->y + borders.top)*Zoom);
				float bottomSide = (float)((Global::currentStage->y + borders.bottom)*Zoom);
				
				if(camX < leftSide)
				{
					camX = leftSide;
				}
				else if((camX + View::getScalingWidth()) > rightSide)
				{
					camX = (rightSide - View::getScalingWidth());
				}
				if(camY < topSide)
				{
					camY = topSide;
				}
				else if((camY + View::getScalingHeight()) > bottomSide)
				{
					camY = (bottomSide - View::getScalingHeight());
				}
				
				float centerX = (float)((camX + ((float)View::getScalingWidth()/2))/Zoom);
				float centerY = (float)((camY + ((float)View::getScalingHeight()/2))/Zoom);
				
				if(firstUpdate)
				{
					centerX = (float)Global::currentStage->x;
					centerY = (float)Global::currentStage->y;
					float zoom1 = (float)View::getScalingWidth()/(float)(borders.right - borders.left);
					float zoom2 = (float)View::getScalingHeight()/(float)(borders.bottom - borders.top);
					if(zoom1 > zoom2)
					{
						Zoom = zoom1;
					}
					else
					{
						Zoom = zoom2;
					}
				}
				else
				{
					if(!firstFocus)
					{
						if(centerX < prevCenterX)
						{
							if((prevCenterX - centerX) > moveSpeed)
							{
								centerX = prevCenterX - moveSpeed;
							}
						}
						else if(prevCenterX < centerX)
						{
							if((centerX - prevCenterX) > moveSpeed)
							{
								centerX = prevCenterX + moveSpeed;
							}
						}
						
						if(centerY < prevCenterY)
						{
							if((prevCenterY - centerY) > moveSpeed)
							{
								centerY = prevCenterY - moveSpeed;
							}
						}
						else if(prevCenterY < centerY)
						{
							if((centerY - prevCenterY) > moveSpeed)
							{
								centerY = prevCenterY + moveSpeed;
							}
						}
					}
					
					camX = (float)((centerX*Zoom) - ((float)View::getScalingWidth()/2));
					camY = (float)((centerY*Zoom) - ((float)View::getScalingHeight()/2));
					
					firstFocus = false;
				}
				
				prevCenterX = centerX;
				prevCenterY = centerY;
				
				View::x = (float)((x*Zoom) + camX);
				View::y = (float)((y*Zoom) + camY);
			}
			break;
		}
		firstUpdate = false;
	}

	void Camera::setMode(byte camera_mode)
	{
		mode = camera_mode;
	}

	RectangleF Camera::getFocusRect(ArrayList<int> players)
	{
		RectangleF rect;
		
		Vector2f ws;
		Vector2f hs;
		float w = 0;
		float h = 0;
		
		for(int i=1; i<=Global::possPlayers; i++)
		{
			for(int j=1; j<=Global::possPlayers; j++)
			{
				if(Global::characters[i]==null || !Global::characters[i]->isAlive())
				{
					j=(Global::possPlayers+1);
				}
				else if(Global::characters[j]==null || !Global::characters[j]->isAlive())
				{
					//
				}
				else if(players.size()==0 || (players.contains(Global::characters[i]->getPlayerNo()) && players.contains(Global::characters[i]->getPlayerNo())))
				{
					float w1 = std::abs(Global::characters[i]->x - Global::characters[j]->x) + (Global::characters[i]->width/2) + (Global::characters[j]->width/2) + 2*offset;
					float h1 = std::abs(Global::characters[i]->y - Global::characters[j]->y) + (Global::characters[i]->height/2) + (Global::characters[j]->height/2) + 2*offset;
					if(w1>w || w==0)
					{
						w = w1;
						if(Global::characters[i]->x < Global::characters[j]->x)
						{
							ws.x = Global::characters[i]->x;
							ws.y = (float)Global::characters[i]->width;
						}
						else
						{
							ws.x = Global::characters[j]->x;
							ws.y = (float)Global::characters[j]->width;
						}
					}
					if(h1>h || h==0)
					{
						h = h1;
						if(Global::characters[i]->y < Global::characters[j]->y)
						{
							hs.x = Global::characters[i]->y;
							hs.y = (float)Global::characters[i]->height;
						}
						else
						{
							hs.x = Global::characters[j]->y;
							hs.y = (float)Global::characters[j]->height;
						}
					}
				}
			}
		}
		
		rect.x = ws.x - ws.y/2 - offset;
		rect.y = hs.x - hs.y/2 - offset;
		rect.width = w;
		rect.height = h + bottomOffset;
		
		if(rect.width <=1 || rect.height<=1)
		{
			rect.width = 300;
			rect.height = 300;
			rect.x = Global::currentStage->x - rect.width/2;
			rect.y = Global::currentStage->y - rect.height/2;
		}
		
		return rect;
	}
	
	int Camera::Width()
	{
		return (int)((double)View::getScalingWidth()/Zoom);
	}

	int Camera::Height()
	{
		return (int)((double)View::getScalingHeight()/Zoom);
	}
}