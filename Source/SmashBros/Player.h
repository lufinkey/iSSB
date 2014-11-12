
#include "GameElement.h"
#include "Game/Stages/StagePieces/OffScreenExplode.h"
#include "Chargebar.h"
#include "Game/Stages/StagePieces/Platform.h"
#include "Game/Stages/StagePieces/HangPoint.h"
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
		friend class Camera;
		friend class CharacterLoader;
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
		boolean skidding;
		boolean tossing;
		byte hurt;
		long hurtTime;
		float moveProgress;
		boolean invincible;
		boolean deflectState;
		
		boolean dropping;
		boolean canDropThrough;
		long dropTime;
		
		boolean canDo;
		
		boolean grabbing;
		boolean holdingPlayer;
		boolean heldByPlayer;
		long grabStartTime;
		Player* grabbedPlayer;
		
		boolean cpu;
		Player*currentEnemy;
		long comboTime;
		byte standardCombo;
		
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
		void setCurrentCollidePlatformActor(byte dir, Platform* actor);
		
		void barrierCollide(byte barrierNo);
		
		void whilePlatformColliding(Platform*collide, byte dir);
		void whileGroundColliding();
		void finishGroundCollide();
		void onHang(HangPoint*collide);
		void whileHanging(HangPoint*collide);
		void finishHang(HangPoint*collide);
		
		void checkPlayerCollision(Player*playr);
		void playerColliding(Player*collide, byte dir);
		void playerHitHandler(Player*collide, byte dir);
		
		void onBorderCollide(byte dir);
		
		void checkAttacks(const String&ignored);
		
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
		byte maxDoubleJumps;
		
		float walkSpeed;
		float runSpeed;
		float fallWalk;
		float fallRun;
		float walkAmount;
		float runAmount;
		float recoverAmount;
		float recoverRunAmount;
		long grabTime;
		
		void addFile(const String&file);
		void loadFile(const String&file);
		
		void setOnGround(boolean toggle);
		void setItemOffset(float x1, float y1);
		void setIndicatorOffset(float x1, float y1);
		
		void setCantDo();
		void setHanging(boolean toggle);
		void setJumping(boolean toggle);
		void resetAttackCollisions();
		void setHitbox(float x1, float y1, int w, int h);
		void showHitboxWireframe(boolean toggle);
		void setHitboxColor(const Color&c);
		void setFolderPath(const String&path);
		
		void addTwoSidedAnimation(const String&name, const String&file, int fps, int rows, int cols);
		void addSingleAnimation(const String&name, const String&file, int fps, int rows, int cols);
		
		void setHangPoint(int x1, int y1);
		void destroyCharge();
		void animFinish();
		void checkAttacks();
		
		void updateGravity();
		void updateFrame();
		void updateMovement();
		void updateHanging();
		void updateHurt();
		void updateDrop();
		void updateAI();
		
		void createProjectile(Projectile*proj);
		void createItem(Item*item);
		
		void causeDamage(Player*collide, int amount);
		void causeHurtLaunch(Player*collide, int xDir, float xAmount, float xMult, int yDir, float yAmount, float yMult);
		void causeHurt(Player*collide, byte dir, int time);
		
		boolean checkItemUse();
		boolean checkItemUseSide();
		boolean checkItemUseUp();
		boolean checkItemUseDown();
		boolean checkItemUseSideSmash(byte stepType);
		boolean checkItemUseUpSmash(byte stepType);
		boolean checkItemUseDownSmash(byte stepType);
		boolean useItem(byte attackType);
		boolean useItemSmash(byte attackType, byte stepType);
		void discardItem();
		void tossItem(byte tossAttackType);
		void grabPlayer(Player*playr);
		void releasePlayer();
		void tossPlayer(byte tossAttackType, float xspeed, float yspeed);
		
		void platformResponse(Platform*collide, byte dir, double multiplier);
		Platform* getCurrentCollidePlatformActor(byte dir);
		
		void addAttackInfo(byte dir, int attackNo, byte playerdir, int damage, long delayTime, int xDir,float xAmount,float xMult,int yDir,float yAmount,float yMult, boolean dirIsPixelBased = true);
		void addAIAttackType(byte attack, byte attacktype, float probability, boolean charge = false);
		
		void jump(float dist1, float dist2);
		void climbUp();
		void climbUpAttack();
		
	public:
		static const byte LEFT = 1;
		static const byte RIGHT = 2;
		
		static const byte STEP_CHARGE = 1;
		static const byte STEP_GO = 2;
		static const byte STEP_FINISH = 3;
		
		static const int CMPDIRPDIR_EQUAL = 1;
		static const int CMPDIRPDIR_OPP = -1;
		static const int CMPDIRPDIR_INVALID = 0;
		
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
		
		virtual boolean onDeflectPlayerDamage(Player*collide, int damage);
		virtual void onDeflectPlayerLaunch(Player*collide, int xDir, float xAmount, float xMult, int yDir, float yAmount, float yMult);
		virtual boolean onDeflectItemCollision(Item*collide, byte dir);
		virtual boolean onDeflectItemDamage(Item*collide, int damage);
		virtual void onDeflectItemLaunch(Item*collide, int xDir, float xAmount, float xMult, int yDir, float yAmount, float yMult);
		virtual boolean onDeflectProjectileCollision(Projectile*collide, byte dir);
		virtual boolean onDeflectProjectileDamage(Projectile*collide, int damage);
		virtual void onDeflectProjectileLaunch(Projectile*collide, int xDir, float xAmount, float xMult, int yDir, float yAmount, float yMult);
		
		virtual void jump();
		virtual void grab();
		
		virtual void onGrab(Player*held);
		virtual void onGrabbed(Player*holder);
		
		virtual void onQueueAttack(byte attackType);
		virtual void onFinishCharge();
		virtual void doChargingAttack(byte button);
		
		virtual void grabAttack();
		virtual void grabAttackSide();
		virtual void grabAttackSwing();
		virtual void grabAttackUp();
		virtual void grabAttackDown();
		
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
		
		void addAnimation(Animation*a);
		void changeTwoSidedAnimation(const String&name, byte direction);
		void changeTwoSidedAnimation(const String&name, byte direction, byte playerdir);
		void setColor(const Color&c);
		
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
		byte getComboNo();
		boolean isOnGround();
		byte getPlayerDir();
		byte getDirFacing();
		byte getTeam();
		boolean canFinalSmash();
		void setPlayerDir(byte dir);
		float getPlayerDirMult();
		static float getPlayerDirMult(byte playerdir);
		String getPlayerDirSuffix();
		static String getPlayerDirSuffix(byte playerdir);
		byte getOppPlayerDir();
		static byte getOppPlayerDir(byte playerdir);
		byte getRelPlayerDir(GameElement*cmp);
		static byte getRelPlayerDir(GameElement*playr, GameElement*cmp);
		static int compareDirPlayerDir(byte dir, byte playerdir);
		byte getPlayerNo();
		boolean CanDo();
		int getStock();
		boolean isJumping();
		boolean isHanging();
		int getSmashPower();
		byte getMoveLeft();
		byte getMoveRight();
		void setPoint(float x, float y);
		Player* getGrabbedPlayer();
		WireframeActor*getHitbox();
		String getFolderPath();
		boolean pickUpItem(Item*item);
		
		boolean hitboxRectsColliding(HitBox*collide);
		boolean hitboxRectsColliding(WireframeActor*collide);
		boolean hitboxRectsColliding(Actor*collide);
		
		void stand();
		void switchDirection();
		void moveDown();
	};
}