#pragma once
#include"Library.h"
#include"Globals.h"

string calculateTime(Uint32 startTime);

void renderTimeGameText(SDL_Renderer* renderer, TTF_Font* font);

void renderScoreText(SDL_Renderer* renderer , TTF_Font* font);

void saveScore(int newScore, string filename);