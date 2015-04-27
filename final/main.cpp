/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//April 19, 2015 got start screen and when clicked anywhere, move into game
//need to fix click location  
//Using SDL, SDL_image, standard IO, and strings	
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <stdlib.h>
#include <sstream>

using namespace std;

//Screen dimension constants
extern const int SCREEN_WIDTH = 800;
extern const int SCREEN_HEIGHT = 800;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;


#include "LTexture.h"
#include "LTimer.h"

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();


//render map
void renderMap(vector<int> & , vector<int> &, vector<int> &, vector<int> &, vector<int> & marbleType, int & targetx, int & targety, string, vector<int> &, vector<int> &, vector<int> &);

//play game function
int play(string, int *, int *);

//start screen function


//Scene textures
LTexture gDotTexture;
LTexture gBlockTexture;
LTexture gBackgroundTexture;
LTexture gTargetTexture;
LTexture gStartTexture;
LTexture gHoleSheetTexture;
LTexture gButtonTexture;
LTexture gLoseTexture;

const int EXPLOSION_ANIMATION_FRAMES = 5;
SDL_Rect gSpriteClips[EXPLOSION_ANIMATION_FRAMES ];
LTexture gSpriteSheetTexture;

const int DOT_FRAMES = 2;
SDL_Rect g2SpriteClips[DOT_FRAMES];
LTexture g2SpriteSheetTexture;

const int HOLE_FRAMES = 2;
SDL_Rect g3SpriteClips[HOLE_FRAMES];
LTexture g3SpriteSheetTexture;

#include "LButton.h"
//Buttons objects
LButton gButtons[ TOTAL_BUTTONS ]; 

#include "Dot.h"
//#include "Obstacle.h"
#include "Hole.h"
#include "LTimer.h"
LTexture gTimeTextTexture;
LTexture gLivesTexture;
TTF_Font* gFont = NULL;

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
		gWindow = SDL_CreateWindow( "Megamaze", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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
				 //Initialize SDL_ttf
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
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
	
	if( !gButtonTexture.loadFromFile( "media/holeButton.png" ) )
	{
		printf( "Failed to load Wall texture image!\n" );
		success = false;
	}
	
	//Load press texture
	if( !gHoleSheetTexture.loadFromFile( "media/hole.png" ) )
	{
		printf( "Failed to load hole texture!\n" );
		success = false;
	}

	else
	{
		//Set sprite clips
		for(int i=0; i<HOLE_FRAMES; i++){
			g3SpriteClips[ i ].x = 20*i;
			g3SpriteClips[ i ].y = 0;
			g3SpriteClips[ i ].w = 20;
			g3SpriteClips[ i ].h = 20;
		}
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
	if( !gLoseTexture.loadFromFile( "media/StartPage.bmp" ) )
	{
		printf( "Failed to load Lose Page!\n" );
		success = false;
	}
	else{
		//Set buttons in corners
		gButtons[ 0 ].setPosition( 292, 336);
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
			gSpriteClips[ i ].x = 60*i;
			gSpriteClips[ i ].y = 0;
			gSpriteClips[ i ].w = 60;
			gSpriteClips[ i ].h = 60;
		}
	}
	//Open the font
	gFont = TTF_OpenFont( "media/Roboto-Black.ttf", 28 );
	if( gFont == NULL )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	else
	{
		//Set text color as black
		SDL_Color textColor = { 0, 0, 0, 255 };
	}
	return success;
}

void close()
{
	//Free global font
	TTF_CloseFont( gFont );
	gFont = NULL;

	//Free loaded images
	gTimeTextTexture.free();
	gLivesTexture.free();
	gDotTexture.free();
	gSpriteSheetTexture.free();
	gStartTexture.free();
	gLoseTexture.free();
	gBlockTexture.free();
	gTargetTexture.free();

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;


	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}



void renderMap(vector<int> & marblecollisionX, vector<int> & marblecollisionY, vector<int> & startx, vector<int> & starty, vector<int> & marbleType, int & targetx, int & targety, string lvl, vector<int> & Holex, vector<int> & Holey, vector<int> & HoleType){


	marblecollisionX.clear();
	marblecollisionY.clear();
	startx.clear();
	starty.clear();
	marbleType.clear();

	Holex.clear();
	Holey.clear();
	HoleType.clear();

        //Rendering map from text file
        char piece;
        ifstream mazeFile(lvl.c_str());
        int x = 0;
        int y = 0;
	int type;
        if (mazeFile.is_open()){
                while (mazeFile.get (piece)){
                        if (piece == '1'){
                            gBlockTexture.render(0+x*21, 40+21*y);
              			marblecollisionX.push_back(0+x*21);
				marblecollisionY.push_back(40+21*y);
				
			}

		       	if (piece == 'o'){
                            gTargetTexture.render(0+x*21, 40+21*y);
			    targetx = 0+x*21;
			    targety = 40+21*y;
                       	}
			if (piece == 's'){
				startx.push_back(0+x*21);				
				starty.push_back(40+21*y);
				type=1;
				marbleType.push_back(type); //player marble
				
			}
			if (piece == 'e'){
				startx.push_back(0+x*21);				
				starty.push_back(40+21*y);
				type=0;
				marbleType.push_back(type); //enemy marble
			}
			if (piece == 'u'){
				Holex.push_back(0+x*21);				
				Holey.push_back(40+21*y);
				HoleType.push_back(1); //hole marble
			}
			if (piece == 'd'){
				Holex.push_back(0+x*21);				
				Holey.push_back(40+21*y);
				HoleType.push_back(3); //hole marble
			}
			if (piece == 'l'){
				Holex.push_back(0+x*21);				
				Holey.push_back(40+21*y);
				HoleType.push_back(4); //hole marble
			}
			if (piece == 'r'){
				Holex.push_back(0+x*21);				
				Holey.push_back(40+21*y);
				HoleType.push_back(2); //hole marble
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

int start(int *game_state, int time, int lives)
{
	//Set text color as black
	SDL_Color textColor = { 0, 0, 0, 255 };	

	//In memory text stream, set up time to display
	stringstream timeText;
	stringstream livesText;
	timeText.str( "" );
	timeText << "Score: " << ( time / 1000 ) ; 
	livesText.str( "" );
	livesText << "Lives: " << (lives);	
	
	SDL_Event e;
	int quit = 0;
	int click = 0;
	//start page with play button	
		
	while( quit < 2 )
	{
		//Render text
		if( !gTimeTextTexture.loadFromRenderedText( timeText.str().c_str(), textColor ) )
		{
			printf( "Unable to render time texture!\n" );
		}
		if( !gLivesTexture.loadFromRenderedText( livesText.str().c_str(), textColor ) )
		{
			printf( "Unable to render time texture!\n" );
		}
		//Clear screen
		SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( gRenderer );
		gStartTexture.render(0,0);
		gTimeTextTexture.render(300,50);
		gLivesTexture.render(300, 0);
		SDL_RenderPresent( gRenderer );
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				*game_state = 7;
				return 0;
			}
			for( int i = 0; i < TOTAL_BUTTONS; ++i )
			{	
				if(gButtons[ i ].handleEvent( &e )){
					
					click=1;
					
					quit++;
				}
			}						
		}
		//Update screen
		SDL_RenderPresent( gRenderer );	
				
	}
	if (click==1) *game_state = *game_state + 1;
	//cout << "Made it here 3" << endl;
	//return click;		

}

int lose(int *game_state, int time, int lives)
{

	//Set text color as black
	SDL_Color textColor = { 0, 0, 0, 255 };	

	//In memory text stream, set up time to display
	stringstream livesText;

	livesText.str( "" );
	livesText << "YOU LOSE";
	//MAKE TEXTURE WITH A CLOSE BUTTON

	SDL_Event e;
	int quit = 0;
	int click = 0;
	//start page with play button	
		
	while( quit < 2 )
	{
		//Render text
		//if( !gTimeTextTexture.loadFromRenderedText( timeText.str().c_str(), textColor ) )
		//{
		//	printf( "Unable to render time texture!\n" );
		//}
		if( !gLivesTexture.loadFromRenderedText( livesText.str().c_str(), textColor ) )
		{
			printf( "Unable to render time texture!\n" );
		}
		//Clear screen
		SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( gRenderer );
		gLoseTexture.render(0,0);
		//gTimeTextTexture.render(300,50);
		gLivesTexture.render(300, 0);
		SDL_RenderPresent( gRenderer );
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				*game_state = 7;
				return 0;
			}
			for( int i = 0; i < TOTAL_BUTTONS; ++i )
			{	
				if(gButtons[ i ].handleEvent( &e )){
					
					click=1;
					
					quit++;
				}
			}						
		}
		//Update screen
		SDL_RenderPresent( gRenderer );	

				
	}
	if (click==1) *game_state = *game_state + 1;

	//return click;	


}

int play(string lvl, int *game_state, int *lives)
{
	vector<Dot*> allMarbles;
	vector<Hole*> allHoles;
	vector<Obstacle*> allObstacles;

	vector<int> marblecollisionX; //wall x
	vector<int> marblecollisionY; //wall y

	vector<int> startx; //vector of marble start x
	vector<int> starty; //vector of marble start y
	vector<int> marbleType; //vector of marble types (correlates with startx starty)

	vector<int> Holex; //vector of marble start x
	vector<int> Holey; //vector of marble start y
	vector<int> HoleType; //vector of marble types (correlates with startx starty)

	int targetx;
	int targety;
	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			int frame = 0;
	
			
			//play game
			renderMap(marblecollisionX, marblecollisionY, startx,starty,marbleType,targetx,targety, lvl, Holex, Holey, HoleType);
					
			for (int i = 0; i < startx.size(); i++){
			    Dot* marble = new Dot(startx[i], starty[i], marbleType[i]);
			    allMarbles.push_back(marble);
			
			}

			for (int i = 0; i < Holex.size(); i++){
			    Hole* hole = new Hole(Holex[i], Holey[i], 21, 21, "Hole", HoleType[i]);
			    allHoles.push_back(hole);
			    allObstacles.push_back(hole);
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
						*game_state = 7;
						return -1;
					}
					

					//Handle input for the dot
					for (int i = 0; i < allMarbles.size(); i++){
					    allMarbles[i]->handleEvent(e);

					}
				}
			

				//Move the dot and check collision
				for (int i = 0; i < allMarbles.size(); i++){
				     int win=allMarbles[i]->move(allMarbles, marblecollisionX, marblecollisionY, targetx, targety/*, allObstacles*/);
				     if (win==1){
					*game_state = *game_state+1;	
					
					return 1;
				     }
				     else if (win==0){
					*game_state = *game_state - 1;
					*lives=(*lives)-1;
					if (*lives==0){
						*game_state=6;
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
				
				renderMap(marblecollisionX, marblecollisionY, startx, starty, marbleType,targetx,targety, lvl, Holex, Holey, HoleType);

				for (int i = 0; i < allHoles.size(); i++){
					allHoles[i]->render();
				}
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
	lvlFiles.push_back("levels/lvl3.txt");
	int lvl=0;
	int complete;
	int lives=2;		//you get 2 lives or you lose
	int time=0;
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
			int game_state = 0;
			bool playing = true;
			while(playing){
				 
				switch(game_state){
					case 0: {start(&game_state, time, lives);}	//start game			
						break; 	
					case 1: {LTimer timer;	
						timer.start();
						play(lvlFiles[0], &game_state, &lives);
						timer.pause();
						time=timer.getTicks();
						timer.stop();}
						break;
					case 2: {start(&game_state, time, lives);}
						break;
					case 3: {LTimer timer2;	
						timer2.start();
						play(lvlFiles[1], &game_state, &lives);
						timer2.pause();
						time=timer2.getTicks();
						timer2.stop();}
						break;
					case 4: {start(&game_state, time, lives);}
						break;
					case 5: {LTimer timer3;	
						timer3.start();
						play(lvlFiles[2], &game_state, &lives);
						timer3.pause();
						time=timer3.getTicks();
						timer3.stop();}
						break;
					case 6: {lose(&game_state, time, lives);}
						break; 
					case 7: {playing=false;}
						break;
				}
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
