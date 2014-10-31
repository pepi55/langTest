#include "LUtilSDL.hpp"
#include "../sdl/LTextureSDL.hpp"

SDL_Window *gWindow;
SDL_Renderer *gRenderer;
SDL_Surface *gScreenSurface;

SDL_Rect gSpriteClips[4];

LTextureSDL gTexture;

Uint8 r = 255,
			g = 255,
			b = 255;

bool initSDL(void) {
	bool success = true;
	int sdlFlags = SDL_INIT_VIDEO;

	if (SDL_Init(sdlFlags) < 0) {
		fprintf(stderr, "Could not initialize SDL!\nSDL_Error: %s\n", SDL_GetError());
		success = false;
	} else {
		gWindow = SDL_CreateWindow(SCREEN_TITLE, SCREEN_POS_X, SCREEN_POS_Y, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (gWindow == NULL) {
			fprintf(stderr, "Window could not be created!\nSDL_Error: %s\n", SDL_GetError());
			success = false;
		} else {
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

			if (gRenderer == NULL) {
				fprintf(stderr, "Count not create renderer!\nSDL_Error: %s\n", SDL_GetError());
				success = false;
			} else {
				int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;

				if (!(IMG_Init(imgFlags)) & imgFlags) {
					fprintf(stderr, "SDL_image could not be initialized!\nSDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia(void) {
	bool success = true;

	if (!gTexture.loadFromFile(gRenderer, "img/full.png")) {
		fprintf(stderr, "Unable to load texture!\n");
		success = false;
	}

	return success;
}

void mainLoop(void) {
	bool quit = false;
	SDL_Event e;

	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			} else if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
					case SDLK_q:
						r += 32;
						break;

					case SDLK_w:
						g += 32;
						break;

					case SDLK_e:
						b += 32;
						break;

					case SDLK_a:
						r -= 32;
						break;

					case SDLK_s:
						g -= 32;
						break;

					case SDLK_d:
						b -= 32;
						break;

					default:
						break;
				}
			}

			render();
		}
	}
}

void render(void) {
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);

	gTexture.setColor(r, g, b);
	gTexture.render(gRenderer, 0, 0);

	SDL_RenderPresent(gRenderer);
}

void closeSDL(void) {
	gTexture.free();

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gRenderer = NULL;
	gWindow = NULL;

	IMG_Quit();
	SDL_Quit();
}
