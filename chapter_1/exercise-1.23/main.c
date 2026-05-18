#include <stdio.h>
#define IN 1
#define OUT 0
#define ONELINE 2
#define MULTILINE 1 


int main()
{
	int c, state, previous, type;

	state = OUT;
	type = -1;
	previous = 0;
	while((c = getchar()) != EOF)
	{
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
		previous = c;
		if(state == OUT)
		{
			if((previous == '/' && c == '/') || (previous == '/' && c == '*'))
				;
			else if(previous == '/' && c != '/' && c != '*')
			{
				putchar(previous);
				putchar(c);
			}
			else
				putchar(c);
		}
	}
	return 0;
}

