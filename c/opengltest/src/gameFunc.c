#include <stdio.h>
#include <GL/glut.h>

#include "sdlFunc.h"
#include "gameFunc.h"
#include "../art/bmp.xpm"

void gameLoop (void) {
	bool quit = 0;
	char **imgFromSrc;
	//const Uint8 *kbState = SDL_GetKeyboardState(NULL);

	int i, j;
	int backgroundWidth, backgroundHeight;

	SDL_Event e;
	SDL_Texture *background;
	//SDL_Texture **;

	imgFromSrc = bmp_xpm;
	background = loadHeader(imgFromSrc, ren);
	//* = loadTexture("src/*.png", ren);
	if (background == NULL /*|| * == NULL*/) {
		logSDLError("loadTexture");
		return;
	}

	SDL_QueryTexture(background, NULL, NULL, &backgroundWidth, &backgroundHeight);

	backgroundWidth /= 2;
	backgroundHeight /= 2;

	while (!quit) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) quit = 1;
			//if (e.type == SDL_MOUSEBUTTONDOWN) quit = 1;
		}

		SDL_RenderClear(ren);

		for (i = 0; i < WINDOW_WIDTH / backgroundWidth; i++) {
			for (j = 0; j <= WINDOW_HEIGHT / backgroundHeight; j++) {
				renderTextureS(background, ren, i * backgroundWidth, j * backgroundHeight, backgroundWidth, backgroundHeight);
			}
		}

		SDL_RenderPresent(ren);
	}

	SDL_DestroyTexture(background);
	//SDL_DestroyTexture(*);
}
