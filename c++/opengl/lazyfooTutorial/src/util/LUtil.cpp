#define GLM_FORCE_RADIANS

#include <IL/il.h>
#include <IL/ilu.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "LUtil.hpp"
#include "../font/LFont.hpp"

GLfloat gCameraX = 0.0f,
				gCameraY = 0.0f;

LFont gFont;
LFontProgram2D gFontProgram;

LColorRGBA gTextColor = {1.0f, 0.5f, 1.0f, 1.0f};

bool initGL(void) {
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK) {
		fprintf(stderr, "Error initializing GLEW!\n%s\n", glewGetErrorString(glewError));
		return false;
	}

	if (!GLEW_VERSION_3_1) {
		fprintf(stderr, "OpenGL 3.1 not supported!\n");
		return false;
	}

	glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);

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

bool loadGP(void) {
	if (!gFontProgram.loadProgram()) {
		fprintf(stderr, "Unable to load font program!\n");
		return false;
	}

	gFontProgram.bind();
	gFontProgram.setProjection(glm::ortho<GLfloat>(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 1.0f, -1.0f));
	gFontProgram.setModelView(glm::mat4());

	gFontProgram.updateProjection();
	gFontProgram.updateModelView();
	gFontProgram.setTextureUnit(0);
	LFont::setFontProgram2D(&gFontProgram);

	gFontProgram.unbind();

	return true;
}

bool loadMedia(void) {
	if (!gFont.loadFreetype("img/font/lazy.ttf", 60)) {
		fprintf(stderr, "Unable to load font!\n");
		return false;
	}

	return true;
}

void update(void) {
}

void render(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	renderScene();

	glutSwapBuffers();
}

void renderScene(void) {
	gFontProgram.bind();
	gFontProgram.setModelView(glm::mat4());
	gFontProgram.setTextColor(gTextColor);
	gFontProgram.unbind();

	gFont.renderText(0.0f, 0.0f, "GLSL REND er I ng!");
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
}

void handleMouseMotion(int x, int y) {
	if (x == 0) {
		if (y == 0) {
			fprintf(stdout, "x and y are 0");
		}
	}
}
