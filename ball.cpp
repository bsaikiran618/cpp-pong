#include "game.h"
#include "ball.h"
#include "paddle.h"
#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>

#define PI 3.14159

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
	if(new_x<0)
	{
		return false;
	}
	if(new_y<0)
	{
		return false;
	}
	if(new_x > WIN_W)
	{
		x = WIN_W;
	}
	if(new_y > WIN_H)
	{
		y = WIN_H;
	}
	if(new_x <= WIN_W && new_y <= WIN_H)
	{
		x = new_x;
		y = new_y;
	}
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
void Ball::checkPaddleCollision(Paddle * paddle)
{
	float top_x = x,top_y=y-BALL_RADIUS;
	float left_x = x-BALL_RADIUS,left_y = y;
	float right_x = x+BALL_RADIUS,right_y = y;
	float bottom_x = x,bottom_y = y+BALL_RADIUS;
	
	//hits top face

	if((bottom_x>=paddle->getCurrentX())&&(bottom_x<=(paddle->getCurrentX()+PADDLE_WIDTH)))
		{
		if((bottom_y>=paddle->getCurrentY())&&(bottom_y<=(paddle->getCurrentY()+PADDLE_HEIGHT)))
		{
			setVelocityY(getVelocityY()*-1);
		}
	}

	//hits bottom face

	if((top_x>=paddle->getCurrentX())&&(top_x<=(paddle->getCurrentX()+PADDLE_WIDTH)))
	{
		if((top_y>=paddle->getCurrentY())&&(top_y<=(paddle->getCurrentY()+PADDLE_HEIGHT)))
		{
			setVelocityY(getVelocityY()*-1);
		}
	}
	//hits left face

	if((right_y>=paddle->getCurrentY())&&(right_y <= (paddle->getCurrentY()+PADDLE_HEIGHT)))
	{
		if((right_x>=paddle->getCurrentX())&&(right_x<=(paddle->getCurrentX()+PADDLE_WIDTH)))
		{
			setVelocityX(getVelocityX()*-1);	

			//change angle.
			float mid_y = paddle->getCurrentY()+(PADDLE_HEIGHT/2);
			float y_diff = left_y - mid_y;

			velocity_y = (y_diff/PADDLE_HEIGHT)*(PI/2.0);
		}
	}

	//hits right face

    if((left_y>=paddle->getCurrentY())&&(left_y <= (paddle->getCurrentY()+PADDLE_HEIGHT)))
	{
		if((left_x>=paddle->getCurrentX())&&(left_x<=(paddle->getCurrentX()+PADDLE_WIDTH)))
		{
			setVelocityX(getVelocityX()*-1);

			//change angle.
			float mid_y = paddle->getCurrentY()+(PADDLE_HEIGHT/2);
			float y_diff = left_y - mid_y;

			velocity_y = (y_diff/PADDLE_HEIGHT)*(PI/2.0);
		}
	}
}
void Ball::checkCollision(Paddle *left_paddle,Paddle *right_paddle)
{

	float top_x = x,top_y=y-BALL_RADIUS;
	float left_x = x-BALL_RADIUS,left_y = y;
	float right_x = x+BALL_RADIUS,right_y = y;
	float bottom_x = x,bottom_y = y+BALL_RADIUS;


	//hit right WALL
		if(right_x>=WIN_W)
		{

			setVelocityX(getVelocityX()*-1);
			left_paddle->score++;
		}

	//hit left wall.
		if(left_x<=0)
		{
			setVelocityX(getVelocityX()*-1);
			right_paddle->score++;
		}

	//collision with ceiling

	if(top_y<=0){setVelocityY(getVelocityY()*-1);}

	//collision with floor

	if(bottom_y>=WIN_H){setVelocityY(getVelocityY()*-1);}

	//collision with left paddle

	checkPaddleCollision(left_paddle);

	//collision with right paddle

	checkPaddleCollision(right_paddle);

}
