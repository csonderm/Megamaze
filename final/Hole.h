//Hole.h

using namespace std;


class Hole{
    public:
	Hole(int, int, int, int, string = "Hole", int);
	int action(&Dot);
	virtual void render(SDL_Rect*); 

    private:
	int bDirect; //position of relevant button
	int covered;
	int hNum; //matches with the same button
};

Hole::Hole(int posX, int posY, int height, int width, string name, int d) : Obstacle(posX, posY, height, width, name) {
	bDirect = d;	// 1 up, 2 right, 3 down, 4 left 
	covered = 0;	// hole is uncovered
}

int Hole::action(&Dot marble){
	if (covered == 0){
		marble.setAlive(false);
		if (marble.getPlayer() == 1){
			return 0;
		}
	}
	else{
	}
}

void Hole::render(SDL_Rect* clip){
	gTexture.render(x,y,"media/hole.png");
	if (bDirect == 1){
		gTexture.render(x, y+21, "media/holeButton.png"); 
	}
	else if (bDirect == 2){
		gTexture.render(x+21, y, "media/holeButton.png"); 
	}
	else if (bDirect == 3){
		gTexture.render(x, y-21, "media/holeButton.png"); 
	}
	else if (bDirect == 4){
		gTexture.render(x-21, y, "media/holeButton.png"); 
	}
	else{
	}
}
