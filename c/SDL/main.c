#include <stdio.h>
#include <SDL2/SDL.h>

#define WINDOW_HEIGHT 200
#define WINDOW_WIDTH 200
#define WINDOW_OFFSET_X 150
#define WINDOW_OFFSET_Y 150

int main (int argv, char **argc) {
	SDL_Window *win;
	SDL_Renderer *ren;
	SDL_Surface *bmp;
	SDL_Texture *tex;

	SDL_Init(SDL_INIT_VIDEO);
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "\nSDL_Init Error: %s\n", SDL_GetError());
		return 1;
	}

	win = SDL_CreateWindow("Hello World!", WINDOW_OFFSET_X, WINDOW_OFFSET_Y, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (win == NULL) {
		fprintf(stderr, "\nSDL_CreateWindow Error: %s\n", SDL_GetError());
		return 1;
	}

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == NULL) {
		fprintf(stderr, "\nSDL_CreateRenderer Error: %s\n", SDL_GetError());
		return 1;
	}

	bmp = SDL_LoadBMP("../SDL/bitmap/bmp.bmp");
	if (bmp == NULL) {
		fprintf(stderr, "\nSDL_LoadBMP Error: %s\n", SDL_GetError());
		return 1;
	}

	tex = SDL_CreateTextureFromSurface(ren, bmp);
	SDL_FreeSurface(bmp);
	if (tex == NULL) {
		fprintf(stderr, "\nSDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
		return 1;
	}

	SDL_RenderClear(ren);
	SDL_RenderCopy(ren, tex, NULL, NULL);
	SDL_RenderPresent(ren);

	SDL_Delay(2000);

	SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();

	return 0;
}
