#!/usr/bin/python
from maths import *

class CompoundFraction:
  def __init__(self, numerator, denominator, whole):
    self.numerator = numerator
    self.denominator = denominator
    self.whole = whole

def compoundFractionToFraction(cf):
  result = Fraction(cf.whole * cf.denominator + cf.numerator, cf.denominator)
  return result

def fractionToCompoundFraction(f):
  whole = math.floor(f.numerator / f.denominator)
  numerator = f.numerator % f.denominator
  denominator = f.denominator
  result = CompoundFraction(whole, numerator, denominator)
  return result
