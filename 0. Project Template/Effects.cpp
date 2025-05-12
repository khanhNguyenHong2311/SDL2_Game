#include"Library.h"
#include"Globals.h"
#include"LTexture.h"
#include"Map.h"
#include"Effects.h"


Effects::Effects() {
	mPosX = 0;
	mPosY = 0;

	frameWidth = 240;
	frameHeight = 240;

	frameRecover = 0;
	frameSignal = 0;
	frameMineExplosion = 0;
	isMineExplosionActive=false;
}



void Effects::setClips() {
	if (frameWidth > 0 && frameHeight > 0) {
		for (int i = 0;i < 7;i++) {
			frameClipsRecover[i].x = i * frameWidth;
			frameClipsRecover[i].y = 0;
			frameClipsRecover[i].w = frameWidth ;
			frameClipsRecover[i].h = frameHeight;
		}

		for (int i = 0;i < 8;i++) {
			frameClipsSignal[i].x = i * frameWidth;
			frameClipsSignal[i].y = 0;
			frameClipsSignal[i].w = frameWidth;
			frameClipsSignal[i].h = frameHeight;
		}
		for (int i = 0;i < 9;i++) {
			frameClipsMineExplosion[i].x = i * frameWidth;
			frameClipsMineExplosion[i].y = 0;
			frameClipsMineExplosion[i].w = frameWidth;
			frameClipsMineExplosion[i].h = frameHeight;
		}
	}
}




void Effects::render(SDL_Renderer* renderer , int posX , int posY  , bool isRecover,bool isSignal) {

	SDL_Rect* currentClip = nullptr;

	SDL_Texture* currentTexture = nullptr;

	SDL_Rect renderQuad = { 0,0,0,0 };
	if (isRecover) {
		frameRecover++;
		if (frameRecover / 5 >= 7) frameRecover = 0;
		currentTexture = gLoadEffects[RECOVER].getTexture();
		currentClip = &frameClipsRecover[frameRecover / 5];
		renderQuad = { posX  - gGameMap.getCameraX(),posY - gGameMap.getCameraY(),currentClip->w,currentClip->h };
	}
	else if (isSignal) {
		frameSignal++;
		if (frameSignal / 8 >= 8) frameSignal = 0;
		currentTexture = gLoadEffects[SIGNAL].getTexture();
		currentClip = &frameClipsSignal[frameSignal / 8];
		renderQuad = { posX - gGameMap.getCameraX(),posY - gGameMap.getCameraY(),currentClip->w,currentClip->h };
	}
	else if (isMineExplosionActive) {
		frameMineExplosion++;
		if (frameMineExplosion / 5 >= 9) {
			frameMineExplosion = 0;
			isMineExplosionActive = false;
		}
		currentTexture = gLoadEffects[MINE_EXPLOSION].getTexture();
		currentClip = &frameClipsMineExplosion[frameMineExplosion / 5];
		renderQuad = { posX - gGameMap.getCameraX(),posY - gGameMap.getCameraY(),currentClip->w,currentClip->h };

	}

	SDL_RenderCopy(renderer, currentTexture, currentClip, &renderQuad);
}


void Effects::setIsMineExplosionActive(bool value) {
	isMineExplosionActive = value;
}

bool Effects::getIsMineExplosionActive() {
	return isMineExplosionActive;
}

void Effects::setMineExplosionPosition(int x, int y) {
	minePosX = x;
	minePosY = y;
}

int	Effects::getMineExplosionPositionX() {
	return minePosX;
}

int	Effects::getMineExplosionPositionY() {
	return minePosY;
}