#include <ctype.h>
#include <stdio.h>

#define SIZE 10
#define BUFSIZE 100





int buf[BUFSIZE];
int bufp = 0;

int getint(int *pn);
int getch(void);
void ungetch(int);

int main()
{
	int n, status;

	status = getint(&n);

	if(status == 0)
		printf("Not a number.\n");
	
	else
		printf("Number:%d", n);
	return 0;
}



int getint(int *pn)
{
	int c, sign;

	while(isspace(c = getch()))
		;

	if(!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c);
		return 0;
	}

	sign = (c == '-') ? -1 : 1;

	if(c == '+' || c == '-')
	{
		int s = c;
		c = getch();
		if(!isdigit(c))
		{
			if(c != EOF)
				ungetch(c);
			ungetch(s);
			return 0;
		}
	}



	for(*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if(c != EOF)
		ungetch(c);

	return c;


}


int getch()
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}	




void ungetch(int c)
{
	if(bufp >= BUFSIZE)
		printf("ungetch: too many characters.");
	else
		buf[bufp++] = c;

}




