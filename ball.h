#ifndef BALL_HEADER
#define BALL_HEADER
#define BALL_RADIUS 10
#define BALL_INIT_X WIN_W/2.0
#define BALL_INIT_Y WIN_H/2.0
#define BALL_INIT_VX 10
#define BALL_INIT_VY 10
#include <SDL2/SDL.h>

class Ball
{
	private:
		int x,y;
		float velocity_x,velocity_y;
		int radius;
	public:
		Ball(int);
		int getCurrentX();
		int getCurrentY();
		float getVelocityX();
		float getVelocityY();
		bool setPosition(int , int );
		bool setVelocityX(float);
		bool setVelocityY(float);
		bool move();
		void render(SDL_Renderer *);
};
#endif
