#include "dio.h"
#include <sys/stat.h>
#include <sys/dir.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define DIRSIZ 14

_DIR *_opendir(char *dirname) 
{	
	int fd;
	struct stat stbuf;
	_DIR *dp;

	if((fd = open(dirname, O_RDONLY, 0)) == -1
	|| fstat(fd, &stbuf) == -1
	|| (stbuf.st_mode & S_IFMT) != S_IFDIR
	|| (dp = (_DIR *) malloc(sizeof(_DIR))) == NULL)
		return NULL;

	dp->fd = fd;
	return dp;
}

void _closedir(_DIR *dp)
{
	if(dp) {
		close(dp->fd);
		free(dp);
	}
}

_Dirent *_readdir(_DIR *dp) 
{
	struct direct dirbuf;
	static _Dirent d;

	while(read(dp->fd, (char *) &dirbuf, sizeof(dirbuf)) == sizeof(dirbuf)) {
		if(dirbuf.d_ino == 0)
			continue;
		d.ino = dirbuf.d_ino;
		strncpy(d.name, dirbuf.d_name, DIRSIZ);
		d.name[DIRSIZ] = '\0';
		return &d;	
	}	
	return NULL;
}
