#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keycode.h>

#include "sdlFunc.h"
#include "sprite.xpm"
#include "bmp.xpm"

#define CLIPS_AMOUNT 4

int main (void) { //int argv, char **argc
	int x, y, i, j, bW, bH, fW, fH, sW, sH;
	int curClip = 0;
	bool quit = 0;
	const Uint8 *kbState = SDL_GetKeyboardState(NULL);
	char **imgFromSrc;

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

	imgFromSrc = bmp_xpm;
	bg = loadHeader(imgFromSrc, ren);

	imgFromSrc = sprite_xpm;
	fg = loadHeader(imgFromSrc, ren);
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

		if (kbState[SDL_SCANCODE_W] || kbState[SDL_SCANCODE_UP]) {
			x -= 5; curClip = 3;
			if (x < -sW) x = WINDOW_WIDTH - sW;
		}
		
		if (kbState[SDL_SCANCODE_A] || kbState[SDL_SCANCODE_LEFT]) {
			y -= 5; curClip = 0;
			if (y < -sH) y = WINDOW_HEIGHT + sH;
		}
		
		if (kbState[SDL_SCANCODE_S] || kbState[SDL_SCANCODE_DOWN]) {
			x += 5; curClip = 1;
			if (x > WINDOW_WIDTH - sW) x = 0 -sW;
		}
		
		if (kbState[SDL_SCANCODE_D] || kbState[SDL_SCANCODE_RIGHT]) {
			y += 5; curClip = 2;
			if (y > WINDOW_HEIGHT + sH) y = 0 -sH;
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
