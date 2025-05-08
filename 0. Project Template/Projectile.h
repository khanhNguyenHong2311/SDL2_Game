#pragma once
#include"Globals.h"
#include"EnemyAZ.h"
#include"EnemyBOSS.h"

struct MotionProjectile {
	bool isExploding;

	MotionProjectile() {
		isExploding = false;
	}
};


enum typeProjectile {
	FIRE_BALL = 0,
	FIRE_BALL_EXPLOSION = 1,
	METEORITE = 3, 
	METEORITE_EXPLOSION = 4
};

class Projectile  {
private:
	bool isAZ;

	bool isBOSS;

	int mVelX;

	int mVelY;

	int mPosX;

	int mPosY;
	
	bool isMoving;

	bool isExploxing;

	float rotationAngle;

	int frameRun;

	int frameExplosion;

	MotionProjectile typeMotion;

public:

	Projectile();

	~Projectile() { ; }

	void handleMotion(int limitX, int limitY);

	void renderProjectile(SDL_Renderer* renderer , bool isEnemyAZ , bool isEnemyBOSS  );

	void checkMapCollision();

	void projectileExploded();

	void setClips();

	void setVelX(int mvelx);

	void setVelY(int mvely);

	void setPosX(int posx);
	
	void setPosY(int posy);

	int getPosX();

	int getPosY();

	int getVelX();

	int getVelY();

	void EnemyIs(bool enemy);

	void setRotationAngle(float rotationangle);
	
	float getRotationAngle();

	MotionProjectile getTypeMotion();

	void setIsMoving(bool ismoving);

	bool getIsMoving();

	SDL_Rect frameClipsFireBallRun[33];
	SDL_Rect frameClipsFireBallExplosion[8];

	SDL_Rect frameClipsMeteoriteRun[19];
	SDL_Rect frameClipsMeteoriteExplosion[14];
};