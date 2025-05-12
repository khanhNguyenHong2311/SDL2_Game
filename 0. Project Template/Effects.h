#pragma once
#include"Library.h"
#include"Globals.h"
#include"LTexture.h"
#include"Map.h"

enum TypeEffect {
	RECOVER = 1 , 
	SIGNAL = 2 ,
	MINE_EXPLOSION = 3
};

class Effects {
private:
	int mPosX; 
	int mPosY;

	int frameWidth;
	int frameHeight;

	int frameRecover;
	int frameSignal; 
	int frameMineExplosion;

	int minePosX, minePosY;

	bool isMineExplosionActive;

	SDL_Rect frameClipsRecover[7];

	SDL_Rect frameClipsSignal[8];

	SDL_Rect frameClipsMineExplosion[9];
public:

	Effects();

	~Effects() { ; }

	void render(SDL_Renderer* renderer, int posX, int posY , bool isRecover = false , bool isSignal = false);

	void setClips();

	void setIsMineExplosionActive(bool value);

	bool getIsMineExplosionActive();

	void setMineExplosionPosition(int x, int y);

	int	getMineExplosionPositionX();

	int	getMineExplosionPositionY();
};