#pragma once
#include"Library.h"
#include"CommonFunc.h"
#include"BaseObject.h"


// Each Tile inherits from BaseObject 
class TileMat : public BaseObject {
public:
	TileMat() { ; }
	~TileMat() { ; }
private:
};


class Map {
private:
	//Position of the Camera ( top left corner ) , use for Camera Scrolling
	int start_x;
	int start_y;
	// Map limit ( pixel )
	int max_x;
	int max_y;
	//Matrix ID
	int tile[MAX_SIZE_MAP_X][MAX_SIZE_MAP_Y];
	string fileName;
	// Tiles
	TileMat tile_mat[MAX_TILES];

public:

	// Read the map file and save to matrix tile[][]
	void LoadMap(string name);
	// Read the tile file ( image.png || image.jpg) , save to matrix tile_mat[] by loadFromFile
	void LoadTiles(SDL_Renderer* renderer);
	// Draw tile on the map
	void DrawMap(SDL_Renderer* renderer);

};

