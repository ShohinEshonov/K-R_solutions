#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000

int getLine(char line[], int max, FILE *fp);

int main(int argc, char *argv[]) {
	char *prog_name = argv[0];
	
	if(argc < 2)
	{
		fprintf(stderr, "Usage: %s <file_name_1> <file_name_2>", prog_name);
		return 0;
	}

	char *fname1 = argv[1];
	char *fname2 = argv[2];

	FILE *fp1 = fopen(fname1, "r");
	FILE *fp2 = fopen(fname2, "r");

	if(fp1 == NULL) {
		fprintf(stderr, "Error: cannot open file %s", fname1);
		exit(1);
	}
	
	if(fp2 == NULL) {
		fprintf(stderr, "Error: cannot open file %s", fname2);
		exit(1);
	}

	char line_f1[MAXLINE];
	char line_f2[MAXLINE];
	int line_num = 0;

	if(getLine(line_f1, MAXLINE, fp1) == 0) {
		fprintf(stderr, "Error: cannot read file %s", fname1);
		exit(2);
	}	

	if(getLine(line_f2, MAXLINE, fp2) == 0) {
		fprintf(stderr, "Error: cannot read file %s", fname2);
		exit(2);
	}	

	line_num++;
	
	int llen1 = 0;
	int llen2 = 0;

	while(1) {
		llen1 = getLine(line_f1, MAXLINE, fp1);
   	     	llen2 = getLine(line_f2, MAXLINE, fp2);

    		if(llen1 == 0 && llen2 == 0)
       			 break;

    		if(llen1 == 0) {
        		fprintf(stderr, "Error: file %s shorter than %s\n",
                	fname1, fname2);
        		exit(2);
    		}

    		if(llen2 == 0) {
        		fprintf(stderr, "Error: file %s shorter than %s\n",
                	fname2, fname1);
        		exit(2);
    		}

    		if(strcmp(line_f1, line_f2) != 0) 
    			break;
	
	}	
		
	printf("Result: \n");

	int last_res = strcmp(line_f1, line_f2);
	
	if(last_res == 0) 
		printf("Files dont have difference\n");
	
	else  
		printf("Line %d: %s\n", line_num, line_f1);

	fclose(fp1);
	fclose(fp2);
	return 0;
}

int getLine(char *line, int max, FILE *fp)
{
	if(fgets(line, max, fp) == NULL)
		return 0;
	else 
		return strlen(line);
}
