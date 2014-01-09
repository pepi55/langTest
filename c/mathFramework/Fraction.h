#ifndef FRACTION_H
#define FRACTION_H

typedef struct Fraction {
	int numerator, denominator;

	int (*fractGcd)(struct Fraction *this);
	int (*reduced_numerator)(struct Fraction *this);
	int (*reduced_denominator)(struct Fraction *this);
} fract;

extern const struct FractionClass {
	struct Fraction (*new)(int numerator, int denominator);
} Fraction;

fract addFraction(struct Fraction a, struct Fraction b);
fract subtractFraction(struct Fraction a, struct Fraction b);

#endif
