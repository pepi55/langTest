#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int integer(float a);
int naturalNumber(float a);

int main () {
	float a = 0;
	float b = 0;

	printf("Insert first number to be manipulated: ");
	scanf("%f", &a);

	fputs(integer(a) ? "true" : "false", stdout);
	fputs(naturalNumber(a) ? "\ntrue" : "\nfalse", stdout);

	return 0;
}

int integer (float a) {
	bool result = 0;

	if (fmod(a, 1) == 0) {
		result = 1;
	}

	return result;
}

int naturalNumber (float a) {
	bool result = 0;

	if (a > 0 && integer(a)) {
		result = 1;
	}

	return result;
}
