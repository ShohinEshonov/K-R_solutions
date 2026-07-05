#ifndef CALC_H

#define CALC_H
#define NUMBER     '0'
#define IDENTIFIER '1'
#define VARIABLE   '2'


void push(double);
double pop(void);
double top(void);
void dup(void);
void swap(void);
void clear(void);
void trace(void);
int getop(char [], char[]);
//int getch(void);
//void ungetch(int);
//void ungets(char *s);
int getLine(char *s, int l);


#endif
