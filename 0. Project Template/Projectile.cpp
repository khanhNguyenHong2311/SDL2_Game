#include"Library.h"
#include"Globals.h"
#include"EnemyAZ.h"
#include"EnemyBOSS.h"
#include"Projectile.h"

Projectile::Projectile() {
	mVelX = 0;

	mVelY = 0;

	isMoving = false;
	
	frameHeight = PROJECTILE_WIDTH;
	frameWidth = PROJECTILE_HEIGHT;

	frameExplosionWidth = PROJECTILE_EXPLOSION_WIDTH;
	frameExplosionHeight = PROJECTILE_EXPLOSION_HEIGHT;

	frameRun = 0;
	
	frameExplosion = 0;

	timeDelayBeforeFall = 60;

	isWaitingToFall = false;

}


void Projectile::setClips() {

	for (int i = 0;i < 33;i++) {
		frameClipsFireBallRun[i].x = i * frameWidth;
		frameClipsFireBallRun[i].y = 0;
		frameClipsFireBallRun[i].w = frameWidth;
		frameClipsFireBallRun[i].h = frameHeight;
	}

	for (int i = 0;i < 8;i++) {
		frameClipsFireBallExplosion[i].x = i * frameExplosionWidth;
		frameClipsFireBallExplosion[i].y = 0;
		frameClipsFireBallExplosion[i].w = frameExplosionWidth;
		frameClipsFireBallExplosion[i].h = frameExplosionHeight;
	}

	
	for (int i = 0;i < 15;i++) {
		frameClipsMeteoriteRun[i].x = i * frameWidth;
		frameClipsMeteoriteRun[i].y = 0;
		frameClipsMeteoriteRun[i].w = frameWidth;
		frameClipsMeteoriteRun[i].h = frameHeight;

		frameClipsMeteoriteExplosion[i].x = i * frameExplosionWidth;
		frameClipsMeteoriteExplosion[i].y = 0;
		frameClipsMeteoriteExplosion[i].w = frameExplosionWidth;
		frameClipsMeteoriteExplosion[i].h = frameExplosionHeight;
	}

	for (int i = 0;i < 10;i++) {
		frameClipsStarRun[i].x = i * frameWidth;
		frameClipsStarRun[i].y = 0;
		frameClipsStarRun[i].w = frameWidth;
		frameClipsStarRun[i].h = frameHeight;
	}


	for (int i = 0;i < 14;i++) {
		frameClipsArrowRun[i].x = i * frameWidth;
		frameClipsArrowRun[i].y = 0;
		frameClipsArrowRun[i].w = frameWidth;
		frameClipsArrowRun[i].h = frameHeight;
	}

	for (int i = 0;i < 13;i++) {
		frameClipsArrowExplosion[i].x = i * (frameWidth - 20);
		frameClipsArrowExplosion[i].y = 0;
		frameClipsArrowExplosion[i].w = frameWidth - 20;
		frameClipsArrowExplosion[i].h = frameHeight - 20;
	}
}



void Projectile::handleMotion(int limitX, int limitY, bool isStar) {

	if (!isStar) {
		checkMapCollision();
	}

	if (isStar && isWaitingToFall) {
		timeDelayBeforeFall--;
		if (timeDelayBeforeFall <= 0) {
			mVelY = 2 * PROJECTILE_VEL;
			isWaitingToFall = false;
		}
	}

	mPosX += mVelX;
	mPosY += mVelY;
	if (mPosX > limitX + 1000) {
		isMoving = false;
	}
}


void Projectile::checkMapCollision() {

	int x1 = (mPosX + mVelX) / TILE_SIZE;
	int x2 = (mPosX + mVelX + frameWidth - 80) / TILE_SIZE  ;

	int y1 = mPosY / TILE_SIZE;
	int y2 = (mPosY + frameHeight - 100 ) / TILE_SIZE ;
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
	x2 = (mPosX + frameWidth - 90) / TILE_SIZE;


	y1 = (mPosY + mVelY) / TILE_SIZE;
	y2 = (mPosY + mVelY + frameHeight - 90) / TILE_SIZE;

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




void Projectile::projectileExploded() {
	isMoving = false;
	typeFlag.isExploding = true;
	mVelX = 0;
	mVelY = 0;
}


void Projectile::renderProjectile(SDL_Renderer* renderer, bool isFireBall, bool isMeteorite, bool isStar , bool isArrow) {
	SDL_Rect* currentClip = nullptr;

	SDL_Texture* currentTexture = nullptr;

	SDL_Rect renderQuad = { 0,0,0,0 };
	if (isFireBall) {
		frameRun++;
		if (frameRun / 4 >= 33) frameRun = 0;

		if (typeFlag.isExploding) {
			frameExplosion++;
			if (frameExplosion / 4 >= 8) {
				frameExplosion = 0;
				typeFlag.isExploding = false;
			}
			renderQuad = { mPosX - gGameMap.getCameraX(), mPosY - gGameMap.getCameraY(), frameExplosionWidth, frameExplosionHeight };
			currentTexture = gLoadProjectile[FIRE_BALL_EXPLOSION].getTexture();
			currentClip = &frameClipsFireBallExplosion[frameExplosion / 4];
		}
		else {
			renderQuad = { mPosX - frameWidth / 2 - gGameMap.getCameraX(), mPosY - frameHeight / 2 - gGameMap.getCameraY(), frameWidth, frameHeight };
			currentTexture = gLoadProjectile[FIRE_BALL].getTexture();
			currentClip = &frameClipsFireBallRun[frameRun / 4];
		}
	}
	else if (isMeteorite) {
		frameRun++;
		if (frameRun / 4 >= 15) frameRun = 0;
		if (typeFlag.isExploding) {
			frameExplosion++;
			if (frameExplosion / 4 >= 16) {
				frameExplosion = 0;
				typeFlag.isExploding = false;
			}
			renderQuad = { mPosX - gGameMap.getCameraX(), mPosY - gGameMap.getCameraY(), frameExplosionWidth , frameExplosionHeight };
			currentTexture = gLoadProjectile[METEORITE_EXPLOSION].getTexture();
			currentClip = &frameClipsMeteoriteExplosion[frameExplosion / 4];
		}
		else {
			renderQuad = { mPosX - frameWidth / 2 - gGameMap.getCameraX(), mPosY - frameHeight / 2 - gGameMap.getCameraY(), frameWidth, frameHeight };
			currentTexture = gLoadProjectile[METEORITE].getTexture();
			currentClip = &frameClipsMeteoriteRun[frameRun / 4];
		}
	}
	else if (isStar) {
		if (isWaitingToFall) {
			float effectX = mPosX - 100 ;
			float effectY = mPosY + 500;
			gEffects.render(renderer, effectX, effectY, false , true ); // hiệu ứng báo
		}
		frameRun++;
		if (frameRun / 4 >= 10) frameRun = 0;
		renderQuad = { mPosX - frameWidth / 2 - gGameMap.getCameraX(), mPosY - frameHeight / 2 - gGameMap.getCameraY(), frameWidth, frameHeight };
		currentTexture = gLoadProjectile[STAR].getTexture();
		currentClip = &frameClipsStarRun[frameRun / 4];
	}
	else if (isArrow) {
		frameRun++;
		if (frameRun / 4 >= 14) frameRun = 0;
		if (typeFlag.isExploding) {
			frameExplosion++;
			if (frameExplosion / 4 >= 13) {
				frameExplosion = 0;
				typeFlag.isExploding = false;
			}
			renderQuad = { mPosX - gGameMap.getCameraX(), mPosY - gGameMap.getCameraY(), frameExplosionWidth + 36 , frameExplosionHeight + 36 };
			currentTexture = gLoadProjectile[ARROW_EXPLOSION].getTexture();
			currentClip = &frameClipsArrowExplosion[frameExplosion / 4];
		}
		else {
			renderQuad = { mPosX - frameWidth / 2 - gGameMap.getCameraX(), mPosY - frameHeight / 2 - gGameMap.getCameraY(), frameWidth, frameHeight };
			currentTexture = gLoadProjectile[ARROW].getTexture();
			currentClip = &frameClipsArrowRun[frameRun / 4];
		}
	}

	SDL_RenderCopyEx(renderer, currentTexture, currentClip, &renderQuad,rotationAngle,NULL,SDL_FLIP_NONE);
}


void Projectile::setRotationAngle(float rotationangle) {
	rotationAngle = rotationangle;
}

void Projectile::setIsMoving(bool ismoving) {
	isMoving = ismoving;
}

void Projectile::setDelayBeforeFall(int delay) {
	timeDelayBeforeFall = delay; 
}

void Projectile::setIsWaitingToFall(bool wait) {
	isWaitingToFall = wait;
}

	
void Projectile::setVelX(int mvelx) {
	mVelX=mvelx;
}

void Projectile::setVelY(int mvely) {
	mVelY=mvely;
}

void Projectile::setPosX(int posx) {
	mPosX = posx;
}

void Projectile::setPosY(int posy) {
	mPosY = posy;
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

float Projectile::getRotationAngle() {
	return rotationAngle;
}

FlagProjectile& Projectile::getTypeFlag() {
	return typeFlag;
}

bool Projectile::getIsMoving() {
	return isMoving;
}