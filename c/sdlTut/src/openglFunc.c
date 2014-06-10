#include <stdio.h>
#include <stdarg.h>
#include <GL/glut.h>

void createCube (float size, float rotation_x, float rotation_y) {
	//glTranslatef(rotate_y * 0.1, 0.0, 0.0);

	glLoadIdentity();
	glRotatef(rotation_x, 1.0, 0.0, 0.0);
	glRotatef(rotation_y, 0.0, 1.0, 0.0);

	//glScalef(rotate_x, rotate_y, 0.0);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	
	//FRONT
	glBegin(GL_POLYGON);

	glColor4f(1.0, 0.0, 1.0, 0.6);
	glVertex3f(size, -size, -size);

	glColor4f(0.0, 0.0, 1.0, 0.7);
	glVertex3f(size, size, -size);

	glColor4f(0.0, 1.0, 0.0, 0.8);
	glVertex3f(-size, size, -size);

	glColor4f(1.0, 0.0, 0.0, 0.9);
	glVertex3f(-size, -size, -size);

	glEnd();

	//BACK
	glBegin(GL_POLYGON);

	glColor4f(1.0, 0.0, 1.0, 0.6);
	glVertex3f(size, -size, size);

	glColor4f(0.0, 0.0, 1.0, 0.7);
	glVertex3f(size, size, size);

	glColor4f(0.0, 1.0, 0.0, 0.8);
	glVertex3f(-size, size, size);

	glColor4f(1.0, 0.0, 0.0, 0.9);
	glVertex3f(-size, -size, size);

	glEnd();

	//RIGHT
	glBegin(GL_POLYGON);

	glColor4f(1.0, 0.0, 0.0, 0.9);
	glVertex3f(size, -size, -size);

	glColor4f(0.0, 1.0, 0.0, 0.8);
	glVertex3f(size, size, -size);

	glColor4f(0.0, 0.0, 1.0, 0.7);
	glVertex3f(size, size, size);

	glColor4f(1.0, 0.0, 1.0, 0.6);
	glVertex3f(size, -size, size);

	glEnd();

	//LEFT
	glBegin(GL_POLYGON);

	glColor4f(1.0, 0.0, 1.0, 0.6);
	glVertex3f(-size, -size, size);

	glColor4f(0.0, 0.0, 1.0, 0.7);
	glVertex3f(-size, size, size);

	glColor4f(0.0, 1.0, 0.0, 0.8);
	glVertex3f(-size, size, -size);

	glColor4f(1.0, 0.0, 0.0, 0.9);
	glVertex3f(-size, -size, -size);

	glEnd();

	//TOP
	glBegin(GL_POLYGON);

	glColor4f(1.0, 0.0, 0.0, 0.9);
	glVertex3f(size, size, size);

	glColor4f(0.0, 1.0, 0.0, 0.8);
	glVertex3f(size, size, -size);

	glColor4f(0.0, 0.0, 1.0, 0.7);
	glVertex3f(-size, size, -size);

	glColor4f(1.0, 0.0, 1.0, 0.6);
	glVertex3f(-size, size, size);

	glEnd();

	//BOT
	glBegin(GL_POLYGON);

	glColor4f(1.0, 0.0, 1.0, 0.6);
	glVertex3f(size, -size, -size);

	glColor4f(0.0, 0.0, 1.0, 0.7);
	glVertex3f(size, -size, size);

	glColor4f(0.0, 1.0, 0.0, 0.8);
	glVertex3f(-size, -size, size);

	glColor4f(1.0, 0.0, 0.0, 0.9);
	glVertex3f(-size, -size, -size);

	glEnd();
}
