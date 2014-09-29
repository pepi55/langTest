#include <IL/il.h>
#include <IL/ilu.h>

#include "LUtil.hpp"
#include "LTexture.hpp"

int gColorMode = COLOR_MODE_MONO;

GLfloat gCameraX = 0.0f,
				gCameraY = 0.0f;

LTexture gLoadedTexture;
LTexture gArrowTexture;

LFRect gArrowClips[4];

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

	ilInit();
	ilClearColor(255, 255, 255, 000);

	ILenum ilError = ilGetError();
	if (ilError != IL_NO_ERROR) {
		fprintf(stderr, "Unable to initialize DevIL!\n%s\n", iluErrorString(ilError));
		return false;
	}

	return true;
}

bool loadMedia(void) {
	gArrowClips[0].x = 0.0f;
	gArrowClips[0].y = 0.0f;
	gArrowClips[0].w = 128.0f;
	gArrowClips[0].h = 128.0f;

	gArrowClips[1].x = 128.0f;
	gArrowClips[1].y = 0.0f;
	gArrowClips[1].w = 128.0f;
	gArrowClips[1].h = 128.0f;

	gArrowClips[2].x = 0.0f;
	gArrowClips[2].y = 128.0f;
	gArrowClips[2].w = 128.0f;
	gArrowClips[2].h = 128.0f;

	gArrowClips[3].x = 128.0f;
	gArrowClips[3].y = 128.0f;
	gArrowClips[3].w = 128.0f;
	gArrowClips[3].h = 128.0f;

	if (!gArrowTexture.loadTextureFromFile("img/arrows.png")) {
		fprintf(stderr, "Unable to load arrow texture!\n");
		return false;
	}

	if (!gLoadedTexture.loadTextureFromFile("img/texture.png")) {
		fprintf(stderr, "Unable to load opengl texture!\n");
		return false;
	}

	return true;
}

void update(void) {
}

void render(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glPushMatrix();

	gDrawQuad(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f,
			SCREEN_WIDTH / 4.0f, SCREEN_HEIGHT / 4.0f, 1.0f, 0.0f, 0.0f);

	gDrawQuad(SCREEN_WIDTH, 0.0f,
			SCREEN_WIDTH / 4.0f, SCREEN_HEIGHT / 4.0f, 0.0f, 1.0f, 0.0f);

	gDrawQuad(0.0f, SCREEN_HEIGHT,
			SCREEN_WIDTH / 4.0f, SCREEN_HEIGHT / 4.0f, 0.0f, 0.0f, 1.0f);

	gDrawQuad(-SCREEN_WIDTH, 0.0f,
			SCREEN_WIDTH / 4.0f, SCREEN_HEIGHT / 4.0f, 1.0f, 0.0f, 1.0f);

	glutSwapBuffers();
}

void handleKeys(unsigned char key, int x, int y) {
	x = 0; y = 0; //Just to stop g++ from complaining
	if (key == 'q') {
		if (gColorMode == COLOR_MODE_MONO) {
			gColorMode = COLOR_MODE_MULTI;
		} else if (gColorMode == COLOR_MODE_MULTI) {
			gColorMode = COLOR_MODE_TEXTURE;
		} else if (gColorMode == COLOR_MODE_TEXTURE) {
			gColorMode = COLOR_MODE_SPRITE;
		} else if (gColorMode == COLOR_MODE_SPRITE) {
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

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glLoadIdentity();

	glTranslatef(-gCameraX, -gCameraY, 0.0f);

	glPushMatrix();
}

void gDrawQuad(GLfloat x, GLfloat y, GLfloat sizeX, GLfloat sizeY, GLfloat R, GLfloat G, GLfloat B) {
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	if (gColorMode == COLOR_MODE_MONO) {
		glTranslatef(x, y, 0.0f);

		glBegin(GL_QUADS);
			glColor3f(R, G, B);
			glVertex2f(-sizeX, -sizeY);
			glVertex2f(sizeX, -sizeY);
			glVertex2f(sizeX, sizeY);
			glVertex2f(-sizeX, sizeY);
		glEnd();
	} else if (gColorMode == COLOR_MODE_MULTI) {
		glTranslatef(x, y, 0.0f);

		glBegin(GL_QUADS);
			glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(-sizeX, -sizeY);
			glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(sizeX, -sizeY);
			glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(sizeX, sizeY);
			glColor3f(1.0f, 1.0f, 0.0f); glVertex2f(-sizeX, sizeY);
		glEnd();
	} else if (gColorMode == COLOR_MODE_TEXTURE) {
		//x = x - (gLoadedTexture.textureWidth() / 2);
		//y = y - (gLoadedTexture.textureHeight() / 2);

		gLoadedTexture.render(x, y);
	} else if (gColorMode == COLOR_MODE_SPRITE) {

		gArrowTexture.render(0.0f, 0.0f, &gArrowClips[0]);
		gArrowTexture.render(SCREEN_WIDTH - gArrowClips[1].w, 0.0f, &gArrowClips[1]);
		gArrowTexture.render(0.0f, SCREEN_HEIGHT - gArrowClips[2].h, &gArrowClips[2]);
		gArrowTexture.render(SCREEN_WIDTH - gArrowClips[3].w, SCREEN_HEIGHT - gArrowClips[3].h, &gArrowClips[3]);
	}
}
