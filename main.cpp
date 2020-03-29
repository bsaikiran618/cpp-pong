#include <iostream>
#include <SDL2/SDL.h>
#include "game.h"
using namespace std;

int main(int argc, char *argv[])
{
	Game *g;

	try 
	{
		g = new Game("Pong++");
		g->startGame();
	}
	catch(...)
	{
		cout << "Couldnt initialize game!" << endl;
	}

	return 0;
}
