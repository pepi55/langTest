#!/usr/bin/python

num = int(input('Calculate prime numbah\'s fo\' dis b*tch ==> '))
result = []

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

numbers = set(range(num, 1, -1))
primes = []

while numbers:
	p = numbers.pop()
	primes.append(p)
	numbers.difference_update(set(range(p*2, num+1, p)))

for i in primes:
	num = num / i
	print(i)
	print('number = ', num)
	if num % 1 == 0:
		result.append(i)

print('primes = ', primes)
print('result = ', result)

#while (temp != 1)
#  {
#   if(isNatuurlijkGetal(temp/primes[i]))
#   {
#   //console.log(primes2[i]);
#   temp = temp/primes[i];
#   out.push(primes[i]);
#   }else{
#    i++
#   }
#  }
