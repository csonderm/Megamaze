all: main

main: main.o LTexture.o Dot.o
	g++ main.o LTexture.o Dot.o -o main -w -lSDL2 -lSDL2_image
main.o: main.cpp
	g++ -c main.cpp 
Dot.o: Dot.cpp Dot.h
	g++ -c Dot.cpp
LTexture.o: LTexture.cpp LTexture.h
	g++ -c LTexture.cpp

clean:
	rm -r *.o main 
