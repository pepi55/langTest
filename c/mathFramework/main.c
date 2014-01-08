#include <stdio.h>
#include <stdlib.h>

#include "maths.h"
#include "Fraction.h"

int main (void) {
	//Vars for main
	float a = 0, b = 400;
	int i, answ = 0;

	//Vars for division and factors
	unsigned int *div, *fct, *prm;
	int l;

	//Fractions
	struct Fraction fract_1;

	printf("Insert first number to be manipulated: ");
	scanf("%f", &a);

	printf("Insert second number to be manipulated: ");
	scanf("%f", &b);

	fputs(integer(a) ? "The first number is an integer.\n" : "The first number is not an integer.\n", stdout);
	fputs(naturalNumber(a) ? "The first number is a natural number.\n" : "The first number is not a natural number.\n", stdout);
	fputs(divisor(a, b) ? "The first number is a divisor.\n" : "The first number is not a divisor.\n", stdout);

	printf("greatest common divider of %i and %i: %i\n", (int) a, (int) b, gcd(a, b));

	fract_1 = Fraction.new(a, b);

	printf("numerator: %i, denominator: %i\n", fract_1.numerator, fract_1.denominator);
	printf("greatest common divider: %i\n", fract_1.fractGcd(&fract_1));
	printf("reduced numerator: %i\n", fract_1.reduced_numerator(&fract_1));
	printf("reduced denominator: %i\n", fract_1.reduced_denominator(&fract_1));

	div = division(a);
	l = div[0];
	for (i = 1; i < l; ++i) {
		printf("Dividers: %u\n", div[i]);
	}
	free(div);

	fct = primes(a);
	l = fct[0];
	for (i = 1; i < l; ++i) {
		printf("Primes: %u\n", fct[i]);
	}
	free(fct);

	prm = primeFactorization(a);
	l = prm[0];
	for (i = 1; i < l; ++i) {
		printf("Factorization: %u\n", prm[i]);
	}
	free(prm);

	//printf("Do you wish to save the division result? (answer with 1 (Yes) or 2 (No)) ");
	//scanf("%i", &answ);

	if (answ == 1) {
		divisionToFile(a);
	}

	return 0;
}
