#include <stdio.h>
#include <GL/glut.h>

#include "mainLoop.h"
#include "sdlFunc.h"
#include "openglFunc.h"

void mainLoop (void) {
	bool exitProgram;
	float rotation_y = 0, rotation_x = 0;

	SDL_Event event;

	while (!exitProgram) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) exitProgram = 1;
			if (event.type == SDL_MOUSEBUTTONDOWN) exitProgram = 1;
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		rotation_x++; rotation_y++;

		createCube(0.5, rotation_x, rotation_y);

		SDL_GL_SwapWindow(screen);
	}
}
