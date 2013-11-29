#!/usr/bin/python

test = [2, 3, 4, 5, 6, 7]

nominator = int(input('nominator of fracture = '))
denominator = int(input('denominator of fracture = '))

def primes(n):
	priemfac = []
	i = 2
	while i * i <= n:
		while (n % i) == 0:
			priemfac.append(i)
			n /= i
		i += 1
	if n > 1:
		priemfac.append(n)
	return priemfac

def Fracture(n, d):
	if n % 1 == 0 & d % 1 == 0:
		print(primes(n), primes(d))

Fracture(nominator, denominator)
