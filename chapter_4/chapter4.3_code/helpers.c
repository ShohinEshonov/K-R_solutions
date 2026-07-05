#include <stdio.h>
#include <string.h>


#define BUFFSIZE 100


static int buf;
static int is_full = 0;

//int bufp = 0;


//int getch(void)
//{
//	if(is_full)
//	{
//		is_full = 0;
//		return buff;
//	}   
//		
//	return getchar();
//}



//void ungetch(int c)
//{	
//	if(is_full)
//	{
//		printf("ungetch: too many characters.");
//	}
//	else
//	{
//		buf = c;
//		is_full = 1;
//	}
//}

int getLine(char* s, int lim)
{
	int c; 
	int i = 0;
	while(i < lim-1 && (c = getchar()) != EOF && c!='\n')
	       s[i++] = c;
	if(c == '\n')
		s[i++] = '\n';
	s[i] = '\0';
	return i;
}



//void ungets(char *s)
//{
//	for(int i=strlen(s)-1; i >= 0; i--)
//		ungetch(s[i]);
//}
