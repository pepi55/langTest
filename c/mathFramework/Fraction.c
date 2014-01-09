#include <stdio.h>
#include <stdlib.h>

#include "maths.h"
#include "Fraction.h"

static int reduced_numerator (struct Fraction *this) {
	return this->numerator / gcd(this->numerator, this->denominator);
}

static int reduced_denominator (struct Fraction *this) {
	return this->denominator / gcd(this->numerator, this->denominator);
}

static int fractGcd (struct Fraction *this) {
	return gcd(this->numerator, this->denominator);
}

static struct Fraction new (int numerator, int denominator) {
	return (struct Fraction) {
		.numerator = numerator, .denominator = denominator, .fractGcd = &fractGcd, .reduced_numerator = &reduced_numerator, .reduced_denominator = &reduced_denominator
	};
}

const struct FractionClass Fraction = {
	.new = &new
};

fract addFraction (struct Fraction a, struct Fraction b) {
	int numerator, denominator;
	fract result;

	numerator = a.numerator * b.denominator + b.numerator * a.denominator;
	denominator = a.denominator * b.denominator;
	result = Fraction.new(numerator, denominator);

	return result;
}

fract subtractFraction (struct Fraction a, struct Fraction b) {
	int numerator, denominator;
	fract result;

	numerator = a.numerator * b.denominator - b.numerator * a.denominator;
	denominator = a.denominator * b.denominator;
	result = Fraction.new(numerator, denominator);

	return result;
}
