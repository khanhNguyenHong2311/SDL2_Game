#include<iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include<sstream>
#include<SDL_mixer.h>
#include"BaseObject.h"
using namespace std;

BaseObject::BaseObject() {
	mTexture = NULL;
	mRect.x = 0;
	mRect.y = 0;
	mRect.w = 0;
	mRect.h = 0;
}

BaseObject::~BaseObject() {
	free();
}

bool BaseObject::loadFromFile(string path , SDL_Renderer* renderer) {
	// Get rid of
	free();

	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		cout << "Unable to load image " << path.c_str() << " ! SDL_Image Error : " << IMG_GetError() << endl;
	}
	else {
		// Color key image 
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0, 255));

		//
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL) {
			cout << "Unable to create texture from " << path.c_str() << " ! SDL_Error : " << SDL_GetError()<<endl;
		}
		else {
			// Get dimensions
			mRect.w = loadedSurface->w;
			mRect.h = loadedSurface->h;
		}

		// Get rid of
		SDL_FreeSurface(loadedSurface);
	}

	// Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

void BaseObject::free() {

	if (mTexture != NULL) {
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mRect.w = 0;
		mRect.h = 0;
	}
}


void BaseObject::render(int x, int y,SDL_Renderer* renderer , SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	//
	SDL_Rect renderQuad = { x , y , mRect.w , mRect.h };
	//
	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopyEx(renderer, mTexture, clip, &renderQuad, angle, center, flip);
}
