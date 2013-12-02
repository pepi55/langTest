#!/usr/bin/python

from math import *
from Fraction import *

a = Fraction(1, 2)
b = Fraction(2, 5)
c = multiplyFraction(a, b)

print(c.reduced_numerator, c.reduced_denominator)
