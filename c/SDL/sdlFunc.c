#include <stdio.h>
#include <SDL2/SDL_image.h>

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

void renderTextureS(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h) {
	SDL_Rect canv;
	SDL_QueryTexture(tex, NULL, NULL, &canv.w, &canv.h);

	canv.x = x;
	canv.y = y;
	canv.w = w;
	canv.h = h;

	SDL_RenderCopy(ren, tex, NULL, &canv);
}

void renderSprite(SDL_Texture *tex, SDL_Renderer *ren, int y, int x, SDL_Rect *clip) {
	SDL_Rect dst;

	dst.x = x;
	dst.y = y;

	if (clip != NULL) {
		dst.w = clip->w;
		dst.h = clip->h;
	} else {
		SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	}

	SDL_RenderCopy(ren, tex, clip, &dst);
}

SDL_Texture *loadBmp(char *loc, SDL_Renderer *ren) {
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

SDL_Texture *loadTexture(char *loc, SDL_Renderer *ren) {
	SDL_Texture *tex = IMG_LoadTexture(ren, loc);
	if (tex == NULL) logSDLError("LoadTexture");

	return tex;
}
