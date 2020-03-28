main : main.o game.o paddle.o ball.o arial.ttf
	g++ main.o game.o paddle.o ball.o -lSDL2 -lSDL2_ttf -o main
main.o: main.cpp game.h
	g++ -c main.cpp
game.o: game.cpp paddle.h game.h
	g++ -c game.cpp
paddle.o : paddle.cpp game.h paddle.h
	g++ -c paddle.cpp
ball.o : ball.cpp ball.h paddle.h
	g++ -c ball.cpp
clearall:
	rm main main.o game.o paddle.o ball.o
