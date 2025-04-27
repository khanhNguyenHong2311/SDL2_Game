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

	frameWidth = ENEMIES_WIDTH;
	frameHeight = ENEMIES_HEIGHT;

	frame = 0;
	frameStand = 0;
	frameAttack = 0;

	timeRespawn = 0;

	timeStand = 200;

	limitPosA = 0;
	limitPosB = 0;
}




void Enemies::setClips() {
	if (frameWidth > 0 && frameHeight > 0) {

		for (int i = 0;i < 8;i++) {
			frameClipsAttackRight[i].x = i * frameWidth;
			frameClipsAttackRight[i].y = 0;
			frameClipsAttackRight[i].w = frameWidth;
			frameClipsAttackRight[i].h = frameHeight;

			frameClipsAttackLeft[i].x = (7 - i) * frameWidth;
			frameClipsAttackLeft[i].y = 0;
			frameClipsAttackLeft[i].w = frameWidth;
			frameClipsAttackLeft[i].h = frameHeight;
		}

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

		for (int i = 0;i < 10;i++) {
			frameClipsRunRight[i].x = i * frameWidth;
			frameClipsRunRight[i].y = 0;
			frameClipsRunRight[i].w = frameWidth;
			frameClipsRunRight[i].h = frameHeight;

			frameClipsRunLeft[i].x = (9 - i) * frameWidth;
			frameClipsRunLeft[i].y = 0;
			frameClipsRunLeft[i].w = frameWidth;
			frameClipsRunLeft[i].h = frameHeight;
		}
	}
}


void Enemies::handleMotion() {

	if (typeMotion.goRight) {
		mVelX = ENEMIES_VEL;
	}
	else if (typeMotion.goLeft) {
		mVelX = -ENEMIES_VEL;
	}
	else if (typeMotion.isStanding) {
		mVelX = 0;
	}

	moveToCharacterIfInRange(gMainCharacter.getPosX(), gMainCharacter.getPosY());
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
		isFacing = FACING_RIGHT_E_CD;
	}
	else if (typeMotion.goLeft) {
		isFacing = FACING_LEFT_E_CD;
	}
	
	if (typeMotion.isStandingOnGround) {
		
		
		frame++;
		if (frame / 10 >= 10) frame = 0;


		if (!typeMotion.isColliding) {
			frameAttack = 0;
		}


		if (typeMotion.isColliding) {
			typeMotion.goLeft = false;
			typeMotion.goRight = false;
			frameAttack++;
			if (frameAttack / 8 >=  8) frameAttack = 0;
			if (isFacing == FACING_RIGHT_E_CD) {
				currentTexture = gLoadEnemiesCD[ATTACK_RIGHT_E_CD].getTexture();
				currentClip = &frameClipsAttackRight[frameAttack / 8];
			}
			else if (isFacing == FACING_LEFT_E_CD ) {
				currentTexture = gLoadEnemiesCD[ATTACK_LEFT_E_CD].getTexture();
				currentClip = &frameClipsAttackLeft[frameAttack / 8];
			}
		}
		else if ((mPosX == limitPosB && isFacing == FACING_RIGHT_E_CD) || (mPosX == limitPosA && isFacing == FACING_LEFT_E_CD)) {
			frameStand++;
			if (frameStand / 9 >= 9) frameStand = 0;
			typeMotion.isStanding = true;
			typeMotion.goLeft = false;
			typeMotion.goRight = false;

			timeStand--;
			if (timeStand == 0) {
				typeMotion.isStanding = false;
				typeMotion.goLeft = (mPosX == limitPosB);
				typeMotion.goRight = (mPosX == limitPosA);
				timeStand = 200;
			}
			if (mPosX == limitPosB) {
				currentTexture = gLoadEnemiesCD[STAND_RIGHT_E_CD].getTexture();
				currentClip = &frameClipsStandRight[frameStand / 9];
			}
			else if (mPosX == limitPosA) {
				currentTexture = gLoadEnemiesCD[STAND_LEFT_E_CD].getTexture();
				currentClip = &frameClipsStandLeft[frameStand / 9];
			}
		}

		else if (mPosX > limitPosB) {
			typeMotion.goLeft = true;
			typeMotion.goRight = false;
			currentTexture = gLoadEnemiesCD[RUN_LEFT_E_CD].getTexture();
			currentClip = &frameClipsRunLeft[frame / 10];

		}
		else if (mPosX < limitPosA) {
			typeMotion.goRight = true;
			typeMotion.goLeft = false;
			currentTexture = gLoadEnemiesCD[RUN_RIGHT_E_CD].getTexture();
			currentClip = &frameClipsRunRight[frame / 10];

		}
		else {
			if (isFacing == FACING_LEFT) {
				typeMotion.goLeft = true;
				typeMotion.goRight = false;
				currentTexture = gLoadEnemiesCD[RUN_LEFT_E_CD].getTexture();
				currentClip = &frameClipsRunLeft[frame / 10];
			}
			else {
				typeMotion.goRight = true;
				typeMotion.goLeft = false;
				currentTexture = gLoadEnemiesCD[RUN_RIGHT_E_CD].getTexture();
				currentClip = &frameClipsRunRight[frame / 10];
			}
		}
	}

	else {
		if (isFacing == FACING_LEFT) {
			typeMotion.goLeft = true;
			typeMotion.goRight = false;
			currentTexture = gLoadEnemiesCD[RUN_LEFT_E_CD].getTexture();
			currentClip = &frameClipsRunLeft[frame / 10];
		}
		else {
			typeMotion.goRight = true;
			typeMotion.goLeft = false;
			currentTexture = gLoadEnemiesCD[RUN_RIGHT_E_CD].getTexture();
			currentClip = &frameClipsRunRight[frame / 10];
		}
	}


	SDL_Rect renderQuad = { mPosX - gGameMap.getCameraX(),mPosY - gGameMap.getCameraY(),currentClip->w,currentClip->h };

	SDL_RenderCopy(renderer, currentTexture, currentClip, &renderQuad);
}


void Enemies::checkEnemyCollisionWithCharacter(int characterPosX , int characterPosY) {

	SDL_Rect enemyCollider = { mPosX + (frameWidth - COLLIDER_WIDTH) / 2,mPosY + (frameHeight - COLLIDER_HEIGHT) / 2, COLLIDER_WIDTH , COLLIDER_HEIGHT };
	SDL_Rect characterCollider = { characterPosX, characterPosY , CHARACTER_WIDTH , CHARACTER_HEIGHT };

	int	rightCharacter = characterCollider.x + characterCollider.w;
	int leftCharacter = characterCollider.x;
	int topCharacter = characterCollider.y;
	int bottomCharacter = characterCollider.y + characterCollider.h;


	int	rightEnemy = enemyCollider.x + enemyCollider.w;
	int leftEnemy = enemyCollider.x;
	int topEnemy = enemyCollider.y;
	int bottomEnemy = enemyCollider.y + enemyCollider.h;

	if ((bottomCharacter <= topEnemy) || (topCharacter >= bottomEnemy) || (rightCharacter <= leftEnemy) || (leftCharacter >= rightEnemy)) {
		typeMotion.isColliding = false;
	}
	else {
		typeMotion.isColliding = true;
	}
}



void Enemies::moveToCharacterIfInRange(int characterPosX, int characterPosY) {
	int enemyRow = mPosY / TILE_SIZE + 1;
	int characterRow = characterPosY / TILE_SIZE;

	if (!typeMotion.isChasing) {
		if (characterPosX >= limitPosA && characterPosX <= limitPosB && enemyRow == characterRow) {
			typeMotion.isChasing = true;
		}
	}

	if (typeMotion.isChasing) {

		if (typeMotion.isColliding) {
			mVelX = 0; 
		}
		else if (characterPosX > mPosX) {
			typeMotion.goRight = true;
			typeMotion.goLeft = false;
			mVelX = 3 * ENEMIES_VEL;
		}
		else if (characterPosX < mPosX) {
			typeMotion.goRight = false;
			typeMotion.goLeft = true;
			mVelX = -3 * ENEMIES_VEL;
		}
	}

	if (characterPosX < limitPosA || characterPosX > limitPosB || enemyRow != characterRow) {
		typeMotion.isChasing = false;
	}
}

void Enemies::FallingInTheHole() {
	if (!typeMotion.isFallingIntoHole && mPosY > gGameMap.getMaxMapY()) {
		typeMotion.isFallingIntoHole = true;
		timeRespawn = 30;
		isFacing = FACING_LEFT;
	}
}



void Enemies::setLimitPos(int limitposa, int limitposb) {
	limitPosA = limitposa;
	limitPosB = limitposb;
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