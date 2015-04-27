//Button.cpp

#include "Obstacle.h"
#include "Button.h"
#include "Hole.h"
#include <iostream>

using namespace std;

Button::Button(int posX, int posY, int height, int width, string name, Hole* ptr):Obstacle(posX, posY, height, width, name){
	holePtr = ptr;
	over = 0;
}

int Button::action(Dot* marble){
	setMarblePtr(marble);
	(*holePtr).changeCovered(over);
	over = 1;
	return -1;
}

void Button::render(){

}

void Button::resetOver(){
	over = 0;
}
