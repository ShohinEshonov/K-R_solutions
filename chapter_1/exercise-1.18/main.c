#include <stdio.h>

#define MAXLINE 1024
#define PRINT_LEN 80

int getLine(char line[], int len);

int main()
{
	int len;
	char line[MAXLINE];

	while((len = getLine(line, MAXLINE)) > 0)
		if(len > PRINT_LEN)
			printf("%s\n", line);
	
	return 0;
}	




int getLine(char line[], int len)
{
	int c, i;

	for(i = 0; i < len && (c = getchar()) != EOF && c != '\n'; ++i)
		line[i] = c;
	
	line[i] = '\0';

	return i;
}

