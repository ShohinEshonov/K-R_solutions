#include <stdio.h>

void escape(char str[], char str2[]);

int main() {
  char str[] = "Hello\\n \\tWorld";
  char str2[5];
  escape(str2, str);
  printf("%s", str2);
  return 0;
}

void escape(char s[], char t[]) {
  int pos = 0;
  for (int i = 0; t[i] != '\0'; i++) {
    switch (t[i]) {
    case '\t': {
      s[pos++] = '\\';
      s[pos++] = 't';
      break;
    }

    case '\n': {
      s[pos++] = '\\';
      s[pos++] = 'n';
      break;
    }
    case '\\':
      switch (t[++i]) {
      case 't':
        s[pos++] = '\t';
        break;
      case 'n':
        s[pos++] = '\n';
        break;

      default:
        s[pos++] = '\\';
        s[pos++] = t[i];
        break;
      }
      break;
    default: {
      s[pos++] = t[i];
      break;
    }
    }
  }
  s[pos] = '\0';
}
