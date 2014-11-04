#include <IL/il.h>
#include <IL/ilu.h>

#include "LUtil.hpp"
#include "../font/LFont.hpp"
#include "../tex/LTexture.hpp"
#include "../tex/LSpriteSheet.hpp"

GLfloat gCameraX = 0.0f,
				gCameraY = 0.0f;

LFont gTTF;
LFontTextAlignment gAlignH = LFONT_TEXT_ALIGN_LEFT;
LFontTextAlignment gAlignV = LFONT_TEXT_ALIGN_TOP;
int gAlign = gAlignH | gAlignV;

LFRect gScreenArea = {0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT};

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

	if (!LFont::initFreetype()) {
		fprintf(stderr, "Unable to initialize Truetype!\n");
	}

	return true;
}

bool loadMedia(void) {
	if (!gTTF.loadFreetype("img/font/lazy.ttf", 60)) {
		fprintf(stderr, "Unable to load ttf font!\n");
		return false;
	}

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

	glColor3f(1.0f, 0.0f, 1.0f);
	gTTF.renderText(0.0f, SCREEN_WIDTH / 2.0f, "Testing alignment\nTesttestestestestei\nstest", &gScreenArea, gAlign);

	glutSwapBuffers();
}

void handleKeys(unsigned char key, int x, int y) {
//////////////////////////////////////////////////
//		GCC FILED SOME COMPLAINTS									//
//////////////////////////////////////////////////
	if (key == '?') {
		fprintf(stdout, "What is x/y? Baby dont %i, %i, me! NO mo'!\n", x, y);
	}
//////////////////////////////////////////////////
//		END OF GCC COMPLAINTS											//
//////////////////////////////////////////////////

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

	if (key == 'h') {
		switch(gAlignH) {
			case LFONT_TEXT_ALIGN_LEFT:
				gAlignH = LFONT_TEXT_ALIGN_RIGHT;
				break;

			case LFONT_TEXT_ALIGN_CENTERED_H:
				gAlignH = LFONT_TEXT_ALIGN_LEFT;
				break;

			case LFONT_TEXT_ALIGN_RIGHT:
				gAlignH = LFONT_TEXT_ALIGN_CENTERED_H;
				break;

			default:
				break;
		}
	}

	if (key == 'k') {
		switch(gAlignH) {
			case LFONT_TEXT_ALIGN_LEFT:
				gAlignH = LFONT_TEXT_ALIGN_CENTERED_H;
				break;

			case LFONT_TEXT_ALIGN_CENTERED_H:
				gAlignH = LFONT_TEXT_ALIGN_RIGHT;
				break;

			case LFONT_TEXT_ALIGN_RIGHT:
				gAlignH = LFONT_TEXT_ALIGN_LEFT;
				break;

			default:
				break;
		}
	}

	if (key == 'u') {
		switch(gAlignV) {
			case LFONT_TEXT_ALIGN_TOP:
				gAlignV = LFONT_TEXT_ALIGN_BOTTOM;
				break;

			case LFONT_TEXT_ALIGN_CENTERED_V:
				gAlignV = LFONT_TEXT_ALIGN_TOP;
				break;

			case LFONT_TEXT_ALIGN_BOTTOM:
				gAlignV = LFONT_TEXT_ALIGN_CENTERED_V;
				break;

			default:
				break;
		}
	}

	if (key == 'j') {
		switch(gAlignV) {
			case LFONT_TEXT_ALIGN_TOP:
				gAlignV = LFONT_TEXT_ALIGN_CENTERED_V;
				break;

			case LFONT_TEXT_ALIGN_CENTERED_V:
				gAlignV = LFONT_TEXT_ALIGN_BOTTOM;
				break;

			case LFONT_TEXT_ALIGN_BOTTOM:
				gAlignV = LFONT_TEXT_ALIGN_TOP;
				break;

			default:
				break;
		}
	}

	gAlign = gAlignH | gAlignV;

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glLoadIdentity();

	glTranslatef(-gCameraX, -gCameraY, 0.0f);

	glPushMatrix();
}
