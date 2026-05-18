#include <stdio.h>

#define MAXLINE 1024

int getLine(char line[], int len);
void printRev(char line[], int len);


int main()
{
	int len;
	char line[MAXLINE];

	while((len = getLine(line, MAXLINE)) > 0)
		printf("%s\n", line);
}


int getLine(char s[], int len)
{
	int c,i; 
	for(i = 0; i < len-1; ++i)
	{

		c = getchar();
		if(c == EOF)
			break;
		if(c == '\n')
			break;
		s[i] = c;
	}
	s[i] = '\0';

	return i;
}




