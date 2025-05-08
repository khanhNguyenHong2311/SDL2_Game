#pragma once
#include"Library.h"
#include"Globals.h"
#include"LTexture.h"
#include"Character.h"



typedef struct MotionE_CD {
	bool goLeft, goRight, isStanding;

	bool isStandingOnGround;

	bool isFallingIntoHole;

	bool isAttacking;

	bool isChasing;

	bool isCollidingWithCharacter;

	bool isHurting;

	bool gotHitByCharacter;

	MotionE_CD() {
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
	}
};


enum Action_CD {
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

	
	MotionE_CD typeMotion;

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

	int limitPosA;
	int limitPosB;


public:

	EnemyCD();
	~EnemyCD() { ; }

	void setVelX(int VelX);
	void setVelY(int VelY);

	void setPosX(int PosX);
	void setPosY(int PosY);

	int getPosX();
	int getPosY();


	void handleMotion();

	void render(SDL_Renderer* renderer);

	void setClips();

	void checkMapCollision();
	void checkEnemyCollisionWithCharacter(int characterPosX , int characterPosY);
	void checkEnemyAttackedCharacter();

	void FallingInTheHole();

	void setCameraX(int camerax);
	void setCameraY(int cameray);

	void setLimitPos(int limitposa, int limitposb);

	void moveToCharacterIfInRange(int charX, int charY);
	
	int getIsFacing();

	void isHurting();

	bool getIsCollidingWithCharacter();

	void setGotHit(bool value) { typeMotion.gotHitByCharacter = value; }

	bool getGotHit() { return typeMotion.gotHitByCharacter; }

	void handleDamage(int damage);

	HealthBar& getHealthBar() {
		return healthBar;
	}



};