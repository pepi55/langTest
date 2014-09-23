//includes
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>

//User includes
#include "shader.hpp"

using namespace std;

GLuint LoadShaders(const char *vertexFilePath, const char *fragmentFilePath) {
	//Variable Declaration
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	GLuint programID = glCreateProgram();

	GLint result = GL_FALSE;

	std::string fragmentShaderCode;
	std::string vertexShaderCode;

	std::ifstream fragmentShaderStream(fragmentFilePath, std::ios::in);
	std::ifstream vertexShaderStream(vertexFilePath, std::ios::in);

	int infoLogLength;
	char const *vertexSourcePointer;
	char const *fragmentSourcePointer;

	//Executions
	if (vertexShaderStream.is_open()) {
		std::string line = "";

		while (getline(vertexShaderStream, line)) {
			vertexShaderCode += "\n" + line;
		}

		vertexShaderStream.close();
	} else {
		printf("Impossible to open %s. Are you in the right directory?\n", vertexFilePath);
		getchar();

		return 0;
	}

	if (fragmentShaderStream.is_open()) {
		std::string line = "";

		while (getline(fragmentShaderStream, line)) {
			fragmentShaderCode += "\n" + line;
		}

		fragmentShaderStream.close();
	} else {
		printf("Impossible to open %s. Are you in the right directory?\n", fragmentFilePath);
		getchar();

		return 0;
	}

	//Compiling vertex shader
	printf("Compiling vertex shader: %s...\n", vertexFilePath);
	vertexSourcePointer = vertexShaderCode.c_str();

	glShaderSource(vertexShaderID, 1, &vertexSourcePointer, NULL);
	glCompileShader(vertexShaderID);

	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

	if (infoLogLength > 0) {
		std::vector<char> vertexShaderErrorMessage(infoLogLength + 1);

		glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
		printf("%s\n", &vertexShaderErrorMessage[0]);
	}

	//Compiling fragment shader
	printf("Compiling fragment shader: %s...\n", fragmentFilePath);
	fragmentSourcePointer = fragmentShaderCode.c_str();

	glShaderSource(fragmentShaderID, 1, &fragmentSourcePointer, NULL);
	glCompileShader(fragmentShaderID);

	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

	if (infoLogLength > 0) {
		std::vector<char> fragmentShaderErrorMessage(infoLogLength + 1);

		glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, &fragmentShaderErrorMessage[0]);
		printf("%s\n", &fragmentShaderErrorMessage[0]);
	}

	//Link program
	printf("Linking program...\n");

	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);

	if (infoLogLength > 0) {
		std::vector<char> programErrorMessage(infoLogLength + 1);

		glGetProgramInfoLog(programID, infoLogLength, NULL, &programErrorMessage[0]);
		printf("%s\n", &programErrorMessage[0]);
	}

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return programID;
}
