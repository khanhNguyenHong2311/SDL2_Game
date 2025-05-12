#pragma once
#include"Library.h"
#include"Globals.h"
#include"LTexture.h"
#include"Character.h"



typedef struct FlagE_CD {
	bool goLeft, goRight, isStanding;

	bool isStandingOnGround;

	bool isFallingIntoHole;

	bool isAttacking;

	bool isChasing;

	bool isCollidingWithCharacter;

	bool isHurting;

	bool gotHitByCharacter;

	bool hasGivenMana; 

	FlagE_CD() {
		goLeft = false;

		goRight = false;

		isStanding = false;

		isStandingOnGround = false;

		isFallingIntoHole = false;

		isAttacking = false;

		isChasing = false;

		isCollidingWithCharacter = false;

		isHurting = false;

		gotHitByCharacter = false;

		hasGivenMana = false;
	}
};


enum StatusE_CD {
	FACING_LEFT_E_CD = 0,
	FACING_RIGHT_E_CD = 1,
	RUN_RIGHT_E_CD = 2,
	RUN_LEFT_E_CD = 3,
	STAND_RIGHT_E_CD = 4,
	STAND_LEFT_E_CD = 5,
	JUMP_LEFT_E_CD = 6,
	JUMP_RIGHT_E_CD = 7,
	ATTACK_RIGHT_E_CD = 8,
	ATTACK_LEFT_E_CD = 9,
	HURT_RIGHT_E_CD = 10,
	HURT_LEFT_E_CD =11,
	DEAD_RIGHT_E_CD = 12,
	DEAD_LEFT_E_CD = 13
};



class EnemyCD  {
private:

	int mPosX, mPosY;

	int mVelX, mVelY;

	int frameWidth, frameHeight;

	int frameRun , frameStand , frameAttack , frameHurt , frameDeath; 

	int isFacing;

	int timeRespawn, timeStand;

	int limitPosA , limitPosB;

	FlagE_CD typeFlag;

	HealthBar healthBar;

	SDL_Rect frameClipsStandRight[9];
	SDL_Rect frameClipsStandLeft[9];

	SDL_Rect frameClipsRunRight[10];
	SDL_Rect frameClipsRunLeft[10];

	SDL_Rect frameClipsAttackRight[8];
	SDL_Rect frameClipsAttackLeft[8];

	SDL_Rect frameClipsHurtRight[5];
	SDL_Rect frameClipsHurtLeft[5];

	SDL_Rect frameClipsDeadRight[8];
	SDL_Rect frameClipsDeadLeft[8];



public:

	EnemyCD();

	~EnemyCD() { ; }

	void setClips();

	void handleMotion();

	void handleDamage(int damage);

	void checkMapCollision();

	void checkEnemyCollisionWithCharacter(int characterPosX , int characterPosY);
	
	void checkEnemyCollisionWithProjectile();
	
	void checkEnemyAttackedCharacter();
	
	void moveToCharacterIfInRange(int charX, int charY);

	void FallingInTheHole();

	void render(SDL_Renderer* renderer);

	void isHurting();

	void setLimitPos(int limitposa, int limitposb);

	void setGotHit(bool value);

	void setVelX(int VelX);

	void setVelY(int VelY);

	void setPosX(int PosX);
	
	void setPosY(int PosY);

	void setHasGivenMana(bool check);

	int getIsFacing();

	bool getIsCollidingWithCharacter();

	bool getGotHit();

	FlagE_CD& getTypeFlag();

	HealthBar& getHealthBar();

	int getPosX();
	
	int getPosY();
};