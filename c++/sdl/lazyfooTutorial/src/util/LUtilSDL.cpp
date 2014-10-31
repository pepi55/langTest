#include "LUtilSDL.hpp"
#include "../sdl/LTextureSDL.hpp"

SDL_Window *gWindow;
SDL_Renderer *gRenderer;
SDL_Surface *gScreenSurface;

SDL_Rect gSpriteClips[4];

LTextureSDL gFooTexture;
LTextureSDL gBackground;
LTextureSDL gSpriteSheetTexture;

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

	if (!gFooTexture.loadFromFile(gRenderer, "img/huisjeBoompjeBeesj/foo.png")) {
		fprintf(stderr, "Unable to load texture!\n");
		success = false;
	}

	if (!gBackground.loadFromFile(gRenderer, "img/huisjeBoompjeBeesj/background.png")) {
		fprintf(stderr, "Unable to load texture!\n");
		success = false;
	}

	if (!gSpriteSheetTexture.loadFromFile(gRenderer, "img/sprites.png")) {
		fprintf(stderr, "Unable to load texture!\n");
		success = false;
	} else {
		//topleft
		gSpriteClips[0].x = 0;
		gSpriteClips[0].y = 0;
		gSpriteClips[0].w = 100;
		gSpriteClips[0].h = 100;

		//topright
		gSpriteClips[1].x = 100;
		gSpriteClips[1].y = 0;
		gSpriteClips[1].w = 100;
		gSpriteClips[1].h = 100;

		//botleft
		gSpriteClips[2].x = 0;
		gSpriteClips[2].y = 100;
		gSpriteClips[2].w = 100;
		gSpriteClips[2].h = 100;

		//botright
		gSpriteClips[3].x = 100;
		gSpriteClips[3].y = 100;
		gSpriteClips[3].w = 100;
		gSpriteClips[3].h = 100;
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
			}

			render();
		}
	}
}

void render(void) {
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);

	gBackground.render(gRenderer, 0, 0);
	gFooTexture.render(gRenderer, 240, 190);

	gSpriteSheetTexture.render(gRenderer, 0, 0, &gSpriteClips[0]);
	gSpriteSheetTexture.render(gRenderer, SCREEN_WIDTH - gSpriteClips[1].w, 0, &gSpriteClips[1]);
	gSpriteSheetTexture.render(gRenderer, 0, SCREEN_HEIGHT - gSpriteClips[2].h, &gSpriteClips[2]);
	gSpriteSheetTexture.render(gRenderer, SCREEN_WIDTH - gSpriteClips[3].w, SCREEN_HEIGHT - gSpriteClips[3].h, &gSpriteClips[3]);

	SDL_RenderPresent(gRenderer);
}

void closeSDL(void) {
	gFooTexture.free();
	gBackground.free();

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gRenderer = NULL;
	gWindow = NULL;

	IMG_Quit();
	SDL_Quit();
}
