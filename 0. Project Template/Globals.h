#pragma once
#include"Library.h"
#include"Character.h"
#include"EnemyCD.h"
#include"EnemyAZ.h"
#include"LTexture.h"
#include"Map.h"

// gClass
extern Character gMainCharacter;

extern LTexture gLoadBackGround;

extern LTexture gLoadMainCharacter[15];

extern LTexture gLoadEnemiesCD[15];

extern LTexture gLoadEnemiesAZ[15];

extern vector<EnemyCD*> listEnemiesCD;

extern vector<EnemyAZ*> listEnemiesAZ;

extern GameMap gGameMap;


static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;
static SDL_Event e;

	
// Screen 

const int SCREEN_WIDTH = 1200 ;
const int SCREEN_HEIGHT = 640;

// Collision
const int COLLIDER_WIDTH = 80;
const int COLLIDER_HEIGHT = 80;




// Character 

#define CHARACTER_WIDTH 80
#define CHARACTER_HEIGHT 80

#define CHARACTER_VEL 8
#define CHARACTER_VEL_JUMP 25


#define GRAVITY_SPEED 1
#define MAX_GRAVITY_SPEED 10



// Enemy AZ


#define ENEMY_AZ_WIDTH 160
#define ENEMY_AZ_HEIGHT 120

#define ENEMY_AZ_VEL 2

#define ENEMY_AZ_GRAVITY_SPEED 0
#define ENEMY_AZ_MAX_GRAVITY_SPEED 0



// Enemy CD

#define ENEMY_CD_WIDTH 120
#define ENEMY_CD_HEIGHT 120

#define ENEMY_CD_VEL 2

#define ENEMY_CD_GRAVITY_SPEED 1
#define ENEMY_CD_MAX_GRAVITY_SPEED 10

