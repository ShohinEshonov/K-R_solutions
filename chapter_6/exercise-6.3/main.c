#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_OCC 1000

struct tnode {
	char *word;
	int lines[MAX_LINE_OCC];
	int word_count;
	struct tnode *left;
	struct tnode *right;
};

#define MAXWORD 100
#define MIN_WORD_LEN 3

int line = 1;

#define BUFSIZE 10
int bufp = 0;
char buf[BUFSIZE];

struct tnode *addtreex(struct tnode *, char *,  int);
void treexprint(struct tnode *);
int getword(char *, int);

int main(int argc, char *argv[]) 
{
	struct tnode *root;
	char word[MAXWORD];

	int res;
	root = NULL;
	while((res = getword(word, MAXWORD)) != EOF) {
		if(res == '\n')
		{
			line++;
			continue;
		}
		if(isalpha(word[0]) && strlen(word) > MIN_WORD_LEN) 
			root = addtreex(root, word, line);
	}
	treexprint(root);
	return 0;
}

struct tnode *talloc(void);

struct tnode *addtreex(struct tnode *p, char *w,  int line) 
{
	int cond;

	if(p == NULL)
	{
		p = (struct tnode *) malloc(sizeof(struct tnode));
		p->word=strdup(w);
		p->word_count = 0;
		p->lines[p->word_count++] = line;
		p->left=p->right=NULL;
	} 
	else if((cond = strcmp(w, p->word)) < 0)
		p->left=addtreex(p->left, w, line);
	else if(cond > 0)
		p->right=addtreex(p->right, w, line);
	else if(cond == 0)
	{
		p->lines[p->word_count++] = line;
	}
	return p;
}

void treexprint(struct tnode *p)
{
	if(p != NULL) {
		treexprint(p->left);
		if(p->word_count >= 1)
		{
			printf("%s:\n", p->word);
			printf("Occured on lines:");
			for(int i = 0; i < p->word_count; i++)
				printf("%d,", p->lines[i]);
			printf("\n");
		}
		treexprint(p->right);
	}
}

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if(bufp >= BUFSIZE)
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

	while((c = getch()) == ' ' || c == '\t')
		;

	if(c != EOF)
		*w++ = c;

	if(c == '#')
	{
		while((c = getch()) != '\n' && c != EOF);
		if(c == '\n')
			return c;

		return getword(dst, lim);
	}

	if(c == '/')
	{
		int next = getch();
		if(next == '/')
		{
			while((c = getch()) != '\n' && c != EOF);
			if(c == '\n')
				return c;

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
				if(c == '\n')
					line++;
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
