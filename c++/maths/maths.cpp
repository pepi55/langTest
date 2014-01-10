#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <math.h>

using namespace std;

float f = 100;
float g = 5;

int isInteger (float a) {
	bool result = false;

	if (fmodf(a, 1) == 0) {
		result = true;
	}

	return result;
}

int isNaturalNumber (float a) {
	bool result = false;

	if (a > 0 && isInteger(a)) {
		result = true;
	}

	return result;
}

int isDivisor (float a, float b) {
	bool result = false;
	float temp = a / b;

	if (isInteger(b / a)) {
		result = true;
	}

	return result;
}

vector<int> divisors (float a) {
	unsigned int i;
	vector<int> result;

	if (isNaturalNumber(a)) {
		for (i = 0; i <= a; ++i) {
			if (isDivisor(i, a)) {
				result.push_back(i);
			}
		}
	}

	return result;
}

vector<int> primes (float a) {
	unsigned int i;
	vector<int> result;

	if (isNaturalNumber(a)) {
		for (i = 0; i <= a; ++i) {
			if (divisors(i).size() == 2) {
				result.push_back(i);
			}
		}
	}

	return result;
}

vector<int> primeFactorization (float a) {
	vector<int> result;
	vector<int> prime = primes(a);

	int i = 0;

	while (a != 1) {
		if (isNaturalNumber(a / prime.at(i))) {
			a /= prime.at(i);
			result.push_back(prime.at(i));
		} else {
			i += 1;
		}
	}

	return result;
}

unsigned gcd (unsigned a, unsigned b) {
	while (b != 0) { unsigned c = a % b; a = b; b = c; }
	return a;
}

int main () {
	unsigned int i;
	unsigned int j;
	unsigned int k;

	cout << "is it an integer? " << isInteger(f);
	cout << "\nis it an natural number? " << isNaturalNumber(f);
	cout << "\nis it an divisor? " << isDivisor(f, g);
	cout << "\nglobal something something of: " << f << " and " << g << " is: " << gcd(f, g);

	cout << "\nwhat are its divisors?";
	for (i = 0; i < divisors(f).size(); ++i)
		cout << " " << divisors(f).at(i);

	cout << "\nprimes to " << f << ":";
	for (j = 0; j < primes(f).size(); ++j)
		cout << " " << primes(f).at(j);

	cout << "\nprime factorization to " << f << ":";
	for (k = 0; k < primeFactorization(f).size(); ++k)
		cout << " " << primeFactorization(f).at(k);

	cout << endl;

	return 0;
}
