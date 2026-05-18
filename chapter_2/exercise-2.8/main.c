#include <stdio.h>


unsigned rightrot(unsigned num, unsigned shift);


int main()
{
	unsigned x = 10;
	printf("%u", rightrot(x, 1));
	return 0;
}




unsigned rightrot(unsigned x, unsigned n)
{
	return (x >> n) | (x << ((sizeof(x)*8) - n));
}
