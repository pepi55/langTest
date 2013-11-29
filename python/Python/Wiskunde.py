def isInteger(a):
    result = False
    if a%1 == 0:
        result = True
    return result

def isNaturalNumber(a):
    result = False
    if(a>0 and isInteger(a)):
        result = True
    return (result)

def isDivisorOf(a,b):
    result = False
    if(isInteger(b/a)):
        result = True
    return(result)
    
def divisor(a):
    result = []
    if(isNaturalNumber(a)):
        for i in range(1,a+1):
            if(isDivisorOf(i,a)):
               result.append(i)
        return(result)
    
def primes(a):
    result = []
    if(isNaturalNumber(a)):
        for i in range(1,a):
            if len(divisor(i)) == 2:
                result.append(i)
    return result

def primeFactorization(a):
    result = []
    prime = primes(a)
    i = 0;
    while(a != 1):
        if(isNaturalNumber(a/prime[i])):
           a = a/ prime[i]
           result.append(prime[i])
        else:
           i=i+1
    return result

def gcd(a,b):
    while a:
        a,b = b%a, a
    return b

class Fraction:
    def __init__(self, numerator, denominator):
        self.numerator = numerator
        self.denominator = denominator
        self.gcd = gcd(self.numerator,self.denominator)
        self.reduced_numerator = int(self.numerator/self.gcd)
        self.reduced_denominator = int(self.denominator/self.gcd)

def addFraction(a,b):
    numerator = a.numerator * b.denominator + b.numerator * a.denominator
    denominator = a.denominator * b.denominator
    result = Fraction(numerator,denominator)
    return result

def substractFraction(a,b):
    numerator = a.numerator * b.denominator - b.numerator * a.denominator
    denominator = a.denominator * b.denominator
    result = Fraction(numerator,denominator)
    return result

def multiplyFraction(a,b):
    numerator = a.numerator * b.numerator 
    denominator = a.denominator * b.denominator
    result = Fraction(numerator,denominator)
    return result

def divideFraction(a,b):
    numerator =  b.denominator * a.numerator 
    denominator = a.denominator * b.denominator
    result = Fraction(numerator,denominator)
    return result

class Ratio():
	def __init__(self, dividend, divisor):
			self.dividend = dividend
    	self.divisor = divisor

def scaleWidth(a, height):
	dividend = a.dividend * height / a.divisor
	divisor = height
	return Ratio(dividend, divisor)

a = Fraction(4, 3)
b = Fraction(16, 9)
c = addFraction(a, b)
print(c.reduced_numerator, c.reduced_denominator)
