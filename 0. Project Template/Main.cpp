#define SDL_MAIN_HANDLE
#include"Library.h"
#include"Globals.h"
#include"LTexture.h"
#include"EnemyCD.h"
#include"Map.h"
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

	gLoadBackGround.loadFromFile("image/background/background.jpg", gRenderer);
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


	gLoadEnemiesCD[STAND_RIGHT_E_CD].loadFromFile("image/character/enemies/CD_STAND_RIGHT.png", gRenderer);
	gLoadEnemiesCD[STAND_LEFT_E_CD].loadFromFile("image/character/enemies/CD_STAND_LEFT.png", gRenderer);
	gLoadEnemiesCD[RUN_LEFT_E_CD].loadFromFile("image/character/enemies/CD_RUN_LEFT.png", gRenderer);
	gLoadEnemiesCD[RUN_RIGHT_E_CD].loadFromFile("image/character/enemies/CD_RUN_RIGHT.png", gRenderer);
	gLoadEnemiesCD[ATTACK_RIGHT_E_CD].loadFromFile("image/character/enemies/CD_ATTACK_RIGHT.png", gRenderer);
	gLoadEnemiesCD[ATTACK_LEFT_E_CD].loadFromFile("image/character/enemies/CD_ATTACK_LEFT.png", gRenderer);
	gLoadEnemiesCD[HURT_RIGHT_E_CD].loadFromFile("image/character/enemies/CD_HURT_LEFT.png", gRenderer);
	gLoadEnemiesCD[HURT_LEFT_E_CD].loadFromFile("image/character/enemies/CD_HURT_RIGHT.png", gRenderer);

	gGameMap.loadMap("map.txt");
	gGameMap.loadTiles(gRenderer);
	return success;
}


vector<EnemyCD*> MakeEnemyCDList() {

	for (int i = 0; i < 1; ++i) {
		EnemyCD* pEnemyCD = new EnemyCD();
		pEnemyCD->setClips();
		pEnemyCD->setPosX(0 + i * 2000);
		pEnemyCD->setPosY(0);
		pEnemyCD->setLimitPos(200, i * 500 + 1200);
		listEnemies.push_back(pEnemyCD);
	}

	return listEnemies;
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

	vector<EnemyCD*> listEnemies = MakeEnemyCDList();

	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			gMainCharacter.handleMotion(e);
		}

		gMainCharacter.checkMapCollision();
		gMainCharacter.FallingInTheHole();
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF,0xFF);
		SDL_RenderClear(gRenderer);
		gLoadBackGround.render(0, 0, gRenderer);
		gGameMap.drawMap(gRenderer);
		gMainCharacter.setClips();
		gMainCharacter.CenterEntityOnMap();


		for (int i = 0;i < listEnemies.size();i++) {
			EnemyCD* pEnemyCD = listEnemies[i];
			if (pEnemyCD != NULL) {
				pEnemyCD->setCameraX(gGameMap.getCameraX());
				pEnemyCD->setCameraY(gGameMap.getCameraY());
				pEnemyCD->handleMotion();
				pEnemyCD->checkMapCollision();
				gMainCharacter.checkCharacterCollisionWithEnemyCD(pEnemyCD->getPosX(), pEnemyCD->getPosY());
				gMainCharacter.checkCharacterAttackedEnemyCD(pEnemyCD);
				pEnemyCD->checkEnemyCollisionWithCharacter(gMainCharacter.getPosX(), gMainCharacter.getPosY());
				pEnemyCD->FallingInTheHole();
				pEnemyCD->render(gRenderer);
			}
		}

		gMainCharacter.render(gRenderer);



		SDL_RenderPresent(gRenderer);
	}



	for (auto x  : listEnemies) {
		delete x;  
	}

	close();

	return 0;
}
