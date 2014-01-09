#include <stdio.h>

#include "SampleHeader.h"

int main (void) {
	struct Sample classInC = Sample.new(3, -4);

	printf("Sample test: %g\n", classInC.abs(&classInC));

	printf("size of \"short\": %lu\n", sizeof(short));
	printf("size of \"int\": %lu\n", sizeof(int));
	printf("size of \"long\": %lu\n", sizeof(long));

	return 0;
}
