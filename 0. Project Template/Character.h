#pragma once
#include"Globals.h"
#include"Library.h"
#include"LTexture.h"
#include"Map.h"

#define CHARACTER_WIDTH 80
#define CHARACTER_HEIGHT 80

#define CHARACTER_VEL 8
#define CHARACTER_VEL_JUMP 22


#define GRAVITY_SPEED 1
#define MAX_GRAVITY_SPEED 10


typedef struct Motion {
	bool goUp, goDown, goLeft, goRight ,isStanding ,isStandingOnGround ,attack;
	Motion() {
		goUp = false;
		goDown = false;
		goLeft = false;
		goRight = false;
		isStanding = false;
		isStandingOnGround = false;
		attack = false;
	}
};

enum status {
	FACING_LEFT = 0,
	FACING_RIGHT = 1,
	RUN_RIGHT = 2 ,
	RUN_LEFT = 3,
	STAND_RIGHT = 4 ,
	STAND_LEFT =5,
};


class Character : public LTexture {
private:

	int mPosX , mPosY;

	int mVelX, mVelY;

	int isFacing;

	Motion typeMotion;

	int frame;

	int frameStand;

	int frameWidth, frameHeight;

	SDL_Rect frameClipsRunRight[8];
	SDL_Rect frameClipsRunLeft[8];

	SDL_Rect frameClipsStandRight[7];
	SDL_Rect frameClipsStandLeft[7];

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
	void Respawn();

};

