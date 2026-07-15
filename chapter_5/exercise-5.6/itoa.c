#include <stdio.h>
#include <string.h>

void itoa(int n, char *s);
void reverse(char *s);


int main()
{
	int n = 498559;
	char s[100];

	itoa(n, s);

	printf("s = %s\n", s);
	return 0;

}


void reverse(char *s)
{
	int c;
	char *t;

	for(t = s + (strlen(s)-1); s < t; s++, t--)
	{
		c = *s;
		*s = *t;
	        *t = c;	
	}
}

void itoa(int n, char *s)
{
	int sign;
	char *bs = s;
	sign = n;

	do
	{
		*s++ = n % 10 + '0';
	}while((n /= 10) > 0);

	if(sign < 0)
		*s++ = '-';

	*s = '\0';

	reverse(bs);
}








