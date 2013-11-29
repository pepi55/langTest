#!/usr/bin/python

action = int(input('You want to: 1. add, 2. divide, 3. multiply? '))

def plus(n):
	num2 = float(input('Insert number to add: '))
	result = n + num2
	return result

def divide(n):
	num2 = float(input('Insert number to divide with: '))
	result = n / num2
	return result

def multiply(n):
	num2 = float(input('Insert number to multiply with: '))
	result = n * num2
	return result

if action == 1:
	num = float(input('Insert number to manipulate: '))
	print(plus(num))
if action == 2:
	num = float(input('Insert number to manipulate: '))
	print(divide(num))
if action == 3:
	num = float(input('Insert number to manipulate: '))
	print(multiply(num))
