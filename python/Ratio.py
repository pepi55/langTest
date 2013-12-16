#!/usr/bin/python
from maths import *

class Ratio:
	def __init__(self, divident, divisor = 1):
		self.divident = divident
		self.divisor = divisor

def scaleDivident(a, divisor):
	divident = a.divident * divisor / a.divisor
	divisor = divisor
	return Ratio(divident, divisor)

def scaleDivisor(a, divident):
	divident = divident
	divisor = a.divisor * divident / a.divident
	return Ratio(divident, divisor)
