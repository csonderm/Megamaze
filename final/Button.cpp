//Button.cpp
//Claire Sonderman, Karina Dube, Bobby Flores
//Fundamentals of Computing II
//button obstacle implementation

#include "Obstacle.h"
#include "Button.h"
#include "Hole.h"
#include <iostream>

using namespace std;


//constructor sets pointer to hole and initializes flag determing whether the marble is over the button
Button::Button(int posX, int posY, int height, int width, string name, Hole* ptr):Obstacle(posX, posY, height, width, name){
	holePtr = ptr;
	over = 0;
}

//button covers the hole when pressed
int Button::action(Dot* marble){
	setMarblePtr(marble);
	(*holePtr).changeCovered(over);
	over = 1;
	return -1;
}

void Button::render(){

}

//ensure button does not repeatedly get pressed when marble is over it
void Button::resetOver(){
	over = 0;
}
