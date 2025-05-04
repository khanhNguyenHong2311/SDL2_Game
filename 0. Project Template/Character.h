#pragma once
#include"HealthBar.h"
#include"Globals.h"
#include"Library.h"
#include"EnemyAZ.h"
#include"EnemyCD.h"
#include"LTexture.h"
#include"Map.h"




typedef struct Motion {
	bool goLeft, goRight, isStanding;

	bool isStandingOnGround;
	
	bool isFallingIntoHole;

	bool isAttacking;

	bool isHurting;

	bool isCollidingWithEnemyCD;

	bool isCollidingWithEnemyAZ;

	bool isCollidingWithEnemyBOSS;

	bool isCollidingWithProjectileAZ;

	bool isCollidingWithProjectileBOSS;

	Motion() {
		goLeft = false;
		goRight = false;
		isStanding = false;

		isStandingOnGround = false;

		isFallingIntoHole = false;

		isAttacking = false;

		isHurting = false;

		isCollidingWithEnemyCD = false;

		isCollidingWithEnemyAZ = false;

		isCollidingWithEnemyBOSS = false;

		isCollidingWithProjectileAZ = false;
		
	}
};

enum Action {
	FACING_LEFT = 0,
	FACING_RIGHT = 1,
	RUN_RIGHT = 2 ,
	RUN_LEFT = 3,
	STAND_RIGHT = 4 ,
	STAND_LEFT =5,
	JUMP_LEFT = 6,
	JUMP_RIGHT = 7,
	ATTACK_RIGHT = 8,
	ATTACK_LEFT = 9,
	HURT_RIGHT = 10,
	HURT_LEFT = 11,
	DEAD_RIGHT = 12,
	DEAD_LEFT = 13,
};


class Character : public LTexture {
private:

	int mPosX , mPosY;

	int mVelX, mVelY;

	Motion typeMotion;

	int frameRun;
	int frameStand;
	int frameJump;
	int frameAttack;
	int frameHurt;
	int frameDeath;

	int isFacing;

	int frameWidth, frameHeight;

	int timeRespawn;

	HealthBar healthBar;

	SDL_Rect frameClipsRunRight[8];
	SDL_Rect frameClipsRunLeft[8];

	SDL_Rect frameClipsStandRight[7];
	SDL_Rect frameClipsStandLeft[7];

	SDL_Rect frameClipsJumpRight[5];
	SDL_Rect frameClipsJumpLeft[5];

	SDL_Rect frameClipsAttackRight[6];
	SDL_Rect frameClipsAttackLeft[6];

	SDL_Rect frameClipsHurtRight[4];
	SDL_Rect frameClipsHurtLeft[4];

	SDL_Rect frameClipsDeadRight[12];
	SDL_Rect frameClipsDeadLeft[12];


public:

	Character();
	~Character() { ; }
	
	void handleMotion(SDL_Event& e);

	void render(SDL_Renderer* renderer);
	
	void setClips();

	void checkMapCollision();

	int getPosX();
	int getPosY();

	void CenterEntityOnMap();

	void FallingInTheHole();

	void checkCharacterCollisionWithEnemy(EnemyCD* pEnemyCD = NULL , EnemyAZ* pEnemyAZ = NULL ,EnemyBOSS* pEnemyBOSS = NULL);

	void checkCharacterCollisionWithProjectile(EnemyAZ* pEnemyAZ = NULL, EnemyBOSS* pEnemyBOSS = NULL);

	void checkCharacterAttackedEnemy(EnemyCD* pEnemyCD = NULL, EnemyAZ* pEnemyAZ = NULL, EnemyBOSS* pEnemyBOSS = NULL);

	void handleDamage(int damage);

	HealthBar& getHealthBar() {
		return healthBar;
	}


};

