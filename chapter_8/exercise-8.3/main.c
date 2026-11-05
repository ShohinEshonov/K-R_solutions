#include "fio.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int _flushbuf(int c, FILE *fp) 
{
	int bufsiz, num_written;
	unsigned char uc = c;
	
	if((fp->flag & (_WRITE | _EOF | _ERR)) != _WRITE) 
		return EOF;

	if(fp->base == NULL && ((fp->flag & _UNBUF) == 0)) {
		if((fp->base = malloc(BUFSIZ)) == NULL)
			fp->flag |= _UNBUF;
		else {
			fp->ptr = fp->base;
			fp->cnt = BUFSIZ;
		}
	}
	
	if(fp->flag  & _UNBUF) {
		fp->ptr = fp->base;
		fp->cnt = 0;

		if(c == EOF) return EOF;
		num_written = write(fp->fd, &uc, 1);
		bufsiz = 1;
	}
	else
	{
		bufsiz = (int) (fp->ptr - fp->base);
		num_written = write(fp->fd, fp->base, bufsiz);
		fp->ptr = fp->base;
		fp->cnt = bufsiz - 1;
		if(c != EOF)
			*fp->ptr++ = uc;
	}

	if(num_written == bufsiz) 
		return c;
	else {
		fp->flag |= _ERR;
		return EOF;
	}	
}
