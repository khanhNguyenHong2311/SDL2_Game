#pragma once
#include"Library.h"
#include"Character.h"
#include"LTexture.h"

// gClass
extern Character gMainCharacter;
extern LTexture gLoadBackGround;
extern LTexture gLoadMainCharacter;
extern SDL_Rect goLeftAnimations[8];
extern SDL_Rect goRightAnimations[8];
extern SDL_Rect standLeftAnimations[8];
extern SDL_Rect standRightAnimations[7];


static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;
static SDL_Event e;
	
// Screen 

const int SCREEN_WIDTH = 1248 ;
const int SCREEN_HEIGHT = 656;

// Character 

//Tiles

const int TILE_WIDTH = 96;
const int TILE_HEIGHT = 96;
const int MAX_TILES = 20;


const int TILE_DIRT = 0;
const int TILE_SURFACE_GRASS = 1;
const int TILE_WALL = 2;
const int TILE_BACK_WALL = 3;




