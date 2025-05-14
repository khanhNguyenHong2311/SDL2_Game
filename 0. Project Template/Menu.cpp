#include "Menu.h"
#include "Globals.h"

Menu::Menu() {
	selectedOption = -1;
	font = nullptr;
	currentMenuType = MAIN_MENU;
}

Menu::~Menu() {}

void Menu::init(TTF_Font* font_, SDL_Renderer* renderer) {
	font = font_;

	// MAIN MENU
	menuOptions[START].setText("Start Game");
	menuOptions[A_QUIT].setText("Quit");
	menuOptions[HOW_TO_PLAY].setText("How to play");
	menuOptions[HIGH_SCORE].setText("High Score");

	for (int i = 0; i < TOTAL_MENU_OPTIONS; ++i) {
		menuOptions[i].setColor(WHITE_TEXT);
		menuOptions[i].loadFromRenderText(font, renderer);

		menuOptionRects[i] = {
			SCREEN_WIDTH / 2 - menuOptions[i].getWidth() / 2,
			SCREEN_HEIGHT / 2 + i * 60,
			menuOptions[i].getWidth(),
			menuOptions[i].getHeight()
		};
	}

	// PAUSE MENU
	pauseOptions[PAUSE].setText("Pause");
	pauseOptions[RESUME].setText("Resume");
	pauseOptions[A_RESTART].setText("Restart");
	pauseOptions[BACK_TO_MENU].setText("Back to Menu");

	for (int i = 0; i < TOTAL_PAUSE_OPTIONS; ++i) {
		pauseOptions[i].setColor(WHITE_TEXT);
		pauseOptions[i].loadFromRenderText(font, renderer);

		pauseOptionRects[i] = {
			SCREEN_WIDTH / 2 - pauseOptions[i].getWidth() / 2,
			SCREEN_HEIGHT / 2 + i * 60,
			pauseOptions[i].getWidth(),
			pauseOptions[i].getHeight()
		};
	}
	// how to play menu
	howToPlayOptions[TEXT_A].setText("Use the arrow keys to move your character .");
	howToPlayOptions[TEXT_B].setText("Press 'A' to attack enemies.");
	howToPlayOptions[TEXT_C].setText("Press 'S' to use a special skill.");
	howToPlayOptions[TEXT_D].setText("You lose if your health drops to zero.");
	howToPlayOptions[TEXT_E].setText("Defeat the boss to win the game!");

	howToPlayOptions[A_BACK_TO_MENU].setText("Back to Menu");

	for (int i = 0; i < TOTAL_HOW_TO_PLAY_OPTIONS; ++i) {
		howToPlayOptions[i].setColor(WHITE_TEXT);
		howToPlayOptions[i].loadFromRenderText(font, renderer);
	}

	howToPlayOptionRects[0] = {	SCREEN_WIDTH / 2 + 80 - howToPlayOptions[0].getWidth() / 2,	SCREEN_HEIGHT / 4 - 50,	howToPlayOptions[0].getWidth(),	howToPlayOptions[0].getHeight() };
	howToPlayOptionRects[1] = { SCREEN_WIDTH / 2 - howToPlayOptions[1].getWidth() / 2,	SCREEN_HEIGHT / 4     + 60  ,	howToPlayOptions[1].getWidth(),	howToPlayOptions[1].getHeight() };
	howToPlayOptionRects[2] = { SCREEN_WIDTH / 2 - howToPlayOptions[2].getWidth() / 2,	SCREEN_HEIGHT / 4 + 160,	howToPlayOptions[2].getWidth(),	howToPlayOptions[2].getHeight() };
	howToPlayOptionRects[3] = { SCREEN_WIDTH / 2 - howToPlayOptions[3].getWidth() / 2,	SCREEN_HEIGHT / 4 + 270 ,	howToPlayOptions[3].getWidth(),	howToPlayOptions[3].getHeight() };
	howToPlayOptionRects[4] = { SCREEN_WIDTH / 2 - howToPlayOptions[4].getWidth() / 2,	SCREEN_HEIGHT / 4 + 300 ,	howToPlayOptions[4].getWidth(),	howToPlayOptions[4].getHeight() };
	howToPlayOptionRects[5] = { SCREEN_WIDTH / 2 - howToPlayOptions[5].getWidth() / 2,	SCREEN_HEIGHT / 4 + 380 ,	howToPlayOptions[5].getWidth(),	howToPlayOptions[5].getHeight() };

	// high score menu

	highScoreOptions[B_BACK_TO_MENU].setText("Back to Menu");


	for (int i = 0; i < TOTAL_HIGH_SCORE_OPTIONS; ++i) {
		highScoreOptions[i].setColor(WHITE_TEXT);
		highScoreOptions[i].loadFromRenderText(font, renderer);
		if (i != 5) {
			highScoreOptionRects[i] = {
				SCREEN_WIDTH / 2 - highScoreOptions[i].getWidth() / 2 - 80,
				SCREEN_HEIGHT / 2 + i * 60 - 150,
				highScoreOptions[i].getWidth(),
				highScoreOptions[i].getHeight()
			};
		}
		else if (i == 5) {
			highScoreOptionRects[i] = {
				SCREEN_WIDTH / 2 - highScoreOptions[i].getWidth() / 2  + 10 ,
				SCREEN_HEIGHT / 2 + i * 60 - 100,
				highScoreOptions[i].getWidth(),
				highScoreOptions[i].getHeight()
			};
		}
	}


	// game over menu
	gameOverOptions[B_RESTART].setText("Restart");
	gameOverOptions[C_BACK_TO_MENU].setText("Back to Menu");
	gameOverOptions[B_QUIT].setText("Quit");
	for (int i = 0; i < TOTAL_GAME_OVER_OPTIONS; ++i) {
		gameOverOptions[i].setColor(WHITE_TEXT);
		gameOverOptions[i].loadFromRenderText(font, renderer);
		if (i == 0) {
			gameOverOptionRects[i] = {
			SCREEN_WIDTH / 2 - gameOverOptions[i].getWidth() / 2 - 140,
			SCREEN_HEIGHT / 2 + i * 60,
			gameOverOptions[i].getWidth(),
			gameOverOptions[i].getHeight()
				};
		}
		else {
			gameOverOptionRects[i] = {
				SCREEN_WIDTH / 2 - gameOverOptions[i].getWidth() / 2,
				SCREEN_HEIGHT / 2 + i * 60,
				gameOverOptions[i].getWidth(),
				gameOverOptions[i].getHeight()
			};
		}
	}

}

void Menu::handleMouse(SDL_Event& e, bool& quit, bool& startGame, bool& pauseGame, bool& resumeGame, bool& restartGame , bool& backToMenu , bool& howToPlay , bool& highScore ) {
	int x, y;
	SDL_GetMouseState(&x, &y);
	selectedOption = -1;

	if (currentMenuType == MAIN_MENU) {
		for (int i = 0; i < TOTAL_MENU_OPTIONS; ++i) {
			if (x >= menuOptionRects[i].x && x <= menuOptionRects[i].x + menuOptionRects[i].w &&
				y >= menuOptionRects[i].y && y <= menuOptionRects[i].y + menuOptionRects[i].h) {
				selectedOption = i;

				if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
					if (i == START) startGame = true;
					else if (i == A_QUIT) quit = true;
					else if (i == HOW_TO_PLAY) howToPlay = true;
					else if (i == HIGH_SCORE) highScore = true;
				}
			}
		}
	}
	else if (currentMenuType == PAUSE_MENU) {
		for (int i = 0; i < TOTAL_PAUSE_OPTIONS; ++i) {
			if (x >= pauseOptionRects[i].x && x <= pauseOptionRects[i].x + pauseOptionRects[i].w &&
				y >= pauseOptionRects[i].y && y <= pauseOptionRects[i].y + pauseOptionRects[i].h) {
				selectedOption = i;

				if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
					if (i == PAUSE) pauseGame = true;
					else if (i == A_RESTART) restartGame = true;
					else if (i == RESUME) resumeGame = true;
					else if (i == BACK_TO_MENU) backToMenu = true;
				}
			}
		}
	}
	else if (currentMenuType == HOW_TO_PLAY_MENU) {
		for (int i = 0; i < TOTAL_HOW_TO_PLAY_OPTIONS; ++i) {
			if (x >= howToPlayOptionRects[i].x && x <= howToPlayOptionRects[i].x + howToPlayOptionRects[i].w &&
				y >= howToPlayOptionRects[i].y && y <= howToPlayOptionRects[i].y + howToPlayOptionRects[i].h) {
				selectedOption = i;

				if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
					if (i == A_BACK_TO_MENU) backToMenu = true;
				}
			}
		}
	}
	else if (currentMenuType == HIGH_SCORE_MENU) {
		for (int i = 0; i < TOTAL_HIGH_SCORE_OPTIONS; ++i) {
			if (x >= highScoreOptionRects[i].x && x <= highScoreOptionRects[i].x + highScoreOptionRects[i].w &&
				y >= highScoreOptionRects[i].y && y <= highScoreOptionRects[i].y + highScoreOptionRects[i].h) {
				selectedOption = i;

				if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
					if (i == B_BACK_TO_MENU) backToMenu = true;
				}
			}
		}
	}
	else if (currentMenuType == GAME_OVER_MENU) {
		for (int i = 0; i < TOTAL_GAME_OVER_OPTIONS; ++i) {
			if (x >= gameOverOptionRects[i].x && x <= gameOverOptionRects[i].x + gameOverOptionRects[i].w &&
				y >= gameOverOptionRects[i].y && y <= gameOverOptionRects[i].y + gameOverOptionRects[i].h) {
				selectedOption = i;

				if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
					if (i == B_RESTART) restartGame = true;
					else if (i == C_BACK_TO_MENU) backToMenu = true;
					else if (i == B_QUIT) quit = true;
				}
			}
		}
	}
	
}

void Menu::render(SDL_Renderer* renderer) {
	if (currentMenuType == MAIN_MENU) {
		for (int i = 0; i < TOTAL_MENU_OPTIONS; ++i) {
			if (i == selectedOption) menuOptions[i].setColor(RED_TEXT);
			else menuOptions[i].setColor(WHITE_TEXT);

			menuOptions[i].loadFromRenderText(font, renderer);
			menuOptions[i].render(renderer, menuOptionRects[i].x, menuOptionRects[i].y);
		}
	}
	else if (currentMenuType == PAUSE_MENU) {
		for (int i = 0; i < TOTAL_PAUSE_OPTIONS; ++i) {
			if (i == selectedOption) pauseOptions[i].setColor(RED_TEXT);
			else pauseOptions[i].setColor(WHITE_TEXT);

			pauseOptions[i].loadFromRenderText(font, renderer);
			pauseOptions[i].render(renderer, pauseOptionRects[i].x, pauseOptionRects[i].y);
		}
	}
	else if (currentMenuType == HOW_TO_PLAY_MENU) {
		for (int i = 0; i < TOTAL_HOW_TO_PLAY_OPTIONS; ++i) {
			if (i == selectedOption && i == 5) howToPlayOptions[i].setColor(RED_TEXT);
			else howToPlayOptions[i].setColor(WHITE_TEXT);

			howToPlayOptions[i].loadFromRenderText(font, renderer);
			howToPlayOptions[i].render(renderer, howToPlayOptionRects[i].x, howToPlayOptionRects[i].y);
		}
	}
	else if (currentMenuType == HIGH_SCORE_MENU) {
		vector<string> scores = loadHighScores("highscore.txt");
		for (int i = 0;i < scores.size() && i < 5;i++) {
			string topScore = "Top " + to_string(i + 1) + ": " + scores[i];
			highScoreOptions[i].setText(topScore);
		}
		for (int i = 0; i < TOTAL_HIGH_SCORE_OPTIONS; ++i) {
			if (i == selectedOption) highScoreOptions[i].setColor(RED_TEXT);
			else highScoreOptions[i].setColor(WHITE_TEXT);
			

			highScoreOptions[i].loadFromRenderText(font, renderer);
			highScoreOptions[i].render(renderer, highScoreOptionRects[i].x, highScoreOptionRects[i].y);
		}
	}
	else if (currentMenuType == GAME_OVER_MENU) {
		string s = "Your score : ";
		s+=to_string(score);
		gameOverOptions[YOUR_SCORE].setText(s);
		for (int i = 0; i < TOTAL_GAME_OVER_OPTIONS; ++i) {
			if (i == selectedOption) gameOverOptions[i].setColor(RED_TEXT);
			else gameOverOptions[i].setColor(WHITE_TEXT);

			gameOverOptions[i].loadFromRenderText(font, renderer);
			gameOverOptions[i].render(renderer, gameOverOptionRects[i].x, gameOverOptionRects[i].y);
		}
	}

}


vector<string>Menu:: loadHighScores(string filename) {
	vector<string> scores;
	ifstream file(filename);
	string line;
	while (getline(file, line)) {
		scores.push_back(line);
	}
	file.close();
	return scores;
}


void Menu::setMenuType(MenuType type) {
	currentMenuType = type;
}
