#!/usr/bin/python
from maths import *

class Fraction:
	def __init__(self, numerator, denominator):
		self.numerator = numerator
		self.denominator = denominator
		self.gcd = gcd(self.numerator, self.denominator)
		self.reduced_numerator = int(self.numerator / self.gcd)
		self.reduced_denominator = int(self.denominator / self.gcd)

def addFraction(a, b):
	numerator = a.numerator * b.denominator + b.numerator * a.denominator
	denominator = a.denominator * b.denominator
	result = Fraction(numerator, denominator)
	return result

def multiplyFraction(a, b):
	numerator = a.numerator * b.numerator
	denominator = a.denominator * b.denominator
	result = Fraction(numerator, denominator)
	return result

def divideFraction(a,b):
	numerator =  b.denominator * a.numerator 
	denominator = a.denominator * b.denominator
	result = Fraction(numerator,denominator)
	return result

def substractFraction(a, b):
	numerator = a.numerator * b.denominator - b.numerator * a.denominator
	denominator = a.denominator * b.denominator
	result = Fraction(numerator,denominator)
	return result

def ratioToFraction(a):
	if not isInteger(a.divident) or not isInteger(a.divisor):
		a.divident *= 10
		a.divisor *= 10
		ratioToFraction(a)
	result = Fraction(int(a.divident), int(a.divisor))
	return result
