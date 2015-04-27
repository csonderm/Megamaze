//Hole.h

#ifndef HOLE_H
#define HOLE_H

using namespace std;
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "LTexture.h"
#include "Dot.h"
#include "Obstacle.h"
//#include "Button.h"

extern LTexture gHoleSheetTexture;
extern LTexture g3SpriteSheetTexture;

class Hole : public Obstacle{
    public:
	Hole(int, int, int, int, string = "Hole", int = 0);
	virtual int action(Dot*);
	virtual void render(); 
	void changeCovered();
	int getbDirect();
	//Button myButton;

    private:
	int bDirect; //position of relevant button
	int covered;
	int hNum; //matches with the same button
};

#endif
