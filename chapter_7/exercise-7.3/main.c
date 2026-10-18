#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define STR_LEN 10
#define FIELD_LEN 10

void miniprintf(char *, ...);

int main()
{
	char *test = "hello, world";

	miniprintf(":%s:\n:%10s:\n:%.10s:\n:%-10s:\n:%.15s:\n:%-15s:\n:%15.10s:\n:%-15.10s:\n", test, test, test, test, test, test, test, test);
	
	miniprintf("|%d|\n", 123);
	miniprintf("|%5d|\n", 123);
	miniprintf("|%-5d|\n", 123);
	miniprintf("|%.5d|\n", 123);
	miniprintf("|%8.5d|\n", 123);
	miniprintf("|%-8.5d|\n", 123);
	miniprintf("|%2d|\n", 123);

	miniprintf("|%f|\n", 3.14159);
	miniprintf("|%.2f|\n", 3.14159);
	miniprintf("|%10.2f|\n", 3.14159);
	miniprintf("|%-10.2f|\n", 3.14159);
	miniprintf("|%3.2f|\n", 3.14159);

	miniprintf("Name: %-10.5s Age: %3d Score: %.2f!\n","Alexander", 21, 9.876);
}

void miniprintf(char *fmt, ...) 
{
	va_list ap;
	
	char *p, *sval;
	int ival;
	double dval;

	char str_len[STR_LEN];
	char field_len[FIELD_LEN];
	
	int istr_len_f = 0;
	int ifield_len_f = 0;
	
	int istr_len;
	int ifield_len;
	
	char *strl_p = str_len;
	char *fieldl_p = field_len;

	va_start(ap, fmt);
	for(p = fmt; *p; p++) {
		if(*p != '%') 
		{ 
			putchar(*p);
			continue;
		}

		++p;
		
		if(*p == '-')
		{
			*fieldl_p++ = '-';
			++p;
		}

		if(isdigit(*p))
		{
			while(isdigit(*p))
				*fieldl_p++ = *p++;
			--p;
			*fieldl_p = '\0';
			ifield_len = atoi(field_len);
			ifield_len_f = 1;
			++p;
		}

		if(*p == '.')
		{
			p++;
			while(isdigit(*p)) 
				*strl_p++ = *p++;
			--p;
			*strl_p = '\0';
			istr_len = atoi(str_len);
			istr_len_f = 1;
			++p;
		}

		if(*p == 'd')
		{
			ival = va_arg(ap, int);
			if(istr_len_f  && ifield_len_f)
				printf("%*.*d", ifield_len, istr_len, ival);
			else if(istr_len_f && ifield_len_f == 0) 
				printf("%.*d", istr_len, ival);
			else if(istr_len_f == 0 && ifield_len_f)
				printf("%*d", ifield_len, ival);
			else printf("%d", ival);
			strl_p = str_len;
			fieldl_p = field_len;
			ifield_len_f = 0;
			istr_len_f = 0;
			continue;
		}

		else if(*p ==  'f') 
		{
			dval = va_arg(ap, double);
			if(istr_len_f && ifield_len_f)
				printf("%*.*f", ifield_len, istr_len, dval);
			else if(istr_len_f && ifield_len_f == 0) 
				printf("%.*f", istr_len, dval);
			else if(istr_len_f == 0 && ifield_len_f)
				printf("%*f", ifield_len, dval);
			else printf("%f", dval);

			strl_p = str_len;
			fieldl_p = field_len;
			ifield_len_f = 0;
			istr_len_f = 0;	
			continue;
		}

		else if(*p == 's')
		{	
			sval = va_arg(ap, char*);
			int len = strlen(sval);

			if(istr_len_f && istr_len < len)
				len = istr_len;	

			if(ifield_len_f && ifield_len > len)
			{
				for(int i = len; i < ifield_len; i++)
					putchar(' ');
			}
			
			for(int i = 0; i < len; i++)
				putchar(*sval++);
			if(ifield_len_f && ifield_len < 0)
			{
				ifield_len = -ifield_len;
				for(int i = len; i < ifield_len; i++)
					putchar(' ');	
			}
			strl_p = str_len;
			fieldl_p = field_len;
			ifield_len_f = 0;
			istr_len_f = 0;			
			continue;
		}
	}
	va_end(ap);
}
