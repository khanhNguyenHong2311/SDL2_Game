#pragma once
#include"Library.h"


enum Color {
	RED_TEXT = 0,
	WHITE_TEXT = 1,
	BLUE_TEXT = 2, 
};

class Text {
private:
	string stringText;
	
	SDL_Color textColor;
	
	SDL_Texture* mTexture;
	
	int textWidth;
	int textHeight;


public:
	Text();
	~Text();

	bool loadFromFile(string path);
	bool loadFromRenderText(TTF_Font* font, SDL_Renderer* renderer);
	void free();

	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	void setColor(int type);

	void render(SDL_Renderer* renderer, int posx, int posy, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* point = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	int getWidth();
	int getHeight();

	void setText(string text);
	string getText();

};