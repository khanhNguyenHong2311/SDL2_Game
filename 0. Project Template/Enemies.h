#pragma once
#include"Library.h"
#include"Globals.h"
#include"LTexture.h"

#define ENEMIES_WIDTH 120
#define ENEMIES_HEIGHT 120

#define ENEMIES_VEL 8

#define ENEMIES_GRAVITY_SPEED 1
#define ENEMIES_MAX_GRAVITY_SPEED 10


typedef struct MotionE {
	bool goLeft, goRight, isStanding;

	bool isStandingOnGround;

	bool isFallingIntoHole;

	bool isAttacking;

	MotionE() {
		goLeft = false;
		goRight = false;
		isStanding = false;

		isStandingOnGround = false;

		isFallingIntoHole = false;

		isAttacking = false;
	}
};


enum statusE {
	FACING_LEFT_E = 0,
	FACING_RIGHT_E = 1,
	RUN_RIGHT_E = 2,
	RUN_LEFT_E = 3,
	STAND_RIGHT_E = 4,
	STAND_LEFT_E = 5,
	JUMP_LEFT_E = 6,
	JUMP_RIGHT_E = 7,
	ATTACK_RIGHT_E = 8,
	ATTACK_LEFT_E = 9
};



class Enemies : public LTexture {
public:
	Enemies();
	~Enemies() { ; }

	void setVelX(int VelX);
	void setVelY(int VelY);

	void setPosX(int PosX);
	void setPosY(int PosY);

	int getPosX();
	int getPosY();


	void handleMotion(SDL_Event& e);

	void render(SDL_Renderer* renderer);

	void setClips();

	void checkMapCollision();

	void FallingInTheHole();

	void setCameraX(int camerax);
	void setCameraY(int cameray);

	void moveTowardsMainCharacter();


private:

	int cameraX;
	int cameraY;

	int frameWidth;
	int frameHeight;

	int mPosX;
	int mPosY;

	int mVelX;
	int mVelY;

	int frame;
	int frameStand;

	int isFacing;

	int timeRespawn;

	MotionE typeMotion;

	SDL_Rect frameClipsStandRight[9];
	SDL_Rect frameClipsStandLeft[9];

	int animationA;
	int animationB;

};