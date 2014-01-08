#ifndef SAMPLE_CLASS_H
#define SAMPLE_CLASS_H

struct Sample {
	int i, j;
};

extern const struct SampleClass {
	struct Sample (*new)(int i, int j);
} Sample;

#endif
