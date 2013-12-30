#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int integer(float a);
int naturalNumber(float a);
int divisor(float a, float b);
int *processDivision(int a, int *output_length);

int main (void) {
	//Vars for array counts
	int intsToProcess = 0XDEADBEEF;

	int dividersCount = 0;
	int *dividers = processDivision(intsToProcess, &dividersCount);

	//Vars for main
	float a = 0, b = 0;
	int i;

	printf("Insert first number to be manipulated: ");
	scanf("%f", &a);
	printf("%d\n", dividersCount);

	/*printf("Insert second number to be manipulated: ");
	scanf("%f", &b);*/

	fputs(integer(a) ? "The first number is an integer.\n" : "The first number is not an integer.\n", stdout);
	fputs(naturalNumber(a) ? "The first number is a natural number.\n" : "The first number is not a natural number.\n", stdout);
	fputs(divisor(a, b) ? "The first number is a divisor.\n" : "The first number is not a divisor.\n", stdout);

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

int *processDivision (int a, int *output_length) {
	int *dividers = malloc(a * sizeof(int));
	int foundDividers = 0;
	int i;

	if (naturalNumber(a)) {
		for (i = 0; i < a + 1; i++) {
			if (divisor(i, a)) {
				foundDividers = i;
			}
		}
	}

	int *tmp = realloc(dividers, foundDividers);
	free(dividers);

	*output_length = foundDividers;

	return tmp;
}
