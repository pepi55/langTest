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

	fprintf(stdout, "The result is: %i\n", answ);

	return 0;
}
