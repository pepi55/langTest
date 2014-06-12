#pragma once

#define SDL_FUNC_H

#include <stdbool.h>
#include <SDL2/SDL.h>

#define WINDOW_NAME "Generic Title"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

Uint16 makeHiColorPixel(SDL_PixelFormat *fmt, Uint8 red, Uint8 green, Uint8 blue);

void sdlInit(SDL_Window *screen);
void sdlExit(SDL_Window *screen, /*SDL_Renderer *renderer, */SDL_GLContext glContext);
void sdlLogError(char *error);

SDL_Window *screen;
//SDL_Renderer *renderer;
SDL_GLContext glContext;
