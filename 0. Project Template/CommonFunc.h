#pragma once
#include"Library.h"

using namespace std;
	
static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;
static SDL_Event e;
	
// Screen 

const int SCREEN_WIDTH = 640 ;
const int SCREEN_HEIGHT = 512;

// Map

#define TILE_SIZE 64
#define MAX_SIZE_MAP_X 400
#define MAX_SIZE_MAP_Y 10
#define MAX_TILES 20

