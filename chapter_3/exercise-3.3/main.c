#include <stdio.h>
#include <ctype.h>









void expand(char str1[], char str2[]);



int main()
{
	char test[] = "a-c-e0-9";
	char result[1024];

	expand(test, result);

	printf("%s", result);

	return 0;
}







void expand(char s1[], char s2[])
{
	int pos = 0;
	for(int i = 0; s1[i] != '\0'; i++)
	{
		s2[pos++] = s1[i];
		if(s1[i+1] == '-') {
			if((islower(s1[i]) && islower(s1[i+2]) && s1[i] <= s1[i+2]) ||
			   (isupper(s1[i]) && isupper(s1[i+2]) && s1[i] <= s1[i+2]) ||
			   (isdigit(s1[i]) && isdigit(s1[i+2]) && s1[i] <= s1[i+2]))
			{
				for(char j = s1[i]+1; j < s1[i+2]; j++)
					s2[pos++] = j;
				i++;
			}
			
		}
	}

	s2[pos] = '\0';
}


