#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

int x = 6;				/*Max digits*/
int max = 9999999;		/*Max number*/

/*
	Prompts the user for an 'input', and determines if 'input' 
	is at most a 'x' digit number. If 'input' is invalid,
	prompt the user to try again. Returns a 'x' digit 'input'.
*/
int		xdigits()
{
	int		input;
	int		i;

	printf("Enter up to a %d digit number: ", x);
	for (i = 1; scanf("%d", &input) < 0 || input > max || input < 0; i++)
	{
		if (i == 1)
		{
			printf("Oops, try 1 more time.\nEnter up to a %d digit number: ", x);
		}
		else
		{
			printf("Oops, try %d more times.\nEnter up to a %d digit number: ", i, x);
		}
		fflush(stdin);
	}
	return (input);
}

/*
	Raises 'base' to the power of 'exponent'.
	Returns the product.
*/
int		power(int base, int exponent)
{
	int		product;

	product = base;
	while (exponent-- > 1)
		product *= base;
	return product;
}

/*
	Determines if 'input' is an Armstrong number.
	Returns 1 on true, 0 on false.
*/
int 	is_armstrong(int input)
{
	int		original;
	int		remainder;
    int		sum;
	int		digits;
	
	sum = 0;
	digits = 0;

	for (original = input; original != 0; digits++)
		original = original/10;
	original = input;
	while (original != 0)
	{
		remainder = original%10;
		sum += power(remainder, digits);
		if (sum > input)
			return 0;
		original = original/10;
	}
	if (sum == input)
		return 1;
	return 0;
}

/*
	Calculates if y or n was inputted by the user.
	Parameters call for 'question' string to print.
	Returns 1 for yes, 0 for no.
*/
int		yorn(char *question)
{
	char	try_again;
	
	while (scanf(" %c", &try_again) < 1 || try_again != 'y' && try_again != 'n' && try_again != 'Y' && try_again != 'N')
		{
			printf("INVALID INPUT\n");
			printf(question);
			printf(" y/n: ");
			fflush(stdin);
		}
	if (try_again == 'y' || try_again == 'Y')
		return 1;
	return 0;
}

/*
	'Guess_armstrong' the game where you input a number, and the computer
	tells you if you are right or wrong. Returns 0 on completion.
*/
int		guess_armstrong()
{
	int		input;
	int		try_again;

	try_again = 1;
	while (try_again)
	{
		input = xdigits();
		if (is_armstrong(input))
			printf("~\n%d is an Armstrong number.\n~\n", input);
		else
			printf("~\n%d is not an Armstrong number.\n~\n", input);
		printf("\nWould you like to try a new number? y/n: ");
		try_again = yorn("Would you like to try a new number?");
	}
	return 0;
}

/*
	Calculates Armstrong numbers. Prints them to the standard output.
	Returns 0 on completion.
*/
int		cal_strong(int start, int i)
{
	
	while (!is_armstrong(start) && start < max)
		start++;
	if (start == max)
	{
		printf("\n~\nLimit reached\n~\n\nTry again? y/n: ");
		if (yorn("Try again?"))
			{
				printf("Too Bad.");
				sleep(3);
			}
		return 0;
	}
	printf("%d is Armstrong number #%d\n~\n", start, i);
	cal_strong(++start, ++i);
	return 0;
}

// Returns n-digits of a number when calculating log base 10 of input number then rounds up
int		count_digits(int n) {
	switch (n)
	{
	case 0:
		return 1;
	default:
		return (log10(abs((double)(n))) + 1);
		break;
	}
}

int		cal_strong_n(int start, int n) {
	while (!is_armstrong(start) && start < max)
		start++;
	if (start == max)
	{
		printf("\n~\nLimit reached\n~\n\nTry again? y/n: ");
		if (yorn("Try again?"))
			{
				printf("Too Bad.");
				sleep(3);
			}
		return 0;
	}
	if (count_digits(start) != n) {
		n = count_digits(start);
		printf("\nn=%d: ",n);
	} else {
		printf(", ");
	}
	printf("%d", start);
	cal_strong_n(++start, n);
	return 0;
}
/*
	Main. Educates the user on using the program, launches the desired
	functions, and returns the user to the "menu" upon completion.
*/

int 	main()
{
	int		input;

	input = 0;
	while (input != 4)
	{
		printf("An Armstrong number is equal to the sum of the products\nof its digits raised to the power of the total number of digits.\nI'm too tired to figure out this sentence rn.\nIf you don't know what it is Google it.\n\n");
		printf("Would you like to\n(1) Guess an Armstrong number\n(2) Calculate Armstrong numbers\n(3) List Armstrong numbers grouped by the same n-digit number\n(4) Quit\n~\n");
		while (scanf("%d", &input) == EOF || input > 4 || input < 1)
		{
			printf("Oops, try again.\nWould you like to\n(1) Guess an Armstrong number\n(2) Calculate Armstrong numbers\n(3) List Armstrong numbers grouped by the same n-digit number\n(4) Quit\n~\n");
			fflush(stdin);
		}
		if (input == 1)
			guess_armstrong();
		if (input == 2)
		{
			cal_strong(0,1);
		}
		if (input == 3)
		{
			cal_strong_n(0, 0);
		}
	}
	return 0;
}