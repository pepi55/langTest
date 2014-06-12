#include <stdio.h>
#include <GL/glut.h>
//#include <SDL2/SDL_image.h>

#include "sdlFunc.h"

Uint16 makeHiColorPixel (SDL_PixelFormat *fmt, Uint8 red, Uint8 green, Uint8 blue) {
	Uint16 value;

	value = ((red >> fmt->Rloss) << fmt->Rshift) + ((green >> fmt->Gloss) << fmt->Gshift) + ((blue >> fmt->Bloss) << fmt->Bshift);

	return value;
}

void sdlInit (SDL_Window *screen) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0 /*|| (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG*/) {
		sdlLogError("SDL initialization");
	}

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	screen = SDL_CreateWindow(
			WINDOW_NAME,
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			WINDOW_WIDTH,
			WINDOW_HEIGHT,
			SDL_WINDOW_OPENGL
			| SDL_WINDOW_SHOWN
			| SDL_WINDOW_ALLOW_HIGHDPI
			//| SDL_WINDOW_FULLSCREEN
			//| SDL_WINDOW_INPUT_GRABBED
			| SDL_WINDOW_BORDERLESS
			| SDL_WINDOW_RESIZABLE
			);
	if (screen == NULL) {
		sdlLogError("Creating window");
	}

	glContext = SDL_GL_CreateContext(screen);

	glClearColor(1.0, 1.0, 1.0, 1.0);
	//glClearDepth(1.0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	SDL_GL_SetSwapInterval(1);
}

void sdlExit (SDL_Window *screen, /*SDL_Renderer *renderer, */SDL_GLContext glContext) {
	SDL_GL_DeleteContext(glContext);
	//SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(screen);

	//IMG_Quit();
	SDL_Quit();
}

void sdlLogError (char *error) {
	fprintf(stderr, "\nError: %s, at %s\n", SDL_GetError(), error);
	exit(1);
}
