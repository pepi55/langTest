#include <IL/il.h>
#include <IL/ilu.h>

#include "LUtil.hpp"
#include "LTexture.hpp"
#include "LVertexPos2D.hpp"

GLfloat gAngle = 0.0;
GLfloat gCameraX = 0.0f,
				gCameraY = 0.0f;

GLuint gIndices[4];
GLuint gIndexBuffer = 0;
GLuint gVertexBuffer = 0;

LVertexPos2D gQuadVertices[4];

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
	gQuadVertices[0].x = SCREEN_WIDTH * 1.0f / 4.0f;
	gQuadVertices[0].y = SCREEN_HEIGHT * 1.0f / 4.0f;

	gQuadVertices[1].x = SCREEN_WIDTH * 3.0f / 4.0f;
	gQuadVertices[1].y = SCREEN_HEIGHT * 1.0f / 4.0f;

	gQuadVertices[2].x = SCREEN_WIDTH * 3.0f / 4.0f;
	gQuadVertices[2].y = SCREEN_HEIGHT * 3.0f / 4.0f;

	gQuadVertices[3].x = SCREEN_WIDTH * 1.0f / 4.0f;
	gQuadVertices[3].y = SCREEN_HEIGHT * 3.0f / 4.0f;

	gIndices[0] = 0;
	gIndices[1] = 1;
	gIndices[2] = 2;
	gIndices[3] = 3;

	glGenBuffers(1, &gVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, gVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(LVertexPos2D), gQuadVertices, GL_STATIC_DRAW);

	glGenBuffers(1, &gIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), gIndices, GL_STATIC_DRAW);

	return true;
}

void update(void) {
	gAngle += 90.0f / SCREEN_FPS;

	if (gAngle > 360.0f) {
		gAngle -= 360.0f;
	}
}

void render(void) {
	int tempW = -(gQuadVertices[1].x + gQuadVertices[0].x),
			tempH = -(gQuadVertices[1].y + gQuadVertices[0].y + gQuadVertices[2].y);

	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glPushMatrix();

	glTranslatef(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f);
	glRotatef(gAngle, 0.0f, 0.0f, 1.0f);
	glScalef(0.5f, 0.5f, 0.0f);
	glTranslatef(tempW / 2.0f, tempH / 2.0f, 0.0f);

	glEnableClientState(GL_VERTEX_ARRAY);

		glBindBuffer(GL_ARRAY_BUFFER, gVertexBuffer);
		glVertexPointer(2, GL_FLOAT, 0, NULL);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIndexBuffer);
		glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, NULL);

	glDisableClientState(GL_VERTEX_ARRAY);

	glutSwapBuffers();
}

void handleKeys(unsigned char key, int x, int y) {
	/*if (key == '-') {
		gAngle += 10.0f / SCREEN_FPS;
	}

	if (key == '=') {
		gAngle -= 10.0f / SCREEN_FPS;
	}*/

	if (key == '?') {
		fprintf(stdout, "What is x/y? Baby dont %i, %i, me! NO mo'!\n", x, y);
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
