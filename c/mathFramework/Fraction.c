#include <stdio.h>
#include <stdlib.h>

#include "maths.h"
#include "Fraction.h"

int fractGcd (fract a) {
	int result;

	result = gcd(a.numerator, a.denominator);

	return result;
}

int fractReducedNumerator(fract a) {
	int result, gcdOfFract;

	gcdOfFract = fractGcd(a);
	result = a.numerator / gcdOfFract;

	return result;
}

int fractReducedDenominator(fract a) {
	int result, gcdOfFract;

	gcdOfFract = fractGcd(a);
	result = a.denominator / gcdOfFract;

	return result;
}

fract addFraction (fract a, fract b) {
	int denominator;
	int numerator;
	fract result;

	numerator = (a.numerator * b.denominator) + (b.numerator * a.denominator);
	denominator = a.denominator * b.denominator;

	result.numerator = numerator;
	result.denominator = denominator;

	return result;
}
