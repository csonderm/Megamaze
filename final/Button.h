//Button.h

#include "Obstacle.h"
#include "Hole.h"

class Button : public Obstacle{
    public:
	Button(int, int, int, int, string = "Button", Hole* = NULL);
	virtual int action(Dot*);
	virtual void render();
    private:
	Hole* holePtr;
};


