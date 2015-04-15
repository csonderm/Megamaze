/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <stdlib.h>

using namespace std;

//Screen dimension constants
extern const int SCREEN_WIDTH = 800;
extern const int SCREEN_HEIGHT = 800;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;


#include "LTexture.h"


//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();


//render map
void renderMap(vector<int> & , vector<int> &, vector<int> &, vector<int> &, vector<int> & marbleType, int & targetx, int & targety);


//Scene textures
LTexture gDotTexture;
LTexture gBlockTexture;
LTexture gBackgroundTexture;
LTexture gTargetTexture;

#include "Dot.h"

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load press texture
	if( !gDotTexture.loadFromFile( "media/dot.bmp" ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}

	//Load Foo' texture
	if( !gBlockTexture.loadFromFile( "media/wall.bmp" ) )
	{
		printf( "Failed to load Wall texture image!\n" );
		success = false;
	}
	
	

	//Load target texture
	if( !gTargetTexture.loadFromFile( "media/target.bmp" ) )
	{
		printf( "Failed to load target texture image!\n" );
		success = false;
	}


	return success;
}

void close()
{
	//Free loaded images
	gDotTexture.free();

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}



void renderMap(vector<int> & marblecollisionX, vector<int> & marblecollisionY, vector<int> & startx, vector<int> & starty, vector<int> & marbleType, int & targetx, int & targety){

        //Rendering map from text file
        char piece;
        ifstream mazeFile("levels/lvl1.txt");
        int x = 0;
        int y = 0;
	
        if (mazeFile.is_open()){
                while (mazeFile.get (piece)){
                        if (piece == '1'){
                            gBlockTexture.render(0+x*20, 40+20*y);
              			marblecollisionX.push_back(0+x*20);
				marblecollisionY.push_back(40+20*y);
				
			}
              
		       	if (piece == 'o'){
                            gTargetTexture.render(0+x*20, 40+20*y);
			    targetx = 0+x*20;
			    targety = 40+20*y;
                       	}
			if (piece == 's'){
				startx.push_back(0+x*20);				
				starty.push_back(40+20*y);
				marbleType.push_back(1); //player marble
				
			}
			if (piece == 'e'){
				startx.push_back(0+x*20);				
				starty.push_back(40+20*y);
				marbleType.push_back(0); //enemy marble
			}
			
                        if (piece == '\n'){
                            y++;
                            x=-1;
                       	}
			
                       	x++;         
		}
                mazeFile.close();
        }
        else cout << "Unable to open file";
}





int main( int argc, char* args[] )
{

	vector<Dot*> allMarbles;

	vector<int> marblecollisionX; //wall x
	vector<int> marblecollisionY; //wall y

	vector<int> startx; //vector of marble start x
	vector<int> starty; //vector of marble start y
	vector<int> marbleType; //vector of marble types (correlates with startx starty)

	int targetx;
	int targety;
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			renderMap(marblecollisionX, marblecollisionY, startx,starty,marbleType,targetx,targety);

			for (int i = 0; i < startx.size(); i++){
			    Dot* marble = new Dot(startx[i], starty[i], marbleType[i]);
			    allMarbles.push_back(marble);
			}

/*			//The dot that will be moving around on the screen
			Dot dot(startx[0],starty[0],marbleType[0]);

			//The dot that will be moving around on the screen

			Dot marble(startx[1], starty[1],marbleType[1]);
			Dot marble2(startx[2], starty[2],marbleType[2]);
*/
			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

					//Handle input for the dot
					for (int i = 0; i < allMarbles.size(); i++){
					    allMarbles[i]->handleEvent(e);

					}
/*					dot.handleEvent( e );
					marble.handleEvent( e );
					marble2.handleEvent( e );
*/				}

				//Move the dot and check collision
				for (int i = 0; i < allMarbles.size(); i++){
				     allMarbles[i]->move(allMarbles, marblecollisionX, marblecollisionY, targetx, targety );
				}

/*				dot.move( marble, marblecollisionX,  marblecollisionY, targetx, targety );
				marble.move( dot,marblecollisionX,  marblecollisionY, targetx, targety);
				marble2.move ( marble,marblecollisionX,  marblecollisionY, targetx, targety);
*/				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );
				marblecollisionX.clear();
				marblecollisionY.clear();
				marbleType.clear();
				startx.clear();
				starty.clear();
				//render Map
				renderMap(marblecollisionX, marblecollisionY, startx, starty, marbleType,targetx,targety);
				
				for (int i = 0; i < allMarbles.size(); i++){
				     allMarbles[i]->render();
				}
				
/*				//Render dot
				dot.render();

				//Render dot
				marble.render();
				
				//Render dot
				marble2.render();
*/	
				//Update screen
				SDL_RenderPresent( gRenderer );
			}

		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
