#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <ctype.h>


#define DEFAULT_TAIL 10
#define MAXLINES     5000
#define MAXLEN       300

char *lines[MAXLINES];

int getlines(int maxlines);
int getLine(char line[], int maxlen);
void validate_number(char *str); 
void tail(int lines_len, int tail_n);
void print_help();

int main(int argc, char *argv[])
{
	int tail_n = DEFAULT_TAIL;


	if(argc == 2)
	{
		if(argv[1][0] == '-')
		{
			char *num_ptr = &argv[1][1];
			validate_number(num_ptr);
			tail_n = atoi(num_ptr);
		}
		else
		{
			print_help(); 
			return 1;
		}
	}


	int lines_len = getlines(MAXLINES);
	if(lines_len < 0)
	{
		printf("Error: Too big input (max string len 300 characters).\n");
		return 1;
	}

	else if(lines_len == 0)
	{
		printf("Empty input");
		return 0;
	}



	tail(lines_len, tail_n);


	return 0;
}


void tail(int lines_len, int tail_n)
{
	printf("Tail:\n");
	
	if(lines_len <= tail_n)
	{
		for(int i = 0; i < lines_len; i++)
			printf("%s\n", lines[i]);	
		return;
	}


	int start_line = lines_len - tail_n;

	for(int i = start_line; i != lines_len; i++)
		printf("%s\n", lines[i]);
}



int getlines(int maxlines)
{
	int len, nlines;
	char *p, line[MAXLEN];

	
	nlines = 0;
	while((len =  getLine(line, MAXLEN)) > 0)
	{
		p = malloc(len);
		if(nlines >= MAXLINES || p == NULL)
			return -1;

		else
		{
			line[len-1] = '\0';
			strcpy(p, line);
			lines[nlines++] = p;
		}
	}

	return nlines;
}




int getLine(char dst[], int maxlen)
{
	int c;
	int len = 0;
	while(--maxlen > 0 && (c = getchar()) != EOF && c != '\n')
	{
		dst[len++] = c;
	}	
	
	if(c == '\n')
		dst[len++] = '\n';

	dst[len] = '\0';

	return len;
}


void validate_number(char *str) 
{
	for(int i = 0; str[i] != '\0'; i++)
	{
		if(!isdigit(str[i]))
		{
			printf("Error: Unexpected argument %s\n", str); 
			exit(1);
		}
	}
}

void print_help()
{
	printf("Usage: ./tail -n\n");
	printf("Arguments:\t-n number of lines to be printed from end(default is 10)\n");
}
