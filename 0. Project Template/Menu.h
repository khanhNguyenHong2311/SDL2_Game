#pragma once
#include"Library.h"
#include "Text.h"

enum MenuType {
	MAIN_MENU,
	PAUSE_MENU
};


enum MenuOption {
	START = 0,
	QUIT = 1,
	TOTAL_MENU_OPTIONS = 2
};


enum PauseOption {
	PAUSE = 0 ,
	RESUME = 1,
	RESTART = 2,
	BACK_TO_MENU = 3,
	TOTAL_PAUSE_OPTIONS = 4

};

class Menu {
private:

	Text menuOptions[TOTAL_MENU_OPTIONS ];
	Text pauseOptions[TOTAL_PAUSE_OPTIONS];

	SDL_Rect menuOptionRects[TOTAL_MENU_OPTIONS];
	SDL_Rect pauseOptionRects[TOTAL_PAUSE_OPTIONS];

	int selectedOption;
	TTF_Font* font;

	MenuType currentMenuType;

public:
	Menu();
	~Menu();

	void init(TTF_Font* font, SDL_Renderer* renderer);
	void handleMouse(SDL_Event& e, bool& quit, bool& startGame, bool& pauseGame, bool& remuseGame, bool& restartGame, bool& backToMenu);
	void render(SDL_Renderer* renderer);
	void setMenuType(MenuType type);

};
