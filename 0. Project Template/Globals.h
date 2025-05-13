#pragma once
#include"Library.h"
#include"LTexture.h"
#include"Character.h"
#include"Map.h"
#include"Text.h"
#include"EnemyCD.h"
#include"EnemyAZ.h"
#include"EnemyBOSS.h"
#include"Projectile.h"
#include"HealthBar.h"
#include"Menu.h"
// gClass

extern Text timeGameText;

extern Character gMainCharacter;

extern Effects gEffects;

extern LTexture gLoadCharacterHealthBar;

extern LTexture gLoadBackGroundGame;

extern LTexture gLoadBackGroundMenu;

extern LTexture gLoadMainCharacter[15];

extern LTexture gLoadEnemiesCD[15];

extern LTexture gLoadEnemiesAZ[15];

extern LTexture gLoadEnemiesBOSS[30];

extern LTexture gLoadProjectile[10];

extern LTexture gLoadEffects[10];

extern vector<EnemyCD*> listEnemiesCD;

extern vector<EnemyAZ*> listEnemiesAZ;

extern vector<EnemyBOSS*> listEnemiesBOSS;

extern GameMap gGameMap;

extern Menu gMenu;


static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;
static TTF_Font* gFont = NULL;
static SDL_Event e;

	
// Screen 

const int SCREEN_WIDTH = 1200 ;
const int SCREEN_HEIGHT = 640;

//Map

#define TILE_SIZE 80

#define TILE_EMPTY 0
#define TILE_HEALTH 9
#define TILE_MANA 8 
#define TILE_MINE 7

#define HEALTH_RECOVER -10 
#define MANA_RECOVER -10
#define MINE_DAMAGE 10


// Character 

#define CHARACTER_WIDTH 80
#define CHARACTER_HEIGHT 80

#define CHARACTER_VEL 8
#define CHARACTER_VEL_JUMP 30
#define CHARACTER_DAMAGE 20
#define CHARACTER_HEALTH 10000
#define CHARACTER_MANA 100

#define GRAVITY_SPEED 1
#define MAX_GRAVITY_SPEED 10



// Enemy AZ


#define ENEMY_AZ_WIDTH 160
#define ENEMY_AZ_HEIGHT 120

#define ENEMY_AZ_VEL 3
#define ENEMY_AZ_DAMAGE 10
#define ENEMY_AZ_HEALTH 10

#define ENEMY_AZ_GRAVITY_SPEED 10
#define ENEMY_AZ_MAX_GRAVITY_SPEED 10

#define ENEMY_AZ_COLLIDER_WIDTH 120
#define ENEMY_AZ_COLLIDER_HEIGHT 120

#define ENEMY_AZ_ATTACK_RANGE 500

// Enemy CD

#define ENEMY_CD_WIDTH 120
#define ENEMY_CD_HEIGHT 120

#define ENEMY_CD_VEL 2

#define ENEMY_CD_DAMAGE 10
#define ENEMY_CD_HEALTH 10

#define ENEMY_CD_GRAVITY_SPEED 1
#define ENEMY_CD_MAX_GRAVITY_SPEED 10

#define ENEMY_CD_COLLIDER_WIDTH 120
#define ENEMY_CD_COLLIDER_HEIGHT 120	


// Enemy BOSS

#define ENEMY_BOSS_WIDTH 340
#define ENEMY_BOSS_HEIGHT 240

#define ENEMY_BOSS_VEL 3
#define ENEMY_BOSS_DAMAGE 10
#define ENEMY_BOSS_HEALTH 10

#define ENEMY_BOSS_GRAVITY_SPEED 10
#define ENEMY_BOSS_MAX_GRAVITY_SPEED 10

#define ENEMY_BOSS_COLLIDER_WIDTH 340
#define ENEMY_BOSS_COLLIDER_HEIGHT 240

#define ENEMY_BOSS_ATTACK_RANGE 500

//Effects

#define EFFECT_RECOVER_WIDTH 240
#define EFFECT_RECOVER_HEIGHT 240


// Projectile
#define PROJECTILE_WIDTH 120
#define PROJECTILE_HEIGHT 120
#define PROJECTILE_VEL 8
#define PROJECTILE_EXPLOSION_WIDTH 64
#define PROJECTILE_EXPLOSION_HEIGHT 64

