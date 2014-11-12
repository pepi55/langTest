#include <IL/il.h>
#include <IL/ilu.h>

#include "LUtil.hpp"
#include "../font/LFont.hpp"
#include "../tex/LTexture.hpp"
#include "../tex/LSpriteSheet.hpp"

GLfloat gCameraX = 0.0f,
				gCameraY = 0.0f;

LTexture gTexture;

GLuint gStencilRenderOp = GL_NOTEQUAL;
GLfloat gPolygonAngle = 0.0f;
GLfloat gPolygonX = SCREEN_WIDTH / 2.0f,
				gPolygonY = SCREEN_WIDTH / 2.0f;

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

	glClearStencil(0);

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
	if (!gTexture.loadTextureFromFile32("img/opengl.png")) {
		fprintf(stderr, "Unable to load texture!\n");
		return false;
	}

	return true;
}

void update(void) {
	gPolygonAngle += 6.0f;
}

void render(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glPushMatrix();

	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glEnable(GL_STENCIL_TEST);

	glStencilFunc(GL_ALWAYS, 1, 1);
	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);

	glTranslatef(gPolygonX, gPolygonY, 0.0f);
	glRotatef(gPolygonAngle, 0.0f, 0.0f, 1.0f);

	glBegin(GL_TRIANGLES);
		glVertex2f(-0.0f / 4.0f, -SCREEN_HEIGHT / 4.0f);
		glVertex2f(SCREEN_WIDTH / 4.0f, SCREEN_HEIGHT / 4.0f);
		glVertex2f(-SCREEN_WIDTH / 4.0f, SCREEN_HEIGHT / 4.0f);
	glEnd();

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glStencilFunc(gStencilRenderOp, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	glLoadIdentity();

	gTexture.render((SCREEN_WIDTH - gTexture.imageWidth()) / 2.0f,
			(SCREEN_HEIGHT - gTexture.imageHeight()) / 2.0f);

	glDisable(GL_STENCIL_TEST);

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

	if (key == 'q') {
		if (gStencilRenderOp == GL_NOTEQUAL) {
			gStencilRenderOp = GL_EQUAL;
		} else if (gStencilRenderOp == GL_EQUAL) {
			gStencilRenderOp = GL_ALWAYS;
		} else if (gStencilRenderOp == GL_ALWAYS) {
			gStencilRenderOp = GL_NOTEQUAL;
		}
	}

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glLoadIdentity();

	glTranslatef(-gCameraX, -gCameraY, 0.0f);

	glPushMatrix();
}

void handleMouseMotion(int x, int y) {
	gPolygonX = x; gPolygonY = y;
}
