#include <IL/il.h>
#include <IL/ilu.h>

#include "LUtil.hpp"
#include "../font/LFont.hpp"
#include "../tex/LTexture.hpp"
#include "../tex/LSpriteSheet.hpp"

GLfloat gCameraX = 0.0f,
				gCameraY = 0.0f;

LTexture gTexture;
LTexture gCircle;
LFont gFont;

bool initGL(void) {
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK) {
		fprintf(stderr, "Error initializing GLEW!\n%s\n", glewGetErrorString(glewError));
		return false;
	}

	if (!GLEW_VERSION_2_1) {
		fprintf(stderr, "OpenGL 2.1 not supported!\n");
		return false;
	}

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
	if (!gFont.loadBitmap("img/lazy_font.png")) {
		fprintf(stderr, "Unable to load font!\n");
		return false;
	}

	/*
	if (!gCircle.loadTextureFromFileWithColorKey32("img/circleWithAlpha.png", 000, 255, 255)) {
		fprintf(stderr, "Unable to load circle!\n");
		return false;
	}

	if (!gTexture.loadTextureFromFile32("img/texture.png")) {
		fprintf(stderr, "Unable to load texture!\n");
		return false;
	}
	*/

	return true;
}

void update(void) {
}

void render(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glPushMatrix();

	glColor3f(0.0f, 0.0f, 1.0f);
	gFont.renderText(0, 0, "the quick brown fox jumps\nover the lazy dawg\nTHE QUICK BROWN FOX\nJUMPS OVER THE LAZY\nDAWG\n\n`~!@#$%^&*()_+[]\\{}|;':\"<>\n?,./");

	glutSwapBuffers();
}

void handleKeys(unsigned char key, int x, int y) {
//////////////////////////////////////////////////////////////////////////
//		GCC FILED SOME COMPLAINTS																					//
//////////////////////////////////////////////////////////////////////////
	if (key == '?') {
		fprintf(stdout, "What is x/y? Baby dont %i, %i, me! NO mo'!\n", x, y);
	}
//////////////////////////////////////////////////////////////////////////
//		END OF GCC COMPLAINTS																							//
//////////////////////////////////////////////////////////////////////////

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
