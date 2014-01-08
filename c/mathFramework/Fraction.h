#ifndef FRACTION_H
#define FRACTION_H

typedef struct Fraction {
	int numerator;
	int denominator;
} fract;

int fractGcd(fract a);
int fractReducedNumerator(fract a);
int fractReducedDenominator(fract a);

fract addFraction(fract a, fract b);

#endif
