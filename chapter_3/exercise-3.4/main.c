#include <stdio.h>
#include <stdlib.h>


void reverse(char str[]);
void itoa(int num, char str[]);


int main()
{
	int num = -2147483648;
	char str[20];

	itoa(num, str);
	printf("%s", str);

	return 0;
}


void reverse(char s[])
{
	int len;
	char c;
	for(len = 0; s[len] != '\0'; len++)
		;
	len -= 1;
	for(int i = 0; i < len; i++, len--)
	{
		c = s[i];	
		s[i] = s[len];
		s[len] = c;
	}
}

void itoa(int n, char s[])
{
	int i, sign;
	
	sign = n;

	i = 0;


	do
	{
		s[i++] = abs(n%10)+'0';
	}while((n/=10) != 0);	
	
	if(sign < 0)
		s[i++] = '-';
	s[i] = '\0';

	reverse(s);
}










