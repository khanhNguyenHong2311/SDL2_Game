#include"Library.h"
#include"Globals.h"
#include"EnemyAZ.h"
#include"EnemyBOSS.h"
#include"Projectile.h"

Projectile::Projectile() {
	mVelX = 0;

	mVelY = 0;

	isMoving = false;
	
	frameRun = 0;
	
	frameExplosion = 0;

}

void Projectile:: projectileExploded() {
	isMoving = false;
	typeMotion.isExploding = true;
	mVelX = 0;
	mVelY = 0;
}

void Projectile::checkMapCollision() {

	int x1 = (mPosX + mVelX) / TILE_SIZE;
	int x2 = (mPosX + mVelX + PROJECTILE_FIRE_BALL_WIDTH - 100) / TILE_SIZE;

	int y1 = mPosY / TILE_SIZE;
	int y2 = (mPosY + PROJECTILE_FIRE_BALL_HEIGHT - 100) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
		if (mVelX > 0) {
			if (gGameMap.getValueOfTile(y1, x2) != TILE_EMPTY || gGameMap.getValueOfTile(y2, x2) != TILE_EMPTY) {
				projectileExploded();
			}
		}
		else if (mVelX < 0) {
			if (gGameMap.getValueOfTile(y1, x1) != TILE_EMPTY || gGameMap.getValueOfTile(y2, x1) != TILE_EMPTY) {
				projectileExploded();

			}
		}
	}

	x1 = mPosX / TILE_SIZE;
	x2 = (mPosX + PROJECTILE_FIRE_BALL_WIDTH - 90 ) / TILE_SIZE;


	y1 = (mPosY + mVelY) / TILE_SIZE;
	y2 = (mPosY + mVelY + PROJECTILE_FIRE_BALL_HEIGHT - 90 ) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
		if (mVelY > 0) {
			if (gGameMap.getValueOfTile(y2, x1) != TILE_EMPTY || gGameMap.getValueOfTile(y2, x2) != TILE_EMPTY) {
				projectileExploded();
			}
		}
		else if (mVelY < 0) {
			if (gGameMap.getValueOfTile(y1, x1) != TILE_EMPTY || gGameMap.getValueOfTile(y1, x2) != TILE_EMPTY) {
				projectileExploded();
			}
		}
	}
}


void Projectile::setClips() {

	if (PROJECTILE_FIRE_BALL_WIDTH > 0 && PROJECTILE_FIRE_BALL_HEIGHT > 0) {
		for (int i = 0;i < 33;i++) {
			frameClipsFireBallRun[i].x = i * PROJECTILE_FIRE_BALL_WIDTH;
			frameClipsFireBallRun[i].y = 0;
			frameClipsFireBallRun[i].w = PROJECTILE_FIRE_BALL_WIDTH;
			frameClipsFireBallRun[i].h = PROJECTILE_FIRE_BALL_HEIGHT;
		}

		for (int i = 0;i < 8;i++) {
			frameClipsFireBallExplosion[i].x = i * PROJECTILE_FIRE_BALL_EXPLOSION_WIDTH;
			frameClipsFireBallExplosion[i].y = 0;
			frameClipsFireBallExplosion[i].w = PROJECTILE_FIRE_BALL_EXPLOSION_WIDTH;
			frameClipsFireBallExplosion[i].h = PROJECTILE_FIRE_BALL_EXPLOSION_HEIGHT;
		}
	}
}




void Projectile::handleMotion(int limitX, int limitY) {
	checkMapCollision();
	mPosX+=mVelX;
	mPosY += mVelY;
	if (mPosX > limitX) {
		isMoving = false;
	}
}



void Projectile::renderProjectile(SDL_Renderer* renderer ) {
	SDL_Rect* currentClip = nullptr;

	SDL_Texture* currentTexture = nullptr;

	SDL_Rect renderQuad = { 0,0,0,0 };

	frameRun++;
	if (frameRun / 4 >= 33) frameRun = 0;

	if (typeMotion.isExploding) {
		frameExplosion++;
		if (frameExplosion / 4 >= 8) {
			frameExplosion = 0;
			typeMotion.isExploding = false;
		}
		renderQuad = { mPosX - gGameMap.getCameraX(), mPosY  - gGameMap.getCameraY(), PROJECTILE_FIRE_BALL_EXPLOSION_WIDTH, PROJECTILE_FIRE_BALL_EXPLOSION_HEIGHT };
		currentTexture = gLoadProjectile[FIRE_BALL_EXPLOSION].getTexture();
		currentClip = &frameClipsFireBallExplosion[frameExplosion / 4];
	}
	else {
		renderQuad = { mPosX - PROJECTILE_FIRE_BALL_WIDTH / 2 - gGameMap.getCameraX(), mPosY - PROJECTILE_FIRE_BALL_HEIGHT / 2 - gGameMap.getCameraY(), PROJECTILE_FIRE_BALL_WIDTH, PROJECTILE_FIRE_BALL_HEIGHT };
		currentTexture = gLoadProjectile[FIRE_BALL].getTexture();
		currentClip = &frameClipsFireBallRun[frameRun / 4];
	}

	SDL_RenderCopyEx(renderer, currentTexture, currentClip, &renderQuad,rotationAngle,NULL,SDL_FLIP_NONE);
}

void Projectile::setRotationAngle(float rotationangle) {
	rotationAngle = rotationangle;
}

float Projectile::getRotationAngle() {
	return rotationAngle;
}


	
void Projectile::setVelX(int mvelx) {
	mVelX=mvelx;
}

void Projectile::setVelY(int mvely) {
	mVelY=mvely;
}

int Projectile::getVelX() {
	return mVelX;
}

int Projectile::getVelY() {
	return mVelY;
}

int Projectile::getPosX() {
	return mPosX;
}

int Projectile::getPosY() {
	return mPosY;
}

void Projectile::setPosX(int posx) {
	mPosX = posx;
}

void Projectile::setPosY(int posy) {
	mPosY = posy;
}

void Projectile::setIsMoving(bool ismoving) {
	isMoving=ismoving;
}

bool Projectile::getIsMoving() {
	return isMoving;
}

MotionProjectile Projectile::getTypeMotion() {
	return typeMotion;
}
