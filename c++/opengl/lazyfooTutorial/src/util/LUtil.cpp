#define GLM_FORCE_RADIANS

#include <IL/il.h>
#include <IL/ilu.h>
#include <glm/gtx/transform.hpp>

#include "LUtil.hpp"

GLfloat gCameraX = 0.0f,
				gCameraY = 0.0f;

LTexturedPolygon2D gTexturedPolygon2D;
LTexture gOpenGLTexture;

LColorRGBA gTextureColor = {1.0f, 1.0f, 1.0f, 0.5f};

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
	if (!gTexturedPolygon2D.loadProgram()) {
		fprintf(stderr, "Unable to load basic shader!\n");
		return false;
	}

	gTexturedPolygon2D.bind();

	gTexturedPolygon2D.setProjection(glm::ortho<GLfloat>(0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0));
	gTexturedPolygon2D.updateProjection();

	gTexturedPolygon2D.setTextureUnit(0);
	LTexture::setTexturedPolygon2D(&gTexturedPolygon2D);

	return true;
}

bool loadMedia(void) {
	if (!gOpenGLTexture.loadTextureFromFile32("img/opengl.png")) {
		fprintf(stderr, "Unable to load texture!\n");
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
	gTexturedPolygon2D.setModelView(glm::mat4());
	gTexturedPolygon2D.setTextureColor(gTextureColor);
	gOpenGLTexture.render((SCREEN_WIDTH - gOpenGLTexture.imageWidth()) / 2.0f, (SCREEN_HEIGHT - gOpenGLTexture.imageHeight()) / 2.0f);
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

void gDrawQuads(GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b) {
	glBegin(GL_QUADS);
		glColor3f(r, g, b);
		glVertex2f(-x, -y);
		glVertex2f(x, -y);
		glVertex2f(x, y);
		glVertex2f(-x, y);
	glEnd();
}
