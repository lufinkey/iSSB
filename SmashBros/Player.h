#include "GameElement.h"
#include "OffScreenExplode.h"
#include "Chargebar.h"
#include "Platform.h"
#include "HangPoint.h"
#include "CollisionManager.h"
#include "AttackManager.h"
#include "AttackRandomizer.h"
#include "HitBox.h"
#include "Projectile.h"
#include "SmashForwards.h"

#pragma once

namespace SmashBros
{
	class Player : public GameElement
	{
		friend class AttackRandomizer;
		friend class AttackTemplates;
		friend class Chargebar;
		friend class Controls;
		friend class Global;
		friend class P2PDataManager;
		friend class Projectile;
		friend class ProjectileManager;
		friend class Stage;
	private:
		static const float jumpXBoost;

		ArrayList<String> files;

		byte aiType;
		boolean firstUpdate;
		Actor*indicator;
		float indicX,indicY;
		boolean setIndic;

		OffScreenExplode*offScreenExplosion;

		String folderPath;

		Vector2i hangPoint;

		Color playerColor;

		int stock;

		Chargebar*chargebar;

		boolean prevCollidePlatform[8];
		boolean currentCollidePlatform[8];
		SmashBros::Platform*currentCollidePlatformActor[8];
		SmashBros::Platform*lastGroundPlat;
		float lastGroundX;
		boolean groundCollidedFrame;
		HangPoint*currentHangPoint;
		ArrayList<byte> collideQueue;

		CollisionManager playerCollisions;
		CollisionManager playerRectCollisions;
		AttackManager attackMgr;
		AttackRandomizer randomizer;

		int itemCollidingIndex;
		friend class Item;
		friend class ItemManager;
		Item*itemHolding;
		Item*itemWearing;
		Item*itemHatting;
		Item*itemWielding;
		float itemOffsetX;
		float itemOffsetY;

		boolean hangColliding;
		boolean prevHangColliding;
		boolean groundColliding;
		boolean prevGroundColliding;

		boolean groundCheck;

		byte hurtFrame;

		HitBox*hitbox;
		RectangleF hitboxPoint;

		boolean up;

		long runTime;
		long smashTime;
		long moveTime;
		byte buttondir;

		byte playerNo;
		byte team;
		int charNo;
		boolean alive;
		byte lastHit;
		int percent;
		friend class HUD;
		boolean onGround;
		boolean jumping;
		byte hurt;
		long hurtTime;
		boolean invincible;
		boolean deflectState;

		boolean dropping;
		boolean canDropThrough;
		long dropTime;

		boolean canDo;

		boolean cpu;
		Player*currentEnemy;
		long comboTime;
		byte standardCombo;

		boolean grabbed;
		boolean hasgrabbed;
		boolean grabbing;
		
		boolean canFinalsmash;
		boolean hanging;

		virtual void whenCreated();
		
		void reset();

		void updateHitbox();
		void setIndicatorColor();

		void setInitialCPUTarget();
		void updateCPUTarget();
		boolean checkbUpRecovery();
		void recoverJump();
		boolean checkTrappedUnder(Platform*plat);
		boolean checkTrappedUnder(GameEngine::Rectangle plat);
		boolean checkTrappedOver(GameEngine::Rectangle plat);
		boolean isObstacle(Platform*plat);
		float getMinAmountTrappedUnder(Platform*plat);
		Vector2f findRecoveryTarget();
		void getToRecoveryTarget(Vector2f target);
		void goInDirection(byte dir);
		boolean checkObstacleDir(RectangleF obst, byte dir);
		boolean checkDirSemicircle(byte dir, byte dirCmp);
		boolean checkDirRelation(byte dir, byte cmp1, byte cmp2);
		double getClosestDistanceUnSqr(Vector2f self, GameEngine::Rectangle rect);
		Vector2f getClosestPoint(GameEngine::Rectangle rect, byte dir);
		boolean getDirSeparating(Vector2f target, Rectangle rect);
		GameEngine::Rectangle getRectSeparating(Vector2f target);
		void followEnemy(boolean canAttack, int level);
		boolean checkEnemyHang();
		boolean recover(int level);

		void stopAI(int level);
		void walkAI(int level);
		void runAI(int level);
		void jumpAI(int level);
		void followAI(int level);
		void normalAI(int level);
		void cpuAI(byte type, int level);

		void hitHandlerRight(Player*collide);
		void hitHandlerLeft(Player*collide);
		boolean isHittableRight(Player*collide);
		boolean isHittableLeft(Player*collide);
		boolean isHittableUp(Player*collide);
		boolean isHittableDown(Player*collide);

		byte isPlayerColliding(Player*collide);
		byte solidPlatformCollision(Platform*collide);
		void platformCollision(Platform*collide, byte dir);

		void barrierCollide(byte barrierNo);

		void whilePlatformCollide(Platform*collide, byte dir);
		void whileGroundColliding();
		void finishGroundCollide();
		void onHang(HangPoint*collide);
		void whileHanging(HangPoint*collide);
		void finishHang(HangPoint*collide);

		void checkPlayerCollision(Player*playr);
		void playerColliding(Player*collide, byte dir);
		void playerHitHandler(Player*collide, byte dir);

		void onBorderCollide(byte dir);
		
		void handleAddP2PData(DataVoid&data);
		void handleSetP2PData(byte*&data);
		
	protected:
		byte moveLeft;
		byte moveRight;
		
		boolean upKey;
		boolean down;

		String name;

		byte playerdir;
		double weight;
		boolean landing;

		int hitAmount;
		long attackTime;

		int attacksHolder;
		double attacksPriority;

		int chargeSmash;

		int smashPower;
		boolean chargingAttack;
		
		boolean bUp;
		byte doubleJump;

		float walkSpeed;
		float runSpeed;
		float fallWalk;
		float fallRun;
		int flyTime;
		int flyRunTime;
		float recoverAmount;
		float recoverRunAmount;

		void addFile(String file);
		void loadFile(String file);

		void setOnGround(boolean toggle);
		void setItemOffset(float x1, float y1);

		void setCantDo();
		void setHanging(boolean toggle);
		void setJumping(boolean toggle);
		void finishDeflect();
		void resetAttackCollisions();
		void setHitbox(float x1, float y1, int w, int h);
		void showHitboxWireframe(boolean toggle);
		void setHitboxColor(Color c);
		void setFolderPath(String path);

		void addTwoSidedAnimation(String name, String file, int fps, int rows, int cols);
		void addSingleAnimation(String name, String file, int fps, int rows, int cols);

		void setHangPoint(int x1, int y1);
		void destroyCharge();
		void animFinish();

		void updateGravity();
		void updateFrame();
		void updateMovement();
		void updateHanging();
		void updateHurt();
		void updateDrop();
		void updateAI();

		void createProjectile(Projectile*p);

		void causeDamage(Player*collide, int amount);
		void causeHurtLaunch(Player*collide, int xDir, float xAmount, float xMult, int yDir, float yAmount, float yMult);
		void causeHurt(Player*collide, byte dir, int time);

		boolean checkItemUse();
		boolean checkItemUseSide();
		boolean checkItemUseSmash(byte type);
		void discardItem();

		void platformResponse(Platform*collide, byte dir, double multiplier);

		void addAttackInfo(byte dir, int attackNo, byte playerdir, int damage, int delayTime, int xDir,float xAmount,float xMult,int yDir,float yAmount,float yMult);

		void jump(float dist1, float dist2);
		void climbUp();
		void climbUpAttack();
		
	public:
		static const byte TEAM_RED = 1;
		static const byte TEAM_BLUE = 2;
		static const byte TEAM_GREEN = 3;
		static const byte TEAM_YELLOW = 4;

		static const byte LEFT = 1;
		static const byte RIGHT = 2;

		static const byte STEP_CHARGE = 1;
		static const byte STEP_GO = 2;
		static const byte STEP_FINISH = 3;

		static const byte ATTACK_A = 1;
		static const byte ATTACK_SIDEA = 2;
		static const byte ATTACK_UPA = 3;
		static const byte ATTACK_DOWNA = 4;
		static const byte ATTACK_B = 5;
		static const byte ATTACK_SIDEB = 6;
		static const byte ATTACK_UPB = 7;
		static const byte ATTACK_DOWNB = 8;
		static const byte ATTACK_SIDESMASH = 9;
		static const byte ATTACK_UPSMASH = 10;
		static const byte ATTACK_DOWNSMASH = 11;
		static const byte ATTACK_FINALSMASH = 12;

		static const byte ATTACKTYPE_MELEE = 1;
		static const byte ATTACKTYPE_UPMELEE = 2;
		static const byte ATTACKTYPE_DOWNMELEE = 3;
		static const byte ATTACKTYPE_STRONGMELEE = 4;
		static const byte ATTACKTYPE_SIDEMOVE = 5;
		static const byte ATTACKTYPE_UPMOVE = 6;
		static const byte ATTACKTYPE_DOWNMOVE = 7;
		static const byte ATTACKTYPE_PROJECTILE = 8;
		static const byte ATTACKTYPE_DEFENSIVE = 9;

		static const byte AI_STOP = 1;
		static const byte AI_WALK = 2;
		static const byte AI_RUN = 3;
		static const byte AI_JUMP = 4;
		static const byte AI_NORMAL = 5;
		static const byte AI_FOLLOW = 6;
		
		float xVel;
		float yVel;
		
		Player(float x1, float y1, byte playerNo, byte team);
		virtual ~Player();
		
		virtual void onCreate();
		virtual void Load();
		virtual void LoadAttackTypes();
		virtual void addP2PData(DataVoid&data);
		virtual void setP2PData(byte*&data);
		virtual void onAnimationFinish(const String&n);
		virtual void setToDefaultValues();
		virtual boolean checkIfAble();
		virtual void onDestroy();
		virtual void Update(long gameTime);
		virtual void Draw(Graphics2D&g, long gameTime);

		virtual void onPlatformCollide(Platform*collide, byte dir);
		virtual void finishPlatformCollide(Platform*collide, byte dir);
		virtual void onGroundCollide();
		virtual void whilePlayerColliding(Player*collide, byte dir);
		virtual void onPlayerHit(Player*collide, byte dir);
		virtual void whilePlayerHitting(Player*collide, byte dir);
		virtual void finishPlayerHit(Player*collide);
		virtual void onPlayerRectHit(Player*collide, byte dir);
		virtual void whilePlayerRectHitting(Player*collide, byte dir);
		virtual void finishPlayerRectHit(Player*collide);

		virtual boolean onPlayerDeflectDamage(Player*collide, int damage);
		virtual boolean onPlayerDeflectLaunch(Player*collide, int xDir, float xAmount, float xMult, int yDir, float yAmount, float yMult);
		virtual boolean onItemDeflectDamage(Item*collide, int damage);
		virtual boolean onItemDeflectLaunch(Item*collide, int xDir, float xAmount, float xMult, int yDir, float yAmount, float yMult);
		virtual boolean onProjectileDeflectDamage(Projectile*collide, int damage);
		virtual boolean onProjectileDeflectLaunch(Projectile*collide, int xDir, float xAmount, float xMult, int yDir, float yAmount, float yMult);

		virtual void onFinishCharge();
		virtual void doChargingAttack(byte button);

		virtual void attackA();
		virtual void attackSideA();
		virtual void attackUpA();
		virtual void attackDownA();
		virtual void attackB();
		virtual void attackSideB();
		virtual void attackUpB();
		virtual void attackDownB();
		virtual void attackSideSmash(byte type);
		virtual void attackUpSmash(byte type);
		virtual void attackDownSmash(byte type);
		virtual void attackFinalSmash();

		void respawn();
		void Unload();
		void addAIAttackType(byte attack, byte attacktype, float probability, boolean charge = false);
		
		void addAnimation(Animation*a);
		void setColor(Color c);

		boolean isCPU();
		boolean isAlive();
		boolean isHurt();
		boolean isHoldingItem();
		boolean isWearingItem();
		boolean isHattingItem();
		boolean isWieldingItem();
		boolean isInvincible();
		String getName();
		int getPercent();
		int getLastHitIndex();
		int getAttacksHolder();
		double getAttacksPriority();
		boolean isOnGround();
		byte getPlayerDir();
		byte getDirFacing();
		byte getTeam();
		boolean canFinalSmash();
		void setPlayerDir(byte dir);
		byte getPlayerNo();
		boolean CanDo();
		boolean isGrabbed();
		int getStock();
		boolean hasGrabbed();
		boolean isGrabbing();
		boolean isJumping();
		boolean isHanging();
		int getSmashPower();
		byte getMoveLeft();
		byte getMoveRight();
		WireframeActor*getHitbox();
		void setIndicatorOffset(float x1, float y1);
		String getFolderPath();
		void checkAttacks();
		boolean pickUpItem(Item*item);

		boolean hitboxRectsColliding(HitBox*collide);
		boolean hitboxRectsColliding(WireframeActor*collide);
		boolean hitboxRectsColliding(Actor*collide);

		void stand();
		void switchDirection();
		void moveDown();
		virtual void jump();
	};
}