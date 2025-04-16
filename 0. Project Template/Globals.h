#pragma once
#include"Library.h"
#include"Character.h"
#include"LTexture.h"
#include"Map.h"

// gClass
extern Character gMainCharacter;
extern LTexture gLoadBackGround;
extern LTexture gLoadMainCharacter[10];
extern LTexture gLoadRunRightCharacter[8];
extern GameMap gGameMap;

static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;
static SDL_Event e;

	
// Screen 

const int SCREEN_WIDTH = 1248 ;
const int SCREEN_HEIGHT = 640;




