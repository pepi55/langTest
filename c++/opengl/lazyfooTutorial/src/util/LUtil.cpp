#include <IL/il.h>
#include <IL/ilu.h>

#include "LUtil.hpp"
#include "../font/LFont.hpp"
#include "../tex/LTexture.hpp"
#include "../tex/LSpriteSheet.hpp"

enum AliasMode {
	ALIAS_MODE_ALIASED,
	ALIAS_MODE_ANTI_ALIASED,
	ALIAS_MODE_MULTISAMPLE
};

AliasMode gMode = ALIAS_MODE_ALIASED;

GLfloat gCameraX = 0.0f,
				gCameraY = 0.0f;

LTexture gTexture,
				 gFBOTexture;

GLuint gStencilRenderOp = GL_NOTEQUAL;
GLuint gFBO = 0x0;

GLfloat gAngle = 0.0f;
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

	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

	glDisable(GL_LINE_SMOOTH);
	glDisable(GL_POLYGON_SMOOTH);
	glDisable(GL_MULTISAMPLE);

	glClearStencil(0);
	glGenFramebuffers(1, &gFBO);

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
	//gPolygonAngle += 6.0f;
	gAngle += 0.01f;
}

void render(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glPushMatrix();

	switch(gMode) {
		case ALIAS_MODE_ALIASED:
			glDisable(GL_LINE_SMOOTH);
			glDisable(GL_POLYGON_SMOOTH);
			glDisable(GL_MULTISAMPLE);
			break;

		case ALIAS_MODE_ANTI_ALIASED:
			glEnable(GL_LINE_SMOOTH);
			glEnable(GL_POLYGON_SMOOTH);
			glDisable(GL_MULTISAMPLE);
			break;

		case ALIAS_MODE_MULTISAMPLE:
			glDisable(GL_LINE_SMOOTH);
			glDisable(GL_POLYGON_SMOOTH);
			glEnable(GL_MULTISAMPLE);
			break;

		default:
			break;
	}

	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glEnable(GL_STENCIL_TEST);

	glStencilFunc(GL_ALWAYS, 1, 1);
	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);

	glTranslatef(gPolygonX, gPolygonY, 0.0f);
	//glRotatef(gPolygonAngle, 0.0f, 0.0f, 1.0f);

	glBegin(GL_QUADS);
		glVertex2f(-SCREEN_WIDTH / 5.0f, -SCREEN_HEIGHT / 5.0f);
		glVertex2f(SCREEN_WIDTH / 5.0f, -SCREEN_HEIGHT / 5.0f);
		glVertex2f(SCREEN_WIDTH / 5.0f, SCREEN_HEIGHT / 5.0f);
		glVertex2f(-SCREEN_WIDTH / 5.0f, SCREEN_HEIGHT / 5.0f);
	glEnd();

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glStencilFunc(gStencilRenderOp, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	glLoadIdentity();

	if (gFBOTexture.getTextureID() != 0) {
		glLoadIdentity();
		glTranslatef(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f);
		glRotatef(-gAngle, 0.0f, 0.0f, 1.0f);
		glTranslatef(gFBOTexture.imageWidth() / -2.0f, gFBOTexture.imageHeight() / -2.0f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		gFBOTexture.render(0.0f, 0.0f);
	}

	renderScene();

	glDisable(GL_STENCIL_TEST);

	switch(gMode) {
		case ALIAS_MODE_ANTI_ALIASED:
			glDisable(GL_LINE_SMOOTH);
			glDisable(GL_POLYGON_SMOOTH);
			break;

		case ALIAS_MODE_MULTISAMPLE:
			glDisable(GL_MULTISAMPLE);
			break;

		default:
			break;
	}

	glutSwapBuffers();
}

void renderScene(void) {
	glLoadIdentity();
	glTranslatef(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f);
	glRotatef(gAngle, 0.0f, 0.0f, 1.0f);
	glTranslatef(gTexture.imageWidth() / -2.0f, gTexture.imageHeight() / -2.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	gTexture.render(0.0f, 0.0f);

	glBindTexture(GL_TEXTURE_2D, 0x0);

	glLoadIdentity();
	glTranslatef(SCREEN_WIDTH * 1.0f / 4.0f, SCREEN_HEIGHT * 1.0f / 4.0f, 0.0f);
	glRotatef(gAngle, 0.0f, 0.0f, 1.0f);
	gDrawQuads(SCREEN_WIDTH / 16.0f, SCREEN_HEIGHT / 16.0f, 1.0f, 0.0f, 0.0f);

	glLoadIdentity();
	glTranslatef(SCREEN_WIDTH * 3.0f / 4.0f, SCREEN_HEIGHT * 1.0f / 4.0f, 0.0f);
	glRotatef(gAngle, 0.0f, 0.0f, 1.0f);
	gDrawQuads(SCREEN_WIDTH / 16.0f, SCREEN_HEIGHT / 16.0f, 0.0f, 1.0f, 0.0f);

	glLoadIdentity();
	glTranslatef(SCREEN_WIDTH * 1.0f / 4.0f, SCREEN_HEIGHT * 3.0f / 4.0f, 0.0f);
	glRotatef(gAngle, 0.0f, 0.0f, 1.0f);
	gDrawQuads(SCREEN_WIDTH / 16.0f, SCREEN_HEIGHT / 16.0f, 0.0f, 0.0f, 1.0f);

	glLoadIdentity();
	glTranslatef(SCREEN_WIDTH * 3.0f / 4.0f, SCREEN_HEIGHT * 3.0f / 4.0f, 0.0f);
	glRotatef(gAngle, 0.0f, 0.0f, 1.0f);
	gDrawQuads(SCREEN_WIDTH / 16.0f, SCREEN_HEIGHT / 16.0f, 1.0f, 1.0f, 0.0f);
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

	if (key == 'e') {
		glBindFramebuffer(GL_FRAMEBUFFER, gFBO);

		if (gFBOTexture.getTextureID() == 0) {
			gFBOTexture.createPixels32(SCREEN_WIDTH, SCREEN_HEIGHT);
			gFBOTexture.padPixels32();
			gFBOTexture.loadTextureFromPixels32();
		}

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gFBOTexture.getTextureID(), 0);

		glClear(GL_COLOR_BUFFER_BIT);
		renderScene();
		glBindFramebuffer(GL_FRAMEBUFFER, 0x0);
	}

	if (key == 'f') {
		switch(gMode) {
			case ALIAS_MODE_ALIASED:
				fprintf(stdout, "AntiAliased\n");
				gMode = ALIAS_MODE_ANTI_ALIASED;
				break;

			case ALIAS_MODE_ANTI_ALIASED:
				fprintf(stdout, "Multisample\n");
				gMode = ALIAS_MODE_MULTISAMPLE;
				break;

			case ALIAS_MODE_MULTISAMPLE:
				fprintf(stdout, "Aliased\n");
				gMode = ALIAS_MODE_ALIASED;
				break;

			default:
				break;
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

void gDrawQuads(GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b) {
	glBegin(GL_QUADS);
		glColor3f(r, g, b);
		glVertex2f(-x, -y);
		glVertex2f(x, -y);
		glVertex2f(x, y);
		glVertex2f(-x, y);
	glEnd();
}
