#include <stdio.h>


unsigned bitcount(unsigned num);




int main()
{
	unsigned x = 10;
	printf("%u", bitcount(x));

	return 0;
}




unsigned bitcount(unsigned x)
{
	unsigned b;

	for(b = 0; x != 0; x &= (x-1))
		b++;

	return b;
}




