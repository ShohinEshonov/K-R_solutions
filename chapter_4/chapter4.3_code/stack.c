#include <stdio.h>
#include "calc.h"

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
		printf("error: stack empty\n");
		return 0;
	}

}


double top(void)
{	
	if(sp > 0)
		return val[sp-1];
	else{
		printf("error: stack empty\n");
		return 0.0;
	}
}


void dup(void)
{

	val[sp] = val[sp-1];
	sp++;	
}


void swap(void)
{
	double tmp = val[sp-1];
	val[sp-1] = val[sp-2];
	val[sp-2]   = tmp;
}



void clear(void)
{
	sp = 0;
}


void trace(void)
{
		while(sp > 0)
			printf("\t%.8g\n", pop());


}

