#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char s[]);
void push(double);
double pop(void);

int main()
{
	int type;
	double op2;
	char s[MAXOP];

	while((type = getop(s)) != EOF)
	{
		switch(type) {
			case NUMBER:
				push(atof(s));
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '/':
				op2 = pop();
				if(op2 != 0.0)
					push(pop() / op2);
				else
					printf("error: zero devisor\n");
				break;

			case '\n':
				printf("\t%.8g\n", pop());
				break;
			default:
				printf("error: unknown command %s\n", s);
				break;
		
		}
	}
	return 0;
}

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

void push(double f)
{
	if(sp < MAXVAL)
		val[sp++] = f;
	else 
		printf("error: stack full, cant push %g\n", f);
}

double pop(void)
{
	if(sp > 0) 
		return val[--sp];
	else {
		printf("error: stack is empty\n");
		return 0.0;
	}	
}

#include <ctype.h>

int getch(void);
void ungetch(int);

int getop(char s[])
{
    int i, c;
    char ch;

    if (scanf("%c", &ch) != 1)
        return EOF;
    c = (unsigned char)ch;

    while (c == ' ' || c == '\t') {
        if (scanf("%c", &ch) != 1)
            return EOF;
        c = (unsigned char)ch;
    }

    s[0] = '\0';

    if (!isdigit((unsigned char)c) && c != '.')
        return c;

    i = 0;

    if (isdigit((unsigned char)c)) {
        while (isdigit((unsigned char)c)) {
            s[i++] = c;

            if (scanf("%c", &ch) != 1) {
                s[i] = '\0';
                return NUMBER;
            }

            c = (unsigned char)ch;
        }
    }

    if (c == '.') {
        s[i++] = c;

        while (1) {
            if (scanf("%c", &ch) != 1) {
                s[i] = '\0';
                return NUMBER;
            }

            c = (unsigned char)ch;

            if (!isdigit((unsigned char)c))
                break;

            s[i++] = c;
        }
    }

    s[i] = '\0';

    ungetc(c, stdin);

    return NUMBER;
}
