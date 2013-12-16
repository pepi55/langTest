#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <math.h>

using namespace std;

float f = 10;
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
	vector<int> result;

	if (isNaturalNumber(a)) {
		for (int i = 0; i <= a; ++i) {
			if (isDivisor(i, a)) {
				result.push_back(i);
			}
		}
	}

	return result;
}

int main () {
	unsigned int i;

	cout << "\nis it an integer? " << isInteger(f);
	cout << "\nis it an natural number? " << isNaturalNumber(f);
	cout << "\nis it an divisor? " << isDivisor(f, g);

	cout << "\nwhat are its divisors?";
	for (i = 0; i < divisors(f).size(); ++i)
		cout << " " << divisors(f).at(i);

	cout << endl;

	return 0;
}
