#ifndef FRACTION_H
#define FRACTION_H

struct Fraction {
	int numerator, denominator;

	int (*fractGcd)(struct Fraction *this);
	int (*reduced_numerator)(struct Fraction *this);
	int (*reduced_denominator)(struct Fraction *this);
};

extern const struct FractionClass {
	struct Fraction (*new)(int numerator, int denominator);
} Fraction;

#endif
