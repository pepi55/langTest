#include <stdio.h>
#include <stdlib.h>

//OpenGL includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

//User includes
#include "src/openglFunc.hpp"

using namespace glm;

int main (void) {
	int antialiasing = 4;

	GLFWInitialization(antialiasing);

	return 0;
}
