#include"Library.h"
#include"Globals.h"
#include"LTexture.h"
#include"EnemyBOSS.h"
#include"EnemyCD.h"
#include"Projectile.h"
#include"Effects.h"





EnemyBOSS::EnemyBOSS() {
	mPosX = 0;
	mPosY = 0;

	mVelX = 0;
	mVelY = 0;

	isFacing = FACING_LEFT_E_BOSS;

	typeFlag.goLeft = true;

	frameWidth = ENEMY_BOSS_WIDTH;
	frameHeight = ENEMY_BOSS_HEIGHT;

	frameRun = 0;
	frameStand = 0;
	frameAttack = 0;
	frameHurt = 0;
	frameDeath = 0;

	timeStand = 200;

	timeReturn = 1;
	timeCoolDownAttack = 20;
	timeCoolDownSummonStar = 50;
	timeDelayBeforeFall= 100;

	limitPosA = 0;
	limitPosB = 0;
}




void EnemyBOSS::setClips() {
	if (frameWidth > 0 && frameHeight > 0) {

		for (int i = 0;i < 7;i++) {
			frameClipsStand[i].x = (6 - i) * (frameWidth - 100);
			frameClipsStand[i].y = 0;
			frameClipsStand[i].w = frameWidth - 100;
			frameClipsStand[i].h = frameHeight;
		}

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

	if (typeFlag.isStanding) {
		mVelX = 0;
	}
	else if (typeFlag.goLeft) {
		mVelX = -ENEMY_BOSS_VEL;
	}
	else if (typeFlag.goRight) {
		mVelX = ENEMY_BOSS_VEL;
	}

	moveToCharacterIfInRange(gMainCharacter.getPosX(), gMainCharacter.getPosY());
}




void EnemyBOSS::handleDamage(float damage) {
	float newHealth = healthBar.getCurrentHealth() - damage;
	if (damage > 0) {
		typeFlag.gotHitByCharacter = true;
	}
	healthBar.setHealth(newHealth);
	if (!typeFlag.isPhase2 && healthBar.getCurrentHealth() <= 0) {
		typeFlag.isPhase2 = true;
		float newHealth = healthBar.getCurrentHealth() + 100;
		healthBar.setHealth(newHealth);
	}
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

	SDL_Rect enemyCollider = { mPosX + (frameWidth - ENEMY_BOSS_COLLIDER_WIDTH) / 2,mPosY + (frameHeight - ENEMY_BOSS_COLLIDER_HEIGHT) / 2, ENEMY_BOSS_COLLIDER_WIDTH , ENEMY_BOSS_COLLIDER_HEIGHT };
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

// Useless
//void EnemyBOSS::checkEnemyAttackedCharacter() {
//
//	int rightCharacter = gMainCharacter.getPosX() + CHARACTER_WIDTH;
//	int rightEnemyCD = mPosX + (ENEMY_CD_WIDTH) * 3 / 4;
//
//	if (isFacing == FACING_RIGHT_E_CD && (frameAttack / 8 == 6) && (rightCharacter >= rightEnemyCD)) gMainCharacter.handleDamage(ENEMY_BOSS_DAMAGE);
//	else if (isFacing == FACING_LEFT_E_CD && (frameAttack / 8 == 6) && (rightCharacter <= rightEnemyCD)) gMainCharacter.handleDamage(ENEMY_BOSS_DAMAGE);
//}
//

void EnemyBOSS::checkEnemyCollisionWithProjectile() {
	SDL_Rect enemyCollider = { mPosX , mPosY , ENEMY_BOSS_COLLIDER_WIDTH, ENEMY_BOSS_COLLIDER_HEIGHT };

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


void EnemyBOSS::moveToCharacterIfInRange(int characterPosX, int characterPosY) {
	if (typeFlag.isPhase2) {
		timeCoolDownSummonStar--;
		if (timeCoolDownSummonStar == 0) {
			timeCoolDownSummonStar = 100;
			createProjectileStar(gRenderer);
		}
	}
	int attackRangeA = mPosX + frameWidth / 2 - ENEMY_BOSS_ATTACK_RANGE;
	int attackRangeB = mPosX + frameWidth / 2 + ENEMY_BOSS_ATTACK_RANGE;

	if (timeReturn == 0) {
		timeReturn = 3;
		typeFlag.isReturning = true;
	}
	typeFlag.isStanding = false;
	if (!typeFlag.isReturning) {

		if (characterPosX > limitPosA - ENEMY_BOSS_ATTACK_RANGE && characterPosX < limitPosB + ENEMY_BOSS_ATTACK_RANGE) {
			typeFlag.isChasing = true;
		}
		if (typeFlag.isChasing) {
			if (characterPosX >= attackRangeA && characterPosX <= attackRangeB) {
				if (timeCoolDownAttack == 0) {
					typeFlag.isAttacking = true;
					frameAttack++;
					if (frameAttack / 6 >= 4) frameAttack = 0;
					if (frameAttack / 6 >= 2) {
						frameAttack = 0;
						typeFlag.isAttacking = false;
						timeCoolDownAttack = 20;
						createProjectileMeteorite(gRenderer);
						timeReturn--;
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
					mVelX = -2 * ENEMY_BOSS_VEL;
				}
				else if (characterPosX >= attackRangeB) {
					typeFlag.goRight = true;
					typeFlag.goLeft = false;
					mVelX = 2 * ENEMY_BOSS_VEL;
				}
			}
		}
		//if (characterPosX < limitPosA - ENEMY_BOSS_ATTACK_RANGE || characterPosX > limitPosB + ENEMY_BOSS_ATTACK_RANGE) {
		//	typeFlag.isChasing = false;
		//	typeFlag.isAttacking = false;
		//	typeFlag.isReturning = true;
		//	timeReturn = 3;
		//	frameAttack = 0;
		//}
	}
	else {
		if (timeStand == 0) {
			typeFlag.isStanding = false;
			typeFlag.isReturning = false;
			typeFlag.isChasing = true;
			typeFlag.hasSummonedAlly = false;
			timeStand = 200;
		}
		typeFlag.goRight = true;
		typeFlag.goLeft = false;
		mVelX = 2 * ENEMY_BOSS_VEL;
		if (mPosX >= 2000  ) {
			timeStand--;
			if (isFacing == FACING_RIGHT_E_BOSS) summonAlly();
			handleDamage(-0.05);
			typeFlag.isStanding = true;
			typeFlag.goLeft = true;
			typeFlag.goRight = false;
			mVelX = 0;
			typeFlag.isChasing = false;
		}
	}

}


void EnemyBOSS::summonAlly() {
	if ( !typeFlag.hasSummonedAlly) {

		EnemyAZ* pEnemyAZ = new EnemyAZ();
		pEnemyAZ->getHealthBar().setMaxHealth(ENEMY_AZ_HEALTH);
		pEnemyAZ->getHealthBar().setHealth(ENEMY_AZ_HEALTH);
		pEnemyAZ->setClips();
		pEnemyAZ->setPosX(mPosX - 100);
		pEnemyAZ->setPosY(96);
		pEnemyAZ->setLimitPos(0,2000);
		listEnemiesAZ.push_back(pEnemyAZ);

		EnemyCD* pEnemyCD = new EnemyCD();
		pEnemyCD->getHealthBar().setMaxHealth(ENEMY_CD_HEALTH);
		pEnemyCD->getHealthBar().setHealth(ENEMY_CD_HEALTH);
		pEnemyCD->setClips();
		pEnemyCD->setPosX(mPosX );
		pEnemyCD->setPosY(0);
		pEnemyCD->setLimitPos(0,2000);
		listEnemiesCD.push_back(pEnemyCD);

		typeFlag.hasSummonedAlly = true;
	}
}	

void EnemyBOSS::summonStar() {
	timeCoolDownSummonStar--;
	if (timeCoolDownSummonStar == 0) {
		typeFlag.hasSummonedStar = true;
		timeCoolDownSummonStar = 50;
	}
}



void EnemyBOSS::createProjectileMeteorite(SDL_Renderer* renderer) {
	int numBullets = 4;
	if (getHealthBar().getCurrentHealth() <= ENEMY_BOSS_HEALTH / 2) {
		numBullets = 6;
	}

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
		if (numBullets == 4 || numBullets == 6) {
			angleOffSetDegrees = (i - 1) * 15.0f;
		}

		float angleOffSetRadian = angleOffSetDegrees * M_PI / 180.0f;
		float finalAngle = baseAngle + angleOffSetRadian;

		float velX = PROJECTILE_VEL * cos(finalAngle);
		float velY = PROJECTILE_VEL * sin(finalAngle);
		if (!typeFlag.isPhase2) {
			Projectile* pProjectile = new Projectile();
			pProjectile->setClips();
			pProjectile->setPosX(projectileStartX);
			pProjectile->setPosY(projectileStartY);
			pProjectile->setVelX(velX);
			pProjectile->setVelY(velY);
			pProjectile->setRotationAngle(finalAngle * 180.0f / M_PI);
			pProjectile->setIsMoving(true);
			ProjectileListMeteorite.push_back(pProjectile);
		}
		else {
			Projectile* pProjectile = new Projectile();
			pProjectile->setClips();
			pProjectile->setPosX(projectileStartX);
			pProjectile->setPosY(projectileStartY);
			pProjectile->setVelX(velX);
			pProjectile->setVelY(velY);
			pProjectile->setRotationAngle(finalAngle * 180.0f / M_PI);
			pProjectile->setIsMoving(true);
			ProjectileListStar.push_back(pProjectile);
		}

	}
}


void EnemyBOSS::createProjectileStar(SDL_Renderer* renderer) {
	float offsetX, offsetY;
	float projectileStartX, projectileStartY;
	for (int i = 0; i < 3; i++) {
		offsetY = 0;
		offsetX = i * 100;
		projectileStartX = gMainCharacter.getPosX() + offsetX;
		projectileStartY = -PROJECTILE_HEIGHT - offsetY;

		Projectile* pProjectile = new Projectile();
		pProjectile->setClips();
		pProjectile->setPosX(projectileStartX);
		pProjectile->setPosY(projectileStartY);
		pProjectile->setVelX(0);
		pProjectile->setVelY(0);  // delay trước khi rơi
		pProjectile->setIsMoving(true);
		pProjectile->setIsWaitingToFall(true);
		pProjectile->setDelayBeforeFall(100);

		ProjectileListStar.push_back(pProjectile);
	}
}



void EnemyBOSS::handleAndRenderProjectile(SDL_Renderer* renderer) {

	for (int i = 0; i < ProjectileListStar.size();) {
		Projectile* pProjectile = ProjectileListStar[i];
		if (pProjectile != NULL) {
			if (pProjectile->getIsMoving() || pProjectile->getTypeFlag().isExploding) {
				pProjectile->handleMotion(SCREEN_WIDTH + gGameMap.getCameraX(), SCREEN_HEIGHT, true);
				pProjectile->renderProjectile(renderer, false, false, true, false);
				++i;
			}
			else {
				delete pProjectile;
				pProjectile = NULL;
				ProjectileListStar.erase(ProjectileListStar.begin() + i);
			}
		}
		else {
			++i;
		}
	}

	for (int i = 0; i < ProjectileListMeteorite.size();) {
		Projectile* pProjectile = ProjectileListMeteorite[i];
		if (pProjectile != NULL) {
			if (pProjectile->getIsMoving() ||  pProjectile->getTypeFlag().isExploding) {
				pProjectile->handleMotion(SCREEN_WIDTH + gGameMap.getCameraX(), SCREEN_HEIGHT, false);
				pProjectile->renderProjectile(renderer, false, true, false, false);
				++i;
			}
			else {
				delete pProjectile;
				pProjectile = NULL;
				ProjectileListMeteorite.erase(ProjectileListMeteorite.begin() + i);
			}
		}
		else {
			++i;
		}
	}
}




void EnemyBOSS::render(SDL_Renderer* renderer) {

	SDL_Rect* currentClip = nullptr;

	SDL_Texture* currentTexture = nullptr;


	if (typeFlag.goRight) isFacing = FACING_RIGHT_E_BOSS;
	else if (typeFlag.goLeft) isFacing = FACING_LEFT_E_BOSS;

	if (!typeFlag.isPhase2) {
		frameRun++;
		if (frameRun / 5 >= 3) frameRun = 0;

		if (typeFlag.gotHitByCharacter) {
			frameHurt++;
			if (frameHurt ==  16) {
				handleDamage(CHARACTER_DAMAGE);
				frameHurt = 0;
				typeFlag.gotHitByCharacter = false;
			}
			currentTexture = gLoadEnemiesBOSS[isFacing == FACING_LEFT_E_BOSS ? HURT_LEFT_E_BOSS : HURT_RIGHT_E_BOSS].getTexture();
			currentClip = isFacing == FACING_LEFT_E_BOSS ? &frameClipsHurtRight[frameHurt / 4] : &frameClipsHurtLeft[frameHurt / 4];
		}
		else if (typeFlag.isAttacking) {
			currentTexture = gLoadEnemiesBOSS[isFacing == FACING_RIGHT_E_BOSS ? ATTACK_RIGHT_E_BOSS : ATTACK_LEFT_E_BOSS].getTexture();
			currentClip = isFacing == FACING_RIGHT_E_BOSS ? &frameClipsAttackRight[frameAttack / 6] : &frameClipsAttackLeft[frameAttack / 6];
		}
		else if (!typeFlag.isChasing) {
			if (typeFlag.isStanding) {
				frameStand++;
				if (frameStand / 7 >= 7) frameStand = 0;
				currentTexture = gLoadEnemiesBOSS[STAND_LEFT_E_BOSS].getTexture();
				currentClip = &frameClipsStand[frameStand / 7];
			}
			else if (mPosX > limitPosB) {
				typeFlag.goLeft = true;
				typeFlag.goRight = false;
				currentTexture = gLoadEnemiesBOSS[RUN_LEFT_E_BOSS].getTexture();
				currentClip = &frameClipsRunLeft[frameRun / 5];

			}
			else if (mPosX < limitPosA) {
				typeFlag.goRight = true;
				typeFlag.goLeft = false;
				currentTexture = gLoadEnemiesBOSS[RUN_RIGHT_E_BOSS].getTexture();
				currentClip = &frameClipsRunRight[frameRun / 5];
			}
			else {
				currentTexture = gLoadEnemiesBOSS[isFacing == FACING_RIGHT_E_BOSS ? RUN_RIGHT_E_BOSS : RUN_LEFT_E_BOSS].getTexture();
				currentClip = isFacing == FACING_RIGHT_E_BOSS ? &frameClipsRunRight[frameRun / 5] : &frameClipsRunLeft[frameRun / 5];
			}
		}
		else {
			currentTexture = gLoadEnemiesBOSS[isFacing == FACING_RIGHT_E_BOSS ? RUN_RIGHT_E_BOSS : RUN_LEFT_E_BOSS].getTexture();
			currentClip = isFacing == FACING_RIGHT_E_BOSS ? &frameClipsRunRight[frameRun / 5] : &frameClipsRunLeft[frameRun / 5];

		}
		healthBar.render(renderer, mPosX - gGameMap.getCameraX(), mPosY - 10 - -gGameMap.getCameraY());
	}

	else {

		if (healthBar.getCurrentHealth() > 0) {
			frameRun++;
			if (frameRun / 5 >= 3) frameRun = 0;

			if (typeFlag.gotHitByCharacter) {
				frameHurt++;
				if (frameHurt / 4 >= 4) {
					handleDamage(CHARACTER_DAMAGE);
					frameHurt = 0;
					typeFlag.gotHitByCharacter = false;
				}
				currentTexture = gLoadEnemiesBOSS[isFacing == FACING_LEFT_E_BOSS ? HURT_LEFT_E_BOSS_PHASE2 : HURT_RIGHT_E_BOSS_PHASE2].getTexture();
				currentClip = isFacing == FACING_LEFT_E_BOSS ? &frameClipsHurtRight[frameHurt / 4] : &frameClipsHurtLeft[frameHurt / 4];

			}
			else if (typeFlag.isAttacking) {
				currentTexture = gLoadEnemiesBOSS[isFacing == FACING_RIGHT_E_BOSS ? ATTACK_RIGHT_E_BOSS_PHASE2 : ATTACK_LEFT_E_BOSS_PHASE2].getTexture();
				currentClip = isFacing == FACING_RIGHT_E_BOSS ? &frameClipsAttackRight[frameAttack / 6] : &frameClipsAttackLeft[frameAttack / 6];
			}
			else if (!typeFlag.isChasing) {
				if (typeFlag.isStanding) {
					frameStand++;
					if (frameStand / 7 >= 7) frameStand = 0;
					currentTexture = gLoadEnemiesBOSS[STAND_LEFT_E_BOSS_PHASE2].getTexture();
					currentClip = &frameClipsStand[frameStand / 7];
				}
				else if (mPosX > limitPosB) {
					typeFlag.goLeft = true;
					typeFlag.goRight = false;
					currentTexture = gLoadEnemiesBOSS[RUN_LEFT_E_BOSS_PHASE2].getTexture();
					currentClip = &frameClipsRunLeft[frameRun / 5];

				}
				else if (mPosX < limitPosA) {
					typeFlag.goRight = true;
					typeFlag.goLeft = false;
					currentTexture = gLoadEnemiesBOSS[RUN_RIGHT_E_BOSS_PHASE2].getTexture();
					currentClip = &frameClipsRunRight[frameRun / 5];
				}
				else {
					currentTexture = gLoadEnemiesBOSS[isFacing == FACING_RIGHT_E_BOSS ? RUN_RIGHT_E_BOSS_PHASE2 : RUN_LEFT_E_BOSS_PHASE2].getTexture();
					currentClip = isFacing == FACING_RIGHT_E_BOSS ? &frameClipsRunRight[frameRun / 5] : &frameClipsRunLeft[frameRun / 5];
				}
			}
			else {
				currentTexture = gLoadEnemiesBOSS[isFacing == FACING_RIGHT_E_BOSS ? RUN_RIGHT_E_BOSS_PHASE2 : RUN_LEFT_E_BOSS_PHASE2].getTexture();
				currentClip = isFacing == FACING_RIGHT_E_BOSS ? &frameClipsRunRight[frameRun / 5] : &frameClipsRunLeft[frameRun / 5];
			}
			healthBar.render(renderer, mPosX - gGameMap.getCameraX(), mPosY - 10 - -gGameMap.getCameraY());
		}
		else {
			mVelX = 0;
			if (frameDeath / 4 <= 5) {
				frameDeath++;
			}
			currentTexture = gLoadEnemiesBOSS[isFacing == FACING_RIGHT_E_BOSS ? DEAD_RIGHT_E_BOSS_PHASE2 : DEAD_LEFT_E_BOSS_PHASE2].getTexture();
			currentClip = isFacing == FACING_RIGHT_E_BOSS ? &frameClipsDeadRight[frameDeath / 5] : &frameClipsDeadLeft[frameDeath / 5];
		}

	}


	SDL_Rect renderQuad = { mPosX - gGameMap.getCameraX(),mPosY - gGameMap.getCameraY(),currentClip->w,currentClip->h };

	SDL_RenderCopy(renderer, currentTexture, currentClip, &renderQuad);

	handleAndRenderProjectile(renderer);
	if (healthBar.getCurrentHealth() > 0) {
		if (typeFlag.isStanding) {
			gEffects.render(renderer, mPosX, mPosY, true ,false);
		}
	}

}


void EnemyBOSS::isHurting() {
	typeFlag.isHurting = true;
}

void EnemyBOSS::setHasGivenScore(bool check) {
	typeFlag.hasGivenScore = check;
}

void EnemyBOSS::setLimitPos(int limitposa, int limitposb) {
	limitPosA = limitposa;
	limitPosB = limitposb;
}

void EnemyBOSS::setGotHit(bool value) { 
	typeFlag.gotHitByCharacter = value; 
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

vector <Projectile*> EnemyBOSS::getProjectileListMeteorite() {
	return ProjectileListMeteorite;
}


vector<Projectile*> EnemyBOSS::getProjectileListStar() {
	return ProjectileListStar;
}

int EnemyBOSS::getIsFacing() {
	return isFacing;
}

bool EnemyBOSS::getIsColliding() {
	return typeFlag.isCollidingWithCharacter;
}

bool EnemyBOSS::getGotHit() {
	return typeFlag.gotHitByCharacter;
}

FlagE_BOSS& EnemyBOSS::getTypeFlag() {
	return typeFlag;
}

HealthBar& EnemyBOSS::getHealthBar() {
	return healthBar;
}


int EnemyBOSS::getPosX() {
	return mPosX;
}

int EnemyBOSS::getPosY() {
	return mPosY;
}