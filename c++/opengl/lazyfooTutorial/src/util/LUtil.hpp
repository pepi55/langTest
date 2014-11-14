#ifndef LUTIL_H
#define LUTIL_H

#include "../ogl/LOpenGL.hpp"
#include "../font/LFont.hpp"
#include "../tex/LTexture.hpp"
#include "../tex/LSpriteSheet.hpp"
#include "../shader/LShaderProgram.hpp"
#include "../prim/LPlainPolygonProgram2D.hpp"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;
const int SCREEN_POSITION[] = {200, 60};
const char *const SCREEN_TITLE = "Generic Title";

bool initGL(void);
bool loadGP(void);
bool loadMedia(void);
void update(void);
void render(void);
void renderScene(void);
void handleKeys(unsigned char key, int x, int y);
void handleMouseMotion(int x, int y);

void gDrawQuads(GLfloat x, GLfloat y, GLfloat r = 1.0f, GLfloat g = 1.0f, GLfloat b = 1.0f);

#endif
