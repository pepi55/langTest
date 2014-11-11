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

		//fprintf(stdout, "curnum: %i\n", curNum);
		//fprintf(stdout, "prevnum: %i\n", prevNum);
		//fprintf(stdout, "answ: %i\n", answ);
	}

	fprintf(stdout, "The result of problem 1 is: %i\n", answ);
	answ = 0;

	return 0;
}
