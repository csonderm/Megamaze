//Bobby Flores, Claire Sonderman, Karina Dube
//March 23, 2015

#ifndef MARBLE_H
#define MARBLE_H
#include <iostream>
#include <SDL2/SDL.h>
#include <string>
using namespace std;

//interface for marble class to represent either a user or enemy marble

Class :: Marble {

	public: 
		Marble();
		void handleEvent( SDL_Event& e);	//waits for user to enter key presses
		void move();	//move marble and determines collision detection
		void render();	//displays marble on screen
		static const int DOT_WIDTH = 20;
		static const int DOT_HEIGHT = 20;
		static const int MAX_VELOCITY = 1;

	private: 
		float xPosition;
		float yPosition;
		int type; //enemy or user 
		float xVelocity;
		float yVelocity;
		SDL_Rect collisionbox;	//detects collision as a box around the marble
		
};

#endif
