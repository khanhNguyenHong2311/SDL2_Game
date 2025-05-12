#pragma once
#include"Globals.h"
#include"Library.h"
#include"LTexture.h"

#define MAX_TILES 20


#define MAX_MAP_X 87
#define MAX_MAP_Y 8


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

	int getValueOfTile(int x, int y);

	void setCameraX(int val );
	void setCameraY(int val );

	void setValueOfTile(int x, int y,int val );

	int getCameraX();
	int getCameraY();

	int getMaxMapX();
	int getMaxMapY();
};