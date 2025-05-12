#pragma once
#include"Library.h"
#include"Globals.h"
#include"LTexture.h"
#include"Character.h"
#include"Projectile.h"
#include"Effects.h"
#include<vector>


class Projectile;

typedef struct FlagE_BOSS {
	bool goLeft, goRight, isStanding;

	bool isAttacking;

	bool isChasing;

	bool isCollidingWithCharacter;

	bool isHurting;

	bool gotHitByCharacter;

	bool isReturning;

	bool hasSummonedAlly;

	bool hasSummonedStar;

	bool isPhase2;

	FlagE_BOSS() {
		goLeft = false;

		goRight = false;

		isStanding = false;

		isAttacking = false;

		isChasing = false;

		isCollidingWithCharacter = false;

		isHurting = false;

		gotHitByCharacter = false;

		isReturning = false;

		hasSummonedAlly = false;

		hasSummonedStar = false;

		isPhase2 = false;
	}
};


enum Status_BOSS {
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
	DEAD_LEFT_E_BOSS = 13,

	FACING_LEFT_E_BOSS_PHASE2 = 14,
	FACING_RIGHT_E_BOSS_PHASE2 = 15,
	RUN_RIGHT_E_BOSS_PHASE2 = 16,
	RUN_LEFT_E_BOSS_PHASE2 = 17,
	STAND_RIGHT_E_BOSS_PHASE2 = 18,
	STAND_LEFT_E_BOSS_PHASE2 = 19,
	JUMP_LEFT_E_BOSS_PHASE2 = 20,
	JUMP_RIGHT_E_BOSS_PHASE2 = 21,
	ATTACK_RIGHT_E_BOSS_PHASE2 = 22,
	ATTACK_LEFT_E_BOSS_PHASE2 = 23,
	HURT_RIGHT_E_BOSS_PHASE2 = 24,
	HURT_LEFT_E_BOSS_PHASE2 = 25,
	DEAD_RIGHT_E_BOSS_PHASE2 = 26,
	DEAD_LEFT_E_BOSS_PHASE2 = 27

};



class EnemyBOSS {

private:

	int mPosX, mPosY;

	int mVelX, mVelY;

	int frameWidth, frameHeight;

	int frameRun, frameStand, frameAttack, frameHurt, frameDeath;

	int isFacing;

	int timeRespawn,timeStand , timeCoolDownAttack , timeReturn , timeCoolDownSummonStar , timeDelayBeforeFall;

	int limitPosA, limitPosB;

	FlagE_BOSS typeFlag;

	HealthBar healthBar;

	vector<Projectile*> ProjectileListMeteorite;

	vector<Projectile*> ProjectileListStar;

	SDL_Rect frameClipsRunRight[3];
	SDL_Rect frameClipsRunLeft[3];

	SDL_Rect frameClipsAttackRight[4];
	SDL_Rect frameClipsAttackLeft[4];

	SDL_Rect frameClipsHurtRight[4];
	SDL_Rect frameClipsHurtLeft[4];

	SDL_Rect frameClipsDeadRight[5];
	SDL_Rect frameClipsDeadLeft[5];

	SDL_Rect frameClipsStand[7];


public:

	EnemyBOSS();

	~EnemyBOSS() { ; }


	void setClips();

	void handleMotion();

	void handleDamage(float damage);

	void checkMapCollision();

	void checkEnemyCollisionWithCharacter(int characterPosX, int characterPosY);

	void checkEnemyCollisionWithProjectile();

	void checkEnemyAttackedCharacter();

	void moveToCharacterIfInRange(int charX, int charY);

	void summonAlly();

	void summonStar();

	void createProjectileMeteorite(SDL_Renderer* renderer);

	void createProjectileStar(SDL_Renderer* renderer);

	void handleAndRenderProjectile(SDL_Renderer* renderer);

	void render(SDL_Renderer* renderer);

	void isHurting();

	void setLimitPos(int limitposa, int limitposb);

	void setGotHit(bool value);

	void setVelX(int VelX);

	void setVelY(int VelY);

	void setPosX(int PosX);

	void setPosY(int PosY);

	vector <Projectile*> getProjectileListMeteorite();

	vector<Projectile*> getProjectileListStar();

	int getIsFacing();

	bool getIsColliding();

	bool getGotHit();

	FlagE_BOSS& getTypeFlag();

	HealthBar& getHealthBar();

	int getPosX();

	int getPosY();



};