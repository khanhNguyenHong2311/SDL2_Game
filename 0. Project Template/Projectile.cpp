#include"Library.h"
#include"Globals.h"
#include"EnemyAZ.h"
#include"Projectile.h"

Projectile::Projectile() {
	mVelX = 0;
	mVelY = 0;
	isMoving = false;
	frameRun = 0;
}

void Projectile::checkMapCollision() {

	int x1 = (mPosX + mVelX) / TILE_SIZE;
	int x2 = (mPosX + mVelX + PROJECTILE_FIRE_BALL_WIDTH - 100) / TILE_SIZE;

	int y1 = mPosY / TILE_SIZE;
	int y2 = (mPosY + PROJECTILE_FIRE_BALL_HEIGHT - 100) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
		if (mVelX > 0) {
			if (gGameMap.getValueOfTile(y1, x2) != TILE_EMPTY || gGameMap.getValueOfTile(y2, x2) != TILE_EMPTY) {
				isMoving = false;
			}
		}
		else if (mVelX < 0) {
			if (gGameMap.getValueOfTile(y1, x1) != TILE_EMPTY || gGameMap.getValueOfTile(y2, x1) != TILE_EMPTY) {
				isMoving = false;;
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
				isMoving = false;
			}
		}
		else if (mVelY < 0) {
			if (gGameMap.getValueOfTile(y1, x1) != TILE_EMPTY || gGameMap.getValueOfTile(y1, x2) != TILE_EMPTY) {
				isMoving = false;
			}
		}
	}
}


void Projectile::setClips() {

	if (PROJECTILE_FIRE_BALL_WIDTH > 0 && PROJECTILE_FIRE_BALL_HEIGHT > 0) {
		for (int i = 0;i < 33;i++) {
			frameClipsFireBallRight[i].x = i * PROJECTILE_FIRE_BALL_WIDTH;
			frameClipsFireBallRight[i].y = 0;
			frameClipsFireBallRight[i].w = PROJECTILE_FIRE_BALL_WIDTH;
			frameClipsFireBallRight[i].h = PROJECTILE_FIRE_BALL_HEIGHT;

			frameClipsFireBallLeft[i].x = (32 - i) * PROJECTILE_FIRE_BALL_HEIGHT;
			frameClipsFireBallLeft[i].y = 0;
			frameClipsFireBallLeft[i].w = PROJECTILE_FIRE_BALL_HEIGHT;
			frameClipsFireBallLeft[i].h = PROJECTILE_FIRE_BALL_HEIGHT;
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


	frameRun++;
	if (frameRun / 4 >= 33) frameRun = 0;


	currentTexture = gLoadProjectile[FIRE_BALL].getTexture();
	currentClip = &frameClipsFireBallRight[frameRun / 4];


	SDL_Rect renderQuad = { mPosX - PROJECTILE_FIRE_BALL_WIDTH / 2  - gGameMap.getCameraX(), mPosY - PROJECTILE_FIRE_BALL_HEIGHT / 2  - gGameMap.getCameraY(), PROJECTILE_FIRE_BALL_WIDTH, PROJECTILE_FIRE_BALL_HEIGHT };

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