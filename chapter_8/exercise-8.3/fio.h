#ifndef IO_FILE 
#define IO_FILE

#define NULL 0
#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20

typedef struct _iobuf {
	int cnt;
	char *ptr;
	char *base;
 	int flag;	
	int fd;	
} FILE;
extern FILE _iob[OPEN_MAX];

enum  _flags {
	_READ  = 01,
	_WRITE = 02,
	_UNBUF = 04,
	_EOF   = 010,
	_ERR   = 020
}; 

#define stdin  (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

#define feof(p) ((p)->flag.eof  != 0)
#define ferror(p) ((p)->flag.err  != 0)
#define fileno(p) ((p)->fd)

#endif
