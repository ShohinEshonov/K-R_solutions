#include <stdio.h>



void strcat(char *, char *);





int main()
{

	//we cannot test this solution on char *s bc char *s doest have enough space to contain Hello World People with out malloc
	char s[17] = "Hello World";
	s[11] = '\0';
	char *t = " People";

	strcat(s, t);

	printf("%s\n", s);
	
	return 0;
}




void strcat(char *s, char *t)
{
	while(*s)
		s++;

	while(*s++ = *t++) 
		;
}	
