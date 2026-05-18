#include <stdio.h>
#include <sys/types.h>

#define MAXCOL 10
#define TABSTOP 8

char line[MAXCOL];

void printline(int pos);
int findlastblank(int pos);
int rerange(int pos);

int main() {
  int c, pos;

  pos = 0;
  while ((c = getchar()) != EOF) {
    line[pos] = c; //copying chars to array
    ++pos; //increment position 

    if (c == '\t') {
      --pos; //decrement bc we need to get before \t
      while (pos < MAXCOL && pos % TABSTOP != 0) {
        line[pos] = ' '; //replace it with ' ' bc tab can be either 6,4,8 characters wide we need occurate wide
        ++pos; 
      }
      if (pos >= MAXCOL) {
        printline(pos); //if pos>= MAXCOL we dont have anything else in line array only blanks we just print the array line
        pos = 0; //we assign 0 bc we dont have anything else in line array and we start filling it from start again
      }
    } else if (c == '\n') {
      --pos; //we get before \n
      printline(pos); //we just print what we have
      pos = 0; //we start from 0 filling array
    } else if (pos >= MAXCOL) {
      pos = findlastblank(pos); //we need find last blank to devide line into lines
      printline(pos); //we print from 0 to pos(lastblank)
      pos = rerange(pos); //we need to shift array to left to print remainder of line
    }
  }
}

void printline(int pos) {
  for (int i = 0; i < pos; ++i) //we just print everything until pos
    putchar(line[i]);
  putchar('\n');
}

int findlastblank(int pos) {
  while (pos >= 0 && line[pos] != ' ')
    --pos;

  if (pos < 0) //we dont have blanks we just devide line by MAXCOLs
    return MAXCOL;
  else
    return pos+1; 
}


int rerange(int pos){
  if(pos == MAXCOL){
    return 0;
  }
  int i = 0;
  for(int j = pos; j < MAXCOL; ++j)
  {
    line[i] = line[j]; //basicly we just shifting array with 2 poniters
    ++i;
  }
  return i;
}
