#include"Library.h"
#include"Globals.h"
#include"Map.h"
#include"Text.h"
#include"EnemyCD.h"
#include"Character.h"


Text timeGameText;
Character gMainCharacter;
LTexture gLoadBackGround;
LTexture gLoadCharacterHealthBar;
LTexture gLoadMainCharacter[15];
LTexture gLoadEnemiesCD[15];
LTexture gLoadEnemiesAZ[15];
LTexture gLoadEnemiesBOSS[15];
LTexture gLoadProjectile[5];
GameMap gGameMap;
vector<EnemyCD*> listEnemiesCD;
vector<EnemyAZ*> listEnemiesAZ;
vector<EnemyBOSS*> listEnemiesBOSS;