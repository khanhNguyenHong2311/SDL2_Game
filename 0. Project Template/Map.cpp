#include"Library.h"
#include"Globals.h"
#include"LTexture.h"
#include"Map.h"


void GameMap::loadMap(string pathFile) {
	fstream fs;
	fs.open(pathFile);
	if (!fs.is_open()) {
		cout << "Failed to open" << pathFile << " !" << endl;
		return;
	}

	max_map_x = 0;
	max_map_y = 0;

	for (int i = 0;i < MAX_MAP_Y;i++) {
		for (int j = 0;j < MAX_MAP_X;j++) {
			fs >> tile[i][j];
			int val = tile[i][j];

			max_map_x = max(max_map_x, j);
			max_map_y = max(max_map_y, i);

		}
	}

	max_map_x = (max_map_x + 1) * TILE_SIZE;
	max_map_y = (max_map_y + 1) * TILE_SIZE;

	camera_x = 0;
	camera_y = 0;

	fileName = pathFile;
	fs.close();
}


void GameMap::loadTiles(SDL_Renderer* renderer) {
	for (int i = 0;i < MAX_TILES;i++) {
		string pathTileImage = "image/map_and_tiles/0" + to_string(i) + ".png";
		fstream fs;
		fs.open(pathTileImage);
		if (!fs.is_open()) {
			continue;
		}
		fs.close();
		tileMatrix[i].loadFromFile(pathTileImage, renderer);
	}
}

void GameMap :: drawMap(SDL_Renderer* renderer) {
	int x1 = 0;
	int x2 = 0;
	
	int y1 = 0;
	int y2 = 0;

	int map_x = 0;
	int map_y = 0;

	map_x = camera_x / TILE_SIZE;
	x1 = (camera_x % TILE_SIZE) * -1;
	x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

	map_y = camera_y / TILE_SIZE;
	y1 = (camera_y % TILE_SIZE) * -1;
	y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

	for (int i = y1;i < y2;i+=TILE_SIZE) {\

		map_x = camera_x / TILE_SIZE;

		for (int j = x1;j < x2;j+=TILE_SIZE) {
	
			int val = tile[map_y][map_x];
			if (val > 0) {
				tileMatrix[val].render(j, i, renderer);
			}
			map_x++;
		}
		map_y++;
	}
}






