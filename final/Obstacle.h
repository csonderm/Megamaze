//Claire Sonderman, Karina Dube, Bobby Flores
//Fundamentals of Computing II
//obstacle interface

#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
class Dot;

using namespace std;

//obstacle base class, derives hole and button
class Obstacle{
    public:
	Obstacle(int, int, int, int, string = "Obstacle");
	virtual int action(Dot*) = 0;	//each obstacle has an action
	virtual void render() = 0; 	//renders each obstacle
	virtual void resetOver();	//resets button obstacle, see button.h
	SDL_Rect mCollider;

	int getX();
	int getY();
	int getH();
	int getW();
	Dot* getMarblePtr(); 		//marble pointer points to marble interacting with obstacle
	void setMarblePtr(Dot*);
	string getTypeName();
	

    private:
	string typeName;	//type of obstacle
	int x;			//rendering coordinates
	int y;
	int h;			//collision box coordinates
	int w;
	Dot* marblePtr;		//pointer to marble
};

#endif
