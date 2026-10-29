#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAGE_LEN 20
#define TITLE_PAD 5 //in tabs
#define MAXLINE 500

void print_title(char *str);
int getLine(char *line, int max, FILE *fp);

int main(int argc, char *argv[])
{
	char *prog_name = argv[0];
	if(argc == 1) {
		fprintf(stderr, "Usage: %s <file_name> <file_name> ...", prog_name);
		return 1;
	}
	
	FILE *fp;
	char *fname;
	char line[MAXLINE];
	int lineno;
	int page;
	for(int i = 1; i < argc; i++) {
		fname = argv[i];
		fp = fopen(fname, "r");
		if(fp == NULL) {
			fprintf(stderr, "Error: cannot open file %s", fname);
			exit(1);
		}
		lineno = 0;
		page = 0;
		print_title(fname);
		while(getLine(line, MAXLINE, fp) > 0)
		{	
			if(lineno >= PAGE_LEN)
			{
				page++;
				char page_str[12];
				snprintf(page_str, sizeof(page_str), "%d", page);
				print_title(page_str);
				putchar('\n');
				print_title(fname);	
				lineno = 0;
				continue;
			}
			printf("%s", line);
			lineno++;
		}
		if(lineno < PAGE_LEN) {
			while(lineno < PAGE_LEN)
			{
				putchar('\n');
				lineno++;
			}
			page++;	
			char page_str[12];
			snprintf(page_str, sizeof(page_str), "%d", page);
			print_title(page_str);
			putchar('\n');
		}
	}
	return 0;
}	

void print_title(char *str) {
	for(int i = 0; i < TITLE_PAD; i++)
		putchar('\t');
	printf("%s\n", str);

}

int getLine(char *line, int max, FILE *fp)
{
	if(fgets(line, max, fp) == NULL)
		return 0;

	return strlen(line);
}
