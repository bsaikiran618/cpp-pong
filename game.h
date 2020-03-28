
#ifndef GAME_HEADER
 #define GAME_HEADER
#define WIN_X SDL_WINDOWPOS_UNDEFINED
#define WIN_Y SDL_WINDOWPOS_UNDEFINED
#define WIN_W 640
#define WIN_H 480

#define TITLE_X (WIN_W/2 - 70)
#define TITLE_Y 100
#define TITLE_W 200
#define TITLE_H 100

#define SUBT_X (WIN_W/2 - 200)
#define SUBT_Y 200
#define SUBT_W 400
#define SUBT_H 50

#define LEFT_RES_X 10
#define LEFT_RES_Y WIN_H/2
#define LEFT_RES_W 100
#define LEFT_RES_H 70

#define RIGHT_RES_X (WIN_W/2) + 400
#define RIGHT_RES_Y WIN_H/2
#define RIGHT_RES_W 100
#define RIGHT_RES_H 70

#define GAME_TITLE "My Window"
#define MESSAGE_DISPLAY_FRAMES 150
#define GAME_MAX_SCORE 5
#include <string>
#include "paddle.h"
#include "ball.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
class Game
{
	private:
		TTF_Font *TitleFont,*SubtitleFont,*ScoreFont,*ResultFont;
		SDL_Window *window;
		SDL_Surface *surface;
		SDL_Renderer *renderer;
		Paddle *left_paddle,*right_paddle;
		Ball *ball;
		bool isComplete;
	public:
		int frames_rendered;
		class InitFailed
		{
			public:
				InitFailed()
				{

				}
		};
		Game(std::string s);
		void displayMessage(TTF_Font *,SDL_Color,std::string ,int ,int ,int , int );
		void startGame();
		void renderNextFrame();
		void displayScore();
};

#endif
