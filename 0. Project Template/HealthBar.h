#pragma once
#include"Library.h"
#include"LTexture.h"



class HealthBar {
private:

	int mPosX;

	int mPosY;
	
	float currentHealth;

	float maxHealth;

	SDL_Texture* healthBarTexture;

	LTexture healthBarImage;
public:
	HealthBar();
	~HealthBar();
	void setHealth(float health);
	void render(SDL_Renderer* renderer , int posX , int posY);
	void loadFromFile(string path, SDL_Renderer* renderer);
	float getCurrentHealth();
	void setMaxHealth(float health);
};