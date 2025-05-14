#pragma once
#include"Library.h"
#include "Text.h"

enum MenuType {
	MAIN_MENU,
	PAUSE_MENU,
	HOW_TO_PLAY_MENU ,
	HIGH_SCORE_MENU ,
	GAME_OVER_MENU ,
};


enum MenuOption {
	START = 0,
	HOW_TO_PLAY = 1,
	HIGH_SCORE = 2 ,
	A_QUIT = 3,
	TOTAL_MENU_OPTIONS = 4,
};


enum PauseOption {
	PAUSE = 0 ,
	RESUME = 1,
	A_RESTART = 2,
	BACK_TO_MENU = 3,
	TOTAL_PAUSE_OPTIONS = 4

};

enum HowToPlayMenu {
	TEXT_A = 0 ,
	TEXT_B = 1,
	TEXT_C = 2 ,
	TEXT_D = 3,
	TEXT_E = 4,
	A_BACK_TO_MENU = 5,
	TOTAL_HOW_TO_PLAY_OPTIONS = 6
};

enum HightScoreMenu {
	SCORE_A = 0 , 
	SCORE_B = 1, 
	SCORE_C = 2 , 
	SCORE_D = 3 , 
	SCORE_E = 4 ,
	B_BACK_TO_MENU = 5, 
	TOTAL_HIGH_SCORE_OPTIONS = 6
};

enum GameOverMenu {
	YOUR_SCORE = 0,
	B_RESTART = 1 , 
	C_BACK_TO_MENU = 2 , 
	B_QUIT = 3 , 
	TOTAL_GAME_OVER_OPTIONS = 4 , 

};

class Menu {
private:

	Text menuOptions[TOTAL_MENU_OPTIONS ];
	Text pauseOptions[TOTAL_PAUSE_OPTIONS];
	Text howToPlayOptions[TOTAL_HOW_TO_PLAY_OPTIONS];
	Text highScoreOptions[TOTAL_HIGH_SCORE_OPTIONS];
	Text gameOverOptions[TOTAL_GAME_OVER_OPTIONS];

	SDL_Rect menuOptionRects[TOTAL_MENU_OPTIONS];
	SDL_Rect pauseOptionRects[TOTAL_PAUSE_OPTIONS];
	SDL_Rect howToPlayOptionRects[TOTAL_HOW_TO_PLAY_OPTIONS];
	SDL_Rect highScoreOptionRects[TOTAL_HIGH_SCORE_OPTIONS];
	SDL_Rect gameOverOptionRects[TOTAL_GAME_OVER_OPTIONS];

	Text highScoreTexts[5];
	vector<int> highScores;


	int selectedOption;
	TTF_Font* font;

	MenuType currentMenuType;

public:
	Menu();
	~Menu();

	void init(TTF_Font* font, SDL_Renderer* renderer);

	void handleMouse(SDL_Event& e, bool& quit, bool& startGame, bool& pauseGame, bool& remuseGame, bool& restartGame, bool& backToMenu ,bool& howToPlay , bool& highScore);

	void render(SDL_Renderer* renderer);

	vector<string> loadHighScores(string filename);

	void setMenuType(MenuType type);


};

