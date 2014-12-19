#define GLM_FORCE_RADIANS

#include "LFontProgram2D.hpp"
#include "glm/gtc/type_ptr.hpp"

LFontProgram2D::LFontProgram2D(void) {
	mVertexPos2DLocation = 0;
	mTexCoordLocation = 0;

	mProjectionMatrixLocation = 0;
	mModelViewMatrixLocation = 0;

	mTextColorLocation = 0;
	mTextureUnitLocation = 0;
}

bool LFontProgram2D::loadProgram(void) {
	mProgramID = glCreateProgram();
	GLuint vertexShader = loadShaderFromFile("src/shader/shaderFiles/LFontVertexShader.glslv", GL_VERTEX_SHADER);

	if (vertexShader == 0) {
		glDeleteProgram(mProgramID);
		mProgramID = 0;

		return false;
	}

	glAttachShader(mProgramID, vertexShader);
	GLuint fragmentShader = loadShaderFromFile("src/shader/shaderFiles/LFontFragmentShader.glslf", GL_FRAGMENT_SHADER);

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

	const GLchar *var = "LVertexPos2D";

	mVertexPos2DLocation = glGetAttribLocation(mProgramID, var);
	if (mVertexPos2DLocation == -1) {
		fprintf(stderr, "%s is not a valid glsl program variable!\n", var);
	}

	var = "LTexCoord";

	mTexCoordLocation = glGetAttribLocation(mProgramID, var);
	if (mTexCoordLocation == -1) {
		fprintf(stderr, "%s is not a valid glsl program variable!\n", var);
	}

	var = "LTextColor";

	mTextColorLocation = glGetUniformLocation(mProgramID, var);
	if (mTextColorLocation == -1) {
		fprintf(stderr, "%s is not a valid glsl program variable!\n", var);
	}

	var = "LTextureUnit";

	mTextureUnitLocation = glGetUniformLocation(mProgramID, var);
	if (mTextureUnitLocation == -1) {
		fprintf(stderr, "%s is not a valid glsl program variable!\n", var);
	}

	var = "LProjectionMatrix";

	mProjectionMatrixLocation = glGetUniformLocation(mProgramID, var);
	if (mProjectionMatrixLocation == -1) {
		fprintf(stderr, "%s is not a valid glsl program variable!\n", var);
	}

	var = "LModelViewMatrix";

	mModelViewMatrixLocation = glGetUniformLocation(mProgramID, var);
	if (mModelViewMatrixLocation == -1) {
		fprintf(stderr, "%s is not a valid glsl program variable!\n", var);
	}

	return true;
}

void LFontProgram2D::setVertexPointer(GLsizei stride, const GLvoid *data) {
	glVertexAttribPointer(mVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, stride, data);
}

void LFontProgram2D::setTexCoorPointer(GLsizei stride, const GLvoid *data) {
	glVertexAttribPointer(mTexCoordLocation, 2, GL_FLOAT, GL_FALSE, stride, data);
}

void LFontProgram2D::enableVertexPointer(void) {
	glEnableVertexAttribArray(mVertexPos2DLocation);
}

void LFontProgram2D::disableVertexPointer(void) {
	glDisableVertexAttribArray(mVertexPos2DLocation);
}

void LFontProgram2D::enableTexCoordPointer(void) {
	glEnableVertexAttribArray(mTexCoordLocation);
}

void LFontProgram2D::disableTexCoordPointer(void) {
	glDisableVertexAttribArray(mTexCoordLocation);
}

void LFontProgram2D::setProjection(glm::mat4 matrix) {
	mProjectionMatrix = matrix;
}

void LFontProgram2D::setModelView(glm::mat4 matrix) {
	mModelViewMatrix = matrix;
}

void LFontProgram2D::leftMultProjection(glm::mat4 matrix) {
	mProjectionMatrix = mProjectionMatrix * matrix;
}

void LFontProgram2D::leftMultModelView(glm::mat4 matrix) {
	mModelViewMatrix = mModelViewMatrix * matrix;
}

void LFontProgram2D::updateProjection(void) {
	glUniformMatrix4fv(mProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(mProjectionMatrix));
}

void LFontProgram2D::updateModelView(void) {
	glUniformMatrix4fv(mModelViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(mModelViewMatrix));
}

void LFontProgram2D::setTextColor(LColorRGBA color) {
	glUniform4f(mTextColorLocation, color.r, color.g, color.b, color.a);
}

void LFontProgram2D::setTextureUnit(GLuint unit) {
	glUniform1i(mTextureUnitLocation, unit);
}
