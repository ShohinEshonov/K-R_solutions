#include <stdio.h>
#include <ctype.h>

int getword(char *, int);
int getch(void);
void ungetch(int);

#define BUFSIZE 10
int bufp = 0;
char buf[BUFSIZE];

int main()
{
	char word[100];
	
	while((getword(word, 100)) != EOF)
		printf("[WORD]: %s\n", word);
	
	return 0;
}

int getword(char *dst, int lim)
{
	int c;
	char *w = dst;

	while(isspace(c = getch()))
		;

	if(c != EOF)
		*w++ = c;

	if(c == '#')
	{
		while((c = getch()) != '\n' && c != EOF);
		return getword(dst, lim);
	}

	if(c == '/')
	{	
		int next = getch();
		if(next == '/')
		{
			while((c = getch()) != '\n' && c != EOF);
			return getword(dst, lim);
		}
		else if(next == '*')
		{
			while((c = getch()) != EOF)
			{
				if(c == '*') 
				{
					if((next = getch()) == '/') break;
					else ungetch(next);
				};
			}
			return getword(dst, lim);

		}
		ungetch(next);
	}
	
	if(c == '\"' || c == '\'')
	{
		int quote = c;
		while((c = getch()) != EOF)
		{
			if(c == '\\')
			{
				int next = getch();
				if(next == EOF)
					ungetch(next);
			}

			else if(c == quote)
				break;
		}
		return getword(dst, lim);
	}

	if(!isalpha(c) && c != '_')
	{
		*w = '\0';
		return c;
	}

	for(; --lim > 0; w++)
	{
		if(!isalnum(*w = getch()) && *w != '_')
		{
			ungetch(*w);
			break;
		}
	}
	 *w = '\0';
	 return dst[0];


}

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if(bufp >= BUFSIZE)
	{
		printf("Ungetch: Buffer overflow\n");
		return;
	}
	buf[bufp++] = c;
}
