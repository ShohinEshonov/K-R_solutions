#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>



#define DEFAULT_START 1 
#define DEFAULT_STEP  8


void validate_number(char *);
void entab(int start, int step);
void print_help();


int main(int argc, char *argv[])
{
	int start = DEFAULT_START;
	int step  = DEFAULT_STEP;  

			


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
			printf("erro: invalid argument\n");
			print_help();
			exit(1);
		}
	
	}
	
	if(start < 0 || step < 0)
	{
		printf("error: invalid arguments\n");
		exit(1);
	}
	entab(start, step);
	return 0;
}



void validate_number(char *str) 
{
	for(int i = 0; str[i] != '\0'; i++)
	{
		if(!isdigit(str[i]))
		{
			printf("error: unexpected argument %s\n", str); 
			exit(1);
		}
	}
}



void entab(int start, int step)
{
	int c, pos, blanks; 

	pos = 1;
	blanks = 0;
	while((c = getchar()) != EOF)
	{
		if(c == '\n')
		{
			pos    = 1;
			blanks = 0;
		}
		if(c == ' ')
		{
			blanks++;
			
			int current_step = (pos >= start) ? step : DEFAULT_STEP;
			int next_tabstop = pos + (current_step - ((pos-1) % current_step));

			if(pos + 1 == next_tabstop)
			{
				putchar('\t');
				blanks = 0;
			}
			pos++;
		}
		else
		{
			while(blanks > 0)
			{
				putchar(' ');
				blanks--;
			}

			putchar(c);

			if(c == '\t')
			{
				int current_step = (pos >= step) ? step : DEFAULT_STEP;
				pos += current_step - ((pos-1) % current_step); 
			}
			else
			{
				pos++;
			}
		}

	}
	while(blanks > 0)
	{
   		putchar(' ');
    		blanks--;
	}

}



void print_help()
{
	printf("Usage: ./entab -m +n\n");
	printf("Argumnts: -m - starting column\n");
	printf("\t  -n - step for every tabstop starting from -m\n");
	printf("All arguments optional\n");
	printf("Default argumnets: -m = 0 and +n = 8\n");
}
