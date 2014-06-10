#include <stdio.h>
#include <stdbool.h>

//#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_opengl.h>

#include "src/sdlFunc.h"
#include "src/gameFunc.h"

int main (void) {
	initGL_SDL();

	gameLoop();

	cleanUp(win, glwin, ren);

	return 0;
}
