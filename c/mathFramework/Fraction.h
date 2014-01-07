#ifndef FRACTION_H
#define FRACTION_H

typedef struct Fraction {
	int numerator;
	int denominator;

	int fractGcd;
	int reduced_numerator;
	int reduced_denominator;
} FRACTION;

int FractionNum (int numerator);
int FractionDen (int denominator);

int FractionGcd (void);

int FractionRen (void);
int FractionRed (void);

#endif
