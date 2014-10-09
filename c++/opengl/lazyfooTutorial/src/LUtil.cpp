#include <IL/il.h>
#include <IL/ilu.h>

#include "LUtil.hpp"
#include "LTexture.hpp"

int gColorMode = COLOR_MODE_MONO;
int gTransformationCombo = 0;

GLfloat gAngle = 0.0f;
GLfloat gCameraX = 0.0f,
				gCameraY = 0.0f;

LTexture gTexture;
GLenum gFiltering = GL_LINEAR;

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
	glEnable(GL_BLEND);

	glDisable(GL_DEPTH_TEST);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		fprintf(stderr, "Error initializing OpenGL!\n%s\n", gluErrorString(error));
		return false;
	}

	ilInit();
	iluInit();
	ilClearColor(255, 255, 255, 000);

	ILenum ilError = ilGetError();
	if (ilError != IL_NO_ERROR) {
		fprintf(stderr, "Unable to initialize DevIL!\n%s\n", iluErrorString(ilError));
		return false;
	}

	return true;
}

bool loadMedia(void) {
	/*
	if (!gTexture.loadTextureFromFileWithColorKey("img/circleWithAlpha.png", 000, 255, 255)) {
		fprintf(stderr, "Unable to load circle with alpha texture!\n");
		return false;
	}
	*/

	if (!gTexture.loadTextureFromFile("img/circleWithAlpha.png")) {
		fprintf(stderr, "Unable to load texture!\n");
		return false;
	}

	return true;
}

void update(void) {
	gAngle += 40.0f / SCREEN_FPS;

	if (gAngle > 360.0f) {
		gAngle -= 360.0f;
	}
}

void render(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glPushMatrix();

	gDrawQuad(0.0f, 0.0f, 200.0f, 200.0f, 1.0f, 1.0f, 0.0f, 1.0f);

	switch(gTransformationCombo) {
		case 0:
			glTranslatef(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f);
			glRotatef(gAngle, 0.0f, 0.0f, 1.0f);
			glScalef(2.0f, 2.0f, 0.0f);
			glTranslatef(gTexture.imageWidth() / -2.0f, gTexture.imageHeight() / -2.0f, 0.0f);

			break;

		case 1:
			glTranslatef(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f);
			glRotatef(gAngle, 0.0f, 0.0f, 1.0f);
			glTranslatef(gTexture.imageWidth() / -2.0f, gTexture.imageHeight() / -2.0f, 0.0f);
			glScalef(2.0f, 2.0f, 0.0f);

			break;

		case 2:
			glScalef(2.0f, 2.0f, 0.0f);
			glTranslatef(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f);
			glRotatef(gAngle, 0.0f, 0.0f, 1.0f);
			glTranslatef(gTexture.imageWidth() / -2.0f, gTexture.imageHeight() / -2.0f, 0.0f);

			break;

		case 3:
			glTranslatef(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f);
			glRotatef(gAngle, 0.0f, 0.0f, 1.0f);
			glScalef(2.0f, 2.0f, 0.0f);

			break;

		case 4:
			glScalef(2.0f, 2.0f, 0.0f);
			glTranslatef(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f);
			glRotatef(gAngle, 0.0f, 0.0f, 1.0f);
			glTranslatef(gTexture.imageWidth() / -2.0f, gTexture.imageHeight() / -2.0f, 0.0f);

			break;
	}

	gTexture.render(0.0f, 0.0f);

	glutSwapBuffers();
}

void handleKeys(unsigned char key, int x, int y) {
	x = 0; y = 0; //Just to stop g++ from complaining
	if (key == 'q') {
		if (gColorMode == COLOR_MODE_MONO) {
			gColorMode = COLOR_MODE_MULTI;
		} else if (gColorMode == COLOR_MODE_MULTI) {
			gColorMode = COLOR_MODE_MONO;
		}
	}

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

	if (key == 'e') {
		glBindTexture(GL_TEXTURE_2D, gTexture.getTextureID());

		if (gFiltering != GL_LINEAR) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

			gFiltering = GL_LINEAR;
		} else if (gFiltering != GL_NEAREST) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			gFiltering = GL_NEAREST;
		}

		glBindTexture(GL_TEXTURE_2D, (GLuint)NULL);
	}

	if (key == 'f') {
		gAngle = 0.0f;

		gTransformationCombo++;

		if (gTransformationCombo > 4) {
			gTransformationCombo = 0;
		}
	}

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glLoadIdentity();

	glTranslatef(-gCameraX, -gCameraY, 0.0f);

	glPushMatrix();
}

void gDrawQuad(GLfloat x, GLfloat y, GLfloat sizeX, GLfloat sizeY, GLfloat R, GLfloat G, GLfloat B, GLfloat A) {
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	if (gColorMode == COLOR_MODE_MONO) {
		glTranslatef(x, y, 0.0f);

		glBegin(GL_QUADS);
			glColor4f(R, G, B, A);
			glVertex2f(-sizeX, -sizeY);
			glVertex2f(sizeX, -sizeY);
			glVertex2f(sizeX, sizeY);
			glVertex2f(-sizeX, sizeY);
		glEnd();
	} else if (gColorMode == COLOR_MODE_MULTI) {
		glTranslatef(x, y, 0.0f);

		glBegin(GL_QUADS);
			glColor4f(0.0f, 0.0f, 1.0f, A); glVertex2f(-sizeX, -sizeY);
			glColor4f(0.0f, 1.0f, 0.0f, A); glVertex2f(sizeX, -sizeY);
			glColor4f(1.0f, 0.0f, 0.0f, A); glVertex2f(sizeX, sizeY);
			glColor4f(1.0f, 1.0f, 0.0f, A); glVertex2f(-sizeX, sizeY);
		glEnd();
	}
}
