#include <stdio.h>


int strncmp(char *s, char *t, int n);



int main()
{
	char *s = "Hella";
	char *t = "Hello";

	int res = strncmp(s, t, 5);

	printf("%d\n", res);
	return 0;
}




int strncmp(char *s, char *t, int n)
{
	while(n > 0)
	{
		if(*s < *t)
			return 1;
		else if(*s > *t)
			return -1;
		*s++;
		*t++;
		n--;
	}
	return 0;
}



