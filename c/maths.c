#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int integer(float a);
int naturalNumber(float a);
int divisor(float a, float b);
int * division(float a);

int main () {
	float a = 0;
	float b = 0;
	int l = (sizeof(division(a)) / sizeof(division(a)[0]));
	int i;

	printf("Insert first number to be manipulated: ");
	scanf("%f", &a);

	printf("Insert second number to be manipulated: ");
	scanf("%f", &b);

	fputs(integer(a) ? "true" : "false", stdout);
	fputs(naturalNumber(a) ? "\ntrue" : "\nfalse", stdout);
	fputs(divisor(a, b) ? "\ntrue" : "\nfalse", stdout);

	//printf(" %d", l);
	for (i = 0; i < l; i++) {
		printf("\n%d", division(a)[i]);
	}

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

int divisor (float a, float b) {
	bool result = 0;

	if (integer(b / a)) result = 1;

	return result;
}

int * division (float a) {
	FILE *f = fopen("divisionResult", "w");
	char maxLiLength[20];
	int i;
	double content[] = {0};
	int result[i];

	if (f == NULL) {
		printf("\nError loading file!\n");
		exit(EXIT_FAILURE);
	}

	if (naturalNumber(a)) {
		for (i = 0; i < a; i++) {
			if (divisor(i, a)) {
				fprintf(f, " %d\n", i);
			}
		}
	}

	while (fgets(maxLiLength, 200, f) != NULL) {
		content[i] = atoi(maxLiLength);
		result[i] = (int) content[i];
		i++;
	}

	fclose(f);

	return result;
}
