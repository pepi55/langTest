#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "src/sdlFunc.h"
#include "src/tetris.h"
#include "art/bmp.xpm"

int main (void) {
	int WidthBack, HeightBack, i, j;
	bool playing = 1;
	//const Uint8 *kbState = SDL_GetKeyboardState(NULL);
	char **imgFromSrc;

	SDL_Event e;
	SDL_Window *win;
	SDL_Renderer *ren;
	SDL_Texture *background;

	//stateOfGamePtr = menu;

	if (SDL_Init(SDL_INIT_VIDEO) != 0 || (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		logSDLError("Init");
		return 1;
	}

	win = SDL_CreateWindow(
			"Generic Title",
			WINDOW_OFFSET_X,
			WINDOW_OFFSET_Y,
			WINDOW_WIDTH,
			WINDOW_HEIGHT,
			SDL_WINDOW_OPENGL
			| SDL_WINDOW_ALLOW_HIGHDPI
			| SDL_WINDOW_BORDERLESS
			| SDL_WINDOW_INPUT_GRABBED
			);
	if (win == NULL) {
		logSDLError("CreateWindow");
		return 2;
	}

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == NULL) {
		logSDLError("CreateRenderer");
		return 3;
	}

	imgFromSrc = bmp_xpm;
	background = loadHeader(imgFromSrc, ren);
	//character = loadTexture("char.png", ren);
	if (background == NULL /*|| character == NULL*/) {
		logSDLError("loadTexture");
		return 4;
	}

	SDL_RenderClear(ren);

	SDL_QueryTexture(background, NULL, NULL, &WidthBack, &HeightBack);

	WidthBack /= 2;
	HeightBack /= 2;

	for (i = 0; i < WINDOW_WIDTH / WidthBack; i++) {
		for (j = 0; j <= WINDOW_HEIGHT / HeightBack; j++) {
			renderTextureS(background, ren, i * WidthBack, j * HeightBack, WidthBack, HeightBack);
		}
	}

	SDL_RenderPresent(ren);

	while (playing) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) playing = 0;
			//if (e.type == SDL_MOUSEBUTTONDOWN) quit = 1;
		}

		SDL_RenderClear(ren);

		for (i = 0; i < WINDOW_WIDTH / WidthBack; i++) {
			for (j = 0; j <= WINDOW_HEIGHT / HeightBack; j++) {
				renderTextureS(background, ren, i * WidthBack, j * HeightBack, WidthBack, HeightBack);
			}
		}

		SDL_RenderPresent(ren);

		playing = stateOfGamePtr();
	}

	SDL_DestroyTexture(background);

	cleanUp(win, ren);

	return 0;
}
