#include <stdio.h>
#include <math.h>

#include "SampleHeader.h"

static int abs(struct Sample *this) {
	return sqrt(this->i * this->j + this->j * this->j);
}

static struct Sample new (int i, int j) {
	return (struct Sample) {.i = i, .j = j, .abs = &abs};
}

const struct SampleClass Sample = {
	.new = &new
};
