/* Megamaze
   Fund II
   Dot interface
*/ 
#ifndef DOT_H
#define DOT_H

#include <vector>

using namespace std;

//The dot that will move around on the screen
class Dot
{
    public:
		//The dimensions of the dot
		static const int DOT_WIDTH = 20;
		static const int DOT_HEIGHT = 20;

		//Maximum axis velocity of the dot
		static const int DOT_VEL = 1;			//modified this

		//Initializes the variables
		Dot(int = 0, int=0, int = 0);

		virtual void colAction(Dot, Graphic);

		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event& e );

		//Moves the dot and checks collision
		int move( vector<Dot*>, vector<int> , vector<int> , int, int );

		//Shows the dot on the screen
		void render();
		void renderMine();

		//Dot's collision box
		SDL_Rect mCollider;

		//The X and Y offsets of the dot
		int mPosX, mPosY;
		
		bool getAlive();
		void setAlive(bool);
		int getPlayer();
		void setVelocity(int x,int y);

    private:
		

		//The velocity of the dot
		int mVelX, mVelY;

		int player;

		bool alive;
		
		
};

#endif
