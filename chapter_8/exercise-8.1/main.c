#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFSIZE 1024

void file_to_stdin(int fd, char *buf, int max);

int main(int argc, char *argv[]) {
	char *prog = argv[0];
	char buf[BUFSIZE];
	int fd;

	if(argc == 1) {
		int n;
		while((n = read(0, buf, 1)) > 0)
			if(write(1, buf, 1) != n) {
				fprintf(stderr, "Error: write error on stdin");
				exit(1);
			}
	}
	else
		while(--argc > 0)
	    		if((fd = open(*++argv, O_RDONLY, 0)) == -1) {
				fd = creat(*++argv, 0666);
				file_to_stdin(fd, buf, BUFSIZE);
			} else {
				file_to_stdin(fd, buf, BUFSIZE);
			}
	exit(0);
}

void file_to_stdin(int fd, char *bf, int max) 
{
	int n;
	while((n = read(fd, bf, max)) > 0)
		if(write(1, bf, n) != n) 
		{
			fprintf(stderr, "Error: write error on stdin");
			exit(1);
		}
}
