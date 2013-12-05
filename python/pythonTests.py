#!/usr/bin/python

from math import *
from Fraction import *
from Ratio import *

a = Fraction(1024, 768)
b = Fraction(1280, 1024)
c = multiplyFraction(a, b)
d = divideFraction(a, b)
e = substractFraction(a, b)
f = addFraction(a, b)

ratio = Ratio(f.numerator, f.denominator)
scaled = scaleDivisor(ratio, 500)

#print(c.reduced_numerator, c.reduced_denominator)
#print(d.reduced_numerator, d.reduced_denominator)
#print(e.reduced_numerator, e.reduced_denominator)
#print(f.reduced_numerator, f.reduced_denominator)
print(scaled.divident, scaled.divisor)
