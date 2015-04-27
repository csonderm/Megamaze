//#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>
//#include "Dot.h"
#include "Obstacle.h"


using namespace std;

Obstacle::Obstacle(int posX, int posY, int height, int width, string name){
	mCollider.x = posX;
	mCollider.y = posY;
	mCollider.h = height;
	mCollider.w = width;
	w = width;
	h = height;
	x = posX;
	y = posY;
	typeName = name;
	marblePtr = NULL;
}

int Obstacle::getX(){
	return x;
}
int Obstacle::getY(){
	return y;
}
int Obstacle::getH(){
	return h;
}
int Obstacle::getW(){
	return w;
}
string Obstacle::getTypeName(){
	return typeName;
}

Dot* Obstacle::getMarblePtr(){
	return marblePtr;
}

void Obstacle::setMarblePtr(Dot* ptr){
	marblePtr = ptr;
}

void Obstacle::resetOver(){
}
