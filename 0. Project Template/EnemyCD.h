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
	}
};


enum statusE_CD {
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
	HURT_LEFT_E_CD =11
};



class EnemyCD  {
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

	int isFacing;

	int timeRespawn;

	int timeStand;

	MotionE_CD typeMotion;

	SDL_Rect frameClipsStandRight[9];
	SDL_Rect frameClipsStandLeft[9];

	SDL_Rect frameClipsRunRight[10];
	SDL_Rect frameClipsRunLeft[10];

	SDL_Rect frameClipsAttackRight[8];
	SDL_Rect frameClipsAttackLeft[8];

	SDL_Rect frameClipsHurtRight[5];
	SDL_Rect frameClipsHurtLeft[5];

	int limitPosA;
	int limitPosB;


};