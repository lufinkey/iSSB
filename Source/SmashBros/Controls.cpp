
#include "Controls.h"
#include "Global.h"
#include "../Game.h"
#include "AttackTemplates.h"
#include "P2PDataManager.h"
#include "Preferences.h"


namespace SmashBros
{
	int**Controls::controls = null;
	bool Controls::ControllerButtonStates[20];
	bool Controls::PrevControllerButtonStates[20];
	Controls::ControlHUD*Controls::touchControls = null;
	bool Controls::touchEnabled = true;
	bool Controls::joystickEnabled = true;
	byte Controls::touchPlayer = 1;
	const float Controls::ControlHUD::farDist = 12100;
	const float Controls::ControlHUD::centerDist = 625;
	const long Controls::ControlHUD::runDelay = 100;
	SDL_Haptic* haptic = nullptr;
	
	typedef struct
	{
		long center;
		byte dir;
		bool far;
		bool down;
		bool pull;
	} JoystickData;
	
	typedef struct
	{
		bool lift;
		byte dir;
		bool far;
		byte button;
	} ControlData;
	
	Controls::ControlHUD::ControlHUD()
	{
		button_a = new Actor(820, 450);
		button_a->addAnimation(new Animation("normal", 1, "Images/Game/Controls/button_a.png"));
		button_a->changeAnimation("normal", FORWARD);
		button_a->setRelativeToView(false);
		button_a->setScale(2);
		button_a->setAlpha(0.2f);
		
		button_b = new Actor(707.5f, 525);
		button_b->addAnimation(new Animation("normal", 1, "Images/Game/Controls/button_b.png"));
		button_b->changeAnimation("normal", FORWARD);
		button_b->setRelativeToView(false);
		button_b->setScale(2);
		button_b->setAlpha(0.2f);
		
		button_x = new Actor(820, 337.5f);
		button_x->addAnimation(new Animation("normal", 1, "Images/Game/Controls/button_xy.png"));
		button_x->changeAnimation("normal", FORWARD);
		button_x->setRelativeToView(false);
		button_x->setScale(2);
		button_x->setAlpha(0.2f);
		
		button_z = new Actor(790, 60);
		button_z->addAnimation(new Animation("normal", 1, "Images/Game/Controls/button_z.png"));
		button_z->changeAnimation("normal", FORWARD);
		button_z->setRelativeToView(false);
		button_z->setScale(2);
		button_z->setAlpha(0.2f);
		
		arrow_up = new Actor(150, 375);
		arrow_up->addAnimation(new Animation("normal", 1, "Images/Game/Controls/arrow_up.png"));
		arrow_up->changeAnimation("normal", FORWARD);
		arrow_up->setRelativeToView(false);
		arrow_up->setScale(2);
		arrow_up->setAlpha(0.5f);
		
		arrow_down = new Actor(150, 525);
		arrow_down->addAnimation(new Animation("normal", 1, "Images/Game/Controls/arrow_down.png"));
		arrow_down->changeAnimation("normal", FORWARD);
		arrow_down->setRelativeToView(false);
		arrow_down->setScale(2);
		arrow_down->setAlpha(0.5f);
		
		arrow_left = new Actor(75, 450);
		arrow_left->addAnimation(new Animation("normal", 1, "Images/Game/Controls/arrow_left.png"));
		arrow_left->changeAnimation("normal", FORWARD);
		arrow_left->setRelativeToView(false);
		arrow_left->setScale(2);
		arrow_left->setAlpha(0.5f);
		
		arrow_right = new Actor(225, 450);
		arrow_right->addAnimation(new Animation("normal", 1, "Images/Game/Controls/arrow_right.png"));
		arrow_right->changeAnimation("normal", FORWARD);
		arrow_right->setRelativeToView(false);
		arrow_right->setScale(2);
		arrow_right->setAlpha(0.5f);
		
		joystickArea = new WireframeActor(0,0,View::getScalingWidth()/2, View::getScalingHeight());
		joystickArea->relativeToView(false);
		
		joystick = new Actor(150, 450);
		joystick->addAnimation(new Animation("center", 1, "Images/Game/Controls/joystick_center.png"));
		joystick->addAnimation(new Animation("up", 1, "Images/Game/Controls/joystick_up.png"));
		joystick->addAnimation(new Animation("up2", 1, "Images/Game/Controls/joystick_up2.png"));
		joystick->addAnimation(new Animation("down", 1, "Images/Game/Controls/joystick_down.png"));
		joystick->addAnimation(new Animation("down2", 1, "Images/Game/Controls/joystick_down2.png"));
		joystick->addAnimation(new Animation("left", 1, "Images/Game/Controls/joystick_left.png"));
		joystick->addAnimation(new Animation("left2", 1, "Images/Game/Controls/joystick_left2.png"));
		joystick->addAnimation(new Animation("right", 1, "Images/Game/Controls/joystick_right.png"));
		joystick->addAnimation(new Animation("right2", 1, "Images/Game/Controls/joystick_right2.png"));
		joystick->addAnimation(new Animation("up_left", 1, "Images/Game/Controls/joystick_up_left.png"));
		joystick->addAnimation(new Animation("up_left2", 1, "Images/Game/Controls/joystick_up_left2.png"));
		joystick->addAnimation(new Animation("up_right", 1, "Images/Game/Controls/joystick_up_right.png"));
		joystick->addAnimation(new Animation("up_right2", 1, "Images/Game/Controls/joystick_up_right2.png"));
		joystick->addAnimation(new Animation("down_left", 1, "Images/Game/Controls/joystick_down_left.png"));
		joystick->addAnimation(new Animation("down_left2", 1, "Images/Game/Controls/joystick_down_left2.png"));
		joystick->addAnimation(new Animation("down_right", 1, "Images/Game/Controls/joystick_down_right.png"));
		joystick->addAnimation(new Animation("down_right2", 1, "Images/Game/Controls/joystick_down_right2.png"));
		joystick->changeAnimation("center", FORWARD);
		joystick->setRelativeToView(false);
		joystick->setScale(2);
		joystick->setAlpha(0.5f);
		
		joystickDir = new byte[Global::possPlayers+1];
		joystickFar = new bool[Global::possPlayers+1];
		joystickDown = new bool[Global::possPlayers+1];
		justPulled = new bool[Global::possPlayers+1];
		lastCenterTime = new long[Global::possPlayers+1];
		for(int i=0; i<=Global::possPlayers; i++)
		{
			joystickDir[i] = 0;
			joystickFar[i] = false;
			joystickDown[i] = false;
			justPulled[i] = false;
			lastCenterTime[i] = 0;
		}
	}
	
	Controls::ControlHUD::~ControlHUD()
	{
		delete button_a;
		delete button_b;
		delete button_x;
		delete button_z;
		delete arrow_up;
		delete arrow_down;
		delete arrow_left;
		delete arrow_right;
		delete joystickArea;
		delete joystick;
		delete[] joystickDir;
		delete[] joystickFar;
		delete[] joystickDown;
		delete[] justPulled;
		delete[] lastCenterTime;
	}
	
	void Controls::ControlHUD::Update(long gameTime)
	{
		joystickArea->Update(gameTime);
		joystick->Update(gameTime);
		button_a->Update(gameTime);
		button_b->Update(gameTime);
		button_x->Update(gameTime);
		button_z->Update(gameTime);
		arrow_up->Update(gameTime);
		arrow_down->Update(gameTime);
		arrow_left->Update(gameTime);
		arrow_right->Update(gameTime);
		
		JoystickData joystickData;
		ArrayList<ControlData> buttonsPressed;
		bool storeButtons = false;
		
		bool CtrlButtonStates[20];
		
		for(int i=0; i<sizeof(ControllerButtonStates); i++)
		{
			CtrlButtonStates[i] = ControllerButtonStates[i];
		}
		
		if(P2PDataManager::isEnabled() && !P2PDataManager::isServer())
		{
			storeButtons = true;
			joystickData.dir = joystickDir[touchPlayer];
			joystickData.far = joystickFar[touchPlayer];
			joystickData.down = joystickDown[touchPlayer];
			joystickData.pull = justPulled[touchPlayer];
			joystickData.center = lastCenterTime[touchPlayer];
		}
		
		if(Controls::touchEnabled && !Global::hud->isClicked())
		{
			if((button_a->isClicked() && !button_a->wasClicked()) ||
			   (CtrlButtonStates[BUTTON_STANDARD] && !PrevControllerButtonStates[BUTTON_STANDARD]))
			{
				if(storeButtons)
				{
					ControlData ctrlData;
					ctrlData.lift = false;
					ctrlData.dir = 0;
					ctrlData.far = false;
					ctrlData.button = BUTTON_STANDARD;
					buttonsPressed.add(ctrlData);
				}
				else
				{
					buttonA(touchPlayer, DOWN);
				}
				button_a->setColor(Color::BLUE);
			}
			else if((!button_a->isClicked() && button_a->wasClicked()) ||
				(!CtrlButtonStates[BUTTON_STANDARD] && PrevControllerButtonStates[BUTTON_STANDARD]))
			{
				if(storeButtons)
				{
					ControlData ctrlData;
					ctrlData.lift = true;
					ctrlData.dir = 0;
					ctrlData.far = false;
					ctrlData.button = BUTTON_STANDARD;
					buttonsPressed.add(ctrlData);
				}
				else
				{
					buttonA(touchPlayer, UP);
				}
				button_a->setColor(Color::WHITE);
			}
			else if((button_b->isClicked() && !button_b->wasClicked()) ||
				(CtrlButtonStates[BUTTON_SPECIAL] && !PrevControllerButtonStates[BUTTON_SPECIAL]))
			{
				if(storeButtons)
				{
					ControlData ctrlData;
					ctrlData.lift = false;
					ctrlData.dir = 0;
					ctrlData.far = false;
					ctrlData.button = BUTTON_SPECIAL;
					buttonsPressed.add(ctrlData);
				}
				else
				{
					buttonB(touchPlayer, DOWN);
				}
				button_b->setColor(Color::GREEN);
			}
			else if((!button_b->isClicked() && button_b->wasClicked()) ||
				(!CtrlButtonStates[BUTTON_SPECIAL] && PrevControllerButtonStates[BUTTON_SPECIAL]))
			{
				if(storeButtons)
				{
					ControlData ctrlData;
					ctrlData.lift = true;
					ctrlData.dir = 0;
					ctrlData.far = false;
					ctrlData.button = BUTTON_SPECIAL;
					buttonsPressed.add(ctrlData);
				}
				else
				{
					buttonB(touchPlayer, UP);
				}
				button_b->setColor(Color::WHITE);
			}
			else if((button_x->isClicked() && !button_x->wasClicked()) ||
				(CtrlButtonStates[BUTTON_JUMP] && !PrevControllerButtonStates[BUTTON_JUMP]))
			{
				if(storeButtons)
				{
					ControlData ctrlData;
					ctrlData.lift = false;
					ctrlData.dir = 0;
					ctrlData.far = false;
					ctrlData.button = BUTTON_JUMP;
					buttonsPressed.add(ctrlData);
				}
				else
				{
					buttonX(touchPlayer, DOWN);
				}
				button_x->setColor(Color::YELLOW);
			}
			else if((!button_x->isClicked() && button_x->wasClicked()) ||
				(!CtrlButtonStates[BUTTON_JUMP] && PrevControllerButtonStates[BUTTON_JUMP]))
			{
				if(storeButtons)
				{
					ControlData ctrlData;
					ctrlData.lift = true;
					ctrlData.dir = 0;
					ctrlData.far = false;
					ctrlData.button = BUTTON_JUMP;
					buttonsPressed.add(ctrlData);
				}
				else
				{
					buttonX(touchPlayer, UP);
				}
				button_x->setColor(Color::WHITE);
			}
			else if((button_z->isClicked() && !button_z->wasClicked()) ||
				(CtrlButtonStates[BUTTON_GRAB] && !PrevControllerButtonStates[BUTTON_GRAB]))
			{
				if(storeButtons)
				{
					ControlData ctrlData;
					ctrlData.lift = false;
					ctrlData.dir = 0;
					ctrlData.far = false;
					ctrlData.button = BUTTON_GRAB;
					buttonsPressed.add(ctrlData);
				}
				else
				{
					Global::characters[touchPlayer]->discardItem();
				}
				button_z->setColor(Color::YELLOW);
			}
			else if((!button_z->isClicked() && button_z->wasClicked()) ||
				(!CtrlButtonStates[BUTTON_GRAB] && PrevControllerButtonStates[BUTTON_GRAB]))
			{
				button_z->setColor(Color::WHITE);
			}
			
			if(joystickEnabled)
			{
				if(joystickArea->isClicked())
				{
					long touchId = joystickArea->getTouchId();
					int mousex = Game::getTouchX(touchId);
					int mousey = Game::getTouchY(touchId);
					byte dir = PrimitiveActor::getDir(joystick->x, joystick->y, (float)mousex, (float)mousey);
					float dist = (float)PrimitiveActor::distanceUnSqr(joystick->x, joystick->y, (float)mousex, (float)mousey);
					if(dist<=centerDist)
					{
						if((lastCenterTime[touchPlayer]+runDelay)>=Game::getGameTime())
						{
							justPulled[touchPlayer] = true;
							if(storeButtons)
							{
								joystickData.pull = true;
							}
						}
						if(joystickDir[touchPlayer]!=0)
						{
							if(storeButtons)
							{
								ControlData ctrlData;
								ctrlData.lift = false;
								ctrlData.dir = 0;
								ctrlData.far = false;
								ctrlData.button = BUTTON_NONE;
								buttonsPressed.add(ctrlData);
								
								joystickDir[touchPlayer] = 0;
								joystickFar[touchPlayer] = false;
								joystickDown[touchPlayer] = true;
								
								joystick->changeAnimation("center", FORWARD);
							}
							else
							{
								js_center(touchPlayer);
							}
							lastCenterTime[touchPlayer] = Game::getGameTime();
						}
					}
					else if(dist<farDist)
					{
						if(joystickDir[touchPlayer]!=dir)
						{
							if((lastCenterTime[touchPlayer]+runDelay)>=Game::getGameTime())
							{
								justPulled[touchPlayer] = true;
								if(storeButtons)
								{
									joystickData.pull = true;
								}
							}
							if(joystickDir[touchPlayer]==0)
							{
								Player*playr = Global::getPlayerActor(touchPlayer);
								playr->smashTime = Game::getGameTime();
							}
							if(storeButtons)
							{
								ControlData ctrlData;
								ctrlData.lift = false;
								ctrlData.dir = dir;
								ctrlData.far = false;
								ctrlData.button = BUTTON_NONE;
								buttonsPressed.add(ctrlData);
								
								joystickDir[touchPlayer] = dir;
								joystickFar[touchPlayer] = false;
								joystickDown[touchPlayer] = true;
								
								switch(dir)
								{
									case PrimitiveActor::DIR_UP:
									joystick->changeAnimation("up", FORWARD);
									break;
									
									case PrimitiveActor::DIR_UPLEFT:
									joystick->changeAnimation("up_left", FORWARD);
									break;
																  
									case PrimitiveActor::DIR_UPRIGHT:
									joystick->changeAnimation("up_right", FORWARD);
									break;
									
									case PrimitiveActor::DIR_LEFT:
									joystick->changeAnimation("left", FORWARD);
									break;
									
									case PrimitiveActor::DIR_RIGHT:
									joystick->changeAnimation("right", FORWARD);
									break;
									
									case PrimitiveActor::DIR_DOWNLEFT:
									joystick->changeAnimation("down_left", FORWARD);
									break;
									
									case PrimitiveActor::DIR_DOWNRIGHT:
									joystick->changeAnimation("down_right", FORWARD);
									break;
									
									case PrimitiveActor::DIR_DOWN:
									joystick->changeAnimation("down", FORWARD);
									break;
								}
							}
							else
							{
								switch(dir)
								{
									case PrimitiveActor::DIR_UP:
									js_up(touchPlayer);
									break;
									
									case PrimitiveActor::DIR_UPLEFT:
									js_upleft(touchPlayer);
									break;
									
									case PrimitiveActor::DIR_UPRIGHT:
									js_upright(touchPlayer);
									break;
								
									case PrimitiveActor::DIR_LEFT:
									js_left(touchPlayer);
									break;
								
									case PrimitiveActor::DIR_RIGHT:
									js_right(touchPlayer);
									break;
									
									case PrimitiveActor::DIR_DOWNLEFT:
									js_downleft(touchPlayer);
									break;
									
									case PrimitiveActor::DIR_DOWNRIGHT:
									js_downright(touchPlayer);
									break;
									
									case PrimitiveActor::DIR_DOWN:
									js_down(touchPlayer);
									break;
								}
							}
						}
					}
					else
					{
						if(!(joystickDir[touchPlayer]==dir && joystickFar[touchPlayer]))
						{
							if((lastCenterTime[touchPlayer]+runDelay)>=Game::getGameTime())
							{
								justPulled[touchPlayer] = true;
								if(storeButtons)
								{
									joystickData.pull = true;
								}
							}
							if(joystickDir[touchPlayer]==0)
							{
								Player*playr = Global::getPlayerActor(touchPlayer);
								playr->smashTime = Game::getGameTime();
							}
							if(storeButtons)
							{
								ControlData ctrlData;
								ctrlData.lift = false;
								ctrlData.dir = dir;
								ctrlData.far = true;
								ctrlData.button = BUTTON_NONE;
								buttonsPressed.add(ctrlData);
								
								joystickDir[touchPlayer] = dir;
								joystickFar[touchPlayer] = true;
								joystickDown[touchPlayer] = true;
								
								switch(dir)
								{
									case PrimitiveActor::DIR_UP:
									joystick->changeAnimation("up2", FORWARD);
									break;
									
									case PrimitiveActor::DIR_UPLEFT:
									joystick->changeAnimation("up_left2", FORWARD);
									break;
									
									case PrimitiveActor::DIR_UPRIGHT:
									joystick->changeAnimation("up_right2", FORWARD);
									break;
									
									case PrimitiveActor::DIR_LEFT:
									joystick->changeAnimation("left2", FORWARD);
									break;
									
									case PrimitiveActor::DIR_RIGHT:
									joystick->changeAnimation("right2", FORWARD);
									break;
									
									case PrimitiveActor::DIR_DOWNLEFT:
									joystick->changeAnimation("down_left2", FORWARD);
									break;
									
									case PrimitiveActor::DIR_DOWNRIGHT:
									joystick->changeAnimation("down_right2", FORWARD);
									break;
									
									case PrimitiveActor::DIR_DOWN:
									joystick->changeAnimation("down2", FORWARD);
									break;
								}
							}
							else
							{
								switch(dir)
								{
									case PrimitiveActor::DIR_UP:
									js_up2(touchPlayer);
									break;
									
									case PrimitiveActor::DIR_UPLEFT:
									js_upleft2(touchPlayer);
									break;
									
									case PrimitiveActor::DIR_UPRIGHT:
									js_upright2(touchPlayer);
									break;
									
									case PrimitiveActor::DIR_LEFT:
									js_left2(touchPlayer);
									break;
									
									case PrimitiveActor::DIR_RIGHT:
									js_right2(touchPlayer);
									break;
									
									case PrimitiveActor::DIR_DOWNLEFT:
									js_downleft2(touchPlayer);
									break;
									
									case PrimitiveActor::DIR_DOWNRIGHT:
									js_downright2(touchPlayer);
									break;
									
									case PrimitiveActor::DIR_DOWN:
									js_down2(touchPlayer);
									break;
								}
							}
						}
					}
				}
				else
				{
					if(joystickDown[touchPlayer])
					{
						if(storeButtons)
						{
							ControlData ctrlData;
							ctrlData.lift = true;
							ctrlData.dir = 0;
							ctrlData.far = false;
							ctrlData.button = BUTTON_NONE;
							buttonsPressed.add(ctrlData);
							
							joystickDir[touchPlayer] = 0;
							joystickFar[touchPlayer] = false;
							joystickDown[touchPlayer] = false;
							
							joystick->changeAnimation("center", FORWARD);
						}
						else
						{
							js_release(touchPlayer);
						}
					}
					lastCenterTime[touchPlayer] = Game::getGameTime();
					joystickDir[touchPlayer] = 0;
				}
			}
			if(!joystickEnabled || iCade_enabled())
			{
				if((arrow_up->isClicked() && !arrow_up->wasClicked()) ||
				   (CtrlButtonStates[BUTTON_UP] && !PrevControllerButtonStates[BUTTON_UP]))
				{
					if(storeButtons)
					{
						ControlData ctrlData;
						ctrlData.lift = false;
						ctrlData.dir = 0;
						ctrlData.far = false;
						ctrlData.button = BUTTON_UP;
						buttonsPressed.add(ctrlData);
					}
					else
					{
						buttonUp(touchPlayer, DOWN);
					}
					arrow_up->setColor(Color::YELLOW);
				}
				else if((!arrow_up->isClicked() && arrow_up->wasClicked()) ||
					(!CtrlButtonStates[BUTTON_UP] && PrevControllerButtonStates[BUTTON_UP]))
				{
					if(storeButtons)
					{
						ControlData ctrlData;
						ctrlData.lift = true;
						ctrlData.dir = 0;
						ctrlData.far = false;
						ctrlData.button = BUTTON_UP;
						buttonsPressed.add(ctrlData);
					}
					else
					{
						buttonUp(touchPlayer, UP);
					}
					arrow_up->setColor(Color::WHITE);
				}
				if((arrow_down->isClicked() && !arrow_down->wasClicked()) ||
					(CtrlButtonStates[BUTTON_DOWN] && !PrevControllerButtonStates[BUTTON_DOWN]))
				{
					if(storeButtons)
					{
						ControlData ctrlData;
						ctrlData.lift = false;
						ctrlData.dir = 0;
						ctrlData.far = false;
						ctrlData.button = BUTTON_DOWN;
						buttonsPressed.add(ctrlData);
					}
					else
					{
						buttonDown(touchPlayer, DOWN);
					}
					arrow_down->setColor(Color::YELLOW);
				}
				else if((!arrow_down->isClicked() && arrow_down->wasClicked()) ||
					(!CtrlButtonStates[BUTTON_DOWN] && PrevControllerButtonStates[BUTTON_DOWN]))
				{
					if(storeButtons)
					{
						ControlData ctrlData;
						ctrlData.lift = true;
						ctrlData.dir = 0;
						ctrlData.far = false;
						ctrlData.button = BUTTON_DOWN;
						buttonsPressed.add(ctrlData);
					}
					else
					{
						buttonDown(touchPlayer, UP);
					}
					arrow_down->setColor(Color::WHITE);
				}
				if((arrow_left->isClicked() && !arrow_left->wasClicked()) ||
					(CtrlButtonStates[BUTTON_LEFT] && !PrevControllerButtonStates[BUTTON_LEFT]))
				{
					if(storeButtons)
					{
						ControlData ctrlData;
						ctrlData.lift = false;
						ctrlData.dir = 0;
						ctrlData.far = false;
						ctrlData.button = BUTTON_LEFT;
						buttonsPressed.add(ctrlData);
					}
					else
					{
						buttonLeft(touchPlayer, DOWN);
					}
					arrow_left->setColor(Color::YELLOW);
				}
				else if((!arrow_left->isClicked() && arrow_left->wasClicked()) ||
					(!CtrlButtonStates[BUTTON_LEFT] && PrevControllerButtonStates[BUTTON_LEFT]))
				{
					if(storeButtons)
					{
						ControlData ctrlData;
						ctrlData.lift = true;
						ctrlData.dir = 0;
						ctrlData.far = false;
						ctrlData.button = BUTTON_LEFT;
						buttonsPressed.add(ctrlData);
					}
					else
					{
						buttonLeft(touchPlayer, UP);
					}
					arrow_left->setColor(Color::WHITE);
				}
				if((arrow_right->isClicked() && !arrow_right->wasClicked()) ||
					(CtrlButtonStates[BUTTON_RIGHT] && !PrevControllerButtonStates[BUTTON_RIGHT]))
				{
					if(storeButtons)
					{
						ControlData ctrlData;
						ctrlData.lift = false;
						ctrlData.dir = 0;
						ctrlData.far = false;
						ctrlData.button = BUTTON_RIGHT;
						buttonsPressed.add(ctrlData);
					}
					else
					{
						buttonRight(touchPlayer, DOWN);
					}
					arrow_right->setColor(Color::YELLOW);
				}
				else if((!arrow_right->isClicked() && arrow_right->wasClicked()) ||
					(!CtrlButtonStates[BUTTON_RIGHT] && PrevControllerButtonStates[BUTTON_RIGHT]))
				{
					if(storeButtons)
					{
						ControlData ctrlData;
						ctrlData.lift = true;
						ctrlData.dir = 0;
						ctrlData.far = false;
						ctrlData.button = BUTTON_RIGHT;
						buttonsPressed.add(ctrlData);
					}
					else
					{
						buttonRight(touchPlayer, UP);
					}
					arrow_right->setColor(Color::WHITE);
				}
			}
		}
		justPulled[touchPlayer] = false;
		
		if(storeButtons)
		{
			DataVoid data;
			byte type = P2PDataManager::DATA_JOYSTICK;
			data.add(&type, sizeof(type));
			long gametime = Game::getGameTime();
			data.add(&gametime, sizeof(gametime));
			data.add(&joystickData.center, sizeof(joystickData.center));
			data.add(&joystickData.dir, sizeof(joystickData.dir));
			data.add(&joystickData.far, sizeof(joystickData.far));
			data.add(&joystickData.down, sizeof(joystickData.down));
			data.add(&joystickData.pull, sizeof(joystickData.pull));
			int size = buttonsPressed.size();
			data.add(&size, sizeof(size));
			for(int i=0; i<size; i++)
			{
				ControlData&ctrlData = buttonsPressed.get(i);
				data.add(&ctrlData.lift, sizeof(ctrlData.lift));
				data.add(&ctrlData.dir, sizeof(ctrlData.dir));
				data.add(&ctrlData.far, sizeof(ctrlData.far));
				data.add(&ctrlData.button, sizeof(ctrlData.button));
			}
			
			P2PManager::sendData(data.getData(), data.length(), P2PManager::SENDDATA_RELIABLE);
		}
		
		for(int i=0; i<sizeof(ControllerButtonStates); i++)
		{
			PrevControllerButtonStates[i] = CtrlButtonStates[i];
		}
	}
	
	void Controls::handleP2PData(byte*&data)
	{
		byte playrNo = 2;
		
		long gametime = DataVoid::toLong(data);
		data += sizeof(long);
		Game::setGameTime(gametime);
		
		touchControls->lastCenterTime[playrNo] = DataVoid::toLong(data);
		data += sizeof(long);
		
		touchControls->joystickDir[playrNo] = DataVoid::toBool(data);
		data += sizeof(bool);
		
		touchControls->joystickFar[playrNo] = DataVoid::toBool(data);
		data += sizeof(bool);
		
		touchControls->joystickDown[playrNo] = DataVoid::toBool(data);
		data += sizeof(bool);
		
		touchControls->justPulled[playrNo] = DataVoid::toBool(data);
		data += sizeof(bool);
		
		ArrayList<ControlData> buttonsPressed;
		
		int totalButtons = DataVoid::toInt(data);
		data += sizeof(int);
		for(int i=0; i<totalButtons; i++)
		{
			ControlData ctrlData;
			
			ctrlData.lift = DataVoid::toBool(data);
			data += sizeof(byte);
			
			ctrlData.dir = data[0];
			data += sizeof(byte);
			
			ctrlData.far = DataVoid::toBool(data);
			data += sizeof(byte);
			
			ctrlData.button = data[0];
			data += sizeof(byte);
			
			buttonsPressed.add(ctrlData);
		}
		
		for(int i=0; i<buttonsPressed.size(); i++)
		{
			ControlData&ctrlData = buttonsPressed.get(i);
			
			if(ctrlData.button<BUTTON_NONE)
			{
				byte type = 0;
				if(ctrlData.lift)
				{
					type = UP;
				}
				else
				{
					type = DOWN;
				}
				switch(ctrlData.button)
				{
					case BUTTON_UP:
					{
						buttonUp(playrNo, type);
					}
					break;
					
					case BUTTON_DOWN:
					{
						buttonDown(playrNo, type);
					}
					break;
					
					case BUTTON_LEFT:
					{
						buttonLeft(playrNo, type);
					}
					break;
					
					case BUTTON_RIGHT:
					{
						buttonRight(playrNo, type);
					}
					break;
					
					case BUTTON_JUMP:
					{
						buttonX(playrNo, type);
					}
					break;
					
					case BUTTON_STANDARD:
					{
						buttonA(playrNo, type);
					}
					break;
					
					case BUTTON_SPECIAL:
					{
						buttonB(playrNo, type);
					}
					break;
					
					case BUTTON_GRAB:
					{
						buttonZ(playrNo, type);
					}
					break;
				}
			}
			else
			{
				switch(ctrlData.dir)
				{
					case 0:
					{
						if(ctrlData.lift)
						{
							touchControls->js_release(playrNo);
						}
						else
						{
							touchControls->js_center(playrNo);
						}
						touchControls->lastCenterTime[playrNo] = Game::getGameTime();
					}
					break;
					
					case PrimitiveActor::DIR_UP:
					{
						if(ctrlData.far)
						{
							touchControls->js_up2(playrNo);
						}
						else
						{
							touchControls->js_up(playrNo);
						}
					}
					break;
					
					case PrimitiveActor::DIR_UPLEFT:
					{
						if(ctrlData.far)
						{
							touchControls->js_upleft2(playrNo);
						}
						else
						{
							touchControls->js_upleft(playrNo);
						}
					}
					break;
					
					case PrimitiveActor::DIR_UPRIGHT:
					{
						if(ctrlData.far)
						{
							touchControls->js_upright2(playrNo);
						}
						else
						{
							touchControls->js_upright(playrNo);
						}
					}
					break;
					
					case PrimitiveActor::DIR_LEFT:
					{
						if(ctrlData.far)
						{
							touchControls->js_left2(playrNo);
						}
						else
						{
							touchControls->js_left(playrNo);
						}
					}
					break;
					
					case PrimitiveActor::DIR_RIGHT:
					{
						if(ctrlData.far)
						{
							touchControls->js_right2(playrNo);
						}
						else
						{
							touchControls->js_right(playrNo);
						}
					}
					break;
					
					case PrimitiveActor::DIR_DOWNLEFT:
					{
						if(ctrlData.far)
						{
							touchControls->js_downleft2(playrNo);
						}
						else
						{
							touchControls->js_downleft(playrNo);
						}
					}
					break;
					
					case PrimitiveActor::DIR_DOWNRIGHT:
					{
						if(ctrlData.far)
						{
							touchControls->js_downright2(playrNo);
						}
						else
						{
							touchControls->js_downright(playrNo);
						}
					}
					break;
					
					case PrimitiveActor::DIR_DOWN:
					{
						if(ctrlData.far)
						{
							touchControls->js_down2(playrNo);
						}
						else
						{
							touchControls->js_down(playrNo);
						}
					}
					break;
				}
			}
		}
	}
	
	void Controls::ControlHUD::Draw(Graphics2D&g, long gameTime)
	{
		button_a->Draw(g, gameTime);
		button_b->Draw(g, gameTime);
		button_x->Draw(g, gameTime);
		button_z->Draw(g, gameTime);
		if(joystickEnabled)
		{
			joystickArea->Draw(g, gameTime);
			joystick->Draw(g, gameTime);
		}
		else
		{
			arrow_up->Draw(g, gameTime);
			arrow_down->Draw(g, gameTime);
			arrow_left->Draw(g, gameTime);
			arrow_right->Draw(g, gameTime);
		}
	}
	
	void Controls::ControlHUD::js_release(byte pNum)
	{
		if(pNum == Controls::touchPlayer)
		{
			joystick->changeAnimation("center", NO_CHANGE);
		}
		Player*playr=Global::getPlayerActor(pNum);
		playr->checkAttacks();
		playr->smashTime=0;
		playr->runTime=0;
		playr->buttondir=BUTTONDIR_CENTER;
		playr->down=false;
		playr->up=false;
		playr->upKey=false;
		playr->moveLeft=0;
		playr->moveRight=0;
		if(playr->chargeSmash > 0 && joystickDir[pNum]!=0)
		{
			int chargeSmash = playr->chargeSmash;
			playr->destroyCharge();
			switch(chargeSmash)
			{
				case AttackTemplates::SMASH_SIDE:
				playr->attackSideSmash(Player::STEP_GO);
				break;
					
				case AttackTemplates::SMASH_UP:
				playr->attackUpSmash(Player::STEP_GO);
				break;
					
				case AttackTemplates::SMASH_DOWN:
				playr->attackDownSmash(Player::STEP_GO);
				break;
			}
		}
		else if(playr->isOnGround() && playr->canDo && !playr->holdingPlayer)
		{
			playr->changeTwoSidedAnimation("stand", NO_CHANGE);
		}
		if(playr->chargingAttack)
		{
			long touchId = joystickArea->getTouchId();
			int mousex = Game::getTouchX(touchId);
			int mousey = Game::getTouchY(touchId);
			byte dir = PrimitiveActor::getDir2(joystick->x, joystick->y, (float)mousex, (float)mousey);
			switch(dir)
			{
				case PrimitiveActor::DIR_UP:
				playr->doChargingAttack(BUTTON_UP);
				break;
				
				case PrimitiveActor::DIR_DOWN:
				playr->doChargingAttack(BUTTON_DOWN);
				break;
					
				case PrimitiveActor::DIR_LEFT:
				playr->doChargingAttack(BUTTON_LEFT);
				break;
				
				case PrimitiveActor::DIR_RIGHT:
				playr->doChargingAttack(BUTTON_RIGHT);
				break;
			}
		}
		joystickDir[pNum] = 0;
		joystickFar[pNum] = false;
		joystickDown[pNum] = false;
	}
	
	void Controls::ControlHUD::js_center(byte pNum)
	{
		if(pNum == Controls::touchPlayer)
		{
			joystick->changeAnimation("center", NO_CHANGE);
		}
		Player*playr=Global::getPlayerActor(pNum);
		if(playr->attacksPriority!=-1)
		{
			playr->checkAttacks();
			playr->buttondir=BUTTONDIR_CENTER;
			playr->smashTime=0;
			playr->runTime=0;
			playr->down=false;
			playr->up=false;
			playr->upKey=false;
			playr->moveLeft=0;
			playr->moveRight=0;
			if(playr->canDo)
			{
				if(playr->isOnGround() && playr->canDo && !playr->holdingPlayer)
				{
					playr->changeTwoSidedAnimation("stand", NO_CHANGE);
				}
			}
		}
		joystickDir[pNum] = 0;
		joystickFar[pNum] = false;
		joystickDown[pNum] = true;
	}
	
	void Controls::ControlHUD::js_up(byte pNum)
	{
		if(joystickDir[pNum] != PrimitiveActor::DIR_UP) {
			Controls::buzzForJoystick();
		}
		if(pNum == Controls::touchPlayer)
		{
			joystick->changeAnimation("up", NO_CHANGE);
		}
		Player*playr=Global::getPlayerActor(pNum);
		if(playr->attacksPriority!=-1)
		{
			if(!joystickDown[pNum])
			{
				playr->smashTime = Global::worldTime+100;
			}
			else
			{
				playr->smashTime = 0;
			}
			playr->buttondir=BUTTONDIR_UP;
			playr->moveLeft=0;
			playr->moveRight=0;
			playr->down=false;
			playr->upKey=true;
			playr->checkAttacks();
			if(playr->canDo)
			{
				if(playr->hanging)
				{
					playr->hanging=false;
					playr->climbUp();
				}
				else if(playr->holdingPlayer)
				{
					//playr->grabAttackUp(); //TODO enable grabbing if needed here
				}
			}
		}
		joystickDir[pNum] = PrimitiveActor::DIR_UP;
		joystickFar[pNum] = false;
		joystickDown[pNum] = true;
	}
	
	void Controls::ControlHUD::js_up2(byte pNum)
	{
		if(joystickDir[pNum] != PrimitiveActor::DIR_UP) {
			Controls::buzzForJoystick();
		}
		if(pNum == Controls::touchPlayer)
		{
			joystick->changeAnimation("up2", NO_CHANGE);
		}
		Player*playr=Global::getPlayerActor(pNum);
		if(playr->attacksPriority!=-1)
		{
			if(!joystickDown[pNum] || justPulled[pNum])
			{
				playr->smashTime = Global::worldTime+100;
			}
			else
			{
				playr->smashTime = 0;
			}
			playr->buttondir=BUTTONDIR_UP;
			if((joystickDir[pNum] == PrimitiveActor::DIR_UPLEFT)||(joystickDir[pNum] == PrimitiveActor::DIR_UPRIGHT))
			{
				playr->moveLeft=0;
				playr->moveRight=0;
				playr->down=false;
				playr->upKey=true;
				playr->checkAttacks();
			}
			else
			{
				playr->moveLeft=0;
				playr->moveRight=0;
				playr->down=false;
				playr->upKey=true;
				playr->checkAttacks();
				if(justPulled[pNum] && playr->canDo)
				{
					if(playr->hanging)
					{
						playr->y-=playr->hitbox->height;
						playr->hanging=false;
						playr->destroyCharge();
						playr->jump();
					}
					else if(playr->holdingPlayer)
					{
						playr->grabAttackUp();
					}
					else
					{
						playr->destroyCharge();
						playr->jump();
					}
				}
			}
		}
		joystickDir[pNum] = PrimitiveActor::DIR_UP;
		joystickFar[pNum] = true;
		joystickDown[pNum] = true;
	}
	
	void Controls::ControlHUD::js_upleft(byte pNum)
	{
		if(joystickDir[pNum] != PrimitiveActor::DIR_UPLEFT) {
			Controls::buzzForJoystick();
		}
		if(pNum == Controls::touchPlayer)
		{
			joystick->changeAnimation("up_left", NO_CHANGE);
		}
		Player*playr=Global::getPlayerActor(pNum);
		if(playr->attacksPriority!=-1)
		{
			long touchId = joystickArea->getTouchId();
			int mousex = Game::getTouchX(touchId);
			int mousey = Game::getTouchY(touchId);
			byte dir = PrimitiveActor::getDir2(joystick->x, joystick->y, (float)mousex, (float)mousey);
			if(dir == PrimitiveActor::DIR_UP)
			{
				playr->buttondir=BUTTONDIR_UP;
			}
			else if(dir == PrimitiveActor::DIR_LEFT)
			{
				playr->buttondir=BUTTONDIR_LEFT;
			}
			playr->up=true;
			playr->upKey=false;
			playr->down=false;
			if(!((joystickDir[pNum]==PrimitiveActor::DIR_UPLEFT || joystickDir[pNum]==PrimitiveActor::DIR_LEFT) && joystickFar[pNum]))
			{
				if(playr->hanging)
				{
					if(playr->playerdir == Player::LEFT)
					{
						playr->hanging=false;
						playr->climbUp();
						playr->x-=4;
					}
				}
				else if(playr->holdingPlayer)
				{
					//playr->grabAttackUp(); //TODO enable grabbing if needed here
				}
			}
			else if(!playr->hanging)
			{
				playr->moveLeft = 1;
				playr->moveRight = 0;
			}

		}
		joystickDir[pNum] = PrimitiveActor::DIR_UPLEFT;
		joystickFar[pNum] = false;
		joystickDown[pNum] = true;
	}
	
	void Controls::ControlHUD::js_upleft2(byte pNum)
	{
		if(joystickDir[pNum] != PrimitiveActor::DIR_UPLEFT) {
			Controls::buzzForJoystick();
		}
		if(pNum == Controls::touchPlayer)
		{
			joystick->changeAnimation("up_left2", NO_CHANGE);
		}
		Player*playr=Global::getPlayerActor(pNum);
		if(playr->attacksPriority!=-1)
		{
			long touchId = joystickArea->getTouchId();
			int mousex = Game::getTouchX(touchId);
			int mousey = Game::getTouchY(touchId);
			byte dir = PrimitiveActor::getDir2(joystick->x, joystick->y, (float)mousex, (float)mousey);
			if(dir == PrimitiveActor::DIR_UP)
			{
				playr->buttondir=BUTTONDIR_UP;
			}
			else if(dir == PrimitiveActor::DIR_LEFT)
			{
				playr->buttondir=BUTTONDIR_LEFT;
			}
			if(joystickDir[pNum]==PrimitiveActor::DIR_UP && joystickFar[pNum])
			{
				playr->moveLeft=1;
				playr->moveRight=0;
				playr->down=false;
				playr->upKey=true;
				playr->checkAttacks();
			}
			else
			{
				playr->moveLeft=1;
				playr->moveRight=0;
				playr->down=false;
				playr->upKey=true;
				playr->checkAttacks();
				if(justPulled[pNum] && playr->canDo)
				{
					if(playr->hanging)
					{
						playr->climbUp();
						playr->hanging=false;
						playr->destroyCharge();
						playr->jump();
					}
					else if(playr->holdingPlayer)
					{
						playr->grabAttackUp();
					}
					else
					{
						playr->destroyCharge();
						playr->jump();
					}
				}
			}
		}
		joystickDir[pNum] = PrimitiveActor::DIR_UPLEFT;
		joystickFar[pNum] = true;
		joystickDown[pNum] = true;
	}
	
	void Controls::ControlHUD::js_upright(byte pNum)
	{
		if(joystickDir[pNum] != PrimitiveActor::DIR_UPRIGHT) {
			Controls::buzzForJoystick();
		}
		if(pNum == Controls::touchPlayer)
		{
			joystick->changeAnimation("up_right", NO_CHANGE);
		}
		Player*playr=Global::getPlayerActor(pNum);
		if(playr->attacksPriority!=-1)
		{
			long touchId = joystickArea->getTouchId();
			int mousex = Game::getTouchX(touchId);
			int mousey = Game::getTouchY(touchId);
			byte dir = PrimitiveActor::getDir2(joystick->x, joystick->y, (float)mousex, (float)mousey);
			if(dir == PrimitiveActor::DIR_UP)
			{
				playr->buttondir=BUTTONDIR_UP;
			}
			else if(dir == PrimitiveActor::DIR_RIGHT)
			{
				playr->buttondir=BUTTONDIR_RIGHT;
			}
			playr->up=true;
			playr->upKey=false;
			playr->down=false;
			if(!((joystickDir[pNum]==PrimitiveActor::DIR_UPRIGHT || joystickDir[pNum]==PrimitiveActor::DIR_RIGHT) && joystickFar[pNum]))
			{
				if(playr->hanging)
				{
					if(playr->playerdir == Player::RIGHT)
					{
						playr->hanging=false;
						playr->climbUp();
						playr->x+=4;
					}
				}
				else if(playr->holdingPlayer)
				{
					//playr->grabAttackUp(); //TODO enable grabbing if needed here
				}
			}
			else if(!playr->hanging)
			{
				playr->moveLeft = 0;
				playr->moveRight = 1;
			}
			
		}
		joystickDir[pNum] = PrimitiveActor::DIR_UPRIGHT;
		joystickFar[pNum] = false;
		joystickDown[pNum] = true;
	}
	
	void Controls::ControlHUD::js_upright2(byte pNum)
	{
		if(joystickDir[pNum] != PrimitiveActor::DIR_UPRIGHT) {
			Controls::buzzForJoystick();
		}
		if(pNum == Controls::touchPlayer)
		{
			joystick->changeAnimation("up_right2", NO_CHANGE);
		}
		Player*playr=Global::getPlayerActor(pNum);
		if(playr->attacksPriority!=-1)
		{
			long touchId = joystickArea->getTouchId();
			int mousex = Game::getTouchX(touchId);
			int mousey = Game::getTouchY(touchId);
			byte dir = PrimitiveActor::getDir2(joystick->x, joystick->y, (float)mousex, (float)mousey);
			if(dir == PrimitiveActor::DIR_UP)
			{
				playr->buttondir=BUTTONDIR_UP;
			}
			else if(dir == PrimitiveActor::DIR_RIGHT)
			{
				playr->buttondir=BUTTONDIR_RIGHT;
			}
			if(joystickDir[pNum] == PrimitiveActor::DIR_UP && joystickFar[pNum])
			{
				playr->moveLeft=0;
				playr->moveRight=1;
				playr->down=false;
				playr->upKey=true;
				playr->checkAttacks();
			}
			else
			{
				playr->moveLeft=0;
				playr->moveRight=1;
				playr->down=false;
				playr->upKey=true;
				playr->checkAttacks();
				if(justPulled[pNum] && playr->canDo)
				{
					if(playr->hanging)
					{
						playr->climbUp();
						playr->hanging=false;
						playr->destroyCharge();
						playr->jump();
					}
					else if(playr->holdingPlayer)
					{
						playr->grabAttackUp();
					}
					else
					{
						playr->destroyCharge();
						playr->jump();
					}
				}
			}
		}
		joystickDir[pNum] = PrimitiveActor::DIR_UPRIGHT;
		joystickFar[pNum] = true;
		joystickDown[pNum] = true;
	}
	
	void Controls::ControlHUD::js_left(byte pNum)
	{
		if(joystickDir[pNum] != PrimitiveActor::DIR_LEFT) {
			Controls::buzzForJoystick();
		}
		if(pNum == Controls::touchPlayer)
		{
			joystick->changeAnimation("left", NO_CHANGE);
		}
		Player*playr=Global::getPlayerActor(pNum);
		if(playr->attacksPriority!=-1)
		{
			playr->buttondir=BUTTONDIR_LEFT;
			playr->up=false;
			playr->upKey=false;
			playr->down=false;
			playr->moveRight=0;
			playr->moveLeft=1;
			if(justPulled[pNum] || joystickDir[pNum]==0)
			{
				playr->runTime = Global::worldTime+200;
			}
			if(!((joystickDir[pNum]==PrimitiveActor::DIR_LEFT || joystickDir[pNum]==PrimitiveActor::DIR_DOWNLEFT) && joystickFar[pNum])
			   && joystickDir[pNum]!=PrimitiveActor::DIR_UPLEFT)
			{
				if(playr->hanging)
				{
					playr->hanging=false;
					switch(playr->playerdir)
					{
						case Player::LEFT:
						playr->climbUp();
						playr->x-=4;
						break;
							
						case Player::RIGHT:
						playr->changeAnimation("fall_right", NO_CHANGE);
						playr->y+=6;
						break;
					}
				}
				else if(playr->holdingPlayer)
				{
					switch(playr->getPlayerDir())
					{
						case Player::LEFT:
						playr->grabAttackSide();
						break;
						
						case Player::RIGHT:
						playr->grabAttackSwing();
						break;
					}
				}
			}
		}
		joystickDir[pNum] = PrimitiveActor::DIR_LEFT;
		joystickFar[pNum] = false;
		joystickDown[pNum] = true;
	}
	
	void Controls::ControlHUD::js_left2(byte pNum)
	{
		if(joystickDir[pNum] != PrimitiveActor::DIR_LEFT) {
			Controls::buzzForJoystick();
		}
		if(pNum == Controls::touchPlayer)
		{
			joystick->changeAnimation("left2", NO_CHANGE);
		}
		Player*playr=Global::getPlayerActor(pNum);
		if(playr->attacksPriority!=-1)
		{
			playr->buttondir=BUTTONDIR_LEFT;
			playr->up=false;
			playr->upKey=false;
			playr->down=false;
			playr->moveRight=0;
			if(justPulled[pNum] || playr->runTime>Global::getWorldTime())
			{
				playr->moveLeft=2;
				playr->smashTime = Global::worldTime+100;
			}
			else
			{
				playr->moveLeft=1;
			}
			if(!(joystickDir[pNum]==PrimitiveActor::DIR_DOWNLEFT && joystickFar[pNum])
			   && joystickDir[pNum]!=PrimitiveActor::DIR_UPLEFT)
			{
				if(playr->hanging)
				{
					playr->hanging=false;
					switch(playr->playerdir)
					{
						case Player::LEFT:
						playr->climbUp();
						playr->x-=4;
						break;
							
						case Player::RIGHT:
						playr->changeAnimation("fall_right", NO_CHANGE);
						playr->y+=6;
						break;
					}
				}
				else if(playr->holdingPlayer)
				{
					switch(playr->getPlayerDir())
					{
						case Player::LEFT:
						playr->grabAttackSide();
						break;
						
						case Player::RIGHT:
						playr->grabAttackSwing();
						break;
					}
				}
			}
		}
		joystickDir[pNum] = PrimitiveActor::DIR_LEFT;
		joystickFar[pNum] = true;
		joystickDown[pNum] = true;
	}
	
	void Controls::ControlHUD::js_right(byte pNum)
	{
		if(joystickDir[pNum] != PrimitiveActor::DIR_RIGHT) {
			Controls::buzzForJoystick();
		}
		if(pNum == Controls::touchPlayer)
		{
			joystick->changeAnimation("right", NO_CHANGE);
		}
		Player*playr=Global::getPlayerActor(pNum);
		if(playr->attacksPriority!=-1)
		{
			playr->buttondir=BUTTONDIR_LEFT;
			playr->up=false;
			playr->upKey=false;
			playr->down=false;
			playr->moveLeft=0;
			playr->moveRight=1;
			if(justPulled[pNum] || joystickDir[pNum]==0)
			{
				playr->runTime = Global::worldTime+100;
			}
			if(!((joystickDir[pNum]==PrimitiveActor::DIR_RIGHT || joystickDir[pNum]==PrimitiveActor::DIR_DOWNRIGHT) && joystickFar[pNum])
			   && joystickDir[pNum]!=PrimitiveActor::DIR_UPRIGHT)
			{
				if(playr->hanging)
				{
					playr->hanging=false;
					switch(playr->playerdir)
					{
						case Player::LEFT:
						playr->changeAnimation("fall_left", NO_CHANGE);
						playr->y+=6;
						break;
							
						case Player::RIGHT:
						playr->climbUp();
						playr->x+=4;
						break;
					}
				}
				else if(playr->holdingPlayer)
				{
					switch(playr->getPlayerDir())
					{
						case Player::LEFT:
						playr->grabAttackSwing();
						break;
						
						case Player::RIGHT:
						playr->grabAttackSide();
						break;
					}
				}
			}
		}
		joystickDir[pNum] = PrimitiveActor::DIR_RIGHT;
		joystickFar[pNum] = false;
		joystickDown[pNum] = true;
	}
	
	void Controls::ControlHUD::js_right2(byte pNum)
	{
		if(joystickDir[pNum] != PrimitiveActor::DIR_RIGHT) {
			Controls::buzzForJoystick();
		}
		if(pNum == Controls::touchPlayer)
		{
			joystick->changeAnimation("right2", NO_CHANGE);
		}
		Player*playr=Global::getPlayerActor(pNum);
		if(playr->attacksPriority!=-1)
		{
			playr->buttondir=BUTTONDIR_LEFT;
			playr->up=false;
			playr->upKey=false;
			playr->down=false;
			playr->moveLeft=0;
			if(justPulled[pNum] || playr->runTime>Global::getWorldTime())
			{
				playr->moveRight=2;
				playr->smashTime = Global::worldTime+100;
			}
			else
			{
				playr->moveRight=1;
			}

			if(!(joystickDir[pNum]==PrimitiveActor::DIR_DOWNRIGHT && joystickFar[pNum])
			   && joystickDir[pNum]!=PrimitiveActor::DIR_UPRIGHT)
			{
				if(playr->hanging)
				{
					playr->hanging=false;
					switch(playr->playerdir)
					{
						case Player::LEFT:
						playr->changeAnimation("fall_left", NO_CHANGE);
						playr->y+=6;
						break;
							
						case Player::RIGHT:
						playr->climbUp();
						playr->x+=4;
						break;
					}
				}
				else if(playr->holdingPlayer)
				{
					switch(playr->getPlayerDir())
					{
						case Player::LEFT:
						playr->grabAttackSwing();
						break;
						
						case Player::RIGHT:
						playr->grabAttackSide();
						break;
					}
				}
			}
		}
		joystickDir[pNum] = PrimitiveActor::DIR_RIGHT;
		joystickFar[pNum] = true;
		joystickDown[pNum] = true;
	}
	
	void Controls::ControlHUD::js_down(byte pNum)
	{
		if(joystickDir[pNum] != PrimitiveActor::DIR_DOWN) {
			Controls::buzzForJoystick();
		}
		if(pNum == Controls::touchPlayer)
		{
			joystick->changeAnimation("down", NO_CHANGE);
		}
		Player*playr=Global::getPlayerActor(pNum);
		if(playr->attacksPriority!=-1)
		{
			playr->buttondir=BUTTONDIR_DOWN;
			playr->up=false;
			playr->upKey=false;
			playr->down = true;
			playr->checkAttacks();
			if(!joystickDown[pNum] || justPulled[pNum])
			{
				playr->smashTime = Global::worldTime+100;
			}
			else
			{
				playr->smashTime = 0;
			}
			if(playr->isOnGround() && playr->canDo && !playr->holdingPlayer)
			{
				playr->changeTwoSidedAnimation("crouch", NO_CHANGE);
			}
		}
		joystickDir[pNum] = PrimitiveActor::DIR_DOWN;
		joystickFar[pNum] = false;
		joystickDown[pNum] = true;
	}
	
	void Controls::ControlHUD::js_down2(byte pNum)
	{
		if(joystickDir[pNum] != PrimitiveActor::DIR_DOWN) {
			Controls::buzzForJoystick();
		}
		if(pNum == Controls::touchPlayer)
		{
			joystick->changeAnimation("down2", NO_CHANGE);
		}
		Player*playr=Global::getPlayerActor(pNum);
		if(playr->attacksPriority!=-1)
		{
			playr->buttondir=BUTTONDIR_DOWN;
			playr->checkAttacks();
			if(!joystickDown[pNum] || justPulled[pNum])
			{
				playr->smashTime = Global::worldTime+100;
			}
			else
			{
				playr->smashTime = 0;
			}
			if(justPulled[pNum] && playr->canDo)
			{
				playr->moveDown(); //< grabbing attack is implemented in here
			}
		}
		joystickDir[pNum] = PrimitiveActor::DIR_DOWN;
		joystickFar[pNum] = true;
		joystickDown[pNum] = true;
	}
	
	void Controls::ControlHUD::js_downleft(byte pNum)
	{
		if(joystickDir[pNum] != PrimitiveActor::DIR_DOWNLEFT) {
			Controls::buzzForJoystick();
		}
		if(pNum == Controls::touchPlayer)
		{
			joystick->changeAnimation("down_left", NO_CHANGE);
		}
		Player*playr=Global::getPlayerActor(pNum);
		if(playr->attacksPriority!=-1)
		{
			playr->buttondir=BUTTONDIR_LEFT;
			playr->up=false;
			playr->upKey=false;
			playr->down=false;
			if(playr->hanging && !(joystickDir[pNum]==PrimitiveActor::DIR_DOWNLEFT && joystickFar[pNum]))
			{
				if(playr->playerdir==Player::RIGHT)
				{
					playr->hanging=false;
					playr->changeAnimation("fall_right", NO_CHANGE);
					playr->y+=6;
				}
			}
			else
			{
				playr->moveRight=0;
				playr->moveLeft=1;
			}
		}
		joystickDir[pNum] = PrimitiveActor::DIR_DOWNLEFT;
		joystickFar[pNum] = false;
		joystickDown[pNum] = true;
	}
	
	void Controls::ControlHUD::js_downleft2(byte pNum)
	{
		if(joystickDir[pNum] != PrimitiveActor::DIR_DOWNLEFT) {
			Controls::buzzForJoystick();
		}
		if(pNum == Controls::touchPlayer)
		{
			joystick->changeAnimation("down_left2", NO_CHANGE);
		}
		Player*playr=Global::getPlayerActor(pNum);
		if(playr->attacksPriority!=-1)
		{
			playr->buttondir=BUTTONDIR_LEFT;
			if(joystickDir[pNum] == PrimitiveActor::DIR_DOWN && joystickFar[pNum])
			{
				playr->up=false;
				playr->upKey=false;
				playr->down=false;
				playr->moveRight=0;
				playr->moveLeft=1;
				if(playr->hanging)
				{
					playr->hanging=false;
					switch(playr->playerdir)
					{
						case 1:
						playr->changeAnimation("fall_right", NO_CHANGE);
						playr->y+=6;
						break;
							
						case 2:
						playr->x-=4;
						break;
					}
				}
			}
			else
			{
				playr->moveLeft = 0;
				playr->moveRight = 0;
				playr->checkAttacks();
				playr->moveDown();
			}
		}
		joystickDir[pNum] = PrimitiveActor::DIR_LEFT;
		joystickFar[pNum] = true;
		joystickDown[pNum] = true;
	}
	
	void Controls::ControlHUD::js_downright(byte pNum)
	{
		if(joystickDir[pNum] != PrimitiveActor::DIR_DOWNRIGHT) {
			Controls::buzzForJoystick();
		}
		if(pNum == Controls::touchPlayer)
		{
			joystick->changeAnimation("down_right", NO_CHANGE);
		}
		Player*playr=Global::getPlayerActor(pNum);
		if(playr->attacksPriority!=-1)
		{
			playr->buttondir=BUTTONDIR_RIGHT;
			playr->up=false;
			playr->upKey=false;
			playr->down=false;
			if(playr->hanging && !(joystickDir[pNum]==PrimitiveActor::DIR_DOWNRIGHT && joystickFar[pNum]))
			{
				if(playr->playerdir==Player::LEFT)
				{
					playr->hanging=false;
					playr->changeAnimation("fall_left", NO_CHANGE);
					playr->y-=6;
				}
			}
			else
			{
				playr->moveRight=1;
				playr->moveLeft=0;
			}
		}
		joystickDir[pNum] = PrimitiveActor::DIR_DOWNRIGHT;
		joystickFar[pNum] = false;
		joystickDown[pNum] = true;
	}
	
	void Controls::ControlHUD::js_downright2(byte pNum)
	{
		if(joystickDir[pNum] != PrimitiveActor::DIR_DOWNRIGHT) {
			Controls::buzzForJoystick();
		}
		if(pNum == Controls::touchPlayer)
		{
			joystick->changeAnimation("down_right2", NO_CHANGE);
		}
		Player*playr=Global::getPlayerActor(pNum);
		if(playr->attacksPriority!=-1)
		{
			playr->buttondir=BUTTONDIR_RIGHT;
			if(joystickDir[pNum]==PrimitiveActor::DIR_DOWN && joystickFar[pNum])
			{
				playr->up=false;
				playr->upKey=false;
				playr->down=false;
				playr->moveLeft=0;
				playr->moveRight=1;
				if(playr->hanging)
				{
					playr->hanging=false;
					switch(playr->playerdir)
					{
						case Player::LEFT:
						playr->x+=4;
						break;
						
						case Player::RIGHT:
						playr->changeAnimation("fall_left", NO_CHANGE);
						playr->y+=6;
						break;
					}
				}
			}
			else
			{
				playr->moveLeft = 0;
				playr->moveRight = 0;
				playr->checkAttacks();
				playr->moveDown();
			}
		}
		joystickDir[pNum] = PrimitiveActor::DIR_DOWNRIGHT;
		joystickFar[pNum] = true;
		joystickDown[pNum] = true;
	}
	
	void Controls::enableTouchControls(bool toggle)
	{
		if(toggle && !touchEnabled)
		{
			touchEnabled = true;
		}
		else if(!toggle && touchEnabled)
		{
			touchEnabled = false;
			if(touchControls->button_a->isClicked())
			{
				buttonA(touchPlayer,UP);
			}
			if(touchControls->button_b->isClicked())
			{
				buttonB(touchPlayer,UP);
			}
			if(touchControls->button_x->isClicked())
			{
				buttonX(touchPlayer, UP);
			}
			
			if(joystickEnabled)
			{
				if(touchControls->joystickDown)
				{
					touchControls->js_release(touchPlayer);
				}
			}
			else
			{
				if(touchControls->arrow_up->isClicked())
				{
					buttonUp(touchPlayer, UP);
				}
				if(touchControls->arrow_down->isClicked())
				{
					buttonDown(touchPlayer, UP);
				}
				if(touchControls->arrow_left->isClicked())
				{
					buttonLeft(touchPlayer, UP);
				}
				if(touchControls->arrow_right->isClicked())
				{
					buttonRight(touchPlayer, UP);
				}
			}
		}
	}
	
	void Controls::setJoystickActive(bool toggle)
	{
		joystickEnabled = toggle;
	}
	
	bool Controls::isJoystickActive()
	{
		return joystickEnabled;
	}
	
	void Controls::loadControls()
	{
		touchControls = new ControlHUD();
		controls = new int*[Global::possPlayers+1];
		
		for(int i=0; i<=Global::possPlayers; i++)
		{
			controls[i] = new int[10];
			for(int j=0; j<10; j++)
			{
				controls[i][j] = 0;
			}
		}
		
		for(int i=0; i<sizeof(ControllerButtonStates); i++)
		{
			ControllerButtonStates[i]=false;
			PrevControllerButtonStates[i]=false;
		}
		
		setDefaultControls();
		
		iCade_enable(true, Game::getWindow());
		iCade_setStateChangedCallback(&Controls::iCadeStateChangedHandler);
		iCade_setButtonDownCallback(&Controls::iCadeButtonDownHandler);
		iCade_setButtonUpCallback(&Controls::iCadeButtonUpHandler);
	}
	
	void Controls::setDefaultControls()
	{
		controls[0][BUTTON_PAUSE]=Keys::ENTER;
		
		controls[1][BUTTON_UP]=Keys::UPARROW;
		controls[1][BUTTON_DOWN]=Keys::DOWNARROW;
		controls[1][BUTTON_LEFT]=Keys::LEFTARROW;
		controls[1][BUTTON_RIGHT]=Keys::RIGHTARROW;
		controls[1][BUTTON_JUMP]=Keys::P;
		controls[1][BUTTON_STANDARD]=Keys::I;
		controls[1][BUTTON_SPECIAL]=Keys::O;
		controls[1][BUTTON_GRAB]=Keys::U;
		
		controls[2][BUTTON_UP]=Keys::W;
		controls[2][BUTTON_DOWN]=Keys::S;
		controls[2][BUTTON_LEFT]=Keys::A;
		controls[2][BUTTON_RIGHT]=Keys::D;
		controls[2][BUTTON_JUMP]=Keys::SHIFT_LEFT;
		controls[2][BUTTON_STANDARD]=Keys::X;
		controls[2][BUTTON_SPECIAL]=Keys::C;
		controls[2][BUTTON_GRAB]=Keys::Z;
		
		controls[3][BUTTON_UP]=Keys::NUMPAD_8;
		controls[3][BUTTON_DOWN]=Keys::NUMPAD_5;
		controls[3][BUTTON_LEFT]=Keys::NUMPAD_4;
		controls[3][BUTTON_RIGHT]=Keys::NUMPAD_6;
		controls[3][BUTTON_JUMP]=Keys::NUMPAD_0;
		controls[3][BUTTON_STANDARD]=Keys::NUMPAD_2;
		controls[3][BUTTON_SPECIAL]=Keys::NUMPAD_3;
		controls[3][BUTTON_GRAB]=Keys::NUMPAD_1;
		
		controls[4][BUTTON_UP]=Keys::T;
		controls[4][BUTTON_DOWN]=Keys::G;
		controls[4][BUTTON_LEFT]=Keys::F;
		controls[4][BUTTON_RIGHT]=Keys::H;
		controls[4][BUTTON_JUMP]=Keys::M;
		controls[4][BUTTON_STANDARD]=Keys::B;
		controls[4][BUTTON_SPECIAL]=Keys::N;
		controls[4][BUTTON_GRAB]=Keys::V;
	}
	
	bool Controls::controlsDown()
	{
		if(joystickEnabled)
		{
			if(touchControls->joystickDown[touchPlayer])
			{
				return true;
			}
		}
		else
		{
			if(touchControls->arrow_up->isClicked())
			{
				return true;
			}
			else if(touchControls->arrow_down->isClicked())
			{
				return true;
			}
			else if(touchControls->arrow_left->isClicked())
			{
				return true;
			}
			else if(touchControls->arrow_right->isClicked())
			{
				return true;
			}
		}

		if(touchControls->button_a->isClicked())
		{
			return true;
		}
		else if(touchControls->button_b->isClicked())
		{
			return true;
		}
		else if(touchControls->button_x->isClicked())
		{
			return true;
		}

		return false;
	}
	
	void Controls::CheckKeysDown()
	{
		for(byte i=1; i<=Global::possPlayers; i++)
		{
			if(Global::characters[i]!=null && !Global::characters[i]->isCPU() && Global::characters[i]->isAlive())
			{
				if(Game::getKeyPressed(controls[i][BUTTON_UP]) && !Game::getPrevKeyPressed(controls[i][BUTTON_UP]))
				{
					buttonUp(i,DOWN);
				}

				if(Game::getKeyPressed(controls[i][BUTTON_DOWN]) && !Game::getPrevKeyPressed(controls[i][BUTTON_DOWN]))
				{
					buttonDown(i,DOWN);
				}
				
				if(Game::getKeyPressed(controls[i][BUTTON_LEFT]) && !Game::getPrevKeyPressed(controls[i][BUTTON_LEFT]))
				{
					buttonLeft(i,DOWN);
				}
				
				if(Game::getKeyPressed(controls[i][BUTTON_RIGHT]) && !Game::getPrevKeyPressed(controls[i][BUTTON_RIGHT]))
				{
					buttonRight(i,DOWN);
				}
				
				if(Game::getKeyPressed(controls[i][BUTTON_JUMP]) && !Game::getPrevKeyPressed(controls[i][BUTTON_JUMP]))
				{
					buttonX(i,DOWN);
				}
				
				if(Game::getKeyPressed(controls[i][BUTTON_STANDARD]) && !Game::getPrevKeyPressed(controls[i][BUTTON_STANDARD]))
				{
					buttonA(i,DOWN);
				}
				
				if(Game::getKeyPressed(controls[i][BUTTON_SPECIAL]) && !Game::getPrevKeyPressed(controls[i][BUTTON_SPECIAL]))
				{
					buttonB(i,DOWN);
				}
				
				if(Game::getKeyPressed(controls[i][BUTTON_GRAB]) && !Game::getPrevKeyPressed(controls[i][BUTTON_GRAB]))
				{
					buttonZ(i,DOWN);
				}
			}
		}
	}
	
	void Controls::CheckKeysUp()
	{
		for(byte i=1; i<=Global::possPlayers; i++)
		{
			if(Global::characters[i]!=null && !Global::characters[i]->isCPU() && Global::characters[i]->isAlive())
			{
				if(!Game::getKeyPressed(controls[i][BUTTON_UP]) && Game::getPrevKeyPressed(controls[i][BUTTON_UP]))
				{
					buttonUp(i,UP);
					if(Game::getKeyPressed(controls[i][BUTTON_LEFT]))
					{
						Global::characters[i]->buttondir=BUTTONDIR_LEFT;
					}
					else if(Game::getKeyPressed(controls[i][BUTTON_RIGHT]))
					{
						Global::characters[i]->buttondir=BUTTONDIR_RIGHT;
					}
					else if(Game::getKeyPressed(controls[i][BUTTON_DOWN]))
					{
						Global::characters[i]->buttondir=BUTTONDIR_DOWN;
					}
				}
			 
				if(!Game::getKeyPressed(controls[i][BUTTON_DOWN]) && Game::getPrevKeyPressed(controls[i][BUTTON_DOWN]))
				{
					buttonDown(i,UP);
					if(Game::getKeyPressed(controls[i][BUTTON_LEFT]))
					{
						Global::characters[i]->buttondir=BUTTONDIR_LEFT;
					}
					else if(Game::getKeyPressed(controls[i][BUTTON_RIGHT]))
					{
						Global::characters[i]->buttondir=BUTTONDIR_RIGHT;
					}
					else if(Game::getKeyPressed(controls[i][BUTTON_UP]))
					{
						Global::characters[i]->buttondir=BUTTONDIR_UP;
					}
				}

				if(!Game::getKeyPressed(controls[i][BUTTON_LEFT]) && Game::getPrevKeyPressed(controls[i][BUTTON_LEFT]))
				{
					buttonLeft(i,UP);
					if(Game::getKeyPressed(controls[i][BUTTON_RIGHT]))
					{
						Global::characters[i]->buttondir=BUTTONDIR_RIGHT;
					}
					else if(Game::getKeyPressed(controls[i][BUTTON_UP]))
					{
						Global::characters[i]->buttondir=BUTTONDIR_UP;
					}
					else if(Game::getKeyPressed(controls[i][BUTTON_DOWN]))
					{
						Global::characters[i]->buttondir=BUTTONDIR_DOWN;
					}
				}
			 
				if(!Game::getKeyPressed(controls[i][BUTTON_RIGHT]) && Game::getPrevKeyPressed(controls[i][BUTTON_RIGHT]))
				{
					buttonRight(i,UP);
					if(Game::getKeyPressed(controls[i][BUTTON_LEFT]))
					{
						Global::characters[i]->buttondir=BUTTONDIR_LEFT;
					}
					else if(Game::getKeyPressed(controls[i][BUTTON_UP]))
					{
						Global::characters[i]->buttondir=BUTTONDIR_UP;
					}
					else if(Game::getKeyPressed(controls[i][BUTTON_DOWN]))
					{
						Global::characters[i]->buttondir=BUTTONDIR_DOWN;
					}
				}
				
				if(!Game::getKeyPressed(controls[i][BUTTON_JUMP]) && Game::getPrevKeyPressed(controls[i][BUTTON_JUMP]))
				{
					buttonX(i,UP);
				}
			 
				if(!Game::getKeyPressed(controls[i][BUTTON_STANDARD]) && Game::getPrevKeyPressed(controls[i][BUTTON_STANDARD]))
				{
					buttonA(i,UP);
				}
			 
				if(!Game::getKeyPressed(controls[i][BUTTON_SPECIAL]) && Game::getPrevKeyPressed(controls[i][BUTTON_SPECIAL]))
				{
					buttonB(i,UP);
				}
			 
				if(!Game::getKeyPressed(controls[i][BUTTON_GRAB]) && Game::getPrevKeyPressed(controls[i][BUTTON_GRAB]))
				{
					buttonZ(i,UP);
				}
			}
		}
	}
	
	void Controls::Update(long gameTime)
	{
		CheckKeysDown();
		CheckKeysUp();
		touchControls->Update(gameTime);
	}
	
	void Controls::Draw(Graphics2D&g, long gameTime)
	{
		touchControls->Draw(g, gameTime);
	}
	
	void Controls::buzzForButton() {
		if(Preferences::hasHapticFeedback()) {
			HapticFeedback::buzz(10, 0.4);
		}
	}
	
	void Controls::buzzForJoystick() {
		if(Preferences::hasHapticFeedback()) {
			HapticFeedback::buzz(10, 0.4);
		}
	}
	
	void Controls::buttonUp(byte pNum, byte type)
	{
		Player*playr=Global::getPlayerActor(pNum);
		switch(type)
		{
			case DOWN:
			buzzForJoystick();
			playr->smashTime=Global::worldTime+100;
			playr->buttondir=BUTTONDIR_UP;
			playr->checkAttacks();
			playr->upKey=true;
			if(playr->hanging)
			{
				playr->hanging=false;
				playr->climbUp();
			}
			else if(playr->canDo)
			{
				if(playr->holdingPlayer)
				{
					playr->grabAttackUp();
				}
				else
				{
					playr->jump();
				}
				//ActorEndDownB();
			}
			break;
	 
			case UP:
			playr->smashTime=0;
			if(playr->buttondir==BUTTONDIR_UP)
			{
				playr->buttondir=BUTTONDIR_CENTER;
			}
			playr->up=false;
			playr->upKey=false;
			if(playr->chargeSmash>0)
			{
				int chargeSmash = playr->chargeSmash;
				playr->destroyCharge();
				switch(chargeSmash)
				{
					case AttackTemplates::SMASH_SIDE:
					playr->attackSideSmash(Player::STEP_GO);
					break;
					
					case AttackTemplates::SMASH_UP:
					playr->attackUpSmash(Player::STEP_GO);
					break;
					
					case AttackTemplates::SMASH_DOWN:
					playr->attackDownSmash(Player::STEP_GO);
					break;
				}
			}
			if(playr->chargingAttack)
			{
				playr->doChargingAttack(BUTTON_UP);
			}
			break;
		}
	}
	
	void Controls::buttonDown(byte pNum, byte type)
	{
		Player*playr=Global::getPlayerActor(pNum);
		switch(type)
		{
			case DOWN:
			buzzForJoystick();
			playr->buttondir=BUTTONDIR_DOWN;
			playr->checkAttacks();
			playr->smashTime=Global::worldTime+100;
			playr->moveDown(); //< grabbing attack is implemented in here
			break;
			
			case UP:
			playr->checkAttacks();
			playr->smashTime=0;
			if(playr->buttondir==BUTTONDIR_DOWN)
			{
				playr->buttondir=BUTTONDIR_CENTER;
			}
			playr->down=false;
			if(playr->chargeSmash>0)
			{
				int chargeSmash = playr->chargeSmash;
				playr->destroyCharge();
				switch(chargeSmash)
				{
					case AttackTemplates::SMASH_SIDE:
					playr->attackSideSmash(Player::STEP_GO);
					break;
	 
					case AttackTemplates::SMASH_UP:
					playr->attackUpSmash(Player::STEP_GO);
					break;
	 
					case AttackTemplates::SMASH_DOWN:
					playr->attackDownSmash(Player::STEP_GO);
					break;
				}
			}
			else if(playr->isOnGround() && playr->canDo && !playr->chargingAttack && !playr->holdingPlayer)
			{
				playr->changeTwoSidedAnimation("stand", NO_CHANGE);
			}
			if(playr->chargingAttack)
			{
				playr->doChargingAttack(BUTTON_DOWN);
			}
			break;
		}
	}
	
	void Controls::buttonLeft(byte pNum, byte type)
	{
		Player*playr = Global::getPlayerActor(pNum);
		switch(type)
		{
			case DOWN:
			buzzForJoystick();
			playr->buttondir=BUTTONDIR_LEFT;
			playr->smashTime=Global::worldTime+100;
			if((Global::worldTime<=playr->runTime && playr->isOnGround())||(playr->moveRight==2))
			{
				playr->moveLeft=2;
			}
			else
			{
				playr->moveLeft=1;
				if(playr->isOnGround())
				{
					playr->runTime=Global::worldTime+200;
				}
			}
			if(playr->hanging)
			{
				playr->hanging=false;
				switch(playr->playerdir)
				{
					case Player::LEFT:
					playr->climbUp();
					playr->x-=4;
					break;
					
					case Player::RIGHT:
					playr->changeAnimation("fall_right", NO_CHANGE);
					playr->y+=6;
					break;
				}
			}
			else if(playr->holdingPlayer)
			{
				switch(playr->getPlayerDir())
				{
					case Player::LEFT:
					playr->grabAttackSide();
					break;
					
					case Player::RIGHT:
					playr->grabAttackSwing();
					break;
				}
			}
			break;
	 
			case UP:
			playr->checkAttacks();
			playr->smashTime=0;
			if(playr->buttondir==BUTTONDIR_LEFT)
			{
				playr->buttondir=BUTTONDIR_CENTER;
			}
			if(playr->moveLeft==2 && playr->isOnGround())
			{
				playr->runTime=Global::worldTime+100;
			}
			playr->moveLeft=0;
			if(playr->chargeSmash>0)
			{
				int chargeSmash = playr->chargeSmash;
				playr->destroyCharge();
				switch(chargeSmash)
				{
					case AttackTemplates::SMASH_SIDE:
					playr->attackSideSmash(Player::STEP_GO);
					break;
					
					case AttackTemplates::SMASH_UP:
					playr->attackUpSmash(Player::STEP_GO);
					break;
					
					case AttackTemplates::SMASH_DOWN:
					playr->attackDownSmash(Player::STEP_GO);
					break;
				}
			}
			else if(playr->isOnGround() && playr->canDo && !playr->chargingAttack && !playr->holdingPlayer)
			{
				playr->changeTwoSidedAnimation("stand", NO_CHANGE);
			}
			if(playr->chargingAttack)
			{
				playr->doChargingAttack(BUTTON_LEFT);
			}
			break;
		}
	}
	
	void Controls::buttonRight(byte pNum, byte type)
	{
		Player*playr = Global::getPlayerActor(pNum);
		switch(type)
		{
			case DOWN:
			buzzForJoystick();
			playr->buttondir=BUTTONDIR_RIGHT;
			playr->smashTime=Global::worldTime+100;
			if((Global::worldTime<=playr->runTime && playr->isOnGround())||(playr->moveLeft==2))
			{
				playr->moveRight=2;
			}
			else
			{
				playr->moveRight=1;
				if(playr->isOnGround())
				{
					playr->runTime=Global::worldTime+200;
				}
			}
			if(playr->hanging)
			{
				playr->hanging=false;
				switch(playr->playerdir)
				{
					case Player::LEFT:
					playr->changeAnimation("fall_left", NO_CHANGE);
					playr->y+=6;
					break;
					
					case Player::RIGHT:
					playr->climbUp();
					playr->x+=4;
					break;
				}
			}
			else if(playr->holdingPlayer)
			{
				switch(playr->getPlayerDir())
				{
					case Player::LEFT:
					playr->grabAttackSwing();
					break;
					
					case Player::RIGHT:
					playr->grabAttackSide();
					break;
				}
			}
			break;
	 
			case UP:
			playr->checkAttacks();
			playr->smashTime=0;
			if(playr->buttondir==BUTTONDIR_RIGHT)
			{
				playr->buttondir=BUTTONDIR_CENTER;
			}
			if(playr->moveRight==2 && playr->isOnGround())
			{
				playr->runTime=Global::worldTime+100;
			}
			playr->moveRight=0;
			if(playr->chargeSmash>0)
			{
				int chargeSmash = playr->chargeSmash;
				playr->destroyCharge();
				switch(chargeSmash)
				{
					case AttackTemplates::SMASH_SIDE:
					playr->attackSideSmash(Player::STEP_GO);
					break;
	 
					case AttackTemplates::SMASH_UP:
					playr->attackUpSmash(Player::STEP_GO);
					break;
	 
					case AttackTemplates::SMASH_DOWN:
					playr->attackDownSmash(Player::STEP_GO);
					break;
				}
			}
			else if(playr->isOnGround() && playr->canDo && !playr->chargingAttack && !playr->holdingPlayer)
			{
				playr->changeTwoSidedAnimation("stand", NO_CHANGE);
			}
			if(playr->chargingAttack)
			{
				playr->doChargingAttack(BUTTON_RIGHT);
			}
			break;
		}
	}
	
	void Controls::buttonX(byte pNum, byte type)
	{
		Player*playr=Global::getPlayerActor(pNum);
		switch(type)
		{
			case DOWN:
			buzzForButton();
			playr->checkAttacks();
			playr->hanging=false;
			playr->upKey=true;
			if(playr->canDo && !playr->holdingPlayer)
			{
				playr->destroyCharge();
				playr->jump();
			}
			break;
 
			case UP:
			playr->upKey=false;
			break;
		}
	}
	
	void Controls::buttonA(byte pNum, byte type)
	{
		
		Player*playr = Global::getPlayerActor(pNum);
		switch(type)
		{
			case DOWN:
			buzzForButton();
			playr->checkAttacks();
			if(playr->canDo && !playr->chargingAttack && !playr->hanging)
			{
				//grab attacks
				if(playr->holdingPlayer)
				{
					switch(playr->buttondir)
					{
						case BUTTONDIR_CENTER:
						playr->grabAttack();
						break;
						
						case BUTTONDIR_UP:
						playr->grabAttackUp();
						break;
						
						case BUTTONDIR_RIGHT:
						playr->grabAttackSide();
						break;
						
						case BUTTONDIR_DOWN:
						playr->grabAttackDown();
						break;
						
						case BUTTONDIR_LEFT:
						playr->grabAttackSide();
						break;
					}
				}
				else //regular attacks
				{
					switch(playr->buttondir)
					{
						case BUTTONDIR_CENTER:
						playr->attackA();
						break;
						
						case BUTTONDIR_UP:
						if(Global::worldTime<=playr->smashTime)
						{
							playr->attackUpSmash(Player::STEP_CHARGE);
							if(playr->jumping)
							{
								playr->jumping=false;
								playr->yvelocity=0;
							}
						}
						else
						{
							playr->attackUpA();
						}
						break;

						case BUTTONDIR_RIGHT:
						if(Global::worldTime<=playr->smashTime)
						{
							playr->attackSideSmash(Player::STEP_CHARGE);
						}
						else
						{
							playr->attackSideA();
						}
						break;

						case BUTTONDIR_DOWN:
						if(Global::worldTime<=playr->smashTime)
						{
							playr->attackDownSmash(Player::STEP_CHARGE);
							playr->canDropThrough=false;
							playr->dropping=false;
							playr->dropTime=0;
						}
						else
						{
							playr->attackDownA();
						}
						break;

						case BUTTONDIR_LEFT:
						if(Global::worldTime<=playr->smashTime)
						{
							playr->attackSideSmash(Player::STEP_CHARGE);
						}
						else
						{
							playr->attackSideA();
						}
						break;
					}
				}
				playr->smashTime=0;
				playr->checkAttacks();
			}
			else if(!playr->canDo)
			{
				if(playr->hanging)
				{
					playr->climbUpAttack();
				}
				else if(!playr->chargingAttack)
				{
					switch(playr->buttondir)
					{
						case BUTTONDIR_CENTER:
						playr->onQueueAttack(Player::ATTACK_A);
						break;
						
						case BUTTONDIR_UP:
						playr->onQueueAttack(Player::ATTACK_UPA);
						break;
						
						case BUTTONDIR_RIGHT:
						playr->onQueueAttack(Player::ATTACK_SIDEA);
						break;
						
						case BUTTONDIR_DOWN:
						playr->onQueueAttack(Player::ATTACK_DOWNA);
						break;
						
						case BUTTONDIR_LEFT:
						playr->onQueueAttack(Player::ATTACK_SIDEA);
						break;
					}
				}
			}
			break;
	 
			case UP:
			{
				playr->checkAttacks();
				playr->smashTime=0;
				int chargeSmash = playr->chargeSmash;
				playr->destroyCharge();
				switch(chargeSmash)
				{
					case AttackTemplates::SMASH_SIDE:
					playr->attackSideSmash(Player::STEP_GO);
					break;
					
					case AttackTemplates::SMASH_UP:
					playr->attackUpSmash(Player::STEP_GO);
					break;
					
					case AttackTemplates::SMASH_DOWN:
					playr->attackDownSmash(Player::STEP_GO);
					break;
				}
			}
			break;
		}
	}
	
	void Controls::buttonB(byte pNum, byte type)
	{
		Player*playr=Global::getPlayerActor(pNum);
		switch(type)
		{
			case DOWN:
			buzzForButton();
			playr->checkAttacks();
			playr->smashTime=0;
			if(playr->canDo)
			{
				//grab attacks
				if(playr->holdingPlayer)
				{
					switch(playr->buttondir)
					{
						case BUTTONDIR_CENTER:
						playr->grabAttack();
						break;
						
						case BUTTONDIR_UP:
						playr->grabAttackUp();
						break;
						
						case BUTTONDIR_RIGHT:
						playr->grabAttackSide();
						break;
						
						case BUTTONDIR_DOWN:
						playr->grabAttackDown();
						break;
						
						case BUTTONDIR_LEFT:
						playr->grabAttackSide();
						break;
					}
				}
				else //special attacks
				{
					switch(playr->buttondir)
					{
						case BUTTONDIR_CENTER:
						playr->attackB();
						break;

						case BUTTONDIR_UP:
						playr->attackUpB();
						break;

						case BUTTONDIR_RIGHT:
						playr->attackSideB();
						break;

						case BUTTONDIR_DOWN:
						playr->attackDownB();
						break;

						case BUTTONDIR_LEFT:
						playr->attackSideB();
						break;
					}
				}
				playr->hanging=false;
				playr->checkAttacks();
			}
			else
			{
				switch(playr->buttondir)
				{
					case BUTTONDIR_CENTER:
					playr->onQueueAttack(Player::ATTACK_B);
					break;
					
					case BUTTONDIR_UP:
					playr->onQueueAttack(Player::ATTACK_UPB);
					break;
					
					case BUTTONDIR_RIGHT:
					playr->onQueueAttack(Player::ATTACK_SIDEB);
					break;
					
					case BUTTONDIR_DOWN:
					playr->onQueueAttack(Player::ATTACK_DOWNB);
					break;
					
					case BUTTONDIR_LEFT:
					playr->onQueueAttack(Player::ATTACK_SIDEB);
					break;
				}
			}
			break;
			
			case UP:
			if(playr->chargingAttack)
			{
				playr->doChargingAttack(BUTTON_SPECIAL);
			}
			break;
		}
	}
	
	void Controls::buttonZ(byte pNum, byte type)
	{
		Player*playr = Global::getPlayerActor(pNum);
		switch(type)
		{
			case DOWN:
			buzzForButton();
			playr->checkAttacks();
			if(playr->canDo)
			{
				if(playr->itemHolding == null)
				{
					if(playr->holdingPlayer)
					{
						playr->grabAttack();
					}
					else
					{
						playr->grab();
					}
				}
				else
				{
					switch(playr->buttondir)
					{
						case BUTTONDIR_CENTER:
						playr->discardItem();
						break;
						
						case BUTTONDIR_UP:
						playr->tossItem(Player::ATTACK_UPA);
						break;
						
						case BUTTONDIR_RIGHT:
						playr->tossItem(Player::ATTACK_SIDEA);
						break;
						
						case BUTTONDIR_DOWN:
						playr->tossItem(Player::ATTACK_DOWNA);
						break;
						
						case BUTTONDIR_LEFT:
						playr->tossItem(Player::ATTACK_SIDEA);
						break;
					}
				}
			}
			break;
			
			case UP:
			break;
		}
	}
	
	void Controls::iCadeStateChangedHandler(iCadeState state)
	{
		ControllerButtonStates[BUTTON_UP] = (state&iCadeJoystickUp)!=0;
		ControllerButtonStates[BUTTON_DOWN] = (state&iCadeJoystickDown)!=0;
		ControllerButtonStates[BUTTON_LEFT] = (state&iCadeJoystickLeft)!=0;
		ControllerButtonStates[BUTTON_RIGHT] = (state&iCadeJoystickRight)!=0;
		
		//ControllerButtonStates[BUTTON_SELECT] = (state&iCadeButtonA)!=0; // Select
		//ControllerButtonStates[BUTTON_SHEILD] = (state&iCadeButtonB)!=0; // Left Shoulder
		ControllerButtonStates[BUTTON_PAUSE] = (state&iCadeButtonC)!=0;
		ControllerButtonStates[BUTTON_GRAB] = (state&iCadeButtonD)!=0;
		if((state&iCadeButtonE) || (state&iCadeButtonH))
		{
			ControllerButtonStates[BUTTON_JUMP] = true;
		}
		else
		{
			ControllerButtonStates[BUTTON_JUMP] = false;
		}
		ControllerButtonStates[BUTTON_STANDARD] = (state&iCadeButtonF)!=0;
		ControllerButtonStates[BUTTON_SPECIAL] = (state&iCadeButtonG)!=0;
	}
	
	void Controls::iCadeButtonDownHandler(iCadeState button)
	{
		//
	}
	
	void Controls::iCadeButtonUpHandler(iCadeState button)
	{
		//
	}
}
