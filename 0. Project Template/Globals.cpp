#include"Library.h"
#include"Globals.h"
#include"Map.h"
#include"EnemyCD.h"
#include"Character.h"

Character gMainCharacter;
LTexture gLoadBackGround;
LTexture gLoadMainCharacter[15];
LTexture gLoadEnemiesCD[15];
LTexture gLoadEnemiesAZ[15];
LTexture gLoadProjectile[5];
GameMap gGameMap;
vector<EnemyCD*> listEnemiesCD;
vector<EnemyAZ*> listEnemiesAZ;
