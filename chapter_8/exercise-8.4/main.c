#include "fio.h"
#include <fcntl.h>
#include <unistd.h>

int fseek(FILE *fp, long offest, int origin);

int _fseek(FILE *fp, long offset, int origin) 
{
	if(fp->flag & _WRITE) {
		if(_fflush(fp) == EOF)
			return EOF;
		if(lseek(fp->fd, offset, origin) == -1)
			return EOF;
	} else if(fp->flag & _READ) {
		if(origin == SEEK_CUR && fp->cnt > 0)
			offset -= fp->cnt;
		if(lseek(fp->fd, offset, origin) == -1)
			return EOF;
		fp->cnt = 0;
		fp->ptr = fp->base;
	}
	else 
		return EOF;

	fp->flag &= ~_EOF; 
	return 0;
}

