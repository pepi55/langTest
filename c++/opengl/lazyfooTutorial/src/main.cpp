#include "util/LUtil.hpp"

void runMainLoop(int val);

int main(int argc, char *args[]) {
	glutInit(&argc, args);
	glutInitContextVersion(2, 1);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_STENCIL);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(SCREEN_POSITION[0], SCREEN_POSITION[1]);
	glutCreateWindow(SCREEN_TITLE);

	if (!initGL()) {
		fprintf(stderr, "Unable to initialize graphics library!\n");
		return 1;
	}

	if (!loadMedia()) {
		fprintf(stderr, "Unable to load media!\n");
		return 2;
	}

	glutKeyboardFunc(handleKeys);
	glutMotionFunc(handleMouseMotion);
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
