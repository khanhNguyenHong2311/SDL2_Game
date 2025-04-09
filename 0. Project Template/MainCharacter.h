#pragma once
#include"Library.h"
#include"CommonFunc.h"
#include"BaseObject.h"
 
class MainCharacter : public BaseObject {
private:
	float x;
	float y;
public:
	MainCharacter() { ; }
	~MainCharacter() { ; }

	bool loadFromFile(string path, SDL_Renderer* renderer);
	void render(SDL_Renderer* renderer);
	void handleInPutAction(SDL_Event e, SDL_Renderer* renderer);
};