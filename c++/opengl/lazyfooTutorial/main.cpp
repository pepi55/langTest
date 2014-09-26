#include "src/LUtil.hpp"

void runMainLoop(int val);

int main(int argc, char *args[]) {
	glutInit(&argc, args);
	glutInitContextVersion(2, 1);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow(SCREEN_TITLE);

	if (!initGL()) {
		fprintf(stderr, "Unable to initialize graphics library!\n");
		return 1;
	}

	glutKeyboardFunc(handleKeys);
	glutDisplayFunc(render);
	glutTimerFunc(1000 / SCREEN_FPS, runMainLoop, 0);
	glutMainLoop();

	return 0;
}

void runMainLoop(int val) {
	update();
	render();

	glutTimerFunc(1000 / SCREEN_FPS, runMainLoop, val);
}
