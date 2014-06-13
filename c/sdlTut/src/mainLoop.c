#include <stdio.h>
#include <GL/glut.h>

#include "mainLoop.h"
#include "sdlFunc.h"
#include "openglFunc.h"

void mainLoop (void) {
	bool exitProgram = 0;
	const Uint8 *kbState = SDL_GetKeyboardState(NULL);
	GLfloat rotation_y = 0, rotation_x = 0;

	SDL_Event event;

	while (!exitProgram) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) exitProgram = 1;
			if (event.type == SDL_MOUSEBUTTONDOWN) exitProgram = 1;
		}

		if (kbState[SDL_SCANCODE_W] || kbState[SDL_SCANCODE_UP]) {
			rotation_x += 0.5;
		}

		if (kbState[SDL_SCANCODE_S] || kbState[SDL_SCANCODE_DOWN]) {
			rotation_x -= 0.5;
		}

		if (kbState[SDL_SCANCODE_A] || kbState[SDL_SCANCODE_LEFT]) {
			rotation_y += 0.5;
		}

		if (kbState[SDL_SCANCODE_D] || kbState[SDL_SCANCODE_RIGHT]) {
			rotation_y -= 0.5;
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(rotation_x * 0.1, rotation_y * 0.1, rotation_x * 0.2, rotation_y * 0.2);

		createCube(0.5, rotation_x, rotation_y);

		SDL_GL_SwapWindow(screen);
	}
}
