#include "paddle.h"
#include "game.h"
#include <iostream>
using namespace std;

Paddle::Paddle(int x1,int y1)
{
	score = 0;
	r.w = PADDLE_WIDTH;
	r.h = PADDLE_HEIGHT;
	r.x = x1;
	r.y = y1;
}
void Paddle::render(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer,255,255,255,0);
	SDL_RenderFillRect(renderer,&r);
	SDL_RenderDrawRect(renderer,&r);
}
int Paddle::getCurrentX()
{
	return r.x;
}
int Paddle::getCurrentY()
{
	return r.y;
}
void Paddle::moveUp()
{
	int new_y = r.y - PADDLE_MOVE_STEP;
	if(new_y > 0)
	{
		r.y = new_y;
	}
}
void Paddle::moveDown()
{
	int new_y = r.y + PADDLE_MOVE_STEP;
	if(new_y < (WIN_H-PADDLE_HEIGHT))
	{
		r.y = new_y;
	}
}
