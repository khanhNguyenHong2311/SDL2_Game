#include"Library.h"
#include"Globals.h"
#include"LTexture.h"
#include"Character.h"

Character::Character() {
	mPosX = 0;
	mPosY = 0;

	mVelX = 0;
	mVelY = 0;
}

void Character::handleMotion(SDL_Event& e) {
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
		case SDLK_UP: mVelY += CHARACTER_VEL; break;
		case SDLK_DOWN: mVelY -= CHARACTER_VEL;break;
		case SDLK_RIGHT:mVelX += CHARACTER_VEL;break;
		case SDLK_LEFT:mVelX-=CHARACTER_VEL
		}
	}
}