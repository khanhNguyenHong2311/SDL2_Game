#include"Library.h"
#include "Map.h"

// Read the map file and save to matrix tile[][]
void Map::LoadMap(string name) {

	// Read the map file
	fstream fs;
	fs.open(name);
	if (!fs.is_open()) {
		cout << "Faild to open " << name << " file !" << endl;
		return ;
	}

	max_x = 0; 
	max_y = 0;
	for (int i = 0;i < MAX_SIZE_MAP_Y;i++) {
		for (int j = 0;j < MAX_SIZE_MAP_X;j++) {
			fs >> tile[i][j];		// Save to matrix tile[][]
			int val = tile[i][j];
			if (val > 0) {			// Check if this ID is valid ( has an Image to Render )  
				if (j > max_x) {
					max_x = j;		//  Update the tile that is farthest
				}
				if (i > max_y) {
					max_y = i;		// Update the tile that is lowest
				}
			}
		}
	}
	max_x = (max_x + 1) * TILE_SIZE; // Convert to pixel
	max_y = (max_y + 1) * TILE_SIZE; // Convert to pixel

	start_x = 0;
	start_y = 0; 

	fileName = name;
	fs.close();
}


// Read the tile file ( image.png || image.jpg) , save to matrix tile_mat[] by loadFromFile
void Map::LoadTiles(SDL_Renderer* renderer) {
	for (int i = 0;i < MAX_TILES;i++) {
		// Check if pathImage exist
		string pathImage = "map/" + to_string(i) + ".png";
		fstream fs;
		fs.open(pathImage);
		if (!fs.is_open()) {
			continue;	
		}

		fs.close();

		tile_mat[i].loadFromFile(pathImage, renderer); // Save image to tile_mat[] and then render by void BaseObject :: render 
	}
}


// Draw tile on the map
void Map::DrawMap(SDL_Renderer* renderer) {
	
	int x1 = 0; int y1 = 0;
	int x2 = 0; int y2 = 0;


	x1 = (start_x % TILE_SIZE) * -1;
	if (x1 == 0) { 
		x2 = x1 + SCREEN_WIDTH;
	}
	else {
		x2 = x1 + SCREEN_WIDTH + TILE_SIZE;
	}

	y1 = (start_y % TILE_SIZE) * -1;
	if (y1 == 0) {
		y2 = y1 + SCREEN_HEIGHT;
	}
	else {
		y2 = y1 + SCREEN_HEIGHT + TILE_SIZE;
	}


	int map_x = 0; 
	int map_y = 0;

	for (int i = y1; i < y2; i+=TILE_SIZE) {
		map_x = start_x / TILE_SIZE;
		for (int j = x1;j < x2;j += TILE_SIZE) {
			int val = tile[map_y][map_x];
			if (val > 0) {	
				tile_mat[val].render(j,i,renderer);
			}
			map_x++;
		}
	map_y++;
	}
}