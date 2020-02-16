#include "game.h"
#include "ball.h"
#include <SDL2/SDL.h>
#include <cmath>


Ball::Ball(int r)
:x(BALL_INIT_X),y(BALL_INIT_Y),radius(r)
{
	
}

int Ball::getCurrentX(){ return x;}
int Ball::getCurrentY(){ return y;}
float Ball::getVelocityX(){ return velocity_x;}
float Ball::getVelocityY(){ return velocity_y;}

bool Ball::setPosition(int new_x, int new_y)
{
	if(new_x<=0 || new_x>=WIN_W)
	{
		return false;
	}
	if(new_y<=0 || new_y>=WIN_H)
	{
		return false;
	}
	x = new_x;
	y = new_y;
}
bool Ball::setVelocityX(float new_vx)
{
	velocity_x = new_vx;
}
bool Ball::setVelocityY(float new_vy)
{
	velocity_y = new_vy;
}
void Ball::render(SDL_Renderer *renderer)
{
	//draw a circle 
	// x = rcos(A)
	// y = rsin(A)

	SDL_SetRenderDrawColor(renderer,255,255,255,0);

	float angle;
	float step = 0.05f;
	float PI = 3.1415f;

	for(int rad=radius;rad>0;rad-=1)
	{
		for(angle = 0;angle<=2*PI;angle+=step)
		{
			int x_offset = int(rad* cosf(angle))%rad;
			int y_offset = int(rad* sinf(angle))%rad;
	
			SDL_RenderDrawPoint(renderer,(x+x_offset),(y+y_offset));
		}
	}
}
bool Ball::move()
{
	//yet to be written.
}
