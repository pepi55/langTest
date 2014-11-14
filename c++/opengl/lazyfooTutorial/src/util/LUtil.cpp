#include <IL/il.h>
#include <IL/ilu.h>

#include "LUtil.hpp"

GLfloat gCameraX = 0.0f,
				gCameraY = 0.0f;

LPlainPolygonProgram2D gPlainPolyProg2D;

GLuint gVBO = 0x0,
			 gIBO = 0x0;

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

bool loadGP(void) {
	if (!gPlainPolyProg2D.loadProgram()) {
		fprintf(stderr, "Unable to load basic shader!\n");
		return false;
	}

	gPlainPolyProg2D.bind();

	return true;
}

bool loadMedia(void) {
	LVertexPos2D quadVertices[4];
	GLuint indices[4];

	quadVertices[0].x = -50.0f;
	quadVertices[0].y = -50.0f;

	quadVertices[1].x = 50.0f;
	quadVertices[1].y = -50.0f;

	quadVertices[2].x = 50.0f;
	quadVertices[2].y = 50.0f;

	quadVertices[3].x = -50.0f;
	quadVertices[3].y = 50.0f;

	for (int i = 0; i < 4; ++i) {
		indices[i] = i;
	}

	glGenBuffers(1, &gVBO);
	glBindBuffer(GL_ARRAY_BUFFER, gVBO);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(LVertexPos2D), quadVertices, GL_STATIC_DRAW);

	glGenBuffers(1, &gIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indices, GL_STATIC_DRAW);

	return true;
}

void update(void) {
}

void render(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glPushMatrix();

	renderScene();

	glutSwapBuffers();
}

void renderScene(void) {
	glTranslatef(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f);
	gPlainPolyProg2D.setColor(1.0f, 0.0f, 1.0f);

	glEnableClientState(GL_VERTEX_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, gVBO);
		glVertexPointer(2, GL_FLOAT, 0, NULL);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);

		glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, NULL);
	glDisableClientState(GL_VERTEX_ARRAY);
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

void handleMouseMotion(int x, int y) {
	if (x == 0) {
		if (y == 0) {
			fprintf(stdout, "x and y are 0");
		}
	}
}

void gDrawQuads(GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b) {
	glBegin(GL_QUADS);
		glColor3f(r, g, b);
		glVertex2f(-x, -y);
		glVertex2f(x, -y);
		glVertex2f(x, y);
		glVertex2f(-x, y);
	glEnd();
}
