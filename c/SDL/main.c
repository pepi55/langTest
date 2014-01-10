#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "sdlFunc.h"

int main (void) { //int argv, char **argc
	int x, y, i, j, bW, bH, fW, fH;
	bool quit = 0;

	SDL_Event e;
	SDL_Window *win;
	SDL_Renderer *ren;
	SDL_Texture *bg;
	SDL_Texture *fg;

	if (SDL_Init(SDL_INIT_VIDEO) != 0 || (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		logSDLError("Init");
		return 1;
	}

	win = SDL_CreateWindow("Hello World!", WINDOW_OFFSET_X, WINDOW_OFFSET_Y, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (win == NULL) {
		logSDLError("CreateWindow");
		return 2;
	}

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == NULL) {
		logSDLError("CreateRenderer");
		return 3;
	}

	bg = loadBmp("../SDL/bitmap/bmp.bmp", ren);
	fg = loadTexture("../SDL/bitmap/png.png", ren);
	if (bg == NULL || fg == NULL) {
		logSDLError("loadTexture");
		return 4;
	}

	SDL_RenderClear(ren);

	SDL_QueryTexture(bg, NULL, NULL, &bW, &bH);

	bW /= 2;
	bH /= 2;

	for (i = 0; i < WINDOW_WIDTH / bW; i++) {
		for (j = 0; j <= WINDOW_HEIGHT / bH; j++) {
			renderTextureS(bg, ren, i * bW, j * bH, bW, bH);
		}
	}

	SDL_QueryTexture(fg, NULL, NULL, &fW, &fH);

	x = 40; //-(fW / 2);
	y = 40; //-(fH / 2);

	renderTexture(fg, ren, x + 50, y + 50);

	SDL_RenderPresent(ren);

	//SDL_Delay(WINDOW_LIFETIME);
	while (!quit) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) quit = 1;
			if (e.type == SDL_MOUSEBUTTONDOWN) quit = 1;
		}

		if (e.type == SDL_KEYDOWN) {
			x -= 5;

			if (x < -fW) {
				x = WINDOW_WIDTH + fW;
			}
		}

		SDL_RenderClear(ren);

		for (i = 0; i < WINDOW_WIDTH / bW; i++) {
			for (j = 0; j <= WINDOW_HEIGHT / bH; j++) {
				renderTextureS(bg, ren, i * bW, j * bH, bW, bH);
			}
		}

		renderTexture(fg, ren, x, y);
		SDL_RenderPresent(ren);
	}

	SDL_DestroyTexture(bg);
	SDL_DestroyTexture(fg);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);

	IMG_Quit();
	SDL_Quit();

	return 0;
}
