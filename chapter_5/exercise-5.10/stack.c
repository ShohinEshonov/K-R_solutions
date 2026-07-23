#include <stdio.h>


#define MAXVAL 500


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
