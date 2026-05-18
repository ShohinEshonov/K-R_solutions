#include <stdio.h>

double fahrToCels(int fahr);

int main()
{
	int fahr;
	for(fahr = 300; fahr >= 0; fahr = fahr - 20)
		printf("%3d %6.1f\n", fahr, fahrToCels(fahr));
	return 0;
}




double fahrToCels(int fahr)
{
	return (5.0/9.0)*(fahr-32);
}
