#ifndef LUTIL_H
#define LUTIL_H

#include "LOpenGL.hpp"
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;
const char *const SCREEN_TITLE = "Generic Title";

const int COLOR_MODE_MONO = 0;
const int COLOR_MODE_MULTI = 1;

enum ViewPortMode {
	VIEWPORT_MODE_FULL,
	VIEWPORT_MODE_HALF_CENTER,
	VIEWPORT_MODE_HALF_TOP,
	VIEWPORT_MODE_QUAD,
	VIEWPORT_MODE_RADAR
};

bool initGL(void);
void update(void);
void render(void);
void handleKeys(unsigned char key, int x, int y);

void drawQuad(GLfloat sizeX, GLfloat sizeY, GLfloat R, GLfloat G, GLfloat B);

#endif
