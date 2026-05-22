#include <stdio.h>
#define MAXLINE 1000


int getLine(char str[], int max);
int strindex(char source[], char pattern[]);


char pattern[] = "at";

int main()
{
	char line[MAXLINE];
	int found = 0;
	int pos;
	
	while(getLine(line, MAXLINE) > 0)
	{
		if((pos = strindex(line, pattern)) >= 0)
		{
			printf("%d\n", pos);
			found++;
		}

	}
	

	return found;


	
}





int getLine(char s[], int l)
{
	int c;
	int i = 0; 
	while(--l > 0 && (c = getchar()) != EOF && c !='\n')
		s[i++] = c;
	if(c == '\n')
		s[i++] = c;
	s[i] = '\0';

	return i;
}




int strindex(char s[], char p[])
{
	int k, j;
	int prev = -1;
	
	for(int i = 0; s[i] != '\0'; i++) {
		for(j = i, k = 0; p[k] != '\0' && s[j] == p[k]; j++, k++)
			;
		if(k > 0 && (p[k] == '\0') && prev < i)
				prev = i;
	}

	return prev;
}






int strindex2(char s[], char p[])
{
        int len;
        int k, j;
        for(len = 0; s[len] != '\0'; len++)
                ;
        len -= 1;

        for(int i = len; i >= 0; i--) {
                for(int j = i, k = 0; p[k] != '\0' && s[j] == p[k]; j--, k++)
                        ;
                if(k > 0 && (p[k] == '\0'))
                        return i;
        }

        return -1;
}
