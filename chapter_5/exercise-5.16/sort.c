#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAXLINES 5000
#define MAXLEN   300

char *lineptr[MAXLINES];

int getLine(char dst[], int maxlen);
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void print_help();

void qSort(void *lineptr[], int left, int right, int (*cmp)(void *, void *));
int numcmp(const char *, const char *);
int rev_strcmp(const char *, const char *);
int dircmp(const char *s1, const char *s2);
void swap(void *v[], int i, int j);
char *to_lower_string(const char *str);
int strcmp_dispatch(const char *, const char *);
//flags
int numeric = 0;
int reverse = 0;
int fold    = 0;
int dir     = 0;

int main(int argc, char *argv[])
{
	int nlines;
	
	if(argc > 3)
	{
		printf("Error: Too many argumnets\n");
		print_help();
		return 1;
	}

	

	for(int i = 1; i < argc; i++)
	{
		if(argv[i][0] == '-')
		{
			for(int j = 1; argv[i][j] != '\0'; j++)
			{
				char flag = argv[i][j];
				switch (flag)
				{
					case 'n':
						numeric = 1;
						break;
					case 'r':
						reverse = 1;
						break;
					case 'f':
						fold    = 1;
						break;
					case 'd':
						dir     = 1;
						break;
					default: 
						printf("Error: Unknown argument.");
						print_help();
						return 1;
				}
			}
		}

		else
		{
			printf("Error: Invalid argument\n");
			print_help();
			return 1;

		}
	}	
	


	nlines = readlines(lineptr, MAXLINES);
	
	if(nlines == 0)
	{
		printf("Empty input");
		return 0;
	}


	if(nlines > 0)
	{
		qSort((void **) lineptr, 0, nlines-1, (int (*)(void *, void *))(numeric ?  numcmp : strcmp_dispatch));
		writelines(lineptr, nlines);
		return 0;
	}	
	else
	{
		printf("Error: Too big input(max length 300 characters)");
		return 1;
	}
}

void qSort(void *v[], int left, int right, int (*cmp)(void *, void *))
{
	int i, last;

	if(left >= right)
		return;

	swap(v, left, (left+right)/2);
	last = left;

	for(i = left+1; i <= right; i++)
		if((*cmp)(v[i], v[left]) < 0)
			swap(v, ++last, i);
	
	swap(v,left, last);
	qSort(v, left, last-1, cmp);
	qSort(v, last+1, right, cmp);
}

void swap(void *v[], int i, int j)
{	
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;

}

int strcmp_dispatch(const char *s1, const char *s2)
{
	if(fold == 1)
	{
		char *s1_lower = to_lower_string(s1);
	      	char *s2_lower = to_lower_string(s2);
		if(reverse == 1)
		{
			if(dir == 1)
				return dircmp(s2_lower, s1_lower);
			return strcmp(s2_lower, s1_lower);
		}
		if(dir == 1)
			return dircmp(s1_lower, s2_lower);
		return strcmp(s1_lower, s2_lower);	
	}

	if(reverse == 1)
		return strcmp(s2, s1);

	if(dir == 1)
		return dircmp(s2, s1);
	return strcmp(s1, s2);
}

int dircmp(const char *s1, const char *s2)
{
	int maxlen = fmax(strlen(s1), strlen(s2))-1;
	int i = 0;
	int j = 0;


	while(i != maxlen || j != maxlen)
	{
		if(s1[i] == '\0' || s2[j] == '\0')
			break;


		while(!isalnum(s1[i]) && s1[i] != ' ')
		      i++;

		while(!isalnum(s2[j]) && s2[j] != ' ')
		      j++;
	

		if(s1[i] != s2[j])
			break;

		i++;
		j++;
			
	}	
	
	if(s1[i] < s2[j])
		return -1;
	else if(s1[i] > s2[j])
		return 1;
	return 0;
}

int numcmp(const char *s1, const char *s2)
{
	double v1, v2;

	int result;

	v1 = atof(s1);
	v2 = atof(s2);

	if(v1 < v2)
		result = -1;

	else if(v1 > v2)
		result = 1;
	else
		return 0;

	if(reverse == 1)
		return -result;
	return result;
}

int readlines(char *lineptr[], int maxlines)
{
	int len, nlines;
	char *p, line[MAXLEN];

	nlines = 0;
	while((len = getLine(line, MAXLEN)) > 0)
	{
		p = malloc(len);
		
		if(nlines >= maxlines || p == NULL)
		{
			return -1;
		}

		else
		{
			line[len-1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
		}

	}
	return nlines;
}

int getLine(char dst[], int maxlen)
{
	int c;
	int i = 0;
	while(--maxlen > 0 && (c = getchar()) != EOF && c != '\n')
		dst[i++] = c;


	if(c == '\n')
		dst[i++] = '\n';

	dst[i] = '\0';

	return i;
}

void writelines(char *lineptr[], int nlines)
{
	for(int i = 0; i  < nlines; i++)
		printf("%s\n", lineptr[i]);
}

void print_help()
{
	printf("Usage: ./sort flags\n");
	printf("Flags:\t-n (for sort in numeric order), -r (for reverse sort), -f (to ignore case of letters when sorting).\n");
	printf("You can combine flags like -nr\n");

}


char *to_lower_string(const char *str)
{
	char  *lower_str = malloc(sizeof(str));

	for(int i = 0; str[i] != '\0'; i++)
		lower_str[i] = tolower(str[i]);

	return lower_str;
}
