#pragma once
#include"Library.h"
	
static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;
static SDL_Event e;
	
// Screen 

const int SCREEN_WIDTH = 1008 ;
const int SCREEN_HEIGHT = 605;

//Tiles

const int TILE_WIDTH = 16;
const int TILE_HEIGHT = 16;
const int MAX_TILES = 20;


const int TILE_DIRT = 0;
const int TILE_SURFACE_GRASS = 1;
const int TILE_WALL = 2;
const int TILE_BACK_WALL = 3;




