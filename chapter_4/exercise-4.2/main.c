#include <stdio.h>
#include <ctype.h>
#include <math.h>


#define MAXLINE 1024
double atof(char num[]);
int getLine(char str[], int lim);


int main()
{
	char line[MAXLINE];
	double result;	

	while(getLine(line, MAXLINE) > 0)
	{
		result = atof(line);
		printf("%.10f\n", result);
	}
	return 0;
}



int getLine(char s[], int lim)
{
	int i = 0;
	int c;	
	while(--lim > 0 && (c = getchar()) != EOF && c!= '\n')
		s[i++] = c;
	s[i] = '\0';

	return i;
}




double atof(char s[])
{
	double val, power, exponent;
	int i, sign, exponent_sign;
	
	for(i = 0; isspace(s[i]); i++)
		;

	sign = (s[i] == '-') ? -1 : 1;
	
	if(s[i] == '-' || s[i] == '+')
		i++;
	for(val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	
	if(s[i] == '.')
		i++;
	
	for(power = 1.0; isdigit(s[i]); i++)
	{
		val = 10.0 * val + (s[i] - '0');
		power *= 10.0;
	}

	exponent = 0.0;
	exponent_sign = 1;




	if(s[i] == 'e' || s[i] == 'E')
		i++;

	exponent_sign = (s[i] == '-') ? -1 : 1;
	
	if(s[i] == '-' || s[i] == '+')
		i++;
	for(exponent = 0.0; isdigit(s[i]); i++)
		exponent = 10 * exponent + (s[i] - '0');
	
	exponent *= exponent_sign;

	val = sign * val / power;

	val = val * pow(10.0, exponent);	

	return val;

}

