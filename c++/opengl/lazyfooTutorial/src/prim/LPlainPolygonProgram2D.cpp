#include "LPlainPolygonProgram2D.hpp"

LPlainPolygonProgram2D::LPlainPolygonProgram2D(void) {
	mPolygonColorLocation = 0;
}

bool LPlainPolygonProgram2D::loadProgram(void) {
	mProgramID = glCreateProgram();

	GLuint vertexShader = loadShaderFromFile("src/shader/shaderFiles/vertexShader.glslv", GL_VERTEX_SHADER);
	GLuint fragmentShader = loadShaderFromFile("src/shader/shaderFiles/fragmentShader.glslf", GL_FRAGMENT_SHADER);

	if (vertexShader == 0) {
		glDeleteProgram(mProgramID);
		mProgramID = 0;

		return false;
	}

	glAttachShader(mProgramID, vertexShader);

	if (fragmentShader == 0) {
		glDeleteShader(vertexShader);
		glDeleteProgram(mProgramID);
		mProgramID = 0;

		return false;
	}

	glAttachShader(mProgramID, fragmentShader);
	glLinkProgram(mProgramID);

	GLint programSuccess = GL_TRUE;
	glGetProgramiv(mProgramID, GL_LINK_STATUS, &programSuccess);
	if (programSuccess != GL_TRUE) {
		fprintf(stderr, "Error linking program %d!\n", mProgramID);
		printProgramLog(mProgramID);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glDeleteProgram(mProgramID);
		mProgramID = 0;

		return false;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	mPolygonColorLocation = glGetUniformLocation(mProgramID, "LPolygonColor");
	if (mPolygonColorLocation == -1) {
		fprintf(stderr, "%s is not a valid glsl program variable!\n", "LPolygonColor");
	}

	return true;
}

void LPlainPolygonProgram2D::setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	glUniform4f(mPolygonColorLocation, r, g, b, a);
}
