#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "maths.h"

int integer (float a) {
	bool result = 0;

	if (fmod(a, 1) == 0) result = 1;

	return result;
}

int naturalNumber (float a) {
	bool result = 0;

	if (a > 0 && integer(a)) result = 1;

	return result;
}

int divisor (float a, float b) {
	bool result = 0;

	if (integer(b / a)) result = 1;

	return result;
}

int gcd (int a, int b) {
	while (b != 0) {
		int c = a % b;
		a = b; b = c;
	}

	return a;
}

long long *division(long long a) {
	unsigned int len = 1;
	long long *result = NULL;

	if (a < 1) return NULL;

	result = (long long *)malloc(a * sizeof(long long));
	if (result) {
		for (long long i = 2; i <= a; ++i) {
			if (divisor(i, a)) {
				result[len++] = i;
			}
		}

		result[0] = len;
		result = (long long *)realloc(result, len * sizeof(long long));
	}

	return result;
}

void divisionToFile (float a) {
	FILE *f = fopen("divisionResult", "wb+");
	unsigned long i, c;
	char line[100];

	if (f == NULL) {
		printf("\nError loading file!\n");
		exit(EXIT_FAILURE);
	}

	if (naturalNumber(a)) {
		for (i = 0; i < a + 1; i++) {
			if (divisor(i, a)) {
				fprintf(f, "%lu\n", i);
			}
		}

		rewind(f);
	}

	while (fgets(line, 100, f) != NULL) {
		sscanf(line, "%lu", &c);
		printf("%lu\n", c);
	}

	fclose(f);
}
