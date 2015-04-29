//Hole.h
//Claire Sonderman, Karina Dube, Bobby Flores
//Fundamentals of Computing II
//hole obstacle interface, hole is covered when button is pressed

#ifndef HOLE_H
#define HOLE_H
//Using SDL, SDL_image
using namespace std;
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "LTexture.h"
#include "Dot.h"
#include "Obstacle.h"
#include "LTimer.h"


extern LTexture gHoleSheetTexture;
extern LTexture g3SpriteSheetTexture;

//hole is derived class from obstacle class
class Hole : public Obstacle{
    public:
	Hole(int, int, int, int, string = "Hole", int = 0);
	virtual int action(Dot*); //marbles fall in hole
	virtual void render(); 
	void changeCovered(int); //when button is pressed cover the hole
	int getbDirect();
	//Button myButton;

    private:
	int bDirect; //position of relevant button
	int covered; //hole is covered or open
	int hNum; //matches with the same button
};

#endif
