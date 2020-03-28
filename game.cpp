#include "game.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include "paddle.h"
#include "ball.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

Game::Game(std::string s)
{
	frames_rendered = 0;
	isComplete = false;
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
	ResultFont = TTF_OpenFont("./arial.ttf",26);

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

		displayMessage(TitleFont,SDL_Color{255,255,255},"Pong++",TITLE_X,TITLE_Y,TITLE_W,TITLE_H);
		displayMessage(SubtitleFont,SDL_Color{0,0,255},"created by Boddulus",SUBT_X,SUBT_Y,SUBT_W,SUBT_H);
	}	
	
	ball->move();
	ball->checkCollision(left_paddle,right_paddle) ;// also checks collisions with walls.
	left_paddle->render(renderer);
	right_paddle->render(renderer);
	ball->render(renderer);
	displayScore();

	if(left_paddle->score == GAME_MAX_SCORE)
	{
		displayMessage(ResultFont,SDL_Color{255,255,0},"WINS!",LEFT_RES_X,LEFT_RES_Y,LEFT_RES_W,LEFT_RES_H);
		isComplete = true;
	}
	else if(right_paddle->score == GAME_MAX_SCORE)
	{
		displayMessage(ResultFont,SDL_Color{255,255,0},"WINS!",RIGHT_RES_X,RIGHT_RES_Y,RIGHT_RES_W,RIGHT_RES_H);
		isComplete = true;
	}

	SDL_RenderPresent(renderer);
	if(frames_rendered <= MESSAGE_DISPLAY_FRAMES)
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
		if(!isComplete)
		{
			renderNextFrame();
		}
	}
}
void Game::displayScore()
{
	SDL_Color White = {0, 255, 0};
	ostringstream os1;
	ostringstream os2;


	os1 << "SCORE: " << left_paddle->score;
	os2 << "SCORE: " << right_paddle->score;

	displayMessage(ScoreFont,SDL_Color{0,255,0},os1.str(),10,10,100,50);
	displayMessage(ScoreFont,SDL_Color{0,255,0},os2.str(),WIN_W-100,10,100,50);
}
void Game::displayMessage(TTF_Font *font,SDL_Color color,string msg,int x,int y,int w, int h)
{
		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, msg.c_str(), color);
		if(surfaceMessage == NULL)
		{
			cerr << "couldnt create font surface!" << endl;
			return;	
		}
		SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); 

		if(Message == NULL)
		{
			cerr << "couldnt create font texture!" << endl;
			return;
		}

		SDL_Rect Message_rect; //create a rect
		Message_rect.x = x; 
		Message_rect.y = y;
		Message_rect.w = w;
		Message_rect.h = h;
		SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

		SDL_FreeSurface(surfaceMessage);
		SDL_DestroyTexture(Message);
}
