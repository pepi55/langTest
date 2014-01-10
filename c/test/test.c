#include <stdio.h>

#include "SampleHeader.h"

void testPrintStr(char *err);

int main (void) {
	//struct Sample classInC = Sample.new(3, -4);

	testPrintStr("errorplace");

	//printf("Sample test: %g\n", classInC.abs(&classInC));

	printf("size of \"short\": %lu\n", sizeof(short));
	printf("size of \"int\": %lu\n", sizeof(int));
	printf("size of \"long\": %lu\n", sizeof(long));

	return 0;
}

void testPrintStr(char *err) {
	fprintf(stderr, err, " Error: %s\n", err);
}
