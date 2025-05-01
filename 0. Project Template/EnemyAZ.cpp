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

	frameWidth = ENEMY_AZ_WIDTH;
	frameHeight = ENEMY_AZ_HEIGHT;

	frameRun = 0;
	frameStand = 0;
	frameAttack = 0;
	frameHurt = 0;

	timeStand = 200;

	timeCoolDownAttack = 20;

	limitPosA = 0;
	limitPosB = 0;
}




void EnemyAZ::setClips() {
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


		for (int i = 0;i < 5;i++) {
			frameClipsRunRight[i].x = i * frameWidth;
			frameClipsRunRight[i].y = 0;
			frameClipsRunRight[i].w = frameWidth;
			frameClipsRunRight[i].h = frameHeight;

			frameClipsRunLeft[i].x = (4 - i) * frameWidth;
			frameClipsRunLeft[i].y = 0;
			frameClipsRunLeft[i].w = frameWidth;
			frameClipsRunLeft[i].h = frameHeight;
		}
	}
}


void EnemyAZ::handleMotion() {

	if (typeMotion.goRight) {
		mVelX = ENEMY_AZ_VEL;
	}
	else if (typeMotion.goLeft) {
		mVelX = -ENEMY_AZ_VEL;
	}
	else if (typeMotion.isStanding) {
		mVelX = 0;
	}

	moveToCharacterIfInRange(gMainCharacter.getPosX(), gMainCharacter.getPosY());
}



void EnemyAZ::checkMapCollision() {

	mVelY += ENEMY_AZ_GRAVITY_SPEED;
	if (mVelY > ENEMY_AZ_MAX_GRAVITY_SPEED) {
		mVelY = ENEMY_AZ_MAX_GRAVITY_SPEED;
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


void EnemyAZ::checkEnemyAttackedCharacter() {

	int rightCharacter = gMainCharacter.getPosX() + CHARACTER_WIDTH;
	int rightEnemyCD = mPosX + (ENEMY_CD_WIDTH) * 3 / 4;

	if (isFacing == FACING_RIGHT_E_CD && (frameAttack / 8 == 6) && (rightCharacter >= rightEnemyCD)) gMainCharacter.isHurting();
	else if (isFacing == FACING_LEFT_E_CD && (frameAttack / 8 == 6) && (rightCharacter <= rightEnemyCD)) gMainCharacter.isHurting();
}


void EnemyAZ::moveToCharacterIfInRange(int characterPosX, int characterPosY) {
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
			mVelX = 3 * ENEMY_AZ_VEL;
		}
		else if (characterPosX < mPosX) {
			typeMotion.goRight = false;
			typeMotion.goLeft = true;
			mVelX = -3 * ENEMY_AZ_VEL;
		}
	}

	if (characterPosX < limitPosA || characterPosX > limitPosB || enemyRow != characterRow) {
		typeMotion.isChasing = false;
	}
}


void EnemyAZ :: createProjectile(SDL_Renderer* renderer) {
	Projectile* pProjectile = new Projectile();
	pProjectile->setClips();

	float projectileStartX = 0;
	float projectileStartY = 0;
	if (isFacing == FACING_RIGHT_E_AZ) {
		projectileStartX = mPosX + frameWidth - 20.0f;
		projectileStartY = mPosY + 40.0f;
	}
	else {
		projectileStartX = mPosX;
		projectileStartY = mPosY + 40.0f;
	}

	pProjectile->setPosX(projectileStartX);
	pProjectile->setPosY(projectileStartY);

	float targetX = gMainCharacter.getPosX() + CHARACTER_WIDTH / 2.0f;  
	float targetY = gMainCharacter.getPosY() + CHARACTER_HEIGHT / 2.0f; 

	float deltaX = targetX - projectileStartX;
	float deltaY = targetY - projectileStartY;

	float distance = sqrt(deltaX * deltaX + deltaY * deltaY);
	if (distance == 0.0f) distance = 1.0f;

	if (distance >= 2000.0f) {
		return;
	}

	float unitVelX = PROJECTILE_FIRE_BALL_VEL * (deltaX / distance);
	float unitVelY = PROJECTILE_FIRE_BALL_VEL * (deltaY / distance);

	pProjectile->setVelX(unitVelX);
	pProjectile->setVelY(unitVelY);

	float angle = atan2(unitVelY, unitVelX) * 180.0f / M_PI;

	pProjectile->setRotationAngle(angle);

	pProjectile->setIsMoving(true);

	ProjectileList.push_back(pProjectile);
}



void EnemyAZ::handleAndRenderProjectile(SDL_Renderer* renderer ) {
	for (int i = 0;i < ProjectileList.size();i++) {
		Projectile* pProjectile = ProjectileList[i];
		if (pProjectile != NULL) {
			if (pProjectile->getIsMoving()) {
				pProjectile->handleMotion(SCREEN_WIDTH + gGameMap.getCameraX(), SCREEN_HEIGHT);
				pProjectile->renderProjectile( renderer );
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



void EnemyAZ::render(SDL_Renderer* renderer) {

	SDL_Rect* currentClip = nullptr;

	SDL_Texture* currentTexture = nullptr;

	// Use for all typeMotion
	if (typeMotion.goRight) {
		isFacing = FACING_RIGHT_E_AZ;
	}
	else if (typeMotion.goLeft) {
		isFacing = FACING_LEFT_E_AZ;
	}

	timeCoolDownAttack--;
	if (timeCoolDownAttack == 0) {	
		createProjectile(renderer);
		timeCoolDownAttack =20;
	}
	handleAndRenderProjectile(renderer );

	frameRun++;
	if (frameRun / 5 >= 5) frameRun = 0;

	if (gMainCharacter.getAttackSuccessAZ()) { 
		frameHurt++;
		if (frameHurt == 1) {
			createProjectile(renderer);
		}
		if (frameHurt / 5 >= 5) {
			frameHurt = 0;
			gMainCharacter.setAttackSuccessAZ(false);
		}
		if (isFacing == FACING_LEFT_E_AZ) {
			currentTexture = gLoadEnemiesAZ[HURT_LEFT_E_AZ].getTexture();
			currentClip = &frameClipsHurtRight[frameHurt / 5];
		}
		else if (isFacing == FACING_RIGHT_E_AZ) {
			currentTexture = gLoadEnemiesAZ[HURT_RIGHT_E_AZ].getTexture();
			currentClip = &frameClipsHurtLeft[frameHurt / 5];
		}
	}
	else if ((mPosX == limitPosB && isFacing == FACING_RIGHT_E_AZ) || (mPosX == limitPosA && isFacing == FACING_LEFT_E_AZ)) {
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
			currentTexture = gLoadEnemiesAZ[RUN_RIGHT_E_AZ].getTexture();
			currentClip = &frameClipsRunRight[frameRun / 5];
		}
		else if (mPosX == limitPosA) {
			currentTexture = gLoadEnemiesAZ[RUN_LEFT_E_AZ].getTexture();
			currentClip = &frameClipsRunLeft[frameRun / 5];
		}
	}

	else if (mPosX > limitPosB) {
		typeMotion.goLeft = true;
		typeMotion.goRight = false;
		currentTexture = gLoadEnemiesAZ[RUN_LEFT_E_AZ].getTexture();
		currentClip = &frameClipsRunLeft[frameRun / 5];

	}
	else if (mPosX < limitPosA) {
		typeMotion.goRight = true;
		typeMotion.goLeft = false;
		currentTexture = gLoadEnemiesAZ[RUN_RIGHT_E_AZ].getTexture();
		currentClip = &frameClipsRunRight[frameRun / 5];

	}
	else {
		if (isFacing == FACING_RIGHT_E_AZ) {
			currentTexture = gLoadEnemiesAZ[RUN_RIGHT_E_AZ].getTexture();
			currentClip = &frameClipsRunRight[frameRun / 5];
		}
		else {
			currentTexture = gLoadEnemiesAZ[RUN_LEFT_E_AZ].getTexture();
			currentClip = &frameClipsRunLeft[frameRun / 5];
		}
	}


	SDL_Rect renderQuad = { mPosX - gGameMap.getCameraX(),mPosY - gGameMap.getCameraY(),currentClip->w,currentClip->h };

	SDL_RenderCopy(renderer, currentTexture, currentClip, &renderQuad);
}



void EnemyAZ::setLimitPos(int limitposa, int limitposb) {
	limitPosA = limitposa;
	limitPosB = limitposb;
}



int EnemyAZ::getIsFacing() {
	return isFacing;
}

void EnemyAZ::isHurting() {
	typeMotion.isHurting = true;
}

bool EnemyAZ::getIsColliding() {
	return typeMotion.isCollidingWithCharacter;
}


void EnemyAZ:: setProjectileList(vector <Projectile*> projectilelist) {
	ProjectileList = projectilelist;
}


vector <Projectile*> EnemyAZ::getProjectileList() {
	return ProjectileList;
}



void EnemyAZ::setCameraX(int camerax) {
	cameraX = camerax;
}

void EnemyAZ::setCameraY(int cameray) {
	cameraY = cameray;
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

int EnemyAZ::getPosX() {
	return mPosX;
}

int EnemyAZ::getPosY() {
	return mPosY;
}