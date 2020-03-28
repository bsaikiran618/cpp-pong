#ifndef PADDLE_H
#define PADDLE_H
#define PADDLE_HEIGHT 50
#define PADDLE_WIDTH 20
#define PADDLE_COLOR(x) SDL_MapRGB(x -> format, 255,255,255)
#define LEFT_PADDLE_INIT_POS_X 30
#define LEFT_PADDLE_INIT_POS_Y 200
#define RIGHT_PADDLE_INIT_POS_X (LEFT_PADDLE_INIT_POS_X + 550)
#define RIGHT_PADDLE_INIT_POS_Y 200
#define PADDLE_MOVE_STEP 15
#include <SDL2/SDL.h>

class Paddle
{
	private:
		SDL_Rect r;
	public:
		Paddle(int x1,int y1);
		int score;
		void render(SDL_Renderer *);
		void moveUp();
		void moveDown();
		int getCurrentX();
		int getCurrentY();
};
#endif
