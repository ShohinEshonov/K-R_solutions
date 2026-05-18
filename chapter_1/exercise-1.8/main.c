#include <stdio.h>



int main()
{
	int c, tabs, blanks, new_l;
	tabs = 0;
	blanks = 0;
	new_l = 0;
	
	while((c = getchar()) != EOF)
	{
		if(c == '\t')
			++tabs;
		if(c == ' ')
			++blanks;
		if(c == '\n')
			++new_l;
	}

	printf("blanks: %d\ntabs: %d\nnew_lines: %d\n", blanks, tabs, new_l);
	return 0;
}
