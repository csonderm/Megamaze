/* Megamaze
   Fund II
   Dot implementation
*/


//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <stdlib.h>

#include <vector>
#include "Dot.h"
#include "LTexture.h"

using namespace std;

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern LTexture gDotTexture;
extern const int DOT_FRAMES=2;
extern SDL_Rect g2SpriteClips[DOT_FRAMES];
extern const int EXPLOSION_ANIMATION_FRAMES = 5;
extern SDL_Rect gSpriteClips[EXPLOSION_ANIMATION_FRAMES ];
extern LTexture gSpriteSheetTexture;
extern SDL_Renderer* gRenderer;


//Box collision detector
bool checkCollision( SDL_Rect a, SDL_Rect b );

Dot::Dot(int x, int y, int type)
{
    //Initialize the offsets
    mPosX = x;
    mPosY = y;

	//Set collision box dimension
	mCollider.w = DOT_WIDTH;
	mCollider.h = DOT_HEIGHT;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;

    player = type;
}

void Dot::handleEvent( SDL_Event& e )
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY -= DOT_VEL; break;
            case SDLK_DOWN: mVelY += DOT_VEL; break;
            case SDLK_LEFT: mVelX -= DOT_VEL; break;
            case SDLK_RIGHT: mVelX += DOT_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += DOT_VEL; break;
            case SDLK_DOWN: mVelY -= DOT_VEL; break;
            case SDLK_LEFT: mVelX += DOT_VEL; break;
            case SDLK_RIGHT: mVelX -= DOT_VEL; break;
        }
    }
}

int Dot::move( vector<Dot*> allMarbles, vector<int> marblecollisionX, vector<int> marblecollisionY, int targetx, int targety )
{
    //Move the dot left or right
    mPosX += mVelX;
	mCollider.x = mPosX;

 
	//Move the dot up or down
    	mPosY += mVelY;
	mCollider.y = mPosY;

	int n = marblecollisionX.size();

	for( int i = 0; i < n; i++){
		int collision = 0;
		SDL_Rect box;
		box.x = marblecollisionX[i];
		box.y = marblecollisionY[i];
		box.w = 20;
		box.h = 20;
		if (checkCollision(mCollider, box)){
			mPosX -= mVelX;
			mCollider.x = mPosX;
			
					
		}


		if (checkCollision(mCollider, box)){
			
			mPosY -= mVelY;
			mCollider.y = mPosY;
					
		}
	}

   //If the dot collided or went too far to the left or right
	if( ( mPosX < 0 ) || ( mPosX + DOT_WIDTH > SCREEN_WIDTH ) )
    {
        //Move back
        mPosX -= mVelX;
	mCollider.x = mPosX;
    }

  
    //If the dot collided or went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + DOT_HEIGHT > SCREEN_HEIGHT ) )
    {
        //Move back
        mPosY -= mVelY;
	mCollider.y = mPosY;
    }
    for (int j = 0; j < allMarbles.size(); j++){
	if (checkCollision(mCollider, (*allMarbles[j]).mCollider)&&(this != allMarbles[j])){
		cout << "MADE IT HERE 2!" << endl;
		if (player == 1){		
		    cout << "YOU LOSE!!!!!!!" << endl;
		    return 0;
		}
		else{
		    //Render current frame
		    for (int frame = 0; frame < 25; frame++){
				SDL_Rect* currentClip = &gSpriteClips[ frame/5];
				gSpriteSheetTexture.render( mPosX, mPosY, currentClip );
				//Update screen
				SDL_RenderPresent( gRenderer );

				//Cycle animation
				if( frame / 5 >= EXPLOSION_ANIMATION_FRAMES )
				{
					frame = 0;
				}
		    }
			

			//allMarbles.erase(allMarbles.begin()+j);
			//delete allMarbles[j];	
		    mPosY = -999;
		    
		    (*allMarbles[j]).mPosX = -999;
		    
		}
		
	}
    }


	SDL_Rect targetCollider;
	targetCollider.x = targetx;
	targetCollider.y = targety;
	targetCollider.h = 20;
	targetCollider.w = 20;
	if (checkCollision(mCollider, targetCollider)){
		if (player == 0){
		    mPosY = -999;
		

		}
		else{
		    cout << "YOU WIN!!!!!!!" << endl;
		 	return 1;
		}
		
		
	}

	return -1;

}

void Dot::render()
{
    //Show the dot
	gDotTexture.render( mPosX, mPosY, &g2SpriteClips[1]);
}

void Dot::renderMine()
{
	//Show my dot
	gDotTexture.render( mPosX, mPosY, &g2SpriteClips[0]);

}


bool checkCollision( SDL_Rect a, SDL_Rect b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }


    //If none of the sides from A are outside B
    return true;
}
