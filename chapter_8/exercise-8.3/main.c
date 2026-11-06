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
		num_written = (bufsiz > 0) ?  write(fp->fd, fp->base, bufsiz) : 0;
		fp->ptr = fp->base;
		if(c != EOF)
		{
			*fp->ptr++ = uc;
			fp->cnt =  BUFSIZ - 1;
		}
		else
			fp->cnt = BUFSIZ;
	}

	if(num_written == bufsiz) 
		return 0;
	else {
		fp->flag |= _ERR;
		return EOF;
	}	
}

int _fflush(FILE *fp)
{
	if((fp->flag & _WRITE) == 0)
		return 0;

	if(fp->flag & (_ERR | _EOF))
		return EOF;

	if(fp->base == NULL || (fp->flag & _UNBUF))
		return 0;

	int bufsiz = (int) (fp->ptr - fp->base); 
	int num_written = (bufsiz > 0) ? write(fp->fd, fp->base, bufsiz) : 0;

	fp->ptr = fp->base;
	fp->cnt = BUFSIZ;

	if(num_written == bufsiz)
		return 0;
	else {
		fp->flag |= _ERR;
		return EOF;
	}
}	

int _fclose(FILE *fp) 
{
	int result = 0;
	if(fp->flag  & _WRITE)
		result = _fflush(fp); 
	if(close(fp->fd) < 0) result = EOF;

	if(fp->base != NULL) free(fp->base);
	
	fp->cnt = 0;
	fp->ptr = NULL;
	fp->base = NULL;
	fp->fd = -1;
	fp->flag = 0;

	return result;
}
