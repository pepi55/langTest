#include <stdio.h>
#include <math.h>

#include "CompoundFraction.h"

static struct CompoundFraction new (int numerator, int denominator, int whole) {
	return (struct CompoundFraction) {
		.numerator = numerator, .denominator = denominator, .whole = whole
	};
}

const struct CompoundFractionClass CompoundFraction = {
	.new = &new
};

fract compoundFractionToFraction(cfract a) {
	return Fraction.new(a.whole * a.denominator + a.numerator, a.denominator);
}

cfract fractionToCompoundFraction(fract a) {
	return CompoundFraction.new(fmod(a.numerator, a.denominator), a.denominator, floor(a.numerator / a.denominator));
}
