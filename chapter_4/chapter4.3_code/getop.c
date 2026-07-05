#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "calc.h"

static int line_i = 0;

int getop(char s[], char token[])
{
	int i = 0;
	while(s[line_i]  == ' ' || s[line_i] == '\t')
	       line_i++;
	 	
	if(s[line_i] == '\0' || s[line_i] == '\n')
	{
		int temp = s[line_i];
		line_i = 0;
		return temp == '\n' ? '\n' : EOF;
	}
	
	
	if(isupper(s[line_i]))
	{
		token[i++] = s[line_i++];
		token[i] = '\0';
		return VARIABLE;
	}
	if(!isdigit(s[line_i]) && !isalpha(s[line_i]) && s[line_i] !='.' && s[line_i] !='-')
		return s[line_i++];
	
	if(isalpha(s[line_i]))
	{
		while(isalpha(s[line_i]))
		{
			token[i++] = s[line_i++];
		}	
		token[i] = '\0';
		
		if(s[line_i] != '\0' && s[line_i] != '\n')
			--line_i;
		return IDENTIFIER;

	}

	if(s[line_i] == '-')
	{
		int next = s[line_i+1];
		if(!isdigit(next) && next != '.')
		{
			if(next != '\0' && next != '\n')
				--line_i;
			return s[line_i++];
		}
		token[i++] = s[line_i++];
	}
	if(isdigit(s[line_i]))
		while(isdigit(s[line_i]))
		{
			token[i++] = s[line_i++];
		}
			
	if(s[line_i] == '.')
		token[i++] = s[line_i++];
		while(isdigit(s[line_i]))
			token[i++] = s[line_i++];

	token[i] = '\0';
	return NUMBER;
}








