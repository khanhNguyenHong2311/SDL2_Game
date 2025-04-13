#include"Library.h"
#include"Globals.h"
#include"LTexture.h"
#include"Character.h"


Character::Character() {
	mPosX = 0;
	mPosY = 0;

	mVelX = 0;
	mVelY = 0;

	isFacing = FACING_RIGHT ;
	
	frame = 0;
}

void Character::handleMotion(SDL_Event& e) {
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
		case SDLK_UP: mVelY -= CHARACTER_VEL; typeMotion.goUp = true; break;
		case SDLK_DOWN: mVelY += CHARACTER_VEL; typeMotion.goDown = true; break;
		case SDLK_LEFT:mVelX -= CHARACTER_VEL; typeMotion.goLeft = true; break;
		case SDLK_RIGHT:mVelX += CHARACTER_VEL; typeMotion.goRight = true; break;
		}
	}

	else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
		case SDLK_UP: mVelY += CHARACTER_VEL; typeMotion.goUp = false ; break;
		case SDLK_DOWN: mVelY -= CHARACTER_VEL; typeMotion.goDown = false ;break;
		case SDLK_LEFT:mVelX += CHARACTER_VEL; typeMotion.goLeft = false ; break;
		case SDLK_RIGHT:mVelX -= CHARACTER_VEL; typeMotion.goRight = false; break;
		}
	}
}

void Character::move() {
	
	mPosX += mVelX;
	if (mPosX<0 || mPosX + CHARACTER_WIDTH  > SCREEN_WIDTH) {
		mPosX -= mVelX;
	}

	mPosY += mVelY;
	if (mPosY<0 || mPosY + CHARACTER_HEIGHT > SCREEN_HEIGHT) {
		mPosY -= mVelY;
	}

}



void Character::render(SDL_Renderer* renderer) {

	if (typeMotion.goRight  || typeMotion.goLeft ) {
		frame++;
		if (frame / 8 >= 8) {
			frame = 0;

		}
	}
	else {
		frame = 0;
	}

	SDL_Rect* currentClip = NULL;

	if (typeMotion.goLeft) {
		isFacing = FACING_LEFT;
		currentClip = &goLeftAnimations[frame / 8];
	}
	else if (typeMotion.goRight) {
		isFacing = FACING_RIGHT;
		currentClip = &goRightAnimations[frame / 8];
	}
	else {
		x ++;
		if (x / 7 >= 7) {
			x = 0;
		}
		if (isFacing == FACING_LEFT) {
			currentClip = &standLeftAnimations[x / 8];
		}
		if (isFacing == FACING_RIGHT) {
			currentClip = &standRightAnimations[x / 8];
		}
	}
	gLoadMainCharacter.render(mPosX, mPosY,renderer, currentClip);
}


int Character::getPosX() {
	return mPosX;
}
int Character::getPosY() {
	return mPosY;
}