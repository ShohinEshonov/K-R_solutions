#include <stdio.h>
#include <string.h>
#include <ctype.h>


#define MAXTOKEN 100
#define BUFSIZE  10


enum {
	NAME, 
	PARENS,
	BRACKETS
};

enum {
	OK,
	ERROR 
};

int dcl(void);
int dirdcl(void);
void error(const char* err);

int gettoken(void);
int getch(void);
void ungetch(int);


int tokentype;
int bufp;
char buf[BUFSIZE];
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];

int main()
{
	while(gettoken() != EOF) {
		strcpy(datatype, token);
		out[0] = '\0';
		if(dcl() == OK && tokentype == '\n')
			printf("%s: %s %s\n", name, out, datatype);
		else
		{
			if(tokentype != '\n')
				printf("Error: Syntax error, missed \\n \n");
			for(int c = 0; c != '\n' && c != EOF; )	
				if((c = getch()) == EOF)
					ungetch(c);
		}


	}
	return 0;
}

int gettoken(void)
{
	int c;
	char *p = token;


	while((c = getch()) == ' ' || c == '\t')
	       ;

	if(c == '(') {
		if((c = getch()) == ')') {
			strcpy(token, "()");
			return tokentype = PARENS;
		} else
		{
			ungetch(c);
			return tokentype = '(';
		}
	} else if(c == '[') {
		for(*p++ = c; (*p++ = getch()) != ']'; )
			;
		*p = '\0';
		return tokentype = BRACKETS;
	} else if(isalpha(c)) {
		for(*p++ = c; isalnum(c = getch()); )
			*p++ = c;
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	} else 
		return tokentype = c;
}

int dcl(void)
{
	int ps;
	
	for(ps = 0; gettoken() == '*'; )
		ps++;
	if(dirdcl() == ERROR)
		return ERROR;
	while(ps-- > 0)
		strcat(out, " pointer to");
	return OK;
}

int dirdcl(void)
{
	int type;

	if(tokentype == '(') {
		if(dcl() == ERROR)
			return ERROR;
		if(tokentype != ')')
		{
			printf("Error: missing )\n");
			return ERROR;	
		}
	} else if(tokentype == NAME)
		strcpy(name, token);
	else
	{
		printf("expected name or (dcl)");
		return ERROR;
	}
	
	while((type = gettoken()) == PARENS || type == BRACKETS)
		if(type == PARENS) 
			strcat(out, " function returning");
		else {
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
	return OK;
}

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int ch)
{
	if(bufp >= BUFSIZE)
		printf("Ungetch: Buffer overflow\n");
	else
		buf[bufp++] = ch;
}
