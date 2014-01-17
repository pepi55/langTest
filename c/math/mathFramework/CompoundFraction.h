#ifndef COMPOUND_FRACTION_H
#define COMPOUND_FRACTION_H

#include "Fraction.h"

typedef struct CompoundFraction {
	int numerator, denominator, whole;
} cfract;

extern const struct CompoundFractionClass {
	struct CompoundFraction (*new)(int numerator, int denominator, int whole);
} CompoundFraction;

fract compoundFractionToFraction(cfract a);
cfract fractionToCompoundFraction(fract a);

#endif
