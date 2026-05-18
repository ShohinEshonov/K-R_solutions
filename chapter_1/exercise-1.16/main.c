#include <stdio.h>
#define MAXLINE 10

int getLine(char line[], int maxline);
void copy(char to[], char from[]);

int main()
{
	int len;
	int max;
	char line[MAXLINE];
	char longest[MAXLINE];

	max = 0;
	while ((len = getLine(line, MAXLINE)) > 0)
		if (len > max) {
			max = len;
			copy(longest, line);
		}
	if (max > 0) {
		printf("%s\n", longest);
		printf("length %d", max);
	}
	return 0;
}



int getLine(char s[], int lim)
{
	int c, i, len;

	len = 0;
	for(i = 0; (c = getchar()) != EOF && c != '\n'; ++i)
	{
		if(len < lim - 1) {
			s[len] = c;
			++len;
		}
	}
	
	s[len] = '\0';
	return i;
}


void copy(char to[], char from[])
{
	int i;

	i = 0;
	while((to[i] = from[i]) != '\0')
		++i;
}




