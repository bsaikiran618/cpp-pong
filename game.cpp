#include "game.h"
#include <SDL2/SDL.h>
#include "paddle.h"
#include "ball.h"
#include <iostream>
using namespace std;

Game::Game(std::string s)
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		throw InitFailed();		
	}
	window = SDL_CreateWindow(s.c_str(),WIN_X,WIN_Y,WIN_W,WIN_H,SDL_WINDOW_SHOWN);
	surface = SDL_GetWindowSurface(window);
	renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

	left_paddle = new Paddle(LEFT_PADDLE_INIT_POS_X,LEFT_PADDLE_INIT_POS_Y);	
	right_paddle = new Paddle(RIGHT_PADDLE_INIT_POS_X,RIGHT_PADDLE_INIT_POS_Y);	
	ball = new Ball(BALL_RADIUS);
	left_paddle->render(renderer);
	right_paddle->render(renderer);
}
void Game::renderNextFrame()
{
	SDL_SetRenderDrawColor(renderer,0,0,0,0);
	SDL_RenderClear(renderer);

	left_paddle->render(renderer);
	right_paddle->render(renderer);
	ball->render(renderer);

	SDL_RenderPresent(renderer);
}
void Game::startGame()
{
	SDL_Event event;
	bool hasQuit = false;

	while(!hasQuit)
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				hasQuit = true;
				break;
			}
			else
			{
				switch(event.key.keysym.sym)
				{
					case SDLK_UP: right_paddle->moveUp();
					break;
					case SDLK_DOWN:right_paddle->moveDown();
					break;
					case SDLK_w: left_paddle->moveUp();
					break;
					case SDLK_s: left_paddle->moveDown();
					break;
				}
			}
		}
		renderNextFrame();
	}
}
