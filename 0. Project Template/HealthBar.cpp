#include"HealthBar.h"


HealthBar::HealthBar() {
	currentHealth = 1;
	maxHealth = 1;
}

HealthBar::~HealthBar() {
	;
}



void HealthBar:: setHealth(int health) {
    currentHealth = health;
    if (currentHealth > maxHealth) currentHealth = maxHealth;
    if (currentHealth < 0) currentHealth = 0;
}

void HealthBar :: loadFromFile(string path, SDL_Renderer* renderer) {
    healthBarImage.loadFromFile(path, renderer);
    healthBarTexture = healthBarImage.getTexture();

}


void  HealthBar::render(SDL_Renderer* renderer, int x, int y) {

    SDL_Rect renderQuad = { x , y , 250 , 30 };

    SDL_Rect healthRect = { x + 2, y + 1, (currentHealth * 250 / maxHealth)-3, 28 }; 

    SDL_SetRenderDrawColor(renderer, 255 - (currentHealth * 255 / maxHealth), currentHealth * 255 / maxHealth, 0, 255);  

    SDL_RenderFillRect(renderer, &healthRect);

    SDL_RenderCopy(renderer, healthBarTexture, NULL , &renderQuad);

}

int HealthBar::getCurrentHealth() {
    return currentHealth;
}


void HealthBar::setMaxHealth(int health) {
    maxHealth = health;
    if (currentHealth > maxHealth) currentHealth = maxHealth;
}
