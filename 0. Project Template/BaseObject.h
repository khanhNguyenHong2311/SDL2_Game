#pragma once
#include"CommonFunc.h"
class BaseObject {
private:
	SDL_Texture* mTexture;
	SDL_Rect mRect;
public:
	BaseObject();
	~BaseObject();

	void setRect(int& x, int& y);
	int getRect();

	bool loadFromFile(string path , SDL_Renderer* renderer);
	void render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void free();
};
