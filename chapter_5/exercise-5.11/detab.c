#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINE 300
#define ON 1
#define OFF 0
#define DEFAULT_TABSTOP 8

void validate_number(char *str);
void init_tabstops_array(int arr[], int len);
void detab();


static int tabstops_arr[MAXLINE];


int main(int argc, char *argv[])
{
	int arr_len = 1;
	if(argc > 1)
		arr_len = argc-1;

	int tabstop_args[arr_len];
	int args_p  = 0;
	for(int i = 1; i < argc;  i++)
	{
		validate_number(argv[i]);
		int number = atoi(argv[i]);
		if(number >= 300 || number <= 0)
		{
			printf("Error: Invalid argument %d\n", number);
			exit(1);
		}
		tabstop_args[args_p++] = number;
	}
	init_tabstops_array(tabstop_args, args_p);
	detab();
	return 0;
}


void detab()
{
	int position, c;

	position =  0;
	while((c = getchar()) != EOF && c != '\n')
	{
		if(c != '\t')
		{
			++position;
			putchar(c);
		}
		if(c == '\t')
		{
			int spaces = 0;
			if(position < MAXLINE)
			{
				int target = position+1;
				while(target < MAXLINE && tabstops_arr[target] != ON)
					target++;
				
				spaces = target - position;

				for(int i = 0; i < spaces; ++i)
					putchar(' ');
				position = target;
			}
			else
			{
				spaces = DEFAULT_TABSTOP - (position % DEFAULT_TABSTOP);
				for(int i = 0; i < spaces; i++)
					putchar(' ');

				position += spaces;
			}
		}
	}
	putchar('\n');
}


	


void init_tabstops_array(int arr[], int len)
{
	if(len == 0)
	{
		int last_pos = 0;
		while(last_pos + DEFAULT_TABSTOP < 300)
		{
			tabstops_arr[last_pos+DEFAULT_TABSTOP] = ON;
		       	last_pos += DEFAULT_TABSTOP;	
		}
		return;
	}




	int i = 0;
	for(i = 0; i < len; i++)
		tabstops_arr[arr[i]] = ON; 

	if(arr[len-1] + DEFAULT_TABSTOP <= 300)
	{
		int last_pos = arr[len-1];
		while(last_pos + DEFAULT_TABSTOP < 300)
		{
			tabstops_arr[last_pos+DEFAULT_TABSTOP] = ON;
		       	last_pos += DEFAULT_TABSTOP;	
		}

	}	

		
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


