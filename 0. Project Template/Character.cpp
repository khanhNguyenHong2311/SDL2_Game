#include"Library.h"
#include"Globals.h"
#include"LTexture.h"
#include"Map.h"
#include"Character.h"
#include"Effects.h"

Character::Character() {

	mPosX = 0;
	mPosY = 0;

	mVelX = 0;
	mVelY = 0;

	isFacing = FACING_RIGHT ;

	typeFlag.isStanding = true;
	typeFlag.isStandingOnGround = false;


	frameWidth = CHARACTER_WIDTH;
	frameHeight = CHARACTER_HEIGHT;

	frameRun = 0;
	frameStand = 0;
	frameJump = 0;
	frameAttack = 0;
	frameDeath = 0;

	timeRespawn = 0;
}




void Character::setClips() {

		for (int i = 0;i < 12;i++) {
			frameClipsDeadRight[i].x = i * frameWidth;
			frameClipsDeadRight[i].y = 0;
			frameClipsDeadRight[i].w = frameWidth;
			frameClipsDeadRight[i].h = frameHeight;

			frameClipsDeadLeft[i].x = (11 - i) * frameWidth;
			frameClipsDeadLeft[i].y = 0;
			frameClipsDeadLeft[i].w = frameWidth;
			frameClipsDeadLeft[i].h = frameHeight;
		}

		for (int i = 0;i < 8;i++) {
			frameClipsRunRight[i].x = i * frameWidth;
			frameClipsRunRight[i].y = 0;
			frameClipsRunRight[i].w = frameWidth;
			frameClipsRunRight[i].h = frameHeight;

			frameClipsRunLeft[i].x = (7 - i) * frameWidth;
			frameClipsRunLeft[i].y = 0;
			frameClipsRunLeft[i].w = frameWidth;
			frameClipsRunLeft[i].h = frameHeight;
		}

		for (int i = 0;i < 7;i++) {
			frameClipsStandRight[i].x = i * frameWidth;
			frameClipsStandRight[i].y = 0;
			frameClipsStandRight[i].w = frameWidth;
			frameClipsStandRight[i].h = frameHeight;

			frameClipsStandLeft[i].x = (6 - i) * frameWidth;
			frameClipsStandLeft[i].y = 0;
			frameClipsStandLeft[i].w = frameWidth;
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





void Character::handleDamage(int damage) {
	if (damage > 0) {
		typeFlag.isHurting = true;
	}
	int newHealth = healthBar.getCurrentHealth() - damage;
	healthBar.setHealth(newHealth);
}




void Character::handleMana(int mana) {
	int newMana = manaBar.getCurrentMana() - mana;
	manaBar.setMana(newMana);
}


void Character::handleMotion(SDL_Event& e) {


	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
		case SDLK_LEFT:mVelX -= CHARACTER_VEL; typeFlag.goLeft = true; break;
		case SDLK_RIGHT:mVelX += CHARACTER_VEL; typeFlag.goRight = true; break;
		case SDLK_UP: 
			if (typeFlag.isStandingOnGround) {
				mVelY = -CHARACTER_VEL_JUMP;
				typeFlag.isStandingOnGround = false;
			}
			break;
		case SDLK_a:typeFlag.isAttacking = true; break;
		case SDLK_s:
			if (!typeFlag.isCasting && manaBar.getCurrentMana() >= 10) {
				typeFlag.isCasting = true;
				frameAttack = 0; 
			}
			break;
		}

	}

	else if (e.type == SDL_KEYUP && e.key.repeat == 0) {	
		switch (e.key.keysym.sym) {
		case SDLK_LEFT:mVelX += CHARACTER_VEL; typeFlag.goLeft = false; break;
		case SDLK_RIGHT:mVelX -= CHARACTER_VEL; typeFlag.goRight = false; break;

		}
	}
}

void Character::checkMapCollision(SDL_Renderer* renderer) {
	
	if (!typeFlag.isFallingIntoHole) {
		typeFlag.isStandingOnGround = false;

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

				int val1 = gGameMap.getValueOfTile(y1, x2);
				int val2 = gGameMap.getValueOfTile(y2, x2);

				if (val1 == TILE_HEALTH || val2 == TILE_HEALTH) {
					gGameMap.setValueOfTile(y1, x2, 0);
					gGameMap.setValueOfTile(y2, x2, 0);
					gMainCharacter.handleDamage(HEALTH_RECOVER);
				}
				else if (val1 == TILE_MANA || val2 == TILE_MANA) {
					gGameMap.setValueOfTile(y1, x2, 0);
					gGameMap.setValueOfTile(y2, x2, 0);
					gMainCharacter.handleMana(MANA_RECOVER);
				}
				else if (val1 == TILE_MINE || val2 == TILE_MINE) {
					gGameMap.setValueOfTile(y1, x2, 0);
					gGameMap.setValueOfTile(y2, x2, 0);
					gMainCharacter.handleDamage(MINE_DAMAGE);
					gEffects.setIsMineExplosionActive(true);
					gEffects.setMineExplosionPosition(x2 * TILE_SIZE, y2 * TILE_SIZE);
				}
				else {
					if (val1 != TILE_EMPTY || val2 != TILE_EMPTY) {
						mPosX = x2 * TILE_SIZE - frameWidth - 8;
						mVelX = CHARACTER_VEL;
					}
				}
			}
			else if (mVelX < 0) {

				int val1 = gGameMap.getValueOfTile(y1, x1);
				int val2 = gGameMap.getValueOfTile(y2, x1);

				if (val1 == TILE_HEALTH || val2 == TILE_HEALTH) {
					gGameMap.setValueOfTile(y1, x1, 0);
					gGameMap.setValueOfTile(y2, x1, 0);
					gMainCharacter.handleDamage(HEALTH_RECOVER);
				}
				else if (val1 == TILE_MANA || val2 == TILE_MANA) {
					gGameMap.setValueOfTile(y1, x1, 0);
					gGameMap.setValueOfTile(y2, x1, 0);
					gMainCharacter.handleMana(MANA_RECOVER);
				}
				else if (val1 == TILE_MINE || val2 == TILE_MINE) {
					gGameMap.setValueOfTile(y1, x1, 0);
					gGameMap.setValueOfTile(y2, x1, 0);
					gMainCharacter.handleDamage(MINE_DAMAGE);
					gEffects.setIsMineExplosionActive(true);
					gEffects.setMineExplosionPosition(x2 * TILE_SIZE, y2 * TILE_SIZE);
				}
				else {
					if (val1 != TILE_EMPTY || val2 != TILE_EMPTY) {
						mPosX = (x1 + 1) * TILE_SIZE + 8;
						mVelX = -CHARACTER_VEL;
					}
				}
	
			}
		}

		x1 = mPosX / TILE_SIZE;
		x2 = (mPosX + frameWidth - 1) / TILE_SIZE;

		y1 = (mPosY + mVelY) / TILE_SIZE;
		y2 = (mPosY + mVelY + frameHeight - 1) / TILE_SIZE;

		if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
			if (mVelY > 0) {

				int val1 = gGameMap.getValueOfTile(y2, x1);
				int val2 = gGameMap.getValueOfTile(y2, x2);

				if (val1 == TILE_HEALTH || val2 == TILE_HEALTH) {
					gGameMap.setValueOfTile(y2, x1, 0);
					gGameMap.setValueOfTile(y2, x2, 0);
					gMainCharacter.handleDamage(HEALTH_RECOVER);
				}
				else if (val1 == TILE_MANA || val2 == TILE_MANA) {
					gGameMap.setValueOfTile(y2, x1, 0);
					gGameMap.setValueOfTile(y2, x2, 0);
					gMainCharacter.handleMana(MANA_RECOVER);
				}
				else if (val1 == TILE_MINE || val2 == TILE_MINE) {
					gGameMap.setValueOfTile(y2, x1, 0);
					gGameMap.setValueOfTile(y2, x2, 0);
					gMainCharacter.handleDamage(MINE_DAMAGE);
					gEffects.setIsMineExplosionActive(true);
					gEffects.setMineExplosionPosition(x2 * TILE_SIZE, y2 * TILE_SIZE);
				}
				else {
					if (val1 != TILE_EMPTY || val2 != TILE_EMPTY) {
						mPosY = y2 * TILE_SIZE - frameHeight;
						mVelY = 0;
						typeFlag.isStandingOnGround = true;
					}
				}
			}
			else if (mVelY < 0) {
				int val1 = gGameMap.getValueOfTile(y1, x1);
				int val2 = gGameMap.getValueOfTile(y1, x2);

				if (val1 == TILE_HEALTH || val2 == TILE_HEALTH) {
					gGameMap.setValueOfTile(y1, x1, 0);
					gGameMap.setValueOfTile(y1, x2, 0);
					gMainCharacter.handleDamage(HEALTH_RECOVER);
				}
				else if (val1 == TILE_MANA || val2 == TILE_MANA) {
					gGameMap.setValueOfTile(y1, x1, 0);
					gGameMap.setValueOfTile(y1, x2, 0);
					gMainCharacter.handleMana(MANA_RECOVER);
				}
				else if (val1 == TILE_MINE || val2 == TILE_MINE) {
					gGameMap.setValueOfTile(y1, x1, 0);
					gGameMap.setValueOfTile(y1, x2, 0);
					gMainCharacter.handleDamage(MINE_DAMAGE);
					gEffects.setIsMineExplosionActive(true);
					gEffects.setMineExplosionPosition(x2* TILE_SIZE, y2* TILE_SIZE);
				}
				else {
				if (val1 != TILE_EMPTY || val2 != TILE_EMPTY) {
					mPosY = (y1 + 1) * TILE_SIZE;
					mVelY = 0;
					}
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
			typeFlag.isFallingIntoHole = false;
		}
	}
	if (gEffects.getIsMineExplosionActive()) {
		gEffects.render(renderer, gEffects.getMineExplosionPositionX() - 80, gEffects.getMineExplosionPositionY() - 160, false, false);
	}
}




void Character::checkCharacterCollisionWithEnemy(EnemyCD* pEnemyCD, EnemyAZ* pEnemyAZ, EnemyBOSS* pEnemyBOSS) {

	SDL_Rect enemyCollider = { 0,0,0,0 };
	if (pEnemyCD != NULL) {
		enemyCollider = { pEnemyCD->getPosX() , pEnemyCD->getPosY() , ENEMY_CD_COLLIDER_WIDTH, ENEMY_CD_COLLIDER_HEIGHT };
	}
	else if (pEnemyAZ != NULL) {
		enemyCollider = { pEnemyAZ->getPosX() , pEnemyAZ->getPosY() , ENEMY_AZ_COLLIDER_WIDTH, ENEMY_AZ_COLLIDER_HEIGHT };

	}
	else if (pEnemyBOSS != NULL) {
		enemyCollider = { pEnemyBOSS->getPosX() , pEnemyBOSS->getPosY() ,ENEMY_BOSS_COLLIDER_WIDTH,ENEMY_BOSS_COLLIDER_HEIGHT };
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
		typeFlag.isCollidingWithEnemyCD = !((bottomCharacter <= topEnemy) || (topCharacter >= bottomEnemy) || (rightCharacter <= leftEnemy) || (leftCharacter >= rightEnemy));
	}
	else if (pEnemyAZ != NULL) {
		typeFlag.isCollidingWithEnemyAZ = !((bottomCharacter <= topEnemy) || (topCharacter >= bottomEnemy) || (rightCharacter <= leftEnemy) || (leftCharacter >= rightEnemy));
	}
	else if (pEnemyBOSS != NULL) {
		typeFlag.isCollidingWithEnemyBOSS = !((bottomCharacter <= topEnemy) || (topCharacter >= bottomEnemy) || (rightCharacter <= leftEnemy) || (leftCharacter >= rightEnemy));
	}
}


void Character::checkCharacterCollisionWithProjectile(EnemyAZ* pEnemyAZ, EnemyBOSS* pEnemyBOSS) {

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
				enemyProjectileRect = { pProjectile->getPosX(),pProjectile->getPosY(),PROJECTILE_WIDTH - 100  ,PROJECTILE_HEIGHT - 100 };

				int rightEnemyProjectile = enemyProjectileRect.x + enemyProjectileRect.w;
				int leftEnemyProjectile = enemyProjectileRect.x;
				int topEnemyProjectile = enemyProjectileRect.y;
				int bottomEnemyProjectile = enemyProjectileRect.y + enemyProjectileRect.h;

				if (!(bottomCharacter <= topEnemyProjectile || topCharacter >= bottomEnemyProjectile || rightCharacter <= leftEnemyProjectile || leftCharacter >= rightEnemyProjectile)) {
					handleDamage(ENEMY_AZ_DAMAGE);
					projectileAZ[i]->setIsMoving(false);
					projectileAZ[i]->projectileExploded();
				}
			}
		}
	}
	else if (pEnemyBOSS != NULL) {
		vector<Projectile*> projectileBOSS = pEnemyBOSS->getProjectileListMeteorite();
		vector<Projectile*> projectileBOSSS = pEnemyBOSS->getProjectileListStar();
		for (int i = 0;i < projectileBOSS.size();i++) {
			Projectile* pProjectile = projectileBOSS[i];
			if (pProjectile->getIsMoving()) {
				enemyProjectileRect = { pProjectile->getPosX(),pProjectile->getPosY(),PROJECTILE_WIDTH - 100 ,PROJECTILE_HEIGHT - 100 };

				int rightEnemyProjectile = enemyProjectileRect.x + enemyProjectileRect.w;
				int leftEnemyProjectile = enemyProjectileRect.x;
				int topEnemyProjectile = enemyProjectileRect.y;
				int bottomEnemyProjectile = enemyProjectileRect.y + enemyProjectileRect.h;

				if (!(bottomCharacter <= topEnemyProjectile || topCharacter >= bottomEnemyProjectile || rightCharacter <= leftEnemyProjectile || leftCharacter >= rightEnemyProjectile)) {
					handleDamage(ENEMY_BOSS_DAMAGE);
					projectileBOSS[i]->setIsMoving(false);
					projectileBOSS[i]->projectileExploded();
				}
			}
		}

		for (int i = 0;i < projectileBOSSS.size();i++) {
			Projectile* pProjectile = projectileBOSSS[i];
			if (pProjectile->getIsMoving()) {
				enemyProjectileRect = { pProjectile->getPosX(),pProjectile->getPosY(),PROJECTILE_WIDTH - 100 ,PROJECTILE_HEIGHT - 100 };

				int rightEnemyProjectile = enemyProjectileRect.x + enemyProjectileRect.w;
				int leftEnemyProjectile = enemyProjectileRect.x;
				int topEnemyProjectile = enemyProjectileRect.y;
				int bottomEnemyProjectile = enemyProjectileRect.y + enemyProjectileRect.h;

				if (!(bottomCharacter <= topEnemyProjectile || topCharacter >= bottomEnemyProjectile || rightCharacter <= leftEnemyProjectile || leftCharacter >= rightEnemyProjectile)) {
					handleDamage(ENEMY_BOSS_DAMAGE);
				}
			}
		}

	}
}





void Character::checkCharacterAttackedEnemy(EnemyCD* pEnemyCD, EnemyAZ* pEnemyAZ, EnemyBOSS* pEnemyBOSS) {

	int leftCharacter = mPosX;
	int rightCharacter = mPosX + CHARACTER_WIDTH;


	if (pEnemyCD != NULL) {
		int leftEnemy = pEnemyCD->getPosX();
		int rightEnemy = leftEnemy + ENEMY_CD_WIDTH;

		if (typeFlag.isAttacking == true && (frameAttack == 24) && typeFlag.isCollidingWithEnemyCD) {
			if (isFacing == FACING_RIGHT) {
				if (pEnemyCD->getIsFacing() == FACING_RIGHT_E_CD) pEnemyCD->setGotHit((rightCharacter >= leftEnemy + ENEMY_CD_WIDTH / 2) && (rightCharacter <= rightEnemy + 20));
				else if (pEnemyCD->getIsFacing() == FACING_LEFT_E_CD) pEnemyCD->setGotHit((rightCharacter >= leftEnemy) && (rightCharacter <= rightEnemy - 20));
			}
			else if (isFacing == FACING_LEFT) {
				if (pEnemyCD->getIsFacing() == FACING_RIGHT_E_CD) pEnemyCD->setGotHit((leftCharacter <= rightEnemy + 20) && (leftCharacter >= leftEnemy + 10));
				else if (pEnemyCD->getIsFacing() == FACING_LEFT_E_CD) pEnemyCD->setGotHit((leftCharacter >= leftEnemy - 20) && (leftCharacter <= rightEnemy - 80));
			}
		}
	}
	else if (pEnemyAZ != NULL) {
		int leftEnemy = pEnemyAZ->getPosX();
		int rightEnemy = leftEnemy + ENEMY_AZ_WIDTH;

		if (typeFlag.isAttacking == true && frameAttack == 24 && typeFlag.isCollidingWithEnemyAZ) {
			if (isFacing == FACING_RIGHT) {
				if (pEnemyAZ->getIsFacing() == FACING_RIGHT_E_AZ) pEnemyAZ->setGotHit((rightCharacter >= leftEnemy + ENEMY_CD_WIDTH / 2) && (rightCharacter <= rightEnemy + 20));
				else if (pEnemyAZ->getIsFacing() == FACING_LEFT_E_CD) pEnemyAZ->setGotHit((rightCharacter >= leftEnemy) && (rightCharacter <= rightEnemy - 20));
			}
			else if (isFacing == FACING_LEFT) {
				if (pEnemyAZ->getIsFacing() == FACING_RIGHT_E_AZ)  pEnemyAZ->setGotHit((leftCharacter <= rightEnemy + 20) && (leftCharacter >= leftEnemy + 10));
				else if (pEnemyAZ->getIsFacing() == FACING_LEFT_E_AZ)  pEnemyAZ->setGotHit((leftCharacter >= leftEnemy - 20) && (leftCharacter <= rightEnemy - 80));
			}
		}
	}
	else if (pEnemyBOSS != NULL) {
		int leftEnemy = pEnemyBOSS->getPosX();
		int rightEnemy = leftEnemy + ENEMY_BOSS_WIDTH;

		if (typeFlag.isAttacking == true && frameAttack == 24 && typeFlag.isCollidingWithEnemyBOSS) {
			if (isFacing == FACING_RIGHT) {
				if (pEnemyBOSS->getIsFacing() == FACING_RIGHT_E_AZ) pEnemyBOSS->setGotHit((rightCharacter >= leftEnemy + ENEMY_BOSS_WIDTH / 2) && (rightCharacter <= rightEnemy + 20));
				else if (pEnemyBOSS->getIsFacing() == FACING_LEFT_E_CD) pEnemyBOSS->setGotHit((rightCharacter >= leftEnemy) && (rightCharacter <= rightEnemy - 20));
			}
			else if (isFacing == FACING_LEFT) {
				if (pEnemyBOSS->getIsFacing() == FACING_RIGHT_E_AZ)  pEnemyBOSS->setGotHit((leftCharacter <= rightEnemy + 20) && (leftCharacter >= leftEnemy + 10));
				else if (pEnemyBOSS->getIsFacing() == FACING_LEFT_E_AZ)  pEnemyBOSS->setGotHit((leftCharacter >= leftEnemy - 20) && (leftCharacter <= rightEnemy - 80));
			}
		}
	}
}




void Character::createProjectileArrow(SDL_Renderer* renderer) {
	float offsetX, offsetY;

	float projectileStartX, projectileStartY;

	offsetY = 0;
	offsetX = 0;

	projectileStartX = mPosX + offsetX;
	projectileStartY = mPosY - offsetY;

	Projectile* pProjectile = new Projectile();
	pProjectile->setClips();
	pProjectile->setPosX(projectileStartX);
	pProjectile->setPosY(projectileStartY);
	pProjectile->setVelY(0); 
	if (isFacing == FACING_RIGHT) {
		pProjectile->setRotationAngle(0);
		pProjectile->setVelX(10);
	}
	else {
		pProjectile->setRotationAngle(180);
		pProjectile->setVelX(-10);
	}
	pProjectile->setIsMoving(true);
	ProjectileListArrow.push_back(pProjectile);
}


void Character::handleAndRenderProjectile(SDL_Renderer* renderer) {

	for (int i = 0; i < ProjectileListArrow.size();) {
		Projectile* pProjectile = ProjectileListArrow[i];
		if (pProjectile != NULL) {
			if (pProjectile->getIsMoving() || pProjectile->getTypeFlag().isExploding ) { // is exploded
				pProjectile->handleMotion(SCREEN_WIDTH + gGameMap.getCameraX(), SCREEN_HEIGHT, false);
				pProjectile->renderProjectile(renderer, false, false, false,true);
				++i;
			}
			else {
				delete pProjectile;
				pProjectile = NULL;
				ProjectileListArrow.erase(ProjectileListArrow.begin() + i);
			}
		}
		else {
			++i;
		}
	}
}


void Character::FallingInTheHole() {
	if (!typeFlag.isFallingIntoHole && mPosY > gGameMap.getMaxMapY()) {
		typeFlag.isFallingIntoHole = true;
		timeRespawn = 30;
		isFacing = FACING_RIGHT;
	}
}




void Character::render(SDL_Renderer* renderer) {
	
	SDL_Rect* currentClip = nullptr;

	SDL_Texture* currentTexture = nullptr;
	

	if (typeFlag.goRight) isFacing = FACING_RIGHT;
	else if (typeFlag.goLeft) isFacing = FACING_LEFT;

	
	if (healthBar.getCurrentHealth() > 0) {

		if (typeFlag.isHurting) {
			typeFlag.isAttacking = false;
			frameHurt++;
			if (frameHurt / 4 >= 4) {
				frameHurt = 0;
				frameAttack = 0;
				typeFlag.isHurting = false;
			}
			currentTexture = gLoadMainCharacter[isFacing == FACING_RIGHT ? HURT_RIGHT : HURT_LEFT].getTexture();
			currentClip = isFacing == FACING_RIGHT ? &frameClipsHurtRight[frameHurt / 4] : &frameClipsHurtLeft[frameHurt / 4];
		}

		else if (typeFlag.isCasting) {
			frameAttack++;
			if (frameAttack / 6 >= 6) {
				frameAttack = 0;
				typeFlag.isCasting = false;
			}
			if (frameAttack == 24) {
				createProjectileArrow(renderer);
				handleMana(10);
			}	
			currentTexture = gLoadMainCharacter[isFacing == FACING_RIGHT ? ATTACK_RIGHT : ATTACK_LEFT].getTexture();
			currentClip = isFacing == FACING_RIGHT ? &frameClipsAttackRight[frameAttack / 6] : &frameClipsAttackLeft[frameAttack / 6];
		}
		else if (typeFlag.isAttacking) {
			frameAttack++;
			if (frameAttack / 6 >= 6) {
				frameAttack = 0;
				typeFlag.isAttacking = false;
			}
			currentTexture = gLoadMainCharacter[isFacing == FACING_RIGHT ? ATTACK_RIGHT : ATTACK_LEFT].getTexture();
			currentClip = isFacing == FACING_RIGHT ? &frameClipsAttackRight[frameAttack / 6] : &frameClipsAttackLeft[frameAttack / 6];
		}

		else if (!typeFlag.isStandingOnGround) {
			typeFlag.isStanding = false;
			frameJump++;
			if (frameJump / 5 >= 5) frameJump = 0;
			currentTexture = gLoadMainCharacter[isFacing == FACING_RIGHT ? JUMP_RIGHT : JUMP_LEFT].getTexture();
			currentClip = isFacing == FACING_RIGHT ? &frameClipsJumpRight[frameJump / 5] : &frameClipsJumpLeft[frameJump / 5];
		}

		else if (typeFlag.goRight || typeFlag.goLeft) {
			typeFlag.isStanding = false;
			frameRun++;
			if (frameRun / 8 >= 8) frameRun = 0;
			currentTexture = gLoadMainCharacter[isFacing == FACING_RIGHT ? RUN_RIGHT : RUN_LEFT].getTexture();
			currentClip = isFacing == FACING_RIGHT ? &frameClipsRunRight[frameRun / 8] : &frameClipsRunLeft[frameRun / 8];
		}


		else {
			typeFlag.isStanding = true;
			frameStand++;
			if (frameStand / 7 >= 7) frameStand = 0;
			currentTexture = gLoadMainCharacter[isFacing == FACING_RIGHT ? STAND_RIGHT : STAND_LEFT].getTexture();
			currentClip = isFacing == FACING_RIGHT ? &frameClipsStandRight[frameStand / 7] : &frameClipsStandLeft[frameStand / 7];
		}
	}
	else {
		mVelX = 0;
		if (frameDeath / 5 <= 12)  frameDeath++;
		currentTexture = gLoadMainCharacter[isFacing == FACING_RIGHT_E_AZ ? DEAD_RIGHT : DEAD_LEFT].getTexture();
		currentClip = isFacing == FACING_RIGHT_E_AZ ? &frameClipsDeadRight[frameDeath / 6] : &frameClipsDeadLeft[frameDeath / 6];
	}

	healthBar.render(renderer, 0, 0);

	manaBar.render(renderer, 0, 100);

	SDL_Rect renderQuad = { mPosX - gGameMap.getCameraX(),mPosY - gGameMap.getCameraY(),currentClip->w,currentClip->h };

	SDL_RenderCopy(renderer, currentTexture, currentClip, &renderQuad);

	handleAndRenderProjectile(renderer);

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


vector <Projectile*>& Character::getProjectileListArrow() {
	return ProjectileListArrow;
}

HealthBar& Character:: getHealthBar() {
	return healthBar;
}

ManaBar& Character::getManaBar() {
	return manaBar;
}

int Character::getPosX() {
	return mPosX;
}

int Character::getPosY() {
	return mPosY;
}

void Character::setPosX(int posx) {
	mPosX = posx;
}

void Character::setPosY(int posy) {
	mPosY = posy;
}


void Character::setVelX(int velx) {
	mVelX = velx;
}

void Character::setVelY(int vely) {
	mVelY = vely;
}


void Character::clearProjectiles() {
	for (auto x : ProjectileListArrow) {
		delete x;
	}
	ProjectileListArrow.clear();
}


void Character::resetCharacter() {

	mPosX = 0;
	mPosY = 0;

	mVelX = 0;
	mVelY = 0;

	healthBar.setMaxHealth(CHARACTER_HEALTH);
	healthBar.setHealth(CHARACTER_HEALTH);
	manaBar.setMaxMana(CHARACTER_MANA);
	manaBar.setMana(CHARACTER_MANA);

	frameRun = 0;
	frameStand = 0;
	frameJump = 0;
	frameAttack = 0;
	frameDeath = 0;

	timeRespawn = 0;

	isFacing = FACING_RIGHT;

	typeFlag.isStanding = true;

	typeFlag.isStandingOnGround = false;

	typeFlag.goLeft = false;

	typeFlag.goRight = false;

	typeFlag.isFallingIntoHole = false;

	typeFlag.isAttacking = false;

	typeFlag.isHurting = false;

	typeFlag.isCollidingWithEnemyCD = false;

	typeFlag.isCollidingWithEnemyAZ = false;

	typeFlag.isCollidingWithEnemyBOSS = false;

	typeFlag.isCasting = false;

	clearProjectiles();
}
