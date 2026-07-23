#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include "stack.c"


#define NUMBER  '0' 
#define NOT_NUMBER '1'

char validate_number(char *str);
void print_help();


int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		print_help();
		return 0;
	}
	++argv;
	while(--argc > 0) 
	{
		char arg_type = validate_number(*argv);
			
		if(arg_type == NUMBER)
		{
			push(atof(*argv));
			argv++;
			continue;	
		}

		switch (*argv[0]) {
			case '+':
				push(pop()+pop());
				break;
			case '*':
				push(pop()*pop());
				break;
			case '-':
			{
				double op2 = pop();
				push(pop()-op2);
				break;
			}
			case '/':
			{	
				double op2 = pop();
				if(op2 != 0.0)
					push(pop()/op2);
				else
					printf("error: zero divisor\n");
				break;
			}
			case '%':
			{	
				double op2 = pop();
				push(fmod(pop(), op2));
				break;	
			}
			default: 
				printf("Error: Invalid operand/operator %s\n", *argv);
				print_help();
				return 0;
			}
			argv++;		
	}
	if(sp != 1)
	{
		printf("Error: %d unused value(s) on stack\n", sp-1);
	       	return 0;	
	}

	printf("Result: %f\n", top());
	return 0;
}





char validate_number(char *str)
{
	int i = 0;

	if (str[i] == '-' || str[i] == '+')
	{
		char next = str[i+1];

		if(!isdigit(next))
			return NOT_NUMBER;
		i++;
	}

	if(isdigit(str[i]))
		while(isdigit(str[i]))
			i++;
		
	if(str[i] == '.')
	{
		i++;
		while(isdigit(str[i]))
			i++;
	}
	if(str[i] != '\0')
		return NOT_NUMBER;
	return NUMBER;
}

void print_help()
{
	printf("Usage: ./calc arg1 arg2 ... argn  op1 op2 ... opn\n");
	printf("\targ - int/double\n");
	printf("\top  - operator, defined operators +, -, *, /, %%\n");
	printf("Example: ./calc 2 2 +\n");
}
