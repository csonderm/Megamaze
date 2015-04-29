//#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>
//#include "Dot.h"
//Claire Sonderman, Karina Dube, Bobby Flores
//Fundamentals of Computing II
//obstacle implementation
#include "Obstacle.h"


using namespace std;
//constructor initializes coordinates of image and size of collision box
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
//returns image x coordinate
int Obstacle::getX(){
	return x;
}
//returns image y coordinate
int Obstacle::getY(){
	return y;
}
//returns collision box height
int Obstacle::getH(){
	return h;
}
//returns collision box width
int Obstacle::getW(){
	return w;
}
//returns type of obtacle
string Obstacle::getTypeName(){
	return typeName;
}
//returns pointer to marble object
Dot* Obstacle::getMarblePtr(){
	return marblePtr;
}
//sets pointer to point to marble 
void Obstacle::setMarblePtr(Dot* ptr){
	marblePtr = ptr;
}

void Obstacle::resetOver(){
}
