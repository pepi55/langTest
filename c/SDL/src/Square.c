#include <stdio.h>

#include "sdlFunc.h"
#include "Square.h"

void input (SDL_Event e, struct Square *this) {
	if (e.type == SDL_KEYDOWN) {
		switch (e.key.keysym.sym) {
			case SDLK_UP:
				this->yVel -= this->box.h / 2;
				break;

			case SDLK_DOWN:
				this->yVel += this->box.h / 2;
				break;

			case SDLK_LEFT:
				this->xVel -= this->box.w / 2;
				break;

			case SDLK_RIGHT:
				this->xVel += this->box.w / 2;
				break;

			default:
				break;
		}
	} else if (e.type == SDL_KEYUP) {
		switch (e.key.keysym.sym) {
			case SDLK_UP:
				this->yVel += this->box.h / 2;
				break;

			case SDLK_DOWN:
				this->yVel -= this->box.h / 2;
				break;

			case SDLK_LEFT:
				this->xVel += this->box.w / 2;
				break;

			case SDLK_RIGHT:
				this->xVel -= this->box.w / 2;
				break;

			default:
				break;
		}
	}
}

void move (struct Square *this) {
	this->box.x += this->xVel;

	if (this->box.x < 0 || this->box.x + this->box.w > WINDOW_WIDTH) {
		this->box.x -= this->xVel;
	}

	this->box.y += this->yVel;
	if (this->box.y < 0 || this->box.y + this->box.h > WINDOW_HEIGHT) {
		this->box.y -= this->yVel;
	}
}

static struct Square new (SDL_Rect box, int xVel, int yVel) {
	return (struct Square) {
		.box = box, .xVel = xVel, .yVel = yVel, .input = &input
	};
}

const struct SquareClass Square = {
	.new = &new
};
