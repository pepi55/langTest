#include <stdio.h>

#include "sdlFunc.h"

void logSDLError(char *err) {
	fprintf(stderr, "\nError: %s, at %s\n", SDL_GetError(), err);
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y) {
	SDL_Rect canv;

	canv.x = x;
	canv.y = y;

	SDL_QueryTexture(tex, NULL, NULL, &canv.w, &canv.h);
	SDL_RenderCopy(ren, tex, NULL, &canv);
}

SDL_Texture *loadTexture(char *loc, SDL_Renderer *ren) {
	SDL_Texture *tex = NULL;
	SDL_Surface *loadedImg = SDL_LoadBMP(loc);

	if (loadedImg != NULL) {
		tex = SDL_CreateTextureFromSurface(ren, loadedImg);
		SDL_FreeSurface(loadedImg);

		if (tex == NULL) logSDLError("CreateTextureFromSurface");
	} else {
		logSDLError("LoadBMP");
	}

	return tex;
}
