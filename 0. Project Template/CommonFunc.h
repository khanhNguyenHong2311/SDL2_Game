#pragma once
#include<iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include<sstream>
#include<SDL_mixer.h>
using namespace std;
	
static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;
static SDL_Event e;
	
// Screen 

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
