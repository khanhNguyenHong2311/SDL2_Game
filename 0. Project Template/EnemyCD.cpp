#include"Library.h"
#include"Globals.h"
#include"LTexture.h"
#include"EnemyCD.h"


void EnemyCD::handleDamage(int damage) {
	int newHealth = healthBar.getCurrentHealth() - damage;
	healthBar.setHealth(newHealth);
	typeMotion.isHurting = true;
}


EnemyCD::EnemyCD() {
	mPosX = 0;
	mPosY = 0;

	mVelX = 0;
	mVelY = 0;

	isFacing = FACING_LEFT;

	frameWidth = ENEMY_CD_WIDTH;
	frameHeight = ENEMY_CD_HEIGHT;

	frameRun = 0;
	frameStand = 0;
	frameAttack = 0;
	frameHurt = 0;
	frameDeath = 0;

	timeRespawn = 0;

	timeStand = 200;

	limitPosA = 0;
	limitPosB = 0;
}




void EnemyCD::setClips() {
	if (frameWidth > 0 && frameHeight > 0) {
		
		for (int i = 0;i < 5;i++) {
			frameClipsHurtRight[i].x = i * frameWidth;
			frameClipsHurtRight[i].y = 0;
			frameClipsHurtRight[i].w = frameWidth;
			frameClipsHurtRight[i].h = frameHeight;

			frameClipsHurtLeft[i].x = (4 - i) * frameWidth;
			frameClipsHurtLeft[i].y = 0;
			frameClipsHurtLeft[i].w = frameWidth;
			frameClipsHurtLeft[i].h = frameHeight;
		}

		for (int i = 0;i < 8;i++) {
			frameClipsAttackRight[i].x = i * frameWidth;
			frameClipsAttackRight[i].y = 0;
			frameClipsAttackRight[i].w = frameWidth;
			frameClipsAttackRight[i].h = frameHeight;

			frameClipsAttackLeft[i].x = (7 - i) * frameWidth;
			frameClipsAttackLeft[i].y = 0;
			frameClipsAttackLeft[i].w = frameWidth;
			frameClipsAttackLeft[i].h = frameHeight;


			frameClipsDeadRight[i].x = i * frameWidth;
			frameClipsDeadRight[i].y = 0;
			frameClipsDeadRight[i].w = frameWidth;
			frameClipsDeadRight[i].h = frameHeight;

			frameClipsDeadLeft[i].x = (7 - i) * frameWidth;
			frameClipsDeadLeft[i].y = 0;
			frameClipsDeadLeft[i].w = frameWidth;
			frameClipsDeadLeft[i].h = frameHeight;

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


void EnemyCD::handleMotion() {

	if (typeMotion.goRight) {
		mVelX = ENEMY_CD_VEL;
	}
	else if (typeMotion.goLeft) {
		mVelX = -ENEMY_CD_VEL;
	}
	else if (typeMotion.isStanding) {
		mVelX = 0;
	}

	moveToCharacterIfInRange(gMainCharacter.getPosX(), gMainCharacter.getPosY());
}



void EnemyCD::checkMapCollision() {

	if (!typeMotion.isFallingIntoHole) {
		typeMotion.isStandingOnGround = false;

		mVelY += ENEMY_CD_GRAVITY_SPEED;
		if (mVelY > ENEMY_CD_MAX_GRAVITY_SPEED) {
			mVelY = ENEMY_CD_MAX_GRAVITY_SPEED;
		}


		int x1 = (mPosX + mVelX) / TILE_SIZE;
		int x2 = (mPosX + mVelX + frameWidth - 1) / TILE_SIZE;

		int y1 = mPosY / TILE_SIZE;
		int y2 = (mPosY + frameHeight - 1) / TILE_SIZE;

		if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
			if (mVelX > 0) {
				if (gGameMap.getValueOfTile(y1, x2) != TILE_EMPTY || gGameMap.getValueOfTile(y2, x2) != TILE_EMPTY) {
					mPosX = x2 * TILE_SIZE - frameWidth - 8;
					mVelX = ENEMY_CD_VEL;
				}
			}
			else if (mVelX < 0) {
				if (gGameMap.getValueOfTile(y1, x1) != TILE_EMPTY || gGameMap.getValueOfTile(y2, x1) != TILE_EMPTY) {
					mPosX = (x1 + 1) * TILE_SIZE + 8;
					mVelX = -ENEMY_CD_VEL;
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



void EnemyCD::render(SDL_Renderer* renderer) {

	SDL_Rect* currentClip = nullptr;

	SDL_Texture* currentTexture = nullptr;

	// Use for all typeMotion
	if (typeMotion.goRight) {
		isFacing = FACING_RIGHT_E_CD;
	}
	else if (typeMotion.goLeft) {
		isFacing = FACING_LEFT_E_CD;
	}

	if (healthBar.getCurrentHealth() > 0) {

		if (typeMotion.isStandingOnGround) {


			frameRun++;
			if (frameRun / 10 >= 10) frameRun = 0;

			if (!typeMotion.isCollidingWithCharacter) frameAttack = 0;

			if (typeMotion.gotHitByCharacter) {
				frameAttack = 0;
				frameHurt++;
				if (frameHurt / 5 >= 5) {
					handleDamage(CHARACTER_DAMAGE);
					frameHurt = 0;
					typeMotion.gotHitByCharacter = false;
				}
				if (isFacing == FACING_LEFT_E_CD) {
					currentTexture = gLoadEnemiesCD[HURT_RIGHT_E_CD].getTexture();
					currentClip = &frameClipsHurtRight[frameHurt / 5];
				}
				else {
					currentTexture = gLoadEnemiesCD[HURT_LEFT_E_CD].getTexture();
					currentClip = &frameClipsHurtLeft[frameHurt / 5];
				}
			}
			else if (typeMotion.isCollidingWithCharacter) {
				typeMotion.goLeft = false;
				typeMotion.goRight = false;
				frameAttack++;
				if (frameAttack / 8 >= 8) frameAttack = 0;
				checkEnemyAttackedCharacter();
				if (isFacing == FACING_RIGHT_E_CD) {
					currentTexture = gLoadEnemiesCD[ATTACK_RIGHT_E_CD].getTexture();
					currentClip = &frameClipsAttackRight[frameAttack / 8];
				}
				else if (isFacing == FACING_LEFT_E_CD) {

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
				currentClip = &frameClipsRunLeft[frameRun / 10];

			}
			else if (mPosX < limitPosA) {
				typeMotion.goRight = true;
				typeMotion.goLeft = false;
				currentTexture = gLoadEnemiesCD[RUN_RIGHT_E_CD].getTexture();
				currentClip = &frameClipsRunRight[frameRun / 10];

			}
			else {
				if (isFacing == FACING_LEFT_E_CD) {
					typeMotion.goLeft = true;
					typeMotion.goRight = false;
					currentTexture = gLoadEnemiesCD[RUN_LEFT_E_CD].getTexture();
					currentClip = &frameClipsRunLeft[frameRun / 10];
				}
				else {
					typeMotion.goRight = true;
					typeMotion.goLeft = false;
					currentTexture = gLoadEnemiesCD[RUN_RIGHT_E_CD].getTexture();
					currentClip = &frameClipsRunRight[frameRun / 10];
				}
			}
		}

		else {
			if (isFacing == FACING_LEFT) {
				typeMotion.goLeft = true;
				typeMotion.goRight = false;
				currentTexture = gLoadEnemiesCD[RUN_LEFT_E_CD].getTexture();
				currentClip = &frameClipsRunLeft[frameRun / 10];
			}
			else {
				typeMotion.goRight = true;
				typeMotion.goLeft = false;
				currentTexture = gLoadEnemiesCD[RUN_RIGHT_E_CD].getTexture();
				currentClip = &frameClipsRunRight[frameRun / 10];
			}
		}
	}
	else {
		mVelX = 0;
		if (frameDeath / 5 <= 8) {
			frameDeath++;
		}

		if (isFacing == FACING_RIGHT_E_CD) {
			currentTexture = gLoadEnemiesCD[DEAD_RIGHT_E_CD].getTexture();
			currentClip = &frameClipsDeadRight[frameDeath / 6];
		}
		else {
			currentTexture = gLoadEnemiesCD[DEAD_LEFT_E_CD].getTexture();
			currentClip = &frameClipsDeadLeft[frameDeath / 6];
		}
	}

	healthBar.render(renderer, mPosX - gGameMap.getCameraX(), mPosY - 10 - -gGameMap.getCameraY());

	SDL_Rect renderQuad = { mPosX - gGameMap.getCameraX(),mPosY - gGameMap.getCameraY(),currentClip->w,currentClip->h };

	SDL_RenderCopy(renderer, currentTexture, currentClip, &renderQuad);

}


void EnemyCD::checkEnemyCollisionWithCharacter(int characterPosX , int characterPosY) {

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
		typeMotion.isCollidingWithCharacter = false;
	}
	else {
		typeMotion.isCollidingWithCharacter = true;
	}
}


void EnemyCD::checkEnemyAttackedCharacter() {

	int rightCharacter = gMainCharacter.getPosX() + CHARACTER_WIDTH;
	int rightEnemyCD = mPosX + (ENEMY_CD_WIDTH) * 3 / 4;

	if (frameAttack == 48 ) {
		if (isFacing == FACING_RIGHT_E_CD && rightCharacter >= rightEnemyCD) {
			gMainCharacter.handleDamage(ENEMY_CD_DAMAGE);
		}
		else if (isFacing == FACING_LEFT_E_CD && rightCharacter <= rightEnemyCD) {
			gMainCharacter.handleDamage(ENEMY_CD_DAMAGE);
		}
	}
}


void EnemyCD::moveToCharacterIfInRange(int characterPosX, int characterPosY) {
	int enemyRow = mPosY / TILE_SIZE + 1;
	int characterRow = characterPosY / TILE_SIZE;
	if (!typeMotion.isChasing) {
		if (characterPosX >= limitPosA && characterPosX <= limitPosB && enemyRow == characterRow) {
			typeMotion.isChasing = true;
		}
	}

	if (typeMotion.isChasing) {

		if (typeMotion.isCollidingWithCharacter) {
			mVelX = 0; 
		}
		else if (characterPosX > mPosX) {
			typeMotion.goRight = true;
			typeMotion.goLeft = false;
			mVelX = 3 * ENEMY_CD_VEL;
		}
		else if (characterPosX < mPosX) {
			typeMotion.goRight = false;
			typeMotion.goLeft = true;
			mVelX = -3 * ENEMY_CD_VEL;
		}
	}

	if (characterPosX < limitPosA || characterPosX > limitPosB || enemyRow != characterRow) {
		typeMotion.isChasing = false;
	}
}

void EnemyCD::FallingInTheHole() {
	if (!typeMotion.isFallingIntoHole && mPosY > gGameMap.getMaxMapY()) {
		typeMotion.isFallingIntoHole = true;
		timeRespawn = 30;
		isFacing = FACING_LEFT_E_CD;
	}
}



void EnemyCD::setLimitPos(int limitposa, int limitposb) {
	limitPosA = limitposa;
	limitPosB = limitposb;
}



int EnemyCD :: getIsFacing() {
	return isFacing;
}

void EnemyCD::isHurting() {
	typeMotion.isHurting = true;
}

bool EnemyCD :: getIsCollidingWithCharacter() {
	return typeMotion.isCollidingWithCharacter;
}


void EnemyCD::setCameraX(int camerax) {
	cameraX = camerax;
}

void EnemyCD:: setCameraY(int cameray) {
	cameraY = cameray;
}


void EnemyCD::setVelX(int VelX) { 
	mVelX = VelX;
}


void EnemyCD::setVelY(int VelY) { 
	mVelY = VelY; 
}


void EnemyCD::setPosX(int PosX) { 
	mPosX = PosX; 
}

void EnemyCD::setPosY(int PosY) { 
	mPosY = PosY; 
}

int EnemyCD::getPosX() { 
	return mPosX;
}

int EnemyCD::getPosY() {
	return mPosY;
}