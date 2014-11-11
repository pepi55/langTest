#include <IL/il.h>
#include <IL/ilu.h>

#include "LUtil.hpp"
#include "../font/LFont.hpp"
#include "../tex/LTexture.hpp"
#include "../tex/LSpriteSheet.hpp"

GLfloat gCameraX = 0.0f,
				gCameraY = 0.0f;

LFont gTTF;

LFRect gScaledArea = {0.0f, 0.0f, 0.0f, 0.0f},
			 gPivotArea = {0.0f, 0.0f, 0.0f, 0.0f},
			 gCircleArea = {0.0f, 0.0f, 0.0f, 0.0f};

GLfloat gBigTextScale = 3.0f,
				gPivotAngle = 0.0f,
				gCircleAngle = 0.0f;

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

	gScaledArea = gTTF.getStringArea("Big Stuff!11!one!one11!");
	gPivotArea = gTTF.getStringArea("Pivot thingy...");
	gCircleArea = gTTF.getStringArea("Circlous much??");

	return true;
}

void update(void) {
	gPivotAngle += -1.0f;
	gCircleAngle += +2.0f;
	gBigTextScale += 0.1f;

	if (gBigTextScale >= 3.0f) {
		gBigTextScale = 0.0f;
	}
}

void render(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glPushMatrix();

	glColor3f(1.0f, 0.0f, 1.0f);
	glTranslatef((SCREEN_WIDTH - gScaledArea.w * gBigTextScale) / 2.0f, (SCREEN_HEIGHT - gScaledArea.h * gBigTextScale) / 4.0f, 0.0f);

	glScalef(gBigTextScale, gBigTextScale, gBigTextScale);
	gTTF.renderText(0.0f, 0.0f, "Big Stuff!11!one!one11!", &gScaledArea, LFONT_TEXT_ALIGN_CENTERED_H);

	glLoadIdentity();
	glColor3f(0.0f, 1.0f, 1.0f);

	glTranslatef((SCREEN_WIDTH - gPivotArea.w * 1.5f) / 2.0f, (SCREEN_HEIGHT - gPivotArea.h * 1.5f) * 3.0f / 4.0f, 0.0f);

	glScalef(1.5f, 1.5f, 1.5f);
	glTranslatef(gPivotArea.w / 2.0f, gPivotArea.h / 2.0f, 0.0f);

	glRotatef(gPivotAngle, 0.0f, 0.0f, 1.0f);

	glTranslatef(-gPivotArea.w / 2.0f, -gPivotArea.h / 2.0f, 0.0f);
	gTTF.renderText(0.0f, 0.0f, "Pivot thingy...", &gPivotArea, LFONT_TEXT_ALIGN_CENTERED_H);

	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 0.0f);

	glTranslatef(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f);
	glRotatef(gCircleAngle, 0.0f, 0.0f, 1.0f);

	glTranslatef(0.0f, -SCREEN_HEIGHT / 2.0f, 0.0f);
	glTranslatef(-gCircleArea.w / 2.0f, 0.0f, 0.0f);

	gTTF.renderText(0.0f, 0.0f, "Circlous much??", &gCircleArea, LFONT_TEXT_ALIGN_CENTERED_H);

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

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glLoadIdentity();

	glTranslatef(-gCameraX, -gCameraY, 0.0f);

	glPushMatrix();
}
