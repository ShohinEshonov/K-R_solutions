#include <stdio.h>

#define TABSTOP 8

int main()
{
	int c, position, blanks, tabs, spaces;

	position = 0;
	blanks = 0;
	while((c = getchar()) != EOF && c != '\n')
	{
		if(c == ' ')
		{
			++blanks;
		}
		else if(c == '\t')
		{
			if(blanks > 0)
			{
				while(blanks > 0)
				{
					spaces = TABSTOP - (position % TABSTOP);
					if(blanks >= spaces)
					{
						putchar('\t');
						position += spaces;
						blanks -= spaces;
					}
					else
					{
						putchar(' ');
						++position;
						--blanks;
					}
				}
			}
			putchar('\t');
			position += TABSTOP - (position % TABSTOP);
		}
		else
		{
			if(blanks > 0)
			{
				while(blanks > 0)
				{
					spaces = TABSTOP - (position % TABSTOP);
					if(blanks >= spaces)
					{
						putchar('\t');
						position += spaces;
						blanks -= spaces;
					}
					else
					{
						putchar(' ');
						++position;
						--blanks;
					}
				}
			}
			++position;
			putchar(c);
		}
	}
	while(blanks > 0)
	{
   		putchar(' ');
    		--blanks;
	}
	return 0;
}
