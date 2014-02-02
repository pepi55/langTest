#include <stdio.h>
#include <time.h>

/* initialize state to random bits */
static unsigned long state[624];
/* init should also reset this to 0 */
static unsigned int index = 0;

int main (void) {
	int i;

	for (i = 0; i < 16; i++) {
		unsigned long seed = (unsigned long)time(NULL);
		state[i] = (seed + 1) * ((seed + 1) << 2) * i;
		printf("random: %lu\ntime: %lu\n", WELLRNG512, seed); //(unsigned long)time(NULL));
	}

	return 0;
}

/* return 32 bit random number */
unsigned long WELLRNG512(void)
   {
   unsigned long a, b, c, d;
   a = state[index];
   c = state[(index+13)&15];
   b = a^c^(a<<16)^(c<<15);
   c = state[(index+9)&15];
   c ^= (c>>11);
   a = state[index] = b^c;
   d = a^((a<<5)& sizeof(unsigned long) * 8); //0xDA442D24UL
   index = (index + 15)&15;
   a = state[index];
   state[index] = a^b^d^(a<<2)^(b<<18)^(c<<28);
   return state[index];
   }
