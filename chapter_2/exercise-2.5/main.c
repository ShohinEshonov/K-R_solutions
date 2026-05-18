#include <stdio.h>


int any(char str1[], char str2[]);




int main()
{
	char str[] = "Linus Torvalds";
	char ch[] = "xbd";
	
	int idx = any(str, ch);

	printf("%d", idx);


	return 0;
}

int any(char s1[], char s2[])
{
	int idx = -1;
	
	for(int i = 0; s2[i] != '\0'; i++)
	{
		for(int j = 0; s1[j] != '\0'; j++)
		{
			if(s2[i] == s1[j])
			{
				idx = j;
				break;
			}	
		}
		
		if(idx != -1)
		{
			break;
		}
	}
	return idx;
}





