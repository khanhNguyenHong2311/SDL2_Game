#pragma once
#include"Globals.h"
#include"Library.h"
#include"EnemyCD.h"
#include"LTexture.h"
#include"Map.h"

#define CHARACTER_WIDTH 80
#define CHARACTER_HEIGHT 80

#define CHARACTER_VEL 8
#define CHARACTER_VEL_JUMP 25


#define GRAVITY_SPEED 1
#define MAX_GRAVITY_SPEED 10


typedef struct Motion {
	bool goLeft, goRight, isStanding;

	bool isStandingOnGround;
	
	bool isFallingIntoHole;

	bool isAttacking;

	bool isHurting;

	bool attackSucces;

	bool isCollidingWithEnemyCD;


	Motion() {
		goLeft = false;
		goRight = false;
		isStanding = false;

		isStandingOnGround = false;

		isFallingIntoHole = false;

		isAttacking = false;

		isHurting = false;

		attackSucces = false;

		isCollidingWithEnemyCD = false;
	}
};

enum status {
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


	int isFacing;

	int frameWidth, frameHeight;

	int timeRespawn;

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

	void checkCharacterCollisionWithEnemyCD(int emnemyPosX, int enemyPosY);

	void checkCharacterAttackedEnemyCD(EnemyCD* pEnemyCD);


	void isHurting();

	bool getAttackSuccess() {
		return typeMotion.attackSucces;
	}

	void setAttackSucces(bool check) {
		typeMotion.attackSucces = check;
	}
};

