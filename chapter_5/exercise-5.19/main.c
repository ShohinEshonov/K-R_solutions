#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS, STAR };
enum { YES, NO };

int gettoken(void);
int peektoken(void);
int getch(void);
void ungetch(int c);

int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];
int previous_tokentype = NO;


int main()
{
	int type;
	char temp[MAXTOKEN];

	while(gettoken() != EOF) {
		strcpy(out, token);
		while((type = gettoken()) != '\n') {
			if(type == PARENS || type == BRACKETS) {
				strcat(out, token);
			} else if(type == STAR) {
				if((type = peektoken()) == PARENS || type == BRACKETS)
					sprintf(temp, "(*%s)", out);
				else
					sprintf(temp, "*%s", out);
				strcpy(out, temp);
			}	
			else if(type == NAME)	{
				sprintf(temp, "%s %s", token, out);
				strcpy(out, temp);
			} else
				printf("invalid input at %s\n", token);
		}
		printf("%s\n", out);
	}
	return 0;
}



int gettoken(void)
{
	int c;
	char *p = token;

	if(previous_tokentype == YES)
	{
		previous_tokentype = NO;
		return tokentype;
	}

	while((c = getch()) == ' ' || c == '\t')
		;
	
	if(c == '(') {
		if((c = getch()) == ')') {
			strcpy(token, "()");
			tokentype = PARENS;
		} else {
			ungetch(c);
			tokentype = '(';
		}
	} else if(c == '[') {
		for(*p++ = c; (*p++ = getch()) != ']'; )
			;

		*p = '\0';
	 	tokentype = BRACKETS;
	} else if(isalpha(c)) {
		for(*p++ = c; isalnum(c = getch()); ) 
			*p++ = c;
		*p = '\0';
		ungetch(c);
		tokentype = NAME;
	} else if(c == '*')
	       tokentype = STAR;	
	else
		tokentype = c;
	return tokentype;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int  bufp = 0;

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if(bufp >= BUFSIZE)
		printf("ungetch: Buffer overflow");
	else
		buf[bufp++] = c;
}



int peektoken(void)
{
	int type;

	type = gettoken();
	previous_tokentype = YES;
	return type;
}



