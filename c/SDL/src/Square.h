#ifndef SQUARE_H
#define SQUARE_H

#include <SDL2/SDL.h>

typedef struct Square {
	SDL_Rect box;
	int xVel, yVel;

	void (*input)(SDL_Event *e, struct Square *this);
	void (*move)(struct Square *this);
	SDL_Texture (*texture)(struct Square *this);
} sqr;

extern const struct SquareClass {
	struct Square (*new)(SDL_Rect box, int xVel, int yVel);
} Square;

#endif
