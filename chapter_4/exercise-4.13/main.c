#include <stdio.h>

void reverse(char str[], unsigned int start, unsigned int end);


int main()
{
	char s[] = "Hello";
	reverse(s,0 , 4);

	printf("%s\n", s);
}





void reverse(char s[], unsigned int start, unsigned int end)
{
	if(start >= end)
	       return;

	char tmp;
	tmp = s[start];
	s[start] = s[end];
	s[end] = tmp;

	reverse(s, start+1, end-1);	
}
