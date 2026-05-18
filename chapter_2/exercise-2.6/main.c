#include <stdio.h>

unsigned setbits(unsigned num1, unsigned pos, unsigned n, unsigned num2);

int main()
{
	unsigned x = 4;
	printf("%d", setbits(x, 3, 4,6));
	return 0;
}


unsigned setbits(unsigned x, unsigned p, unsigned n, unsigned y)
{
	int shift = p+1-n;
	x &= ~(~(~0<<n) << shift);
       	x |= (y & ~(~0<<n)) << shift;	
	return x;	
}
