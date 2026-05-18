#include <stdio.h>

#define MAXLEN 26    //максимальная длина слова


int main()
{
	int c, len;
	int lengths[MAXLEN+1];

  for (int i = 0; i <= MAXLEN; ++i)
  	lengths[i] = 0;

	len = 0;
	while((c = getchar()) != EOF)
	{
		if(c != ' ' && c != '\n' && c != '\t')
			++len;
		else if(len > 0)
		{
			if(len <= MAXLEN)
				++lengths[len];
			else
				++lengths[MAXLEN];
			len = 0;
		}
	}

	if(len > 0)
	{
		if(len <= MAXLEN)
			++lengths[len];
		else 
			++lengths[MAXLEN];
	}

	for(int i = 1; i <= MAXLEN; ++i)
	{
		printf("%d: ", i);
		for(int j = 0; j < lengths[i]; ++j)
			printf("*");
		printf("\n");
	}

	return 0;
}


