#pragma once
#include"Library.h"
#include"LTexture.h"



class ManaBar {
private:

	int mPosX;

	int mPosY;

	float currentMana;

	float maxMana;

	SDL_Texture* ManaBarTexture;

	LTexture ManaBarImage;
public:
	ManaBar();
	~ManaBar();
	void setMana(float mana);
	void render(SDL_Renderer* renderer, int posX, int posY);
	void loadFromFile(string path, SDL_Renderer* renderer);
	float getCurrentMana();
	void setMaxMana(float mana);

};