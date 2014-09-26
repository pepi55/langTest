#include "LUtil.hpp"
#include <stdbool.h>

int gColorMode = COLOR_MODE_MONO;
int gViewPortMode = VIEWPORT_MODE_FULL;

GLfloat gProjectionScale = 1.0f;

bool initGL(void) {
	glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 1.0f, -1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

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

	//glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f);

	if (gViewPortMode == VIEWPORT_MODE_FULL) {
		glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);

		drawQuad(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 1.0f, 0.0f, 0.0f);
	} else if (gViewPortMode == VIEWPORT_MODE_HALF_CENTER) {
		glViewport(SCREEN_WIDTH / 4.0f, SCREEN_HEIGHT / 4.0f, SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);

		drawQuad(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f, 1.0f, 1.0f);
	} else if (gViewPortMode == VIEWPORT_MODE_HALF_TOP) {
		glViewport(SCREEN_WIDTH / 4.0f, SCREEN_HEIGHT / 2.0f, SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);

		drawQuad(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f, 1.0f, 0.0f);
	} else if (gViewPortMode == VIEWPORT_MODE_QUAD) {
		//Bottom left
		glViewport(0.0f, 0.0f, SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);

		drawQuad(SCREEN_WIDTH / 4.0f, SCREEN_HEIGHT / 4.0f, 1.0f, 1.0f, 0.0f);

		//Bottom right
		glViewport(SCREEN_WIDTH / 2.0f, 0.0f, SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);

		drawQuad(SCREEN_WIDTH / 4.0f, SCREEN_HEIGHT / 4.0f, 0.0f, 1.0f, 1.0f);

		//Top left
		glViewport(0.0f, SCREEN_HEIGHT / 2.0f, SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);

		drawQuad(SCREEN_WIDTH / 4.0f, SCREEN_HEIGHT / 4.0f, 1.0f, 0.0f, 1.0f);

		//Top right
		glViewport(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);

		drawQuad(SCREEN_WIDTH / 4.0f, SCREEN_HEIGHT / 4.0f, 0.0f, 0.0f, 1.0f);
	} else if (gViewPortMode == VIEWPORT_MODE_RADAR) {
		//Full size quad
		glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);

		drawQuad(SCREEN_WIDTH / 8.0f, SCREEN_HEIGHT / 8.0f, 1.0f, 1.0f, 1.0f);
		drawQuad(SCREEN_WIDTH / 16.0f, SCREEN_HEIGHT / 16.0f, 0.0f, 1.0f, 1.0f);
	} else if (gViewPortMode == VIEWPORT_MODE_RADAR) {
		glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
		glBegin(GL_QUADS);
			glColor3f(1.0f, 1.0f, 0.0f);
			glVertex2f(-SCREEN_WIDTH / 8.0f, -SCREEN_HEIGHT / 8.0f);
			glVertex2f(SCREEN_WIDTH / 8.0f, -SCREEN_HEIGHT / 8.0f);
			glVertex2f(SCREEN_WIDTH / 8.0f, SCREEN_HEIGHT / 8.0f);
			glVertex2f(-SCREEN_WIDTH / 8.0f, SCREEN_HEIGHT / 8.0f);

			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex2f(-SCREEN_WIDTH / 16.0f, -SCREEN_HEIGHT / 16.0f);
			glVertex2f(SCREEN_WIDTH / 16.0f, -SCREEN_HEIGHT / 16.0f);
			glVertex2f(SCREEN_WIDTH / 16.0f, SCREEN_HEIGHT / 16.0f);
			glVertex2f(-SCREEN_WIDTH / 16.0f, SCREEN_HEIGHT / 16.0f);
		glEnd();

		glViewport(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);
		glBegin(GL_QUADS);
			glColor3f(1.0f, 1.0f, 1.0f);
			glVertex2f(-SCREEN_WIDTH / 8.0f, -SCREEN_HEIGHT / 8.0f);
			glVertex2f(SCREEN_WIDTH / 8.0f, -SCREEN_HEIGHT / 8.0f);
			glVertex2f(SCREEN_WIDTH / 8.0f, SCREEN_HEIGHT / 8.0f);
			glVertex2f(-SCREEN_WIDTH / 8.0f, SCREEN_HEIGHT / 8.0f);

			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex2f(-SCREEN_WIDTH / 16.0f, -SCREEN_HEIGHT / 16.0f);
			glVertex2f(SCREEN_WIDTH / 16.0f, -SCREEN_HEIGHT / 16.0f);
			glVertex2f(SCREEN_WIDTH / 16.0f, SCREEN_HEIGHT / 16.0f);
			glVertex2f(-SCREEN_WIDTH / 16.0f, SCREEN_HEIGHT / 16.0f);
		glEnd();
	}

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

	if (key == 'w') {
		gViewPortMode++;

		if (gViewPortMode > VIEWPORT_MODE_RADAR) {
			gViewPortMode = VIEWPORT_MODE_FULL;
		}
	}
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
