#include <iostream>
#include <math.h>

using namespace std;

float f = 10;
float g = 5;

int isInteger (float a) {
	bool result = false;

	//cout << "function input: " << a << "\n";

	if (fmodf(a, 1) == 0) {
		result = true;
	}

	return result;
}

int isNaturalNumber (float a) {
	bool result = false;

	cout << "\nfunction input: " << a << "\n";

	if (a > 0 && isInteger(a)) {
		result = true;
	}

	return result;
}

int isDivisor (float a, float b) {
	bool result = false;
	float temp = a / b;

	cout << "\nfunction input: " << temp << "\n";

	if (isInteger(a / b)) {
		result = true;
	}

	return result;
}

int main () {
	cout << "is it an integer? " << isInteger(f);
	cout << "is it an natural number? " << isNaturalNumber(f);
	cout << "is it an divisor? " << isDivisor(f, g);

	return 0;
}
