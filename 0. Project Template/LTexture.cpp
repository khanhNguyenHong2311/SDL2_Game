#include"Globals.h"
#include"Library.h"
#include<SDL_mixer.h>
#include"LTexture.h"
using namespace std;


LTexture::LTexture() {
	mTexture = NULL;
	mRect.x = 0;
	mRect.y = 0;
	mRect.w = 0;
	mRect.h = 0;
}


LTexture::~LTexture() {
	free();
}


bool LTexture::loadFromFile(string path , SDL_Renderer* renderer) {
	free();
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		cout << "Unable to load image " << path.c_str() << " ! SDL_Image Error : " << IMG_GetError() << endl;
	}
	else {
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0, 255));
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL) {
			cout << "Unable to create texture from " << path.c_str() << " ! SDL_Error : " << SDL_GetError()<<endl;
		}
		else {
			mRect.w = loadedSurface->w;
			mRect.h = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	mTexture = newTexture;
	return mTexture != NULL;
}


void LTexture::free() {

	if (mTexture != NULL) {
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mRect.w = 0;
		mRect.h = 0;
	}
}


void LTexture::render(int x, int y,SDL_Renderer* renderer , SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	SDL_Rect renderQuad = { x , y , mRect.w , mRect.h };
	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopyEx(renderer, mTexture, clip, &renderQuad, angle, center, flip);
}


int LTexture::getWidth(){
	return mRect.w;
}

int LTexture::getHeight() {
	return mRect.h;
}