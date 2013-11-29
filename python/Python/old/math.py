#!/usr/bin/python

def isInteger(a):
	result = False
	if a % 1 == 0:
		result = True
	return result

def isNaturalNum(a):
	result = False
	if a > 0 and isInteger(a):
		result = True
	return result

def isDivisorOf(a, b):
	result = False
	if isInteger(b / a):
		result = True
	return result

def divisors(a):
	result = []
	if isNaturalNum(a):
		for i in range(1, a + 1):
			if isDivisorOf(i, a):
				result.append(i)
	return result

def primes(a):
	result = []
	if isNaturalNum(a):
		for i in range(1, a + 1):
			if len(divisors(i)) == 2:
				result.append(i)
	return result

print(primes(1080))
