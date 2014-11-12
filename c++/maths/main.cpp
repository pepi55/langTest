#include <stdio.h>
#include <stdlib.h>

#include "maths.h"

int main (void) {
	int answ = 0;

	for (int i = 0; i < 1000; ++i) {
		if (i % 3 == 0) {
			answ += i;
		} else if (i % 5 == 0) {
			answ += i;
		}
	}

	fprintf(stdout, "The result of problem 1 is: %i\n", answ);
	answ = 0;

	int prevNum = 0,
			curNum = 1,
			nextNum = curNum + prevNum;

	while (nextNum <= 4000000) {
		prevNum = curNum;
		curNum = nextNum;

		nextNum = curNum + prevNum;

		if (curNum % 2 == 0) {
			answ += curNum;
		}
	}

	fprintf(stdout, "The result of problem 2 is: %i\n", answ);
	answ = 0;

	//int num = 13195;
	//for (int i = 2; i < num; i++) {
	//	if (num % i == 0 && i != num) {
	//		answ = i;
	//	}
	//}
	//unsigned long large = 600851475143;
	unsigned long small = 13195;

	unsigned long *primes = primeFactorization(small);
	fprintf(stdout, "The result of problem 3 is: %lu\n", primes[primes[0] - 1]);
	free(primes);

	//fprintf(stdout, "The result of problem 3 is: %i\n", answ);
	//answ = 0;

	return 0;
}
