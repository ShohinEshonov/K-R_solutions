#include <stdio.h>
#define TABSTOPS 8

int main()
{
	int position, c,spaces;
	
	position = 0;
	while((c = getchar()) != EOF && c != '\n')
	{
		if(c != '\t')
		{	
			++position;
			putchar(c);
		}
		if(c == '\t')
		{
			spaces = TABSTOPS - (position % TABSTOPS);
			for(int i = 0; i < spaces; ++i)
				putchar(' ');
			position += spaces;
		}
	}
	putchar('\n');
	return 0;
}
