#ifndef BALL_HEADER
#define BALL_HEADER
#define BALL_RADIUS 10
#define BALL_INIT_X WIN_W/2.0
#define BALL_INIT_Y WIN_H/2.0
#define BALL_INIT_VX 0.8
#define BALL_INIT_VY 0
#include <SDL2/SDL.h>
#include "paddle.h"

class Ball
{
	private:
		float x,y;
		float velocity_x,velocity_y;
		int radius;
		void checkPaddleCollision(Paddle*);
	public:
		Ball(int);
		float getCurrentX();
		float getCurrentY();
		float getVelocityX();
		float getVelocityY();
		bool setPosition(float , float );
		bool setVelocityX(float);
		bool setVelocityY(float);
		bool move();
		void checkCollision(Paddle *,Paddle *);
		void render(SDL_Renderer *);
};
#endif
