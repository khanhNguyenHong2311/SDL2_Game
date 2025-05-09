#pragma once
#include"Library.h"
#include"Globals.h"
#include"LTexture.h"
#include"Character.h"
#include"Projectile.h"
#include<vector>


class Projectile;

typedef struct MotionE_BOSS {
	bool goLeft, goRight, isStanding;

	bool isAttacking;

	bool isChasing;

	bool isCollidingWithCharacter;

	bool isHurting;

	bool gotHitByCharacter;

	bool isReturning;

	bool hasSummoned;

	MotionE_BOSS() {
		goLeft = false;
		goRight = false;
		isStanding = false;

		isAttacking = false;

		isChasing = false;

		isCollidingWithCharacter = false;

		isHurting = false;

		gotHitByCharacter = false;

		isReturning = false;

		hasSummoned = false;
	}
};


enum Action_BOSS {
	FACING_LEFT_E_BOSS = 0,
	FACING_RIGHT_E_BOSS = 1,
	RUN_RIGHT_E_BOSS = 2,
	RUN_LEFT_E_BOSS = 3,
	STAND_RIGHT_E_BOSS = 4,
	STAND_LEFT_E_BOSS = 5,
	JUMP_LEFT_E_BOSS = 6,
	JUMP_RIGHT_E_BOSS = 7,
	ATTACK_RIGHT_E_BOSS = 8,
	ATTACK_LEFT_E_BOSS = 9,
	HURT_RIGHT_E_BOSS = 10,
	HURT_LEFT_E_BOSS = 11,
	DEAD_RIGHT_E_BOSS = 12,
	DEAD_LEFT_E_BOSS = 13
};



class EnemyBOSS {

private:

	int cameraX;
	int cameraY;

	int frameWidth;
	int frameHeight;

	int mPosX;
	int mPosY;

	int mVelX;
	int mVelY;

	int frameRun;
	int frameStand;
	int frameAttack;
	int frameHurt;
	int frameDeath;

	int isFacing;

	int timeRespawn;

	int timeStand;

	int timeCoolDownAttack;

	int timeReturn;

	int timeSummonMeteorite; 

	MotionE_BOSS typeMotion;

	HealthBar healthBar;

	SDL_Rect frameClipsRunRight[3];
	SDL_Rect frameClipsRunLeft[3];

	SDL_Rect frameClipsAttackRight[4];
	SDL_Rect frameClipsAttackLeft[4];

	SDL_Rect frameClipsHurtRight[4];
	SDL_Rect frameClipsHurtLeft[4];

	SDL_Rect frameClipsDeadRight[5];
	SDL_Rect frameClipsDeadLeft[5];

	SDL_Rect frameClipsStand[7];


	vector<Projectile*> ProjectileList;

	int limitPosA;
	int limitPosB;

public:

	EnemyBOSS();
	~EnemyBOSS() { ; }

	void setVelX(int VelX);
	void setVelY(int VelY);

	void setPosX(int PosX);
	void setPosY(int PosY);

	int getPosX();
	int getPosY();


	void handleMotion();

	void render(SDL_Renderer* renderer);

	void setClips();

	void setProjectileList(vector <Projectile*> projectilelist);

	vector <Projectile*> getProjectileList();

	void createProjectile(SDL_Renderer* renderer);

	void checkMapCollision();
	void checkEnemyCollisionWithCharacter(int characterPosX, int characterPosY);
	void checkEnemyAttackedCharacter();

	void moveToCharacterIfInRange(int charX, int charY);

	void summonAlly();

	void handleAndRenderProjectile(SDL_Renderer* renderer);

	void isHurting();

	int getIsFacing();

	bool getIsColliding();

	void setLimitPos(int limitposa, int limitposb);

	void setCameraX(int camerax);
	void setCameraY(int cameray);

	void setGotHit(bool value) { typeMotion.gotHitByCharacter = value; }

	bool getGotHit() { return typeMotion.gotHitByCharacter; }

	void handleDamage(float damage);

	HealthBar& getHealthBar() {
		return healthBar;
	}

};