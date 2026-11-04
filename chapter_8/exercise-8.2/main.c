#include "fio.h"
#include <fcntl.h>
#include <unistd.h>

#define PERMS 0666


FILE _iob[OPEN_MAX] = {
     { 0, NULL, NULL, { .read = 1 },             0 },
     { 0, NULL, NULL, { .write = 1 },            1 },
     { 0, NULL, NULL, { .write = 1, .unbuf = 1 }, 2 }
};

FILE *fopen(char *name, char *mode) 
{
	int fd;
	FILE *fp;

	if(*mode != 'r' && *mode != 'w' && *mode != 'a') 
		return NULL;
	for(fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if((fp->flag.write == 0) && (fp->flag.read == 0))
			break;
	if(fp >= _iob + OPEN_MAX)
		return NULL;

	if(*mode == 'w')
		fd = creat(name, PERMS);
	else if(*mode == 'a') {
		if((fd = open(name, O_WRONLY, 0)) == -1)
			fd = creat(name, PERMS);
		lseek(fd, 0L, 2);
	} else 
		fd = open(name, O_RDONLY, 0);
	if(fd == -1)
		return NULL;
	fp->fd = fd;
	fp->cnt = 0;
	fp->base = NULL;
	if(*mode == 'r') 
		fp->flag.read = 1;
	else
		fp->flag.write = 1;
	return fp;
}
