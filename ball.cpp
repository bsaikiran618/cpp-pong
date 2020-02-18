#include "game.h"
#include "ball.h"
#include "paddle.h"
#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>

Ball::Ball(int r)
:x(BALL_INIT_X),y(BALL_INIT_Y),radius(r),velocity_x(BALL_INIT_VX),velocity_y(BALL_INIT_VY)
{
	
}

float Ball::getCurrentX(){ return x;}
float Ball::getCurrentY(){ return y;}
float Ball::getVelocityX(){ return velocity_x;}
float Ball::getVelocityY(){ return velocity_y;}

bool Ball::setPosition(float new_x, float new_y)
{
	if(new_x<0 || new_x>WIN_W-radius)
	{
		return false;
	}
	if(new_y<0 || new_y>WIN_H-radius)
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
	
			SDL_RenderDrawPoint(renderer,int(x+x_offset),int(y+y_offset));
		}
	}
}
bool Ball::move()
{
	setPosition(getCurrentX()+velocity_x,getCurrentY()+velocity_y);
}
void Ball::checkCollision(Paddle *left_paddle,Paddle *right_paddle)
{
	if(y == WIN_H-radius || y==radius) //collision with upper wall.
	{
		velocity_y *= -1;
	}
	if(y>=left_paddle->getCurrentY() && y<=left_paddle->getCurrentY()+PADDLE_HEIGHT) //collision with left paddle
	{
		if(x == left_paddle->getCurrentX() || x == left_paddle->getCurrentX()+PADDLE_WIDTH)
			velocity_x *= -1;
	}
	if(y>=right_paddle->getCurrentY() && y<=right_paddle->getCurrentY()+PADDLE_HEIGHT) //collision with right paddle
	{
		if(x == right_paddle->getCurrentX() || x == right_paddle->getCurrentX()+PADDLE_WIDTH)
			velocity_x *= -1;
	}
	if(x == WIN_W-radius || x == radius) //collision with lower wall.
	{
		velocity_x *= -1;
	}
	std::cout << "VELOCITY (X) :" << velocity_x << std::endl;
}
