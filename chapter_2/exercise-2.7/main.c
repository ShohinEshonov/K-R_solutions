#include <stdio.h>


unsigned invert(unsigned num, unsigned pos, unsigned n);


int main()
{
	unsigned x = 6;
       	printf("%d", invert(x, 6, 2));
}


unsigned invert(unsigned x, unsigned p, unsigned n)
{	
	return x ^ (~(~0 << n)) << (p+1-n);
}

