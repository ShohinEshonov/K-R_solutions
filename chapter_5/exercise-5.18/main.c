#include <stdio.h>
#include <string.h>
#include <ctype.h>


#define MAXTOKEN 100
#define BUFSIZE  10


enum {
	NAME,
       	NUMBER,	
	OPEN_PAREN,
	CLOSE_PAREN,
	OPEN_BRACKET,
	CLOSE_BRACKET,
	STAR,
	END_OF_FILE,
	NEW_LINE,
	UNKNOWN_TOKEN,
	
	EMPTY,
};

enum {
	OK,
	ERROR 
};

int dcl(void);
int dirdcl(void);
void error(const char* err);

int gettoken(void);
void ungettoken(void);
int peektoken(void);
int getch(void);
void ungetch(int);


int tokentype = EMPTY;
int bufp;
char buf[BUFSIZE];
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];
int previous_tokentype = EMPTY;

int main()
{
	while(gettoken() != EOF) {
		strcpy(datatype, token);
		out[0] = '\0';
		if(dcl() == OK && tokentype == NEW_LINE)
			printf("%s: %s %s\n", name, out, datatype);
		else
		{
			if(tokentype != NEW_LINE)
				printf("Error: Syntax error, missed \\n \n");
			
			for(int c = 0; c != NEW_LINE && c != END_OF_FILE; )	
				if((c = getch()) == EOF)
					ungetch(c);
		}


	}
	return 0;
}

int gettoken(void)
{
	int c;
	int type;
	char *p = token;


	while((c = getch()) == ' ' || c == '\t')
	       ;

	if(c == '(') 
		type = OPEN_PAREN;
	
	else if(c == ')')
		type = CLOSE_PAREN;
	
	else if(c == '[') {
		*p++ = c;
		*p = '\0';
		type = OPEN_BRACKET;
	}else if(c == ']')
		type = CLOSE_BRACKET;	

	else if(isalpha(c)) {
		for(*p++ = c; isalnum(c = getch()); )
			*p++ = c;
		*p = '\0';
		ungetch(c);
		type = NAME;
	}
	else if(isdigit(c))
	{
		*p++ = c;
		while(isdigit(c = getchar()))
		       *p++ = c;
		*p = '\0';
		ungetch(c);
		type = NUMBER;	
	}
	else if(c == '\n')
       		type = NEW_LINE;	
	else if(c == EOF)
		type = END_OF_FILE;
	else	
		type = UNKNOWN_TOKEN;
		
	previous_tokentype = tokentype;

	return tokentype = type;
}

int dcl(void)
{
	int ps;
	
	for(ps = 0; gettoken() == STAR; )
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

	if(tokentype == OPEN_PAREN) {
		if(peektoken() == CLOSE_PAREN)
		{
			gettoken();
			strcat(out, " function returning");
		}
		else if(dcl() == ERROR)
			return ERROR;
	
		if(tokentype != CLOSE_PAREN)
		{
			ungettoken();
			printf("Error: missing )\n");
			return ERROR;	
		}
	} else if(tokentype == NAME)
		strcpy(name, token);
	else if(tokentype  == OPEN_BRACKET)
	{
		strcat(out, "array");
		dirdcl();	
	}
	else if(tokentype == NUMBER)
	{
		if(previous_tokentype == OPEN_BRACKET)
			strcat(out, token);

		else 
		{
			printf("Error: Unexpected number\n");
			return ERROR;
		}
	}
	else if(tokentype == CLOSE_BRACKET)
	{
		if(previous_tokentype == OPEN_BRACKET || previous_tokentype == NUMBER)
		{
			strcat(out, token);
			strcat(out, "of");
		}
		else
			printf("Error: Unexpected ]\n");
			return ERROR;
	}
	else
		printf("expected name or (dcl)");
	
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

void ungettoken(void)
{
	int c;
	if(tokentype == NUMBER || tokentype == NAME)
	{
		int token_len = strlen(token);
		for(int i = 0; i < token_len; i++)
			ungetch(token[i]);
	}
	tokentype = previous_tokentype;
}

int peektoken(void)
{
	int token = gettoken();
	ungettoken();
	return token;
}
