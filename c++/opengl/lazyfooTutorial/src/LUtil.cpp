#include "LUtil.hpp"
#include "LTexture.hpp"
//#include <stdbool.h>

int gColorMode = COLOR_MODE_MONO;

GLfloat gCameraX = 0.0f, gCameraY = 0.0f;
LTexture gCheckerBoardTexture;

bool initGL(void) {
	glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 1.0f, -1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_TEXTURE_2D);

	GLenum error = glGetError();

	if (error != GL_NO_ERROR) {
		fprintf(stderr, "Error initializing OpenGL!\n%s\n", gluErrorString(error));
		return false;
	}

	return true;
}

bool loadMedia(void) {
	const int CHECHERBOARD_WIDTH = 128;
	const int CHECKERBOARD_HEIGHT = 128;
	const int CHECKERBOARD_PIXEL_COUNT = CHECHERBOARD_WIDTH * CHECKERBOARD_HEIGHT;

	GLuint checkerboard[CHECKERBOARD_PIXEL_COUNT];

	for (int i = 0; i < CHECKERBOARD_PIXEL_COUNT; ++i) {
		GLubyte *colors = (GLubyte*)&checkerboard[i];

		if (i / 128 & 16 ^ i % 128 & 16) {
			colors[0] = 0xFF;
			colors[1] = 0xFF;
			colors[2] = 0xFF;
			colors[3] = 0xAA;
		} else {
			colors[0] = 0xFF;
			colors[1] = 0x00;
			colors[2] = 0xFF;
			colors[3] = 0xFF;
		}
	}

	if (!gCheckerBoardTexture.loadTextureFromPixels32(checkerboard, CHECHERBOARD_WIDTH, CHECKERBOARD_HEIGHT)) {
		fprintf(stderr, "Unable to load checkerboard texture!\n");
		return false;
	}

	return true;
}

void update(void) {
}

void render(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	glPopMatrix();
	glPushMatrix();

	glTranslatef(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f);
	gDrawQuad(SCREEN_WIDTH / 4.0f, SCREEN_HEIGHT / 4.0f, 1.0f, 0.0f, 0.0f);

	glTranslatef(SCREEN_WIDTH, 0.0f, 0.0f);
	gDrawQuad(SCREEN_WIDTH / 4.0f, SCREEN_HEIGHT / 4.0f, 0.0f, 1.0f, 0.0f);

	glTranslatef(0.0f, SCREEN_HEIGHT, 0.0f);
	gDrawQuad(SCREEN_WIDTH / 4.0f, SCREEN_HEIGHT / 4.0f, 0.0f, 0.0f, 1.0f);

	glTranslatef(-SCREEN_WIDTH, 0.0f, 0.0f);
	gDrawQuad(SCREEN_WIDTH / 4.0f, SCREEN_HEIGHT / 4.0f, 1.0f, 0.0f, 1.0f);

	glutSwapBuffers();
}

void handleKeys(unsigned char key, int x, int y) {
	if (key == 'q') {
		if (gColorMode == COLOR_MODE_MONO) {
			gColorMode = COLOR_MODE_MULTI;
		} else if (gColorMode == COLOR_MODE_MULTI) {
			gColorMode = COLOR_MODE_TEXTURE;
		} else if (gColorMode == COLOR_MODE_TEXTURE) {
			gColorMode = COLOR_MODE_MONO;
		}
	}

	/*if (key == 'e') {
		gViewPortMode++;
		if (gViewPortMode > VIEWPORT_MODE_RADAR) {
			gViewPortMode = VIEWPORT_MODE_FULL;
		}
	}*/

	if (key == 'w') {
		gCameraY -= 16.0f;
	}

	if (key == 'a') {
		gCameraX -= 16.0f;
	}

	if (key == 's') {
		gCameraY += 16.0f;
	}

	if (key == 'd') {
		gCameraX += 16.0f;
	}

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glLoadIdentity();

	glTranslatef(-gCameraX, -gCameraY, 0.0f);

	glPushMatrix();
}

void gDrawQuad(GLfloat sizeX, GLfloat sizeY, GLfloat R, GLfloat G, GLfloat B) {
		if (gColorMode == COLOR_MODE_MONO) {
			glBegin(GL_QUADS);
				glColor3f(R, G, B);
				glVertex2f(-sizeX, -sizeY);
				glVertex2f(sizeX, -sizeY);
				glVertex2f(sizeX, sizeY);
				glVertex2f(-sizeX, sizeY);
			glEnd();
		} else if (gColorMode == COLOR_MODE_MULTI) {
			glBegin(GL_QUADS);
				glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(-sizeX, -sizeY);
				glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(sizeX, -sizeY);
				glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(sizeX, sizeY);
				glColor3f(1.0f, 1.0f, 0.0f); glVertex2f(-sizeX, sizeY);
			glEnd();
		} else if (gColorMode == COLOR_MODE_TEXTURE) {
			GLfloat x = (sizeX - gCheckerBoardTexture.textureWidth()) / 2.0f;
			GLfloat y = (sizeY - gCheckerBoardTexture.textureHeight()) / 2.0f;

			gCheckerBoardTexture.render(x, y);
		}
}
