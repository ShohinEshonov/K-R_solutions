#include <stdio.h>


char *strncpy(char *s, char *t, int n);


int main()
{
	char s[] = "Hello";
	char *t  = "World";

	char *r = strncpy(s, t, 5);
	printf("%s\n", r);
	return 0;
}


char *strncpy(char *s, char *t, int n)
{
	char *st  = s;

	while(n > 0 && *t != '\0')
	{
		*s++ = *t++;
		n--;
	}

	while(n > 0)
	{
		*s++ = '\0';
		n--;
	}

	return st;

}



