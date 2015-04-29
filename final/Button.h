//Button.h
//Claire Sonderman, Karina Dube, Bobby Flores
//Fundamentals of Computing II
//button obstacle interface


#include "Obstacle.h"
#include "Hole.h"

//derived button class from obstacle base class
class Button : public Obstacle{
    public:
	Button(int, int, int, int, string = "Button", Hole* = NULL);
	virtual int action(Dot*);
	virtual void render();
	virtual void resetOver();
    private:
	Hole* holePtr;	//pointer to corresponding hole
	int over;	//whether marble is over the button
	
};


