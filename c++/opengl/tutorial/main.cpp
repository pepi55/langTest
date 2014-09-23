#include <stdio.h>

//OpenGL includes
//#include <glm/glm.hpp>

//User includes
#include "src/openglFunc.hpp"

//using namespace glm;

int main (void) {
	int antialiasing = 4;
	int success;
	
	success = GLFWInitialization(antialiasing);

	if (success != 0) {
		fprintf(stderr, "Error at GLFWInit\n");
		return -1;
	}

	mainLoop();

	return 0;
}
