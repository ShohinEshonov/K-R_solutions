#include <stdio.h>


void squeeze(char str1[], char str2[]);

int main()
{
	char s[] = "Hello World";
	char ch[] = "l";
	squeeze(s, ch);
	printf("%s", s);
	return 0;
}



void squeeze(char s1[], char s2[])
{
	int i,j,k;

	
	k = 0;
	for(i = 0; s2[i] != '\0'; i++)
	{
		for(j = 0; s1[j] != '\0'; j++)
		{
			if(s2[i] != s1[j])
				s1[k++] = s1[j];
		}

		s1[k] = '\0';
		k = 0;
	}
}

