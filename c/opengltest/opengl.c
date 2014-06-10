#include <stdio.h>
#include <stdarg.h>

#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>

void display();
void specialKeys();

double rotate_y = 0;
double rotate_x = 0;

int main (int argc, char *argv[]) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutCreateWindow("Generic OpenGL Cube");

	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(display);
	glutSpecialFunc(specialKeys);

	glutMainLoop();

	return 0;
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glTranslatef(rotate_y * 0.1, 0.0, 0.0);

	glLoadIdentity();
	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);

	//glScalef(rotate_x, rotate_y, 0.0);

	//FRONT
	glBegin(GL_POLYGON);

	glColor4f(1.0, 0.0, 1.0, 0.6);
	glVertex3f(0.5, -0.5, -0.5);

	glColor4f(0.0, 0.0, 1.0, 0.7);
	glVertex3f(0.5, 0.5, -0.5);

	glColor4f(0.0, 1.0, 0.0, 0.8);
	glVertex3f(-0.5, 0.5, -0.5);

	glColor4f(1.0, 0.0, 0.0, 0.9);
	glVertex3f(-0.5, -0.5, -0.5);

	glEnd();

	//BACK
	glBegin(GL_POLYGON);

	glColor4f(1.0, 0.0, 1.0, 0.6);
	glVertex3f(0.5, -0.5, 0.5);

	glColor4f(0.0, 0.0, 1.0, 0.7);
	glVertex3f(0.5, 0.5, 0.5);

	glColor4f(0.0, 1.0, 0.0, 0.8);
	glVertex3f(-0.5, 0.5, 0.5);

	glColor4f(1.0, 0.0, 0.0, 0.9);
	glVertex3f(-0.5, -0.5, 0.5);

	glEnd();

	//RIGHT
	glBegin(GL_POLYGON);

	glColor4f(1.0, 0.0, 0.0, 0.9);
	glVertex3f(0.5, -0.5, -0.5);

	glColor4f(0.0, 1.0, 0.0, 0.8);
	glVertex3f(0.5, 0.5, -0.5);

	glColor4f(0.0, 0.0, 1.0, 0.7);
	glVertex3f(0.5, 0.5, 0.5);

	glColor4f(1.0, 0.0, 1.0, 0.6);
	glVertex3f(0.5, -0.5, 0.5);

	glEnd();

	//LEFT
	glBegin(GL_POLYGON);

	glColor4f(1.0, 0.0, 1.0, 0.6);
	glVertex3f(-0.5, -0.5, 0.5);

	glColor4f(0.0, 0.0, 1.0, 0.7);
	glVertex3f(-0.5, 0.5, 0.5);

	glColor4f(0.0, 1.0, 0.0, 0.8);
	glVertex3f(-0.5, 0.5, -0.5);

	glColor4f(1.0, 0.0, 0.0, 0.9);
	glVertex3f(-0.5, -0.5, -0.5);

	glEnd();

	//TOP
	glBegin(GL_POLYGON);

	glColor4f(1.0, 0.0, 0.0, 0.9);
	glVertex3f(0.5, 0.5, 0.5);

	glColor4f(0.0, 1.0, 0.0, 0.8);
	glVertex3f(0.5, 0.5, -0.5);

	glColor4f(0.0, 0.0, 1.0, 0.7);
	glVertex3f(-0.5, 0.5, -0.5);

	glColor4f(1.0, 0.0, 1.0, 0.6);
	glVertex3f(-0.5, 0.5, 0.5);

	glEnd();

	//BOT
	glBegin(GL_POLYGON);

	glColor4f(1.0, 0.0, 1.0, 0.6);
	glVertex3f(0.5, -0.5, -0.5);

	glColor4f(0.0, 0.0, 1.0, 0.7);
	glVertex3f(0.5, -0.5, 0.5);

	glColor4f(0.0, 1.0, 0.0, 0.8);
	glVertex3f(-0.5, -0.5, 0.5);

	glColor4f(1.0, 0.0, 0.0, 0.9);
	glVertex3f(-0.5, -0.5, -0.5);

	glEnd();

	glFlush();
	glutSwapBuffers();
}

void specialKeys(int key, int x, int y) {
	if (key == GLUT_KEY_RIGHT) {
		rotate_y += 5;
	}

	if (key == GLUT_KEY_LEFT) {
		rotate_y -= 5;
	}

	if (key == GLUT_KEY_UP) {
		rotate_x += 5;
	}

	if (key == GLUT_KEY_DOWN) {
		rotate_x -= 5;
	}

	glutPostRedisplay();
}
