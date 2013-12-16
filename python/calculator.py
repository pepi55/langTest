#!/usr/bin/python

from maths import *
from Fraction import *
from Ratio import *

# Divisor = bottom, divident = top

action = int(input("\n1. Scale divisor\n2. Scale divident\n3. Multiply fraction\n4. Divide fraction\n5. Add fraction\n6. Substract fraction\n7. Convert ratio to fraction\n\nChoose an option: "))

if action == 1:
  ratioDivident = float(input("Desired divident: "))
  ratioDivisor = float(input("Desired divisor: "))
  dividentToScale = float(input("Divident to scale with: "))
  ratio = Ratio(ratioDivident, ratioDivisor)

  scaleRatio = scaleDivisor(ratio, dividentToScale)
  print(scaleRatio.divident, scaleRatio.divisor)

if action == 2:
  ratioDivident = float(input("Desired divident: "))
  ratioDivisor = float(input("Desired divisor: "))
  divisorToScale = float(input("Divisor to scale with: "))
  ratio = Ratio(ratioDivident, ratioDivisor)

  scaleRatio = scaleDivident(ratio, divisorToScale)
  print(scaleRatio.divident, scaleRatio.divisor)

#a = Fraction(1024, 768)
#b = Fraction(1280, 1024)
#c = multiplyFraction(a, b)
#d = divideFraction(a, b)
#e = substractFraction(a, b)
#f = addFraction(a, b)
#g = Ratio(16, 10)
#
#ratio = Ratio(f.numerator, f.denominator)
#scaled = scaleDivisor(g, 960)
#
#print(scaled.divident, scaled.divisor)
