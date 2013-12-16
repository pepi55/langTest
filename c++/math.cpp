#include <iostream>
#include <math.h>

using namespace std;

float a;
float f = 12.3;

float isInteger (float a) {
	bool result = false;

	cout << a << "\n";

	if (a % 1 == 0) {
		result = true;
	}

	return result;
}

int main () {
	cout << isInteger(f);
	//cout << "\n" << f;

	return 0;
}
