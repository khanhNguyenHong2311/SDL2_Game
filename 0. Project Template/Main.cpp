#define SDL_MAIN_HANDLE
#include"Library.h"
#include"Globals.h"
#include"LTexture.h"
#include"EnemyCD.h"
#include"EnemyAZ.h"
#include"EnemyBOSS.h"
#include"Map.h"
#include"HealthBar.h"
#include"Projectile.h"
using namespace std;



bool init() {
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "SDL couln't initialize ! SDL Error :" << SDL_GetError();
		success = false;
	}
	else {
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			cout << "Warning : Linear texture filtering not enabled ! " << endl;
		}

		gWindow = SDL_CreateWindow("Game cua Khanh", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			cout << "Window could not be created! SDL Error :" << SDL_GetError() << endl;
			success = false;
		}
		else {
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL) {
				cout << "Renderer couldn't be created! SDL Error : " << SDL_GetError() << endl;
				success = false;
			}
			else {
				int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;  
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					cout << "SDL_image couldn't initialize! SDL_image error : " << IMG_GetError() << endl;
					success = false;
				}
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}
	return success;
}



void close() {
	gLoadBackGround.free();
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
}

bool LoadMedia() {
	bool success = true;

	gFont = TTF_OpenFont("font/ThaleahFat.ttf",28);

	gLoadBackGround.loadFromFile("image/background/background.jpg", gRenderer);
	gMainCharacter.getHealthBar().loadFromFile("image/icons/healthbar.png", gRenderer);

	gLoadMainCharacter[RUN_RIGHT].loadFromFile("image/character/maincharacter/RUN_RIGHT.png", gRenderer);
	gLoadMainCharacter[RUN_LEFT].loadFromFile("image/character/maincharacter/RUN_LEFT.png", gRenderer);
	gLoadMainCharacter[STAND_RIGHT].loadFromFile("image/character/maincharacter/STAND_RIGHT.png", gRenderer);
	gLoadMainCharacter[STAND_LEFT].loadFromFile("image/character/maincharacter/STAND_LEFT.png", gRenderer);
	gLoadMainCharacter[JUMP_RIGHT].loadFromFile("image/character/maincharacter/JUMP_RIGHT.png", gRenderer);
	gLoadMainCharacter[JUMP_LEFT].loadFromFile("image/character/maincharacter/JUMP_LEFT.png", gRenderer);
	gLoadMainCharacter[ATTACK_RIGHT].loadFromFile("image/character/maincharacter/ATTACK_RIGHT.png", gRenderer);
	gLoadMainCharacter[ATTACK_LEFT].loadFromFile("image/character/maincharacter/ATTACK_LEFT.png", gRenderer);
	gLoadMainCharacter[HURT_LEFT].loadFromFile("image/character/maincharacter/HURT_LEFT.png", gRenderer);
	gLoadMainCharacter[HURT_RIGHT].loadFromFile("image/character/maincharacter/HURT_RIGHT.png", gRenderer);
	gLoadMainCharacter[DEAD_LEFT].loadFromFile("image/character/maincharacter/DEAD_LEFT.png", gRenderer);
	gLoadMainCharacter[DEAD_RIGHT].loadFromFile("image/character/maincharacter/DEAD_RIGHT.png", gRenderer);


	gLoadEnemiesCD[STAND_RIGHT_E_CD].loadFromFile("image/character/enemies/CD_STAND_RIGHT.png", gRenderer);
	gLoadEnemiesCD[STAND_LEFT_E_CD].loadFromFile("image/character/enemies/CD_STAND_LEFT.png", gRenderer);
	gLoadEnemiesCD[RUN_LEFT_E_CD].loadFromFile("image/character/enemies/CD_RUN_LEFT.png", gRenderer);
	gLoadEnemiesCD[RUN_RIGHT_E_CD].loadFromFile("image/character/enemies/CD_RUN_RIGHT.png", gRenderer);
	gLoadEnemiesCD[ATTACK_RIGHT_E_CD].loadFromFile("image/character/enemies/CD_ATTACK_RIGHT.png", gRenderer);
	gLoadEnemiesCD[ATTACK_LEFT_E_CD].loadFromFile("image/character/enemies/CD_ATTACK_LEFT.png", gRenderer);
	gLoadEnemiesCD[HURT_RIGHT_E_CD].loadFromFile("image/character/enemies/CD_HURT_LEFT.png", gRenderer);
	gLoadEnemiesCD[HURT_LEFT_E_CD].loadFromFile("image/character/enemies/CD_HURT_RIGHT.png", gRenderer);
	gLoadEnemiesCD[DEAD_RIGHT_E_CD].loadFromFile("image/character/enemies/CD_DEAD_RIGHT.png", gRenderer);
	gLoadEnemiesCD[DEAD_LEFT_E_CD].loadFromFile("image/character/enemies/CD_DEAD_LEFT.png", gRenderer);

	gLoadEnemiesAZ[RUN_RIGHT_E_AZ].loadFromFile("image/character/enemies/AZ_RUN_RIGHT.png", gRenderer);
	gLoadEnemiesAZ[RUN_LEFT_E_AZ].loadFromFile("image/character/enemies/AZ_RUN_LEFT.png", gRenderer);
	gLoadEnemiesAZ[HURT_RIGHT_E_AZ].loadFromFile("image/character/enemies/AZ_HURT_RIGHT.png", gRenderer);
	gLoadEnemiesAZ[HURT_LEFT_E_AZ].loadFromFile("image/character/enemies/AZ_HURT_LEFT.png", gRenderer);
	gLoadEnemiesAZ[ATTACK_RIGHT_E_AZ].loadFromFile("image/character/enemies/AZ_ATTACK_RIGHT.png", gRenderer);
	gLoadEnemiesAZ[ATTACK_LEFT_E_AZ].loadFromFile("image/character/enemies/AZ_ATTACK_LEFT.png", gRenderer);
	gLoadEnemiesAZ[DEAD_RIGHT_E_AZ].loadFromFile("image/character/enemies/AZ_DEAD_RIGHT.png", gRenderer);
	gLoadEnemiesAZ[DEAD_LEFT_E_AZ].loadFromFile("image/character/enemies/AZ_DEAD_LEFT.png", gRenderer);

	gLoadEnemiesBOSS[RUN_RIGHT_E_BOSS].loadFromFile("image/character/enemies/BOSS_RUN_RIGHT.png", gRenderer);
	gLoadEnemiesBOSS[RUN_LEFT_E_BOSS].loadFromFile("image/character/enemies/BOSS_RUN_LEFT.png", gRenderer);
	gLoadEnemiesBOSS[HURT_RIGHT_E_BOSS].loadFromFile("image/character/enemies/BOSS_HURT_RIGHT.png", gRenderer);
	gLoadEnemiesBOSS[HURT_LEFT_E_BOSS].loadFromFile("image/character/enemies/BOSS_HURT_LEFT.png", gRenderer);
	gLoadEnemiesBOSS[ATTACK_RIGHT_E_BOSS].loadFromFile("image/character/enemies/BOSS_ATTACK_RIGHT.png", gRenderer);
	gLoadEnemiesBOSS[ATTACK_LEFT_E_BOSS].loadFromFile("image/character/enemies/BOSS_ATTACK_LEFT.png", gRenderer);
	gLoadEnemiesBOSS[DEAD_RIGHT_E_BOSS].loadFromFile("image/character/enemies/BOSS_DEAD_RIGHT.png", gRenderer);
	gLoadEnemiesBOSS[DEAD_LEFT_E_BOSS].loadFromFile("image/character/enemies/BOSS_DEAD_LEFT.png", gRenderer);

	gLoadProjectile[FIRE_BALL].loadFromFile("image/projectile/fireball/FIRE_BALL.png", gRenderer);
	gLoadProjectile[FIRE_BALL_EXPLOSION].loadFromFile("image/projectile/fireball/FIRE_BALL_EXPLOSION.png", gRenderer);
	gLoadProjectile[METEORITE].loadFromFile("image/projectile/meteorite/METEORITE_RUN.png", gRenderer);
	gLoadProjectile[METEORITE_EXPLOSION].loadFromFile("image/projectile/meteorite/METEORITE_EXPLOSION.png", gRenderer);


	gGameMap.loadMap("map.txt");
	gGameMap.loadTiles(gRenderer);
	return success;
}


vector<EnemyCD*> MakeEnemyCDList() {

	for (int i = 0; i < 1; ++i) {
		EnemyCD* pEnemyCD = new EnemyCD();
		pEnemyCD->getHealthBar().setMaxHealth(ENEMY_BOSS_HEALTH);
		pEnemyCD->getHealthBar().setHealth(ENEMY_BOSS_HEALTH);
		pEnemyCD->setClips();
		pEnemyCD->setPosX(200 + i * 2000);
		pEnemyCD->setPosY(0);
		pEnemyCD->setLimitPos(i*1000, i * 500 + 2000);
		listEnemiesCD.push_back(pEnemyCD);
	}

	return listEnemiesCD;
}	

vector<EnemyAZ*> MakeEnemyAZList() {
	for (int i = 0; i < 1; ++i) {
		EnemyAZ* pEnemyAZ= new EnemyAZ();
		pEnemyAZ->getHealthBar().setMaxHealth(ENEMY_AZ_HEALTH);
		pEnemyAZ->getHealthBar().setHealth(ENEMY_AZ_HEALTH);
		pEnemyAZ->setClips();
		pEnemyAZ->setPosX(950 + i * 2000);
		pEnemyAZ->setPosY(96);
		pEnemyAZ->setLimitPos(800 , i * 500 + 1000);
		listEnemiesAZ.push_back(pEnemyAZ);
	}

	return listEnemiesAZ;
}

vector<EnemyBOSS*> MakeEnemyBOSSList() {
	for (int i = 0; i <1; ++i) {
		EnemyBOSS* pEnemyBOSS = new EnemyBOSS();
		pEnemyBOSS->getHealthBar().setMaxHealth(ENEMY_BOSS_HEALTH);
		pEnemyBOSS->getHealthBar().setHealth(ENEMY_BOSS_HEALTH);
		pEnemyBOSS->setClips();
		pEnemyBOSS->setPosX(800 + i * 2000);
		pEnemyBOSS->setPosY(96);
		pEnemyBOSS->setLimitPos(700, 2000);
		if (pEnemyBOSS !=NULL) listEnemiesBOSS.push_back(pEnemyBOSS);
	}

	return listEnemiesBOSS;
}


int main(int argc, char* args[]) {

	if (!init()) {
		cout << "Failed to initialize !" << endl;
		return -1;
	}

	if (!LoadMedia()) {
		cout << "Failed to load background !" << endl;
		return -1;
	}

	timeGameText.setColor(RED_TEXT);
	gMainCharacter.getHealthBar().setMaxHealth(CHARACTER_HEALTH);
	gMainCharacter.getHealthBar().setHealth(CHARACTER_HEALTH);

	vector<EnemyCD*> listEnemiesCD = MakeEnemyCDList();
	vector<EnemyAZ*> listEnemiesAZ = MakeEnemyAZList();
	vector<EnemyBOSS*> listEnemiesBOSS = MakeEnemyBOSSList();

	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			if (gMainCharacter.getHealthBar().getCurrentHealth()>0) gMainCharacter.handleMotion(e);
		}

		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);
		gLoadBackGround.render(0, 0, gRenderer);
		gGameMap.drawMap(gRenderer);
		gMainCharacter.FallingInTheHole();
		gMainCharacter.setClips();
		gMainCharacter.CenterEntityOnMap();
		gMainCharacter.checkMapCollision();


		for (int i = 0;i < listEnemiesCD.size();i++) {
			EnemyCD* pEnemyCD = listEnemiesCD[i];
			if (pEnemyCD != NULL) {
				if (pEnemyCD->getHealthBar().getCurrentHealth() > 0) {
					pEnemyCD->handleMotion();
					gMainCharacter.checkCharacterCollisionWithEnemy(pEnemyCD,NULL,NULL);
					gMainCharacter.checkCharacterAttackedEnemy(pEnemyCD,NULL,NULL);
					pEnemyCD->checkEnemyCollisionWithCharacter(gMainCharacter.getPosX(), gMainCharacter.getPosY());
					pEnemyCD->FallingInTheHole();
				}
				pEnemyCD->setCameraX(gGameMap.getCameraX());
				pEnemyCD->setCameraY(gGameMap.getCameraY());
				pEnemyCD->checkMapCollision();
				pEnemyCD->render(gRenderer);
			}
		}


		for (int i = 0;i < listEnemiesAZ.size();i++) {
			EnemyAZ* pEnemyAZ = listEnemiesAZ[i];
			if (pEnemyAZ != NULL) {
				if (pEnemyAZ->getHealthBar().getCurrentHealth() > 0) {
					pEnemyAZ->handleMotion();
					gMainCharacter.checkCharacterCollisionWithEnemy(NULL, pEnemyAZ,NULL);
					gMainCharacter.checkCharacterAttackedEnemy(NULL, pEnemyAZ,NULL);
					gMainCharacter.checkCharacterCollisionWithProjectile(pEnemyAZ,NULL);
					pEnemyAZ->checkEnemyCollisionWithCharacter(gMainCharacter.getPosX(), gMainCharacter.getPosY());
				}
				pEnemyAZ->setCameraX(gGameMap.getCameraX());
				pEnemyAZ->setCameraY(gGameMap.getCameraY());
				pEnemyAZ->checkMapCollision();
				pEnemyAZ->render(gRenderer);
			}
		}

		for (int i = 0;i < listEnemiesBOSS.size();i++) {
			EnemyBOSS* pEnemyBOSS = listEnemiesBOSS[i];	
			if (pEnemyBOSS != NULL) {
				if (pEnemyBOSS->getHealthBar().getCurrentHealth() > 0) {
					pEnemyBOSS->handleMotion();
					gMainCharacter.checkCharacterCollisionWithEnemy(NULL,NULL, pEnemyBOSS);
					gMainCharacter.checkCharacterAttackedEnemy(NULL, NULL, pEnemyBOSS);
					gMainCharacter.checkCharacterCollisionWithProjectile(NULL , pEnemyBOSS);
					pEnemyBOSS->checkEnemyCollisionWithCharacter(gMainCharacter.getPosX(), gMainCharacter.getPosY());
				}
				pEnemyBOSS->setCameraX(gGameMap.getCameraX());
				pEnemyBOSS->setCameraY(gGameMap.getCameraY());
				pEnemyBOSS->checkMapCollision();
				pEnemyBOSS->render(gRenderer);
			}
		}

		gMainCharacter.render(gRenderer);

		string strTimeGameText = "Health : ";
		int valTimeGameText = gMainCharacter.getHealthBar().getCurrentHealth();
		//string	strTime = to_string(valTimeGameText);
		strTimeGameText += to_string(valTimeGameText);
		timeGameText.setText(strTimeGameText);
		timeGameText.loadFromRenderText(gFont, gRenderer);
		timeGameText.render(gRenderer, SCREEN_HEIGHT - 200, 15);

		SDL_RenderPresent(gRenderer);
	}



	for (auto x  : listEnemiesCD) {
		delete x;  
	}
	for (auto x : listEnemiesAZ) {
		delete x;
	}
	for (auto x : listEnemiesBOSS) {
		delete x;
	}

	close();

	return 0;
}
