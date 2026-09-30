#include <stdio.h>
#include "tablelookup.h"

#define HASHSIZE 4

static struct nlist *hashtab[HASHSIZE];

int main()
{
	install("INT", "32");
	install("FLOAT", "32");
	install("INT_64", "64");
	install("DOUBLE", "64");



	struct nlist *p;
	for(int i = 0; i < HASHSIZE; i++)
	{
		for(p = hashtab[i]; p != NULL; p = p->next)
			printf("name: %s, defn: %s\n", p->name, p->defn);
	}


	undef("INT");
	undef("FLOAT");
	
	printf("After undefined INT and FLOAT\n");

	for(int i = 0; i < HASHSIZE; i++)
	{
		for(p = hashtab[i]; p != NULL; p = p->next)
			printf("name: %s, defn: %s\n", p->name, p->defn);
	}
	
	install("INT", "64");
	install("FLOAT", "16");


	printf("After defined INT and FLOAT to new  values\n");
	for(int i = 0; i < HASHSIZE; i++)
	{
		for(p = hashtab[i]; p != NULL; p = p->next)
			printf("name: %s, defn: %s\n", p->name, p->defn);
	}

	return 0;
}

unsigned hash(char *s)
{
	unsigned hashval;

	for(hashval = 0; *s != '\0'; s++)
	      hashval = *s+31*hashval;
	return hashval % HASHSIZE;	
}

struct nlist *lookup(char *s)
{
	struct nlist *np;

	for(np = hashtab[hash(s)]; np != NULL; np = np->next)
		if(strcmp(s, np->name) == 0)
			return np;
	return NULL;
}

struct nlist *install(char *name, char *defn)
{
	struct nlist *np;
	unsigned hashval;


	if((np = lookup(name)) == NULL) {
		np = (struct nlist *) malloc(sizeof(*np));

		if(np == NULL || (np->name = strdup(name)) == NULL)
				return NULL;
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	} else 
		free((void *) np->defn);
	if((np->defn = strdup(defn)) == NULL) 
		return NULL;
	return np;
}


void undef(char *name)
{
	struct nlist *np;
	struct nlist *prev;
	unsigned hashval = hash(name);

	if((np = lookup(name)) == NULL)
		return;
	else {
		if((np = lookup(name)) == hashtab[hash(name)])
		{
			hashtab[hashval] =  np->next; 

			free(np->name);
			free(np->defn);
			return;
		}
		
		for(np = hashtab[hash(name)]; np != NULL;)
		{
			prev = np;
			np = np->next;
		}

		prev->next = np->next;
		free(np->name);
		free(np->defn);
	}
}
