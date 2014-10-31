#include "LUtilSDL.hpp"

SDL_Window *gWindow;
SDL_Surface *gScreenSurface;

SDL_Surface *gCurrentSurface;

bool initSDL(void) {
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Could not initialize SDL!\nSDL_Error: %s\n", SDL_GetError());
		success = false;
	} else {
		gWindow = SDL_CreateWindow(SCREEN_TITLE, SCREEN_POS_X, SCREEN_POS_Y, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (gWindow == NULL) {
			fprintf(stderr, "Window could not be created!\nSDL_Error: %s\n", SDL_GetError());
			success = false;
		} else {
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}

	return success;
}

bool loadMedia(void) {
	bool success = true;

	gCurrentSurface = loadSurface("img/stretch.bmp");
	if (gCurrentSurface == NULL) {
		fprintf(stderr, "Failed to load stretch bmp!\n");
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
			}

			render();
		}
	}
}

void render(void) {
	SDL_Rect stretchRect;
	stretchRect.x = 0; stretchRect.y = 0;
	stretchRect.w = SCREEN_WIDTH; stretchRect.h = SCREEN_HEIGHT;
	SDL_BlitScaled(gCurrentSurface, NULL, gScreenSurface, &stretchRect);

	SDL_UpdateWindowSurface(gWindow);
}

void closeSDL(void) {
	SDL_FreeSurface(gCurrentSurface);
	gCurrentSurface = NULL;

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	SDL_Quit();
}

SDL_Surface *loadSurface(std::string path) {
	SDL_Surface *loadedSurface = SDL_LoadBMP(path.c_str());
	SDL_Surface *optimizedSurface = NULL;

	if (loadedSurface == NULL) {
		fprintf(stderr, "Unable to load image %s!\nSDL_Error: %s\n", path.c_str(), SDL_GetError());
	} else {
		optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0x0);

		if (optimizedSurface == NULL) {
			fprintf(stderr, "Unable to optimize image %s!\nSDL_Error: %s\n", path.c_str(), SDL_GetError());

			SDL_FreeSurface(loadedSurface);
		}
	}

	return optimizedSurface;
}
