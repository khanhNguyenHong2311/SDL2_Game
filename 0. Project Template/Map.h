#pragma once
#include"Library.h"
#include"Globals.h"
#include"LTexture.h"



#define TILE_SIZE 96
#define MAX_TILES 20


#define MAX_MAP_X 13
#define MAX_MAP_Y 7

#define TILE_DIRT 0
#define TILE_SURFACE_GRASS  1
#define TILE_WALL 2
#define TILE_BACK_WALL 3



class TileMatrix:public LTexture {
public:
	TileMatrix() { ; }
	~TileMatrix() { ; }
};

class GameMap {
private:

	int camera_x; 
	int camera_y;

	int max_map_x;
	int max_map_y;
	
	int tile[MAX_MAP_Y][MAX_MAP_X];
	
	string fileName;

	TileMatrix tileMatrix[MAX_TILES];
	
public:

	GameMap() { ; }
	~GameMap() { ; }

	void loadMap(string pathFile);

	void loadTiles(SDL_Renderer* renderer);

	void drawMap(SDL_Renderer* renderer);

};