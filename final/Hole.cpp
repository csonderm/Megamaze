//Hole.cpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Hole.h"
#include <stdio.h>
#include <iostream>
#include "LTexture.h"
#include "Obstacle.h"
#include "Dot.h"
extern LTexture gHoleSheetTexture;
extern LTexture g3SpriteSheetTexture;
extern LTexture gButtonTexture;

extern const int HOLE_FRAMES = 2;
extern SDL_Rect g3SpriteClips[HOLE_FRAMES];

using namespace std;

Hole::Hole(int posX, int posY, int height, int width, string name, int d):Obstacle(posX, posY, height, width, name) {
	bDirect = d;	// 1 up, 2 right, 3 down, 4 left 
	covered = 0;	// hole is uncovered
}

int Hole::action(Dot* marble){
	if (covered == 0){
		marble->setAlive(false);
		if (marble->getPlayer() == 1){
			return 0;
		}
		return -1;
	}
	else{
		return -1;
	}
}

void Hole::render(){
	if (covered == 0){
	    gHoleSheetTexture.render(getX(), getY(), &g3SpriteClips[0]);
	}
	else{
	    gHoleSheetTexture.render(getX(), getY(), &g3SpriteClips[1]);
	}
	if (bDirect == 1){ //up
		gButtonTexture.render(getX(), getY()-21); 
	}
	else if (bDirect == 2){ //right
		gButtonTexture.render(getX()+21, getY()); 
	}
	else if (bDirect == 3){ //down
		gButtonTexture.render(getX(), getY()+21); 
	}
	else if (bDirect == 4){ // left
		gButtonTexture.render(getX()-21, getY()); 
	}
	else{
	}
}

void Hole::changeCovered(int over){
    if (over == 0){
	if (covered == 0){
		covered = 1;
	}
	else{
		covered = 0;
	}
    }
}

