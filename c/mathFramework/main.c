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
	fract fraction1, fraction2, fractionSum, reducedFraction;
	int gcdOfFract;

	printf("Insert first number to be manipulated: ");
	scanf("%f", &a);

	printf("Insert second number to be manipulated: ");
	scanf("%f", &b);

	fputs(integer(a) ? "The first number is an integer.\n" : "The first number is not an integer.\n", stdout);
	fputs(naturalNumber(a) ? "The first number is a natural number.\n" : "The first number is not a natural number.\n", stdout);
	fputs(divisor(a, b) ? "The first number is a divisor.\n" : "The first number is not a divisor.\n", stdout);

	printf("greatest common divider of %i and %i: %i\n", (int) a, (int) b, gcd(a, b));

	fraction1.numerator = a;
	fraction1.denominator = b;
	fraction2.numerator = a * 2;
	fraction2.denominator = b * 2;

	fractionSum = addFraction(fraction1, fraction2);
	reducedFraction.numerator = fractReducedNumerator(fractionSum);
	reducedFraction.denominator = fractReducedDenominator(fractionSum);
	gcdOfFract = fractGcd(fraction1);

	printf("numerator: %i, denominator: %i\n", fraction1.numerator, fraction1.denominator);
	printf("add fraction: numerator is %i, denominator is %i\n", fractionSum.numerator, fractionSum.denominator);
	printf("greatest common divider: %i\n", gcdOfFract);
	printf("reduced fraction: numerator %i, denominator %i\n", reducedFraction.numerator, reducedFraction.denominator);

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

	printf("Do you wish to save the division result? (answer with 1 (Yes) or 2 (No)) ");
	scanf("%i", &answ);

	if (answ == 1) {
		divisionToFile(a);
	}

	return 0;
}
