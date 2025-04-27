#pragma once
#include"Library.h"
#include"Character.h"
#include"Enemies.h"
#include"LTexture.h"
#include"Map.h"

// gClass
extern Character gMainCharacter;
extern LTexture gLoadBackGround;
extern LTexture gLoadMainCharacter[15];
extern LTexture gLoadEnemiesCD[15];
extern GameMap gGameMap;
extern Enemies gEnemies;

static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;
static SDL_Event e;

	
// Screen 

const int SCREEN_WIDTH = 1200 ;
const int SCREEN_HEIGHT = 640;

// Collision
const int COLLIDER_WIDTH = 80;
const int COLLIDER_HEIGHT = 80;



