#define SDL_MAIN_HANDLE
#include"Library.h"
#include"Globals.h"
#include"LTexture.h"
#include"Map.h"
using namespace std;


LTexture gBackGround1;
LTexture gBackGround2;
LTexture gBackGround3;


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
	gBackGround1.free();
	gBackGround2.free();
	gBackGround3.free();
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
}



bool LoadBackGround() {
	bool success = true;
	if (!gBackGround1.loadFromFile("image/background/BG1.png", gRenderer)) {
		cout<<"Failed to load image/background/BG1.png "<<endl;
		success = false;
	}
	if (!gBackGround2.loadFromFile("image/background/BG2.png", gRenderer)) {
		cout << "Failed to load image/background/BG2.png " << endl;
		success = false;
	}
	if (!gBackGround3.loadFromFile("image/background/BG3.png", gRenderer)) {
		cout << "Failed to load image/background/BG3.png " << endl;
		success = false;
	}
	return success;
}



int main(int argc, char* args[]) {

	if (!init()) {
		cout << "Failed to initialize !" << endl;
		return -1;
	}

	if (!LoadBackGround()) {
		cout << "Failed to load background !" << endl;
		return -1;
	}



	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}

		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF,0xFF);
		SDL_RenderClear(gRenderer);
		gBackGround1.render(0,0, gRenderer);
		gBackGround2.render(0, 0, gRenderer);
		gBackGround3.render(0, 0, gRenderer);
		SDL_RenderPresent(gRenderer);
	}
	close();
	return 0;
}
