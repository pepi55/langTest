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

unsigned int *division (long a) {
	int i, l = 1;
	unsigned int *result;

	if (a < 1) return NULL;

	result = malloc(a * sizeof(unsigned int));
	if (result) {
		if (naturalNumber(a)) {
			for (i = 1; i <= a; ++i) {
				if (divisor(i, a)) {
					result[l++] = i;
				}
			}

			result[0] = l;
			result = realloc(result, l * sizeof(unsigned int));
		}
	}

	return result;
}

unsigned int *primes (long a) {
	int i, ln, l = 1;
	unsigned int *result, *div;

	if (a < 1) return NULL;

	result = malloc(a * sizeof(unsigned int));
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
			result = realloc(result, l * sizeof(unsigned int));
		}
	}

	return result;
}

unsigned int *primeFactorization (float a) {
	int ln, l = 1, i = 1;
	unsigned int *result, *prime;

	if (a < 1) return NULL;

	result = malloc(a * sizeof(unsigned int));
	if (result) {
		prime = primes(a);
		ln = prime[0];

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
		result = realloc(result, l * sizeof(unsigned int));
	}

	return result;
}

void divisionToFile (float a) {
	FILE *f = fopen("divisionResult", "wb+");
	int i, c;
	char line[100];

	if (f == NULL) {
		printf("\nError loading file!\n");
		exit(EXIT_FAILURE);
	}

	if (naturalNumber(a)) {
		for (i = 0; i < a + 1; i++) {
			if (divisor(i, a)) {
				fprintf(f, "%d\n", i);
			}
		}

		rewind(f);
	}

	while (fgets(line, 100, f) != NULL) {
		sscanf(line, "%d", &c);
		printf("%d\n", c);
	}

	fclose(f);
}
