#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "sdlFunc.h"

int main (void) { //int argv, char **argc
	int i, j, bW, bH, fW, fH;

	SDL_Window *win;
	SDL_Renderer *ren;
	SDL_Texture *bg;
	SDL_Texture *fg;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
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
	fg = loadTexture("../SDL/bitmap/bmp2.bmp", ren);
	if (bg == NULL || fg == NULL) {
		logSDLError("loadTexture");
		return 4;
	}

	SDL_RenderClear(ren);

	SDL_QueryTexture(bg, NULL, NULL, &bW, &bH);
	for (i = 0; i < WINDOW_WIDTH / bW; i++) {
		for (j = 0; j <= WINDOW_HEIGHT / bH; j++) {
			renderTexture(bg, ren, i * bW, j * bH);
		}
	}

	SDL_QueryTexture(fg, NULL, NULL, &fW, &fH);
	renderTextureS(fg, ren, WINDOW_WIDTH / 2 - (fW / 2) / 2, WINDOW_HEIGHT / 2 - (fH / 2) / 2, fW / 2, fH / 2);

	SDL_RenderPresent(ren);

	SDL_Delay(WINDOW_LIFETIME);

	SDL_DestroyTexture(bg);
	SDL_DestroyTexture(fg);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();

	return 0;
}
