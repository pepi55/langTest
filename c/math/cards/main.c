#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "sdlFunc.h"
#include "cards.xpm"
#include "bmp.xpm"

#define SPRITES_ON_ROW 13 //Amount of sprites on a single row
#define SPRITES_ON_COLUMN 4 //Amount of sprites on a single column
#define CLIPS_AMOUNT 52 //Amount of total sprites on a sheet

#define WINDOW_WIDTH 640 //Window height & width
#define WINDOW_HEIGHT 460

#define WINDOW_OFFSET_X 200 //Position of window on screen
#define WINDOW_OFFSET_Y 150


int main (void) {
	int x, y, i, j, tW, tH, bW, bH, sW, sH;
	bool quit = 0;

	x = 0; y = 0;

	SDL_Window *win = NULL;
	SDL_Renderer *ren = NULL;
	SDL_Texture *bg = NULL;
	SDL_Texture *fg = NULL;

	SDL_Event e;
	SDL_Rect clips[CLIPS_AMOUNT];

	if (SDL_Init(SDL_INIT_VIDEO) != 0 || (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		logSDLError("Init");
		return 1;
	}

	win = SDL_CreateWindow("Cards", WINDOW_OFFSET_X, WINDOW_OFFSET_Y, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (win == NULL) {
		logSDLError("CreateWindow");
		return 2;
	}

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == NULL) {
		logSDLError("CreateRenderer");
		return 3;
	}

	//Load bg, fg and other textures below
	bg = loadHeader(bmp_xpm, ren);
	fg = loadHeader(cards_xpm, ren);
	if (bg == NULL || fg == NULL) {
		logSDLError("loadTexture");
		return 4;
	}

	SDL_RenderClear(ren);

	//Query size values of textures
	SDL_QueryTexture(bg, NULL, NULL, &bW, &bH);
	SDL_QueryTexture(fg, NULL, NULL, &sW, &sH);

	tW = sW / SPRITES_ON_ROW;
	tH = sH / SPRITES_ON_COLUMN;

	//Tiled background
	for (i = 0; i < WINDOW_WIDTH / bW; i++) {
		for (j = 0; j <= WINDOW_HEIGHT / bH; j++) {
			renderTextureS(bg, ren, i * bW, j * bH, bW, bH);
		}
	}

	//Define "places" on the sprite sheet per sprite
	for (i = 0; i < CLIPS_AMOUNT; i++) {
		clips[i].x = i % SPRITES_ON_ROW * tW;
		clips[i].y = floor(i / SPRITES_ON_ROW) * tH;

		clips[i].w = tW;
		clips[i].h = tH;
	}

	SDL_RenderPresent(ren);

	while (!quit) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) quit = 1;
			//if (e.type == SDL_MOUSEBUTTONDOWN) quit = 1;
		}

		SDL_RenderClear(ren);

		//Render background durning game
		for (i = 0; i < WINDOW_WIDTH / bW; i++) {
			for (j = 0; j <= WINDOW_HEIGHT / bH; j++) {
				renderTextureS(bg, ren, i * bW, j * bH, bW, bH);
			}
		}

		for (i = 0; i < CLIPS_AMOUNT; i++) {
			renderSprite(fg, ren, x, y * i, &clips[i]);
		}

		SDL_RenderPresent(ren);
	}

	SDL_DestroyTexture(bg);
	SDL_DestroyTexture(fg);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);

	cleanUp();

	return 0;
}
