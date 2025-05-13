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
	menuOptions[QUIT].setText("Quit");

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
	pauseOptions[RESTART].setText("Restart");
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
}

void Menu::handleMouse(SDL_Event& e, bool& quit, bool& startGame, bool& pauseGame, bool& resumeGame, bool& restartGame , bool& backToMenu) {
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
					else if (i == QUIT) quit = true;
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
					else if (i == RESTART) restartGame = true;
					else if (i == RESUME) resumeGame = true;
					else if (i == BACK_TO_MENU) backToMenu = true;
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
}


void Menu::setMenuType(MenuType type) {
	currentMenuType = type;
}
