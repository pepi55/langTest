#ifndef LUTIL_H
#define LUTIL_H

#include "LOpenGL.hpp"
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;

const int COLOR_MODE_CYAN = 0;
const int COLOR_MODE_MULTI = 1;

bool initGL(void);
void update(void);
void render(void);
void handleKeys(unsigned char key, int x, int y);

#endif
