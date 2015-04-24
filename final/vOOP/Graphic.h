// Graphic.h

#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "LTexture.h"

using namespace std;

class Graphic{
    public:
	Graphic(int w = 21, int h = 21, int x, int y);
	virtual void colAction(Dot, Graphic);
	LTexture gTexture;
	SDL_Rect mCollider;
	int getPosX();
	int getPosY();
	virtual void render(int, int, SDL_Rect* = NULL);
    private:
	int width;
	int height;
	int posX;
	int posY;

};

Graphic::Graphic(int w, int h, int x, int y){
	width = w;
	height = h;

	posX = x;
	posY = y;
	
	mCollider.w = w;
	mCollider.h = h;
}

int Graphic::getPosX(){
	return posX;
}

int Graphic::getPosY(){
	return posY;
}

void render(int x, int y, SDL_Rect* clip){
	gTexture.render(x, y, clip);
}

#endif
