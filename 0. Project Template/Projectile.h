#pragma once
#include"Globals.h"
#include"EnemyAZ.h"
#include"EnemyBOSS.h"

struct FlagProjectile {
	bool isExploding;

	FlagProjectile() {
		isExploding = false;
	}
};


enum SatusProjectile {
	FIRE_BALL = 0,
	FIRE_BALL_EXPLOSION = 1,
	METEORITE = 3, 
	METEORITE_EXPLOSION = 4 ,
	STAR = 5 , 
	ARROW = 6 , 
	ARROW_EXPLOSION = 7
};

class Projectile  {
private:

	int mVelX, mVelY;

	int mPosX , mPosY;

	int frameWidth, frameHeight;

	int frameExplosionWidth, frameExplosionHeight;
	
	bool isMoving , isExploxing , isWaitingToFall;

	float rotationAngle;

	int frameRun , frameExplosion;

	int timeDelayBeforeFall;

	FlagProjectile typeFlag;

	SDL_Rect frameClipsFireBallRun[33];
	SDL_Rect frameClipsFireBallExplosion[8];

	SDL_Rect frameClipsMeteoriteRun[15];
	SDL_Rect frameClipsMeteoriteExplosion[15];

	SDL_Rect frameClipsStarRun[10];

	SDL_Rect frameClipsArrowRun[14];
	SDL_Rect frameClipsArrowExplosion[13];


public:

	Projectile();

	~Projectile() { ; }

	void setClips();

	void handleMotion(int limitX, int limitY , bool isStar);

	void checkMapCollision();

	void projectileExploded();

	void renderProjectile(SDL_Renderer* renderer , bool isFireBall, bool isMeteorite, bool isStar,bool isArrow);

	void setRotationAngle(float rotationangle);

	void setIsMoving(bool ismoving);

	void setDelayBeforeFall(int delay);

	void setIsWaitingToFall(bool wait);

	void setVelX(int mvelx);

	void setVelY(int mvely);

	void setPosX(int posx);
	
	void setPosY(int posy);

	int getPosX();

	int getPosY();

	int getVelX();

	int getVelY();
	
	float getRotationAngle();

	FlagProjectile& getTypeFlag();

	bool getIsMoving();


};