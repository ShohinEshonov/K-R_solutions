#include <stdio.h>


int main()
{
	int c;
	int freq[26];

	for(int i = 0; i < 26; ++i)
		freq[i] = 0;

	while((c = getchar()) != EOF)
	{
		if(c >= 'a' && c <= 'z')
			++freq[c-'a'];
		if(c >= 'A' && c <= 'Z')
			++freq[c-'A'];
	}

	for(int i = 0; i < 26; ++i)
	{
		printf("%c - %d: ", i+'a', freq[i]);
		for(int j = 0; j < freq[i]; ++j)
			printf("*");
		printf("\n");
	}
	return 0;
}
