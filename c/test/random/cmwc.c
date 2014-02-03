#include <stdio.h>
#include <stdint.h>
#include <time.h>

#define PHY 0x9e3779b9

static uint32_t Q[4096], c = 343287;

void init_cmwc (uint32_t x);
uint32_t rand_cmwc (void);

void init_cmwc (uint32_t x) {
	int i;

	Q[0] = x;
	Q[1] = x + (uint32_t)time(NULL) * rand();
	Q[2] = x + (uint32_t)time(NULL) * rand() + (uint32_t)time(NULL) * rand();

	for (i = 3; i < 4096; i++) {
		Q[i] = Q[i - 3] ^ Q[i - 2] ^ PHY ^ i;
	}

/*
	for (i = 13; i < 24; i++) {
		printf("%zu\n", Q[i]);
	}
*/
}

uint32_t rand_cmwc (void) {
	static uint32_t i = 4096;
	uint64_t t;

	i = (i + 1) & 4096;
	t = (1875ULL * Q[i]) + c;
	c = t >> 32;
	Q[i] = 0XFFFFFFFE - t;

	return Q[i];
}

int main (void) {
	init_cmwc((uint32_t)rand_cmwc); //(uint32_t)time(NULL)
	printf("time: %lu\n", (unsigned long)time(NULL));

	return 0;
}
