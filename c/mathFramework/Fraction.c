#include <stdio.h>
#include <stdlib.h>

#include "maths.h"
#include "Fraction.h"

FRACTION Fraction;

int FractionNum (int numerator) {
	Fraction.numerator = numerator;

	return numerator;
}

int FractionDen (int denominator) {
	Fraction.denominator = denominator;

	return denominator;
}

int FractionGcd (void) {
	Fraction.fractGcd = gcd(Fraction.numerator, Fraction.denominator);

	return 0;
}

int FractionRen (void) {
	Fraction.reduced_numerator = Fraction.numerator / Fraction.fractGcd;

	return 0;
}

int FractionRed (void) {
	Fraction.reduced_denominator = Fraction.denominator / Fraction.fractGcd;

	return 0;
}
