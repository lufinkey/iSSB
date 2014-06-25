
#include "Player.h"
#include "Global.h"
#include "Stage.h"
#include "Item.h"
#include "Projectile.h"
#include "ProjectileManager.h"
#include "Camera.h"
#include "AttackTemplates.h"
#include "ItemManager.h"
#include "P2PDataManager.h"

namespace SmashBros
{
	const float Player::jumpXBoost = 0.8f;

	Player::Player(float x1, float y1, byte playerNo, byte team) : GameElement(x1,y1)
	{
		aiType = AI_NORMAL;
		firstUpdate = true;
		folderPath = "/";
		playerColor = Color::WHITE;
		stock = 3;
		chargebar = null;
		lastGroundPlat = null;
		lastGroundX = 0;
		groundCollidedFrame = false;
		//collideQueue = ArrayList<byte>();
		itemCollidingIndex = -1;
		itemHolding = null;
		itemWearing = null;
		itemHatting = null;
		itemWielding = null;
		hangColliding = false;
		prevHangColliding = false;
		groundColliding = false;
		prevGroundColliding = false;
		groundCheck = false;
		hurtFrame = 0;
		//hitboxPoint = RectangleF();
		moveLeft = 0;
		moveRight = 0;
		up = false;
		upKey = false;
		down = false;
		runTime = 0;
		smashTime = 0;
		moveTime = 0;
		buttondir = 0;
		name = "unknown";
		charNo = 0;
		alive = false;
		weight = 0.1;
		lastHit = 0;
		percent = 0;
		onGround = false;
		landing = false;
		jumping = false;
		hurt = 0;
		hurtTime = 0;
		invincible = false;
		deflectState = false;
		dropping = false;
		canDropThrough = false;
		dropTime = 0;
		canDo = false;
		xVel = 0;
		yVel = 0;
		cpu = false;
		comboTime = 0;
		standardCombo = 0;
		hitAmount = 0;
		attackTime = 0;
		grabbed = false;
		hasgrabbed = false;
		grabbing = false;
		attacksHolder = -1;
		attacksPriority = 0;
		chargeSmash = 0;
		chargingAttack = false;
		smashPower = 0;
		canFinalsmash = false;
		bUp = false;
		doubleJump = 0;
		hanging = false;
		
		walkSpeed = 2;
		runSpeed = 3;
		fallWalk = 1;
		fallRun = 2;
		flyTime = 4;
		flyRunTime = 4;
		recoverAmount = 7/8;
		recoverRunAmount = 6/7;
		
		this->playerNo = playerNo;
		Console::WriteLine((String)"successfully created player " + playerNo);
		
		this->team=team;
		Console::WriteLine(((String)"player" + playerNo) + ((String)" is on team " + team));
		
		offScreenExplosion = new OffScreenExplode(playerNo);
		
		indicator = new Actor(0,0);
		setIndicatorColor();
		switch(playerNo)
		{
			default:
			indicator->addAnimation(new Animation("normal",1,"Images/Game/Indicators/p0_down.png"));
			break;
			
			case 1:
			indicator->addAnimation(new Animation("normal",1,"Images/Game/Indicators/p1_down.png"));
			break;
			
			case 2:
			indicator->addAnimation(new Animation("normal",1,"Images/Game/Indicators/p2_down.png"));
			break;
			
			case 3:
			indicator->addAnimation(new Animation("normal",1,"Images/Game/Indicators/p3_down.png"));
			break;
			
			case 4:
			indicator->addAnimation(new Animation("normal",1,"Images/Game/Indicators/p4_down.png"));
			break;
		}
		indicator->changeAnimation("normal", FORWARD);
		
		indicX = 0;
		indicY = 0;
		setIndic = false;

		weight=0.2;
		hangPoint = Vector2i(15,20);
		itemOffsetX = 0;
		itemOffsetY = 0;

		charNo = Global::selectedChar[playerNo-1];

		alive = true;
		
		stock = Global::stockAmount;
		
		percent = 0;
		
		onGround = false;
		groundCheck = false;
		down = false;
		
		//canDo=1;
		//runTime=-5;

		hitbox = new HitBox(playerNo, x,y,1,1);
		setHitbox(-10, -10, 20, 20);
		setHangPoint(8, 16);

		attacksHolder=-1;
		grabbed = false;
		hasgrabbed = false;
		grabbing = false;
	}

	Player::~Player()
	{
		if(indicator!=null)
		{
			delete indicator;
		}
		if(offScreenExplosion!=null)
		{
			delete offScreenExplosion;
		}
		if(chargebar!=null)
		{
			delete chargebar;
		}
		if(itemHolding!=null)
		{
			delete itemHolding;
		}
		if(itemWearing!=null)
		{
			delete itemWearing;
		}
		if(itemHatting!=null)
		{
			delete itemHatting;
		}
		if(itemWielding!=null)
		{
			delete itemWielding;
		}
		if(hitbox!=null)
		{
			delete hitbox;
		}
	}
	
	void Player::whenCreated()
	{
		Console::WriteLine((String)"loading player " + playerNo + "'s animations");
		
		this->Load();
		
		//randomizer = AttackRandomizer(playerNo);
		randomizer.setPlayerNo(playerNo);
		
		LoadAttackTypes();
		
		if(x <= Global::currentStage->x)
		{
			playerdir = 2;
			changeAnimation("stand_right",FORWARD);
		}
		else
		{
			playerdir = 1;
			changeAnimation("stand_left",FORWARD);
		}
		
		cpu = Global::CPU[playerNo-1];
		
		currentEnemy = null;

		if(Global::suddenDeath)
		{
		    percent=300;
		}
		
		for(int i=0; i<8; i++)
		{
			prevCollidePlatform[i]=false;
		}
		
		//attackMgr = AttackManager();
		//playerCollisions = CollisionManager();
		//playerRectCollisions = CollisionManager();

		if(cpu)
		{
			setInitialCPUTarget();
		    //currentTarget=initCheckTarget(playerNo);
			if(currentEnemy!=null)
			{
				Console::WriteLine((String)"player " + playerNo + (String)" created with currentTarget " + currentEnemy->playerNo);
			}
			else
			{
				Console::WriteLine((String)"player " + playerNo + (String)" created with no currentTarget");
			}
		}
		else
		{
			currentEnemy = null;
		}
		
		onCreate();
	}

	void Player::onCreate()
	{
		//Open for implementation
	}

	void Player::reset()
	{
		if(attacksPriority==7 || canFinalsmash)
	    {
	    	Global::playerHasSmashBall = false;
	    	Global::smashBallOnField = false;
	    	canFinalsmash = false;
	    }
		xvelocity = 0;
		yvelocity = 0;
		alive = true;
		for(int i=0; i<8; i++)
		{
			prevCollidePlatform[i] = false;
			currentCollidePlatform[i] = false;
			currentCollidePlatformActor[i] = null;
		}
		playerCollisions.clear();
		playerRectCollisions.clear();
		if(itemHolding!=null)
        {
			itemHolding->destroy();
        	itemHolding->onDestroy();
        	Console::WriteLine((String)"Destroyed Item " + Global::getItemName(itemHolding->itemNo));
        	delete itemHolding;
        	itemHolding = null;
        }
        if(itemWearing!=null)
        {
			itemWearing->destroy();
        	itemWearing->onDestroy();
        	Console::WriteLine((String)"Destroyed Item " + Global::getItemName(itemWearing->itemNo));
        	delete itemWearing;
        	itemWearing = null;
        }
        if(itemHatting!=null)
        {
			itemHatting->destroy();
        	itemHatting->onDestroy();
        	Console::WriteLine((String)"Destroyed Item " + Global::getItemName(itemHatting->itemNo));
        	delete itemHatting;
        	itemHatting = null;
        }
        if(itemWielding!=null)
        {
			itemWielding->destroy();
        	itemWielding->onDestroy();
        	Console::WriteLine((String)"Destroyed Item " + Global::getItemName(itemWielding->itemNo));
        	delete itemWielding;
        	itemWielding = null;
        }
		currentHangPoint = null;
		hangColliding = false;
		prevHangColliding = false;
		groundColliding = false;
		prevGroundColliding = false;
		hurtFrame = 0;
		moveLeft = 0;
		moveRight = 0;
		up = false;
		upKey = false;
		down = false;
		runTime = 0;
		smashTime = 0;
		moveTime = 0;
		buttondir = 0;
		playerdir = 2;
		lastHit = 0;
		percent = 00;
		onGround = false;
		landing = false;
		jumping = false;
		hurt = 0;
		hurtTime = 0;
		dropping = false;
		canDropThrough = false;
		dropTime = 0;
		canDo = true;
		xVel = 0;
		yVel = 0;
		currentEnemy = null;
		grabbed = false;
		hasgrabbed = false;
		grabbing = false;
		attacksHolder = -1;
		attacksPriority = 0;
		chargeSmash = 0;
		smashPower = 0;
		bUp = false;
		doubleJump = 0;
		hitAmount=0;
		deflectState = false;
		//canFinalsmash = false;
		hanging = false;
		//invincible = false;
		setToDefaultValues();
		onDestroy();
	}

	void Player::respawn()
	{
		reset();
		Vector2i pnt = Global::currentStage->getSpawnPoint(playerNo);
		x = (float)pnt.x;
		y = (float)pnt.y;
		animFinish();
		setInitialCPUTarget();
		Console::WriteLine((String)"respawning player " + playerNo);
	}
	
	/** Loads all of the animations for the character. Should be overridden. 
	 * Animations can be added using {@link #addSingleAnimation(String, String, int, int, int)} 
	 * and {@link #addTwoSidedAnimation(String, String, int, int, int)} */
	void Player::Load()
	{
		//
	}
	
	void Player::Unload()
	{
		for(int i=0; i<files.size(); i++)
		{
			AssetManager::unloadImage(files.get(i));
		}
	}
	
	void Player::addFile(String file)
	{
		for(int i=0; i<files.size(); i++)
		{
			if(file.equals(files.get(i)))
			{
				return;
			}
		}
		files.add(file);
	}
	
	void Player::loadFile(String file)
	{
		AssetManager::loadImage(file);
		addFile(file);
	}
	
	void Player::LoadAttackTypes()
	{
		//Open for implementation
	}
	
	//x, y, animIndex, frame, percent, Scale, bools
	//4, 4, 4,         4,     4        4,     1     = 25
	void Player::handleAddP2PData(DataVoid&data)
	{
		int frame = getAnimation()->getCurrentFrame();
		int animIndex = getAnimIndex();
		Bitset bools;
		//hurt color
		if(hurtFrame>0)
		{
			bools.set(0, true);
		}
		else
		{
			bools.set(0, false);
		}
		//charge color
		if(chargeSmash>0)
		{
			bools.set(1, true);
		}
		else
		{
			bools.set(1, false);
		}
		//visible
		if(isVisible())
		{
			bools.set(2, true);
		}
		else
		{
			bools.set(2, false);
		}
		//alive
		if(alive)
		{
			bools.set(3, true);
		}
		else
		{
			bools.set(3, false);
		}
		byte boolsByte = bools.getByte();
		
		data.add(&x, sizeof(x));
		data.add(&y, sizeof(y));
		data.add(&animIndex, sizeof(animIndex));
		data.add(&frame, sizeof(frame));
		data.add(&percent, sizeof(percent));
		data.add(&Scale, sizeof(Scale));
		data.add(&boolsByte, sizeof(boolsByte));
		
		addP2PData(data);
	}
	
	void Player::handleSetP2PData(byte*&data)
	{
		//x
		x = DataVoid::toFloat(data);
		data += sizeof(float);
		
		//y
		y = DataVoid::toFloat(data);
		data += sizeof(float);
		
		//animIndex
		int animIndex = DataVoid::toInt(data);
		changeAnimation(animIndex, STOPPED);
		data += sizeof(int);
		
		//frame
		int frame = DataVoid::toInt(data);
		getAnimation()->setCurrentFrame(frame);
		data += sizeof(int);
		
		//percent
		percent = DataVoid::toInt(data);
		data += sizeof(int);
		
		Scale = DataVoid::toFloat(data);
		data += sizeof(float);
		
		//bools
		byte boolsByte = data[0];
		Bitset bools(boolsByte);
		//hurtColor and charge color
		if(bools.get(0))
		{
			Actor::setColor(Color::RED);
		}
		else if(bools.get(1))
		{
			Actor::setColor(Color::YELLOW);
		}
		else
		{
			Actor::setColor(playerColor);
		}
		//visibility
		if(bools.get(2))
		{
			setVisible(true);
		}
		else
		{
			setVisible(false);
		}
		//alive
		if(bools.get(3))
		{
			alive = true;
		}
		else
		{
			alive = false;
		}
		data += sizeof(byte);
		
		setP2PData(data);
	}
	
	void Player::addP2PData(DataVoid&data)
	{
		//Open for implementation
	}
	
	void Player::setP2PData(byte*&data)
	{
		//Open for implementation
	}
	
	void Player::addAIAttackType(byte attack, byte attacktype, float probability, boolean charge)
	{
		randomizer.setAttack(attack, attacktype, probability, charge);
	}
	
	void Player::addAnimation(Animation*a)
	{
		ArrayList<String> animFiles = a->getAllFilenames();
		for(int i=0; i<animFiles.size(); i++)
		{
			addFile(animFiles[i]);
		}
		Actor::addAnimation(a);
	}
	
	void Player::setColor(Color c)
	{
		playerColor = c;
		Actor::setColor(c);
	}
	
	boolean Player::isCPU()
	{
		return cpu;
	}
	
	boolean Player::isAlive()
	{
		return alive;
	}
	
	boolean Player::isHurt()
	{
		if(hurt==2)
		{
			return true;
		}
		return false;
	}
	
	boolean Player::isHoldingItem()
	{
		if(itemHolding!=null)
		{
			return true;
		}
		return false;
	}
	
	boolean Player::isWearingItem()
	{
		if(itemWearing!=null)
		{
			return true;
		}
		return false;
	}
	
	boolean Player::isHattingItem()
	{
		if(itemHatting!=null)
		{
			return true;
		}
		return false;
	}
	
	boolean Player::isWieldingItem()
	{
		if(itemWielding!=null)
		{
			return true;
		}
		return false;
	}
	
	boolean Player::isInvincible()
	{
		return invincible;
	}
	
	String Player::getName()
	{
		return name;
	}
	
	int Player::getPercent()
	{
		return percent;
	}
	
	int Player::getLastHitIndex()
	{
		return lastHit;
	}
	
	int Player::getAttacksHolder()
	{
		return attacksHolder;
	}
	
	double Player::getAttacksPriority()
	{
		return attacksPriority;
	}
	
	boolean Player::isOnGround()
	{
		return onGround;
	}
	
	void Player::setOnGround(boolean toggle)
	{
		onGround = toggle;
	}
	
	void Player::setItemOffset(float x1, float y1)
	{
		this->itemOffsetX = x1;
		this->itemOffsetY = y1;
	}
	
	byte Player::getPlayerDir()
	{
		return playerdir;
	}
	
	byte Player::getDirFacing()
	{
		if(upKey || up)
		{
			if(moveLeft>0)
			{
				return DIR_UPLEFT;
			}
			else if(moveRight>0)
			{
				return DIR_UPRIGHT;
			}
			else
			{
				return DIR_UP;
			}
		}
		else if(down)
		{
			if(moveLeft>0)
			{
				return DIR_DOWNLEFT;
			}
			else if(moveRight>0)
			{
				return DIR_DOWNRIGHT;
			}
			else
			{
				return DIR_DOWN;
			}
		}
		else if(moveLeft>0)
		{
			return DIR_LEFT;
		}
		else if(moveRight>0)
		{
			return DIR_RIGHT;
		}
		return 0;
	}
	
	byte Player::getTeam()
	{
		return team;
	}
	
	boolean Player::canFinalSmash()
	{
		return canFinalsmash;
	}
	
	void Player::setPlayerDir(byte dir)
	{
		if(dir==1 || dir==2)
		{
			playerdir = dir;
		}
		else
		{
			Console::WriteLine((String)"Error Player.setPlayerDir(byte): invalid argument " + dir);
		}
	}
	
	byte Player::getPlayerNo()
	{
		return playerNo;
	}
	
	void Player::setCantDo()
	{
		canDo = false;
	}
	
	boolean Player::CanDo()
	{
		checkAttacks();
		return canDo;
	}
	
	boolean Player::checkIfAble()
	{
		return true;
	}
	
	boolean Player::isGrabbed()
	{
		return grabbed;
	}
	
	int Player::getStock()
	{
		return stock;
	}
	
	boolean Player::hasGrabbed()
	{
		return hasgrabbed;
	}
	
	boolean Player::isGrabbing()
	{
		return grabbing;
	}
	
	boolean Player::isJumping()
	{
		return jumping;
	}
	
	boolean Player::isHanging()
	{
		return hanging;
	}
	
	void Player::setHanging(boolean toggle)
	{
		hanging = toggle;
	}
	
	void Player::setJumping(boolean toggle)
	{
		jumping = toggle;
	}
	
	void Player::finishDeflect()
	{
		deflectState = false;
	}
	
	void Player::resetAttackCollisions()
	{
		playerCollisions.clear();
	}
	
	int Player::getSmashPower()
	{
		if(chargebar!=null)
		{
			smashPower = (int)chargebar->currentPower;
		}
		else
		{
			smashPower = 0;
		}
		return smashPower;
	}
	
	byte Player::getMoveLeft()
	{
		return moveLeft;
	}
	
	byte Player::getMoveRight()
	{
		return moveRight;
	}
	
	/** Sets the hitbox coordinates relative to the center of the character. Default value is -10, -10, 20, 20 */
	void Player::setHitbox(float x1, float y1, int w, int h)
	{
		hitboxPoint.x = x1;
		hitboxPoint.y = y1;
		hitboxPoint.width = (float)w;
		hitboxPoint.height = (float)h;
		hitbox->x = x + x1;
		hitbox->y = y + y1;
		hitbox->width = w;
		hitbox->height = h;
	}
	
	WireframeActor*Player::getHitbox()
	{
		updateHitbox();
		return hitbox;
	}
	
	void Player::showHitboxWireframe(boolean toggle)
	{
		hitbox->setVisible(toggle);
	}
	
	void Player::setHitboxColor(Color c)
	{
		hitbox->setColor(c);
	}
	
	void Player::updateHitbox()
	{
		hitbox->x = x + (float)((float)hitboxPoint.x*this->Scale);
		hitbox->y = y + (float)((float)hitboxPoint.y*this->Scale);
		hitbox->width = (int)((float)hitboxPoint.width*this->Scale);
		hitbox->height = (int)((float)hitboxPoint.height*this->Scale);
	}
	
	void Player::setIndicatorOffset(float x1, float y1)
	{
		setIndic = true;
		indicX = x1;
		indicY = y1;
	}
	
	void Player::setIndicatorColor()
	{
		switch(team)
		{
			default:
			switch(playerNo)
			{
				default:
				indicator->setColor(Color(64,64,64));
				break;
				
				case 1:
				indicator->setColor(Color::RED);
				break;
				
				case 2:
				indicator->setColor(Color::BLUE);
				break;
				
				case 3:
				indicator->setColor(Color::GREEN);
				break;
				
				case 4:
				indicator->setColor(Color::YELLOW);
				break;
			}
			break;
			
			case TEAM_RED:
			indicator->setColor(Color::RED);
			break;
			
			case TEAM_BLUE:
			indicator->setColor(Color::BLUE);
			break;
			
			case TEAM_GREEN:
			indicator->setColor(Color::GREEN);
			break;
			
			case TEAM_YELLOW:
			indicator->setColor(Color::YELLOW);
			break;
		}
	}
	
	/** Sets the folder path where all of the animations are stored. Default value is "/" */
	void Player::setFolderPath(String path)
	{
		this->folderPath = path;
	}
	
	String Player::getFolderPath()
	{
		return this->folderPath;
	}
	
	/**
	 * Adds to the character an Animation that changes depending on the direction the character is facing. 
	 * Animations added this way can be accessed with the string of the animation name and either "_left" or "_right" depending on the direction 
	 * the character is facing.
	 * <p>
	 * @param name the name of the animation. (ex: "stand"). 
	 * After name is input here, it becomes 2 animations for each direction. (ex: "stand_left" or "stand_right")
	 * @param file the file name of the animation. Only the file name needs to be given since the path is set via {@link #setFolderPath(String)}
	 * @param fps the frame rate of the animation in frames per second.
	 * @param rows the number of rows that the image file contains.
	 * @param cols the number of columns that the image file contains.
	 */
	void Player::addTwoSidedAnimation(String name, String file, int fps, int rows, int cols)
	{
		Animation*anim;
		anim = new Animation(name + "_left",fps, rows,cols);
		anim->addFrame(folderPath + file);
		this->addAnimation(anim);
		
		anim = new Animation(name + "_right",fps, rows,cols);
		anim->addFrame(folderPath + file);
		anim->mirror(true);
		this->addAnimation(anim);
	}
	
	/**
	 * Adds to the character an Animation that stays the same regardless of the direction it is facing.
	 * <p>
	 * @param name the name of the animation. (ex: "special_attack_down").
	 * @param file the file name of the animation. Only the file name needs to be given since the path is set via {@link #setFolderPath(String)}
	 * @param fps the frame rate of the animation in frames per second.
	 * @param rows the number of rows that the image file contains.
	 * @param cols the number of columns that the image file contains.
	 */
	void Player::addSingleAnimation(String name, String file, int fps, int rows, int cols)
	{
		Animation*anim;
		anim = new Animation(name,fps, rows,cols);
		anim->addFrame(folderPath + file);
		this->addAnimation(anim);
	}
	
	/** Sets the point where the character hangs, relative to the top left corner of the character. Default value is 8, 16 */
	void Player::setHangPoint(int x1,int y1)
	{
		hangPoint.x = x1;
		hangPoint.y = y1;
	}
	
	void Player::onAnimationFinish(const String&n)
	{
		if(n.equals("walk_left") || n.equals("walk_right") || n.equals("run_left") || n.equals("run_right") ||
			n.equals("smash_charge_left") || n.equals("smash_charge_right") || n.equals("hang_left") || 
			n.equals("hang_right"))
		{
			//
		}
		else if(n.equals("hurt_spin_up"))
		{
			if(yvelocity>0)
			{
			    switch(playerdir)
			    {
			        case 1:
			        changeAnimation("fall_left", NO_CHANGE);
			        break;
			 
			        case 2:
			        changeAnimation("fall_right", NO_CHANGE);
			        break;
			    }
			}
		}
		else if(n.equals("hurt_flip_left") || n.equals("hurt_flip_right"))
		{
			if(onGround && yvelocity==0 && xvelocity==0)
			{
			    animFinish();
			}
		}
		else if(n.equals("hurt_minor_left") || n.equals("hurt_minor_right") || n.equals("hurt_fly_left") || n.equals("hurt_fly_right")
		|| n.equals("hurt_spin_left") || n.equals("hurt_spin_right"))
		{
			if(onGround)
			{
				animFinish();
			}
		}
		else
		{
			animFinish();
		}
	}
	
	void Player::checkAttacks()
	{
		boolean itemDo = true;
		if(itemHolding!=null)
		{
			itemDo = itemHolding->holderCanDo();
		}
	    if((attacksHolder==-1) && (!grabbed) && (hurt!=2) && (!landing) && checkIfAble() && itemDo)
	    {
	        canDo=true;
	    }
	    else
	    {
	        canDo=false;
	    }
	}
	
	void Player::destroyCharge()
	{
		chargingAttack = false;
		chargeSmash = 0;
		if(chargebar!=null)
		{
			this->smashPower = (int)chargebar->currentPower;
		}
		chargebar = null;
	}
	
	void Player::animFinish()
	{
		switch(playerdir)
	    {
	        case 1:
	        if(onGround)
	        {
	            if(down)
	            {
	            	changeAnimation("crouch_left", NO_CHANGE);
	            }
	            else
	            {
	            	changeAnimation("stand_left", NO_CHANGE);
	            }
	        }
	        else
	        {
	        	changeAnimation("fall_left", NO_CHANGE);
	        }
	        break;
	 
	        case 2:
		    if(onGround)
		    {
		        if(down)
		        {
		         	changeAnimation("crouch_right", NO_CHANGE);
		        }
		        else
		        {
		          	changeAnimation("stand_right", NO_CHANGE);
		        }
		    }
		    else
		    {
		      	changeAnimation("fall_right", NO_CHANGE);
		    }
		    break;
	    }
		playerCollisions.clear();
	    landing = false;
	    up = false;
	    jumping = false;
	    canDo=true;
	    chargingAttack = false;
	    attacksHolder=-1;
	    attacksPriority=0;
	    chargeSmash=0;
	    smashPower=0;
	    hitAmount=0;
	    xVel=0;
	    yVel=0;
	    deflectState = false;
	    setToDefaultValues();
	}
	
	/**
	 * Used for reseting variables when Animations finish or character must be reset. Should be overridden if custom variables are used.
	 */
	void Player::setToDefaultValues()
	{
		//
	}
	
	void Player::onDestroy()
	{
		//
	}
	
	void Player::setInitialCPUTarget()
	{
		double closestDist = 0;
		Player*closestTarget = null;
		
		for(int i=0; i<=Global::possPlayers; i++) //TODO: loop characters
		{
			Player*compareTarget = Global::characters[i];
			if(closestTarget==null)
			{
				if(compareTarget!=null && compareTarget->playerNo!=playerNo && compareTarget->isAlive() && !(Global::teamBattle && compareTarget->team == team)
				&& Global::currentStage->checkSafeArea(compareTarget))
				{
					closestTarget = compareTarget;
					closestDist = distanceUnSqr(x,y,compareTarget->x,compareTarget->y);
				}
			}
			else if(compareTarget!=null && compareTarget->playerNo!=playerNo && compareTarget->isAlive() && !(Global::teamBattle && compareTarget->team == team)
				&& Global::currentStage->checkSafeArea(compareTarget))
			{
				double dist = distanceUnSqr(x,y,compareTarget->x,compareTarget->y);
				if(dist<closestDist)
				{
					closestTarget = compareTarget;
					closestDist = dist;
				}
			}
		}
		
		if(closestTarget!=null && Global::teamBattle && closestTarget->team == team)
		{
			closestTarget = null;
		}
		
		currentEnemy = closestTarget;
	}
	
	void Player::updateCPUTarget()
	{
		double currentDist = 0;
		boolean targetNull = true;
		if(currentEnemy!=null)
		{
			if(!(currentEnemy->playerNo!=playerNo && currentEnemy->isAlive() && !(Global::teamBattle && currentEnemy->team == team) && Global::currentStage->checkSafeArea(currentEnemy)))
			{
				currentEnemy=null;
			}
		}
		if(currentEnemy!=null)
		{
			targetNull = false;
			currentDist = distanceUnSqr(x,y,currentEnemy->x, currentEnemy->y);
		}
		else
		{
			setInitialCPUTarget();
			if(currentEnemy!=null)
			{
				targetNull = false;
				currentDist = distanceUnSqr(x,y,currentEnemy->x, currentEnemy->y);
			}
		}
		
		ArrayList<Player*> possibleTargets = ArrayList<Player*>();
		
		for(int i=0; i<=Global::possPlayers; i++) //TODO: loop characters
		{
			Player*playr = Global::characters[i];
			if(playr!=null && playr->playerNo!=playerNo && playr->isAlive() && !(Global::teamBattle && playr->team == team) && Global::currentStage->checkSafeArea(playr))
			{
				possibleTargets.add(playr);
			}
		}
		
		if(possibleTargets.size()==0)
		{
			currentEnemy = null;
			return;
		}
		
		ArrayList<Player*> priorityTargets = ArrayList<Player*>();
		
		for(int i=0; i<possibleTargets.size(); i++)
		{
			Player*playr = possibleTargets.get(i);
			boolean hitOverlap = hitbox->rectsColliding(playr->hitbox);
			double dist = distanceUnSqr(x,y,playr->x,playr->y);
			if((dist<10000 || hitOverlap) && ((!targetNull && dist<currentDist)||targetNull))
			{
				if(playr->x < x)
				{
					if(playerdir==RIGHT)
					{
						priorityTargets.add(playr);
					}
				}
				else if(playr->x > x)
				{
					if(playerdir==LEFT)
					{
						priorityTargets.add(playr);
					}
				}
			}
		}
		
		if(priorityTargets.size() > 0)
		{
			Player*newTarget = priorityTargets.get(0);
			double dist = distanceUnSqr(x, y, newTarget->x, newTarget->y);
			
			for(int i=1; i<priorityTargets.size(); i++)
			{
				Player*cmpr = priorityTargets.get(i);
				double cmprDist = distanceUnSqr(x, y, cmpr->x, cmpr->y);
				
				if(cmprDist<dist)
				{
					newTarget = cmpr;
					dist = cmprDist;
				}
			}
			
			currentEnemy = newTarget;
		}
		else if(currentEnemy!=null)
		{
			if(currentDist>108900) //330
			{
				for(int i=0; i<possibleTargets.size(); i++)
				{
					Player*cmpr = possibleTargets.get(i);
					double cmprDist = distanceUnSqr(x, y, cmpr->x, cmpr->y);
					if(cmprDist<currentDist)
					{
						currentEnemy = cmpr;
						currentDist = cmprDist;
					}
				}
			}
		}
		else
		{
			currentEnemy = possibleTargets.get(0);
			currentDist = distanceUnSqr(x, y, currentEnemy->x, currentEnemy->y);
			
			for(int i=1; i<possibleTargets.size(); i++)
			{
				Player*cmpr = possibleTargets.get(i);
				double cmprDist = distanceUnSqr(x, y, cmpr->x, cmpr->y);
				if(cmprDist<currentDist)
				{
					currentEnemy = cmpr;
					currentDist = cmprDist;
				}
			}
		}
	}
	
	boolean Player::checkbUpRecovery()
	{
		if(bUp && CanDo() && randomizer.totalAttacks(ATTACKTYPE_UPMOVE)>0)
		{
			return true;
		}
		return false;
	}
	
	void Player::recoverJump()
	{
		if(CanDo())
		{
			if(doubleJump>0 || onGround)
			{
				jump();
			}
			else if(!bUp)
			{
				randomizer.doAttack(ATTACKTYPE_UPMOVE);
			}
		}
	}
	
	boolean Player::checkTrappedUnder(Platform*plat)
	{
		updateHitbox();
		if(plat->getType() == Platform::TYPE_NORMAL)
		{
			float platX = plat->x;
			float platY = plat->y;
			if(plat->getCollideType() == Platform::COLLIDE_SOLID)
			{
				platX = plat->x - plat->width/2;
				platY = plat->y - plat->height/2;
			}
			if(y > (platY + plat->height/2))
			{
				if((hitbox->x + hitbox->width)>=(platX-2) && hitbox->x<=(platX + plat->width+2))
				{
					return true;
				}
			}
		}
		return false;
	}
	
	boolean Player::checkTrappedUnder(Rectangle plat)
	{
		updateHitbox();
		if(y > (plat.y + plat.height/2))
		{
			if((hitbox->x + hitbox->width)>=(plat.x-2) && hitbox->x<=(plat.x + plat.width+2))
			{
				return true;
			}
		}
		return false;
	}
	
	boolean Player::checkTrappedOver(Rectangle plat)
	{
		updateHitbox();
		if(y < (plat.y + plat.height/2))
		{
			if((hitbox->x + hitbox->width)>=(plat.x-2) && hitbox->x<=(plat.x + plat.width+2))
			{
				return true;
			}
		}
		return false;
	}
	
	boolean Player::isObstacle(Platform*plat)
	{
		if(plat==null)
		{
			return false;
		}
		if(plat->getType()==Platform::TYPE_GOTHROUGH)
		{
			return false;
		}
		return true;
	}
	
	float Player::getMinAmountTrappedUnder(Platform*plat)
	{
		updateHitbox();
		if(plat->getType() == Platform::TYPE_NORMAL)
		{
			float platX = plat->x;
			float platY = plat->y;
			if(plat->getCollideType() == Platform::COLLIDE_SOLID)
			{
				platX = plat->x - plat->width/2;
				platY = plat->y - plat->height/2;
			}
			if(y < (platY + plat->height/2))
			{
				if(hitbox->x>platX && (hitbox->x + hitbox->width)<(platX + plat->width))
				{
					float d1 = (hitbox->x + hitbox->width) - platX;
					float d2 = (platX + plat->width) - hitbox->x;
					if(d1<d2)
					{
						return d1;
					}
					else
					{
						return d2;
					}
				}
			}
		}
		return -1;
	}
	
	Vector2f Player::findRecoveryTarget()
	{
		HangPoint*lHangLeft = null; double lHldist = 0;
		HangPoint*lHangRight = null; double lHrdist = 0;
		Platform*lPlat = null; double lPlatdist = 0;
		Platform*lGTPlat = null; double lgtPlatdist = 0;
		HangPoint*rHangLeft = null; double rHldist = 0;
		HangPoint*rHangRight = null; double rHrdist = 0;
		Platform*rPlat = null; double rPlatdist = 0;
		Platform*rGTPlat = null; double rgtPlatdist = 0;
		
		for(int i=0; i<Global::currentStage->hangs.size(); i++) //check for best hangpoints (closest)
		{
			HangPoint*hang = Global::currentStage->hangs.get(i);
			float hangX = hang->x;
			if(hang->getHangSide()==HangPoint::RIGHT)
			{
				hangX = hang->x + hang->width;
			}
			if(hangX<=x)
			{
				switch(hang->getHangSide())
				{
					case HangPoint::LEFT:
					if(lHangLeft==null)
					{
						lHangLeft = hang;
						lHldist = distanceUnSqr(x, y, hangX, hang->y);
					}
					else
					{
						double newDist = distanceUnSqr(x, y, hangX, hang->y);
						if(newDist<lHldist)
						{
							lHldist = newDist;
							lHangLeft = hang;
						}
					}
					break;
					
					case HangPoint::RIGHT:
					if(lHangRight==null)
					{
						lHangRight = hang;
						lHrdist = distanceUnSqr(x, y, hangX, hang->y);
					}
					else
					{
						double newDist = distanceUnSqr(x, y, hangX, hang->y);
						if(newDist<lHrdist)
						{
							lHrdist = newDist;
							lHangRight = hang;
						}
					}
					break;
				}
			}
			else //hangX>this->x
			{
				switch(hang->getHangSide())
				{
					case HangPoint::LEFT:
					if(rHangLeft==null)
					{
						rHangLeft = hang;
						rHldist = distanceUnSqr(x, y, hangX, hang->y);
					}
					else
					{
						double newDist = distanceUnSqr(x, y, hangX, hang->y);
						if(newDist<rHldist)
						{
							rHldist = newDist;
							rHangLeft = hang;
						}
					}
					break;
					
					case HangPoint::RIGHT:
					if(rHangRight==null)
					{
						rHangRight = hang;
						rHrdist = distanceUnSqr(x, y, hangX, hang->y);
					}
					else
					{
						double newDist = distanceUnSqr(x, y, hangX, hang->y);
						if(newDist<rHrdist)
						{
							rHrdist = newDist;
							rHangRight = hang;
						}
					}
					break;
				}
			}
		}
		
		for(int i=0; i<Global::currentStage->platforms.size(); i++) //check for best platforms (closest)
		{
			Platform*plat = Global::currentStage->platforms.get(i);
			float platX;
			float platY;
			if(plat->getCollideType()==Platform::COLLIDE_BOX)
			{
				platX = plat->x + (plat->width/2);
				platY = plat->y;
			}
			else
			{
				platX = plat->x;
				platY = plat->y - (plat->height/2);
			}
			if(platX<=this->x)
			{
				switch(plat->getType())
				{
					case Platform::TYPE_NORMAL:
					if(lPlat==null)
					{
						lPlat = plat;
						lPlatdist = distanceUnSqr(x, y, platX, platY);
					}
					else
					{
						double newDist = distanceUnSqr(x, y, platX, platY);
						if(newDist<lPlatdist)
						{
							lPlatdist = newDist;
							lPlat = plat;
						}
					}
					break;
					
					case Platform::TYPE_GOTHROUGH:
					if(lGTPlat==null)
					{
						lGTPlat = plat;
						lgtPlatdist = distanceUnSqr(x, y, platX, platY);
					}
					else
					{
						double newDist = distanceUnSqr(x, y, platX, platY);
						if(newDist<lgtPlatdist)
						{
							lgtPlatdist = newDist;
							lGTPlat = plat;
						}
					}
					break;
				}
			}
			else //platX>x
			{
				switch(plat->getType())
				{
					case Platform::TYPE_NORMAL:
					if(rPlat==null)
					{
						rPlat = plat;
						rPlatdist = distanceUnSqr(x, y, platX, platY);
					}
					else
					{
						double newDist = distanceUnSqr(x, y, platX, platY);
						if(newDist<rPlatdist)
						{
							rPlatdist = newDist;
							rPlat = plat;
						}
					}
					break;
					
					case Platform::TYPE_GOTHROUGH:
					if(rGTPlat==null)
					{
						rGTPlat = plat;
						rgtPlatdist = distanceUnSqr(x, y, platX, platY);
					}
					else
					{
						double newDist = distanceUnSqr(x, y, platX, platY);
						if(newDist<rgtPlatdist)
						{
							rgtPlatdist = newDist;
							rGTPlat = plat;
						}
					}
					break;
				}
			}
		}
			
		//Finished checking best hangpoints and platforms
			
		//check best among the best and return its location, else return Vector(x,y)
			
		HangPoint*bestHang = null;
		double bestHangDist = 0;
		Platform*bestPlat = null;
		double bestPlatDist = 0;
		
		//checking best hang
		if(playerdir==LEFT)
		{
			if(lHangLeft!=null)
			{
				if(rHangRight!=null && (lHldist>10000 && y>lHangLeft->y)) //100
				{
					if(lHldist<rHrdist)
					{
						if(lHangRight!=null && lHrdist<lHldist && (doubleJump>0 || checkbUpRecovery() || (y<=lHangRight->y && lHrdist<2500)))//50
						{
							bestHang = lHangRight;
							bestHangDist = lHrdist;
						}
						else
						{
							bestHang = lHangLeft;
							bestHangDist = lHldist;
						}
					}
					else
					{
						if(rHangLeft!=null && rHldist<rHrdist && (doubleJump>0 || checkbUpRecovery() || (y<=rHangLeft->y && rHldist<2500)))//50
						{
							bestHang = rHangLeft;
							bestHangDist = rHldist;
						}
						else
						{
							bestHang = rHangRight;
							bestHangDist = rHrdist;
						}
					}
				}
				else
				{
					if(rHangLeft!=null && rHldist<lHldist && (doubleJump>0 || checkbUpRecovery() || (y<=rHangLeft->y && rHldist<2500)))//50
					{
						bestHang = rHangLeft;
						bestHangDist = rHldist;
					}
					else
					{
						bestHang = lHangLeft;
						bestHangDist = lHldist;
					}
				}
			}
			else
			{
				if(rHangRight!=null)
				{
					if(rHangLeft!=null && rHldist<rHrdist && (doubleJump>0 || checkbUpRecovery() || (y<=rHangLeft->y && rHldist<2500)))//50
					{
						bestHang = rHangLeft;
						bestHangDist = rHldist;
					}
					else
					{
						if(lHangRight!=null && lHrdist<rHrdist && (doubleJump>0 || checkbUpRecovery() || (y<=lHangRight->y && lHrdist<2500)))//50
						{
							bestHang = lHangRight;
							bestHangDist = lHrdist;
						}
						else
						{
							bestHang = rHangRight;
							bestHangDist = rHrdist;
						}
					}
				}
				else
				{
					if(lHangRight!=null)
					{
						if(rHangLeft!=null && rHldist<lHrdist && (doubleJump>0 || checkbUpRecovery() || (y<=rHangLeft->y && rHldist<2500)))//50
						{
							bestHang = rHangLeft;
							bestHangDist = rHldist;
						}
						else
						{
							bestHang = lHangRight;
							bestHangDist = lHrdist;
						}
					}
					else
					{
						if(rHangLeft!=null)
						{
							bestHang = rHangLeft;
							bestHangDist = rHldist;
						}
					}
				}
			}
		}
		else if(playerdir==RIGHT)
		{
			if(rHangRight!=null)
			{
				if(lHangLeft!=null && (lHldist>10000 && y>lHangLeft->y))
				{
					if(rHrdist<lHldist)
					{
						if(rHangLeft!=null && rHldist<rHrdist && (doubleJump>0 || checkbUpRecovery() || (y<=rHangLeft->y && rHldist<2500)))//50
						{
							bestHang = rHangLeft;
							bestHangDist = rHldist;
						}
						else
						{
							bestHang = rHangRight;
							bestHangDist = rHrdist;
						}
					}
					else
					{
						if(lHangRight!=null && lHrdist<lHldist && (doubleJump>0 || checkbUpRecovery() || (y<=lHangRight->y && lHrdist<2500)))//50
						{
							bestHang = lHangRight;
							bestHangDist = lHrdist;
						}
						else
						{
							bestHang = lHangLeft;
							bestHangDist = lHldist;
						}
					}
				}
				else
				{
					if(lHangRight!=null && lHrdist<rHrdist && (doubleJump>0 || checkbUpRecovery() || (y<=lHangRight->y && lHrdist<2500)))//50
					{
						bestHang = lHangRight;
						bestHangDist = lHrdist;
					}
					else
					{
						bestHang = rHangRight;
						bestHangDist = rHrdist;
					}
				}
			}
			else
			{
				if(lHangLeft!=null)
				{
					if(lHangRight!=null && lHrdist<lHldist && (doubleJump>0 || checkbUpRecovery() || (y<=lHangRight->y && lHrdist<2500)))//50
					{
						bestHang = lHangRight;
						bestHangDist = lHrdist;
					}
					else
					{
						if(rHangLeft!=null && rHldist<lHldist && (doubleJump>0 || checkbUpRecovery() || (y<=rHangLeft->y && rHldist<2500)))//50
						{
							bestHang = rHangLeft;
							bestHangDist = rHldist;
						}
						else
						{
							bestHang = lHangLeft;
							bestHangDist = lHldist;
						}
					}
				}
				else
				{
					if(rHangLeft!=null)
					{
						if(lHangRight!=null && lHrdist<rHldist && (doubleJump>0 || checkbUpRecovery() || (y<=lHangRight->y && lHrdist<2500)))//50
						{
							bestHang = lHangRight;
							bestHangDist = lHrdist;
						}
						else
						{
							bestHang = rHangLeft;
							bestHangDist = rHldist;
						}
					}
					else
					{
						if(lHangRight!=null)
						{
							bestHang = lHangRight;
							bestHangDist = lHrdist;
						}
					}
				}
			}
		}
		
		//checking best platform
		if(playerdir==LEFT)
		{
			ArrayList<Platform*> plats = ArrayList<Platform*>();
			ArrayList<double> platDists = ArrayList<double>();
			if(lPlat!=null)
			{
				plats.add(lPlat);
				platDists.add(lPlatdist);
			}
			if(rPlat!=null)
			{
				plats.add(rPlat);
				platDists.add(rPlatdist);
			}
			if(lGTPlat!=null)
			{
				plats.add(lGTPlat);
				platDists.add(lgtPlatdist);
			}
			if(rGTPlat!=null)
			{
				plats.add(rGTPlat);
				platDists.add(rgtPlatdist);
			}
			
			for(int i=0; i<plats.size(); i++)
			{
				Platform*plat = plats.get(i);
				double platDist = platDists.get(i);
				if(bestPlat==null)
				{
					bestPlat = plat;
					bestPlatDist = platDist;
				}
				else
				{
					float platX = plat->x;
					if(plat->getCollideType()==Platform::COLLIDE_BOX)
					{
						platX = plat->x + plat->width/2;
					}
					float plat2X = bestPlat->x;
					if(plat->getCollideType()==Platform::COLLIDE_BOX)
					{
						plat2X = bestPlat->x + bestPlat->width/2;
					}
					if(platX <= x)
					{
						if(plat2X > x)
						{
							if(bestPlatDist >= 10000 && (doubleJump==0 || !checkbUpRecovery()) && platDist<bestPlatDist)//100
							{
								bestPlat = plat;
								bestPlatDist = platDist;
							}
							else if(checkTrappedUnder(plat))
							{
								if(!checkTrappedUnder(bestPlat))
								{
									bestPlat = plat;
									bestPlatDist = platDist;
								}
							}
						}
						else if(platDist < bestPlatDist)
						{
							if(!checkTrappedUnder(plat))
							{
								bestPlat = plat;
								bestPlatDist = platDist;
							}
							else if(checkTrappedUnder(bestPlat))
							{
								float d1 = getMinAmountTrappedUnder(plat);
								float d2 = getMinAmountTrappedUnder(bestPlat);
								if(d1<d2)
								{
									bestPlat = plat;
									bestPlatDist = platDist;
								}
							}
						}
					}
					else if(platX > x)
					{
						if(plat2X <= x)
						{
							if(!checkTrappedUnder(plat))
							{
								if(checkTrappedUnder(bestPlat))
								{
									bestPlat = plat;
									bestPlatDist = platDist;
								}
								else
								{
									if(platDist<bestPlatDist)
									{
										bestPlat = plat;
										bestPlatDist = platDist;
									}
								}
							}
							else
							{
								if(checkTrappedUnder(bestPlat))
								{
									if(getMinAmountTrappedUnder(plat)<getMinAmountTrappedUnder(bestPlat))
									{
										bestPlat = plat;
										bestPlatDist = platDist;
									}
								}
								else
								{
									bestPlat = plat;
									bestPlatDist = platDist;
								}
							}
						}
						else if(plat2X > x)
						{
							if(checkTrappedUnder(plat))
							{
								if(checkTrappedUnder(bestPlat))
								{
									if(getMinAmountTrappedUnder(plat)<getMinAmountTrappedUnder(bestPlat))
									{
										bestPlat = plat;
										bestPlatDist = platDist;
									}
								}
							}
							else
							{
								if(platDist < bestPlatDist)
								{
									bestPlat = plat;
									bestPlatDist = platDist;
								}
							}
						}
					}
				}
			}
		}
		else if(playerdir==RIGHT)
		{
			ArrayList<Platform*> plats = ArrayList<Platform*>();
			ArrayList<double> platDists = ArrayList<double>();
			if(lPlat!=null)
			{
				plats.add(lPlat);
				platDists.add(lPlatdist);
			}
			if(rPlat!=null)
			{
				plats.add(rPlat);
				platDists.add(rPlatdist);
			}
			if(lGTPlat!=null)
			{
				plats.add(lGTPlat);
				platDists.add(lgtPlatdist);
			}
			if(rGTPlat!=null)
			{
				plats.add(rGTPlat);
				platDists.add(rgtPlatdist);
			}
			
			for(int i=0; i<plats.size(); i++)
			{
				Platform*plat = plats.get(i);
				double platDist = platDists.get(i);
				if(bestPlat==null)
				{
					bestPlat = plat;
					bestPlatDist = platDist;
				}
				else
				{
					float platX = plat->x;
					if(plat->getCollideType()==Platform::COLLIDE_BOX)
					{
						platX = plat->x + plat->width/2;
					}
					float plat2X = bestPlat->x;
					if(plat->getCollideType()==Platform::COLLIDE_BOX)
					{
						plat2X = bestPlat->x + bestPlat->width/2;
					}
					if(platX >= x)
					{
						if(plat2X < x)
						{
							if(bestPlatDist >= 10000 && (doubleJump==0 || !checkbUpRecovery()) && platDist<bestPlatDist)//100
							{
								bestPlat = plat;
								bestPlatDist = platDist;
							}
							else if(checkTrappedUnder(plat))
							{
								if(!checkTrappedUnder(bestPlat))
								{
									bestPlat = plat;
									bestPlatDist = platDist;
								}
							}
						}
						else if(platDist < bestPlatDist)
						{
							if(!checkTrappedUnder(plat))
							{
								bestPlat = plat;
								bestPlatDist = platDist;
							}
							else if(checkTrappedUnder(bestPlat))
							{
								float d1 = getMinAmountTrappedUnder(plat);
								float d2 = getMinAmountTrappedUnder(bestPlat);
								if(d1<d2)
								{
									bestPlat = plat;
									bestPlatDist = platDist;
								}
							}
						}
					}
					else if(platX < x)
					{
						if(plat2X >= x)
						{
							if(!checkTrappedUnder(plat))
							{
								if(checkTrappedUnder(bestPlat))
								{
									bestPlat = plat;
									bestPlatDist = platDist;
								}
								else
								{
									if(platDist<bestPlatDist)
									{
										bestPlat = plat;
										bestPlatDist = platDist;
									}
								}
							}
							else
							{
								if(checkTrappedUnder(bestPlat))
								{
									if(getMinAmountTrappedUnder(plat)<getMinAmountTrappedUnder(bestPlat))
									{
										bestPlat = plat;
										bestPlatDist = platDist;
									}
								}
								else
								{
									bestPlat = plat;
									bestPlatDist = platDist;
								}
							}
						}
						else if(plat2X < x)
						{
							if(checkTrappedUnder(plat))
							{
								if(checkTrappedUnder(bestPlat))
								{
									if(getMinAmountTrappedUnder(plat)<getMinAmountTrappedUnder(bestPlat))
									{
										bestPlat = plat;
										bestPlatDist = platDist;
									}
								}
							}
							else
							{
								if(platDist < bestPlatDist)
								{
									bestPlat = plat;
									bestPlatDist = platDist;
								}
							}
						}
					}
				}
			}
		}
		
		if(bestPlat==null)
		{
			if(bestHang==null)
			{
				return Vector2f(x,y);
			}
			else
			{
				float hangX = bestHang->x + bestHang->width/2;
				float hangY = bestHang->y;
				return Vector2f(hangX,hangY);
			}
		}
		else if(bestHang==null)
		{
			float platX;
			float platY;
			if(bestPlat->getCollideType()==Platform::COLLIDE_BOX)
			{
				platX = bestPlat->x + bestPlat->width/2;
				platY = bestPlat->y;
			}
			else
			{
				platX = bestPlat->x;
				platY = bestPlat->y-bestPlat->height/2;
			}
			return Vector2f(platX,platY);
		}
		else if(checkTrappedUnder(bestPlat) || bestHangDist<bestPlatDist)
		{
			float hangX = bestHang->x + bestHang->width/2;
			float hangY = bestHang->y;
			return Vector2f(hangX,hangY);
		}
		else
		{
			float platX;
			float platY;
			if(bestPlat->getCollideType()==Platform::COLLIDE_BOX)
			{
				platX = bestPlat->x + bestPlat->width/2;
				platY = bestPlat->y;
			}
			else
			{
				platX = bestPlat->x;
				platY = bestPlat->y-bestPlat->height/2;
			}
			return Vector2f(platX,platY);
		}
	}
	
	void Player::getToRecoveryTarget(Vector2f target)
	{
		byte dir = getDir2(x,y,target.x,target.y);
		
		double dist = distanceUnSqr(x,y,target.x,target.y);
		
		ArrayList<RectangleF> obstacles = ArrayList<RectangleF>();
		
		//find obstacles and adjust target to avoid
		for(int i=0; i<Global::currentStage->platforms.size(); i++)
		{
			Platform*plat = Global::currentStage->platforms.get(i);
			if(plat->getType() == Platform::TYPE_NORMAL)
			{
				RectangleF obstRect = RectangleF();
				if(plat->getCollideType() == Platform::COLLIDE_SOLID)
				{
					obstRect.x = plat->x - plat->width/2;
					obstRect.y = plat->y - plat->height/2;
					obstRect.width = (float)plat->width;
					obstRect.height = (float)plat->height;
				}
				else
				{
					obstRect.x = plat->x;
					obstRect.y = plat->y;
					obstRect.width = (float)plat->width;
					obstRect.height = (float)plat->height;
				}
				
				
				
				if(checkObstacleDir(obstRect, dir))
				{
					if(distanceUnSqr(x,y,obstRect.x+obstRect.width/2, obstRect.y+obstRect.height/2)<dist)
					{
						obstacles.add(obstRect);
					}
				}
			}
		}
		
		if(obstacles.size()>0)
		{
			float left = 0;
			float right = 0;
			float top = 0;
			float bottom = 0;
			for(int i=0; i<obstacles.size(); i++)
			{
				RectangleF rect = obstacles.get(i);
				if(i==0)
				{
					left = rect.x;
					right = rect.x+rect.width;
					top = rect.y;
					bottom = rect.y + rect.height;
				}
				else
				{
					if(rect.x<left)
					{
						left = rect.x;
					}
					if((rect.x + rect.width)>right)
					{
						right = rect.x+rect.width;
					}
					if(rect.y<top)
					{
						top = rect.y;
					}
					if((rect.y + rect.height)>bottom)
					{
						bottom = rect.y + rect.height;
					}
				}
			}
			
			byte obstDir = getDir2(x,y,(left+right)/2,(bottom+top)/2);
			if(obstDir==DIR_UP)
			{
				double distBottomLeft = distanceUnSqr(x,y,bottom,left);
				double distBottomRight = distanceUnSqr(x,y,bottom,right);
				if(distBottomLeft<distBottomRight)
				{
					target = Vector2f(bottom,left);
				}
				else
				{
					target = Vector2f(bottom,right);
				}
			}
			else
			{
				double distTopLeft = distanceUnSqr(x,y,top,left);
				double distTopRight = distanceUnSqr(x,y,top,right);
				if(distTopLeft<distTopRight)
				{
					target = Vector2f(top,left);
				}
				else
				{
					target = Vector2f(top,right);
				}
			}
		}
		byte targetDir = getDir2(x,y,target.x,target.y);
		if(targetDir==DIR_UP)
		{
			if(target.x<x && (x-target.x)>=1)
			{
				moveLeft=1;
				moveRight=0;
				playerdir=LEFT;
			}
			else if(x<target.x && (target.x-x)>=1)
			{
				moveLeft=0;
				moveRight=1;
				playerdir=RIGHT;
			}
			else
			{
				moveLeft=0;
				moveRight=0;
			}
			if(yvelocity>=-2)
			{
				recoverJump();
			}
		}
		else if(targetDir==DIR_LEFT)
		{
			moveLeft=1;
			moveRight=0;
			playerdir=LEFT;
			if((target.y<(y+60)) && (xvelocity<=1 || (y-target.y)>60))
			{
				if(yvelocity>=-2)
				{
					recoverJump();
				}
			}
			else if(target.y>y+60)
			{
				if(CanDo())
				{
					double randNum = GameEngine::random()*100;
					if(randNum>90)
					{
						randomizer.doAttack(ATTACKTYPE_SIDEMOVE);
					}
				}
			}
		}
		else if(targetDir==DIR_RIGHT)
		{
			moveLeft=0;
			moveRight=1;
			playerdir=RIGHT;
			if((target.y<(y+60)) && (xvelocity>=1 || y-target.y>60))
			{
				if(yvelocity>=-2)
				{
					recoverJump();
				}
			}
			else if(target.y>y+60)
			{
				if(CanDo())
				{
					double randNum = GameEngine::random()*100;
					if(randNum>90)
					{
						randomizer.doAttack(ATTACKTYPE_SIDEMOVE);
					}
				}
			}
		}
		else if(targetDir==DIR_DOWN)
		{
			if(target.x<x && (x-target.x)>=1)
			{
				moveLeft=1;
				moveRight=0;
				playerdir=LEFT;
			}
			else if(x<target.x && (target.x-x)>=1)
			{
				moveLeft=0;
				moveRight=1;
				playerdir=RIGHT;
			}
			else
			{
				moveLeft=0;
				moveRight=0;
			}
			
			double targetDist = distanceUnSqr(x,y,target.x,target.y);
			if((targetDist>100 || yvelocity<=10)&&(abs(x - target.x)<10))
			{
				randomizer.doAttack(ATTACKTYPE_DOWNMOVE);
			}
		}
	}
	
	void Player::goInDirection(byte dir)
	{
		moveLeft = 0;
		moveRight = 0;
		down = false;
		up = false;
		upKey = false;
		
		switch(dir)
		{
			case DIR_UP:
			if(isObstacle(currentCollidePlatformActor[DIR_DOWN]))
			{
				switch(playerdir)
				{
					case LEFT:
					if(isObstacle(currentCollidePlatformActor[DIR_RIGHT]))
					{
						if(!isObstacle(currentCollidePlatformActor[DIR_LEFT]))
						{
							moveLeft = 0;
							moveRight = 1;
							playerdir = RIGHT;
						}
						else
						{
							moveLeft = 1;
							moveRight = 0;
							playerdir = LEFT;
						}
					}
					else
					{
						moveLeft = 1;
						moveRight = 0;
						playerdir = LEFT;
					}
					break;
					
					case RIGHT:
					if(isObstacle(currentCollidePlatformActor[DIR_LEFT]))
					{
						if(!isObstacle(currentCollidePlatformActor[DIR_RIGHT]))
						{
							moveLeft = 1;
							moveRight = 0;
							playerdir = LEFT;
						}
						else
						{
							moveLeft = 0;
							moveRight = 1;
							playerdir = RIGHT;
						}
					}
					else
					{
						moveLeft = 0;
						moveRight = 1;
						playerdir = RIGHT;
					}
					break;
				}
			}
			else
			{
				if(yvelocity>=0)
				{
					recoverJump();
				}
			}
			break;
			
			case DIR_UPLEFT:
			if(!isObstacle(currentCollidePlatformActor[DIR_DOWN]))
			{
				if(yvelocity>=0)
				{
					recoverJump();
				}
			}
			if(!isObstacle(currentCollidePlatformActor[DIR_RIGHT]))
			{
				moveLeft = 1;
				moveRight = 0;
				playerdir = LEFT;
			}
			break;
			
			case DIR_UPRIGHT:
			if(!isObstacle(currentCollidePlatformActor[DIR_DOWN]))
			{
				if(yvelocity>=0)
				{
					recoverJump();
				}
			}
			if(!isObstacle(currentCollidePlatformActor[DIR_LEFT]))
			{
				moveLeft = 0;
				moveRight = 1;
				playerdir = RIGHT;
			}
			break;
			
			case DIR_LEFT:
			if(!isObstacle(currentCollidePlatformActor[DIR_RIGHT]))
			{
				moveLeft = 1;
				moveRight = 0;
				playerdir = LEFT;
			}
			else
			{
				if(yvelocity>=0)
				{
					recoverJump();
				}
			}
			break;
			
			case DIR_RIGHT:
			if(!isObstacle(currentCollidePlatformActor[DIR_LEFT]))
			{
				moveLeft = 0;
				moveRight = 1;
				playerdir = RIGHT;
			}
			else
			{
				if(yvelocity>=0)
				{
					recoverJump();
				}
			}
			break;
			
			case DIR_DOWNLEFT:
			if(currentCollidePlatformActor[DIR_UP]!=null)
			{
				Platform*plat = currentCollidePlatformActor[DIR_UP];
				if(plat->getType() == Platform::TYPE_GOTHROUGH)
				{
					moveDown();
				}
				else
				{
					if(!isObstacle(currentCollidePlatformActor[DIR_RIGHT]))
					{
						moveLeft = 1;
						moveRight = 0;
						playerdir = LEFT;
					}
					else
					{
						if(yvelocity>=0)
						{
							recoverJump();
						}
					}
				}
			}
			else
			{
				if(!isObstacle(currentCollidePlatformActor[DIR_RIGHT]))
				{
					moveLeft = 1;
					moveRight = 0;
					playerdir = LEFT;
				}
			}
			break;
			
			case DIR_DOWNRIGHT:
			if(currentCollidePlatformActor[DIR_UP]!=null)
			{
				Platform*plat = currentCollidePlatformActor[DIR_UP];
				if(plat->getType() == Platform::TYPE_GOTHROUGH)
				{
					moveDown();
				}
				else
				{
					if(!isObstacle(currentCollidePlatformActor[DIR_LEFT]))
					{
						moveLeft = 0;
						moveRight = 1;
						playerdir = RIGHT;
					}
					else
					{
						if(yvelocity>=0)
						{
							recoverJump();
						}
					}
				}
			}
			else
			{
				if(!isObstacle(currentCollidePlatformActor[DIR_LEFT]))
				{
					moveLeft = 0;
					moveRight = 1;
					playerdir = RIGHT;
				}
			}
			break;
			
			case DIR_DOWN:
			if(currentCollidePlatformActor[DIR_UP]!=null)
			{
				Platform*plat = currentCollidePlatformActor[DIR_UP];
				if(plat->getType() == Platform::TYPE_GOTHROUGH)
				{
					moveDown();
				}
				else
				{
					switch(playerdir)
					{
						case LEFT:
						if(!isObstacle(currentCollidePlatformActor[DIR_RIGHT]))
						{
							moveLeft = 1;
							moveRight = 0;
							playerdir = LEFT;
						}
						else
						{
							moveLeft = 0;
							moveRight = 1;
							playerdir = RIGHT;
						}
						break;
						
						case RIGHT:
						if(!isObstacle(currentCollidePlatformActor[DIR_LEFT]))
						{
							moveLeft = 0;
							moveRight = 1;
							playerdir = RIGHT;
						}
						else
						{
							moveLeft = 1;
							moveRight = 0;
							playerdir = LEFT;
						}
						break;
					}
				}
			}
			break;
		}
	}
	
	boolean Player::checkObstacleDir(RectangleF obst, byte dir)
	{
		byte obstDir1 = getDir2(x,y,obst.x,obst.y);
		byte obstDir2 = getDir2(x, y, obst.x + obst.width, obst.y + obst.height);
		if(checkDirRelation(dir,obstDir1, obstDir2))
		{
			return true;
		}
		return false;
	}
	
	boolean Player::checkDirSemicircle(byte dir, byte dirCmp)
	{
		ArrayList<byte> dirs = ArrayList<byte>();
		dirs.add(dir);
		byte newDir = (byte)(dir-1);
		if(newDir<1)
		{
			newDir = 8;
		}
		dirs.add(newDir);
		newDir--;
		if(newDir<1)
		{
			newDir = 8;
		}
		dirs.add(newDir);
		newDir = (byte)(dir+1);
		if(newDir>8)
		{
			newDir = 1;
		}
		dirs.add(newDir);
		newDir--;
		if(newDir>8)
		{
			newDir = 1;
		}
		dirs.add(newDir);
		
		for(int i=0; i<dirs.size(); i++)
		{
			byte checkDir = dirs.get(i);
			if(checkDir==dirCmp)
			{
				return true;
			}
		}
		return false;
	}
	
	boolean Player::checkDirRelation(byte dir, byte cmp1, byte cmp2)
	{
		if(cmp2>cmp1)
		{
			if(dir>cmp1 && dir<cmp2)
			{
				return true;
			}
			return false;
		}
		else if(cmp1>cmp2)
		{
			if(dir>cmp1 || dir<cmp2)
			{
				return true;
			}
			return false;
		}
		else
		{
			if(dir==cmp1)
			{
				return true;
			}
		}
		return false;
	}
	
	double Player::getClosestDistanceUnSqr(Vector2f self, Rectangle rect)
	{
		float left = (float)rect.x - (float)rect.width/2;
		float right = (float)rect.x + (float)rect.width/2;
		float top = (float)rect.y - (float)rect.height/2;
		float bottom = (float)rect.y + (float)rect.height/2;
		
		if(self.x < left)
		{
			if(self.y > bottom)
			{
				return distanceUnSqr(self.x, self.y, left, bottom);
			}
			else if(self.y < top)
			{
				float middleY = (bottom - rect.height/2);
				if(self.y > middleY)
				{
					return distanceUnSqr(self.x, self.y, left, middleY);
				}
				else
				{
					return distanceUnSqr(self.x, self.y, left, top);
				}
			}
			else
			{
				return distanceUnSqr(self.x, self.y, left, top);
			}
		}
		else if(self.x > right)
		{
			if(self.y > bottom)
			{
				return distanceUnSqr(self.x, self.y, right, bottom);
			}
			else if(self.y < top)
			{
				float middleY = (bottom - rect.height/2);
				if(self.y > middleY)
				{
					return distanceUnSqr(self.x, self.y, right, middleY);
				}
				else
				{
					return distanceUnSqr(self.x, self.y, right, top);
				}
			}
			else
			{
				return distanceUnSqr(self.x, self.y, right, top);
			}
		}
		else //self is in between left and right
		{
			if(self.y > bottom)
			{
				float leftDist = self.x - left;
				float rightDist = right - self.x;
				if(leftDist<rightDist)
				{
					return distanceUnSqr(self.x, self.y, left, bottom);
				}
				else
				{
					return distanceUnSqr(self.x, self.y, right, bottom);
				}
			}
			else
			{
				return distanceUnSqr(self.x, self.y, (float)rect.x + (float)rect.width/2, (float)rect.y + (float)rect.height/2);
			}
		}
	}
	
	Vector2f Player::getClosestPoint(Rectangle rect, byte dir)
	{
		float left = (float)rect.x - (float)rect.width/2;
		float right = (float)rect.x + (float)rect.width/2;
		float top = (float)rect.y - (float)rect.height/2;
		float bottom = (float)rect.y + (float)rect.height/2;
		float middleY = top + rect.height/2;
		
		switch(dir)
		{
			case DIR_UP:
			case DIR_UPLEFT:
			case DIR_UPRIGHT:
			if(y>middleY)
			{
				if(x<left)
				{
					if(dir==DIR_UPLEFT)
					{
						return Vector2f(left, middleY);
					}
					return Vector2f(left, top);
				}
				else if(x>right)
				{
					if(dir==DIR_UPRIGHT)
					{
						return Vector2f(right, middleY);
					}
					return Vector2f(right, top);
				}
				else
				{
					if(dir==DIR_UPRIGHT || (dir==DIR_UP && playerdir==RIGHT))
					{
						return Vector2f(right, bottom);
					}
					else if(dir==DIR_UPLEFT || (dir==DIR_UP && playerdir==LEFT))
					{
						return Vector2f(left, bottom);
					}
					return Vector2f((float)rect.x + (float)rect.width/2, bottom);
				}
			}
			else
			{
				if(x<left)
				{
					return Vector2f(left, top);
				}
				else if(x>right)
				{
					return Vector2f(right, top);
				}
				else
				{
					if(dir == DIR_UPRIGHT)
					{
						return Vector2f(right, top);
					}
					else if(dir == DIR_UPLEFT)
					{
						return Vector2f(left, top);
					}
					return Vector2f((float)rect.x + (float)rect.width/2, top);
				}
			}
			
			case DIR_LEFT:
			if(y>middleY)
			{
				if(x<left)
				{
					return Vector2f(left, top);
				}
				else if(x>right)
				{
					return Vector2f(right, top);
				}
				return Vector2f(left, bottom);
			}
			else
			{
				if(x<left)
				{
					return Vector2f(left, top);
				}
				else if(x>right)
				{
					return Vector2f(right, top);
				}
				return Vector2f(left, middleY);
			}
			
			case DIR_RIGHT:
			if(y>middleY)
			{
				if(x<left)
				{
					return Vector2f(left, top);
				}
				else if(x>right)
				{
					return Vector2f(right, top);
				}
				return Vector2f(right, bottom);
			}
			else
			{
				if(x<left)
				{
					return Vector2f(left, top);
				}
				else if(x>right)
				{
					return Vector2f(right, top);
				}
				return Vector2f(right, middleY);
			}
			
			case DIR_DOWNLEFT:
			case DIR_DOWNRIGHT:
			case DIR_DOWN:
			if(y<middleY)
			{
				if(x<left)
				{
					return Vector2f(left, bottom);
				}
				else if(x>right)
				{
					return Vector2f(right, bottom);
				}
				else
				{
					if(dir==DIR_DOWNLEFT || (dir==DIR_DOWN && playerdir==LEFT))
					{
						return Vector2f(left, middleY);
					}
					else if(dir==DIR_DOWNRIGHT || (dir==DIR_DOWN && playerdir==RIGHT))
					{
						return Vector2f(right, middleY);
					}
					return Vector2f((float)rect.x + (float)rect.width/2, middleY);
				}
			}
			else if(y<bottom)
			{
				if(x<left)
				{
					return Vector2f(left, bottom);
				}
				else if(x>right)
				{
					return Vector2f(right, bottom);
				}
				else
				{
					if(dir==DIR_DOWNLEFT || (dir==DIR_DOWN && playerdir==LEFT))
					{
						return Vector2f(left, bottom);
					}
					else if(dir==DIR_DOWNRIGHT || (dir==DIR_DOWN && playerdir==RIGHT))
					{
						return Vector2f(right, bottom);
					}
					return Vector2f((float)rect.x + (float)rect.width/2, bottom);
				}
			}
			return Vector2f(x,y);
		}
		return Vector2f(x,y);
	}
	
	//true means plat goes x way, false means y
	boolean Player::getDirSeparating(Vector2f target, Rectangle rect)
	{
		int left = (int)hitbox->x;
		int right = (int)(hitbox->x + hitbox->width);
		float middlePlatY = (float)rect.y + (float)rect.height/2;
		if((target.y < middlePlatY && middlePlatY < y)||(target.y > middlePlatY && middlePlatY > y))
		{
			if(right<rect.x)
			{
				if(target.x > rect.x)
				{
					return true;
				}
			}
			else if(left>(rect.x + rect.width))
			{
				if(target.x < (rect.x + rect.width))
				{
					return true;
				}
			}
			else
			{
				return true;
			}
		}
		else if((target.y > rect.y && target.y < (rect.y + rect.height))||(y > rect.y && y < (rect.y + rect.height)))
		{
			if(x<=rect.x && target.x>=(rect.x+rect.width))
			{
				return false;
			}
			else if(x>=(rect.x+rect.width) && target.x<=rect.x)
			{
				return false;
			}
		}
		return true;
	}
	
	Rectangle Player::getRectSeparating(Vector2f target)
	{
		int left = (int)hitbox->x;
		int right = (int)(hitbox->x + hitbox->width);
		
		Rectangle separatingRect = Rectangle(-1,-1,-1,-1);
		boolean hasRect = false;
		float currentDist = 0;
		
		for(int i=0; i<Global::currentStage->platforms.size(); i++)
		{
			Platform*plat = Global::currentStage->platforms.get(i);
			if(isObstacle(plat))
			{
				Rectangle platRect;
				if(plat->getCollideType()==Platform::COLLIDE_SOLID)
				{
					platRect = Rectangle((int)(plat->x-plat->width/2),(int)(plat->y-plat->height),plat->width,plat->height);
				}
				else
				{
					platRect = Rectangle((int)plat->x,(int)plat->y,plat->width,plat->height);
				}
				
				if(!hasRect)
				{
					float middlePlatY = (float)platRect.y + (float)platRect.height/2;
					if((target.y < middlePlatY && middlePlatY < y)||(target.y > middlePlatY && middlePlatY > y))
					{
						if(right<platRect.x)
						{
							if(target.x > platRect.x)
							{
								separatingRect = platRect;
								currentDist = (float)platRect.x - (float)right;
							}
						}
						else if(left>(platRect.x + platRect.width))
						{
							if(target.x < (platRect.x + platRect.width))
							{
								separatingRect = platRect;
								currentDist = (float)left - ((float)platRect.x + (float)platRect.width);
							}
						}
						else
						{
							separatingRect = platRect;
							currentDist = abs(y - middlePlatY);
						}
					}
					else if((target.y > platRect.y && target.y < (platRect.y + platRect.height))||(y > platRect.y && y < (platRect.y + platRect.height)))
					{
						if(x<=platRect.x && target.x>=(platRect.x+platRect.width))
						{
							separatingRect = platRect;
							currentDist = platRect.x - x;
						}
						else if(x>=(platRect.x+platRect.width) && target.x<=platRect.x)
						{
							separatingRect = platRect;
							currentDist = x - (platRect.x+platRect.width);
						}
					}
				}
				else
				{
					float middlePlatY = (float)platRect.y + (float)platRect.height/2;
					if((target.y < middlePlatY && middlePlatY < y)||(target.y > middlePlatY && middlePlatY > y))
					{
						if(right<platRect.x)
						{
							if(target.x > platRect.x)
							{
								float newDist = (float)platRect.x - (float)right;
								if(newDist < currentDist)
								{
									separatingRect = platRect;
									currentDist = newDist;
								}
							}
						}
						else if(left>(platRect.x + platRect.width))
						{
							if(target.x < (platRect.x + platRect.width))
							{
								float newDist = (float)left - ((float)platRect.x + (float)platRect.width);
								if(newDist < currentDist)
								{
									separatingRect = platRect;
									currentDist = newDist;
								}
							}
						}
						else
						{
							float newDist = abs(y - middlePlatY);
							if(newDist < currentDist)
							{
								separatingRect = platRect;
								currentDist = newDist;
							}
						}
					}
					else if((target.y > platRect.y && target.y < (platRect.y + platRect.height))||(y > platRect.y && y < (platRect.y + platRect.height)))
					{
						if(x<=platRect.x && target.x>=(platRect.x+platRect.width))
						{
							float newDist = platRect.x - x;
							if(newDist < currentDist)
							{
								separatingRect = platRect;
								currentDist = newDist;
							}
						}
						else if(x>=(platRect.x+platRect.width) && target.x<=platRect.x)
						{
							float newDist = x - (platRect.x+platRect.width);
							if(newDist < currentDist)
							{
								separatingRect = platRect;
								currentDist = newDist;
							}
						}
					}
				}
			}
		}
		
		for(int i=0; i<ProjectileManager::projectiles.size(); i++)
		{
			Projectile*proj = ProjectileManager::projectiles.get(i);
			Rectangle rect = Rectangle((int)(proj->x-(proj->width/2)),(int)(proj->y-(proj->height/2)),proj->width,proj->height);
			
			if(proj->getPlayerNo()!=playerNo || (Global::teamBattle && proj->getTeam()!=team))
			{
				if(!hasRect)
				{
					float middlePlatY = (float)rect.y + (float)rect.height/2;
					if((target.y < middlePlatY && middlePlatY < y)||(target.y > middlePlatY && middlePlatY > y))
					{
						if(right<rect.x)
						{
							if(target.x > rect.x)
							{
								separatingRect = rect;
								currentDist = (float)rect.x - (float)right;
							}
						}
						else if(left>(rect.x + rect.width))
						{
							if(target.x < ((float)rect.x + (float)rect.width))
							{
								separatingRect = rect;
								currentDist = (float)left - ((float)rect.x + (float)rect.width);
							}
						}
						else
						{
							separatingRect = rect;
							currentDist = abs(y - middlePlatY);
						}
					}
					else if((target.y > rect.y && target.y < (rect.y + rect.height))||(y > rect.y && y < (rect.y + rect.height)))
					{
						if(x<=rect.x && target.x>=(rect.x+rect.width))
						{
							separatingRect = rect;
							currentDist = rect.x - x;
						}
						else if(x>=(rect.x+rect.width) && target.x<=rect.x)
						{
							separatingRect = rect;
							currentDist = x - (rect.x+rect.width);
						}
					}
				}
				else
				{
					float middlePlatY = (float)rect.y + (float)rect.height/2;
					if((target.y < middlePlatY && middlePlatY < y)||(target.y > middlePlatY && middlePlatY > y))
					{
						if(right<rect.x)
						{
							if(target.x > rect.x)
							{
								float newDist = (float)rect.x - (float)right;
								if(newDist < currentDist)
								{
									separatingRect = rect;
									currentDist = newDist;
								}
							}
						}
						else if(left>(rect.x + rect.width))
						{
							if(target.x < (rect.x + rect.width))
							{
								float newDist = (float)left - ((float)rect.x + (float)rect.width);
								if(newDist < currentDist)
								{
									separatingRect = rect;
									currentDist = newDist;
								}
							}
						}
						else
						{
							float newDist = abs(y - middlePlatY);
							if(newDist < currentDist)
							{
								separatingRect = rect;
								currentDist = newDist;
							}
						}
					}
					else if((target.y > rect.y && target.y < (rect.y + rect.height))||(y > rect.y && y < (rect.y + rect.height)))
					{
						if(x<=rect.x && target.x>=(rect.x+rect.width))
						{
							float newDist = rect.x - x;
							if(newDist < currentDist)
							{
								separatingRect = rect;
								currentDist = newDist;
							}
						}
						else if(x>=(rect.x+rect.width) && target.x<=rect.x)
						{
							float newDist = x - (rect.x+rect.width);
							if(newDist < currentDist)
							{
								separatingRect = rect;
								currentDist = newDist;
							}
						}
					}
				}
			}
		}
		return separatingRect;
	}
	
	void Player::followEnemy(boolean canAttack, int level)
	{
		currentEnemy->updateHitbox();
		Vector2f enemyVect = Vector2f(currentEnemy->x, currentEnemy->y);
		byte hitboxDir = getDir(hitbox,currentEnemy->hitbox);
		double closeDist = 20;
		switch(hitboxDir)
		{
			case DIR_UP:
			case DIR_DOWN:
			closeDist = hitbox->height/2 + currentEnemy->hitbox->height/2 + 4;
			break;
			
			case DIR_LEFT:
			case DIR_RIGHT:
			closeDist = hitbox->width/2 + currentEnemy->hitbox->width/2 + 4;
			break;
		}
		closeDist = closeDist*closeDist;
		
		byte enemyDir = getDir(x,y,currentEnemy->x,currentEnemy->y);
		
		Rectangle separatingRect = getRectSeparating(enemyVect);
		if(separatingRect.x==-1)
		{
			goInDirection(enemyDir);
		}
		else
		{
			boolean dirSeparating = getDirSeparating(enemyVect,separatingRect);
			if(dirSeparating)
			{
				if(y>enemyVect.y)
				{
					if(checkTrappedUnder(separatingRect))
					{
						switch(playerdir)
						{
							case LEFT:
							goInDirection(DIR_LEFT);
							break;
							
							case RIGHT:
							goInDirection(DIR_RIGHT);
							break;
						}
					}
					else
					{
						goInDirection(DIR_UP);
						if(moveLeft==0 && moveRight==0)
						{
							if(enemyVect.x < x)
							{
								playerdir = LEFT;
							}
							else if(enemyVect.x > x)
							{
								playerdir = RIGHT;
							}
						}
					}
				}
				else
				{
					if(checkTrappedOver(separatingRect) || isObstacle(currentCollidePlatformActor[DIR_UP]))
					{
						switch(playerdir)
						{
							case LEFT:
							goInDirection(DIR_LEFT);
							break;
							
							case RIGHT:
							goInDirection(DIR_RIGHT);
							break;
						}
					}
					else
					{
						goInDirection(DIR_DOWN);
						if(enemyVect.x < x)
						{
							playerdir = LEFT;
						}
						else if(enemyVect.x > x)
						{
							playerdir = RIGHT;
						}
					}
				}
			}
			else
			{
				if(separatingRect.y <= y)
				{
					if(getClosestDistanceUnSqr(Vector2f(x,y),separatingRect)<=1000)
					{
						if(enemyVect.x < x)
						{
							goInDirection(DIR_UPLEFT);
						}
						else
						{
							goInDirection(DIR_UPRIGHT);
						}
					}
					else
					{
						if(enemyVect.x < x)
						{
							goInDirection(DIR_LEFT);
						}
						else
						{
							goInDirection(DIR_RIGHT);
						}
					}
				}
				else
				{
					if(enemyVect.x < x)
					{
						goInDirection(DIR_LEFT);
					}
					else
					{
						goInDirection(DIR_RIGHT);
					}
				}
			}
		}
	}
	
	boolean Player::checkEnemyHang()
	{
		for(int i=0; i<=Global::possPlayers; i++) //TODO: loop characters
		{
			Player*playr = Global::characters[i];
			
			if(playr!=null)
			{
				switch(playerdir)
				{
					case LEFT:
					if(playr->x<x && playr->y<=y && (y-playr->y)<60 && (x-playr->x)<60)
					{
						return true;
					}
					return false;
					
					case RIGHT:
					if(playr->x>x && playr->y<=y && (y-playr->y)<60 && (playr->x-x)<60)
					{
						return true;
					}
					return false;
				}
			}
		}
		return false;
	}
	
	boolean Player::recover(int level)
	{
		boolean canFollow = Global::currentStage->checkSafeArea(this);
		if(!canFollow && !hanging)
		{
			Vector2f target = findRecoveryTarget();
			
			getToRecoveryTarget(target);
			
			return true;
		}
		else if(hanging)
		{
			if(checkEnemyHang())
			{
				climbUpAttack();
			}
			else
			{
				climbUp();
			}
		}
		/*else if(onGround && CanDo())
		{
			moveLeft=0;
			moveRight=0;
			animFinish();
		}*/
		return false;
	}
	
	void Player::stopAI(int level)
	{
		boolean needToRecover = recover(level);
		if(!needToRecover)
		{
			if(onGround)
			{
				moveLeft = 0;
				moveRight = 0;
				down = false;
				up = false;
			}
		}
	}
	
	void Player::walkAI(int level)
	{
		boolean needToRecover = recover(level);
		if(!needToRecover)
		{
			if(onGround)
			{
				Platform*plat = currentCollidePlatformActor[DIR_UP];
				boolean leftSide = false;
				if(currentCollidePlatformActor[DIR_RIGHT]!=null && currentCollidePlatformActor[DIR_RIGHT]!=currentCollidePlatformActor[DIR_UP])
				{
					leftSide = true;
				}
				boolean rightSide = false;
				if(currentCollidePlatformActor[DIR_LEFT]!=null && currentCollidePlatformActor[DIR_LEFT]!=currentCollidePlatformActor[DIR_UP])
				{
					rightSide = true;
				}
				if(plat!=null)
				{
					Rectangle platRect;
					if(plat->getCollideType() == Platform::COLLIDE_BOX)
					{
						platRect = Rectangle((int)plat->x,(int)plat->y,plat->width,plat->height);
					}
					else
					{
						platRect = Rectangle((int)(plat->x-plat->width/2),(int)(plat->y-plat->height/2),plat->width,plat->height);
					}
					
					float leftX = (x - hitbox->width/2);
					float rightX = (x + hitbox->width/2);
					
					if(leftX<=platRect.x || leftSide)
					{
						playerdir = RIGHT;
						moveLeft = 0;
						moveRight = 1;
					}
					else if(rightX>=(platRect.x+platRect.width) || rightSide)
					{
						playerdir = LEFT;
						moveLeft = 1;
						moveRight = 0;
					}
				}
			}
			if(moveLeft==0 && moveRight==0)
			{
				switch(playerdir)
				{
					case LEFT:
					moveLeft = 1;
					break;
					
					case RIGHT:
					moveRight = 1;
					break;
				}
			}
		}
	}
	
	void Player::runAI(int level)
	{
		boolean needToRecover = recover(level);
		if(!needToRecover)
		{
			if(onGround)
			{
				Platform*plat = currentCollidePlatformActor[DIR_UP];
				boolean leftSide = false;
				if(currentCollidePlatformActor[DIR_RIGHT]!=null && currentCollidePlatformActor[DIR_RIGHT]!=currentCollidePlatformActor[DIR_UP])
				{
					leftSide = true;
				}
				boolean rightSide = false;
				if(currentCollidePlatformActor[DIR_LEFT]!=null && currentCollidePlatformActor[DIR_LEFT]!=currentCollidePlatformActor[DIR_UP])
				{
					rightSide = true;
				}
				if(plat!=null)
				{
					Rectangle platRect;
					if(plat->getCollideType() == Platform::COLLIDE_BOX)
					{
						platRect = Rectangle((int)plat->x,(int)plat->y,plat->width,plat->height);
					}
					else
					{
						platRect = Rectangle((int)(plat->x-plat->width/2),(int)(plat->y-plat->height/2),plat->width,plat->height);
					}
					
					float leftX = (x - hitbox->width/2);
					float rightX = (x + hitbox->width/2);
					
					if(leftX<=platRect.x || leftSide)
					{
						if(moveLeft>0)
						{
							playerdir = RIGHT;
							moveLeft = 0;
							moveRight = 2;
						}
					}
					else if(rightX>=(platRect.x+platRect.width) || rightSide)
					{
						if(moveRight>0)
						{
							playerdir = LEFT;
							moveLeft = 2;
							moveRight = 0;
						}
					}
				}
			}
			if(moveLeft==0 && moveRight==0)
			{
				switch(playerdir)
				{
					case LEFT:
					moveLeft = 2;
					break;
					
					case RIGHT:
					moveRight = 2;
					break;
				}
			}
		}
	}
	
	void Player::jumpAI(int level)
	{
		boolean needToRecover = recover(level);
		if(!needToRecover)
		{
			if(yvelocity>=0)
			{
				recoverJump();
			}
		}
	}
	
	void Player::followAI(int level)
	{
		moveLeft = 0;
		moveRight = 0;
		down = false;
		up = false;
		upKey = false;
		
		boolean needToRecover = recover(level);
		if(!needToRecover)
		{
			updateCPUTarget();
			
			if(currentEnemy!=null)
			{
				/*double enemyDist = distanceUnSqr(x, y, currentEnemy->x, currentEnemy->y);
				if(enemyDist>3600) //60
					goInDirection(enemyDir);*/
				updateHitbox();
				currentEnemy->updateHitbox();
				byte hitboxDir = getDir(hitbox,currentEnemy->hitbox);
				double enemyDist = distanceUnSqr(hitbox->x+hitbox->width/2, hitbox->y+hitbox->height/2,currentEnemy->hitbox->x+currentEnemy->hitbox->width/2,currentEnemy->hitbox->y+currentEnemy->hitbox->height/2);
				double closeDist = 20;
				switch(hitboxDir)
				{
					case DIR_UP:
					case DIR_DOWN:
					closeDist = hitbox->height/2 + currentEnemy->hitbox->height/2 + 4;
					break;
					
					case DIR_LEFT:
					case DIR_RIGHT:
					closeDist = hitbox->width/2 + currentEnemy->hitbox->width/2 + 4;
					break;
				}
				closeDist = closeDist*closeDist;
				
				if(enemyDist>closeDist)
				{
					//perform melee attacks
					followEnemy(false, level);
				}
			}
		}
	}
	
	void Player::normalAI(int level)
	{
		moveLeft = 0;
		moveRight = 0;
		down = false;
		up = false;
		upKey = false;
		
		boolean needToRecover = recover(level);
		if(!needToRecover)
		{
			updateCPUTarget();
			
			if(currentEnemy!=null)
			{
				/*double enemyDist = distanceUnSqr(x, y, currentEnemy->x, currentEnemy->y);
				if(enemyDist>3600) //60
					goInDirection(enemyDir);*/
				updateHitbox();
				currentEnemy->updateHitbox();
				byte hitboxDir = getDir(hitbox,currentEnemy->hitbox);
				double enemyDist = distanceUnSqr(hitbox->x+hitbox->width/2, hitbox->y+hitbox->height/2,currentEnemy->hitbox->x+currentEnemy->hitbox->width/2,currentEnemy->hitbox->y+currentEnemy->hitbox->height/2);
				double closeDist = 20;
				switch(hitboxDir)
				{
					case DIR_UP:
					case DIR_DOWN:
					closeDist = hitbox->height/2 + currentEnemy->hitbox->height/2 + 8;
					break;
					
					case DIR_LEFT:
					case DIR_RIGHT:
					closeDist = hitbox->width/2 + currentEnemy->hitbox->width/2 + 8;
					break;
				}
				closeDist = closeDist*closeDist;
				
				if(enemyDist<=closeDist)
				{
					//perform melee attacks
					double randWait = GameEngine::random()*20;
					double levelCompare = (double)level;
					if(randWait<levelCompare)
					{
						boolean charging = randomizer.doChargingAttack();
						if(!charging)
						{
							if(CanDo())
							{
								switch(hitboxDir)
								{
									case DIR_LEFT:
									case DIR_RIGHT:
									{
										boolean enemyFacing = false;
										if(currentEnemy->x<x)
										{
											playerdir = LEFT;
											if(currentEnemy->playerdir==RIGHT)
											{
												enemyFacing = true;
											}
										}
										else if(currentEnemy->x>x)
										{
											playerdir = RIGHT;
											if(currentEnemy->playerdir==LEFT)
											{
												enemyFacing = true;
											}
										}
										
										if(currentEnemy->attacksPriority>0 && enemyFacing)
										{
											double choice = GameEngine::random()*100;
											if(choice>=75)
											{
												randomizer.doAttack(ATTACKTYPE_STRONGMELEE);
											}
											else if(choice>68)
											{
												randomizer.doAttack(ATTACKTYPE_PROJECTILE);
											}
										}
										else
										{
											randomizer.doAttack(ATTACKTYPE_MELEE);
										}
									}
									break;
									
									case DIR_UP:
									randomizer.doAttack(ATTACKTYPE_UPMELEE);
									break;
									
									case DIR_DOWN:
									randomizer.doAttack(ATTACKTYPE_DOWNMELEE);
									break;
								}
							}
						}
					}
				}
				else
				{
					followEnemy(true, level);
				}
			}
		}
	}
	
	void Player::cpuAI(byte type, int level)
	{
		switch(type)
		{
			case AI_NORMAL:
			normalAI(level);
			break;
			
			case AI_STOP:
			stopAI(level);
			break;
			
			case AI_WALK:
			walkAI(level);
			break;
			
			case AI_RUN:
			runAI(level);
			break;
			
			case AI_JUMP:
			jumpAI(level);
			break;
			
			case AI_FOLLOW:
			followAI(level);
			break;
		}
	}
	
	void Player::Update(long gameTime)
	{
		if(firstUpdate)
		{
			changeAnimation(getAnimName(), getAnimation()->getDirection());
		}
		/*if(playerNo==2 && currentCollidePlatformActor[DIR_UP]!=null)
		{
			Console::WriteLine("" + (currentCollidePlatformActor[DIR_UP].x + currentCollidePlatformActor[DIR_UP].width/2) + ", " + (x + hitbox->width/2));
		}*/
		//updateBooleanGrid();
		GameElement::Update(gameTime);
		groundCheck = false;
		collideQueue.clear();
		
		groundCollidedFrame = false;
		if(chargebar!=null)
		{
			if(chargebar->inactive)
			{
				delete chargebar;
				chargebar = null;
			}
			else
			{
				chargebar->Update(gameTime);
			}
		}
		if(itemHolding!=null)
		{
			itemHolding->Update(gameTime);
			if(itemHolding->dead)
			{
				itemHolding->destroy();
	        	itemHolding->onDestroy();
	        	Console::WriteLine((String)"Destroyed Item " + Global::getItemName(itemHolding->itemNo));
	        	delete itemHolding;
	        	itemHolding = null;
			}
		}
		if(itemWearing!=null)
		{
			itemWearing->Update(gameTime);
			if(itemWearing->dead)
			{
				itemWearing->destroy();
	        	itemWearing->onDestroy();
	        	Console::WriteLine((String)"Destroyed Item " + Global::getItemName(itemWearing->itemNo));
	        	delete itemWearing;
	        	itemWearing = null;
			}
		}
		if(itemHatting!=null)
		{
			itemHatting->Update(gameTime);
			if(itemHatting->dead)
			{
				itemHatting->destroy();
	        	itemHatting->onDestroy();
	        	Console::WriteLine((String)"Destroyed Item " + Global::getItemName(itemHatting->itemNo));
	        	delete itemHatting;
	        	itemHatting = null;
			}
		}
		if(itemWielding!=null)
		{
			itemWielding->Update(gameTime);
			if(itemWielding->dead)
			{
				itemWielding->destroy();
	        	itemWielding->onDestroy();
	        	Console::WriteLine((String)"Destroyed Item " + Global::getItemName(itemWielding->itemNo));
	        	delete itemWielding;
	        	itemWielding = null;
			}
		}
		if(alive)
		{
			if(yVel!=0)
			{
				y+=yVel;
				yvelocity=0;
			}
			if(xVel!=0)
			{
				x += xVel;
				xvelocity=0;
			}
			updateHitbox();
			hitbox->Update(gameTime);
			indicator->Update(gameTime);
			if(!firstUpdate)
			{
				for(int i=0; i<=Global::possPlayers; i++) //TODO: loop characters
				{
					if(Global::characters[i]!=null && i!=playerNo)
					{
						checkPlayerCollision(Global::characters[i]);
					}
				}
				
				String animname = getAnimName();
				
				if(animname.equals("stand_left") && !onGround)
				{
					changeAnimation("fall_left",NO_CHANGE);
				}
				else if(animname.equals("stand_right") && !onGround)
				{
					changeAnimation("fall_right",NO_CHANGE);
				}
			}
			updateHitbox();
		}
		else
		{
			x = -10000;
			y = -10000;
		}
		offScreenExplosion->Update(gameTime);
		firstUpdate = false;
	}
	
	void Player::updateGravity()
	{
		if(!grabbed && !hanging)
	    {
	        yvelocity+=(float)(Global::currentStage->getGravity()+weight);
	    }
	}
	
	void Player::updateFrame()
	{
	    if(hurtFrame>0)
	    {
	        Actor::setColor(Color::RED);
	        hurtFrame-=1;
	    }
	    else if(chargeSmash>0)
	    {
	    	Actor::setColor(Color::YELLOW);
	    }
	    else
	    {
	        Actor::setColor(playerColor);
	        hurtFrame=0;
	    }
	}
	
	void Player::updateMovement()
	{
		//(int flyD, float recS, float waterS, float fallS, float moveS,
        //        int flyRD,float recRS,float waterRS,float fallRS,float moveRS)
		if((CanDo())&&(chargeSmash==0)&&(!chargingAttack))
		{
			if(moveRight>0)
			{
				switch(moveRight)
			    {
			        case 1:
			        if(moveTime<=Game::getGameTime())
			        {
			            moveTime=Game::getGameTime()+flyTime;
			            if(!onGround)
			            {
			            	xvelocity=xvelocity*(recoverAmount);
			            }
			        }
			        hurt=0;
			        playerdir=2;
			        if(!onGround)
			        {
			            /*if(inWater==1)
			            {
			                x+=waterS;
			                if(jumping==0)
			                {
			                    changeAnimation("Event Actor", "walk_right", NO_CHANGE);
			                }
			            }
			            else
			            {*/
			        	if(jumping)
		                {
		                	x+=(fallWalk+jumpXBoost);
		                }
		                else
		                {
		                	x+=fallWalk;
		                }
			            //}
			        }
			 
			        else
			        {
			            if(canDo)
			            {
			                if(!jumping)
			                {
			                    changeAnimation("walk_right", NO_CHANGE);
			                }
			                x+=walkSpeed;
			            }
			        }
			        break;
			 
			        case 2:
			        if(moveTime<=Game::getGameTime())
			        {
			            moveTime=Game::getGameTime()+flyRunTime;
			            if(!onGround)
			            {
			            	xvelocity=xvelocity*(recoverRunAmount);
			            }
			        }
			        hurt=0;
			        playerdir=2;
			        if(!onGround)
			        {
			            /*if(inWater==1)
			            {
			                x+=waterRS;
			                if(jumping==0)
			                {
			                    changeAnimation("Event Actor", "walk_right", NO_CHANGE);
			                }
			            }
			            else
			            {*/
			        	if(jumping)
		                {
		                	x+=(fallRun+jumpXBoost);
		                }
		                else
		                {
		                	x+=fallRun;
		                }
			            //}
			        }
			 
			        else
			        {
			            if(canDo)
			            {
			                if(!jumping)
			                {
			                    changeAnimation("run_right", NO_CHANGE);
			                }
			                x+=runSpeed;
			            }
			        }
			        break;
			    }
			}
			
			else if(moveLeft>0)
			{
				switch(moveLeft)
			    {
			        case 1:
			        if(moveTime<=Game::getGameTime())
			        {
			            moveTime=Game::getGameTime()+flyTime;
			            if(!onGround)
			            {
			            	xvelocity=xvelocity*(recoverAmount);
			            }
			        }
			        hurt=0;
			        playerdir=1;
			        if(!onGround)
			        {
			            /*if(inWater==1)
			            {
			                x-=waterS;
			                if(jumping==0)
			                {
			                    changeAnimation("Event Actor", "walk_left", NO_CHANGE);
			                }
			            }
			            else
			            {*/
			        	if(jumping)
		                {
		                	x-=(fallWalk+jumpXBoost);
		                }
		                else
		                {
		                	x-=fallWalk;
		                }
			            //}
			        }
			 
			        else
			        {
			            if(canDo)
			            {
			                if(!jumping)
			                {
			                    changeAnimation("walk_left", NO_CHANGE);
			                }
			                x-=walkSpeed;
			            }
			        }
			        break;
			 
			        case 2:
			        if(moveTime<=Game::getGameTime())
			        {
			            moveTime=Game::getGameTime()+flyRunTime;
			            if(!onGround)
			            {
			            	xvelocity=xvelocity*(recoverRunAmount);
			            }
			        }
			        hurt=0;
			        playerdir=1;
			        if(!onGround)
			        {
			            /*if(inWater==1)
			            {
			                x-=waterRS;
			                if(jumping==0)
			                {
			                    changeAnimation("Event Actor", "walk_left", NO_CHANGE);
			                }
			            }
			            else
			            {*/
			        	if(jumping)
		                {
		                	x-=(fallRun+jumpXBoost);
		                }
		                else
		                {
		                	x-=fallRun;
		                }
			            //}
			        }
			 
			        else
			        {
			            if(canDo)
			            {
			                if(!jumping)
			                {
			                    changeAnimation("run_left", NO_CHANGE);
			                }
			                x-=runSpeed;
			            }
			        }
			        break;
			    }
			}
			else
			{
				String animName = getAnimName();
				if(animName.equals("walk_left") || animName.equals("walk_right") || animName.equals("run_left") || animName.equals("run_right"))
				{
					animFinish();
				}
			}
		}
	}
	
	void Player::updateHanging()
	{
	    if(hanging)
	    {
	        hurt=0;
	        canDo=true;
	        attacksHolder=-1;
	        attacksPriority=0;
	        yvelocity=0;
	        xvelocity=0;
	        switch(playerdir)
	        {
	            case 1:
	            changeAnimation("hang_left", NO_CHANGE);
	            break;
	 
	            case 2:
	            changeAnimation("hang_right", NO_CHANGE);
	            break;
	        }
	        switch(currentHangPoint->getHangSide())
			{
				case 1:
				if(playerdir==2 || hurt==2)
				{
					x=(currentHangPoint->x+(currentHangPoint->width/2))-hangPoint.x;
					y=currentHangPoint->y+((height/2)-hangPoint.y);
				}
				else
				{
					hanging = false;
					currentHangPoint->hanging=0;
					animFinish();
				}
				break;
				
				case 2:
				if(playerdir==1 || hurt==2)
				{
					x=currentHangPoint->x+(currentHangPoint->width/2)+hangPoint.x;
				    y=currentHangPoint->y+((height/2)-hangPoint.y);
				}
				else
				{
					hanging = false;
					currentHangPoint->hanging=0;
					animFinish();
				}
				break;
			}
	    }
	    updateHitbox();
	}
	
	void Player::updateHurt()
	{
	    if((hurtTime>0)&&(Global::worldTime>=hurtTime))
	    {
	        hurtTime=0;
	        if(hurt==2)
	        {
	            hurt=1;
	            xvelocity*=0.8f;
	            attacksHolder=-1;
	        }
	    }
	}

	void Player::updateDrop()
	{
	    if(dropTime>0)
	    {
	    	if(Global::worldTime>=dropTime)
	    	{
		        dropTime=0;
		        dropping=false;
	    	}
	    	else if((Global::worldTime+2)>=dropTime)
	    	{
	    		if(canDo && !onGround && !jumping)
		        {
		        	switch(playerdir)
		        	{
		        		case 1:
		        		changeAnimation("fall_left", FORWARD);
		        		break;
		        		
		        		case 2:
		        		changeAnimation("fall_right", FORWARD);
		        		break;
		        	}
		        }
	    	}
	    }
	}

	/*void updateChargeB()
	{
	    if((chargeTimeB>0)&&(worldTime>=chargeTimeB))
	    {
	        chargeTimeB=0;
	        charge_bdown=0;
	    }
	}*/
	
	void Player::updateAI()
	{
	    if(this->cpu)
	    {
	        if(Global::gamePlaying)
	        {
	        	//if(aiTime>0 && aiTime>=Global::getWorldTime())
	        	{
	        		
	        		if(Global::gameType == Global::TYPE_TRAINING)
	        		{
	        			cpuAI(aiType,1);
	        		}
	        		else
	        		{
	        			cpuAI(AI_NORMAL, 1);
	        		}
	        	}
	            updateHitbox();
	        }
	    }
	}
	
	void Player::Draw(Graphics2D&g, long gameTime)
	{
		if(alive)
		{
			GameElement::Draw(g, gameTime);
			
			if(setIndic)
			{
				switch(playerdir)
				{
					case LEFT:
					indicator->x = (float)(this->x*Camera::Zoom) - (float)(indicX*Scale*Camera::Zoom);
					break;
					
					case RIGHT:
					indicator->x = (float)(this->x*Camera::Zoom) + (float)(indicX*Scale*Camera::Zoom);
					break;
				}
				indicator->y = (float)(this->y*Camera::Zoom) + (int)(indicY*Scale*Camera::Zoom) - (int)((indicator->height)/2);
			}
			else
			{
				indicator->x = (float)(this->x*Camera::Zoom);
				indicator->y = (float)(this->y*Camera::Zoom) - (float)((height/2)*Camera::Zoom) - (float)((indicator->height)/2);
			}
			indicator->Draw(g, gameTime);
			updateHitbox();
			hitbox->Draw(g, gameTime);
		}
		else
		{
			//x = -10000;
			//y = -10000;
		}
		if(itemHolding!=null)
		{
			itemHolding->Draw(g, gameTime);
		}
		if(itemWearing!=null)
		{
			itemWearing->Draw(g, gameTime);
		}
		if(itemHatting!=null)
		{
			itemHatting->Draw(g, gameTime);
		}
		if(itemWielding!=null)
		{
			itemWielding->Draw(g, gameTime);
		}
		offScreenExplosion->Draw(g, gameTime);
	}
	
	void Player::createProjectile(Projectile*p)
	{
		ProjectileManager::AddProjectile(p);
	}
	
	void Player::causeDamage(Player*collide, int amount)
	{
	    AttackTemplates::causeDamage(this, collide, amount);
	}
	
	void Player::causeHurtLaunch(Player*collide, int xDir, float xAmount, float xMult, int yDir, float yAmount, float yMult)
	{
	    AttackTemplates::causeHurtLaunch(this, collide, xDir, xAmount, xMult, yDir, yAmount, yMult);
	}
	
	void Player::causeHurt(Player*collide, byte dir, int time)
	{
	    AttackTemplates::causeHurt(this, collide, dir, time);
	}
	
	//TODO: make these methods
	
	boolean Player::checkItemUse()
	{
		boolean pickedUp = false;
		if(itemCollidingIndex>-1 && itemCollidingIndex < ItemManager::TotalItems())
		{
			Item*item = ItemManager::GetItem(itemCollidingIndex);
			if(!item->held && item->canPickUp())
			{
				pickedUp = pickUpItem(item);
			}
		}
		if(pickedUp)
		{
			return true;
		}
		else
		{
			if(itemHolding!=null)
			{
				return itemHolding->use(Item::ATTACK_NORMAL);
			}
		}
		return false;
	}
	
	boolean Player::checkItemUseSide()
	{
		if(itemHolding!=null)
		{
			return itemHolding->use(Item::ATTACK_SIDE);
		}
		return false;
	}
	
	boolean Player::checkItemUseSmash(byte type)
	{
		if(itemHolding!=null)
		{
			if(type==STEP_CHARGE)
			{
				return itemHolding->chargeSmash();
			}
			else if(type==STEP_GO)
			{
				return itemHolding->use(Item::ATTACK_SMASH);
			}
			return false;
		}
		return false;
	}
	
	boolean Player::pickUpItem(Item*item)
	{
		if(!item->held)
		{
			switch(item->type)
			{
				case Item::TYPE_HOLD:
				if(itemHolding == null)
				{
					itemHolding = item;
					item->pickUp(this);
					return true;
				}
				return false;
				
				case Item::TYPE_WEAR:
				if(itemWearing == null)
				{
					itemWearing = item;
					item->pickUp(this);
					return true;
				}
				return false;
				
				case Item::TYPE_HAT:
				if(itemHatting == null)
				{
					itemHatting = item;
					item->pickUp(this);
					return true;
				}
				return false;
				
				case Item::TYPE_WIELD:
				if(item->getItemNo() == Global::ITEM_SMASHBALL)
				{
					if(itemWielding!=null)
					{
						itemWielding->onDestroy();
					}
					delete itemWielding;
					itemWielding = item;
					item->pickUp(this);
					return true;
				}
				else if(itemWielding == null)
				{
					itemWielding = item;
					item->pickUp(this);
					return true;
				}
				return false;
				
				case Item::TYPE_FOOD:
				item->pickUp(this);
				return true;
			}
		}
		return false;
	}
	
	void Player::discardItem()
	{
		if(this->itemHolding!=null)
		{
			ItemManager::AddItem(itemHolding);
			itemHolding->discard();
			this->itemHolding = null;
		}
	}
	
	void Player::hitHandlerRight(Player*collide)
	{
	    if((collide->playerNo>0)&&!((Global::teamBattle)&&(team==collide->team)))
	    {
	        if(cpu)
	        {
	            x-=(float)1;
	        }
	        else
	        {
	            collide->x+=(float)0.7;
	        }
	    }
	}
	
	void Player::hitHandlerLeft(Player*collide)
	{
	    if((collide->playerNo>0)&&!((Global::teamBattle)&&(team==collide->team)))
	    {
	        if(cpu)
	        {
	            x+=(float)1;
	        }
	        else
	        {
	            collide->x-=(float)0.7;
	        }
	    }
	}
	
	boolean Player::isHittableRight(Player*collide)
	{
	    if((collide->playerNo>0)&&!((Global::teamBattle)&&(team==collide->team))&&!(collide->attacksPriority==6)
	    &&!(collide->attacksPriority==7)&&(collide->attacksPriority<attacksPriority)
	    &&!(collide->attacksPriority==attacksPriority)
	    &&!((collide->playerdir==1)&&(collide->attacksPriority==5))&&(!collide->invincible))
	    {
	        return true;
	    }
	    return false;
	}
	
	boolean Player::isHittableLeft(Player*collide)
	{
	    if((collide->playerNo>0)&&!((Global::teamBattle)&&(team==collide->team))&&!(collide->attacksPriority==6)
	    &&!(collide->attacksPriority==7)&&(collide->attacksPriority<attacksPriority)
	    &&!(collide->attacksPriority==attacksPriority)
	    &&!((collide->playerdir==2)&&(collide->attacksPriority==5))&&(!collide->invincible))
	    {
	        return true;
	    }
	    return false;
	}

	boolean Player::isHittableUp(Player*collide)
	{
	    if((collide->playerNo>0)&&!((Global::teamBattle)&&(team==collide->team))&&(collide->attacksPriority<attacksPriority)
	    &&!(collide->attacksPriority==6)&&!(collide->attacksPriority==7)&&(!collide->invincible))
	    {
	        return true;
	    }
	    return false;
	}
	
	boolean Player::isHittableDown(Player*collide)
	{
	    if((collide->playerNo>0)&&!((Global::teamBattle)&&(team==collide->team))&&(collide->attacksPriority<attacksPriority)
	    &&!(collide->attacksPriority==6)&&!(collide->attacksPriority==7)&&(!collide->invincible))
	    {
	        return true;
	    }
	    return false;
	}
	
	byte Player::isPlayerColliding(Player*collide)
	{
		RectF overlap = getOverlapArea(collide);
		if(overlap.left != -1)
		{
			RectF overlap2 = collide->getOverlapArea(this);
			
			int w = (int)(overlap.right - overlap.left);
			int h = (int)(overlap.bottom - overlap.top);
			
			float x1 = ((float)overlap.left/Scale);
			float y1 = ((float)overlap.top/Scale);
			float x2 = ((float)overlap2.left/collide->Scale);
			float y2 = ((float)overlap2.top/collide->Scale);
			
			float incr1 = (float)(1/Scale);
			float incr2 = (float)(1/collide->Scale);
			
			boolean colliding = false;
			
			boolean g1 = false;
			
			int left1 = 0;
			int right1 = 0;
			int top1 = 0;
			int bottom1 = 0;

			PixelIterator pxlIter = PixelIterator(this);
			pxlIter.reset(x1,y1,incr1,incr1,(int)w,(int)h);
			PixelIterator colPxlIter = PixelIterator(collide);
			colPxlIter.reset(x2,y2,incr2,incr2,(int)w,(int)h);

			for(int cntY = 0; cntY<h; cntY++)
			{
				for(int cntX = 0; cntX<w; cntX++)
				{
					boolean grid1 = false;
					boolean grid2 = false;
					
					//grid1 = pixelAtPoint((int)pntX1, (int)pntY1);
					//grid2 = collide->pixelAtPoint((int)pntX2, (int)pntY2);
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
					
					if(grid1 && grid2)
					{
						colliding = true;
					}
				}
			}

			if(colliding)
			{
				Rectangle r1 = Rectangle((int)(overlap.left + left1 + (x-(width/2))),(int)(overlap.top + top1 + (y-(height/2))), right1-left1, bottom1-top1);
				collide->updateHitbox();
				Rectangle r2 = Rectangle((int)collide->hitbox->x, (int)collide->hitbox->y, collide->hitbox->width, collide->hitbox->height);
				
				byte dir = getDir(r2,r1);
				
				switch(dir)
				{
					case DIR_UP:
					return DIR_DOWN;
					
					case DIR_UPLEFT:
					return DIR_RIGHT;
					
					case DIR_UPRIGHT:
					return DIR_LEFT;
					
					case DIR_LEFT:
					return DIR_RIGHT;
					
					case DIR_RIGHT:
					return DIR_LEFT;
					
					case DIR_DOWNLEFT:
					return DIR_RIGHT;
					
					case DIR_DOWNRIGHT:
					return DIR_LEFT;
					
					case DIR_DOWN:
					return DIR_UP;
				}
				return dir;
			}
		}
		return 0;
	}
	
	byte Player::solidPlatformCollision(Platform*collide)
	{
		updateHitbox();
		RectangleF r1 = RectangleF(hitbox->x, hitbox->y, (float)hitbox->width, (float)hitbox->height);
		RectangleF r2 = RectangleF((collide->x - collide->width/2),(collide->y - collide->height/2),(float)collide->width,(float)collide->height);
		RectangleF collideOverlap = getOverlapRect(r2,r1);
		RectangleF overlap = getOverlapRect(r1,r2);
		
		if(collideOverlap.x!=-1)
		{
			int startX = (int)collideOverlap.x;
			int endX = (int)(collideOverlap.x + collideOverlap.width);
			int startY = (int)collideOverlap.y;
			int endY = (int)(collideOverlap.y + collideOverlap.height);
			
			float x2 = ((float)startX/collide->Scale);
			float y2 = ((float)startY/collide->Scale);
			float incr = (float)(1/collide->Scale);
			
			float pntX2 = x2;
			float pntY2 = y2;
			
			int left=0;
			int right=0;
			int top=0;
			int bottom=0;
			boolean colliding = false;

			PixelIterator colPxlIter = PixelIterator(collide);
			colPxlIter.reset(x2,y2,incr,incr,(int)collideOverlap.width,(int)collideOverlap.height);
			
			for(int cntY=startY; cntY<endY; cntY++)
			{
				pntX2 = x2;
				for(int cntX=startX; cntX<endX; cntX++)
				{
					boolean checker = false;
					
					checker = collide->pixelAtPoint((int)pntX2, (int)pntY2);
					
					if(checker)
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
					pntX2+=incr;
				}
				pntY2+=incr;
			}
			
			if(colliding)
			{
				int w = right - left;
				int h = bottom - top;
				Rectangle collideOverlap2 = Rectangle(left, top, w, h);
				int overlapX = (int)((left - startX) + overlap.x + (w/2));
				int overlapY = (int)((top - startY) + overlap.y + (h/2));
				byte dir = getDir2((float)hitbox->width/2,(float)hitbox->height/2,(float)overlapX, (float)overlapY);
				
				byte type = collide->getType();
				if((type == Platform::TYPE_NORMAL)|| (type == Platform::TYPE_GOTHROUGH && dir == DIR_DOWN && (!jumping || (jumping&&yvelocity>=0))))
				{
					switch(dir)
					{
						case DIR_DOWN:
						this->y = (collideOverlap2.y + (collide->y - collide->height/2)) - (float)((float)(hitbox->height + ((float)hitboxPoint.y*Scale))) + 1;
						updateHitbox();
						return DIR_UP;
						
						case DIR_UP:
						this->y = ((collide->y - collide->height/2) + (collideOverlap2.y + collideOverlap2.height)) + this->height/2 - ((float)((float)hitboxPoint.y*Scale) + this->height/2) + 1;
						updateHitbox();
						return DIR_DOWN;
						
						case DIR_LEFT:
						this->x = ((collide->x - collide->width/2) + (collideOverlap2.x + collideOverlap2.width) + (float)((float)this->hitbox->width)/2);
						updateHitbox();
						return DIR_RIGHT;
						
						case DIR_RIGHT:
						this->x = (collideOverlap2.x + (collide->x - collide->width/2)) - (float)((float)this->hitbox->width)/2;
						updateHitbox();
						return DIR_LEFT;
					}
				}
			}
		}
		return 0;
	}
	
	boolean Player::hitboxRectsColliding(HitBox*collide)
	{
		float left1, left2;
		float right1, right2;
        float top1, top2;
        float bottom1, bottom2;
        
        Player*playr = Global::getPlayerActor(collide->playerNo);
        RectangleF collidePoint = playr->hitboxPoint;

        left1 = (float)(x + (hitboxPoint.x*Scale));
        left2 = (float)(playr->x + (collidePoint.x*Scale));
        right1 = (float)(left1+(hitboxPoint.width*Scale));
        right2 = (float)(left2+(collidePoint.width*Scale));
        top1 = (float)(y + (hitboxPoint.y*Scale));
        top2 = (float)(playr->y + (collidePoint.y*Scale));
        bottom1 = (float)(top1+(hitboxPoint.height*Scale));
        bottom2 = (float)(top2+(collidePoint.height*Scale));

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
	
	boolean Player::hitboxRectsColliding(WireframeActor*collide)
	{
		int left1, left2;
        int right1, right2;
        int top1, top2;
        int bottom1, bottom2;
        
        left1 = (int)(x + (hitboxPoint.x*Scale));
        left2 = (int)collide->x;
        right1 = (int)(left1+(hitboxPoint.width*Scale));
        right2 = (int)collide->x + collide->width;
        top1 = (int)(y + (hitboxPoint.y*Scale));
        top2 = (int)collide->y;
        bottom1 = (int)(top1+(hitboxPoint.height*Scale));
        bottom2 = (int)collide->y + collide->height;
        
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
	
	boolean Player::hitboxRectsColliding(Actor*collide)
	{
		int left1, left2;
        int right1, right2;
        int top1, top2;
        int bottom1, bottom2;

        left1 = (int)(x + (hitboxPoint.x*Scale));
        left2 = (int)collide->x-(collide->width/2);
        right1 = (int)(left1+(hitboxPoint.width*Scale));
        right2 = (int)collide->x+(collide->width/2);
        top1 = (int)(y + (hitboxPoint.y*Scale));
        top2 = (int)collide->y-(collide->height/2);
        bottom1 = (int)(top1+(hitboxPoint.height*Scale));
        bottom2 = (int)collide->y+(collide->height/2);

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
	
	void Player::platformCollision(Platform*collide, byte dir)
	{
		if(dir>0)
		{
			if(prevCollidePlatform[dir-1])
			{
				if(dir==DIR_UP)
				{
					if(!groundCollidedFrame)
					{
						if(lastGroundPlat == collide) //compare pointers
						{
							float dif = collide->x - lastGroundX;
							if(dif!=0)
							{
								x += dif;
								groundCollidedFrame = true;
							}
						}
						lastGroundPlat = collide;
						lastGroundX = collide->x;
					}
				}
				whilePlatformCollide(collide, dir);
				collide->whilePlayerColliding(this, dir);
			}
			else
			{
				if(dir==DIR_UP)
				{
					lastGroundX = collide->x;
				}
				onPlatformCollide(collide, dir);
				collide->onPlayerCollide(this, dir);
				whilePlatformCollide(collide, dir);
				collide->whilePlayerColliding(this, dir);
			}
		}
		else
		{
			if(prevCollidePlatform[dir-1])
			{
				finishPlatformCollide(collide,dir);
				collide->finishPlayerCollide(this, dir);
			}
		}
	}
	
	void Player::barrierCollide(byte barrierNo)
	{
	    float xSave = 0;
	    float ySave = 0;
		
	    String collideSide = "";
		
	    switch(barrierNo)
	    {
	        case DIR_UP:
	        offScreenExplosion->setRotation(180);
	        collideSide = "top";
	        break;
	        
	        case DIR_RIGHT:
	        offScreenExplosion->setRotation(270);
	        collideSide = "right";
	        break;
	        
	        case DIR_DOWN:
	        offScreenExplosion->setRotation(0);
	        collideSide = "bottom";
	        break;
	        
	        case DIR_LEFT:
	        offScreenExplosion->setRotation(90);
	        collideSide = "left";
	        break;
	    }
	    bool finishedGame = false;
	    if(alive)
	    {
	        Console::WriteLine((String)"player " + playerNo + (String)" collided with " + collideSide + (String)"border");
	        if(Global::suddenDeath)
	        {
	        	Console::WriteLine((String)"player " + playerNo + (String)" lost a life");
	        	
	        	stock -= 1;
	        	
	        	if(Global::gamePlaying)
	            {
		        	Global::deaths[playerNo]++;
		        	Global::scores[playerNo]--;
		        	
		        	if(lastHit>0)
		            {
		        		Global::scores[lastHit]++;
		            	Global::KOs[lastHit]++;
		            }
	            }
	        	
	        	if(stock == 0)
	        	{
		        	boolean winResult=Global::checkWinners(playerNo);
	                for(int i=1; i<=Global::possPlayers; i++)
	                {
	                    Console::WriteLine((String)"winners[" + i + (String)"]=" + Global::winners[i] + (String)", ");
	                }
	                if(winResult)
	                {
	                    Global::finishGame();
						finishedGame = true;
	                }
	        	}
	        }
	        else
	        {
		        switch(Global::gameMode)
		        {
		            default:
		            if(Global::gamePlaying)
		            {
			            Global::scorePoint(this->getPlayerNo());
			            if(lastHit>0)
			            {
			            	Global::KOs[lastHit]++;
			            }
			            Global::deaths[playerNo]++;
		            }
		            break;
		 
		            case 2:
		            Console::WriteLine((String)"player " + playerNo + (String)" lost a life");
		 
		            stock -= 1;
		            
		            if(Global::gamePlaying)
		            {
			            if(lastHit>0)
			            {
			            	Global::scores[lastHit]++;
			            	Global::KOs[lastHit]++;
			            }
			            Global::scores[playerNo]--;
			            Global::deaths[playerNo]++;
		            }
		            
		            Console::Write("Remaining Lives: ");
		            for(int i=1; i<=4; i++)
		            {
		            	if(Global::characters[i]!=null)
		            	{
		            		Console::Write((String)"player " + i + (String)"=" + Global::characters[i]->stock + (String)"; ");
		            	}
		            }
		            Console::WriteLine("");
		            
	                boolean winResult=Global::checkWinners(playerNo);
					for(int i=1; i<=Global::possPlayers; i++)
	                {
	                    Console::WriteLine((String)"winners[" + i + (String)"]=" + Global::winners[i] + (String)", ");
	                }
	                if(winResult)
	                {
	                    Global::finishGame();
						finishedGame = true;
	                }
		            break;
		        }
	        }
	        percent=00;
			
			if(P2PDataManager::isEnabled())
			{
				P2PDataManager::sendScore(this, finishedGame);
			}
			
	        if(itemHolding!=null)
	        {
	        	itemHolding->onDestroy();
	        	Console::WriteLine((String)"Destroyed Item " + Global::getItemName(itemHolding->itemNo));
	        	delete itemHolding;
	        	itemHolding = null;
	        }
	        if(itemWearing!=null)
	        {
	        	itemWearing->onDestroy();
	        	Console::WriteLine((String)"Destroyed Item " + Global::getItemName(itemWearing->itemNo));
	        	delete itemWearing;
	        	itemWearing = null;
	        }
	        if(itemHatting!=null)
	        {
	        	itemHatting->onDestroy();
	        	Console::WriteLine((String)"Destroyed Item " + Global::getItemName(itemHatting->itemNo));
	        	delete itemHatting;
	        	itemHatting = null;
	        }
	        if(itemWielding!=null)
	        {
	        	itemWielding->onDestroy();
	        	Console::WriteLine((String)"Destroyed Item " + Global::getItemName(itemWielding->itemNo));
	        	delete itemWielding;
	        	itemWielding = null;
	        }
	        
	        if(canFinalsmash)
	        {
	        	canFinalsmash = false;
	        	Global::smashBallOnField = false;
	        }
	        Rect borders = Global::currentStage->getViewBorders();
	        switch(barrierNo)
	        {
	        	case DIR_LEFT:
	            ySave=y;
	            xSave=(float)Global::currentStage->x + (float)borders.left-40;
	            break;
	            
	            case DIR_UP:
	            xSave=x;
	            ySave=(float)Global::currentStage->y + (float)borders.top+80;
	            break;
	            
	            case DIR_RIGHT:
	            ySave=y;
	            xSave=(float)Global::currentStage->x + (float)borders.right-80;
	            break;
	            
	            case DIR_DOWN:
	            xSave=x;
	            ySave=(float)Global::currentStage->y + (float)borders.bottom-80;
	            break;
	        }
	        
	        reset();
	        
	        offScreenExplosion->x = xSave;
	        offScreenExplosion->y = ySave;
	        
	        offScreenExplosion->setActive();
			
	        alive = false;
			
	        Console::WriteLine((String)"player " + playerNo + " finished collision event with " + collideSide + "border");
	    }
	}
	
	void Player::platformResponse(Platform*collide, byte dir, double multiplier)
	{
		switch(dir)
		{
			case DIR_UP:
			yvelocity*=(float)multiplier;
			//y = (collide->y - (hitbox->height + hitboxPoint[1]));
			break;
			
			case DIR_DOWN:
			yvelocity*=(float)multiplier;
			//y=(collide->y+collide->height - hitboxPoint[1]);
			break;
			
			case DIR_LEFT:
			xvelocity*=(float)multiplier;
			//x = (collide->x - (hitbox->width/2));
			break;
			
			case DIR_RIGHT:
			xvelocity*=(float)multiplier;
			//x = (collide->x + collide->width + (hitbox->width/2));
			break;
		}
	}
	
	//TODO: add actions to these events
	
	void Player::onPlatformCollide(Platform*collide, byte dir)
	{
		//Open for implementation, but call super method
		if(dir==DIR_UP)
		{
			switch(collide->getType())
			{
				default:
				case Platform::TYPE_NORMAL:
				checkAttacks();
				if(hurt==2)
				{
				    hurt=1;
				    if(yvelocity>=0)
				    {
				        hurt=0;
				    }
				    checkAttacks();
				}
				lastHit=0;
				if((canDo)&&((jumping && yvelocity>=-1)||(yvelocity>16))&&!landing)
				{
					if(chargingAttack || chargeSmash>0)
					{
						destroyCharge();
					}
				    jumping=false;
				    landing=true;
				    switch(playerdir)
				    {
				        case 1:
				        changeAnimation("land_left", FORWARD);
				        break;
				 
				        case 2:
				        changeAnimation("land_right", FORWARD);
				        break;
				    }
				}
				else if((yvelocity>=0)&&(canDo)&&(!chargingAttack)&&(moveRight==0)&&(moveLeft==0)
				&&(!hasgrabbed)&&(!grabbing)&&(chargeSmash==0)&&(!chargingAttack))
				{
				    if(down)
				    {
				    	switch(playerdir)
				        {
				            case 1:
				            changeAnimation("crouch_left", NO_CHANGE);
				            break;
				 
				            case 2:
				            changeAnimation("crouch_right", NO_CHANGE);
				            break;
				        }
				    }
				    else if(chargeSmash==0 && !chargingAttack)
				    {
				        switch(playerdir)
				        {
				            case 1:
				            changeAnimation("stand_left", NO_CHANGE);
				            break;
				 
				            case 2:
				            changeAnimation("stand_right", NO_CHANGE);
				            break;
				        }
				    }
				}
				break;
				
				case Platform::TYPE_GOTHROUGH:
				canDropThrough=true;
				checkAttacks();
				lastHit=0;
				if((canDo)&&((jumping && yvelocity>=-1)||(yvelocity>16))&&!landing)
				{
				    jumping=false;
				    landing=true;
				    switch(playerdir)
				    {
				        case 1:
				        changeAnimation("land_left", FORWARD);
				        break;
				 
				        case 2:
				        changeAnimation("land_right", FORWARD);
				        break;
				    }
				}
				else if((yvelocity>0)&&(canDo)&&(!chargingAttack)&&(moveRight==0)&&(moveLeft==0)&&(chargeSmash==0)&&(!chargingAttack))
				{
				    if(down)
				    {
				        dropping=true;
				        canDropThrough=false;
				        dropTime=Global::worldTime+4;
				    }
				    else
				    {
				        switch(playerdir)
				        {
				            case 1:
				            changeAnimation("stand_left", NO_CHANGE);
				            break;
				 
				            case 2:
				            changeAnimation("stand_right", NO_CHANGE);
				            break;
				        }
				    }
				}
				break;
			}
		}
	}
	
	void Player::whilePlatformCollide(Platform*collide, byte dir)
	{
		//Open for implementation, but call super method
		switch(collide->getType())
		{
			default:
			case Platform::TYPE_NORMAL:
			if((hurt>0)&&(abs(yvelocity)>6))
			{
			    if(hurt==2)
			    {
			        hurt=1;
			        canDo=true;
			    }
			    yvelocity=-(abs(yvelocity)/2);
			    switch(playerdir)
			    {
			        case 1:
			        changeAnimation("hurt_flip_left", NO_CHANGE);
			        break;
			 
			        case 2:
			        changeAnimation("hurt_flip_right", NO_CHANGE);
			        break;
			    }
			}
			else
			{
			    hurt=0;
			    if(dir==DIR_DOWN)
			    {
			    	if(yvelocity<0)
			    	{
			    		y+=(ceil(abs(yvelocity)));
			    	}
			    }
			    else if(dir == DIR_UP)
			    {
			    	if(yvelocity>=0 && !hanging)
			    	{
			    		platformResponse(collide,dir,0);
			    		xvelocity = 0;
			    	}
			    }
			    else
			    {
			    	if(!hanging)
			    	{
			    		platformResponse(collide,dir,0);
			    		xvelocity = 0;
			    	}
			    }
			}
			break;
			
			case Platform::TYPE_GOTHROUGH:
			if(dir == DIR_UP)
			{
				if(canDo && hurt==0 && yvelocity>=-0.5f && jumping && !landing)
				{
					jumping=false;
				    landing=true;
				    switch(playerdir)
				    {
				        case 1:
				        changeAnimation("land_left", FORWARD);
				        break;
				 
				        case 2:
				        changeAnimation("land_right", FORWARD);
				        break;
				    }
				}
				else if((hurt>0)&&(yvelocity>6))
				{
				    canDo=true;
				    if(hurt==2)
				    {
				        hurt=1;
				    }
				    yvelocity=-(abs(yvelocity)/2);
				    switch(playerdir)
				    {
				        case 1:
				        changeAnimation("hurt_flip_left", NO_CHANGE);
				        break;
				 
				        case 2:
				        changeAnimation("hurt_flip_right", NO_CHANGE);
				        break;
				    }
				}
				else
				{
				    if((!dropping)&&(yvelocity>=0))
				    {
				        canDo=true;
				        hurt=0;
				        this->platformResponse(collide, dir, 0);
				        xvelocity=0;
				    }
				}
			}
			break;
		}
	}
	
	void Player::finishPlatformCollide(Platform*collide, byte dir)
	{
		//Open for implementation, but call super method
	}
	
	void Player::onGroundCollide()
	{
		//Open for implementation, but call super method
		if((hurt!=2)&&(!hanging)&&(!jumping)&&(!dropping))
		{
		    onGround=true;
		    doubleJump=0;
		    up=false;
		    bUp=false;
		}
	}
	
	void Player::whileGroundColliding()
	{
		//Open for implementation, but call super method
		if((hurt!=2)&&(!hanging)&&(!jumping)&&(!dropping))
		{
		    onGround=true;
		    doubleJump=0;
		    up=false;
		    bUp=false;
		}
	}
	
	void Player::finishGroundCollide()
	{
		//Open for implementation, but call super method
		onGround=false;
		doubleJump=1;
		checkAttacks();
		if((!hanging)&&(yvelocity>0)&&(canDo))
		{
			if(moveLeft>0)
		    {
		        changeAnimation("fall_left", NO_CHANGE);
		    }
			else if(moveRight>0)
		    {
		        changeAnimation("fall_right", NO_CHANGE);
		    }
		}
	}
	
	void Player::onHang(HangPoint*collide)
	{
		//Open for implementation, but call super method
		switch(collide->getHangSide())
		{
			case 1:
			if((playerdir==2)&&(collide->hanging==0)&&(!onGround))
			{
			    collide->hanging=playerNo;
			    moveLeft=0;
			    moveRight=0;
			    setToDefaultValues();
			    jumping=false;
			    landing=false;
			    hanging=true;
			    onGround = false;
			    bUp=false;
			    canDo=true;
			    doubleJump=1;
			    changeAnimation("hang_right", NO_CHANGE);
			    x=(collide->x+(collide->width/2))-hangPoint.x;
			    y=collide->y+((height/2)-hangPoint.y);
			    if(attacksPriority!=7)
			    {
			        attacksHolder=-1;
			        attacksPriority=0;
			    }
			    yVel=0;
			    xVel=0;
			    xvelocity=0;
			    yvelocity=0;
			}
			break;
			
			case 2:
			if((playerdir==1)&&(collide->hanging==0)&&(!onGround))
			{
			    collide->hanging=playerNo;
			    moveLeft=0;
			    moveRight=0;
			    setToDefaultValues();
			    jumping=false;
			    landing=false;
			    hanging=true;
			    onGround = false;
			    bUp=false;
			    canDo=true;
			    doubleJump=1;
			    changeAnimation("hang_left", NO_CHANGE);
			    x=collide->x+(collide->width/2)+hangPoint.x;
			    y=collide->y+((height/2)-hangPoint.y);
			    if(attacksPriority!=7)
			    {
			        attacksHolder=-1;
			        attacksPriority=0;
			    }
			    yVel=0;
			    xVel=0;
			    xvelocity=0;
			    yvelocity=0;
			}
			break;
		}
	}
	
	void Player::whileHanging(HangPoint*collide)
	{
		onGround = false;
		/*if(hanging)
		{
			xvelocity = 0;
			yvelocity = 0;
			switch(playerdir)
			{
				case LEFT:
				changeAnimation("hang_left",NO_CHANGE);
				break;
				
				case RIGHT:
				changeAnimation("hang_right",NO_CHANGE);
				break;
			}
		}*/
	}
	
	void Player::finishHang(HangPoint*collide)
	{
		hanging=false;
		//noFollow=0;
		canDo=true;
		if(collide->hanging==playerNo)
		{
		    collide->hanging=0;
		}
	}
	
	void Player::checkPlayerCollision(Player*playr)
	{
		byte dir = isPlayerColliding(playr);
		if(dir>0)
		{
			if(playerCollisions.isColliding(playr->playerNo))
			{
				if(attacksHolder>-1 || attacksPriority>0)
				{
					switch(dir)
					{
						case DIR_UP:
						if(isHittableUp(playr))
						{
							whilePlayerHitting(playr,dir);
						}
						break;
						
						case DIR_LEFT:
						if(isHittableLeft(playr))
						{
							whilePlayerHitting(playr,dir);
						}
						break;
						
						case DIR_RIGHT:
						if(isHittableRight(playr))
						{
							whilePlayerHitting(playr,dir);
						}
						break;
						
						case DIR_DOWN:
						if(isHittableDown(playr))
						{
							whilePlayerHitting(playr,dir);
						}
						break;
					}
				}
				else
				{
					playerCollisions.removeCollision(playr->playerNo);
					finishPlayerHit(playr);
				}
			}
			else
			{
				if(attacksHolder>-1 || attacksPriority>0)
				{
					playerCollisions.addCollision(playr->playerNo);
					switch(dir)
					{
						case DIR_UP:
						if(isHittableUp(playr))
						{
							playerHitHandler(playr,dir);
						}
						break;
						
						case DIR_LEFT:
						if(isHittableLeft(playr))
						{
							playerHitHandler(playr,dir);
						}
						break;
						
						case DIR_RIGHT:
						if(isHittableRight(playr))
						{
							playerHitHandler(playr,dir);
						}
						break;
						
						case DIR_DOWN:
						if(isHittableDown(playr))
						{
							playerHitHandler(playr,dir);
						}
						break;
					}
				}
				else
				{
					playerCollisions.removeCollision(playr->playerNo);
					finishPlayerHit(playr);
				}
			}
			whilePlayerColliding(playr,dir);
		}
		else if(playerCollisions.isColliding(playr->playerNo))
		{
			playerCollisions.removeCollision(playr->playerNo);
			finishPlayerHit(playr);
		}
		
		if(Actor::rectsColliding(playr))
		{
			if(playerRectCollisions.isColliding(playr->playerNo))
			{
				if(attacksHolder>-1 || attacksPriority>0)
				{
					byte dir2 = getDir2(this->x, this->y, playr->x, playr->y);
					switch(dir2)
					{
						case DIR_UP:
						if(isHittableUp(playr))
						{
							whilePlayerRectHitting(playr,dir2);
						}
						break;
						
						case DIR_LEFT:
						if(isHittableLeft(playr))
						{
							whilePlayerRectHitting(playr,dir2);
						}
						break;
						
						case DIR_RIGHT:
						if(isHittableRight(playr))
						{
							whilePlayerRectHitting(playr,dir2);
						}
						break;
						
						case DIR_DOWN:
						if(isHittableDown(playr))
						{
							whilePlayerRectHitting(playr,dir2);
						}
						break;
					}
				}
				else
				{
					playerRectCollisions.removeCollision(playr->playerNo);
					finishPlayerRectHit(playr);
				}
			}
			else
			{
				if(attacksHolder>-1 || attacksPriority>0)
				{
					playerRectCollisions.addCollision(playr->playerNo);
					byte dir2 = getDir2(this->x, this->y, playr->x, playr->y);
					switch(dir2)
					{
						case DIR_UP:
						if(isHittableUp(playr))
						{
							onPlayerRectHit(playr,dir2);
						}
						break;
						
						case DIR_LEFT:
						if(isHittableLeft(playr))
						{
							onPlayerRectHit(playr,dir2);
						}
						break;
						
						case DIR_RIGHT:
						if(isHittableRight(playr))
						{
							onPlayerRectHit(playr,dir2);
						}
						break;
						
						case DIR_DOWN:
						if(isHittableDown(playr))
						{
							onPlayerRectHit(playr,dir2);
						}
						break;
					}
				}
				else
				{
					playerRectCollisions.removeCollision(playr->playerNo);
					finishPlayerRectHit(playr);
				}
			}
		}
		else if(playerRectCollisions.isColliding(playr->playerNo))
		{
			playerRectCollisions.removeCollision(playr->playerNo);
			finishPlayerRectHit(playr);
		}
		
		if(hitboxRectsColliding(playr->getHitbox()))
		{
			if(!(attacksHolder>-1 || attacksPriority>0))
			{
				if(playr->x < x)
				{
					playerColliding(playr,DIR_LEFT);
				}
				else
				{
					playerColliding(playr,DIR_RIGHT);
				}
			}
		}
	}
	
	void Player::playerColliding(Player*collide, byte dir)
	{
		switch(dir)
		{
			case DIR_LEFT:
			hitHandlerLeft(collide);
			break;
			
			case DIR_RIGHT:
			hitHandlerRight(collide);
			break;
		}
	}
	
	void Player::playerHitHandler(Player*collide, byte dir)
	{
		if(attacksHolder>-1)
		{
			AttackManager::AttackInfo*nfo = attackMgr.getAttackInfo(dir, attacksHolder, playerdir);
			if(nfo!=null)
			{
				causeDamage(collide,nfo->damage);
		        causeHurtLaunch(collide,nfo->xDir,nfo->xAmount,nfo->xMult, nfo->yDir,nfo->yAmount,nfo->yMult);
		        if(collide->xvelocity>0)
		        {
		        	causeHurt(collide, LEFT, nfo->delayTime);
		        }
		        else if(collide->xvelocity<0)
		        {
		        	causeHurt(collide, RIGHT,nfo->delayTime);
		        }
		        else
		        {
		        	causeHurt(collide, collide->playerdir,nfo->delayTime);
		        }
			}
		}
		onPlayerHit(collide,dir);
	}
	
	void Player::whilePlayerColliding(Player*collide, byte dir)
	{
		//Open for implementation
	}
	
	void Player::onPlayerHit(Player*collide, byte dir)
	{
		//Open for implementation
	}
	
	void Player::whilePlayerHitting(Player*collide, byte dir)
	{
		//Open for implementation
	}
	
	void Player::finishPlayerHit(Player*collide)
	{
		//Open for implementation
	}
	
	void Player::onPlayerRectHit(Player*collide, byte dir)
	{
		//Open for implementation
	}
	
	void Player::whilePlayerRectHitting(Player*collide, byte dir)
	{
		//Open for implementation
	}
	
	void Player::finishPlayerRectHit(Player*collide)
	{
		//Open for implementation
	}
	
	boolean Player::onPlayerDeflectDamage(Player*collide, int damage)
	{
		//Open for implementation
		return false;
	}
	
	boolean Player::onPlayerDeflectLaunch(Player*collide, int xDir, float xAmount, float xMult, int yDir, float yAmount, float yMult)
	{
		//Open for implementation
		return false;
	}
	
	boolean Player::onItemDeflectDamage(Item*collide, int damage)
	{
		//Open for implementation
		return false;
	}
	
	boolean Player::onItemDeflectLaunch(Item*collide, int xDir, float xAmount, float xMult, int yDir, float yAmount, float yMult)
	{
		//Open for implementation
		return false;
	}
	
	boolean Player::onProjectileDeflectDamage(Projectile*collide, int damage)
	{
		//Open for implementation
		return false;
	}
	
	boolean Player::onProjectileDeflectLaunch(Projectile*collide, int xDir, float xAmount, float xMult, int yDir, float yAmount, float yMult)
	{
		//Open for implementation
		return false;
	}
	
	void Player::onBorderCollide(byte dir)
	{
		barrierCollide(dir);
	}
	
	void Player::addAttackInfo(byte dir, int attackNo, byte playerdir, int damage, int delayTime, int xDir,float xAmount,float xMult,int yDir,float yAmount,float yMult)
	{
		switch(dir)
		{
			case DIR_LEFT:
			attackMgr.addLeftAttackInfo(attackNo, playerdir, damage, delayTime, xDir, xAmount, xMult, yDir, yAmount, yMult);
			break;
			
			case DIR_RIGHT:
			attackMgr.addRightAttackInfo(attackNo, playerdir, damage, delayTime, xDir, xAmount, xMult, yDir, yAmount, yMult);
			break;
			
			case DIR_UP:
			attackMgr.addUpAttackInfo(attackNo, playerdir, damage, delayTime, xDir, xAmount, xMult, yDir, yAmount, yMult);
			break;
			
			case DIR_DOWN:
			attackMgr.addDownAttackInfo(attackNo, playerdir, damage, delayTime, xDir, xAmount, xMult, yDir, yAmount, yMult);
			break;
		}
	}
	
	void Player::stand()
	{
	    /*checkAttacks();
	    if(canDo && !jumping)
	    {
	        moveLeft=0;
	        moveRight=0;
	        switch(playerdir)
	        {
	            case 1:
	            changeAnimation("stand_left", NO_CHANGE);
	            break;
	 
	            case 2:
	            changeAnimation("stand_right", NO_CHANGE);
	            break;
	        }
	    }*/
		if(attacksPriority!=7)
		{
			animFinish();
		}
	}
	
	void Player::switchDirection()
	{
		if(playerdir == LEFT)
		{
			playerdir = RIGHT;
			String animName = getAnimName();
			String suffix = animName.substring(animName.length()-5, animName.length());
			if(suffix.equals("_left"))
			{
				String prefix = animName.substring(0, animName.length()-5);
				changeAnimation(prefix + "_right", FORWARD);
			}
		}
		else if(playerdir == RIGHT)
		{
			playerdir = LEFT;
			String animName = getAnimName();
			String suffix = animName.substring(animName.length()-6, animName.length());
			if(suffix.equals("_right"))
			{
				String prefix = animName.substring(0, animName.length()-6);
				changeAnimation(prefix + "_left", FORWARD);
			}
		}
	}
	
	void Player::moveDown()
	{
	    hurt=0;
	    down=true;
	    upKey=false;
	    if((onGround)&&(canDo))
	    {
	        switch(playerdir)
	        {
	            case 1:
	            changeAnimation("crouch_left", NO_CHANGE);
	            break;
	 
	            case 2:
	            changeAnimation("crouch_right", NO_CHANGE);
	            break;
	        }
	    }
	    if(hanging)
	    {
	        hanging=false;
	        onGround = false;
	        switch(playerdir)
	        {
	            case 1:
	            changeAnimation("fall_left", NO_CHANGE);
	            break;
	 
	            case 2:
	            changeAnimation("fall_right", NO_CHANGE);
	            break;
	        }
	    }
	    if(canDropThrough)
	    {
	        dropping=true;
	        canDropThrough=false;
	        yvelocity+=2;
	        dropTime=Global::worldTime+4;
	    }
	}
	
	void Player::jump()
	{
		jump(5,5);
	}
	
	void Player::jump(float dist1, float dist2)
	{
		if(!chargingAttack && chargeSmash==0 && CanDo())
		{
		    if((hurt==2)&&(onGround))
		    {
		        hurt=0;
		        animFinish();
		    }
		    else if(hurt==1)
		    {
		        hurt=0;
		    }
		    up=true;
		    upKey=true;
		    if(hanging)
		    {
		        hanging=false;
		        climbUp();
		    }
		    else if(onGround)
		    {
		        jumping=true;
		        yvelocity=-dist1;
		        y-=1;
		        switch(playerdir)
		        {
		            case 1:
		            changeAnimation("jump_left", FORWARD);
		            break;
		 
		            case 2:
		            changeAnimation("jump_right", FORWARD);
		            break;
		        }
		        doubleJump=1;
		    }
		    else
		    {
		        if(doubleJump==1)
		        {
		        	jumping = true;
		            yvelocity=-dist2;
		            doubleJump=0;
		            switch(playerdir)
		            {
		                case 1:
		                changeAnimation("jump2_left", FORWARD);
		                break;
		 
		                case 2:
		                changeAnimation("jump2_right", FORWARD);
		                break;
		            }
		        }
		    }
		}
	}
	
	void Player::climbUp()
	{
	    if((hurt==2)&&(onGround))
	    {
	        hurt=0;
	        animFinish();
	    }
	    up=true;
	    hanging=false;
	    y-=((float)hitbox->height + ((float)height*0.26f));
	    if(doubleJump==1)
	    {
	        yvelocity=-2;
	        doubleJump=0;
	        switch(playerdir)
	        {
	            case 1:
	            x-=(hitbox->width);
	            changeAnimation("jump2_left", FORWARD);
	            break;
	 
	            case 2:
	            x+=(hitbox->width);
	            changeAnimation("jump2_right", FORWARD);
	            break;
	        }
	    }
	    onGround = false;
	}
	
	void Player::climbUpAttack()
	{
	    climbUp();
	    attackA();
	}
	
	void Player::onFinishCharge()
	{
		//
	}
	
	void Player::doChargingAttack(byte button)
	{
		//
	}
	
	/**
	 * Standard attack. Should be overridden. {@link AttackTemplates} class can be used for basic attacks.
	 */
	void Player::attackA()
	{
		//
	}
	
	/**
	 * Standard side attack. Should be overridden. {@link AttackTemplates} class can be used for basic attacks.
	 */
	void Player::attackSideA()
	{
		//
	}
	
	/**
	 * Standard up attack. Should be overridden. {@link AttackTemplates} class can be used for basic attacks.
	 */
	void Player::attackUpA()
	{
		//
	}
	
	/**
	 * Standard down attack. Should be overridden. {@link AttackTemplates} class can be used for basic attacks.
	 */
	void Player::attackDownA()
	{
		//
	}
	
	/**
	 * Special attack. Should be overridden. {@link AttackTemplates} class can be used for basic attacks.
	 */
	void Player::attackB()
	{
		//
	}
	
	/**
	 * Special side attack. Should be overridden. {@link AttackTemplates} class can be used for basic attacks.
	 */
	void Player::attackSideB()
	{
		//
	}
	
	/**
	 * Special up attack. Should be overridden. {@link AttackTemplates} class can be used for basic attacks.
	 */
	void Player::attackUpB()
	{
		//
	}
	
	/**
	 * Special down attack. Should be overridden. {@link AttackTemplates} class can be used for basic attacks.
	 */
	void Player::attackDownB()
	{
		//
	}
	
	/**
	 * Smash side attack. Should be overridden. {@link AttackTemplates} class can be used for basic attacks.
	 * <p>
	 * @param type determines whether the smash attack is {@link #STEP_CHARGE charging}, {@link #STEP_GO going}, or {@link #STEP_FINISH finishing}.
	 */
	void Player::attackSideSmash(byte type)
	{
		//
	}
	
	/**
	 * Smash up attack. Should be overridden. {@link AttackTemplates} class can be used for basic attacks.
	 * <p>
	 * @param type determines whether the smash attack is {@link #STEP_CHARGE charging}, {@link #STEP_GO going}, or {@link #STEP_FINISH finishing}.
	 */
	void Player::attackUpSmash(byte type)
	{
		//
	}
	
	/**
	 * Smash down attack. Should be overridden. {@link AttackTemplates} class can be used for basic attacks.
	 * <p>
	 * @param type determines whether the smash attack is {@link #STEP_CHARGE charging}, {@link #STEP_GO going}, or {@link #STEP_FINISH finishing}.
	 */
	void Player::attackDownSmash(byte type)
	{
		//
	}
	
	/**
	 * Final Smash attack. Should be overridden. 
	 * It is recommended to write this method from scratch.
	 */
	void Player::attackFinalSmash()
	{
		//
	}
}