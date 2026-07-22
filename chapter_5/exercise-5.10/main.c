#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include "stack.c"




char validate_str(char *str);
void print_help();






int main(int argc, char *argv[])
{
	while(--argc > 0 && (isdigit((*++argv)[0]) || (*argv)[0] == '.'))
	{
		char is_number = validate_str(*argv);
		if(is_number == 1)
		{
			printf("Error: Invalid argument %s\n", *argv);
			argc = 0;
			break;
		}
		else
			push(atof(*argv));
	}

	if(argc == 0)
	{
		print_help();
		return 0;
	}
	else
	{
		while(*argv != NULL)
		{
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
					printf("Error: Invalid operator\n");
					print_help();
					return 0;

			}
			argv++;	
		}	
		printf("Result: %f\n", top());
	}
	return 0;
}





char validate_str(char *str)
{
	int i = 0;

	if (str[i] == '-' || str[i] == '+')
		i++;


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
		return 1;
	return 0;
}

void print_help()
{
	printf("Usage: ./calc arg1 arg2 ... argn  op1 op2 ... opn\n");
	printf("\targ - int/double\n");
	printf("\top  - operator, defined operators +, -, *, /, %\n");
	printf("Example: ./calc 2 2 +\n");
}
