#include <stdio.h>

#include "SampleHeader.h"

static struct Sample new (int i, int j) {
	return (struct Sample) {
		.i = i, .j = j
	};

}

const struct SampleClass Sample = {
	.new = &new
};
