#include <stdio.h>

#include "src/sdlFunc.h"
#include "src/mainLoop.h"

int main (void) {
	sdlInit();

	mainLoop();

	sdlExit(screen, /*renderer, */glContext);

	return 0;
}
