#include "LUtilSDL.hpp"

enum KeyPressSurfaces {
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

SDL_Window *gWindow;
SDL_Surface *gScreenSurface;

SDL_Surface *gKeyPressSurface[KEY_PRESS_SURFACE_TOTAL];
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

	gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("img/keys/press.bmp");
	if (gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
		fprintf(stderr, "Failed to load default image!\n");
		success = false;
	}

	gKeyPressSurface[KEY_PRESS_SURFACE_UP] = loadSurface("img/keys/up.bmp");
	if (gKeyPressSurface[KEY_PRESS_SURFACE_UP] == NULL) {
		fprintf(stderr, "Failed to load up image!\n");
		success = false;
	}

	gKeyPressSurface[KEY_PRESS_SURFACE_DOWN] = loadSurface("img/keys/down.bmp");
	if (gKeyPressSurface[KEY_PRESS_SURFACE_DOWN] == NULL) {
		fprintf(stderr, "Failed to load down image!\n");
		success = false;
	}

	gKeyPressSurface[KEY_PRESS_SURFACE_LEFT] = loadSurface("img/keys/left.bmp");
	if (gKeyPressSurface[KEY_PRESS_SURFACE_LEFT] == NULL) {
		fprintf(stderr, "Failed to load left image!\n");
		success = false;
	}

	gKeyPressSurface[KEY_PRESS_SURFACE_RIGHT] = loadSurface("img/keys/right.bmp");
	if (gKeyPressSurface[KEY_PRESS_SURFACE_RIGHT] == NULL) {
		fprintf(stderr, "Failed to load right image!\n");
		success = false;
	}

	return success;
}

void mainLoop(void) {
	bool quit = false;
	SDL_Event e;

	gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT];

	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			} else if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
					case SDLK_UP:
						gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_UP];
						break;

					case SDLK_DOWN:
						gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_DOWN];
						break;

					case SDLK_LEFT:
						gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_LEFT];
						break;

					case SDLK_RIGHT:
						gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_RIGHT];
						break;

					default:
						gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT];
						break;
				}
			}

			render();
		}
	}
}

void render(void) {
	SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);

	SDL_UpdateWindowSurface(gWindow);
}

void closeSDL(void) {
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	SDL_Quit();
}

SDL_Surface *loadSurface(std::string path) {
	SDL_Surface *loadedSurface = SDL_LoadBMP(path.c_str());

	if (loadedSurface == NULL) {
		fprintf(stderr, "Unable to load image %s!\nSDL_Error: %s\n", path.c_str(), SDL_GetError());
	}

	return loadedSurface;
}
