#include <limits.h> //for NAME_MAX

typedef struct {
	long ino;
	char name[NAME_MAX+1];
} _Dirent;

typedef struct {
	int fd;
	_Dirent d;
}_DIR;

_DIR *_opendir(char *dirname);
_Dirent *_readdir(_DIR *dfd);
void _closedir(_DIR *dfd);
