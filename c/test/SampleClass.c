//System headers
#include <stdio.h>
#include <math.h>
#include <stdint.h>

//Custom headers
#include "SampleHeader.h"

//Randomization
static unsigned long state[16];
static unsigned int index = 0;

unsigned long ran (void) {
	unsigned long a, b, c, d;

	a = state[index];
	c = state[(index + 13) & 15];
	b = a^c^(a << 16)^(c << 15);
	c = state[(index + 9) & 15];
	c ^= (c >> 11);
	a = state[index] = b^c;
	d = a^((a << 5) & 0xDA442D24UL); //0xDA442D24UL
	index = (index + 15) & 15;
	a = state[index];
	state[index] = a^b^d^(a << 2)^(b << 18)^(c << 28);

	return state[index];
}

static int absolute(struct Sample *this) {
	return sqrt(this->i * this->j + this->j * this->j);
}

static struct Sample new (int i, int j) {
	return (struct Sample) {.i = i, .j = j, .absolute = &absolute};
}

const struct SampleClass Sample = {
	.new = &new
};
