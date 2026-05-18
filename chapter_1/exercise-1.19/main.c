#include <stdio.h>

#define MAXLINE 1024

int getLine(char line[], int len);
void printRev(char line[], int len);


int main()
{
	int len;
	char line[MAXLINE];

	while((len = getLine(line, MAXLINE)) > 0)
		printRev(line, len);

}


int getLine(char s[], int len)
{
	int c,i; 
	for(i = 0; i < len-1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	
	s[i] = '\0';

	return i;
}

void printRev(char s[], int len)
{
	for(int i = len; i >= 0; --i)
		putchar(s[i]);
	putchar('\n');
}
