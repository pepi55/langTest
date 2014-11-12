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

unsigned long *division (unsigned long a) {
	unsigned long i, l = 1;
	unsigned long *result;

	if (a < 1) return NULL;

	result = (unsigned long *)malloc(a * sizeof(unsigned long));
	if (result) {
		if (naturalNumber(a)) {
			for (i = 1; i <= a; ++i) {
				if (divisor(i, a)) {
					result[l++] = i;
				}
			}

			result[0] = l;
			result = (unsigned long *)realloc(result, l * sizeof(unsigned long));
		}
	}

	return result;
}

unsigned long *primes (unsigned long a) {
	unsigned long i, ln, l = 1;
	unsigned long *result, *div;

	if (a < 1) return NULL;

	result = (unsigned long *)malloc(a * sizeof(unsigned long));
	if (result) {
		if (naturalNumber(a)) {
			for (i = 1; i <= a; ++i) {
				div = division(i);
				ln = div[0];

				if (ln == 3) {
					result[l++] = i;
				}

				free(div);
			}

			result[0] = l;
			result = (unsigned long *)realloc(result, l * sizeof(unsigned long));
		}
	}

	return result;
}

unsigned long *primeFactorization (float a) {
	unsigned long l = 1, i = 1;
	unsigned long *result = NULL, *prime = NULL;

	if (a < 1) return NULL;

	prime = primes(a);
	result = (unsigned long *)malloc((size_t)prime * sizeof(unsigned long *));
	if (result) {
		while (a != 1) {
			if (naturalNumber((float)(a / prime[i]))) {
				a /= prime[i];
				result[l++] = prime[i];
			} else {
				i += 1;
			}
		}

		free(prime);

		result[0] = l;
		result = (unsigned long *)realloc(result, l * sizeof(unsigned long));
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
