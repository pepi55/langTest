int *division (float a) {
	int i;
	int *divResult = malloc(a * sizeof(long));

	if (naturalNumber(a)) {
		divLength = 0;
		for (i = 0; i < a + 1; i++) {
			if (divisor(i, a)) {
				//divResult = realloc(divResult, sizeof(long));
				divResult[i] = i;
				//divLength += 1;
			}
		}
	}

	free(divResult);
	//printf("Mem: %p\n", (void *)divResult);
	return divResult;
}

int *primes (long a) {
	int i;
	int *primeResult = malloc(a * sizeof(long));

	if (naturalNumber(a)) {
		for (i = 0; i < a + 1; i++) {
			division(i);
			printf("len = %d\n", divLength);
			if (divLength == 2) {
				//primeResult[i] = i;
			}
		}
	}

	free(primeResult);
	return primeResult;
}

void divisionToFile (float a) {
	FILE *f = fopen("divisionResult", "wb+");
	int i, j, k, c, answ = 0;
	char line[100];

	if (f == NULL) {
		printf("\nError loading file!\n");
		exit(EXIT_FAILURE);
	}

	if (naturalNumber(a)) {
		for (i = 0; i < a + 1; i++) {
			if (divisor(i, a)) {
				fprintf(f, "%d\n", i);
			}
		}

		rewind(f);
	}

	printf("Do you wish to print the division result? (answer with 1 (Yes) or 2 (No)) ");
	scanf("%d", &answ);

	if (answ == 1) {
		while (fgets(line, 100, f) != NULL) {
			sscanf(line, "%d", &c);
			printf("%d\n", c);
		}
	}

	fclose(f);
}

int fractGcd (fract a) {
	int result;

	result = gcd(a.numerator, a.denominator);

	return result;
}

int fractReducedNumerator(fract a) {
	int result, gcdOfFract;

	gcdOfFract = fractGcd(a);
	result = a.numerator / gcdOfFract;

	return result;
}

int fractReducedDenominator(fract a) {
	int result, gcdOfFract;

	gcdOfFract = fractGcd(a);
	result = a.denominator / gcdOfFract;

	return result;
}

fract addFraction (fract a, fract b) {
	int denominator;
	int numerator;
	fract result;

	numerator = (a.numerator * b.denominator) + (b.numerator * a.denominator);
	denominator = a.denominator * b.denominator;

	result.numerator = numerator;
	result.denominator = denominator;

	return result;
}
