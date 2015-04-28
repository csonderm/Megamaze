//Claire Sonderman, Karina Dube, Bobby Flores
//Fundamentals of Computing II
//main.cpp is the main file where all of the Megamaze classes
//and logic will come together. It includes a game manager switch-case
//structure. 

//Using SDL, SDL_image, SDL_ttf, standard IO, and strings, etc.	
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


//Important global variables
//Screen dimension constants
extern const int SCREEN_WIDTH = 800;
extern const int SCREEN_HEIGHT = 800;
//The window we'll be rendering to
SDL_Window* gWindow = NULL;
//The window renderer
SDL_Renderer* gRenderer = NULL;



//More class header files to include
#include "LTexture.h"



//Function prototypes
//Starts up SDL and creates window
bool init();
//Loads media
bool loadMedia();
//Frees media and shuts down SDL
void close();
//render map
void renderMap(vector<int> & , vector<int> &, vector<int> &, vector<int> &, vector<int> & marbleType, int & targetx, int & targety, string, vector<int> &, vector<int> &, vector<int> &);
//play game function
int play(string, int *, int *, int *);
//start screen function
//transition screen function 



//Scene textures and sprite sheets
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



//More header files
#include "LButton.h"
//Buttons objects
LButton gButtons[ TOTAL_BUTTONS ]; 
#include "Dot.h"
//#include "Obstacle.h"
#include "Hole.h"
#include "LTimer.h"
#include "Button.h"



//Font textures and declarations
LTexture gTimeTextTexture;
LTexture gLivesTexture;
TTF_Font* gFont = NULL;
LTexture gTTextTexture;



bool init()	
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else {
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) {
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Megamaze", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL ) {
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else {
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_SOFTWARE);
			if( gRenderer == NULL ) {
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else {
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
				 //Initialize SDL_ttf
				if( TTF_Init() == -1 ) {
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

	//Load dot texture
	if( !gDotTexture.loadFromFile( "media/marbles.png" ) ) {
		printf( "Failed to load dot texture!\n" );
		success = false;
	}
	else {
		//Set sprite clips
		for(int i=0; i<DOT_FRAMES; i++) {
			g2SpriteClips[ i ].x = 20*i;
			g2SpriteClips[ i ].y = 0;
			g2SpriteClips[ i ].w = 20;
			g2SpriteClips[ i ].h = 20;
		}
	}

	//Load block(wall) texture
	if( !gBlockTexture.loadFromFile( "media/wall.bmp" ) ) {
		printf( "Failed to load Wall texture image!\n" );
		success = false;
	}

	//Load button texture	
	if( !gButtonTexture.loadFromFile( "media/holeButton.png" ) ) {
		printf( "Failed to load Wall texture image!\n" );
		success = false;
	}
	
	//Load hole texture
	if( !gHoleSheetTexture.loadFromFile( "media/hole.png" ) ) {
		printf( "Failed to load hole texture!\n" );
		success = false;
	}

	else {
		//Set sprite clips
		for(int i=0; i<HOLE_FRAMES; i++) {
			g3SpriteClips[ i ].x = 20*i;
			g3SpriteClips[ i ].y = 0;
			g3SpriteClips[ i ].w = 20;
			g3SpriteClips[ i ].h = 20;
		}
	}
	
	//Load target texture
	if( !gTargetTexture.loadFromFile( "media/target.bmp" ) ) {
		printf( "Failed to load target texture image!\n" );
		success = false;
	}

	//Load start screen texture
	if( !gStartTexture.loadFromFile( "media/StartPage.bmp" ) ) {
		printf( "Failed to load Start Page!\n" );
		success = false;
	}
	else {
		//Set buttons in corners
		gButtons[ 0 ].setPosition( 292, 336);
	}

	//Load lose screen texture
	if( !gLoseTexture.loadFromFile( "media/StartPage.bmp" ) ) {
		printf( "Failed to load Lose Page!\n" );
		success = false;
	}
	else {
		//Set buttons in corners
		gButtons[ 0 ].setPosition( 292, 336);
	}

	//Load explosionsprite sheet texture
	if( !gSpriteSheetTexture.loadFromFile( "media/Explosion-Sprite-Sheet.png" ) ) {
		printf( "Failed to load explosion texture!\n" );
		success = false;
	}
	else {
		//Set sprite clips
		for(int i=0; i<EXPLOSION_ANIMATION_FRAMES; i++) {
			gSpriteClips[ i ].x = 60*i;
			gSpriteClips[ i ].y = 0;
			gSpriteClips[ i ].w = 60;
			gSpriteClips[ i ].h = 60;
		}
	}

	//Open the font
	gFont = TTF_OpenFont( "media/Roboto-Black.ttf", 28 );
	if( gFont == NULL ) {
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	else {
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
	g3SpriteSheetTexture.free();
	gHoleSheetTexture.free();
	gButtonTexture.free();

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


void renderMap(vector<int> & marblecollisionX, vector<int> & marblecollisionY, vector<int> & startx, vector<int> & starty, vector<int> & marbleType, int & targetx, int & targety, string lvl, vector<int> & Holex, vector<int> & Holey, vector<int> & HoleType, vector<int> & Buttonx, vector<int> & Buttony)
{
	//Clear all vectors to render new map
	marblecollisionX.clear();
	marblecollisionY.clear();
	startx.clear();
	starty.clear();
	marbleType.clear();

	Holex.clear();
	Holey.clear();
	HoleType.clear();

	Buttonx.clear();
	Buttony.clear();

        //Rendering map from text file
        char piece;
        ifstream mazeFile(lvl.c_str());
        int x = 0;
        int y = 0;
	int type;
        if (mazeFile.is_open()) {	//open file
        	while (mazeFile.get (piece)) {	//parse through text level file
                	if (piece == '1') {			//block wall 
                            gBlockTexture.render(0+x*21, 40+21*y);
              			marblecollisionX.push_back(0+x*21);
				marblecollisionY.push_back(40+21*y);
			}
		       	if (piece == 'o') {			//target
                            gTargetTexture.render(0+x*21, 40+21*y);
			    targetx = 0+x*21;
			    targety = 40+21*y;
                       	}
			if (piece == 's') {			//player marble
				startx.push_back(0+x*21);				
				starty.push_back(40+21*y);
				type=1;
				marbleType.push_back(type); 
			}
			if (piece == 'e') {			//enemy marcle
				startx.push_back(0+x*21);				
				starty.push_back(40+21*y);
				type=0;
				marbleType.push_back(type); 
			}
			if (piece == 'u') {			//hole, button above
				Holex.push_back(0+x*21);				
				Holey.push_back(40+21*y);
				Buttonx.push_back(0+x*21);				
				Buttony.push_back(40+21*y-21);
				HoleType.push_back(1);
			}
			if (piece == 'd') {			//hole, button below		
				Holex.push_back(0+x*21);				
				Holey.push_back(40+21*y);
				Buttonx.push_back(0+x*21);				
				Buttony.push_back(40+21*y+21);
				HoleType.push_back(3); 
			}
			if (piece == 'l') {			//hole, button to left
				Holex.push_back(0+x*21);				
				Holey.push_back(40+21*y);
				Buttonx.push_back(0+x*21-21);				
				Buttony.push_back(40+21*y);
				HoleType.push_back(4); 
			}
			if (piece == 'r') {			//hole, button to right
				Holex.push_back(0+x*21);				
				Holey.push_back(40+21*y);
				Buttonx.push_back(0+x*21+21);				
				Buttony.push_back(40+21*y);
				HoleType.push_back(2); 
			}
                        if (piece == '\n') {			//new line
                            y++;
                            x=-1;
                       	}
			
                       	x++;         
		}
                mazeFile.close();				//close lvl file
        }
        else cout << "Unable to open file";			//can't open the lvl file
}

int start(int *game_state, int time, int lives)
{
	//Set text color as black
	SDL_Color textColor = { 0, 0, 0, 255 };	

	//In memory text stream, set up time and lives left to display
	stringstream timeText;
	stringstream livesText;
	timeText.str( "" );
	timeText << "Time: " << ( time / 1000 ) ; 
	livesText.str( "" );
	livesText << "Lives: " << (lives);	
	
	//event handler
	SDL_Event e;

	//initialize variables
	int quit = 0;
	int click = 0;
		
	//set up start screen with play button	
	while( quit < 2 ) {
		//Load text
		if( !gTimeTextTexture.loadFromRenderedText( timeText.str().c_str(), textColor ) ) {
			printf( "Unable to render time texture!\n" );
		}
		if( !gLivesTexture.loadFromRenderedText( livesText.str().c_str(), textColor ) ) {
			printf( "Unable to render time texture!\n" );
		}

		//Clear screen, set up draw color, then render, text textures and set up renderer
		SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( gRenderer );
		gStartTexture.render(0,0);
		gTimeTextTexture.render(300,50);
		gLivesTexture.render(300, 0);
		SDL_RenderPresent( gRenderer );
		
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 ) {
			//User requests quit
			if( e.type == SDL_QUIT ) {
				//exit
				*game_state = 9;	
				return 0;
			}
			for( int i = 0; i < TOTAL_BUTTONS; ++i ) {	
				if(gButtons[ i ].handleEvent( &e )) {
					click=1;
					quit++;
					//button has been clicked
				}
			}						
		}
		//Update screen
		SDL_RenderPresent( gRenderer );	
				
	}
	if (click==1) *game_state = *game_state + 1;
	//return click;		

}

int lose(int *game_state, int time, int lives)
{

	//Set text color as black
	SDL_Color textColor = { 0, 0, 0, 255 };	

	//In memory text stream, set up lose message to display
	stringstream livesText;
	livesText.str( "" );
	livesText << "YOU LOSE";
	
	//MAKE TEXTURE WITH A CLOSE BUTTON

	//event handler
	SDL_Event e;

	//initialize variables
	int quit = 0;
	int click = 0;
	
	//lose screen
	while( quit < 2 ) {
		//load text
		if( !gLivesTexture.loadFromRenderedText( livesText.str().c_str(), textColor ) ) {
			printf( "Unable to render time texture!\n" );
		}

		//Clear screen, set draw color, render texts and set up renderer
		SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( gRenderer );
		gLoseTexture.render(0,0);
		gLivesTexture.render(300, 0);
		SDL_RenderPresent( gRenderer );
		
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 ) {
			//User requests quit
			if( e.type == SDL_QUIT ) {
				//exit
				*game_state = 9;
				return 0;
			}
			for( int i = 0; i < TOTAL_BUTTONS; ++i ) {	
				if(gButtons[ i ].handleEvent( &e )) {
					//button was clicked
					click=1;
					quit++;
				}
			}						
		}
		//Update screen
		SDL_RenderPresent( gRenderer );				
	}
	//next screen
	if (click==1) *game_state = *game_state + 1;

	//return click;	


}

int play(string lvl, int *game_state, int *lives, int *time)
{
	vector<Dot*> allMarbles;	//all of the marbles are here, pointer to the marbles
	vector<Hole*> allHoles;		//all of the holes are here, pointer to holes
	vector<Obstacle*> allObstacles;	//all obstacles are here, pointer to obstacles

	vector<int> marblecollisionX; 	//wall x coords
	vector<int> marblecollisionY; 	//wall y coords

	vector<int> startx; 		//vector of marble start x coords, indices align with allMarbles
	vector<int> starty; 		//vector of marble start y coords
	vector<int> marbleType; 	//vector of marble types (correlates with startx starty)

	vector<int> Holex; 		//vector of hole start x
	vector<int> Holey; 		//vector of hole start y
	vector<int> HoleType; 		//vector of hole types (correlates with Holex, Holey)

	vector<int> Buttonx; 		//vector of button start x coords, not LButton
	vector<int> Buttony; 		//vector of button start y coords

	int targetx;			//target x coord
	int targety;			//target y coord
	
	//Set text color as black
	SDL_Color textColor = { 0, 0, 0, 255 };	

	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	int frame = 0;

	//play game
	//render map, allocate for marcles, holes, buttons, put into appropriate vectors
	renderMap(marblecollisionX, marblecollisionY, startx,starty,marbleType,targetx,targety, lvl, Holex, Holey, HoleType, Buttonx, Buttony);
					
	for (int i = 0; i < startx.size(); i++) {
		Dot* marble = new Dot(startx[i], starty[i], marbleType[i]);
		allMarbles.push_back(marble);
	}

	for (int i = 0; i < Holex.size(); i++) {
		Hole* hole = new Hole(Holex[i], Holey[i], 15, 15, "Hole", HoleType[i]);
		allHoles.push_back(hole);
		allObstacles.push_back(hole);
	}
			
	for (int i = 0; i < Buttonx.size(); i++){
		Button* button = new Button(Buttonx[i], Buttony[i], 5, 5, "Button", allHoles[i]);
		allObstacles.push_back(button);
	}

	//initialize timer and start it for the level
	LTimer timer;	
	timer.start();
	
	//While application is running
	while( !quit ) {
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 ) {
			//User requests quit
			if( e.type == SDL_QUIT ) {
				*game_state = 9;
				return -1;
			}
			
			//Handle input for the dot
			for (int i = 0; i < allMarbles.size(); i++) {
				allMarbles[i]->handleEvent(e);
			}
		}

		//In memory text stream, set up time to display
		stringstream tText;
		stringstream lText;
		tText.str( "" );
		tText << "Time: " << ( timer.getTicks() / 1000 ) ; 
		lText.str( "" );
		lText << "Lives: " << ( *lives); 
		//load text
		if( !gTTextTexture.loadFromRenderedText( tText.str().c_str(), textColor ) ) {
			printf( "Unable to render time texture!\n" );
		}
		if( !gLivesTexture.loadFromRenderedText( lText.str().c_str(), textColor ) ) {
			printf( "Unable to render lives texture!\n" );
		}

		//Move the dot and check collision
		for (int i = 0; i < allMarbles.size(); i++) {
	 		int win=allMarbles[i]->move(allMarbles, marblecollisionX, marblecollisionY, targetx, targety, allObstacles);
			if (win==1) {
				*game_state = *game_state+1;	//next state
				timer.pause();			//pause timer
				*time=timer.getTicks();		//get timer time for transition screen
				timer.stop();			//stop the timer			
				return 1;			//you win this level
			}
			else if (win==0) {			//didn't win
				*game_state = *game_state - 1;
				*lives=(*lives)-1;
				if (*lives==0) {
					*game_state=8;
				}
				timer.pause();
				*time=timer.getTicks();
				timer.stop();	
				return 0;
			}	
			else {	//else do nothing
			}
		}
			
		//Clear screen, draw color, clear vectors for next iteration
		SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( gRenderer );
		marblecollisionX.clear();
		marblecollisionY.clear();
		marbleType.clear();
		startx.clear();
		starty.clear();
		
		//rerender Map, render texts, holes, marbles, etc. to screen 
		renderMap(marblecollisionX, marblecollisionY, startx, starty, marbleType,targetx,targety, lvl, Holex, Holey, HoleType, Buttonx, Buttony);
		gTTextTexture.render(600,20);
		gLivesTexture.render(600, 55);
	
		for (int i = 0; i < allHoles.size(); i++) {
			allHoles[i]->render();
		}
		for (int i = 0; i < allMarbles.size(); i++) {	
		//render mine if player marcle, else render other marbles if they are alive
			if ( marbleType[i]== 1 ) {
				allMarbles[i]->renderMine();
			}
			else if ( marbleType[i] == 0 && (*allMarbles[i]).getAlive()==true ) {
		    		allMarbles[i]->render();
			}
		}
			
		//Update screen
		SDL_RenderPresent( gRenderer );
	}
}



//main program
int main( int argc, char* args[] )
{
	//set up level vector that we will run through
	vector<string> lvlFiles;
	lvlFiles.push_back("levels/lvl1.txt");
	lvlFiles.push_back("levels/lvl2.txt");
	lvlFiles.push_back("levels/lvl3.txt");
	lvlFiles.push_back("levels/lvl4.txt");
	
	//initialize variacles
	int lvl=0;
	int complete;
	//three lives or dead
	//time and lives passed into and out of screens to display
	int lives=3;		
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
			//case condition
			int game_state = 0;
			//loop condition
			bool playing = true;
			while(playing){
				//start game, go through each level, going to transition states between the levels 
				switch(game_state){
					case 0: {start(&game_state, time, lives);}				
						break; 	
					case 1: play(lvlFiles[3], &game_state, &lives, &time);
						break;
					case 2: {start(&game_state, time, lives);}
						break;	
					case 3: play(lvlFiles[1], &game_state, &lives, &time);
						break;
					case 4: {start(&game_state, time, lives);}
						break;
					case 5: play(lvlFiles[2], &game_state, &lives, &time);
						break;
					case 6: {start(&game_state, time, lives);}
						break;
					case 7: play(lvlFiles[3], &game_state, &lives, &time);
						break;
					case 8: {lose(&game_state, time, lives);}	//you lost
						break; 
					case 9: {playing=false;}			//end game
						break;
				}
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
