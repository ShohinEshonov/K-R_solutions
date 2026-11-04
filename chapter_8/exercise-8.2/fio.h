#ifndef IO_FILE 
#define IO_FILE

#define NULL 0
#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20

typedef struct {
	unsigned int read:1;
	unsigned int write:1;
	unsigned int unbuf:1;
	unsigned int eof:1;
	unsigned int err:1;
} F_FLAGS;

typedef struct _iobuf {
	int cnt;
	char *ptr;
	char *base;
	F_FLAGS flag;	
	int fd;	
} FILE;
extern FILE _iob[OPEN_MAX];

#define stdin  (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

#define feof(p) ((p)->flag.eof  != 0)
#define ferror(p) ((p)->flag.err  != 0)
#define fileno(p) ((p)->fd)

#endif
