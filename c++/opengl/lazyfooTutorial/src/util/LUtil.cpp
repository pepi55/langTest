#include <IL/il.h>
#include <IL/ilu.h>

#include "LUtil.hpp"
#include "../tex/LTexture.hpp"
#include "../tex/LSpriteSheet.hpp"

GLfloat gCameraX = 0.0f,
				gCameraY = 0.0f;

LTexture gTexture;
LSpriteSheet gSprites;

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
	if (!gTexture.loadTextureFromFile("img/texture.png")) {
		fprintf(stderr, "Unable to load texture!\n");
		return false;
	}

	if (!gSprites.loadTextureFromFile("img/arrows.png")) {
		fprintf(stderr, "Unable to load sprite sheet!\n");
		return false;
	}

	LFRect clip = {0.0f, 0.0f, 128.0f, 128.0f};

	clip.x = 0.0f;
	clip.y = 0.0f;
	gSprites.addClipSprite(clip);

	clip.x = 128.0f;
	clip.y = 0.0f;
	gSprites.addClipSprite(clip);

	clip.x = 0.0f;
	clip.y = 128.0f;
	gSprites.addClipSprite(clip);

	clip.x = 128.0f;
	clip.y = 128.0f;
	gSprites.addClipSprite(clip);

	if (!gSprites.generateDataBuffer()) {
		fprintf(stderr, "Unable to clip sprite sheet!\n");
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

	gTexture.render(100, 100);

	glLoadIdentity();
	glTranslatef(64.0f, 64.0f, 0.0f);
	gSprites.renderSprite(0);

	glLoadIdentity();
	glTranslatef(SCREEN_WIDTH - 64.0f, 64.0f, 0.0f);
	gSprites.renderSprite(1);

	glLoadIdentity();
	glTranslatef(64.0f, SCREEN_HEIGHT - 64.0f, 0.0f);
	gSprites.renderSprite(2);

	glLoadIdentity();
	glTranslatef(SCREEN_WIDTH - 64.0f, SCREEN_HEIGHT - 64.0f, 0.0f);
	gSprites.renderSprite(3);

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
