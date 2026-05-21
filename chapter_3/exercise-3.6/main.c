#include <stdio.h>

void reverse(char str[]); 
void itoa(int num, char str[], int field_width);



int main()
{
	int num = 101020;
	char s[20];
	int width = 10;

	itoa(num, s, width);

	printf("%s", s);

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

void itoa(int n, char s[], int fw)
{
	int i, sign;
	sign = n;

	i = 0;
	do
	{
		int digit = n%10;
		if(digit < 0)
		{
			digit = -digit;
		}
		digit += '0';
		s[i++] = digit;
	}while((n /=10) > 0);
	if(sign < 0)
		s[i++] = '-';
	if(i < fw)
	{
		unsigned padding = fw - i;
		for(unsigned j = 0; j < padding; j++)
			s[i++] = ' ';
	}
	s[i] = '\0';
	reverse(s);
}	
