//Claire Sonderman, Karina Dube, Bobby Flores
//Fundamentals of Computing II
//Interface for the LButton class
//LButton is used for mouse clicks in game states between levels

//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
using namespace std;

//Button constants
const int BUTTON_WIDTH = 450;
const int BUTTON_HEIGHT = 120;
const int TOTAL_BUTTONS = 1;


//The mouse button
class LButton
{
	public:
		//Initializes internal variables
		LButton();

		//Sets top left position
		void setPosition( int x, int y );

		//Handles mouse event
		bool handleEvent( SDL_Event* e );

	private:
		//Top left position
		SDL_Point mPosition;

};

