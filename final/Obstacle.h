
#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
class Dot;

using namespace std;

class Obstacle{
    public:
	Obstacle(int, int, int, int, string = "Obstacle");
	virtual int action(Dot*) = 0;
	virtual void render() = 0; 
	virtual void resetOver();
	SDL_Rect mCollider;

	int getX();
	int getY();
	int getH();
	int getW();
	Dot* getMarblePtr();
	void setMarblePtr(Dot*);
	string getTypeName();
	

    private:
	string typeName;
	int x;
	int y;
	int h;
	int w;
	Dot* marblePtr;
};

#endif
