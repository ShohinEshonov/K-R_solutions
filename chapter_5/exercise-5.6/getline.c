#include <stdio.h>


#define LIMIT 100

int getLine(char *s, int lim);




int main()
{
	char line[100];
	int len = getLine(line, LIMIT);

	printf("line = %s, len = %d \n", line, len);
	return 0;
}




int getLine(char *s, int lim)
{
	int c, i;

	i = 0;

	while(--lim > 0 && (c = getchar()) != EOF && c != '\0')
	{
		*s++ = c;
		i++;
	}
	if(c == '\n')
	{
		*s++ = c;
		i++;
	}
	*s = '\0';
	return i;
}

