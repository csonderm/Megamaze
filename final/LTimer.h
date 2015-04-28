#ifndef LTIMER_H
#define LTIMER_H
//Claire Sonderman, Karina Dube, Bobby Flores
//Fundamentals of Computing II
//Timer class interface used for a real time clock during game play
//Time is the basis of your score for each level

//Include SDL2 libraries and LTexture class
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include "LTexture.h"
using namespace std;

class LTimer
{
    public:
		//Initializes variables - constructor
		LTimer();

		//The various clock actions
		void start();		//start clock
		void stop();		//stop and set clock to 0
		void pause();		//pause the clock 
		void unpause();		//make the clock keep going if paused

		//Gets the timer's time
		Uint32 getTicks();	//returns how many ticks on the clock (your time)		

		//Checks the status of the timer
		bool isStarted();	//return mStarted
		bool isPaused();	//return mPaused

    private:
		//The clock time when the timer started
		Uint32 mStartTicks;

		//The ticks stored when the timer was paused
		Uint32 mPausedTicks;

		//The timer status
		bool mPaused;
		bool mStarted;
};
#endif
