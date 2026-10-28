#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 1000

int getLine(char line[], int max, FILE *fp);

int main(int argc, char *argv[])
{
    char *prog_name = argv[0];
    char line[MAXLINE];
    long lineno = 0;
    int c, except = 0, number = 0, found = 0;
    FILE *fp;

    if (--argc == 0)
        exit(2);

    while (argc > 0 && (*++argv)[0] == '-') {
        argc--;

        while ((c = *++argv[0]))
            switch (c) {
                case 'x':
                    except = 1;
                    break;

                case 'n':
                    number = 1;
                    break;

                default:
                    fprintf(stderr, "Find: illegal option %c\n", c);
                    return 2;
            }
    }

    if (argc != 1) {
        char *pattern = *argv;
	
        while (argc > 1) {
            argc--;

            fp = fopen(argv[argc], "r");

            if (fp == NULL) {
                fprintf(stderr, "Error: cannot open %s\n", argv[argc]);
                exit(1);
            }
	    
            lineno = 0;

            while (getLine(line, MAXLINE, fp) > 0) {
                lineno++;

                if ((strstr(line, pattern) != NULL) != except) {
                   found++;
		   if(found > 0)
            		printf("%s\n", argv[argc]);
		   if (number)
                        printf("%ld: ", lineno);

                    printf("%s", line);
                }
            }
	    found = 0;
            fclose(fp);
        }
    }
    else {
        while (getLine(line, MAXLINE, stdin) > 0) {
            lineno++;

            if ((strstr(line, *argv) != NULL) != except) {
                if (number)
                    printf("%ld: ", lineno);

                printf("%s", line);
                found++;
            }
        }
    }

    return found;
}

int getLine(char line[], int max, FILE *fp)
{
    if (fgets(line, max, fp) == NULL)
        return 0;
    else
        return strlen(line);
}
