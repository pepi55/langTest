#include <stdio.h>
#include <stdarg.h>
#include <GL/glut.h>

/*void createSphere (GLfloat size, GLfloat rotation_x, GLfloat rotation_y, GLfloat position_x, GLfloat position_y) {
	GLsizei numVAOs = 1;
	GLsizei numBuffers = 1;

	GLuint buffers[numBuffers];
	GLuint VAOs[numVAOs];

	glGenVertexArrays(numVAOs, VAOs);
	glBindVertexArray(VAOs);

	GLfloat vertices[] = {
		//Triangle 1
		{ -0.90, -0.90 },
		{ 0.85, -0.90 },
		{ -0.90, 0.85 },

		//Triangle 2
		{ 0.90, -0.85 },
		{ 0.90, 0.90 },
		{ -0.85, 0.90 }
	};

	glGenBuffers(numBuffers, buffers);
	glBindBuffer(GL_ARRAY_BUFFER, buffers);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "src/shr/triangle.vert" },
		{ GL_FRAGMENT_SHADER, "src/shr/triangle.frag" },
		{ GL_NONE, NULL }
	};

	GLuint program = LoadShaders(shaders);
	glUseProgram(program);

	glDeleteVertexArrays(numVAOs, VAOs);
	glDeleteBuffers(numBuffers, buffers);
}*/

void createCube (GLfloat size, GLfloat rotation_x, GLfloat rotation_y) {
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
