#include"Library.h"
#include"Globals.h"
#include"Map.h"
#include"Text.h"
#include"EnemyCD.h"
#include"Character.h"
#include"Menu.h"


Text timeGameText;

Uint32 startTime;

int score = 0;

int timeDelayGameOver = 100;

Text scoreText;

Character gMainCharacter;

Effects gEffects;

LTexture gLoadBackGroundGame;

LTexture gLoadBackGroundMenu;

LTexture gLoadBackGroundMenuWin;

LTexture gLoadBackGroundMenuLose;

LTexture gLoadBackGroundMenuHowToPlay;

LTexture gLoadBackGroundMenuHighScores;

LTexture gLoadCharacterHealthBar;

LTexture gLoadMainCharacter[15];

LTexture gLoadEnemiesCD[15];

LTexture gLoadEnemiesAZ[15];

LTexture gLoadEnemiesBOSS[30];

LTexture gLoadProjectile[10];

LTexture gLoadEffects[10];

GameMap gGameMap;

Menu gMenu;

vector<EnemyCD*> listEnemiesCD;

vector<EnemyAZ*> listEnemiesAZ;

vector<EnemyBOSS*> listEnemiesBOSS;