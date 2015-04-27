//Button.cpp

#include "Obstacle.h"
#include "Button.h"
#include "Hole.h"
#include <iostream>

using namespace std;

Button::Button(int posX, int posY, int height, int width, string name, Hole* ptr):Obstacle(posX, posY, height, width, name){
	holePtr = ptr;
}

int Button::action(Dot* button){
	(*holePtr).changeCovered();
	return -1;
}

void Button::render(){

}
