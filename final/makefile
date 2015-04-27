all: main

main: main.o LTexture.o Dot.o LButton.o Obstacle.o Hole.o Button.o LTimer.o
	g++ main.o LTexture.o Dot.o LButton.o Obstacle.o Hole.o Button.o LTimer.o -o main -w -lSDL2 -lSDL2_image -lSDL2_ttf
main.o: main.cpp
	g++ -c main.cpp 
Dot.o: Dot.cpp Dot.h
	g++ -c Dot.cpp
LTexture.o: LTexture.cpp LTexture.h
	g++ -c LTexture.cpp
LButton.o: LButton.cpp LButton.h
	g++ -c LButton.cpp
Obstacle.o: Obstacle.cpp Obstacle.h
	g++ -c Obstacle.cpp
Hole.o: Hole.cpp Hole.h
	g++ -c Hole.cpp
Button.o: Button.cpp Button.h
	g++ -c Button.cpp
LTimer.o: LTimer.cpp LTimer.h
	g++ -c LTimer.cpp

clean:
	rm -r *.o main 
