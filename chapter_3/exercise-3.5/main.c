#include <stdio.h>


void reverse(char str[]);
void itob(int num, char str[], int base);



int main()
{
	int num = 255;
	char str[20];
	int base = 16;

	itob(num, str, base);

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

void itob(int n, char s[], int b)
{
	int pos = 0;
	int digit;
	do
	{	
		int digit;
		digit = n%b;
		if(b == 16)
		{
			switch (digit)
			{
				case 10:
					s[pos++] = 'A';
					break;
				case 11: 
					s[pos++] = 'B';
					break;
				case 12: 
					s[pos++] = 'C';
					break;
				case 13:
					s[pos++] = 'D';
					break;
				case 14:
					s[pos++] = 'E';
					break;
				case 15:
					s[pos++] = 'F';
					break;
				default:
					s[pos++] = digit + '0';
					break;
			}

		}
		else
			s[pos++] = digit + '0';
		n = n/b;
	}while(n != 0);
	if(b == 16)
	{
		s[pos++] = 'x';
		s[pos++] = '0';
	}
	s[pos] = '\0';
	reverse(s);
}
