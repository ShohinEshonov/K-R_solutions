#include <stdio.h>
#include <stdlib.h>

void itoa(int number, char str[], unsigned int len);

int main()
{
	int n = -10293;
	int z = -19383;

	char s[7];
	s[7] = '\0';
	
	char a[7];
	a[7] = '\0';
	itoa(n, s, 7);
	itoa(z, a, 7);

	printf("%s\n",s);
	printf("%s\n",a);
}


void itoa(int n, char s[], int l)
{
	static int i = 0;
	int sign = n;

	if(sign < 0 && i == 0) 
		s[i++] = '-';

	if(n/10)
		itoa(n/10, s, l);

	s[i++] = abs(n%10)+'0';
      	s[i] = '\0';


	if(i == l - 1)
		i = 0;
}
