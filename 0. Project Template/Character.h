#pragma once
#include"Globals.h"
#include"Library.h"
#include"LTexture.h"
 



typedef struct Motion {
	bool goUp, goDown, goLeft, goRight;
	Motion() {
		goUp = false;
		goDown = false;
		goLeft = false;
		goRight = false;
	}
};

enum status {
	FACING_RIGHT = 0,
	FACING_LEFT = 1,
};

class Character : public LTexture {
private:

	int mPosX , mPosY;

	int mVelX, mVelY;

	int isFacing;

	Motion typeMotion;

	int frame;

	int x;


public:
	static const int CHARACTER_WIDTH = 80;
	static const int CHARACTER_HEIGHT = 80;
	static const int CHARACTER_VEL = 10;


	Character();
	~Character() { ; }
	
	void handleMotion(SDL_Event& e);

	void move();
	
	void render(SDL_Renderer* renderer);
	
	int getPosX();
	int getPosY();

};

