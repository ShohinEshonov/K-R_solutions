#include <stdio.h>
#include <limits.h>
#include <math.h>



int main()
{
	const float float_min =1.0 * pow(2, 1-127);
	const float float_max = (2 - pow(2, -23)) * pow(2, 127);
	const double double_min = 1.0 * pow(2, -1022); 
	const double double_max = (2 - pow(2, -52)) * pow(2, 1023);
	printf("CHAR min:%d, max:%d\n",  CHAR_MIN, CHAR_MAX);
	printf("UNSIGNED CHAR min: 0, max:%d\n", UCHAR_MAX);
	printf("INT min:%d, max:%d\n",  INT_MIN, INT_MAX);
	printf("UNSIGNED INT min: 0, max:%u\n", UINT_MAX);
	printf("SHORT  min:%hd, max:%hd\n",  SHRT_MIN, SHRT_MAX);
	printf("UNSIGNED SHORT min: 0, max:%hu\n",  USHRT_MAX);
	printf("LONG min:%ld, max:%ld\n", LONG_MIN, LONG_MAX);
	printf("UNSIGNED LONG min:0, max:%lu\n", ULONG_MAX);
	printf("FLOAT min:%e, max:%e\n", float_min, float_max);
	printf("DOUBLE min:%e, max:%e\n", double_min, double_max);
	return 0;
}

