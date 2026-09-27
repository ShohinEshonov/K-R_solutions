#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

struct word {
	char *word;
	int count;
};

struct tnode {
	struct word word;
	struct tnode *left;
	struct tnode *right;
};

#define MAXWORD 1000
#define MAXWORDS 10000
#define BUFSIZE 10
int bufp = 0;
char buf[BUFSIZE];

struct tnode *addtreex(struct tnode *, char *);
int getword(char *, int);
void tree_to_array(struct tnode *root, struct word words[], int *n);
int comparator(const void* a, const void* b);
void print_words(struct word words[], int);

int main(int argc, char *argv[]) 
{
	struct tnode *root;
	char word[MAXWORD];

	int res;
	root = NULL;
	while((res = getword(word, MAXWORD)) != EOF) {
		if(isalpha(word[0])) 
			root = addtreex(root, word);
	}
	int n = 0;
	struct word words[MAXWORDS];

	tree_to_array(root, words, &n);


	qsort(words, n, sizeof(words[0]), comparator);

	print_words(words, n);

	return 0;
}

struct tnode *addtreex(struct tnode *p, char *w) 
{
	int cond;

	if(p == NULL)
	{
		p = (struct tnode *) malloc(sizeof(struct tnode));
		p->word.word = strdup(w);
		p->word.count = 1;
		p->left=p->right=NULL;
	} 
	else if((cond = strcmp(w, p->word.word)) < 0)
		p->left=addtreex(p->left, w);
	else if(cond > 0)
		p->right=addtreex(p->right, w);
	else if(cond == 0)
		p->word.count++;
	
	return p;
}

void tree_to_array(struct tnode *root, struct word words[], int *n) 
{
	if(root == NULL)
		return;

	
	tree_to_array(root->left, words, n);


	words[*n].word = root->word.word;
	words[*n].count = root->word.count;
	(*n)++;

	tree_to_array(root->right, words, n);
}



int comparator(const void* a, const void* b)
{
	const struct word *w1 = a;
	const struct word *w2 = b;

	return w2->count - w1->count;
}

void print_words(struct word words[], int n)
{
	for(int i = 0; i < n; i++)
		printf("%s : Finded %d times.\n", words[i].word, words[i].count);

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
