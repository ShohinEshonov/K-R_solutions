#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

struct tnode {
	char *word;
	int match;
	struct tnode *left;
	struct tnode *right;
};

#define MAXWORD 100
#define YES 1
#define NO 0

#define BUFSIZE 10
int bufp = 0;
char buf[BUFSIZE];

struct tnode *addtreex(struct tnode *, char *, int, int *);
void treexprint(struct tnode *);
int getword(char *, int);

int main(int argc, char *argv[]) 
{
	struct tnode *root;
	char word[MAXWORD];
	int found = NO;
	int num;

	num = (--argc && (*++argv[0] == '-')) ? atoi(argv[0]+1) : 6;
	root = NULL;
	while(getword(word, MAXWORD) != EOF) {
		if(isalpha(word[0]) && strlen(word) >= num) 
			root = addtreex(root, word, num, &found);
		found = NO;
	}
	treexprint(root);
	return 0;
}

struct tnode *talloc(void);
int compare(char *, struct tnode *, int, int *);

struct tnode *addtreex(struct tnode *p, char *w, int num, int *found) 
{
	int cond;

	if(p == NULL)
	{
		p = (struct tnode *) malloc(sizeof(struct tnode));
		p->word=strdup(w);
		p->match=*found;
		p->left=p->right=NULL;
	} else if((cond=compare(w, p, num, found)) < 0)
		p->left=addtreex(p->left, w, num, found);
	else if(cond > 0)
		p->right=addtreex(p->right, w, num, found);
	return p;
}

int compare(char *s, struct tnode *p, int num, int *found)
{
	int i;
	char *t=p->word;
	
	for(i = 0; *s==*t; i++, s++, t++)
		if(*s='\0')
			return 0;
	if(i >= num) {
		*found = YES;
		p->match = YES;
	}
	return *s-*t;
}

void treexprint(struct tnode *p)
{
	if(p != NULL) {
		treexprint(p->left);
		if(p->match)
			printf("%s\n", p->word);
		treexprint(p->right);
	}
}

int getch(void)
{
	return (bufp > 0) ? buf[bufp--] : getchar();
}

void ungetch(int c)
{
	if(bufp > BUFSIZE)
	{
		printf("Ungetch: Buffer overflow\n");
		return;
	}
	buf[bufp++] = c;
}

int getword(char *dst, int lim)
{
	int c;
	char *w = dst;

	while(isspace(c = getch()))
		;

	if(c != EOF)
		*w++ = c;

	if(c == '#')
	{
		while((c = getch()) != '\n' && c != EOF);
		return getword(dst, lim);
	}

	if(c == '/')
	{
		int next = getch();
		if(next == '/')
		{
			while((c = getch()) != '\n' && c != EOF);
			return getword(dst, lim);
		}
		else if(next == '*')
		{
			while((c = getch()) != EOF)
			{
				if(c == '*')
				{
					if((next = getch()) == '/') break;
					else ungetch(next);
				};
			}
			return getword(dst, lim);

		}
		ungetch(next);
	}

	if(c == '\"' || c == '\'')
	{
		int quote = c;
		while((c = getch()) != EOF)
		{
			if(c == '\\')
			{
				int next = getch();
				if(next == EOF)
					ungetch(next);
			}

			else if(c == quote)
				break;
		}
		return getword(dst, lim);
	}

	if(!isalpha(c) && c != '_')
	{
		*w = '\0';
		return c;
	}

	for(; --lim > 0; w++)
	{
		if(!isalnum(*w = getch()) && *w != '_')
		{
			ungetch(*w);
			break;
		}
	}
	 *w = '\0';
	 return dst[0];


}
