#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int integer(float a);
int naturalNumber(float a);
int divisor(float a, float b);
long *division(long a);

int main (void) {
	float a = 0, b = 0;
	int i;

	printf("Insert first number to be manipulated: ");
	scanf("%f", &a);

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

long *division(long a){
	int i, len = 1;//for 1
	long *result;

	if (a < 1) return NULL;

	result = malloc(a * sizeof(long));
	if (result) {
		for (i = 2; i <= a; ++i)//skip 1
			if (a % i == 0)
				result[len++] = i;

		result[0] = len;//put a length instead of 1
		result=realloc(result, len*sizeof(long));
	}

	return result;
}
