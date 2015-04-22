/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//April 19, 2015 got start screen and when clicked anywhere, move into game
//need to fix click location  
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
void renderMap(vector<int> & , vector<int> &, vector<int> &, vector<int> &, vector<int> & marbleType, int & targetx, int & targety, string);

//play game function
int play(string);

//start screen function
int start();


//Scene textures
LTexture gDotTexture;
LTexture gBlockTexture;
LTexture gBackgroundTexture;
LTexture gTargetTexture;
LTexture gStartTexture;

const int EXPLOSION_ANIMATION_FRAMES = 5;
SDL_Rect gSpriteClips[EXPLOSION_ANIMATION_FRAMES ];
LTexture gSpriteSheetTexture;

const int DOT_FRAMES = 2;
SDL_Rect g2SpriteClips[DOT_FRAMES];
LTexture g2SpriteSheetTexture;

#include "LButton.h"
//Buttons objects
LButton gButtons[ TOTAL_BUTTONS ]; 

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
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_SOFTWARE);
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
	if( !gDotTexture.loadFromFile( "media/marbles.png" ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}

	else
	{
		//Set sprite clips
		for(int i=0; i<DOT_FRAMES; i++){
			g2SpriteClips[ i ].x = 20*i;
			g2SpriteClips[ i ].y = 0;
			g2SpriteClips[ i ].w = 20;
			g2SpriteClips[ i ].h = 20;
		}
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

	if( !gStartTexture.loadFromFile( "media/StartPage.bmp" ) )
	{
		printf( "Failed to load Start Page!\n" );
		success = false;
	}
	else{
		//Set buttons in corners
		gButtons[ 0 ].setPosition( 292, 336);
	//	gButtons[ 1 ].setPosition(0, 0 );
	//	gButtons[ 2 ].setPosition( 0,0 );
	//	gButtons[ 3 ].setPosition( 292, 336);
	}

	//Load sprite sheet texture
	if( !gSpriteSheetTexture.loadFromFile( "media/Explosion-Sprite-Sheet.png" ) )
	{
		printf( "Failed to load explosion texture!\n" );
		success = false;
	}
	else
	{
		//Set sprite clips
		for(int i=0; i<EXPLOSION_ANIMATION_FRAMES; i++){
			gSpriteClips[ i ].x = 118*i;
			gSpriteClips[ i ].y = 0;
			gSpriteClips[ i ].w = 118;
			gSpriteClips[ i ].h = 118;
		}
	}

	return success;
}

void close()
{
	//Free loaded images
	gDotTexture.free();
	gSpriteSheetTexture.free();
	gStartTexture.free();
	gBlockTexture.free();
	gTargetTexture.free();

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}



void renderMap(vector<int> & marblecollisionX, vector<int> & marblecollisionY, vector<int> & startx, vector<int> & starty, vector<int> & marbleType, int & targetx, int & targety, string lvl){


	marblecollisionX.clear();
	marblecollisionY.clear();
	startx.clear();
	starty.clear();
	marbleType.clear();

        //Rendering map from text file
        char piece;
        ifstream mazeFile(lvl.c_str());
        int x = 0;
        int y = 0;
	int type;
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
				type=1;
				marbleType.push_back(type); //player marble
				
			}
			if (piece == 'e'){
				startx.push_back(0+x*20);				
				starty.push_back(40+20*y);
				type=0;
				marbleType.push_back(type); //enemy marble
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

int start()
{
	SDL_Event e;
	bool quit=false;
	int click;
	//start page with play button	
	//cout << "Made it here 2" << endl;		
	while( !quit )
	{
		gStartTexture.render(0,0);
		SDL_RenderPresent( gRenderer );
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}
			for( int i = 0; i < TOTAL_BUTTONS; ++i )
			{	
				if(gButtons[ i ].handleEvent( &e )){
					click=1;
					quit=true;
				}
			}						
		}
				
	}
	//cout << "Made it here 3" << endl;
	return click;		

}

int play(string lvl)
{
	vector<Dot*> allMarbles;

	vector<int> marblecollisionX; //wall x
	vector<int> marblecollisionY; //wall y

	vector<int> startx; //vector of marble start x
	vector<int> starty; //vector of marble start y
	vector<int> marbleType; //vector of marble types (correlates with startx starty)

	int targetx;
	int targety;
	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			int frame = 0;
	
			
			//play game
			renderMap(marblecollisionX, marblecollisionY, startx,starty,marbleType,targetx,targety, lvl);
					
			for (int i = 0; i < startx.size(); i++){
			    Dot* marble = new Dot(startx[i], starty[i], marbleType[i]);
			    allMarbles.push_back(marble);
				(*allMarbles[i]).setVelocity(0,0);		
			}
			
			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						return -1;
					}


					//Handle input for the dot
					for (int i = 0; i < allMarbles.size(); i++){
					    allMarbles[i]->handleEvent(e);

					}
				}
			

				//Move the dot and check collision
				for (int i = 0; i < allMarbles.size(); i++){
				     int win=allMarbles[i]->move(allMarbles, marblecollisionX, marblecollisionY, targetx, targety );
				     if (win==1){
					int size = allMarbles.size();
					for(int i = 0; i < size; i++){
						(*allMarbles[i]).setVelocity(0,0);
						delete allMarbles[i];
					}
					
					return 1;
				     }
				     else if (win==0){
					int size = allMarbles.size();
					for(int i = 0; i < size; i++){
						(*allMarbles[i]).setVelocity(0,0);
						delete allMarbles[i];
					}
					return 0;
				     }	
				     else{
				     }
				}
			

				//if(!win) break;
				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );
				marblecollisionX.clear();
				marblecollisionY.clear();
				marbleType.clear();
				startx.clear();
				starty.clear();
				//render Map
				
				renderMap(marblecollisionX, marblecollisionY, startx, starty, marbleType,targetx,targety, lvl);

				for (int i = 0; i < allMarbles.size(); i++){
					if ( marbleType[i]== 1 ) {
						allMarbles[i]->renderMine();
					}
					else if ( marbleType[i] == 0 && (*allMarbles[i]).getAlive()==true ){
				     		allMarbles[i]->render();
					}
				}
				
				//Update screen
				SDL_RenderPresent( gRenderer );

			}
}




int main( int argc, char* args[] )
{
	vector<string> lvlFiles;
	lvlFiles.push_back("levels/lvl1.txt");
	lvlFiles.push_back("levels/lvl2.txt");
	int lvl=0;
	int complete;
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
			//start page
			int startgame=start();
			//cout << "Made it here" << endl;
			while(lvl!=lvlFiles.size()){
				complete = play(lvlFiles[lvl]);
				if (complete==0){

				}
				else if (complete == 1){
					lvl++;				
				}
				else if (complete == -1){
					return SDL_QUIT;

				}
			}		
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
