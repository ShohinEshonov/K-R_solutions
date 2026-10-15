#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define LIMIT 100000

#define NLINE_L 20
#define HEX 1
#define OCTAL 0

int getLine(char *s, int lim);
void print_string_formated(char *line);


int main() 
{
	char line[LIMIT];
	
	getLine(line, LIMIT);
	print_string_formated(line);

	return 0;
}

void print_string_formated(char *line)
{	
	char num_holder[LIMIT];
	int hold_p = 0;
	int line_len = strlen(line);

	for(int i = 0; i < line_len; i++) 
	{
		if(i % NLINE_L == 0)
			putchar('\n');
		if(isdigit(line[i])) {
			hold_p = 0;
			while(isdigit(line[i]) && i < line_len)
				num_holder[hold_p++] = line[i++];	
			
			num_holder[hold_p] = '\0';		

			long long num = strtol(num_holder, NULL, 10);

			if(OCTAL == 1)
				printf("%llo", num);
			
			else if(HEX == 1)
				printf("%llx", num);
			
			putchar(line[i]);
			continue;	
		}

		putchar(line[i]);
	}
}

int getLine(char *s, int lim)
{
	int c, i;

	i = 0;

	while(--lim > 0 && (c = getchar()) != EOF && c != '\n')
	{
		*s++ = c;
		i++;
	}
	*s = '\0';
	return i;
}
