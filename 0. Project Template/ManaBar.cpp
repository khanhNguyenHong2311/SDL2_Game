#include"ManaBar.h"


ManaBar::ManaBar() {
    currentMana = 1;
    maxMana = 1;
}

ManaBar::~ManaBar() {
    ;
}



void ManaBar::setMana(float Mana) {
    currentMana = Mana;
    if (currentMana > maxMana) currentMana = maxMana;
    if (currentMana < 0) currentMana = 0;
}

void ManaBar::loadFromFile(string path, SDL_Renderer* renderer) {
    ManaBarImage.loadFromFile(path, renderer);
    ManaBarTexture = ManaBarImage.getTexture();

}


void  ManaBar::render(SDL_Renderer* renderer, int x, int y) {

    SDL_Rect renderQuad = { x , y , 250 , 30 };

    SDL_Rect ManaRect = { x + 2, y + 1, (currentMana * 250 / maxMana) - 3, 28 };

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

    SDL_RenderFillRect(renderer, &ManaRect);

    SDL_RenderCopy(renderer, ManaBarTexture, NULL, &renderQuad);

}

float ManaBar::getCurrentMana() {
    return currentMana;
}


void ManaBar::setMaxMana(float Mana) {
    maxMana = Mana;
    if (currentMana > maxMana) currentMana = maxMana;
}
