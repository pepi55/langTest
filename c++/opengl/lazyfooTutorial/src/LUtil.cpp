#include "LUtil.hpp"
#include <stdbool.h>

int gColorMode = COLOR_MODE_MONO;
int gViewPortMode = VIEWPORT_MODE_FULL;

GLfloat gCameraX = 0.0f, gCameraY = 0.0f;
GLfloat gProjectionScale = 1.0f;

bool initGL(void) {
	glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 1.0f, -1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	GLenum error = glGetError();

	if (error != GL_NO_ERROR) {
		fprintf(stderr, "Error initializing OpenGL!\n%s\n", gluErrorString(error));
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

	glutSwapBuffers();
}

void handleKeys(unsigned char key, int x, int y) {
	if (key == 'q') {
		if (gColorMode == COLOR_MODE_MONO) {
			gColorMode = COLOR_MODE_MULTI;
		} else {
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

void drawQuad(GLfloat sizeX, GLfloat sizeY, GLfloat R, GLfloat G, GLfloat B) {
		if (gColorMode == COLOR_MODE_MONO) {
			glBegin(GL_QUADS);
				glColor3f(R, G, B);
				glVertex2f(-sizeX, -sizeY);
				glVertex2f(sizeX, -sizeY);
				glVertex2f(sizeX, sizeY);
				glVertex2f(-sizeX, sizeY);
			glEnd();
		} else {
			glBegin(GL_QUADS);
				glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(-sizeX, -sizeY);
				glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(sizeX, -sizeY);
				glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(sizeX, sizeY);
				glColor3f(1.0f, 1.0f, 0.0f); glVertex2f(-sizeX, sizeY);
			glEnd();
		}
}
