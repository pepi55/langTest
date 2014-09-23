#include <stdio.h>

//User includes
#include "src/openglFunc.hpp"

int main (void) {
	int antialiasing = 4;
	int success;
	
	success = GLFWInitialization(antialiasing);

	if (success != 0) {
		fprintf(stderr, "Error at GLFWInit\a\n");
		return -1;
	}

	mainLoop();

	return 0;
}
