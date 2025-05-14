#define SDL_MAIN_HANDLE
#include"Library.h"
#include"Globals.h"
#include"LTexture.h"
#include"EnemyCD.h"
#include"EnemyAZ.h"
#include"EnemyBOSS.h"
#include"Map.h"
#include"HealthBar.h"
#include"ManaBar.h"
#include"Projectile.h"
#include"Menu.h"
#include"TimeAndScore.h"

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
	gLoadBackGroundGame.free();
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
	gFontA = TTF_OpenFont("font/ThaleahFat.ttf", 40);

	gLoadBackGroundGame.loadFromFile("image/background/background.jpg", gRenderer);
	gLoadBackGroundMenu.loadFromFile("image/background/backgroundmenu.png", gRenderer);
	gLoadBackGroundMenuWin.loadFromFile("image/background/backgroundmenu_win.png",gRenderer);
	gLoadBackGroundMenuLose.loadFromFile("image/background/backgroundmenu_lose.png", gRenderer);
	gLoadBackGroundMenuHowToPlay.loadFromFile("image/background/backgroundmenu_howtoplay.png", gRenderer);
	gLoadBackGroundMenuHighScores.loadFromFile("image/background/backgroundmenu_highscores.png", gRenderer);
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
	gLoadEnemiesBOSS[STAND_LEFT_E_BOSS].loadFromFile("image/character/enemies/BOSS_STAND.png", gRenderer);

	gLoadEnemiesBOSS[RUN_RIGHT_E_BOSS_PHASE2].loadFromFile("image/character/enemies/BOSSPLUS_RUN_RIGHT.png", gRenderer);
	gLoadEnemiesBOSS[RUN_LEFT_E_BOSS_PHASE2].loadFromFile("image/character/enemies/BOSSPLUS_RUN_LEFT.png", gRenderer);
	gLoadEnemiesBOSS[HURT_RIGHT_E_BOSS_PHASE2].loadFromFile("image/character/enemies/BOSSPLUS_HURT_RIGHT.png", gRenderer);
	gLoadEnemiesBOSS[HURT_LEFT_E_BOSS_PHASE2].loadFromFile("image/character/enemies/BOSSPLUS_HURT_LEFT.png", gRenderer);
	gLoadEnemiesBOSS[ATTACK_RIGHT_E_BOSS_PHASE2].loadFromFile("image/character/enemies/BOSSPLUS_ATTACK_RIGHT.png", gRenderer);
	gLoadEnemiesBOSS[ATTACK_LEFT_E_BOSS_PHASE2].loadFromFile("image/character/enemies/BOSSPLUS_ATTACK_LEFT.png", gRenderer);
	gLoadEnemiesBOSS[DEAD_RIGHT_E_BOSS_PHASE2].loadFromFile("image/character/enemies/BOSSPLUS_DEAD_RIGHT.png", gRenderer);
	gLoadEnemiesBOSS[DEAD_LEFT_E_BOSS_PHASE2].loadFromFile("image/character/enemies/BOSSPLUS_DEAD_LEFT.png", gRenderer);
	gLoadEnemiesBOSS[STAND_LEFT_E_BOSS_PHASE2].loadFromFile("image/character/enemies/BOSSPLUS_STAND.png", gRenderer);


	gLoadProjectile[FIRE_BALL].loadFromFile("image/projectile/fireball/FIRE_BALL.png", gRenderer);
	gLoadProjectile[FIRE_BALL_EXPLOSION].loadFromFile("image/projectile/fireball/FIRE_BALL_EXPLOSION.png", gRenderer);
	gLoadProjectile[METEORITE].loadFromFile("image/projectile/meteorite/METEORITE_RUN.png", gRenderer);
	gLoadProjectile[METEORITE_EXPLOSION].loadFromFile("image/projectile/meteorite/METEORITE_EXPLOSION.png", gRenderer);
	gLoadProjectile[STAR].loadFromFile("image/projectile/star/STAR.png", gRenderer);
	gLoadProjectile[ARROW].loadFromFile("image/projectile/arrow/ARROW.png", gRenderer);
	gLoadProjectile[ARROW_EXPLOSION].loadFromFile("image/projectile/arrow/ARROW_EXPLOSION.png", gRenderer);

	gLoadEffects[RECOVER].loadFromFile("image/effects/RECOVER.png", gRenderer);
	gLoadEffects[SIGNAL].loadFromFile("image/effects/SIGNAL.png", gRenderer);
	gLoadEffects[MINE_EXPLOSION].loadFromFile("image/effects/MINE_EXPLOSION.png", gRenderer);

	gGameMap.loadMap("map.txt");
	gGameMap.loadTiles(gRenderer);
	return success;
}


vector<EnemyCD*> MakeEnemyCDList() {

	for (int i = 0; i < 0; ++i) {
		EnemyCD* pEnemyCD = new EnemyCD();
		pEnemyCD->getHealthBar().setMaxHealth(ENEMY_CD_HEALTH);
		pEnemyCD->getHealthBar().setHealth(ENEMY_CD_HEALTH);
		pEnemyCD->setClips();
		pEnemyCD->setPosX(200 + i * 2000);
		pEnemyCD->setPosY(0);
		pEnemyCD->setLimitPos(i*1000, i * 500 + 2000);
		listEnemiesCD.push_back(pEnemyCD);
	}

	return listEnemiesCD;
}	

vector<EnemyAZ*> MakeEnemyAZList() {
	for (int i = 0; i < 0; ++i) {
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

void restartGame() {
	score = 0;
	timeDelayGameOver = 100;
	startTime = SDL_GetTicks();
	gGameMap.loadMap("map.txt");
	gGameMap.loadTiles(gRenderer);

	for (auto x : listEnemiesCD) delete x;
	for (auto x : listEnemiesAZ) delete x;
	for (auto x : listEnemiesBOSS) delete x;
	listEnemiesCD.clear();
	listEnemiesAZ.clear();
	listEnemiesBOSS.clear();

	gMainCharacter.resetCharacter();


	listEnemiesCD = MakeEnemyCDList();
	listEnemiesAZ = MakeEnemyAZList();
	listEnemiesBOSS = MakeEnemyBOSSList();
}




void showMainMenu(bool& quit, bool& startGame, bool& isPaused, bool& resumeGame, bool& isRestart, bool& backToMenu, bool& howToPlay , bool& highScore) {
	gMenu.setMenuType(MAIN_MENU);
	while (!quit && !startGame) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) quit = true;
			gMenu.handleMouse(e, quit, startGame, isPaused, resumeGame, isRestart, backToMenu, howToPlay , highScore);
		}

		if (howToPlay) {
			gMenu.setMenuType(HOW_TO_PLAY_MENU);
			howToPlay = false;

			bool inHowToPlay = true;
			while (inHowToPlay && !quit) {
				while (SDL_PollEvent(&e)) {
					if (e.type == SDL_QUIT) {
						quit = true;
						break;
					}
					gMenu.handleMouse(e, quit, startGame, isPaused, resumeGame, isRestart, backToMenu, howToPlay , highScore);
				}

				if (backToMenu) {
					backToMenu = false;
					gMenu.setMenuType(MAIN_MENU);
					inHowToPlay = false;
				}

				SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
				SDL_RenderClear(gRenderer);
				gLoadBackGroundMenuHowToPlay.render(0, 0, gRenderer);
				gMenu.render(gRenderer);
				SDL_RenderPresent(gRenderer);
			}

			continue;
		}

		if (highScore) {
			gMenu.setMenuType(HIGH_SCORE_MENU);
			highScore = false;

			bool inHighScore = true;
			while (inHighScore && !quit) {
				while (SDL_PollEvent(&e)) {
					if (e.type == SDL_QUIT) {
						quit = true;
						break;
					}
					gMenu.handleMouse(e, quit, startGame, isPaused, resumeGame, isRestart, backToMenu, howToPlay, highScore);
				}

				if (backToMenu) {
					backToMenu = false;

					gMenu.setMenuType(MAIN_MENU);

					inHighScore = false;

					showMainMenu(quit, startGame, isPaused, resumeGame, isRestart, backToMenu, howToPlay, highScore);

					if (quit) break;

					restartGame();

					break;

				}

				SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
				SDL_RenderClear(gRenderer);
				gLoadBackGroundMenuHighScores.render(0, 0, gRenderer);
				gMenu.render(gRenderer);
				SDL_RenderPresent(gRenderer);
			}

			continue;
		}


		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
		SDL_RenderClear(gRenderer);
		gLoadBackGroundMenu.render(0, 0, gRenderer);
		gMenu.render(gRenderer);
		SDL_RenderPresent(gRenderer);
	}
}


void showPauseMenu(bool& quit, bool& startGame, bool& isPaused, bool& resumeGame, bool& isRestart, bool& backToMenu, bool& howToPlay, bool& highScore) {
	gMenu.setMenuType(PAUSE_MENU);

	gMainCharacter.setVelX(0);
	gMainCharacter.setVelY(0);


	while (isPaused) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				quit = true;
				isPaused = false;
				break;
			}

			gMenu.handleMouse(e, quit, startGame, isPaused, resumeGame, isRestart, backToMenu, howToPlay, highScore);

			if (resumeGame) {
				resumeGame = false;
				isPaused = false;

				break;
			}

			if (backToMenu) {

				backToMenu = false;

				isPaused = false;

				startGame = false;

				showMainMenu(quit, startGame, isPaused, resumeGame, isRestart, backToMenu, howToPlay, highScore);

				if (quit) break;

				restartGame();

				break;
			}

			if (isRestart) {

				isRestart = false;
				isPaused = false;

				restartGame();

				break;
			}
		}
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
		SDL_RenderClear(gRenderer);
		gLoadBackGroundMenu.render(0, 0, gRenderer);
		gMenu.render(gRenderer);
		SDL_RenderPresent(gRenderer);
	}
}

void showGameOverMenu(bool& quit, bool& startGame, bool& isPaused, bool& resumeGame, bool& isRestart, bool& backToMenu, bool& howToPlay, bool& highScore) {
	gMenu.setMenuType(GAME_OVER_MENU);

	gMainCharacter.setVelX(0);
	gMainCharacter.setVelY(0);

	bool inGameOverMenu = true;

	while (inGameOverMenu) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				quit = true;
				inGameOverMenu = false;
				break;
			}
			gMenu.handleMouse(e, quit, startGame, isPaused, resumeGame, isRestart, backToMenu, howToPlay, highScore);

			if (quit) {
				inGameOverMenu = false;
				break;
			}

			if (backToMenu) {

				backToMenu = false;

				isPaused = false;

				startGame = false;

				inGameOverMenu = false;

				showMainMenu(quit, startGame, isPaused, resumeGame, isRestart, backToMenu, howToPlay, highScore);

				if (quit) break;

				restartGame();

				break;
			}

			if (isRestart) {

				isRestart = false;

				isPaused = false;

				inGameOverMenu = false;

				restartGame();

				break;
			}
		}
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
		SDL_RenderClear(gRenderer);
		if (gMainCharacter.getHealthBar().getCurrentHealth() <= 0) gLoadBackGroundMenuLose.render(0, 0, gRenderer);
		else gLoadBackGroundMenuWin.render(0, 0, gRenderer);
		gMenu.render(gRenderer);
		SDL_RenderPresent(gRenderer);
	}

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


	gMenu.init(gFontA, gRenderer);

	bool quit = false;
	bool startGame = false;
	bool isPaused = false;
	bool resumeGame = false;
	bool backToMenu = false;
	bool isRestart = false;
	bool howToPlay = false;
	bool highScore = false;
	bool hasSavedScore = false;

	// Menu
	gMenu.setMenuType(MAIN_MENU);

	showMainMenu(quit, startGame, isPaused, resumeGame, isRestart, backToMenu, howToPlay , highScore);

	if (quit) {
		restartGame();
		close();
		return 0;
	}


	timeGameText.setColor(RED_TEXT);

	gEffects.setClips();
	restartGame();

	// Menu pause

	while (!quit) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) quit = true;
			if (!isPaused && gMainCharacter.getHealthBar().getCurrentHealth()>0) gMainCharacter.handleMotion(e);
			if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_p && !isPaused) {
				isPaused = true;
			}

		}
		if (isPaused) {
			showPauseMenu(quit, startGame, isPaused, resumeGame, isRestart, backToMenu, howToPlay, highScore);
		}

		if (quit) {
			restartGame();
			close();
			return 0;
		}

		// Main game play
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);
		gLoadBackGroundGame.render(0, 0, gRenderer);
		gGameMap.drawMap(gRenderer);
		gMainCharacter.FallingInTheHole();
		gMainCharacter.setClips();
		gMainCharacter.CenterEntityOnMap();
		gMainCharacter.checkMapCollision(gRenderer);


		for (int i = 0;i < listEnemiesCD.size();i++) {
			EnemyCD* pEnemyCD = listEnemiesCD[i];
			if (pEnemyCD != NULL) {
				if (pEnemyCD->getHealthBar().getCurrentHealth() > 0) {
					pEnemyCD->handleMotion();
					gMainCharacter.checkCharacterCollisionWithEnemy(pEnemyCD,NULL,NULL);
					gMainCharacter.checkCharacterAttackedEnemy(pEnemyCD,NULL,NULL);
					pEnemyCD->checkEnemyCollisionWithProjectile();
					pEnemyCD->checkEnemyCollisionWithCharacter(gMainCharacter.getPosX(), gMainCharacter.getPosY());
					pEnemyCD->FallingInTheHole();
				}
				else {
					if (!pEnemyCD->getTypeFlag().hasGivenMana) {
					gMainCharacter.handleMana(-10);
					pEnemyCD->setHasGivenMana(true);
					}
					if (!pEnemyCD->getTypeFlag().hasGivenScore) {
						score += 10;
						pEnemyCD->setHasGivenScore(true);
					}
				}

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
					pEnemyAZ->checkEnemyCollisionWithProjectile();
					pEnemyAZ->checkEnemyCollisionWithCharacter(gMainCharacter.getPosX(), gMainCharacter.getPosY());
				}
				else {
					if (!pEnemyAZ->getTypeFlag().hasGivenMana) {
						gMainCharacter.handleMana(-10);
						pEnemyAZ->setHasGivenMana(true);
					}
					if (!pEnemyAZ->getTypeFlag().hasGivenScore) {
						score += 20;
						pEnemyAZ->setHasGivenScore(true);
					}
				}

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
					pEnemyBOSS->checkEnemyCollisionWithProjectile();
					pEnemyBOSS->checkEnemyCollisionWithCharacter(gMainCharacter.getPosX(), gMainCharacter.getPosY());
				}
				else {
					if (!pEnemyBOSS->getTypeFlag().hasGivenScore) {
						score += 100;
						pEnemyBOSS->setHasGivenScore(true);
					}
					if (!hasSavedScore) {
						int finalScore = score;
						saveScore(score, "highscore.txt");
						hasSavedScore = true;
					}
					timeDelayGameOver--;
					if (timeDelayGameOver == 0) {
						showGameOverMenu(quit, startGame, isPaused, resumeGame, isRestart, backToMenu, howToPlay, highScore);
					}
					if (quit) {
						restartGame();
						close();
						return 0;
					}

				}
				pEnemyBOSS->checkMapCollision();
				pEnemyBOSS->render(gRenderer);
			}
		}

		gMainCharacter.render(gRenderer);

		renderScoreText(gRenderer,gFont);
		renderTimeGameText(gRenderer , gFont);

		SDL_RenderPresent(gRenderer);

		if (gMainCharacter.getHealthBar().getCurrentHealth() <= 0) {
			if (!hasSavedScore) {
				int finalScore = score;
				saveScore(score, "highscore.txt");
				hasSavedScore = true;
			}
			timeDelayGameOver--;
			if (timeDelayGameOver == 0) {
			showGameOverMenu(quit, startGame, isPaused, resumeGame, isRestart, backToMenu, howToPlay, highScore);
			}
			
			if (quit) {
				restartGame();
				close();
				return 0;
			}

		}
		
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
