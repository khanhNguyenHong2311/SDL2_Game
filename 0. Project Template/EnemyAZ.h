#pragma once
#include"Library.h"
#include"Globals.h"
#include"LTexture.h"
#include"Character.h"
#include"Projectile.h"
#include<vector>


class Projectile;

typedef struct FlagE_AZ {
	bool goLeft, goRight, isStanding;

	bool isAttacking;

	bool isChasing;

	bool isCollidingWithCharacter;

	bool isHurting;

	bool isDead;

	bool gotHitByCharacter;

	bool hasGivenMana;
	FlagE_AZ() {
		goLeft = false;

		goRight = false;

		isStanding = false;

		isAttacking = false;

		isChasing = false;

		isCollidingWithCharacter = false;

		isHurting = false;

		gotHitByCharacter = false;

		isDead = false;

		hasGivenMana = false;
	}
};


enum Status_AZ {
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
	HURT_LEFT_E_AZ = 11 ,
	DEAD_RIGHT_E_AZ= 12,
	DEAD_LEFT_E_AZ= 13
};



class EnemyAZ {

private:

	int mPosX, mPosY;

	int mVelX, mVelY;

	int frameWidth, frameHeight;

	int frameRun, frameStand, frameAttack, frameHurt, frameDeath;

	int isFacing;

	int timeRespawn , timeStand , timeCoolDownAttack;

	int limitPosA, limitPosB;

	FlagE_AZ typeFlag;

	HealthBar healthBar;

	vector<Projectile*> ProjectileList;

	SDL_Rect frameClipsStandRight[9];
	SDL_Rect frameClipsStandLeft[9];

	SDL_Rect frameClipsRunRight[5];
	SDL_Rect frameClipsRunLeft[5];

	SDL_Rect frameClipsAttackRight[4];
	SDL_Rect frameClipsAttackLeft[4];

	SDL_Rect frameClipsHurtRight[5];
	SDL_Rect frameClipsHurtLeft[5];

	SDL_Rect frameClipsDeadRight[6];
	SDL_Rect frameClipsDeadLeft[6];


public:

	EnemyAZ();

	~EnemyAZ() { ; }

	void setClips();

	void handleMotion();

	void handleDamage(int damage);

	void checkMapCollision();

	void checkEnemyCollisionWithCharacter(int characterPosX, int characterPosY);

	void checkEnemyCollisionWithProjectile();

	void checkEnemyAttackedCharacter();

	void moveToCharacterIfInRange(int charX, int charY);

	void createProjectile(SDL_Renderer* renderer);

	void handleAndRenderProjectile(SDL_Renderer* renderer);

	void render(SDL_Renderer* renderer);

	void isHurting();

	void setLimitPos(int limitposa, int limitposb);

	void setGotHit(bool value);

	void setVelX(int VelX);

	void setVelY(int VelY);

	void setPosX(int PosX);

	void setPosY(int PosY);

	void setHasGivenMana(bool check);

	void setProjectileList(vector <Projectile*> projectilelist);

	vector <Projectile*> getProjectileList();

	int getIsFacing();

	bool getIsColliding();

	bool getGotHit();

	FlagE_AZ& getTypeFlag();

	HealthBar& getHealthBar();

	int getPosX();

	int getPosY();

};