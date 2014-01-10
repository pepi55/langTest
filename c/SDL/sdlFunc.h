#ifndef SDL_FUNC_H
#define SDL_FUNC_H

#include <SDL2/SDL.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 460
#define WINDOW_OFFSET_X 200
#define WINDOW_OFFSET_Y 150
#define WINDOW_LIFETIME 2000

#define TILE_SIZE 40

void logSDLError(char *err);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
void renderTextureS(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);

SDL_Texture *loadBmp(char *loc, SDL_Renderer *ren);
SDL_Texture *loadTexture(char *loc, SDL_Renderer *ren);

#endif
