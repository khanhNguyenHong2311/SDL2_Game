#include"Library.h"
#include"Text.h"



Text::Text() {
	textColor.r = 255;
	textColor.g = 255;
	textColor.b = 255;
	mTexture = NULL;
}

Text::~Text() {
	;
}


bool Text::loadFromRenderText(TTF_Font* font, SDL_Renderer* renderer) {
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, stringText.c_str(), textColor);
	if (textSurface!=NULL) {
		mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		textWidth = textSurface->w;
		textHeight = textSurface->h;
		SDL_FreeSurface(textSurface);
	}
	return mTexture != NULL;
}


void Text::free() {
	if (mTexture != NULL) {
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
	}
}



void Text::setColor(Uint8 red, Uint8 green, Uint8 blue) {
	textColor.r = red;
	textColor.g = green;
	textColor.b = blue;
}

void Text::setColor(int type) {
	if (type == RED_TEXT) {
		textColor = { 255,0,0 };
	}
	else if (type == WHITE_TEXT) {
		textColor = { 255,255,255 };
	}
	else if (type == BLUE_TEXT) {
		textColor = { 0,0,255 };
	}
}

void Text::render(SDL_Renderer* renderer, int posX, int posY, SDL_Rect* clip, double angle , SDL_Point* point , SDL_RendererFlip flip ) {
	SDL_Rect renderQuad = { posX , posY ,textWidth,textHeight };
	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(renderer, mTexture, clip, &renderQuad, angle, point, flip);
}

int Text::getWidth() {
	return textWidth;
}

int Text::getHeight() {
	return textHeight;
}

void Text::setText(string text) {
	stringText = text;
}
string Text::getText() {
	return stringText;
}