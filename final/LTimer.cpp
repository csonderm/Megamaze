//Claire Sonderman, Karina Dube, Bobby Flores
//Fundamentals of Computing II
//Timer class implementation used for a real time clock during game play
//Time is the basis of your score for each level

//Include SDL2 libraries and LTexture class and LTimer header file
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include "LTexture.h"
#include "LTimer.h"
using namespace std;


//Globally used font for timer
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern LTexture gTimeTextTexture;
extern SDL_Renderer* gRenderer;


LTimer::LTimer()	//constructor
{
	//Initialize the variables
	mStartTicks = 0;
	mPausedTicks = 0;
	
	mPaused = false;
	mStarted = false;
}

void LTimer::start()
{
	//Start the timer
	mStarted = true;
	
	//Unpause the timer
	mPaused = false;
	
	//Get the current clock time
	mStartTicks = SDL_GetTicks();
	mPausedTicks = 0;
}

void LTimer::stop()
{
    	//Stop the timer
    	mStarted = false;

    	//Unpause the timer
   	mPaused = false;

	//Clear tick variables
	mStartTicks = 0;
	mPausedTicks = 0;
}

void LTimer::pause()
{
    	//If the timer is running and isn't already paused
    	if( mStarted && !mPaused ) {
        
		//Pause the timer
        	mPaused = true;

        	//Calculate the paused ticks
       		mPausedTicks = SDL_GetTicks() - mStartTicks;
		mStartTicks = 0;
	}
}

void LTimer::unpause()
{
    	//If the timer is running and paused
    	if( mStarted && mPaused ) {

	        //Unpause the timer
	        mPaused = false;

	        //Reset the starting ticks
	        mStartTicks = SDL_GetTicks() - mPausedTicks;

	        //Reset the paused ticks
	        mPausedTicks = 0;
    	}
}

Uint32 LTimer::getTicks()
{
	//The actual timer time
	Uint32 time = 0;

    	//If the timer is running
	if( mStarted ) {
        
		//If the timer is paused
	        if( mPaused ) {
            		//Return the number of ticks when the timer was paused
            		time = mPausedTicks;
        	}
        	else {
            		//Return the current time minus the start time
            		time = SDL_GetTicks() - mStartTicks;
        	}
    	}

    	return time;
}

bool LTimer::isStarted()
{
	//Timer is running and paused or unpaused
    	return mStarted;
}

bool LTimer::isPaused()
{
	//Timer is running and paused
    	return mPaused && mStarted;
}




