#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>



#define DEFAULT_START 1 
#define DEFAULT_STEP  8
#define MAXLINE       300




void validate_number(char *);
void detab(int start, int step);
void print_help();


int main(int argc, char *argv[])
{
	int start = DEFAULT_START;
	int step  = DEFAULT_STEP;  

	if(argc == 1)
	{
		start = DEFAULT_START;
		step  = DEFAULT_STEP; 
	}
			


	if(argc > 3) 
	{
		print_help();
		exit(1);
	}


	char *num_ptr;
	for(int i = 1;  i < argc; i++)
	{
		if(argv[i][0] == '-')
		{
			num_ptr = &argv[i][1];
			validate_number(num_ptr);
			start = atoi(num_ptr);
		}
		else if(argv[i][0] == '+')
		{
			num_ptr = &argv[i][1];
			validate_number(num_ptr);
			step = atoi(num_ptr);
		}
		else
		{
			printf("Erro: Invalid argument\n");
			print_help();
			exit(1);
		}
	
	}
	
	if(start < 0 || step < 0)
	{
		printf("Error: Invalid arguments\n");
		exit(1);
	}
	detab(start, step);
	return 0;
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



void detab(int start, int step)
{
	int pos,c;

	pos = 1;
	while((c = getchar()) != EOF)
	{
		if(c == '\n')
		{
			putchar(c);
			pos = 1;
			continue;
		}
		if(c != '\t')
		{
			++pos;
			putchar(c);
		}
		if(c == '\t')
		{
			int spaces;
			if(pos >= start)
				spaces = (step - ((pos - start) % step)) + 1;
			else
			{
				putchar('\t');
				pos += (DEFAULT_STEP - (pos % DEFAULT_STEP))+1;
				continue;
			}
			while(spaces-- > 0)
			{
				putchar(' ');
				pos++;
			}

		}

	}
}



void print_help()
{
	printf("Usage: ./detab -m +n\n");
	printf("Argumnts: -m - starting column\n");
	printf("\t  -n - step for every tabstop starting from -m\n");
	printf("All arguments optional\n");
	printf("Default argumnets: -m = 0 and +n = 8\n");
}
