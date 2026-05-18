#include <stdio.h>

#define MAXLEN 64
#define IN 1
#define OUT 0
#define ONELINE 1
#define MULTILINE 0

int main(){
	int c;
	char stack[MAXLEN];
	int stack_top,line,previous,type,state,quotes_single,quotes_double;
	for(int i = 0; i < MAXLEN; ++i)
		stack[i] = 0;

	stack_top = -1;
	previous = 0;
	line = 1;
	quotes_single = 0;
	quotes_double = 0;
	type = -1;
	state = OUT;
	while((c = getchar()) != EOF)
	{
		if(c == '\n')
			++line;
		if(c == '\'' && state == OUT && quotes_double == 0 && previous != '\\')
		{
			if(quotes_single > 0)
				--quotes_single;
			else
				++quotes_single;
		}
		if(c == '\"' && state == OUT  && quotes_single == 0 && previous != '\\')
		{
			if(quotes_double > 0)
				--quotes_double;
			else
				++quotes_double;
		}
		if((c == '(' || c == '[' || c == '{') && state == OUT && quotes_double == 0 && quotes_single == 0)
			stack[++stack_top] = c;
	          	
		if(previous == '/' && c == '/')
		{
			state = IN;
			type = ONELINE;
		}
		if(state == IN && type == ONELINE && c == '\n')
		{
			state = OUT;
		}
		if(previous == '/' && c == '*')
		{
			state = IN;
			type = MULTILINE;
		}
		if(state == IN && type == MULTILINE && previous == '*' && c == '/')
		{
			state = OUT;
		}
	
			
		if(((c == ']' && stack[stack_top] != '[') || (c == '}' && stack[stack_top] != '{') || (c == ')' && stack[stack_top] != '(')) && state == OUT && quotes_single == 0 && quotes_double == 0) 
		{
			printf("Unclosed parentheses on line: %d, %c\n", line, stack[stack_top]);
			return 69;
		}

		if(((c == ']' && stack[stack_top] == '[') || (c == '}' && stack[stack_top] == '{') || (c == ')' && stack[stack_top] == '(')) && state == OUT)
			--stack_top;
		previous = c;
	}
	if(stack_top != -1)
		printf("Unclosed parentheses: %c\n", stack[stack_top]);
	if(quotes_single > 0)
		printf("Unclosed qoutes: ' \n");
	if(quotes_double > 0) 
		printf("Unclosed quotes \" \n");
	
	if(state == IN && type == ONELINE)
		printf("Undetirminated oneline commentry\n");
	if(state == IN && type == MULTILINE)	
		printf("Undetirminated multiline commentry\n");



	return 0;
}
