#include <stdio.h>


int strend(char *, char  *);


int main()
{
	char *s = "";
	char *t = "";
	
	int is_end = strend(s, t);
	printf("is_end:%d\n", is_end);
	return 0;
}




int strend(char *s, char *t)
{
	char *bs = s; 
	char *bt = t;

	for(; *s; s++)
		;

	for(; *t; t++)
		;



	for(; *s == *t; s--, t--)
		if(t == bt || s == bs)
			break;


	if(*s == *t && t == bt)
		return 1;

	return 0;

}
