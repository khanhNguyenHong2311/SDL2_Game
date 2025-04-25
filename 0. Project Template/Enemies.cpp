#include"Library.h"
#include"Globals.h"
#include"LTexture.h"
#include"Enemies.h"



Enemies::Enemies() {
	mPosX = 0;
	mPosY = 0;

	mVelX = 0;
	mVelY = 0;

	isFacing = FACING_LEFT;

	typeMotion.isStanding = true;
	typeMotion.isStandingOnGround = false;

	frameWidth = ENEMIES_WIDTH;
	frameHeight = ENEMIES_HEIGHT;

	frame = 0;

	timeRespawn = 0;
}




void Enemies::setClips() {
	if (frameWidth > 0 && frameHeight > 0) {
		for (int i = 0;i < 9;i++) {
			frameClipsStandRight[i].x = i * frameWidth;
			frameClipsStandRight[i].y = 0;
			frameClipsStandRight[i].w = frameWidth;
			frameClipsStandRight[i].h = frameHeight;

			frameClipsStandLeft[i].x = (8 - i) * frameWidth;
			frameClipsStandLeft[i].y = 0;
			frameClipsStandLeft[i].w = frameWidth;
			frameClipsStandLeft[i].h = frameHeight;
		}
	}
}





void Enemies::checkMapCollision() {

	if (!typeMotion.isFallingIntoHole) {
		typeMotion.isStandingOnGround = false;

		mVelY += ENEMIES_GRAVITY_SPEED;
		if (mVelY > ENEMIES_MAX_GRAVITY_SPEED) {
			mVelY = ENEMIES_MAX_GRAVITY_SPEED;
		}

		int x1 = (mPosX + mVelX) / TILE_SIZE;
		int x2 = (mPosX + mVelX + frameWidth - 1) / TILE_SIZE;

		int y1 = mPosY / TILE_SIZE;
		int y2 = (mPosY + frameHeight - 1) / TILE_SIZE;

		if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
			if (mVelX > 0) {
				if (gGameMap.getValueOfTile(y1, x2) != TILE_EMPTY || gGameMap.getValueOfTile(y2, x2) != TILE_EMPTY) {
					mPosX = x2 * TILE_SIZE - frameWidth - 8;
					mVelX = ENEMIES_VEL;
				}
			}
			else if (mVelX < 0) {
				if (gGameMap.getValueOfTile(y1, x1) != TILE_EMPTY || gGameMap.getValueOfTile(y2, x1) != TILE_EMPTY) {
					mPosX = (x1 + 1) * TILE_SIZE + 8;
					mVelX = -ENEMIES_VEL;
				}
			}
		}

		x1 = mPosX / TILE_SIZE;
		x2 = (mPosX + frameWidth - 1) / TILE_SIZE;

		y1 = (mPosY + mVelY) / TILE_SIZE;
		y2 = (mPosY + mVelY + frameHeight - 1) / TILE_SIZE;

		if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
			if (mVelY > 0) {
				if (gGameMap.getValueOfTile(y2, x1) != TILE_EMPTY || gGameMap.getValueOfTile(y2, x2) != TILE_EMPTY) {
					mPosY = y2 * TILE_SIZE - frameHeight;
					mVelY = 0;
					typeMotion.isStandingOnGround = true;
				}
			}
			else if (mVelY < 0) {
				if (gGameMap.getValueOfTile(y1, x1) != TILE_EMPTY || gGameMap.getValueOfTile(y1, x2) != TILE_EMPTY) {
					mPosY = (y1 + 1) * TILE_SIZE;
					mVelY = 0;
				}
			}
		}


		mPosY += mVelY;
		mPosX += mVelX;

		if (mPosX < 0) {
			mPosX = 0;
		}
		else if (mPosX + frameWidth > gGameMap.getMaxMapX()) {
			mPosX = gGameMap.getMaxMapX() - frameWidth - 1;
		}
	}

	else {
		timeRespawn--;
		if (timeRespawn == 0) {
			mPosX -= 3 * TILE_SIZE;
			mPosY = 0;
			timeRespawn = 30;
			typeMotion.isFallingIntoHole = false;
		}
	}
}



void Enemies::render(SDL_Renderer* renderer) {

	SDL_Rect* currentClip = nullptr;

	SDL_Texture* currentTexture = nullptr;

	// Use for all typeMotion
	if (typeMotion.goRight) {
		isFacing = FACING_RIGHT;
	}
	else if (typeMotion.goLeft) {
		isFacing = FACING_LEFT;
	}
	//
	//if (typeMotion.isAttacking) {
	//	frameAttack++;
	//	if (frameAttack / 6 >= 6) {
	//		frameAttack = 0;
	//		typeMotion.isAttacking = false;
	//	}

	//	if (isFacing == FACING_RIGHT) {
	//		currentTexture = gLoadMainCharacter[ATTACK_RIGHT].getTexture();
	//		currentClip = &frameClipsAttackRight[frameAttack / 6];
	//	}
	//	else {
	//		currentTexture = gLoadMainCharacter[ATTACK_LEFT].getTexture();
	//		currentClip = &frameClipsAttackLeft[frameAttack / 6];
	//	}
	//}

	//else if (!typeMotion.isStandingOnGround) {
	//	typeMotion.isStanding = false;
	//	frameJump++;
	//	if (frameJump / 5 >= 5) { frameJump = 0; }
	//	//if (typeMotion.goRight) {
	//	//	isFacing = FACING_RIGHT;
	//	//}
	//	//else if (typeMotion.goLeft) {
	//	//	isFacing = FACING_LEFT;
	//	//}
	//	if (isFacing == FACING_RIGHT) {
	//		currentTexture = gLoadMainCharacter[JUMP_RIGHT].getTexture();
	//		currentClip = &frameClipsJumpRight[frameJump / 5];
	//	}
	//	else {
	//		currentTexture = gLoadMainCharacter[JUMP_LEFT].getTexture();
	//		currentClip = &frameClipsJumpLeft[frameJump / 5];
	//	}
	//}

	//else if (typeMotion.goRight) {
	//	isFacing = FACING_RIGHT;
	//	typeMotion.isStanding = false;
	//	frame++;
	//	if (frame / 8 >= 8) frame = 0;
	//	currentTexture = gLoadMainCharacter[RUN_RIGHT].getTexture();
	//	currentClip = &frameClipsRunRight[frame / 8];
	//}
	//else if (typeMotion.goLeft) {
	//	isFacing = FACING_LEFT;
	//	typeMotion.isStanding = false;
	//	frame++;
	//	if (frame / 8 >= 8) frame = 0;
	//	currentTexture = gLoadMainCharacter[RUN_LEFT].getTexture();
	//	currentClip = &frameClipsRunLeft[frame / 8];
	//}


	if (1) {
		typeMotion.isStanding = true;
		frameStand++;
		if (frameStand / 9 >= 9) frameStand = 0;

		if (isFacing == FACING_RIGHT) {
			currentTexture = gLoadEnemiesCD[STAND_RIGHT_E].getTexture();
			currentClip = &frameClipsStandRight[frameStand / 9];
		}
		else {
			currentTexture = gLoadEnemiesCD[STAND_LEFT_E].getTexture();
			currentClip = &frameClipsStandLeft[frameStand / 9];
		}
	}


	SDL_Rect renderQuad = { mPosX - gGameMap.getCameraX(),mPosY - gGameMap.getCameraY(),currentClip->w,currentClip->h };

	SDL_RenderCopy(renderer, currentTexture, currentClip, &renderQuad);
}



void Enemies::moveTowardsMainCharacter() {

}



void Enemies::FallingInTheHole() {
	if (!typeMotion.isFallingIntoHole && mPosY > gGameMap.getMaxMapY()) {
		typeMotion.isFallingIntoHole = true;
		timeRespawn = 30;
		isFacing = FACING_LEFT;
	}
}


void Enemies::setCameraX(int camerax) {
	cameraX = camerax;
}

void Enemies:: setCameraY(int cameray) {
	cameraY = cameray;
}


void Enemies::setVelX(int VelX) { 
	mVelX = VelX;
}


void Enemies::setVelY(int VelY) { 
	mVelY = VelY; 
}


void Enemies::setPosX(int PosX) { 
	mPosX = PosX; 
}

void Enemies::setPosY(int PosY) { 
	mPosY = PosY; 
}

int Enemies::getPosX() { 
	return mPosX;
}

int Enemies::getPosY() {
	return mPosY;
}