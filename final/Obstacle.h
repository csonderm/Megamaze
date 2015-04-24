#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <string>

using namespace std;

class Obstacle{
    public:
	Obstacle(int, int, int, int, string = "Obstacle");
	virtual void action() = 0;
	virtual void render(int, int, SDL_Rect*) = 0; 
	LTexture gTexture;
	SDL_Rect mCollider;

    private:
	string typeName;
	int x;
	int y;
	int h;
	int w;
};


#endif













#endif OBSTACLE
