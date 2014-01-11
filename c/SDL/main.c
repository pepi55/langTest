#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keycode.h>

#include "sdlFunc.h"

int main (void) { //int argv, char **argc
	int x, y, i, j, bW, bH, fW, fH, sW, sH;
	int curClip = 0;
	bool quit = 0;

	SDL_Event e;
	SDL_Window *win;
	SDL_Renderer *ren;
	SDL_Texture *bg;
	SDL_Texture *fg;
	SDL_Rect clips[CLIPS_AMOUNT];

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

	bg = loadBmp("../SDL/pic/bmp.bmp", ren);
	fg = loadTexture("../SDL/sprites/sprite.png", ren);
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

	fW = 95;
	fH = 95;
	x = WINDOW_WIDTH / 2 - fW / 2;
	y = WINDOW_WIDTH / 2 - fH / 2;

	for (i = 0; i < CLIPS_AMOUNT; i++) {
		clips[i].x = i / 2 * fW;
		clips[i].y = i % 2 * fH;

		clips[i].w = fW;
		clips[i].h = fH;
	}

	SDL_QueryTexture(fg, NULL, NULL, &sW, &sH);
	renderTexture(fg, ren, x, y);

	SDL_RenderPresent(ren);

	while (!quit) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) quit = 1;
			//if (e.type == SDL_MOUSEBUTTONDOWN) quit = 1;
		}

		if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
				case SDLK_UP:
					x -= 5;
					curClip = 3;
					break;
				case SDLK_DOWN:
					x += 5;
					curClip = 1;
					break;
				case SDLK_LEFT:
					y -= 5;
					curClip = 0;
					break;
				case SDLK_RIGHT:
					y += 5;
					curClip = 2;
					break;
				default:
					break;
			}

			if (x < -sW) {
				x = WINDOW_WIDTH + sW;
			} else if (y < -sH) {
				y = WINDOW_HEIGHT + sH;
			} else if (x > WINDOW_WIDTH + sW) {
				x = 0 - sW;
			} else if (y > WINDOW_HEIGHT + sH) {
				y = 0 - sH;
			}
		}

		SDL_RenderClear(ren);

		for (i = 0; i < WINDOW_WIDTH / bW; i++) {
			for (j = 0; j <= WINDOW_HEIGHT / bH; j++) {
				renderTextureS(bg, ren, i * bW, j * bH, bW, bH);
			}
		}

		renderSprite(fg, ren, x, y, &clips[curClip]);
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
