#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int integer(float a);
int naturalNumber(float a);
int divisor(float a, float b);
int primes(float a);

void division(float a);

int main (void) {
	float a = 0, b = 0;

	printf("Insert first number to be manipulated: ");
	scanf("%f", &a);

	/*printf("Insert second number to be manipulated: ");
	scanf("%f", &b);*/

	fputs(integer(a) ? "The first number is an integer.\n" : "The first number is not an integer.\n", stdout);
	fputs(naturalNumber(a) ? "The first number is a natural number.\n" : "The first number is not a natural number.\n", stdout);
	fputs(divisor(a, b) ? "The first number is a divisor.\n" : "The first number is not a divisor.\n", stdout);

	division(a);
	//primes(a);

	return 0;
}

int integer (float a) {
	bool result = 0;

	if (fmod(a, 1) == 0) result = 1;

	return result;
}

int naturalNumber (float a) {
	bool result = 0;

	if (a > 0 && integer(a))	result = 1;

	return result;
}

int divisor (float a, float b) {
	bool result = 0;

	if (integer(b / a)) result = 1;

	return result;
}

void division (float a) {
	FILE * f = fopen("divisionResult", "wb+");
	int i, j, k, c, answ = 0;
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

	printf("Do you wish to print the division result? (answer with 1 (Yes) or 2 (No)) ");
	scanf("%d", &answ);

	if (answ == 1) {
		while (fgets(line, 100, f) != NULL) {
			sscanf(line, "%d", &c);
			printf("%d\n", c);
		}
	}

	fclose(f);
}

int primes (float a) {

}
