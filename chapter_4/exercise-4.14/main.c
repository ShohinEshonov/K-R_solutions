#include <stdio.h>
#define swap(t,x,y)  t tmp = x; x = y; y=tmp;



int main()
{
  int a = 67;
  int b = 13;
  swap(int, a, b);
  printf("a:%d, b:%d", a, b);
  return 0;
  
}
