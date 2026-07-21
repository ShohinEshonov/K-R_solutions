#include <stdio.h>
#include <string.h>
#include <stdlib.h> 


#define MAXLINES 1000
#define MAXLEN 1000
#define MAXCHARS (MAXLINES) * (MAXLEN)

char *lineptr[MAXLINES];

int readLines(char *lineptr[], int nlines, char buffer[], int buffersize);
void writelines(char *lineptr[], int nlines);

void qSort(char *lineptr[], int left, int right);



int main()
{
	int nlines;
	
	char allstrs[MAXCHARS]; 

	if((nlines = readLines(lineptr, MAXLINES, allstrs, MAXCHARS)) >= 0) {
		qSort(lineptr, 0, nlines-1);
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("error: input too big to sort\n");
		return 1;
	}
}



int getLine(char *s, int lim)
{
	int c, i;

	for(i = 0; i < lim-1  && (c = getchar()) != EOF && c != '\n'; ++i)
		*s++ = c;

	if(c == '\n')
	{
		*s++ = c;
		++i;
	}	
	*s = '\0';

	return i;
}

int readLines(char *lineptr[], int maxlines, char buffer[], int buffersize)
{
	int   len, nlines, bufptr;
	char  line[MAXLEN];
	char  *p;

	bufptr = 0;
	nlines = 0;
	while((len = getLine(line, MAXLEN)) > 0) {
		if(nlines >= maxlines || bufptr + len > buffersize)
			return -1;
		else {
			line[len-1] = '\0';
			strcpy(&buffer[bufptr], line);
			lineptr[nlines++] = &buffer[bufptr];
			bufptr += len;
		}
	}
	return nlines;
}


void writelines(char *lineptr[], int nlines)
{
	while(nlines-- > 0)
		printf("%s\n", *lineptr++);
}

void qSort(char *v[], int left, int right)
{
	int i, last;
	void swap(char *v[], int i, int j);

	if(left >= right)
		return;

	swap(v, left, (left + right)/2);
	last = left;

	for(i = left+1; i <= right; i++)
		if(strcmp(v[i], v[left]) < 0)
			swap(v, ++last, i);
	
	swap(v, left, last);
	qSort(v, left, last-1);
	qSort(v, last+1, right);
}


void swap(char *v[], int i, int j)
{
	char *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}
