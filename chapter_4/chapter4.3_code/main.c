#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "calc.h"

#define MAXOP 100 
 
void push(double);
double pop(void);
void identifier_handler(char *s);

int main()
{
	int type;
	double op2;
	char s[MAXOP];
	char token[MAXOP];
	double variables[26] = { -1.0 };
	char var = -1; 
	double recent_top = 0;
	
	while(getLine(s, MAXOP) > 0) {
		while((type = getop(s, token)) != EOF)
		{
			switch(type){
				case NUMBER:
					push(atof(token));
					break;
				case '+':
					push(pop()+pop());
					break;
				case '*':
					push(pop()*pop());
					break;
				case '-':
					op2 = pop();
					push(pop()-op2);
					break;
				case '/':
					op2 = pop();
					if(op2 != 0.0)
						push(pop()/op2);
					else
						printf("error: zero divisor\n");
					break;
				case '%':
					op2 = pop();
					push(fmod(pop(), op2));
					break;
				case '=':
					if(isupper(var))
					{
						pop();
						variables[var - 'A'] = pop();
						break;
					}
					else
					{
						printf("error: invalid variable name");
						break;
					}
				case '_':
					push(recent_top);
					break;
				case IDENTIFIER:
					identifier_handler(token);
					break;
				case VARIABLE:
					var = token[0];
					push(variables[var-'A']);				
					break;
				case '\n':
					recent_top = pop();
					printf("\t%.8g\n", recent_top);
					goto break_loop;
				default:
					printf("error: unknown command %s\n", s);
					break;
				}
		}
		break_loop:;
	}
	return 0;
}




void  identifier_handler(char *s)
{
	if(strcmp(s, "dup") == 0)
	{
		dup();
		return;
	}
	if(strcmp(s, "swap") == 0)
	{
		swap();
		return;
	}
	if(strcmp(s, "clear") == 0)
	{
		clear();
		return;
	}
	if(strcmp(s,  "top") == 0)
	{
		printf("\t%.8g\n", top());
		return;
	}
	if(strcmp(s, "sin") == 0)
	{
		double val = pop();
		push(sin(val));
		return;
	}
	if(strcmp(s,"cos") == 0)
	{
		double val = pop();		
		push(cos(val));
		return;
	}
	if(strcmp(s,  "pow") == 0)
	{	
		double power = pop();
		double val   = pop();
		push(pow(val, power));
		return;
	}
	if(strcmp(s,  "exp")==0)
	{
		double power  = pop();
		push(expf(power));
		return;
	}
	printf("error: unknown identifier/function, %s", s);
	
}




