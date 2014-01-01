#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int integer(float a);
int naturalNumber(float a);
int divisor(float a, float b);

unsigned int *division(long a);
unsigned int *primes(long a);
unsigned int *primeFactorization(float a);

int main (void) {
	//Vars for main
	float a = 0, b = 0;
	int i;

	//Vars for division and factors
	unsigned int *div, *fct, *prm;
	int l;

	printf("Insert first number to be manipulated: ");
	scanf("%f", &a);

	/*printf("Insert second number to be manipulated: ");
	scanf("%f", &b);*/

	fputs(integer(a) ? "The first number is an integer.\n" : "The first number is not an integer.\n", stdout);
	fputs(naturalNumber(a) ? "The first number is a natural number.\n" : "The first number is not a natural number.\n", stdout);
	fputs(divisor(a, b) ? "The first number is a divisor.\n" : "The first number is not a divisor.\n", stdout);

	div = division(a);
	l = div[0];
	for (i = 1; i < l; ++i) {
		printf("Dividers: %ld\n", div[i]);
	}
	free(div);

	fct = primes(a);
	l = fct[0];
	for (i = 1; i < l; ++i) {
		printf("Primes: %ld\n", fct[i]);
	}
	free(fct);

	prm = primeFactorization(a);
	l = prm[0];
	for (i = 1; i < l; ++i) {
		printf("Factorization: %ld\n", prm[i]);
	}
	free(prm);

	return 0;
}

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

		result[0] = l;
		result = realloc(result, l * sizeof(unsigned int));
	}

	return result;
}
