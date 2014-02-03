#include <stdio.h>
#include <time.h>

static unsigned long state[16];
static unsigned int index = 0;

unsigned long WELLRNG512 (void);

int main (void) {
	int i;

	for (i = 0; i < 16; i++) {
		state[i] = rand()^(rand()<<16)^(rand()<<31) * (unsigned int)time(NULL);
	}

	for (i = 0; i < 16; i++) {
		printf("random: %lu\n", WELLRNG512());
	}

	return 0;
}

unsigned long WELLRNG512 (void) {
	unsigned long a, b, c, d;

	a = state[index];
	c = state[(index+13)&15];
	b = a^c^(a<<16)^(c<<15);
	c = state[(index+9)&15];
	c ^= (c>>11);
	a = state[index] = b^c;
	d = a^((a<<5)&0xDA442D24UL);
	index = (index + 15)&15;
	a = state[index];
	state[index] = a^b^d^(a<<2)^(b<<18)^(c<<28);

	return state[index];
}
