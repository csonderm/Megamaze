//Claire Sonderman, Karina Dube, Bobby Flores
//Fundamentals of Computing II
//Implementation for the LButton class
//LButton is used for mouse clicks in game states between levels

//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include "LButton.h"
using namespace std;

//Buttons objects
extern LButton gButtons[ TOTAL_BUTTONS ]; 


LButton::LButton()	
{
	//Constructor, initialize position
	mPosition.x = 0;
	mPosition.y = 0;
}

void LButton::setPosition( int x, int y )
{
	//set the x and y position markers
	mPosition.x = x;
	mPosition.y = y;
}

bool LButton::handleEvent( SDL_Event* e )
{
	//If mouse button up event happened
	if(e->type == SDL_MOUSEBUTTONUP ) {
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if( x < mPosition.x ) {
			inside = false;
		}
		//Mouse is right of the button
		else if( x > mPosition.x + BUTTON_WIDTH ) {
			inside = false;
		}
		//Mouse above the button
		else if( y < mPosition.y ) {
			inside = false;
		}
		//Mouse below the button
		else if( y > mPosition.y + BUTTON_HEIGHT ) {
			inside = false;
		}
		//You clicked in the button area
		else {
			inside=true;
			return inside;
		}
	}
	return false;
}
	

