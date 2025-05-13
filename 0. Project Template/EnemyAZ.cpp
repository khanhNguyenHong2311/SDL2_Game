#include"Library.h"
#include"Globals.h"
#include"LTexture.h"
#include"EnemyAZ.h"
#include"EnemyCD.h"
#include"Projectile.h"





EnemyAZ::EnemyAZ() {
	mPosX = 0;
	mPosY = 0;

	mVelX = 0;
	mVelY = 0;

	isFacing = FACING_LEFT_E_AZ;

	typeFlag.goLeft = true;

	frameWidth = ENEMY_AZ_WIDTH;
	frameHeight = ENEMY_AZ_HEIGHT;

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


void EnemyAZ::setClips() {

	for (int i = 0;i < 6;i++) {
		frameClipsDeadRight[i].x = i * frameWidth;
		frameClipsDeadRight[i].y = 0;
		frameClipsDeadRight[i].w = frameWidth;
		frameClipsDeadRight[i].h = frameHeight;

		frameClipsDeadLeft[i].x = (5 - i) * frameWidth;
		frameClipsDeadLeft[i].y = 0;
		frameClipsDeadLeft[i].w = frameWidth;
		frameClipsDeadLeft[i].h = frameHeight;
	}

	for (int i = 0;i < 5;i++) {
		frameClipsHurtRight[i].x = i * frameWidth;
		frameClipsHurtRight[i].y = 0;
		frameClipsHurtRight[i].w = frameWidth;
		frameClipsHurtRight[i].h = frameHeight;

		frameClipsHurtLeft[i].x = (4 - i) * frameWidth;
		frameClipsHurtLeft[i].y = 0;
		frameClipsHurtLeft[i].w = frameWidth;
		frameClipsHurtLeft[i].h = frameHeight;

		frameClipsRunRight[i].x = i * frameWidth;
		frameClipsRunRight[i].y = 0;
		frameClipsRunRight[i].w = frameWidth;
		frameClipsRunRight[i].h = frameHeight;

		frameClipsRunLeft[i].x = (4 - i) * frameWidth;
		frameClipsRunLeft[i].y = 0;
		frameClipsRunLeft[i].w = frameWidth;
		frameClipsRunLeft[i].h = frameHeight;

	}


	for (int i = 0;i < 4;i++) {
		frameClipsAttackRight[i].x = i * frameWidth;
		frameClipsAttackRight[i].y = 0;
		frameClipsAttackRight[i].w = frameWidth;
		frameClipsAttackRight[i].h = frameHeight;

		frameClipsAttackLeft[i].x = (3 - i) * frameWidth;
		frameClipsAttackLeft[i].y = 0;
		frameClipsAttackLeft[i].w = frameWidth;
		frameClipsAttackLeft[i].h = frameHeight;
	}
}


void EnemyAZ::handleMotion() {

	if (typeFlag.goRight) {
		mVelX = ENEMY_AZ_VEL;
	}
	else if (typeFlag.goLeft) {
		mVelX = -ENEMY_AZ_VEL;
	}
	else if (typeFlag.isStanding) {
		mVelX = 0;
	}
	moveToCharacterIfInRange(gMainCharacter.getPosX(), gMainCharacter.getPosY());
}

void EnemyAZ::handleDamage(int damage) {
	int newHealth = healthBar.getCurrentHealth() - damage;
	healthBar.setHealth(newHealth);
	typeFlag.gotHitByCharacter = true;

}


void EnemyAZ::checkMapCollision() {

	if (healthBar.getCurrentHealth() > 0) {
		mVelY += ENEMY_AZ_GRAVITY_SPEED;
		if (mVelY > ENEMY_AZ_MAX_GRAVITY_SPEED) {
			mVelY = ENEMY_AZ_MAX_GRAVITY_SPEED;
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
				mPosX = x2 * TILE_SIZE - frameWidth - ENEMY_AZ_VEL;
				mVelX = ENEMY_AZ_VEL;
			}
		}
		else if (mVelX < 0) {
			if (gGameMap.getValueOfTile(y1, x1) != TILE_EMPTY || gGameMap.getValueOfTile(y2, x1) != TILE_EMPTY) {
				mPosX = (x1 + 1) * TILE_SIZE + ENEMY_AZ_VEL;
				mVelX = -ENEMY_AZ_VEL;
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



void EnemyAZ::checkEnemyCollisionWithCharacter(int characterPosX, int characterPosY) {

	SDL_Rect enemyCollider = { mPosX + (frameWidth - ENEMY_AZ_COLLIDER_WIDTH) / 2,mPosY + (frameHeight - ENEMY_AZ_COLLIDER_HEIGHT) / 2, ENEMY_AZ_COLLIDER_WIDTH , ENEMY_AZ_COLLIDER_HEIGHT };
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
		typeFlag.isCollidingWithCharacter = false;
	}
	else {
		typeFlag.isCollidingWithCharacter = true;
	}
}


void EnemyAZ::checkEnemyCollisionWithProjectile() {
	SDL_Rect enemyCollider = { mPosX , mPosY , ENEMY_CD_COLLIDER_WIDTH, ENEMY_AZ_COLLIDER_HEIGHT };

	int	rightEnemy = enemyCollider.x + enemyCollider.w;
	int lefttEnemy = enemyCollider.x;
	int toptEnemy = enemyCollider.y;
	int bottomtEnemy = enemyCollider.y + enemyCollider.h;

	SDL_Rect characterProjectileRect = { 0,0,0,0 };
	vector<Projectile*> projectile = gMainCharacter.getProjectileListArrow();
	for (int i = 0;i < projectile.size();i++) {
		Projectile* pProjectile = projectile[i];
		if (pProjectile->getIsMoving()) {
			characterProjectileRect = { pProjectile->getPosX(),pProjectile->getPosY(),PROJECTILE_WIDTH - 100  ,PROJECTILE_HEIGHT - 100 };

			int rightCharacterProjectile = characterProjectileRect.x + characterProjectileRect.w;
			int leftCharacterProjectile = characterProjectileRect.x;
			int topCharacterProjectile = characterProjectileRect.y;
			int bottomCharacterProjectile = characterProjectileRect.y + characterProjectileRect.h;

			if (!(bottomtEnemy <= topCharacterProjectile || toptEnemy >= bottomCharacterProjectile || rightEnemy <= leftCharacterProjectile || lefttEnemy >= rightCharacterProjectile)) {
				typeFlag.gotHitByCharacter = true;
				projectile[i]->setIsMoving(false);
				projectile[i]->projectileExploded();
			}
		}
	}

}



// Useless
void EnemyAZ::checkEnemyAttackedCharacter() {

	int rightCharacter = gMainCharacter.getPosX() + CHARACTER_WIDTH;
	int rightEnemyCD = mPosX + (ENEMY_CD_WIDTH) * 3 / 4;

	if (isFacing == FACING_RIGHT_E_CD && (frameAttack / 8 == 6) && (rightCharacter >= rightEnemyCD)) gMainCharacter.handleDamage(ENEMY_AZ_DAMAGE);
	else if (isFacing == FACING_LEFT_E_CD && (frameAttack / 8 == 6) && (rightCharacter <= rightEnemyCD)) gMainCharacter.handleDamage(ENEMY_AZ_DAMAGE);
}



void EnemyAZ::moveToCharacterIfInRange(int characterPosX, int characterPosY) {

	int attackRangeA = mPosX + frameWidth / 2 - ENEMY_AZ_ATTACK_RANGE;
	int attackRangeB = mPosX + frameWidth / 2 + ENEMY_AZ_ATTACK_RANGE;
	if (!typeFlag.isChasing) {
		if (characterPosX > limitPosA - ENEMY_AZ_ATTACK_RANGE && characterPosX < limitPosB + ENEMY_AZ_ATTACK_RANGE) {
			typeFlag.isChasing = true;
		}
	}

	if (typeFlag.isChasing) {
		if (characterPosX >= attackRangeA && characterPosX <= attackRangeB) {
			if (timeCoolDownAttack == 0) {
				typeFlag.isAttacking = true;
				frameAttack++;
				if (frameAttack / 6 >= 4) frameAttack = 0;
				if (frameAttack == 12) {
					frameAttack = 0;
					typeFlag.isAttacking = false;
					timeCoolDownAttack = 100;
					createProjectile(gRenderer);
				}
			}
			else {
				timeCoolDownAttack--;
				typeFlag.isAttacking = false;
			}

			mVelX = 0;
			if (characterPosX <= mPosX + frameWidth / 2) {
				typeFlag.goRight = false;
				typeFlag.goLeft = true;
			}
			else {
				typeFlag.goRight = true;
				typeFlag.goLeft = false;
			}
		}
		else {
			typeFlag.isAttacking = false;
			frameAttack = 0;

			if (characterPosX <= attackRangeA) {
				typeFlag.goRight = false;
				typeFlag.goLeft = true;
				mVelX = -2 * ENEMY_AZ_VEL;
			}
			else if (characterPosX >= attackRangeB) {
				typeFlag.goRight = true;
				typeFlag.goLeft = false;
				mVelX = 2 * ENEMY_AZ_VEL;
			}
		}
	}
	if (characterPosX < limitPosA - ENEMY_AZ_ATTACK_RANGE || characterPosX > limitPosB + ENEMY_AZ_ATTACK_RANGE) {
		typeFlag.isChasing = false;
		typeFlag.isAttacking = false;
		frameAttack = 0;
	}
}




void EnemyAZ::createProjectile(SDL_Renderer* renderer) {
	int numBullets = 3;


	float projectileStartX = isFacing == FACING_RIGHT_E_BOSS ? mPosX + frameWidth - 20.0f : mPosX;
	float projectileStartY = mPosY + 100.0f;

	float targetX = gMainCharacter.getPosX() + CHARACTER_WIDTH / 2.0f;
	float targetY = gMainCharacter.getPosY() + CHARACTER_HEIGHT / 2.0f;

	float deltaX = targetX - projectileStartX;
	float deltaY = targetY - projectileStartY;

	float distance = sqrt(deltaX * deltaX + deltaY * deltaY);
	if (distance == 0.0f) distance = 1.0f;

	float baseAngle = atan2(deltaY, deltaX);

	for (int i = 0; i < numBullets; ++i) {
		float angleOffSetDegrees = 0.0f;		
		
		angleOffSetDegrees = (i - 1) * 15.0f;

		float angleOffSetRadian = angleOffSetDegrees * M_PI / 180.0f;
		float finalAngle = baseAngle + angleOffSetRadian;

		float velX = PROJECTILE_VEL * cos(finalAngle);
		float velY = PROJECTILE_VEL * sin(finalAngle);

		Projectile* pProjectile = new Projectile();
		pProjectile->setClips();
		pProjectile->setPosX(projectileStartX);
		pProjectile->setPosY(projectileStartY);
		pProjectile->setVelX(velX);
		pProjectile->setVelY(velY);
		pProjectile->setRotationAngle(finalAngle * 180.0f / M_PI);
		pProjectile->setIsMoving(true);

		ProjectileList.push_back(pProjectile);
	}
}




void EnemyAZ::handleAndRenderProjectile(SDL_Renderer* renderer) {
	for (int i = 0; i < ProjectileList.size();) {
		Projectile* pProjectile = ProjectileList[i];
		if (pProjectile != NULL) {
			if (pProjectile->getIsMoving() || pProjectile->getTypeFlag().isExploding) {
				pProjectile->handleMotion(SCREEN_WIDTH + gGameMap.getCameraX(), SCREEN_HEIGHT , false);
				pProjectile->renderProjectile(renderer, true, false,false,false); 
				++i;
			}
			else {
				delete pProjectile;
				pProjectile = NULL;
				ProjectileList.erase(ProjectileList.begin() + i); 
			}
		}
		else {
			++i;
		}
	}
}





void EnemyAZ::render(SDL_Renderer* renderer) {

	SDL_Rect* currentClip = nullptr;

	SDL_Texture* currentTexture = nullptr;

	if (typeFlag.goRight) isFacing = FACING_RIGHT_E_AZ;
	else if (typeFlag.goLeft) isFacing = FACING_LEFT_E_AZ;

	frameRun++;
	if (frameRun / 5 >= 5) frameRun = 0;

	if (healthBar.getCurrentHealth() > 0) {

		if (typeFlag.gotHitByCharacter) {
			frameHurt++;
			if (frameHurt / 5 >= 5) {
				handleDamage(CHARACTER_DAMAGE);
				frameHurt = 0;
				typeFlag.gotHitByCharacter = false;
			}
			currentTexture = (isFacing == FACING_LEFT_E_AZ) ? gLoadEnemiesAZ[HURT_LEFT_E_AZ].getTexture() : gLoadEnemiesAZ[HURT_RIGHT_E_AZ].getTexture();
			currentClip = (isFacing == FACING_LEFT_E_AZ) ? &frameClipsHurtRight[frameHurt / 5] : &frameClipsHurtLeft[frameHurt / 5];
		}
		else if (typeFlag.isAttacking) {
			currentTexture = (isFacing == FACING_RIGHT_E_AZ) ? gLoadEnemiesAZ[ATTACK_RIGHT_E_AZ].getTexture() : gLoadEnemiesAZ[ATTACK_LEFT_E_AZ].getTexture();
			currentClip = (isFacing == FACING_RIGHT_E_AZ) ? &frameClipsAttackRight[frameAttack / 6] : &frameClipsAttackLeft[frameAttack / 6];

		}
		else if (!typeFlag.isChasing) {
			if ((mPosX >= limitPosB && isFacing == FACING_RIGHT_E_AZ) || (mPosX <= limitPosA && isFacing == FACING_LEFT_E_AZ)) {
				typeFlag.isStanding = true;
				typeFlag.goLeft = false;
				typeFlag.goRight = false;
				timeStand--;
				if (timeStand == 0) {
					typeFlag.isStanding = false;
					typeFlag.goLeft = (mPosX >= limitPosB);
					typeFlag.goRight = (mPosX <= limitPosA);
					timeStand = 60;
				}
				if (mPosX >= limitPosB) {
					currentTexture = gLoadEnemiesAZ[RUN_RIGHT_E_AZ].getTexture();
					currentClip = &frameClipsRunRight[frameRun / 5];
				}
				else if (mPosX <= limitPosA) {
					currentTexture = gLoadEnemiesAZ[RUN_LEFT_E_AZ].getTexture();
					currentClip = &frameClipsRunLeft[frameRun / 5];
				}
			}

			else if (mPosX > limitPosB) {
				typeFlag.goLeft = true;
				typeFlag.goRight = false;
				currentTexture = gLoadEnemiesAZ[RUN_LEFT_E_AZ].getTexture();
				currentClip = &frameClipsRunLeft[frameRun / 5];

			}
			else if (mPosX < limitPosA) {
				typeFlag.goRight = true;
				typeFlag.goLeft = false;
				currentTexture = gLoadEnemiesAZ[RUN_RIGHT_E_AZ].getTexture();
				currentClip = &frameClipsRunRight[frameRun / 5];
			}
			else {
				currentTexture = isFacing == FACING_RIGHT_E_AZ ? gLoadEnemiesAZ[RUN_RIGHT_E_AZ].getTexture() : gLoadEnemiesAZ[RUN_LEFT_E_AZ].getTexture(); 
				currentClip = isFacing == FACING_RIGHT_E_AZ ? &frameClipsRunRight[frameRun / 5] : &frameClipsRunLeft[frameRun / 5];
			}
		}
		else {
			currentTexture = isFacing == FACING_RIGHT_E_AZ ? gLoadEnemiesAZ[RUN_RIGHT_E_AZ].getTexture() : gLoadEnemiesAZ[RUN_LEFT_E_AZ].getTexture();
			currentClip = isFacing == FACING_RIGHT_E_AZ ? &frameClipsRunRight[frameRun / 5] : &frameClipsRunLeft[frameRun / 5];
		}
	}
	else {
		mVelX = 0;
		if (frameDeath / 5 <= 6) frameDeath++;
		currentTexture = isFacing == FACING_RIGHT_E_AZ ? gLoadEnemiesAZ[DEAD_RIGHT_E_AZ].getTexture() : gLoadEnemiesAZ[DEAD_LEFT_E_AZ].getTexture();
		currentClip = isFacing == FACING_RIGHT_E_AZ  ? &frameClipsDeadRight[frameDeath / 6] : &frameClipsDeadLeft[frameDeath / 6];
	}


	SDL_Rect renderQuad = { mPosX - gGameMap.getCameraX(),mPosY - gGameMap.getCameraY(),currentClip->w,currentClip->h };

	SDL_RenderCopy(renderer, currentTexture, currentClip, &renderQuad);

	handleAndRenderProjectile(renderer);

	healthBar.render(renderer, mPosX - gGameMap.getCameraX(), mPosY - 10 - -gGameMap.getCameraY());
}

void EnemyAZ::isHurting() {
	typeFlag.isHurting = true;
}

void EnemyAZ::setLimitPos(int limitposa, int limitposb) {
	limitPosA = limitposa;
	limitPosB = limitposb;
}

void EnemyAZ::setGotHit(bool value) {
	typeFlag.gotHitByCharacter = value;
}

void EnemyAZ::setVelX(int VelX) {
	mVelX = VelX;
}


void EnemyAZ::setVelY(int VelY) {
	mVelY = VelY;
}


void EnemyAZ::setPosX(int PosX) {
	mPosX = PosX;
}

void EnemyAZ::setPosY(int PosY) {
	mPosY = PosY;
}


void EnemyAZ::setHasGivenMana(bool check) {
	typeFlag.hasGivenMana = check;
}

void EnemyAZ::setProjectileList(vector <Projectile*> projectilelist) {
	ProjectileList = projectilelist;
}


vector <Projectile*> EnemyAZ::getProjectileList() {
	return ProjectileList;
}


int EnemyAZ::getIsFacing() {
	return isFacing;
}

bool EnemyAZ::getIsColliding() {
	return typeFlag.isCollidingWithCharacter;
}


bool EnemyAZ::getGotHit() { 
	return typeFlag.gotHitByCharacter; 
}

FlagE_AZ& EnemyAZ::getTypeFlag() {
	return typeFlag;
}

HealthBar& EnemyAZ::getHealthBar() {
	return healthBar;
}

int EnemyAZ::getPosX() {
	return mPosX;
}

int EnemyAZ::getPosY() {
	return mPosY;
}

