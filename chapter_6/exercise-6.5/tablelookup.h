#include <stdlib.h>
#include <string.h>

#ifndef HASHSIZE 
#define HASHSIZE 100
#endif

struct nlist {
	struct nlist *next;
	char *name;
	char *defn;
};


unsigned hash(char *str);
struct nlist *lookup(char *str);
struct nlist *install(char *name, char *defn);
void undef(char *name);
