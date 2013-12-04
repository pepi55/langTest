#!/usr/bin/python

from math import *
from Fraction import *

a = Fraction(1, 2)
b = Fraction(2, 5)
c = multiplyFraction(a, b)
d = divideFraction(a, b)
e = substractFraction(a, b)
f = addFraction(a, b)

print(c.reduced_numerator, c.reduced_denominator)
print(d.reduced_numerator, d.reduced_denominator)
print(e.reduced_numerator, e.reduced_denominator)
print(f.reduced_numerator, f.reduced_denominator)
