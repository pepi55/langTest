#include <stdio.h>
#include <stdlib.h>

#include "SampleHeader.h"

int main (void) {
	struct Sample classInC = Sample.new(3, -4);

	//Seed time
	srand((unsigned) time(NULL));

	printf("Sample test: %i\nSample ran: %lu\n", classInC.absolute(&classInC), classInC.ran);
	printf("random: %u\n", (unsigned)time(NULL));

	printf("size of \"short\": %lu\n", sizeof(short));
	printf("size of \"int\": %lu\n", sizeof(int));
	printf("size of \"long\": %lu\n", sizeof(long));

	return 0;
}
