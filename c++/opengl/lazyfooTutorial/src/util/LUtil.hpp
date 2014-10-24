#ifndef LUTIL_H
#define LUTIL_H

#include "../ogl/LOpenGL.hpp"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;
const int SCREEN_POSITION[] = {200, 50};
const char *const SCREEN_TITLE = "Generic Title";

bool initGL(void);
bool loadMedia(void);
void update(void);
void render(void);
void handleKeys(unsigned char key, int x, int y);

void gDrawQuad(GLfloat x, GLfloat y, GLfloat sizeX, GLfloat sizeY, GLfloat R, GLfloat G, GLfloat B, GLfloat A = 1.0f);

#endif
