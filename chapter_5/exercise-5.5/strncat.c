#include <stdio.h>

char *strncat(char *s, char *t, int n);



int main()
{	
	char s[30] = "Hello ";
	s[6] = '\0';
	char *t    = "World";

	char *res = strncat(s, t, 5);


	printf("%s\n", res);

	return 0;
}



char *strncat(char *s, char *t, int n)
{	
	char *bs = s;

	while(*s)
		*s++;

	while(n > 0 && *t != '\0')
	{
		*s++ = *t++;
		n--;
	}

	*s = '\0';
	return bs;
}
