
#ifndef GAME_HEADER
 #define GAME_HEADER
#define WIN_X SDL_WINDOWPOS_UNDEFINED
#define WIN_Y SDL_WINDOWPOS_UNDEFINED
#define WIN_W 640
#define WIN_H 480
#define GAME_TITLE "My Window"
#include <string>
#include "paddle.h"
#include "ball.h"
#include <SDL2/SDL.h>
class Game
{
	private:
		SDL_Window *window;
		SDL_Surface *surface;
		SDL_Renderer *renderer;
		Paddle *left_paddle,*right_paddle;
		Ball *ball;
	public:
		class InitFailed
		{
			public:
				InitFailed()
				{
				
				}
		};
		Game(std::string s);
		void startGame();
		void renderNextFrame();
};

#endif
