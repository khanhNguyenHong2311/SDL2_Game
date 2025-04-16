#include"Library.h"
#include"Globals.h"
#include"LTexture.h"
#include"Map.h"
#include"Character.h"


Character::Character() {
	mPosX = 0;
	mPosY = 0;

	mVelX = 0;
	mVelY = 0;

	isFacing = FACING_RIGHT ;

	typeMotion.isStanding = true;

	frameWidth = 90;
	frameHeight = 80 ;
	
	frame = 0;

	frameStand = 0;
}

void Character::handleMotion(SDL_Event& e) {
	
	mVelY += GRAVITY_SPEED;
	if (mVelY > MAX_GRAVITY_SPEED) {
		mVelY = MAX_GRAVITY_SPEED;
	}
	

	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
		case SDLK_LEFT:mVelX -= CHARACTER_VEL; typeMotion.goLeft = true; break;
		case SDLK_RIGHT:mVelX += CHARACTER_VEL; typeMotion.goRight = true; break;
		}
	}

	else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
		case SDLK_LEFT:mVelX += CHARACTER_VEL; typeMotion.goLeft = false ; break;
		case SDLK_RIGHT:mVelX -= CHARACTER_VEL; typeMotion.goRight = false; break;
		}
	}
}

void Character::checkMapCollision() {


	int heightMin = min(frameHeight, TILE_SIZE);

	int x1 = (mPosX + mVelX) / TILE_SIZE;
	int x2 = (mPosX + mVelX + frameWidth - 1) / TILE_SIZE;

	int y1 = mPosY / TILE_SIZE;
	int y2 = (mPosY + heightMin - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
		if (mVelX > 0) {
			if (gGameMap.getValueOfTile(y1, x2) != TILE_EMPTY || gGameMap.getValueOfTile(y2, x2) != TILE_EMPTY) {
				mPosX = x2 * TILE_SIZE;
				mPosX -= frameWidth +1 ;
				mVelX = 8;
			}
		}
		else if (mVelX < 0) {
			if (gGameMap.getValueOfTile(y1, x1) != TILE_EMPTY || gGameMap.getValueOfTile(y2, x1) != TILE_EMPTY) {
				mPosX = (x1 + 1) * TILE_SIZE;
				mVelX = -8;
			}
		}
	} 
	//x1y1        x2y1
  	//
	//
	//x1y2        x2y2


	int widthMin = min(frameWidth, TILE_SIZE);
	x1 = mPosX / TILE_SIZE;
	x2 = (mPosX + widthMin - 1) / TILE_SIZE;

	y1 = (mPosY + mVelY) / TILE_SIZE;
	y2 = (mPosY + mVelY + frameHeight - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
		if (mVelY > 0) {
			cout << x1 << " " << x2 << " " << y1 << " " << y2 << endl;
			if (gGameMap.getValueOfTile(y2, x1) != TILE_EMPTY || gGameMap.getValueOfTile(y2, x2) != TILE_EMPTY) {
				mPosY = y2 * TILE_SIZE;
				mPosY -= frameHeight ;
				mVelY = 0;
				gMainCharacter.typeMotion.isStandingOnGround = true;
			}
		}
		else if (mVelY < 0) {
			if (gGameMap.getValueOfTile(y1, x1) != TILE_EMPTY || gGameMap.getValueOfTile(y1, x2) != TILE_EMPTY) {
				mPosY = (y1 + 1) * TILE_SIZE;
				mVelY = 0;
			}
		}
	}
	
	
	mPosY += mVelY;
	mPosX += mVelX;
	
	if (mPosX < 0) {
		mPosX = 0;
	}
	else if (mPosX + frameWidth > gGameMap.getMaxMapX()) {
		mPosX = gGameMap.getMaxMapX() - frameWidth + 1;
	}
	
}




void Character::setClips() {
	
	if (frameWidth > 0 && frameHeight > 0) {
		for (int i = 0;i < 8;i++) {
			frameClipsRunRight[i].x = i * frameWidth;
			frameClipsRunRight[i].y = 0;
			frameClipsRunRight[i].w = frameWidth;
			frameClipsRunRight[i].h = frameHeight;

			frameClipsRunLeft[i].x =(7 - i )* frameWidth ;
			frameClipsRunLeft[i].y = 0;
			frameClipsRunLeft[i].w = frameWidth ;
			frameClipsRunLeft[i].h = frameHeight;
		}	

		for (int i = 0;i < 7;i++) {
			frameClipsStandRight[i].x = i * frameWidth;
			frameClipsStandRight[i].y = 0;
			frameClipsStandRight[i].w = frameWidth ;
			frameClipsStandRight[i].h = frameHeight;

			frameClipsStandLeft[i].x = (6 - i) * frameWidth ;
			frameClipsStandLeft[i].y = 0;
			frameClipsStandLeft[i].w = frameWidth ;
			frameClipsStandLeft[i].h = frameHeight;
		}

	}
}


void Character::render(SDL_Renderer* renderer) {

	if (typeMotion.goRight  || typeMotion.goLeft ) {
		frame++;
		if (frame / 8 >= 8) {
			frame = 0;
		}
	}
	else {

		frame = 0;
	}
		
	SDL_Texture* currentTexture = NULL;

	if (typeMotion.goRight ) {
		typeMotion.isStanding = false;
		isFacing = FACING_RIGHT;
		currentTexture = gLoadMainCharacter[RUN_RIGHT].getTexture();
	}
	else if (typeMotion.goLeft) {
		isFacing = FACING_LEFT;
		typeMotion.isStanding = false;
		currentTexture = gLoadMainCharacter[RUN_LEFT].getTexture();
	}
	else {
		typeMotion.isStanding = true;
		if (isFacing == FACING_RIGHT) {
			currentTexture = gLoadMainCharacter[STAND_RIGHT].getTexture();
		}
		if (isFacing == FACING_LEFT) {
			currentTexture = gLoadMainCharacter[STAND_LEFT].getTexture();
		}
	}
	SDL_Rect* currentClip = NULL;

	if (typeMotion.isStanding) {
		
		frameStand++;
		if (frameStand / 7 >= 7) {
			frameStand = 0;
		}

		if (isFacing == FACING_RIGHT) {
			currentClip = &frameClipsStandRight[frameStand / 7];
		}
		else {
			currentClip = &frameClipsStandLeft[frameStand / 7];
		}
	}
	else {
		if (isFacing == FACING_RIGHT) {
			currentClip = &frameClipsRunRight[frame / 8];
		}
		else {
			currentClip = &frameClipsRunLeft[frame / 8];
		}
	}
	
	SDL_Rect renderQuad = { mPosX ,mPosY,currentClip->w, currentClip->h };

	SDL_RenderCopy(renderer, currentTexture, currentClip, &renderQuad);
}


int Character::getPosX() {
	return mPosX;
}
int Character::getPosY() {
	return mPosY;
}