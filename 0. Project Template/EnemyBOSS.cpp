#include"Library.h"
#include"Globals.h"
#include"LTexture.h"
#include"EnemyBOSS.h"
#include"EnemyCD.h"
#include"Projectile.h"





EnemyBOSS::EnemyBOSS() {
	mPosX = 0;
	mPosY = 0;

	mVelX = 0;
	mVelY = 0;

	isFacing = FACING_LEFT_E_BOSS;

	typeMotion.goLeft = true;

	frameWidth = ENEMY_BOSS_WIDTH;
	frameHeight = ENEMY_BOSS_HEIGHT;

	frameRun = 0;
	frameStand = 0;
	frameAttack = 0;
	frameHurt = 0;
	frameDeath = 0;

	timeStand = 60;

	timeCoolDownAttack = 20;

	limitPosA = 0;
	limitPosB = 0;
}


void EnemyBOSS::handleDamage(int damage) {
	int newHealth = healthBar.getCurrentHealth() - damage;
	healthBar.setHealth(newHealth);
	typeMotion.isHurting = true;
}


void EnemyBOSS::setClips() {
	if (frameWidth > 0 && frameHeight > 0) {


		for (int i = 0;i < 5;i++) {
			frameClipsDeadRight[i].x = i * frameWidth;
			frameClipsDeadRight[i].y = 0;
			frameClipsDeadRight[i].w = frameWidth;
			frameClipsDeadRight[i].h = frameHeight;

			frameClipsDeadLeft[i].x = (4 - i) * frameWidth;
			frameClipsDeadLeft[i].y = 0;
			frameClipsDeadLeft[i].w = frameWidth;
			frameClipsDeadLeft[i].h = frameHeight;
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

			frameClipsAttackRight[i].x = i * frameWidth;
			frameClipsAttackRight[i].y = 0;
			frameClipsAttackRight[i].w = frameWidth;
			frameClipsAttackRight[i].h = frameHeight;

			frameClipsAttackLeft[i].x = (3 - i) * frameWidth;
			frameClipsAttackLeft[i].y = 0;
			frameClipsAttackLeft[i].w = frameWidth;
			frameClipsAttackLeft[i].h = frameHeight;

		}


		for (int i = 0;i < 3;i++) {
			frameClipsRunRight[i].x = i * frameWidth;
			frameClipsRunRight[i].y = 0;
			frameClipsRunRight[i].w = frameWidth;
			frameClipsRunRight[i].h = frameHeight;

			frameClipsRunLeft[i].x = (2 - i) * frameWidth;
			frameClipsRunLeft[i].y = 0;
			frameClipsRunLeft[i].w = frameWidth;
			frameClipsRunLeft[i].h = frameHeight;
		}
	}
}


void EnemyBOSS::handleMotion() {

	if (typeMotion.goRight) {	
		mVelX = ENEMY_BOSS_VEL;
	}
	else if (typeMotion.goLeft) {
		mVelX = -ENEMY_BOSS_VEL;
	}
	else if (typeMotion.isStanding) {
		mVelX = 0;
	}
	moveToCharacterIfInRange(gMainCharacter.getPosX(), gMainCharacter.getPosY());
}



void EnemyBOSS::checkMapCollision() {

	if (healthBar.getCurrentHealth() > 0) {
		mVelY += ENEMY_BOSS_GRAVITY_SPEED;
		if (mVelY > ENEMY_BOSS_MAX_GRAVITY_SPEED) {
			mVelY = ENEMY_BOSS_MAX_GRAVITY_SPEED;
		}
	}
	else {
		mVelY += 1;
		if (mVelY >= 5) {
			mVelY = 5;
		}
	}


	int x1 = (mPosX + mVelX) / TILE_SIZE;
	int x2 = (mPosX + mVelX + frameWidth - 1) / TILE_SIZE;

	int y1 = mPosY / TILE_SIZE;
	int y2 = (mPosY + frameHeight - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
		if (mVelX > 0) {
			if (gGameMap.getValueOfTile(y1, x2) != TILE_EMPTY || gGameMap.getValueOfTile(y2, x2) != TILE_EMPTY) {
				mPosX = x2 * TILE_SIZE - frameWidth - ENEMY_BOSS_VEL;
				mVelX = ENEMY_BOSS_VEL;
			}
		}
		else if (mVelX < 0) {
			if (gGameMap.getValueOfTile(y1, x1) != TILE_EMPTY || gGameMap.getValueOfTile(y2, x1) != TILE_EMPTY) {
				mPosX = (x1 + 1) * TILE_SIZE + ENEMY_BOSS_VEL;
				mVelX = -ENEMY_BOSS_VEL;
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



void EnemyBOSS::checkEnemyCollisionWithCharacter(int characterPosX, int characterPosY) {

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

// Useless
void EnemyBOSS::checkEnemyAttackedCharacter() {

	int rightCharacter = gMainCharacter.getPosX() + CHARACTER_WIDTH;
	int rightEnemyCD = mPosX + (ENEMY_CD_WIDTH) * 3 / 4;

	if (isFacing == FACING_RIGHT_E_CD && (frameAttack / 8 == 6) && (rightCharacter >= rightEnemyCD)) gMainCharacter.handleDamage(ENEMY_BOSS_DAMAGE);
	else if (isFacing == FACING_LEFT_E_CD && (frameAttack / 8 == 6) && (rightCharacter <= rightEnemyCD)) gMainCharacter.handleDamage(ENEMY_BOSS_DAMAGE);
}



void EnemyBOSS::createProjectile(SDL_Renderer* renderer) {
	Projectile* pProjectile = new Projectile();
	pProjectile->setClips();

	float projectileStartX = 0;
	float projectileStartY = 0;
	if (isFacing == FACING_RIGHT_E_BOSS) {
		projectileStartX = mPosX + frameWidth - 20.0f;
		projectileStartY = mPosY + 100.0f;
	}
	else {
		projectileStartX = mPosX;
		projectileStartY = mPosY + 100.0f;
	}

	pProjectile->setPosX(projectileStartX);
	pProjectile->setPosY(projectileStartY);

	float targetX = gMainCharacter.getPosX() + CHARACTER_WIDTH / 2.0f;
	float targetY = gMainCharacter.getPosY() + CHARACTER_HEIGHT / 2.0f;

	float deltaX = targetX - projectileStartX;
	float deltaY = targetY - projectileStartY;

	float distance = sqrt(deltaX * deltaX + deltaY * deltaY);
	if (distance == 0.0f) distance = 1.0f;


	float unitVelX = PROJECTILE_FIRE_BALL_VEL * (deltaX / distance);
	float unitVelY = PROJECTILE_FIRE_BALL_VEL * (deltaY / distance);

	pProjectile->setVelX(unitVelX);
	pProjectile->setVelY(unitVelY);

	float angle = atan2(unitVelY, unitVelX) * 180.0f / M_PI;

	pProjectile->setRotationAngle(angle);

	pProjectile->setIsMoving(true);

	ProjectileList.push_back(pProjectile);
}



void EnemyBOSS::handleAndRenderProjectile(SDL_Renderer* renderer) {
	for (int i = 0;i < ProjectileList.size();i++) {
		Projectile* pProjectile = ProjectileList[i];
		if (pProjectile != NULL) {
			if (pProjectile->getIsMoving() || (pProjectile->getTypeMotion().isExploding)) {
				pProjectile->handleMotion(SCREEN_WIDTH + gGameMap.getCameraX(), SCREEN_HEIGHT);
				pProjectile->renderProjectile(renderer);
			}
			else {
				ProjectileList.erase(ProjectileList.begin() + i);
				if (pProjectile != NULL) {
					delete pProjectile;
					pProjectile = NULL;
				}
			}
		}
	}
}



void EnemyBOSS::moveToCharacterIfInRange(int characterPosX, int characterPosY) {

	int attackRangeA = mPosX + frameWidth / 2 - 500;
	int attackRangeB = mPosX + frameWidth / 2 + 500;
	if (!typeMotion.isChasing) {
		if (characterPosX > limitPosA - 500 && characterPosX < limitPosB + 500) {
			typeMotion.isChasing = true;
		}
	}

	if (typeMotion.isChasing) {
		if (characterPosX >= attackRangeA && characterPosX <= attackRangeB) {
			if (timeCoolDownAttack == 0) {
				typeMotion.isAttacking = true;

				frameAttack++;

				if (frameAttack / 6 >= 4) {
					frameAttack = 0;
					typeMotion.isAttacking = false;
					timeCoolDownAttack = 20;
					typeMotion.hasShot = false;
				}
			}
			else {
				timeCoolDownAttack--;
				typeMotion.isAttacking = false;
				frameAttack = 0;
			}

			mVelX = 0;
			if (characterPosX <= mPosX + frameWidth / 2) {
				typeMotion.goRight = false;
				typeMotion.goLeft = true;
			}
			else {
				typeMotion.goRight = true;
				typeMotion.goLeft = false;
			}
		}
		else {
			typeMotion.isAttacking = false;
			frameAttack = 0;

			if (characterPosX <= attackRangeA) {
				typeMotion.goRight = false;
				typeMotion.goLeft = true;
				mVelX = -2 * ENEMY_BOSS_VEL;
			}
			else if (characterPosX >= attackRangeB) {
				typeMotion.goRight = true;
				typeMotion.goLeft = false;
				mVelX = 2 * ENEMY_BOSS_VEL;
			}
		}
	}
	if (characterPosX < limitPosA - 500 || characterPosX > limitPosB + 500) {
		typeMotion.isChasing = false;
		typeMotion.isAttacking = false;
		frameAttack = 0;
	}
}




void EnemyBOSS::render(SDL_Renderer* renderer) {

	SDL_Rect* currentClip = nullptr;

	SDL_Texture* currentTexture = nullptr;

	// Use for all typeMotion
	if (typeMotion.goRight) {
		isFacing = FACING_RIGHT_E_BOSS;
	}
	else if (typeMotion.goLeft) {
		isFacing = FACING_LEFT_E_BOSS;
	}



	frameRun++;
	if (frameRun / 5 >= 3) frameRun = 0;
	if (healthBar.getCurrentHealth() > 0) {

		if (typeMotion.gotHitByCharacter) {
			frameHurt++;
			if (frameHurt / 4 >= 4) {
				handleDamage(CHARACTER_DAMAGE);
				frameHurt = 0;
				typeMotion.gotHitByCharacter = false;
			}
			if (isFacing == FACING_LEFT_E_BOSS) {
				currentTexture = gLoadEnemiesBOSS[HURT_LEFT_E_BOSS].getTexture();
				currentClip = &frameClipsHurtRight[frameHurt / 4];
			}
			else if (isFacing == FACING_RIGHT_E_BOSS) {
				currentTexture = gLoadEnemiesBOSS[HURT_RIGHT_E_BOSS].getTexture();
				currentClip = &frameClipsHurtLeft[frameHurt / 4];
			}
		}
		else if (typeMotion.isAttacking) {
			if (!typeMotion.hasShot) {
				createProjectile(renderer);
				typeMotion.hasShot = true;
			}
			if (isFacing == FACING_RIGHT_E_BOSS) {
				currentTexture = gLoadEnemiesBOSS[ATTACK_RIGHT_E_BOSS].getTexture();
				currentClip = &frameClipsAttackRight[frameAttack / 6];
			}
			else if (isFacing == FACING_LEFT_E_BOSS) {
				currentTexture = gLoadEnemiesBOSS[ATTACK_LEFT_E_BOSS].getTexture();
				currentClip = &frameClipsAttackLeft[frameAttack / 6];
			}

		}
		else if (!typeMotion.isChasing) {
			if ((mPosX >= limitPosB && isFacing == FACING_RIGHT_E_BOSS) || (mPosX <= limitPosA && isFacing == FACING_LEFT_E_BOSS)) {
				typeMotion.isStanding = true;
				typeMotion.goLeft = false;
				typeMotion.goRight = false;
				timeStand--;
				if (timeStand == 0) {
					typeMotion.isStanding = false;
					typeMotion.goLeft = (mPosX >= limitPosB);
					typeMotion.goRight = (mPosX <= limitPosA);
					timeStand = 60;
				}
				if (mPosX >= limitPosB) {
					currentTexture = gLoadEnemiesBOSS[RUN_RIGHT_E_BOSS].getTexture();
					currentClip = &frameClipsRunRight[frameRun / 5];
				}
				else if (mPosX <= limitPosA) {
					currentTexture = gLoadEnemiesBOSS[RUN_LEFT_E_BOSS].getTexture();
					currentClip = &frameClipsRunLeft[frameRun / 5];
				}
			}

			else if (mPosX > limitPosB) {
				typeMotion.goLeft = true;
				typeMotion.goRight = false;
				currentTexture = gLoadEnemiesBOSS[RUN_LEFT_E_BOSS].getTexture();
				currentClip = &frameClipsRunLeft[frameRun / 5];

			}
			else if (mPosX < limitPosA) {
				typeMotion.goRight = true;
				typeMotion.goLeft = false;
				currentTexture = gLoadEnemiesBOSS[RUN_RIGHT_E_BOSS].getTexture();
				currentClip = &frameClipsRunRight[frameRun / 5];
			}
			else {
				if (isFacing == FACING_RIGHT_E_BOSS) {
					currentTexture = gLoadEnemiesBOSS[RUN_RIGHT_E_BOSS].getTexture();
					currentClip = &frameClipsRunRight[frameRun / 5];
				}
				else {
					currentTexture = gLoadEnemiesBOSS[RUN_LEFT_E_BOSS].getTexture();
					currentClip = &frameClipsRunLeft[frameRun / 5];
				}
			}
		}
		else {
			if (isFacing == FACING_RIGHT_E_BOSS) {
				currentTexture = gLoadEnemiesBOSS[RUN_RIGHT_E_BOSS].getTexture();
				currentClip = &frameClipsRunRight[frameRun / 5];
			}
			else {
				currentTexture = gLoadEnemiesBOSS[RUN_LEFT_E_BOSS].getTexture();
				currentClip = &frameClipsRunLeft[frameRun / 5];
			}
		}
		healthBar.render(renderer, mPosX - gGameMap.getCameraX(), mPosY - 10 - -gGameMap.getCameraY());
	}
	else {

		if (frameDeath / 4 <= 5) {
			frameDeath++;
		}

		if (isFacing == FACING_RIGHT_E_BOSS) {
			currentTexture = gLoadEnemiesBOSS[DEAD_RIGHT_E_BOSS].getTexture();
			currentClip = &frameClipsDeadRight[frameDeath / 5];
		}
		else {
			currentTexture = gLoadEnemiesBOSS[DEAD_LEFT_E_BOSS].getTexture();
			currentClip = &frameClipsDeadLeft[frameDeath / 5];
		}
	}



	SDL_Rect renderQuad = { mPosX - gGameMap.getCameraX(),mPosY - gGameMap.getCameraY(),currentClip->w,currentClip->h };

	SDL_RenderCopy(renderer, currentTexture, currentClip, &renderQuad);

	handleAndRenderProjectile(renderer);

}



void EnemyBOSS::setLimitPos(int limitposa, int limitposb) {
	limitPosA = limitposa;
	limitPosB = limitposb;
}



int EnemyBOSS::getIsFacing() {
	return isFacing;
}

void EnemyBOSS::isHurting() {
	typeMotion.isHurting = true;
}

bool EnemyBOSS::getIsColliding() {
	return typeMotion.isCollidingWithCharacter;
}


void EnemyBOSS::setProjectileList(vector <Projectile*> projectilelist) {
	ProjectileList = projectilelist;
}


vector <Projectile*> EnemyBOSS::getProjectileList() {
	return ProjectileList;
}



void EnemyBOSS::setCameraX(int camerax) {
	cameraX = camerax;
}

void EnemyBOSS::setCameraY(int cameray) {
	cameraY = cameray;
}


void EnemyBOSS::setVelX(int VelX) {
	mVelX = VelX;
}


void EnemyBOSS::setVelY(int VelY) {
	mVelY = VelY;
}


void EnemyBOSS::setPosX(int PosX) {
	mPosX = PosX;
}

void EnemyBOSS::setPosY(int PosY) {
	mPosY = PosY;
}

int EnemyBOSS::getPosX() {
	return mPosX;
}

int EnemyBOSS::getPosY() {
	return mPosY;
}