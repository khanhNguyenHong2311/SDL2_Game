#pragma once
#include"Globals.h"
#include"EnemyAZ.h"


enum typeProjectile {
	FIRE_BALL = 0
};

class Projectile  {
private:

	int mVelX;

	int mVelY;

	int mPosX;

	int mPosY;
	
	bool isMoving;

	float rotationAngle;

	int frameRun;

public:

	Projectile();

	~Projectile() { ; }

	void handleMotion(int limitX, int limitY);

	void renderProjectile(SDL_Renderer* renderer);

	void checkMapCollision();

	void setClips();

	void setVelX(int mvelx);

	void setVelY(int mvely);

	void setPosX(int posx);
	
	void setPosY(int posy);

	int getPosX();

	int getPosY();

	int getVelX();

	int getVelY();

	void setRotationAngle(float rotationangle);
	
	float getRotationAngle();

	void setIsMoving(bool ismoving);

	bool getIsMoving();

	SDL_Rect frameClipsFireBallRight[33];
	SDL_Rect frameClipsFireBallLeft[33];
};