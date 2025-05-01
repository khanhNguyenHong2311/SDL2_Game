#include"Library.h"
#include"Globals.h"
#include"LTexture.h"
#include"Map.h"
#include"Character.h"


Character::Character() {
	mPosX = 0;
	mPosY = 0;

	mVelX = 0;
	mVelY = 0;

	isFacing = FACING_RIGHT ;

	typeMotion.isStanding = true;
	typeMotion.isStandingOnGround = false;

	typeMotion.attackSuccessCD = false;

	typeMotion.attackSuccessAZ = false;


	frameWidth = CHARACTER_WIDTH;
	frameHeight = CHARACTER_HEIGHT;


	
	frameRun = 0;

	frameStand = 0;

	frameJump = 0;

	frameAttack = 0;

	timeRespawn = 0;
}

void Character::handleMotion(SDL_Event& e) {


	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
		case SDLK_LEFT:mVelX -= CHARACTER_VEL; typeMotion.goLeft = true; break;
		case SDLK_RIGHT:mVelX += CHARACTER_VEL; typeMotion.goRight = true; break;
		case SDLK_UP: 
			if (typeMotion.isStandingOnGround) {
				mVelY = -CHARACTER_VEL_JUMP;
				typeMotion.isStandingOnGround = false;
			}
			break;
		case SDLK_a:typeMotion.isAttacking = true; break;
		}

	}

	else if (e.type == SDL_KEYUP && e.key.repeat == 0) {	
		switch (e.key.keysym.sym) {
		case SDLK_LEFT:mVelX += CHARACTER_VEL; typeMotion.goLeft = false; break;
		case SDLK_RIGHT:mVelX -= CHARACTER_VEL; typeMotion.goRight = false; break;
		}
	}
}

void Character::checkMapCollision() {
	
	if (!typeMotion.isFallingIntoHole) {
		typeMotion.isStandingOnGround = false;

		mVelY += GRAVITY_SPEED;
		if (mVelY > MAX_GRAVITY_SPEED) {
			mVelY = MAX_GRAVITY_SPEED;
		}

		int x1 = (mPosX + mVelX) / TILE_SIZE;
		int x2 = (mPosX + mVelX + frameWidth - 1) / TILE_SIZE;

		int y1 = mPosY / TILE_SIZE;
		int y2 = (mPosY + frameHeight - 1) / TILE_SIZE;

		if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
			if (mVelX > 0) {
				if (gGameMap.getValueOfTile(y1, x2) != TILE_EMPTY || gGameMap.getValueOfTile(y2, x2) != TILE_EMPTY) {
					mPosX = x2 * TILE_SIZE - frameWidth - 8;
					mVelX = CHARACTER_VEL;
				}
			}
			else if (mVelX < 0) {
				if (gGameMap.getValueOfTile(y1, x1) != TILE_EMPTY || gGameMap.getValueOfTile(y2, x1) != TILE_EMPTY) {
					mPosX = (x1 + 1) * TILE_SIZE + 8;
					mVelX = -CHARACTER_VEL;
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




void Character::setClips() {
	
	if (frameWidth > 0 && frameHeight > 0) {
		for (int i = 0;i < 8;i++) {
			frameClipsRunRight[i].x = i * frameWidth;
			frameClipsRunRight[i].y = 0;
			frameClipsRunRight[i].w = frameWidth;
			frameClipsRunRight[i].h = frameHeight;

			frameClipsRunLeft[i].x =(7 - i )* frameWidth ;
			frameClipsRunLeft[i].y = 0;
			frameClipsRunLeft[i].w = frameWidth ;
			frameClipsRunLeft[i].h = frameHeight;
		}	


		for (int i = 0;i < 7;i++) {
			frameClipsStandRight[i].x = i * frameWidth;
			frameClipsStandRight[i].y = 0;
			frameClipsStandRight[i].w = frameWidth ;
			frameClipsStandRight[i].h = frameHeight;

			frameClipsStandLeft[i].x = (6 - i) * frameWidth ;
			frameClipsStandLeft[i].y = 0;
			frameClipsStandLeft[i].w = frameWidth ;
			frameClipsStandLeft[i].h = frameHeight;
		}

		for (int i = 0;i < 6;i++) {
			frameClipsAttackRight[i].x = i * frameWidth;
			frameClipsAttackRight[i].y = 0;
			frameClipsAttackRight[i].w = frameWidth;
			frameClipsAttackRight[i].h = frameHeight;

			frameClipsAttackLeft[i].x = (5 - i) * frameWidth;
			frameClipsAttackLeft[i].y = 0;
			frameClipsAttackLeft[i].w = frameWidth;
			frameClipsAttackLeft[i].h = frameHeight;
		}

		for (int i = 0;i < 5;i++) {
			frameClipsJumpRight[i].x = i * frameWidth;
			frameClipsJumpRight[i].y = 0;
			frameClipsJumpRight[i].w = frameWidth;
			frameClipsJumpRight[i].h = frameHeight;

			frameClipsJumpLeft[i].x = (4 - i) * frameWidth;
			frameClipsJumpLeft[i].y = 0;
			frameClipsJumpLeft[i].w = frameWidth;
			frameClipsJumpLeft[i].h = frameHeight;
		}

		for (int i = 0;i < 4;i++) {
			frameClipsHurtRight[i].x = i * frameWidth;
			frameClipsHurtRight[i].y = 0;
			frameClipsHurtRight[i].w = frameWidth;
			frameClipsHurtRight[i].h = frameHeight;

			frameClipsHurtLeft[i].x = (3 - i) * frameWidth;
			frameClipsHurtLeft[i].y = 0;
			frameClipsHurtLeft[i].w = frameWidth;
			frameClipsHurtLeft[i].h = frameHeight;
		}
	}
}




void Character::checkCharacterCollisionWithEnemy(EnemyCD* pEnemyCD , EnemyAZ* pEnemyAZ ) {

	SDL_Rect enemyCollider = { 0,0,0,0 };
	if (pEnemyCD != NULL) {
		enemyCollider = { pEnemyCD->getPosX() , pEnemyCD->getPosY() , COLLIDER_WIDTH + 40, COLLIDER_HEIGHT };
	}
	else if (pEnemyAZ != NULL) {
		enemyCollider = { pEnemyAZ->getPosX() , pEnemyAZ->getPosY() , COLLIDER_WIDTH + 40, COLLIDER_HEIGHT };

	}

	SDL_Rect characterCollider = { mPosX, mPosY , CHARACTER_WIDTH , CHARACTER_HEIGHT };

	int	rightCharacter = characterCollider.x + characterCollider.w;
	int leftCharacter = characterCollider.x;
	int topCharacter = characterCollider.y;
	int bottomCharacter = characterCollider.y + characterCollider.h;

	int	rightEnemy = enemyCollider.x + enemyCollider.w;
	int leftEnemy = enemyCollider.x;
	int topEnemy = enemyCollider.y;
	int bottomEnemy = enemyCollider.y + enemyCollider.h;


	if (pEnemyCD != NULL) {
		typeMotion.isCollidingWithEnemyCD = !((bottomCharacter <= topEnemy) || (topCharacter >= bottomEnemy) || (rightCharacter <= leftEnemy) || (leftCharacter >= rightEnemy));
	}
	else if (pEnemyAZ != NULL) {
		typeMotion.isCollidingWithEnemyAZ = !((bottomCharacter <= topEnemy) || (topCharacter >= bottomEnemy) || (rightCharacter <= leftEnemy) || (leftCharacter >= rightEnemy));
	}
}

void Character::checkCharacterCollisionWithProjectile( EnemyAZ* pEnemyAZ , EnemyCD* pEnemyCD) {

	SDL_Rect characterCollider = { mPosX, mPosY , CHARACTER_WIDTH , CHARACTER_HEIGHT };

	int	rightCharacter = characterCollider.x + characterCollider.w;
	int leftCharacter = characterCollider.x;
	int topCharacter = characterCollider.y;
	int bottomCharacter = characterCollider.y + characterCollider.h;


	SDL_Rect enemyProjectileRect = { 0,0,0,0 };
	if (pEnemyAZ != NULL) {
		vector<Projectile*> projectileAZ = pEnemyAZ->getProjectileList();
		for (int i = 0;i < projectileAZ.size();i++) {
			Projectile* pProjectile = projectileAZ[i];
			if (pProjectile->getIsMoving()) {
				enemyProjectileRect = { pProjectile->getPosX(),pProjectile->getPosY(),PROJECTILE_FIRE_BALL_WIDTH - 100,PROJECTILE_FIRE_BALL_HEIGHT - 100 };

				int rightEnemyProjectile = enemyProjectileRect.x + enemyProjectileRect.w;
				int leftEnemyProjectile = enemyProjectileRect.x;
				int topEnemyProjectile = enemyProjectileRect.y;
				int bottomEnemyProjectile = enemyProjectileRect.y + enemyProjectileRect.h;

				if (!(bottomCharacter <= topEnemyProjectile || topCharacter >= bottomEnemyProjectile || rightCharacter <= leftEnemyProjectile || leftCharacter >= rightEnemyProjectile)) {
					typeMotion.isHurting = true;
					projectileAZ[i]->setIsMoving(false);
				}
			}
		}
	}
}


void Character::checkCharacterAttackedEnemy(EnemyCD* pEnemyCD, EnemyAZ* pEnemyAZ ) {

	int leftCharacter = mPosX;
	int rightCharacter = mPosX + CHARACTER_WIDTH;


	if (pEnemyCD != NULL) {
		int leftEnemy= pEnemyCD->getPosX();
		int rightEnemy = leftEnemy + ENEMY_CD_WIDTH;

		if (typeMotion.isAttacking == true && ( frameAttack / 6 == 4  ) && typeMotion.isCollidingWithEnemyCD) {
			if (isFacing == FACING_RIGHT) {
				if (pEnemyCD->getIsFacing() == FACING_RIGHT_E_CD) typeMotion.attackSuccessCD = (rightCharacter >= leftEnemy + ENEMY_CD_WIDTH / 2) && (rightCharacter <= rightEnemy + 20);
				else if (pEnemyCD->getIsFacing() == FACING_LEFT_E_CD) typeMotion.attackSuccessCD = (rightCharacter >= leftEnemy) && (rightCharacter <= rightEnemy - 20);
			}
			else if (isFacing == FACING_LEFT) {
				if (pEnemyCD->getIsFacing() == FACING_RIGHT_E_CD) typeMotion.attackSuccessCD = (leftCharacter <= rightEnemy + 20) && (leftCharacter >= leftEnemy + 10);
				else if (pEnemyCD->getIsFacing() == FACING_LEFT_E_CD) typeMotion.attackSuccessCD = (leftCharacter >= leftEnemy - 20) && (leftCharacter <= rightEnemy - 80);
			}
		}
	}
	else if (pEnemyAZ != NULL) {
		int leftEnemy = pEnemyAZ->getPosX();
		int rightEnemy = leftEnemy + ENEMY_AZ_WIDTH;

		if (typeMotion.isAttacking == true && frameAttack / 6 == 4 && typeMotion.isCollidingWithEnemyAZ) {
			if (isFacing == FACING_RIGHT) {
				if (pEnemyAZ->getIsFacing() == FACING_RIGHT_E_AZ) typeMotion.attackSuccessAZ = (rightCharacter >= leftEnemy + ENEMY_CD_WIDTH / 2) && (rightCharacter <= rightEnemy + 20);
				else if (pEnemyAZ->getIsFacing() == FACING_LEFT_E_CD) typeMotion.attackSuccessAZ = (rightCharacter >= leftEnemy) && (rightCharacter <= rightEnemy - 20);
			}
			else if (isFacing == FACING_LEFT) {
				if (pEnemyAZ->getIsFacing() == FACING_RIGHT_E_AZ) typeMotion.attackSuccessAZ = (leftCharacter <= rightEnemy + 20) && (leftCharacter >= leftEnemy + 10);
				else if (pEnemyAZ->getIsFacing() == FACING_LEFT_E_AZ) typeMotion.attackSuccessAZ = (leftCharacter >= leftEnemy - 20) && (leftCharacter <= rightEnemy - 80);
			}
		}
	}
}



void Character::render(SDL_Renderer* renderer) {
	
	SDL_Rect* currentClip = nullptr;

	SDL_Texture* currentTexture = nullptr;
	
	// Use for all typeMotion
	if (typeMotion.goRight) {
		isFacing = FACING_RIGHT;
	}
	else if (typeMotion.goLeft) {
		isFacing = FACING_LEFT;
	}
	

	if (typeMotion.isHurting) {
		frameHurt++;
		if (frameHurt / 4 >= 4) {
			frameHurt = 0;
			frameAttack = 0;
			typeMotion.isHurting = false;
		}
		if (isFacing == FACING_RIGHT) {
			currentTexture = gLoadMainCharacter[HURT_RIGHT].getTexture();
			currentClip = &frameClipsHurtRight[frameHurt / 4];
		}
		else {
			currentTexture = gLoadMainCharacter[HURT_LEFT].getTexture();
			currentClip = &frameClipsHurtLeft[frameHurt / 4];
		}
	}
	else if (typeMotion.isAttacking) {
		frameAttack++;
		if (frameAttack / 6 >= 6) {
			frameAttack = 0;
			typeMotion.isAttacking = false;
		}
		if (isFacing == FACING_RIGHT) {
			currentTexture = gLoadMainCharacter[ATTACK_RIGHT].getTexture();
			currentClip = &frameClipsAttackRight[frameAttack / 6];
		}
		else if (isFacing == FACING_LEFT) {
			currentTexture = gLoadMainCharacter[ATTACK_LEFT].getTexture();
			currentClip = &frameClipsAttackLeft[frameAttack / 6];
		}
	}

	else if (!typeMotion.isStandingOnGround) {
		typeMotion.isStanding = false;
		frameJump++;
		if (frameJump / 5 >= 5) { frameJump = 0; }
		//if (typeMotion.goRight) {
		//	isFacing = FACING_RIGHT;
		//}
		//else if (typeMotion.goLeft) {
		//	isFacing = FACING_LEFT;
		//}
		if (isFacing == FACING_RIGHT) {
			currentTexture = gLoadMainCharacter[JUMP_RIGHT].getTexture();
			currentClip = &frameClipsJumpRight[frameJump / 5];
		}
		else {
			currentTexture = gLoadMainCharacter[JUMP_LEFT].getTexture();
			currentClip = &frameClipsJumpLeft[frameJump / 5];
		}
	}

	else if (typeMotion.goRight) {
		typeMotion.isStanding = false;
		frameRun++;
		if (frameRun / 8 >= 8) frameRun = 0;
		currentTexture = gLoadMainCharacter[RUN_RIGHT].getTexture();
		currentClip = &frameClipsRunRight[frameRun / 8];
	}
	else if (typeMotion.goLeft) {
		typeMotion.isStanding = false;
		frameRun++;
		if (frameRun / 8 >= 8) frameRun = 0;
		currentTexture = gLoadMainCharacter[RUN_LEFT].getTexture();
		currentClip = &frameClipsRunLeft[frameRun / 8];
	}


	else {
		typeMotion.isStanding = true;
		frameStand++;
		if (frameStand / 7 >= 7) frameStand = 0;

		if (isFacing == FACING_RIGHT) {
			currentTexture = gLoadMainCharacter[STAND_RIGHT].getTexture();
			currentClip = &frameClipsStandRight[frameStand / 7];
		}
		else {
			currentTexture = gLoadMainCharacter[STAND_LEFT].getTexture();
			currentClip = &frameClipsStandLeft[frameStand / 7];
		}
	}


	SDL_Rect renderQuad = { mPosX - gGameMap.getCameraX(),mPosY - gGameMap.getCameraY(),currentClip->w,currentClip->h };

	SDL_RenderCopy(renderer, currentTexture, currentClip, &renderQuad);
}


void Character::CenterEntityOnMap() {
	
	gGameMap.setCameraX(mPosX - (SCREEN_WIDTH / 2));
	if (gGameMap.getCameraX() < 0) {
		gGameMap.setCameraX(0);
	}
	else if (gGameMap.getCameraX() + SCREEN_WIDTH >= gGameMap.getMaxMapX()) {
		gGameMap.setCameraX(gGameMap.getMaxMapX() - SCREEN_WIDTH);
	}

	gGameMap.setCameraY(mPosY - (SCREEN_HEIGHT / 2));
	if (gGameMap.getCameraY() < 0) {
		gGameMap.setCameraY(0);
	}
	else if (gGameMap.getCameraY() + SCREEN_HEIGHT >= gGameMap.getMaxMapY()) {
		gGameMap.setCameraY(gGameMap.getMaxMapY()-SCREEN_HEIGHT);
	}

}

void Character::FallingInTheHole() {
	if (!typeMotion.isFallingIntoHole && mPosY > gGameMap.getMaxMapY()) {	
		typeMotion.isFallingIntoHole = true;
		timeRespawn = 30;
		isFacing = FACING_RIGHT;
	}
}



void Character:: isHurting() {
	typeMotion.isHurting = true;
}


bool Character::getAttackSuccessCD() {
	return typeMotion.attackSuccessCD;
}

void Character::setAttackSuccessCD(bool check) {
	typeMotion.attackSuccessCD = check;
}

bool Character::getAttackSuccessAZ() {
	return typeMotion.attackSuccessAZ;
}

void Character::setAttackSuccessAZ(bool check) {
	typeMotion.attackSuccessAZ = check;
}



int Character::getPosX() {
	return mPosX;
}
int Character::getPosY() {
	return mPosY;
}