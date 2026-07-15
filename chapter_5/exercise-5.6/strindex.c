#include <stdio.h>

int strindex(char *s, char *t);



int main()
{
	char *s = "Hello World";

	char *t = "World";

	int index = strindex(s,t);
	if(index >= 0)
		printf("%s\n", s);
	printf("%d\n", index);
	return 0;
}




int strindex(char *s, char *t)
{
	int i, j, k;


	for(i = 0; *(s+i) != '\0'; i++)
	{
		for(j = i, k = 0; *(t+k) != '\0' && *(s+j) == *(t+k); j++, k++)
		;
		if(k > 0 && *(t+k) == '\0')
		       return i;	
	}	
	return -1;
}



