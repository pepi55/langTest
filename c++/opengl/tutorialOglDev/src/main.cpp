#include "ogl/openGL.hpp"

int main (int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(SCREEN_HEIGHT, SCREEN_WIDTH);

	return 0;
}

static void renderSceneCB() {
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}

static void initGlutCallbacks() {
	glutDisplayFunc(renderSceneCB);
}
