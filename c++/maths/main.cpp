#include <stdio.h>

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

	for (int i = 0; i < 4000000; ++i) {

	}

	return 0;
}
