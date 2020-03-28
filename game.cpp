#include "game.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include "paddle.h"
#include "ball.h"
#include <iostream>
#include <sstream>
using namespace std;

Game::Game(std::string s)
{
	frames_rendered = 0;
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		throw InitFailed();		
	}
	if(TTF_Init() < 0)
	{
		cerr << "Couldnt initialize TTF!" << endl;
		throw InitFailed();
	}

	TitleFont = TTF_OpenFont("./arial.ttf",26);
	SubtitleFont = TTF_OpenFont("./arial.ttf",20);
	ScoreFont = TTF_OpenFont("./arial.ttf",15);

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


	if(frames_rendered < MESSAGE_DISPLAY_FRAMES)
	{

		SDL_Color White = {255, 255, 255};
		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(TitleFont, "PONG++", White);

		if(surfaceMessage == NULL){cout << "cannot create surface!" << endl;}
		SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); 

		if(Message == NULL){cout << "cannot create texture!" << endl;}

		SDL_Rect Message_rect; //create a rect
		Message_rect.x = (WIN_W/2) - 70;  //controls the rect's x coordinate 
		Message_rect.y = (WIN_H/3) - 100; // controls the rect's y coordinte
		Message_rect.w = 200; // controls the width of the rect
		Message_rect.h = 70; // controls the height of the rect
		SDL_RenderCopy(renderer, Message, NULL, &Message_rect); 


		surfaceMessage = TTF_RenderText_Solid(SubtitleFont, "-created by boddulus", White);

		if(surfaceMessage == NULL){cout << "cannot create surface!" << endl;}
		Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); 

		if(Message == NULL){cout << "cannot create texture!" << endl;}

		Message_rect.x = (WIN_W/2) - 40;  //controls the rect's x coordinate 
		Message_rect.y = (WIN_H/3); // controls the rect's y coordinte
		Message_rect.w = 200; // controls the width of the rect
		Message_rect.h = 50; // controls the height of the rect
		SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

		SDL_FreeSurface(surfaceMessage);
		SDL_DestroyTexture(Message);
	}	
	
	ball->move();
	ball->checkCollision(left_paddle,right_paddle) ;// also checks collisions with walls.
	left_paddle->render(renderer);
	right_paddle->render(renderer);
	ball->render(renderer);
	displayScore();
	SDL_RenderPresent(renderer);
	if(frames_rendered < MESSAGE_DISPLAY_FRAMES)
		frames_rendered++;
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
			const Uint8 *keyState = SDL_GetKeyboardState(NULL);
			if(keyState[SDL_SCANCODE_UP])
			{
				right_paddle->moveUp();
			}
			if(keyState[SDL_SCANCODE_DOWN])
			{
				right_paddle->moveDown();
			}
			if(keyState[SDL_SCANCODE_W])
			{
				left_paddle->moveUp();
			}
			if(keyState[SDL_SCANCODE_S])
			{
				left_paddle->moveDown();
			}

		}
		renderNextFrame();
	}
}
void Game::displayScore()
{

		SDL_Color White = {0, 255, 0};
		ostringstream os1;
		ostringstream os2;


		os1 << "SCORE: " << left_paddle->score;
		os2 << "SCORE: " << right_paddle->score;



		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(ScoreFont, os1.str().c_str() , White);
		
		if(surfaceMessage == NULL){cout << "cannot create font surface!" << endl;}
		SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); 

		if(Message == NULL){cout << "cannot create font texture!" << endl;}

		SDL_Rect Message_rect; //create a rect
		Message_rect.x = 10;  //controls the rect's x coordinate 
		Message_rect.y = 10; // controls the rect's y coordinte
		Message_rect.w = 100; // controls the width of the rect
		Message_rect.h = 30; // controls the height of the rect

		SDL_RenderCopy(renderer, Message, NULL, &Message_rect); 

		surfaceMessage = TTF_RenderText_Solid(ScoreFont, os2.str().c_str() , White);
		
		if(surfaceMessage == NULL){cout << "cannot create font surface!" << endl;}
		Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); 

		if(Message == NULL){cout << "cannot create font texture!" << endl;}

		Message_rect.x = WIN_W - 120;  //controls the rect's x coordinate 
		Message_rect.y = 10; // controls the rect's y coordinte
		Message_rect.w = 100; // controls the width of the rect
		Message_rect.h = 30; // controls the height of the rect

		SDL_RenderCopy(renderer, Message, NULL, &Message_rect); 
		


		SDL_FreeSurface(surfaceMessage);
		SDL_DestroyTexture(Message);

}
