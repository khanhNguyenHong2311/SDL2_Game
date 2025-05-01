#pragma once
#include"Library.h"
#include"Globals.h"
#include"LTexture.h"
#include"Character.h"
#include"Projectile.h"
#include<vector>


class Projectile;

typedef struct MotionE_AZ {
	bool goLeft, goRight, isStanding;

	bool isAttacking;

	bool isChasing;

	bool isCollidingWithCharacter;

	bool isHurting;

	MotionE_AZ() {
		goLeft = false;
		goRight = false;
		isStanding = false;

		isAttacking = false;

		isChasing = false;

		isCollidingWithCharacter = false;

		isHurting = false;
	}
};


enum statusE_AZ {
	FACING_LEFT_E_AZ = 0,
	FACING_RIGHT_E_AZ = 1,
	RUN_RIGHT_E_AZ = 2,
	RUN_LEFT_E_AZ = 3,
	STAND_RIGHT_E_AZ = 4,
	STAND_LEFT_E_AZ = 5,
	JUMP_LEFT_E_AZ = 6,
	JUMP_RIGHT_E_AZ = 7,
	ATTACK_RIGHT_E_AZ = 8,
	ATTACK_LEFT_E_AZ = 9,
	HURT_RIGHT_E_AZ = 10,
	HURT_LEFT_E_AZ = 11 
};



class EnemyAZ {

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

	int timeCoolDownAttack;

	MotionE_AZ typeMotion;

	SDL_Rect frameClipsStandRight[9];
	SDL_Rect frameClipsStandLeft[9];

	SDL_Rect frameClipsRunRight[5];
	SDL_Rect frameClipsRunLeft[5];

	SDL_Rect frameClipsAttackRight[8];
	SDL_Rect frameClipsAttackLeft[8];

	SDL_Rect frameClipsHurtRight[5];
	SDL_Rect frameClipsHurtLeft[5];

	vector<Projectile*> ProjectileList;

	int limitPosA;
	int limitPosB;

public:

	EnemyAZ();
	~EnemyAZ() { ; }

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


	void handleAndRenderProjectile(SDL_Renderer* renderer );

	void isHurting();

	int getIsFacing();

	bool getIsColliding();

	void setLimitPos(int limitposa, int limitposb);

	void setCameraX(int camerax);
	void setCameraY(int cameray);

};