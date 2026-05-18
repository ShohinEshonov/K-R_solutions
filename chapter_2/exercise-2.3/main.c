#include <stdio.h>


int htoi(char str[], int len);

int main()
{
	char num[7]  = "0xA539F";
	printf("%d", htoi(num, 7));
	return 0;
}




int htoi(char s[], int l)
{	
	int  i = 0;
	int  result = 0; 
	int  n;

	if(s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
		i = 2;
	
	for(; i < l; ++i)
	{
		if(s[i] >='0' && s[i] <= '9')
				n = s[i] - '0';
		else if(s[i] >= 'a' && s[i] <= 'f')
			n = s[i] - 'a' + 10;
		else if(s[i] >= 'A' && s[i] <= 'F')
			n = s[i] - 'A' + 10;
		result = 16 * result + n;
	}
	return result;
}
