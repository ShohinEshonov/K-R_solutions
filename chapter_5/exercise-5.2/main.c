#include <stdio.h>
#include <ctype.h>

#define BUFFSIZE 100

static int buf[BUFFSIZE];
static int buf_p = 0;

int getch(void);
void ungetch(int);
int getfloat(double *);


int main(void)
{
  double n;

  if(getfloat(&n)  == 0)
    printf("Not a number: 0\n");
  else
    printf("Number: %f\n", n);

  return 0;
}



int getfloat(double *pn)
{
  int c, sign;
  double power = 1.0;
  
  while(isspace(c = getch()))
    ;

  if(!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.')
  {
    ungetch(c);
    return 0;
  }


  sign = (c == '-') ? -1 : 1;

  if(c == '-' || c == '+' || c == '.')
  {
    int d = c;
    c = getch();

    if((d == '-' || d == '+') && c == '.')
    {
      int peek = c;
      c = getch();
      if(!isdigit(c))
      {
	if(c != EOF)
	 ungetch(c);
	ungetch(peek);
	ungetch(d);
	return 0;
      }
      ungetch(c);
      c = peek;
    }
 
    else if(!isdigit(c))
    {
      if(c != EOF)
	ungetch(c);
      ungetch(d);
      return 0;
    }
    else if(d == '.' && isdigit(c))
    {
      ungetch(c);
      c = d;
    }
  }

  for(*pn = 0; isdigit(c); c = getch())
    *pn = 10 * *pn + (c - '0');

  if(c == '.')
  {
    c = getch();
    for(power = 1.0; isdigit(c); c = getch())
    {
      *pn = 10 * *pn + (c - '0');
      power *= 10;
    }
  }

  *pn =(*pn * sign)/power;

  if(c != EOF)
    ungetch(c);

  return c;
  
}

int getch(void)
{
  return buf_p > 0 ? buf[--buf_p] : getchar();
}

void ungetch(int c)
{
  if(buf_p >= BUFFSIZE)
    printf("ungetch: Too many characters");
  else
    buf[buf_p++] = c; 
}








