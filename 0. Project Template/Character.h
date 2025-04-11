#pragma once
#include"Library.h"
#include"Globals.h"
#include"LTexture.h"
 
class Character {
private:

	int mPosX , mPosY;

	int mVelX, mVelY;

public:
	static const int CHARACTER_WIDTH = 100;
	static const int CHARACTER_HEIGHT = 100;

	static const int CHARACTER_VEL = 10;
	
	void handleMotion(SDL_Event& e);

	void move();
	
	void render();

	int getPosX();
	int getPosY();

};