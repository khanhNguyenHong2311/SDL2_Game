#pragma once
#include"Library.h"
#include"LTexture.h"



class HealthBar {
private:

	int mPosX;

	int mPosY;
	
	int currentHealth;

	int maxHealth;

	SDL_Texture* healthBarTexture;

	LTexture healthBarImage;
public:
	HealthBar();
	~HealthBar();
	void setHealth(int health);
	void render(SDL_Renderer* renderer , int posX , int posY);
	void loadFromFile(string path, SDL_Renderer* renderer);
	int getCurrentHealth();
	void setMaxHealth(int health);
};