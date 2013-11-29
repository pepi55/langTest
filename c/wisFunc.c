#include <stdio.h>
#include <stdbool.h>
#include <math.h>

float num1 = 0;
float num2 = 0;

int isWholeNumber();
int isNaturalNumber();
int isDivisor();
int fracture();

int main(int argc, char *argv[])
{
	isWholeNumber();
	isNaturalNumber();
	isDivisor();
	fracture();

	return 0;
}

int fracture()
{
	int nominator = 0;
	int denominator = 0;
}

int isDivisor()
{
	bool divisor = 0;

	printf("\nInsert number first number (the one who will be divided): ");
	scanf("%f", &num1);

	printf("Insert divisor: ");
	scanf("%f", &num2);

	float num3 = num1 / num2;

	if (fmod(num3, 1) == 0)
	{
		divisor = 1;	
	} else {
		divisor = 0;
	}

	fputs(divisor ? "true the number is a divisor" : "false the number is not a divisor", stdout);

	return 0;
}

int isWholeNumber()
{
	bool wholeNum = 0;

	printf("Insert number to see if its a whole number: ");
	scanf("%f", &num1);

	if (fmod(num1, 1) == 0)
	{
		wholeNum = 1;
	} else {
		wholeNum = 0;
	}

	fputs(wholeNum ? "true" : "false", stdout);

	return 0;
}

int isNaturalNumber()
{
	bool natNum = 0;

	printf("\nInsert number to see if its a natural number: ");
	scanf("%f", &num1);

	if (fmod(num1, 1) == 0 && num1 >= 1)
	{
		natNum = 1;
	} else {
		natNum = 0;
	}

	fputs(natNum ? "true" : "false", stdout);
	
	return 0;
}
