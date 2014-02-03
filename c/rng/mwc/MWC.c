#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

typedef struct {
	uint32_t seed;
	uint32_t m;
	uint32_t a;
	uint32_t b;
} lcd;

lcd lcg (lcd src);

lcd lcg (lcd src) {
	uint64_t newseed = src.seed;
	newseed *= src.a;
	newseed += src.b;

	src.seed = newseed % src.m;

	return src;
}

int main (void) {
	lcd src;

	srand((unsigned int)time(NULL));

	src.seed = (uint32_t)time(NULL);
	src.m = /*3 * */rand() * (uint32_t)time(NULL);
	src.a = 5 * (uint32_t)time(NULL);
	src.b = 9 * (uint32_t)time(NULL);

	lcd randoms = lcg(src);

	printf("time: %u\n", (uint32_t)time(NULL));
	printf("seed: %u\nmodulo: %u\nmultuply: %u\nadd: %u\n", randoms.seed, randoms.m, randoms.a, randoms.b);

	return 0;
}
