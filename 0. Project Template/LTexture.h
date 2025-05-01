#pragma once
#include"Library.h"
#include"Globals.h"
class LTexture{
private:
	SDL_Texture* mTexture;
	SDL_Rect mRect;
public:

	LTexture();
	~LTexture();

	bool loadFromFile(string path , SDL_Renderer* renderer);
	
	void render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void free();

	int getWidth();

	int getHeight();

	void setRect(int x, int y);

	int getRectX();

	int getRectY();

	void updateRectX(int mVelX);

	void updateRectY(int mVelY);


	SDL_Texture* getTexture() {
		return mTexture;
	}
};

